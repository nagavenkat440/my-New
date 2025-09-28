#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDateTime>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger* instance();  // Singleton instance

    void setLogDirectory(const QString &dirPath);
    bool createNewLogFile();
    void logText(const QString &text);

private:
    explicit Logger(QObject *parent = nullptr);  // Private constructor

    QString directory;
    QFile file;
    QTextStream stream;
};

#endif // LOGGER_H
