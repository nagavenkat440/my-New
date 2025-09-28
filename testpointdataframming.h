#ifndef TESTPOINTDATAFRAMMING_H
#define TESTPOINTDATAFRAMMING_H

#include <QObject>
#include <QThread>
#include <QtDebug>
#include <QtCore>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMap>

#include <QFileDialog>

#ifndef WF_PKT_SIZE
#define WF_PKT_SIZE 128
#endif

static_assert(true, "Dummy static assert"); // dummy declaration, ends the preamble
#pragma pack(push, 1)
    typedef struct
    {
        uint8_t startByte;
        uint8_t MsgID;
        uint16_t packetSize;
        uint16_t FTU_TestNo;
        uint8_t TransmissionMode;
        uint8_t SignalType;
        uint8_t ProjectName;
        uint8_t SignalInjectionPoint;
        float Amplitude1;
        float Amplitude2;
        float SafeEngageTime;
        uint8_t InvertFlag;
        float C0;
        float C1;
        float StartFrequency;
        float EndFrequency;
        float FrequencyStep;
        float DwellDuration;
        uint8_t TypeOfInput;
        float SlatInput;
        float PulseWidth;
        uint16_t NoOfRepeats;
        float TimeBetweenRepeats;
        float RiseTime;
        float FallTime;
        uint8_t CH1:1;
        uint8_t CH2:1;
        uint8_t CH3:1;
        uint8_t CH4:1;
        uint8_t CH5:1;
        uint8_t CH6:1;
        uint8_t CH7:1;
        uint8_t CH8:1;
        uint8_t waveformSelect1:1;
        uint8_t waveformSelect2:1;
        uint8_t waveformSelect3:1;
        uint8_t waveformSelect4:1;
        uint16_t NumberOfSamples;
        uint16_t waveformSamples1[WF_PKT_SIZE];
        uint16_t waveformSamples2[WF_PKT_SIZE];
        uint16_t waveformSamples3[WF_PKT_SIZE];
        uint16_t waveformSamples4[WF_PKT_SIZE];
        uint16_t CRC_WORD;
        uint16_t endByte;
        //        double Fs = 128.0 * 100.0;
        //        double freqStart;
        //        double freqStep;
        //        double freqStop;
        //        const QVector<double> &durations;
        //        const QVector<double> &sineTable;
        //        double MID;
        //        double gain;
        //        double dcOffset;
        //        int n_bits;
    }TestPoint_main;
#pragma pack(pop)

class TestPointDataFramming : public QObject
{
    Q_OBJECT
public:
    explicit TestPointDataFramming(QObject *parent = nullptr);

signals:
    void update_waveform_table(uint16_t counter,int testPointNum, QString TestPointfileName,bool ok);
    void requestDirectorySelection();
    void testPointsUpdated(const QVector<TestPoint_main>& testPoints);
    void finished();

public slots:
    QVector<TestPoint_main> loadTestPoints(const QString& directory);
    void SlotdirectorySelected(const QString &directory);
    void stop();

private:
    QVector<TestPoint_main> testPoints;
};

#endif // TESTPOINTDATAFRAMMING_H
