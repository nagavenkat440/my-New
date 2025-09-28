#ifndef QSERIALWORK_UPORT_H
#define QSERIALWORK_UPORT_H

#include <dataprocessor.h>
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QMutex>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui {
class qSerialWorkMoxa;
}
QT_END_NAMESPACE

class qSerialWorkMoxa : public QObject
{
    Q_OBJECT

public:
    explicit qSerialWorkMoxa(QString portName, QObject *parent = nullptr);
    ~qSerialWorkMoxa();

signals:
    void Moxa_finished(); // Add this line
    void Moxa_sig_SerialErrorOccurred(QSerialPort::SerialPortError error);
    void Moxa_sig_SerialAboutToClose();
    void Moxa_newDataAvailable(QByteArray data);
    void Moxa_triggerProcessData();
    void msg_process(const QByteArray &message);
    void clear_buffer();

private slots:
    void Moxa_dataArrived();
    void Moxa_SerialAboutToClose();
    void Moxa_SerialErrorOccurred(QSerialPort::SerialPortError error);
    void msg_recevied(const QByteArray &message);

public slots:
    void start(); // Starts serial port operations
    void stop();  // Stops serial port operations
    void Moxa_serialPort_Close();
    bool Moxa_get_serialPort_openSTS();
    qint64 Moxa_writeData(const char *buf, qint64 len);

private:
    QSerialPort *serialPort;
    QString m_portName;
    QByteArray buffer; // Buffer for incoming data
    QMutex mutex;      // Mutex for thread-safe access to the buffer
    QThread processingThread;
    DataProcessor *dataProcessor;
};

#endif // qSerialWorkMoxa_H
