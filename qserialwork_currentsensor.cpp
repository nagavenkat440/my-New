#include "qserialwork_currentsensor.h"
#include "dataprocessor.h"
#include <QDebug>

SerialWork_CurrentSensor::SerialWork_CurrentSensor(const QString &portName,
                                                   bool isWriter,
                                                   QObject *parent)
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

    connect(this,
            &SerialWork_CurrentSensor::newDataAvailable,
            dataProcessor,
            &DataProcessor::appendData);
    connect(this,
            &SerialWork_CurrentSensor::triggerProcessData,
            dataProcessor,
            &DataProcessor::processData);
    connect(dataProcessor,
            &DataProcessor::dataProcessed,
            this,
            &SerialWork_CurrentSensor::msg_received);

    processingThread.start();
}

SerialWork_CurrentSensor::~SerialWork_CurrentSensor()
{
    if (serial->isOpen())
        serial->close();

    processingThread.quit();
    processingThread.wait();
    delete dataProcessor;
}

void SerialWork_CurrentSensor::start()
{
    if (!serial->open(QIODevice::ReadWrite)) {
        //        qDebug() << "[ERROR] Failed to open port:" << port << "Error:" << serial->errorString();
        //        emit portOpenedCurrent(false);
        return;
    }

    //    qDebug() << "[INFO] Opened port:" << port << "in ReadWrite mode";
    connect(serial, &QSerialPort::readyRead, this, &SerialWork_CurrentSensor::readFromPort);

    //    emit portOpenedCurrent(true);
}

qint64 SerialWork_CurrentSensor::writeData(const QByteArray &data)
{
    if (writer && serial->isOpen()) {
        //        qDebug() << "@@[TX]" << serial->portName() << data.toHex(' ').toUpper();
        return serial->write(data);
    }
    return -1;
}

void SerialWork_CurrentSensor::readFromPort()
{
    QByteArray data = serial->readAll();
    //    qDebug() << data.toHex();

    if (!data.isEmpty()) {
        emit newDataAvailable(data);
        emit triggerProcessData();
    }
}

void SerialWork_CurrentSensor::msg_received(const QByteArray &message)
{
    //    qDebug() << "[RX]" << serial->portName() << message.toHex(' ').toUpper();
    emit msg_process(message);
}
