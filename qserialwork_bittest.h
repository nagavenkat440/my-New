#ifndef QSERIALWORK_BITTEST_H
#define QSERIALWORK_BITTEST_H

#include "dataprocessor.h"
#include <QObject>
#include <QSerialPort>
#include <QThread>

class SerialWork_Bittest : public QObject
{
    Q_OBJECT

public:
    explicit SerialWork_Bittest(const QString &portName,
                                bool isWriter,
                                QObject *parent = nullptr); // ✅ Constructor with writer
    ~SerialWork_Bittest();

    void start();
    // qint64 writeData(const QByteArray &data);

public slots:
    qint64 writeData(const char *buf, qint64 len);
    bool isConnected() const;
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

#endif // QSERIALWORK_BITTEST_H
