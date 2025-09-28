#include "qserialwork_bittest.h"
#include "dataprocessor.h"
#include <QDebug>

SerialWork_Bittest::SerialWork_Bittest(const QString &portName, bool isWriter, QObject *parent)
    : QObject(parent)
    , port(portName)
    , writer(isWriter)
{
    serial = new QSerialPort(this);
    serial->setPortName(port);
    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    dataProcessor = new DataProcessor();
    dataProcessor->moveToThread(&processingThread);

    connect(this, &SerialWork_Bittest::newDataAvailable, dataProcessor, &DataProcessor::appendData);
    connect(this,
            &SerialWork_Bittest::triggerProcessData,
            dataProcessor,
            &DataProcessor::processData);
    connect(dataProcessor, &DataProcessor::dataProcessed, this, &SerialWork_Bittest::msg_received);

    processingThread.start();
}

SerialWork_Bittest::~SerialWork_Bittest()
{
    if (serial->isOpen())
        serial->close();

    processingThread.quit();
    processingThread.wait();
    delete dataProcessor;
}

void SerialWork_Bittest::start()
{
    if (!serial->open(QIODevice::ReadWrite)) {
        //        qDebug() << "[ERROR] Failed to open port:" << port << "Error:" << serial->errorString();
        //        emit portOpenedCurrent(false);
        return;
    }

    //    qDebug() << "[INFO] Opened port:" << port << "in ReadWrite mode";
    connect(serial, &QSerialPort::readyRead, this, &SerialWork_Bittest::readFromPort);

    //    emit portOpenedCurrent(true);
}

qint64 SerialWork_Bittest::writeData(const char *buf, qint64 len)
{
    // emit clear_buffer();
    if (serial->isOpen() && serial->isWritable()) {
        return serial->write(buf, len);
    } else {
        //        qDebug() << "Serial port is not ready for writing.";
    }

    return -1;

    //    if (writer && serial->isOpen()) {
    //        //        qDebug() << "@@[TX]" << serial->portName() << data.toHex(' ').toUpper();
    //        return serial->write(data);
    //    }
    //    return -1;
}

void SerialWork_Bittest::readFromPort()
{
    QByteArray data = serial->readAll();
    //    qDebug() << "data.toHex" << data.toHex();
    //    qDebug() << "data" << data;

    if (!data.isEmpty()) {
        emit newDataAvailable(data);
        emit triggerProcessData();
    }
}

void SerialWork_Bittest::msg_received(const QByteArray &message)
{
    //    qDebug() << "[RX]" << serial->portName() << message.toHex(' ').toUpper();
    emit msg_process(message);
}

bool SerialWork_Bittest::isConnected() const
{
    return serial && serial->isOpen();
}
