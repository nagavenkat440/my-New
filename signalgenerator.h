#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#include "crcutility.h"
#include "qcustomplot.h"
#include "testpointdataframming.h"
#include <algorithm> // qBound
#include <cstdint>
#include <random>
#include <QGroupBox>
#include <QVector>
#include <QWidget>
#include <QtGlobal> // qBound
/*
 * Output Range of DAC is Measured through Oscilloscope
 * Positive side voltage = 2.38V
 * Negative side voltage = -2.40V
 * So, output range = 2.38-(-2.40) = 4.78V
 * So, 1 LSB = 4.78V/4095 = 1.167mV(0.00116727716727716727716727716728)
 * So, here my gain is 4.5V so 4.78/4.5 = 1.0622
 * So, Now scale factor is equal to 1.0622/4096 =259uV(0.00025939492606159272825939492606159)
 */



//#define DAC_SF (0.00026331f * DAC_GAINFACTOR)
#define DAC_SF (0.00051891f * DAC_GAINFACTOR)
#define DAC_GAINFACTOR 1
#define OFFSET_CORRECTION -150//1048//2096//(34.5 / 1000.0f) // 34.5 mV in volts //as DAC is having an offset in +ve need to subtract this and in -Ve we need to add this

#define WF_PKT_SIZE 128
#define SET 1
#define RESET 0
#define WAVEFORM_ARRAY1 0x01
#define WAVEFORM_ARRAY2 0x02
#define WAVEFORM_ARRAY3 0x04
#define WAVEFORM_ARRAY4 0x08

typedef enum SignalInjectionPoint {
    INBOARD_ELEVON_SYMMETRIC = 0,
    OUTBOARD_ELEVON_SYMMETRIC,
    INBOARD_ELEVON_ASYMMETRIC,
    OUTBOARD_ELEVON_ASYMMETRIC,
    INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC,
    INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC,
    RUDDER,
    CANARD_SYMMETRIC,
    CANARD_ASYMMETRIC,
    PITCH_STICK_FTU_INPUT,
    ROLL_STICK_FTU_INPUT,
    RUDDER_PEDAL_FTU_INPUT,
    SLAT_INPUT,
    AIRBRAKE_INPUT,
    STABILATORS_SYMMETRIC,
    STABILATORS_ASYMMETRIC,
    AILERONS_SYMMETRIC,
    AILERONS_ASYMMETRIC,
    RUDDER_SYMMETRIC,
    RUDDER_ASYMMETRIC,
    TEF_SYMMETRIC,
    TEF_ASYMMETRIC,
    LEF_ACTUATOR_INPUT
} Signal_Injection_Point;

namespace Ui {
class SignalGenerator;
}

class SignalGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit SignalGenerator(QWidget *parent = nullptr);
    TestPoint_main g_WaveFormFile_pkt;

    ~SignalGenerator();
    // Member functions
    QVector<quint16> generateSineWave(double f_out,
                                      double duration_s,
                                      const QVector<double> &sineTable,
                                      double Fs = 12800.0,
                                      double gain = 1.0,
                                      double dc_offset = 0.0,
                                      int n_bits = 12,
                                      bool dither = false);

