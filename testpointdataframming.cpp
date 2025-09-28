#include "testpointdataframming.h"
#include <QMessageBox>
#include "crcutility.h"

TestPointDataFramming::TestPointDataFramming(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<uint16_t>("uint16_t");
    qRegisterMetaType<QVector<TestPoint_main>>("QVector<TestPoint_main>");
}

QVector<TestPoint_main> TestPointDataFramming::loadTestPoints(const QString& directory) {

    QDir dir(directory);
    uint16_t counter = 0;
    // Debug the directory and file list
    if (!dir.exists()) {
        //        qDebug() << "Directory does not exist:" << directory;
        QMessageBox::information(nullptr, tr("Information"), tr("Directory does not exist: %1").arg(directory));
        return {};
    }
    // Retrieve all .bin files
    QStringList files = dir.entryList(QStringList() << "*.bin", QDir::Files, QDir::Name);
    if (files.isEmpty()) {
        //        qDebug() << "No files found in the directory:" << directory;
        QMessageBox::information(nullptr, tr("Information"), tr("No .bin files found in the directory: %1").arg(directory));
        return {};
    }
    //    qDebug() << "Files found:" << files;
    QVector<TestPoint_main> testPoints;
    // Iterate over all files
    for (int i = 0; i < files.size(); ++i) {
        const QString &filename = files[i];
        //    for (const QString &filename : files) {
        QString filePath = dir.filePath(filename);
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            //            qDebug() << "Failed to open file:" << filePath;
            QMessageBox::information(nullptr, tr("Information"), tr("Failed to open file: %1").arg(filePath));
            continue;
        }
        TestPoint_main testPoint = {};
        if (file.read(reinterpret_cast<char *>(&testPoint), sizeof(TestPoint_main)) != sizeof(TestPoint_main)) {
            //            qDebug() << "Invalid file size for:" << filePath;
            QMessageBox::information(nullptr, tr("Information"), tr("Invalid file size for: %1").arg(filePath));
            file.close();
        }
        uint16_t ref_calculatedCRC = testPoint.CRC_WORD;
        testPoint.CRC_WORD = 0;
        uint16_t calculatedCRC = CRCUtility::g_CRC_calc(reinterpret_cast<const uint8_t *>(&testPoint), sizeof(TestPoint_main));
        if (calculatedCRC != ref_calculatedCRC) {
            //            qDebug() << "CRC validation failed for file:" << filename;
            QMessageBox::information(nullptr, tr("Information"), tr("CRC validation failed for file: %1").arg(filename));
            file.close();
        }
        // Extracting TestPoint number from the filename
        bool ok;
        int fileNumber = filename.leftRef(3).toInt(&ok);
        if (!ok) {
            //            qDebug() << "Filename format error for" << filename;
            QMessageBox::information(nullptr, tr("Information"), tr("Filename format error for: %1").arg(filename));
        }
        emit update_waveform_table(++counter, fileNumber, filename, true);
        QThread::msleep(10); // Simulate processing delay

        testPoints.append(testPoint);
        //        qDebug() << "File processed successfully:" << filename;

        file.close();
    }
    //    qDebug() << "Total files processed successfully:" << testPoints.size();
    return testPoints;
}

void TestPointDataFramming::SlotdirectorySelected(const QString &directory)
{
    if (!directory.isEmpty()) {
        testPoints = loadTestPoints(directory);
        //        qDebug() << "Loaded" << testPoints.size() << "TestPoints.";

        emit testPointsUpdated(testPoints);
    }
    else
    {
        //        qDebug() << "Directory is empty.";
    }
}


void TestPointDataFramming::stop()
{
    //    qDebug() << "TestPointDataFramming stop triggered;";
    emit finished(); // Notify that the worker is finished
}



