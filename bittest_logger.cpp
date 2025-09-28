#include "bittest_logger.h"

#include <QDebug>

BitTestLogger *BitTestLogger::instance()
{
    static BitTestLogger bittestloggerInstance;
    return &bittestloggerInstance;
}

BitTestLogger::BitTestLogger(QObject *parent)
    : QObject(parent)
{
    directory1 = "C:/FTU_ATE/Data/BIT_LOG";
    QDir().mkpath(directory1);
    createNewLogFile1();

    directory2 = "C:/FTU_ATE/Backup_Data/BIT_LOG";
    QDir().mkpath(directory2);
    createNewLogFile2();
}

void BitTestLogger::setLogDirectory(const QString &dirPath)
{
    directory1 = dirPath;
    QDir().mkpath(directory1);

    directory2 = dirPath;
    QDir().mkpath(directory2);
}

bool BitTestLogger::createNewLogFile1()
{
    QString fileName1 = directory1 + "/Log_"
                        + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".txt";

    file1.setFileName(fileName1);
    if (file1.open(QIODevice::WriteOnly | QIODevice::Text)) {
        stream1.setDevice(&file1);
        stream1 << "=== Log Started!!!: " << QDateTime::currentDateTime().toString() << " ===\n";
        stream1.flush();
        return true;
    } else {
        //        qDebug() << "Failed to open log file!";
        return false;
    }
}

bool BitTestLogger::createNewLogFile2()
{
    QString fileName2 = directory2 + "/Log_"
                        + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".txt";

    file2.setFileName(fileName2);
    if (file2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        stream2.setDevice(&file2);
        stream2 << "=== Log Started!!!: " << QDateTime::currentDateTime().toString() << " ===\n";
        stream2.flush();
        return true;
    } else {
        //        qDebug() << "Failed to open log file!";
        return false;
    }
}

void BitTestLogger::logText(const QString &text)
{
    stream1 << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " - " << text << "\n";
    stream1.flush();

    stream2 << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " - " << text << "\n";
    stream2.flush();
}