private slots:

    void plotWaveforms(const QString text);

    void plotSquarePulse(QCustomPlot &plot,
                         QLabel &Graphlabel,
                         const QString GraphName,
                         double frequency,
                         double amplitude,
                         double riseTime,
                         double fallTime,
                         int numSamples);

    void plotSquareDoublet(QCustomPlot &plot, QLabel &Graphlabel, const QString GraphName, double frequency, double amplitude, double riseTime, double fallTime, int numSamples, uint8_t pktNo);

    //    void plotHalfSinePulse(QCustomPlot &plot, QLabel &Graphlabel, const QString GraphName, double frequency, double amplitude,int numSamples, uint8_t pktNo);

    //void plotFullSineDoublet(QCustomPlot &plot, QLabel &Graphlabel, const QString GraphName, double frequency, double amplitude,int numSamples, uint8_t pktNo);

    void plotHalfSinePulse(QCustomPlot &plot,
                           QLabel &Graphlabel,
                           const QString GraphName,
                           double freqStart,
                           double freqStep,
                           double freqStop,
                           const QVector<double> &durations,
                           double Fs,
                           const QVector<double> &HalfsineTable,
                           double MID,
                           double gain,
                           double dcOffset,
                           int n_bits);
    void plotFullSineDoublet(QCustomPlot &plot,
                             QLabel &Graphlabel,
                             const QString GraphName,
                             double freqStart,
                             double freqStep,
                             double freqStop,
                             const QVector<double> &durations,
                             double Fs,
                             const QVector<double> &sineTable,
                             double MID,
                             double gain,
                             double dcOffset,
                             int n_bits);
    void plot3211PulseTrain(QCustomPlot &plot,
                            QLabel &Graphlabel,
                            const QString GraphName,
                            double frequency,
                            double amplitude,
                            int numSamples);

    void generateRandomNoise(QCustomPlot &plot,
                             QLabel &Graphlabel,
                             const QString GraphName,
                             double amplitude,
                             int numPoints);

    void IO_ELEVON_Single(uint8_t signal);

    void IO_ELEVON_Combined(uint8_t signal);

    void Rudder_single(uint8_t signal);

    void Canard_Single(uint8_t signal);

    void on_pbtn_FTU_TestNo_clicked();

    void on_waveform_read_pbtn_clicked();

    void on_PlotWaveforms_PB_clicked();

    void on_SignalInjectionPoint_lineedit_textChanged(const QString &arg1);

private:
    Ui::SignalGenerator *ui;

    uint16_t g_checkCRC_word;
    uint16_t g_CRC_word;
    QString selectedFolderPath;

    // Helper functions
    static QVector<double> getSineTableDouble();

    // Generate DAC codes from sine table
    static QVector<quint16> generateSineWaveCodes(double f_out,
                                                  double duration_s,
                                                  const QVector<uint16_t> &sineTable,
                                                  double Fs = 12800.0,
                                                  double gain = 1.0,
                                                  double dc_offset = 0.0,
                                                  int n_bits = 12);

    // Clamp values 0..4095
    //    static void sanitizeSineTable(QVector<uint16_t> &table);
};

typedef enum { ANALOG, DIGITAL } TransmissionMode;

typedef enum
{
    SQUARE_PULSE,
    SQUARE_DOUBLET,
    HALF_SINE_PULSE,
    FULL_SINE_DOUBLET,
    PULSE_TRAIN_3_2_1_1,
    LINEAR_SINE_SWEEP,
    LOGARITHMIC_SINE_SWEEP,
    RANDOM_SIGNAL
} SignalType;

//typedef enum {
//    Inboard_Elevon_Symmetric,
//    OUTBOARD_Elevon_Symmetric,
//    INBOARD_Elevon_ASymmetric,
//    OUTBOARD_Elevon_ASymmetric,
//    INBOARD_AND_OUTBOARD_Elevon_Symmetric,
//    INBOARD_AND_OUTBOARD_Elevon_ASymmetric,
//    Rudder,
//    Canard_Symmetric,
//    Canard_Asymmetric,
//    Pitch_Stick_FTU_Input,
//    Roll_Stick_FTU_Input,
//    Rudder_Pedal_FTU_Input,
//    Slat_Input,
//    AirBrake_Input
//} Signal_Injection_Point;

typedef enum
{
    LCA_AF_MK2,
    AMCA
} ProjectName;

SignalInjectionPoint stringToCommand(const QString &command);
SignalType stringToSignalType(const QString &Signal_type);
extern QVector<double> sineTable;
extern QVector<double> HalfsineTable;

#endif // SIGNALGENERATOR_H
