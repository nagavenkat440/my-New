#ifndef QSERIALWORK_H
#define QSERIALWORK_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QByteArray>
#include <dataprocessor.h>

QT_BEGIN_NAMESPACE
namespace Ui { class qSerialWork; }
QT_END_NAMESPACE

class qSerialWork : public QObject
{
    Q_OBJECT


public:
    explicit qSerialWork(QString portName, QObject *parent = nullptr);
    ~qSerialWork();


signals:
    void finished(); // Add this line
    void sig_SerialErrorOccurred(QSerialPort::SerialPortError error);
    void sig_SerialAboutToClose();
    void newDataAvailable(QByteArray data);
    void triggerProcessData();
    void msg_process(const QByteArray &message);

private slots:
    void dataArrived();
    void SerialAboutToClose();
    void SerialErrorOccurred(QSerialPort::SerialPortError error);
    void msg_recevied(const QByteArray &message);

public slots:
    void start(); // Starts serial port operations
    void stop();  // Stops serial port operations
    void serialPort_Close();
    bool get_serialPort_openSTS();
    qint64 writeData(const char* buf, qint64 len);

private:
    QSerialPort *serialPort;
    QString m_portName;
    QByteArray buffer; // Buffer for incoming data
    QMutex mutex; // Mutex for thread-safe access to the buffer
    QThread processingThread;
    DataProcessor *dataProcessor;
};

#endif // QSERIALWORK_H
