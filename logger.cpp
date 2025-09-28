#include "logger.h"
#include <QDebug>

Logger* Logger::instance()
{
    static Logger loggerInstance;
    return &loggerInstance;
}

Logger::Logger(QObject *parent) : QObject(parent)
{
    directory = "C:/FTU_ATE/Data/ATE_LOG";
    QDir().mkpath(directory);
    createNewLogFile();
}

void Logger::setLogDirectory(const QString &dirPath)
{
    directory = dirPath;
    QDir().mkpath(directory);
}

bool Logger::createNewLogFile()
{
    QString fileName = directory + "/Log_" +
        QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".txt";

    file.setFileName(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        stream.setDevice(&file);
        stream << "=== Log Started: " << QDateTime::currentDateTime().toString() << " ===\n";
        stream.flush();
        return true;
    } else {
        //        qDebug() << "Failed to open log file!";
        return false;
    }
}

void Logger::logText(const QString &text)
{
    stream << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << " - " << text << "\n";
    stream.flush();
}
