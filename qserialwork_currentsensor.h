#ifndef QSERIALWORK_CURRENTSENSOR_H
#define QSERIALWORK_CURRENTSENSOR_H

#include "dataprocessor.h"
#include <QObject>
#include <QSerialPort>
#include <QThread>

class SerialWork_CurrentSensor : public QObject
{
    Q_OBJECT

public:
    explicit SerialWork_CurrentSensor(const QString &portName,
                                      bool isWriter,
                                      QObject *parent = nullptr); // ✅ Constructor with writer
    ~SerialWork_CurrentSensor();

    void start();
    qint64 writeData(const QByteArray &data);

signals:
    //    void portOpenedCurrent(bool ok);
    void newDataAvailable(const QByteArray &data); // ✅ For processor
    void triggerProcessData();                     // ✅ For processor
    void msg_process(const QByteArray &msg);       // ✅ To MainWindow

private slots:
    void readFromPort();
    void msg_received(const QByteArray &message); // ✅ Slot called when message parsed

private:
    QString port;
    QSerialPort *serial;
    bool writer; // ✅ Store writer mode
    DataProcessor *dataProcessor;
    QThread processingThread; // ✅ Thread for processing
};

#endif // QSERIALWORK_CURRENTSENSOR_H
