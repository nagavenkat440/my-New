#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QMutex>

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr);


public slots:
    void appendData(const QByteArray &data);
    void processData();
    void clear_buffer();

signals:
    void dataProcessed(const QByteArray &message); // Signal to emit after processing each message

private:
    QByteArray buffer;
    void parseBuffer();
    QMutex mutex;
    QByteArray message;
};

#endif // DATAPROCESSOR_H
