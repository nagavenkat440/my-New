#include "hellothread.h"
#include <QTime>
#include "logger.h"

HelloThread::HelloThread(QObject *parent) :
    QObject(parent)
{
    var1 = 0;
    var2 = 0;
}


void HelloThread::call_thread()
{
    //    qDebug() << "running from thread 0" << thread()->currentThreadId();
    emit testSignal_1();
}

void HelloThread::display1()
{
    while(running)
    {
        //        qDebug() << "running from thread 1" << thread()->currentThreadId();
        QThread::msleep(1000) ;
    }
}

HelloThread::~HelloThread()
{
    // Perform any additional cleanup if needed
}

void HelloThread::stopThread() {
    running = false;
}

