#include "qserialwork.h"

qSerialWork::qSerialWork(QString portName, QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError"); // Register the custom type
    m_portName = portName;

    dataProcessor = new DataProcessor();
    dataProcessor->moveToThread(&processingThread);

    connect(this,&qSerialWork::newDataAvailable, dataProcessor, &DataProcessor::appendData);
    connect(&processingThread, &QThread::started, dataProcessor, &DataProcessor::processData);
    connect(this, &qSerialWork::triggerProcessData, dataProcessor, &DataProcessor::processData);
    connect(dataProcessor,&DataProcessor::dataProcessed, this, &qSerialWork::msg_recevied);
    processingThread.start();
}

qSerialWork::~qSerialWork()
{
    serialPort->close();
    processingThread.quit();
    processingThread.wait();
    delete dataProcessor;
    //    qDebug() << "serial port distructor;";
}



void qSerialWork::start()
{
    // qDebug() << "hello";
    serialPort = new QSerialPort();
    connect(serialPort, &QSerialPort::readyRead, this, &qSerialWork::dataArrived);
    connect(serialPort, &QIODevice::aboutToClose, this, &qSerialWork::SerialAboutToClose);
    connect(serialPort, &QSerialPort::errorOccurred, this, &qSerialWork::SerialErrorOccurred);

    serialPort->setPortName(m_portName);
    //    qDebug() << "seirla port com:"<<m_portName;
    serialPort->setBaudRate(QSerialPort::Baud57600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setReadBufferSize(65536);
    if(serialPort->open(QIODevice::ReadWrite))
    {
        // Success
        //        qDebug() << "serial port opened";
    }
    else
    {
        // Handle error
    }
}

void qSerialWork::stop()
{
    //    qDebug() << "serial port stop pressed;";
    serialPort->close();
    emit finished(); // Notify that the worker is finished
}

void qSerialWork::serialPort_Close()
{
    serialPort->close();
    //    qDebug() << "serial port closed function;";
}

bool qSerialWork::get_serialPort_openSTS()
{
    if(serialPort->isOpen())
    {
        return true;
    }
    else
    {
        return false;
    }
}

qint64 qSerialWork::writeData(const char* buf, qint64 len)
{
    //    qDebug() << "writeData() Thread ID:" << QThread::currentThreadId();
    if(serialPort->isOpen() && serialPort->isWritable()) {
        return serialPort->write(buf, len);
    } else {
        // Log an error or handle it appropriately
        //        qDebug() << "Serial port is not ready for writing.";
        //        QMessageBox::information(this,tr("Error"),"Open Serial Port");
        return -1; // Indicate that the write operation was not successful
    }
}

void qSerialWork::dataArrived()
{
    //    qDebug() << "dataArrived() Thread ID:" << QThread::currentThreadId();
    //    QByteArray data1 = serialPort->readAll();
    //    qDebug() <<"serial receive" << data1;
    //    serialPort->waitForBytesWritten(5);
    //    emit this->newData(data1);
    //    mutex.lock();
    //    buffer.append(serialPort->readAll());
    //    mutex.unlock();
    // Consider signaling that data has arrived for processing if necessary

//    mutex.lock();
    QByteArray data = serialPort->readAll();
//    qDebug() <<"serial receive" << data;
//    mutex.unlock();
    emit newDataAvailable(data); // Append new data for processing
    emit triggerProcessData(); // Trigger processing on new data arrival
}

void qSerialWork::SerialErrorOccurred(QSerialPort::SerialPortError error)
{
    //    qDebug() <<"error print from serialwork" << error;
    emit this->sig_SerialErrorOccurred(error);
}

void qSerialWork::SerialAboutToClose()
{
    //    qDebug() <<"in serial about to close";
    emit this->sig_SerialAboutToClose();
}

void qSerialWork::msg_recevied(const QByteArray &message)
{
    //qDebug() << "ms_receive_from data process:" << message;
    emit msg_process(message);
}
