#ifndef HELLOTHREAD_H
#define HELLOTHREAD_H

#include <QObject>
#include <QThread>
#include <QtDebug>
#include <QtCore>


class HelloThread : public QObject
{
    Q_OBJECT

public:
explicit HelloThread(QObject *parent = 0);
    ~HelloThread();

    void call_thread();
    void stopThread();
private:
    uint8_t var1;
    uint8_t var2;
    std::atomic<bool> running{true};
signals:
    void testSignal_1();
    void testSignal_2();

public slots:
    void display1();
//    void display2();

private:
};

#endif // HELLOTHREAD_H
