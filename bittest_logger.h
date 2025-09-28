#ifndef BITTEST_LOGGER_H
#define BITTEST_LOGGER_H

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QTextStream>

class BitTestLogger : public QObject
{
    Q_OBJECT

public:
    static BitTestLogger *instance(); // Singleton instance

    void setLogDirectory(const QString &dirPath);
    bool createNewLogFile1();
    bool createNewLogFile2();
    void logText(const QString &text);

private:
    explicit BitTestLogger(QObject *parent = nullptr); // Private constructor

    QString directory1;
    QString directory2;

    QFile file1;
    QFile file2;
    QTextStream stream1;
    QTextStream stream2;
};

#endif // BITTEST_LOGGER_H
