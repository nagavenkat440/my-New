#include "signalgenerator.h"
#include "mainwindow.h"
#include "testpointdataframming.h"
#include "ui_signalgenerator.h"
#include <cmath>
#include <QFileDialog>
#include <QIntValidator>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

//static constexpr double kFs = 128.0 * 100.0; // 12800.0
//static constexpr double kMid = 4095.0 / 2.0; // 2047.5

QString DisplayGraphName;
QString DisplayGraphName2;
TestPoint_Table_Data dataArray;
struct SweepResult
{
    QVector<quint16> codes; // DAC codes
    QVector<double> freqs;  // frequencies used (Hz)
    QVector<int> segStarts; // start sample index for each frequency segment
};

// Quantize to N-bit DAC range [0 .. 2^n_bits - 1]
inline QVector<quint16> quantizeForDac(const QVector<double> &x, int n_bits = 12)
{
    const int max_code = (1 << n_bits) - 1;
    QVector<quint16> out;
    out.reserve(x.size());
    for (double v : x) {
        // round to nearest
        double r = std::rint(v);
        if (r < 0.0)
            r = 0.0;
        if (r > max_code)
            r = max_code;
        out.push_back(static_cast<quint16>(r));
    }
    return out;
}

// Build an arithmetic sequence handling +/- step; inclusive of stop if on grid
inline QVector<double> arangeInclusive(double start, double stop, double step)
{
    QVector<double> v;
    if (step == 0.0) {
        v.push_back(start);
        return v;
    }
    const double eps = std::abs(step) * 1e-9;
    if (step > 0.0) {
        for (double f = start; f <= stop + eps; f += step)
            v.push_back(f);
        // trim any tiny floating overflow beyond stop
        while (!v.isEmpty() && v.back() > stop + eps)
            v.pop_back();
    } else {
        for (double f = start; f >= stop - eps; f += step)
            v.push_back(f);
        while (!v.isEmpty() && v.back() < stop - eps)
            v.pop_back();
    }
    return v;
}

inline SweepResult generateSineSweepCodes(double freqStart,
                                          double freqStep,
                                          double freqStop,
                                          const QVector<double> &durations,
                                          double Fs,
                                          const QVector<double> &sineTable,
                                          double MID,
                                          double gain,
                                          double dcOffset,
                                          int n_bits)
{
    SweepResult R;

    // Frequencies list
    QVector<double> freqs = (freqStep == 0.0) ? QVector<double>{freqStart}
                                              : arangeInclusive(freqStart, freqStop, freqStep);

    if (freqStep == 0.0) {
        // Preserve Python behavior when start==stop and step==0
        // (single frequency)
        R.freqs = freqs;
    } else {
        R.freqs = freqs;
    }

    if (freqs.isEmpty()) {
        // nothing to generate
        return R;
    }

    // Normalize durations
    QVector<double> durList;
    if (durations.size() == 1) {
        durList.fill(durations[0], freqs.size());
    } else if (durations.size() == freqs.size()) {
        durList = durations;
    } else {
        // fall back: treat as scalar 0 if mismatched to avoid crash; user can handle
        qWarning() << "durations length must match number of frequencies (or be scalar).";
        durList.fill(0.0, freqs.size());
    }

    const int TABLE_N = sineTable.size();
    if (TABLE_N <= 1 || Fs <= 0.0) {
        qWarning() << "Invalid table length or sample rate.";
        return R;
    }

    QVector<double> y;
    y.reserve(1024);
    R.segStarts.reserve(freqs.size());

    // continuous phase via fractional index into table
    double idx = 0.0;

    auto currentLen = [&]() -> int { return y.size(); };

    for (int fi = 0; fi < freqs.size(); ++fi) {
        const double f = freqs[fi];
        const double dur = durList[fi];
        const int nSamples = static_cast<int>(std::llround(dur * Fs));

        R.segStarts.push_back(currentLen());

        if (nSamples <= 0)
            continue;

        const double step = (static_cast<double>(TABLE_N) * f) / Fs;

        for (int i = 0; i < nSamples; ++i) {
            int k = static_cast<int>(idx);
            double frac = idx - static_cast<double>(k);
            int k1 = (k + 1 < TABLE_N) ? (k + 1) : 0;

            // linear interpolation
            double val = (1.0 - frac) * sineTable[k] + frac * sineTable[k1];

            // scale around MID (same as Python: dc_offset + MID + gain * (val - MID))
            double sample = dcOffset + MID + (gain) * (val - MID);
            y.push_back(sample);

            idx += step;
            // wrap idx into [0, TABLE_N)
            if (idx >= TABLE_N) {
                idx -= TABLE_N;
            } else if (idx < 0.0) {
                idx += TABLE_N;
            }
        }
    }

    // Quantize to DAC codes
    R.codes = quantizeForDac(y, n_bits);
    return R;
}

SignalGenerator::SignalGenerator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignalGenerator)
{
    ui->setupUi(this);
    QStringList waveForms;
    QStringList TransmissionModes;
    QStringList ListProjectName;
    QStringList ListInvertFlag;

    ListProjectName << " "
                    << "LCA AF MK2";

    ui->ProjectName->addItems(ListProjectName);

    //----------------
    // for FTU Test number
    QIntValidator *validator = new QIntValidator(0, 999, this);
    ui->lineEdit_FTU_TestNo->setValidator(validator);

    // Optional: Format the input to always display 3 digits (leading zeros)
    connect(ui->lineEdit_FTU_TestNo, &QLineEdit::editingFinished, this, [this]() {
        QString text = ui->lineEdit_FTU_TestNo->text();
        ui->lineEdit_FTU_TestNo->setText(
            text.rightJustified(3, '0')); // Add leading zeros if necessary
    });

    ui->Graph2->setVisible(false);
    ui->Graph3->setVisible(false);
    ui->Graph4->setVisible(false);

    ui->LabelGraph1->setVisible(false);
    ui->LabelGraph2->setVisible(false);
    ui->LabelGraph3->setVisible(false);
    ui->LabelGraph4->setVisible(false);

    //    plotFullSineDoublet(*ui->Graph1,
    //                        *ui->LabelGraph1,
    //                        "Half Sine Doublet",
    //                        5,
    //                        0.5,
    //                        20,
    //                        QVector<double>() << 1,
    //                        12800.0,
    //                        sineTable,
    //                        2048,
    //                        1.0,
    //                        0.0,
    //                        12);
    plotFullSineDoublet(*ui->Graph1,
                        *ui->LabelGraph1,
                        "Half Sine Doublet",
                        5,
                        0.5,
                        20,
                        QVector<double>() << 1,
                        10000.0,
                        HalfsineTable,
                        2048,
                        1.0,
                        0.0,
                        12);
}

SignalGenerator::~SignalGenerator()
{
    delete ui;
}

void SignalGenerator::on_SignalInjectionPoint_lineedit_textChanged(const QString &arg1)
{
    switch (stringToCommand(arg1)) {
    case INBOARD_ELEVON_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = SET;   //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = RESET; //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = SET;   //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = RESET; //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = RESET; //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case OUTBOARD_ELEVON_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = SET;   //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = RESET; //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = SET;   //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = RESET; //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case INBOARD_ELEVON_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = SET;   //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = RESET; //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = SET;   //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = RESET; //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = RESET; //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    case OUTBOARD_ELEVON_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = SET;   //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = RESET; //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = SET;   //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = RESET; //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    case INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = SET;   //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = SET;   //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = SET;   //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = SET;   //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = RESET; //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = SET;   //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = SET;   //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = SET;   //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = SET;   //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = RESET; //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    case RUDDER: {
        g_WaveFormFile_pkt.CH1 = RESET; //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = RESET; //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = RESET; //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = RESET; //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = SET;   //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = RESET; //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = RESET;
        g_WaveFormFile_pkt.waveformSelect2 = RESET;
        g_WaveFormFile_pkt.waveformSelect3 = SET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case CANARD_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = RESET; //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = RESET; //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = RESET; //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = SET;   //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = SET;   //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = RESET;
        g_WaveFormFile_pkt.waveformSelect2 = RESET;
        g_WaveFormFile_pkt.waveformSelect3 = SET;
        g_WaveFormFile_pkt.waveformSelect4 = SET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case CANARD_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //LIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH2 = RESET; //LOE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH3 = RESET; //RIE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH4 = RESET; //ROE      ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH5 = RESET; //Rudder   ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH6 = SET;   //L-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH7 = SET;   //R-Canard ''''LCA-mk2'''
        g_WaveFormFile_pkt.CH8 = RESET; //Spare    ''''LCA-mk2'''
        g_WaveFormFile_pkt.waveformSelect1 = RESET;
        g_WaveFormFile_pkt.waveformSelect2 = RESET;
        g_WaveFormFile_pkt.waveformSelect3 = SET;
        g_WaveFormFile_pkt.waveformSelect4 = SET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    case STABILATORS_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = SET;   //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = RESET; //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = SET;   //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = RESET; //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = RESET; //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = RESET; //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = RESET; //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case STABILATORS_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = SET;   //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = RESET; //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = SET;   //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = RESET; //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = RESET; //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = RESET; //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = RESET; //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    case AILERONS_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = SET;   //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = RESET; //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = SET;   //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = RESET; //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = RESET; //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = RESET; //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case AILERONS_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = SET;   //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = RESET; //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = SET;   //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = RESET; //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = RESET; //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = RESET; //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = SET;
        g_WaveFormFile_pkt.waveformSelect2 = SET;
        g_WaveFormFile_pkt.waveformSelect3 = RESET;
        g_WaveFormFile_pkt.waveformSelect4 = RESET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    case RUDDER_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = RESET; //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = RESET; //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = RESET; //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = SET;   //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = RESET; //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = SET;   //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = RESET; //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = RESET;
        g_WaveFormFile_pkt.waveformSelect2 = RESET;
        g_WaveFormFile_pkt.waveformSelect3 = SET;
        g_WaveFormFile_pkt.waveformSelect4 = SET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case RUDDER_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = RESET; //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = RESET; //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = RESET; //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = SET;   //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = RESET; //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = SET;   //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = RESET; //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = RESET;
        g_WaveFormFile_pkt.waveformSelect2 = RESET;
        g_WaveFormFile_pkt.waveformSelect3 = SET;
        g_WaveFormFile_pkt.waveformSelect4 = SET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    case TEF_SYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = RESET; //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = RESET; //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = RESET; //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = RESET; //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = SET;   //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = SET;   //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = RESET;
        g_WaveFormFile_pkt.waveformSelect2 = RESET;
        g_WaveFormFile_pkt.waveformSelect3 = SET;
        g_WaveFormFile_pkt.waveformSelect4 = SET;
        g_WaveFormFile_pkt.InvertFlag = RESET;
        break;
    }
    case TEF_ASYMMETRIC: {
        g_WaveFormFile_pkt.CH1 = RESET; //L-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH2 = RESET; //L-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH3 = RESET; //R-Stabilator     ''''AMCA''''
        g_WaveFormFile_pkt.CH4 = RESET; //R-Ailerons       ''''AMCA''''
        g_WaveFormFile_pkt.CH5 = RESET; //L-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH6 = SET;   //L-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.CH7 = RESET; //R-Rudder         ''''AMCA''''
        g_WaveFormFile_pkt.CH8 = SET;   //R-TEF            ''''AMCA''''
        g_WaveFormFile_pkt.waveformSelect1 = RESET;
        g_WaveFormFile_pkt.waveformSelect2 = RESET;
        g_WaveFormFile_pkt.waveformSelect3 = SET;
        g_WaveFormFile_pkt.waveformSelect4 = SET;
        g_WaveFormFile_pkt.InvertFlag = SET;
        break;
    }
    default: {
        break;
    }
    }
}

void SignalGenerator::IO_ELEVON_Single(uint8_t signal)
{
    if ((ui->SignalInjectionPoint_lineedit->text() == "INBOARD_ELEVON_SYMMETRIC")
        || (ui->SignalInjectionPoint_lineedit->text() == "INBOARD_ELEVON_ASYMMETRIC")
        || (ui->SignalInjectionPoint_lineedit->text() == "OUTBOARD_ELEVON_SYMMETRIC")
        || (ui->SignalInjectionPoint_lineedit->text() == "OUTBOARD_ELEVON_ASYMMETRIC")) {
        ui->Graph2->setVisible(true);
        ui->Graph3->setVisible(false);
        ui->Graph4->setVisible(false);

        ui->LabelGraph1->setVisible(true);
        ui->LabelGraph2->setVisible(true);
        ui->LabelGraph3->setVisible(false);
        ui->LabelGraph4->setVisible(false);
        if ((g_WaveFormFile_pkt.CH1 == SET) || (g_WaveFormFile_pkt.CH2 == SET)) {
            if ((ui->SignalInjectionPoint_lineedit->text() == "INBOARD_ELEVON_ASYMMETRIC")
                || (ui->SignalInjectionPoint_lineedit->text() == "OUTBOARD_ELEVON_ASYMMETRIC")) {
                g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
                if (g_WaveFormFile_pkt.CH1 == SET) {
                    DisplayGraphName = "LEFT INBOARD_ELEVON_ASYMMETRIC";
                } else if (g_WaveFormFile_pkt.CH2 == SET) {
                    DisplayGraphName = "LEFT OUTBOARD_ELEVON_ASYMMETRIC";
                }
            } else {
                if (g_WaveFormFile_pkt.CH1 == SET) {
                    DisplayGraphName = "LEFT INBOARD_ELEVON_SYMMETRIC";
                } else if (g_WaveFormFile_pkt.CH2 == SET) {
                    DisplayGraphName = "LEFT OUTBOARD_ELEVON_SYMMETRIC";
                }
            }
            switch (signal) {
            case SQUARE_PULSE: {
                plotSquarePulse(*ui->Graph1,
                                *ui->LabelGraph1,
                                DisplayGraphName,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude1,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case SQUARE_DOUBLET: {
                plotSquareDoublet(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude1,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  1);
                break;
            }
            case HALF_SINE_PULSE: {
                plotHalfSinePulse(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                break;
            }
            case FULL_SINE_DOUBLET: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));

                break;
            }
            case PULSE_TRAIN_3_2_1_1: {
                plot3211PulseTrain(*ui->Graph1,
                                   *ui->LabelGraph1,
                                   DisplayGraphName,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude1,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case LINEAR_SINE_SWEEP: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                break;
            }
            case LOGARITHMIC_SINE_SWEEP: {
                //                plotFullSineDoublet(*ui->Graph1,*ui->LabelGraph1,DisplayGraphName,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude1,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,1);
                break;
            }
            case RANDOM_SIGNAL: {
                generateRandomNoise(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    g_WaveFormFile_pkt.Amplitude1,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            default: {
                break;
            }
            }
        }
        if ((g_WaveFormFile_pkt.CH3 == SET) || (g_WaveFormFile_pkt.CH4 == SET)) {
            if ((ui->SignalInjectionPoint_lineedit->text() == "INBOARD_ELEVON_ASYMMETRIC")
                || (ui->SignalInjectionPoint_lineedit->text() == "OUTBOARD_ELEVON_ASYMMETRIC")) {
                g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
                if (g_WaveFormFile_pkt.CH3 == SET) {
                    DisplayGraphName = "RIGHT INBOARD_ELEVON_ASYMMETRIC";
                } else if (g_WaveFormFile_pkt.CH4 == SET) {
                    DisplayGraphName = "RIGHT OUTBOARD_ELEVON_ASYMMETRIC";
                }
            } else {
                if (g_WaveFormFile_pkt.CH3 == SET) {
                    DisplayGraphName = "RIGHT INBOARD_ELEVON_SYMMETRIC";
                } else if (g_WaveFormFile_pkt.CH4 == SET) {
                    DisplayGraphName = "RIGHT OUTBOARD_ELEVON_SYMMETRIC";
                }
            }
            switch (signal) {
            case SQUARE_PULSE: {
                plotSquarePulse(*ui->Graph2,
                                *ui->LabelGraph2,
                                DisplayGraphName,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude2,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case SQUARE_DOUBLET: {
                plotSquareDoublet(*ui->Graph2,
                                  *ui->LabelGraph2,
                                  DisplayGraphName,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude2,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  2);
                break;
            }
            case HALF_SINE_PULSE: {
                plotHalfSinePulse(*ui->Graph2,
                                  *ui->LabelGraph2,
                                  DisplayGraphName,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  //                                    g_WaveFormFile_pkt.duration,
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                break;
            }
            case FULL_SINE_DOUBLET: {
                plotFullSineDoublet(*ui->Graph2,
                                    *ui->LabelGraph2,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    //                                    g_WaveFormFile_pkt.duration,
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (-1),
                                    (0),
                                    (12));

                break;
            }
            case PULSE_TRAIN_3_2_1_1: {
                plot3211PulseTrain(*ui->Graph2,
                                   *ui->LabelGraph2,
                                   DisplayGraphName,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude2,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case LINEAR_SINE_SWEEP: {
                plotFullSineDoublet(*ui->Graph2,
                                    *ui->LabelGraph2,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    //                                    g_WaveFormFile_pkt.duration,
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    -1,
                                    (0),
                                    (12));
                break;
            }
            case LOGARITHMIC_SINE_SWEEP: {
                break;
            }
            case RANDOM_SIGNAL: {
                generateRandomNoise(*ui->Graph2,
                                    *ui->LabelGraph2,
                                    DisplayGraphName,
                                    g_WaveFormFile_pkt.Amplitude2,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            default: {
                break;
            }
            }
        }

        g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_WaveFormFile_pkt, sizeof(TestPoint_main));
        g_WaveFormFile_pkt.CRC_WORD = g_CRC_word;
    }
}
void SignalGenerator::IO_ELEVON_Combined(uint8_t signal)
{
    if ((ui->SignalInjectionPoint_lineedit->text() == "INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC")
        || (ui->SignalInjectionPoint_lineedit->text() == "INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC")) {
        ui->Graph2->setVisible(true);
        ui->Graph3->setVisible(true);
        ui->Graph4->setVisible(true);

        ui->LabelGraph1->setVisible(true);
        ui->LabelGraph2->setVisible(true);
        ui->LabelGraph3->setVisible(true);
        ui->LabelGraph4->setVisible(true);
        if ((g_WaveFormFile_pkt.CH1 == SET) && (g_WaveFormFile_pkt.CH2 == SET)) {
            if ((ui->SignalInjectionPoint_lineedit->text()
                 == "INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC")) {
                g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
                if (g_WaveFormFile_pkt.CH1 == SET) {
                    DisplayGraphName = "LEFT INBOARD_ELEVON_ASYMMETRIC";
                }
                if (g_WaveFormFile_pkt.CH2 == SET) {
                    DisplayGraphName2 = "LEFT OUTBOARD_ELEVON_ASYMMETRIC";
                }
            } else {
                if (g_WaveFormFile_pkt.CH1 == SET) {
                    DisplayGraphName = "LEFT INBOARD_ELEVON_SYMMETRIC";
                }
                if (g_WaveFormFile_pkt.CH2 == SET) {
                    DisplayGraphName2 = "LEFT OUTBOARD_ELEVON_SYMMETRIC";
                }
            }
            switch (signal) {
            case SQUARE_PULSE: {
                plotSquarePulse(*ui->Graph1,
                                *ui->LabelGraph1,
                                DisplayGraphName,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude1,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                plotSquarePulse(*ui->Graph2,
                                *ui->LabelGraph2,
                                DisplayGraphName2,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude1,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case SQUARE_DOUBLET: {
                plotSquareDoublet(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude1,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  1);
                plotSquareDoublet(*ui->Graph2,
                                  *ui->LabelGraph2,
                                  DisplayGraphName2,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude1,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  1);
                break;
            }
            case HALF_SINE_PULSE: {
                plotHalfSinePulse(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                plotHalfSinePulse(*ui->Graph2,
                                  *ui->LabelGraph2,
                                  DisplayGraphName2,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                break;
            }
            case FULL_SINE_DOUBLET: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                plotFullSineDoublet(*ui->Graph2,
                                    *ui->LabelGraph2,
                                    DisplayGraphName2,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                break;
            }
            case PULSE_TRAIN_3_2_1_1: {
                plot3211PulseTrain(*ui->Graph1,
                                   *ui->LabelGraph1,
                                   DisplayGraphName,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude1,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                plot3211PulseTrain(*ui->Graph2,
                                   *ui->LabelGraph2,
                                   DisplayGraphName2,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude1,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case LINEAR_SINE_SWEEP: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                break;
            }
            case LOGARITHMIC_SINE_SWEEP: {
                //                plotFullSineDoublet(*ui->Graph1,*ui->LabelGraph1,DisplayGraphName,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude1,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,1);
                //                plotFullSineDoublet(*ui->Graph2,*ui->LabelGraph2,DisplayGraphName2,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude1,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,1);
                break;
            }
            case RANDOM_SIGNAL: {
                generateRandomNoise(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    g_WaveFormFile_pkt.Amplitude1,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                generateRandomNoise(*ui->Graph2,
                                    *ui->LabelGraph2,
                                    DisplayGraphName2,
                                    g_WaveFormFile_pkt.Amplitude2,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            default: {
                break;
            }
            }
        }
        if ((g_WaveFormFile_pkt.CH3 == SET) && (g_WaveFormFile_pkt.CH4 == SET)) {
            if ((ui->SignalInjectionPoint_lineedit->text()
                 == "INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC")) {
                g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
                if (g_WaveFormFile_pkt.CH3 == SET) {
                    DisplayGraphName = "RIGHT INBOARD_ELEVON_ASYMMETRIC";
                }
                if (g_WaveFormFile_pkt.CH4 == SET) {
                    DisplayGraphName2 = "RIGHT OUTBOARD_ELEVON_ASYMMETRIC";
                }
            } else {
                if (g_WaveFormFile_pkt.CH3 == SET) {
                    DisplayGraphName = "RIGHT INBOARD_ELEVON_SYMMETRIC";
                }
                if (g_WaveFormFile_pkt.CH4 == SET) {
                    DisplayGraphName2 = "RIGHT OUTBOARD_ELEVON_SYMMETRIC";
                }
            }
            switch (signal) {
            case SQUARE_PULSE: {
                plotSquarePulse(*ui->Graph3,
                                *ui->LabelGraph3,
                                DisplayGraphName,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude2,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                plotSquarePulse(*ui->Graph4,
                                *ui->LabelGraph4,
                                DisplayGraphName2,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude2,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case SQUARE_DOUBLET: {
                plotSquareDoublet(*ui->Graph3,
                                  *ui->LabelGraph3,
                                  DisplayGraphName,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude2,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  2);
                plotSquareDoublet(*ui->Graph4,
                                  *ui->LabelGraph4,
                                  DisplayGraphName2,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude2,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  2);
                break;
            }
            case HALF_SINE_PULSE: {
                plotHalfSinePulse(*ui->Graph3,
                                  *ui->LabelGraph3,
                                  DisplayGraphName,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2047.5),
                                  (1),
                                  (0),
                                  (12));
                plotHalfSinePulse(*ui->Graph4,
                                  *ui->LabelGraph4,
                                  DisplayGraphName2,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                break;
            }
            case FULL_SINE_DOUBLET: {
                plotFullSineDoublet(*ui->Graph3,
                                    *ui->LabelGraph3,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (-1),
                                    (0),
                                    (12));

                plotFullSineDoublet(*ui->Graph4,
                                    *ui->LabelGraph4,
                                    DisplayGraphName2,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2047.5),
                                    (-1),
                                    (0),
                                    (12));
                break;
            }
            case PULSE_TRAIN_3_2_1_1: {
                plot3211PulseTrain(*ui->Graph3,
                                   *ui->LabelGraph3,
                                   DisplayGraphName,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude2,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                plot3211PulseTrain(*ui->Graph4,
                                   *ui->LabelGraph4,
                                   DisplayGraphName2,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude2,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case LINEAR_SINE_SWEEP: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (-1),
                                    (0),
                                    (12));
                break;
            }
            case LOGARITHMIC_SINE_SWEEP: {
                //                plotFullSineDoublet(*ui->Graph3,*ui->LabelGraph3,DisplayGraphName,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude2,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,2);
                //                plotFullSineDoublet(*ui->Graph4,*ui->LabelGraph4,DisplayGraphName2,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude2,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,2);
                break;
            }
            case RANDOM_SIGNAL: {
                generateRandomNoise(*ui->Graph3,
                                    *ui->LabelGraph3,
                                    DisplayGraphName,
                                    g_WaveFormFile_pkt.Amplitude1,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                generateRandomNoise(*ui->Graph4,
                                    *ui->LabelGraph4,
                                    DisplayGraphName2,
                                    g_WaveFormFile_pkt.Amplitude2,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            default: {
                break;
            }
            }
        }

        g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_WaveFormFile_pkt, sizeof(TestPoint_main));
        g_WaveFormFile_pkt.CRC_WORD = g_CRC_word;

        //        printStructure(g_WaveFormFile_pkt);

        //        saveWaveformDataToFile();
    }
}

void SignalGenerator::Rudder_single(uint8_t signal)
{
    if ((ui->SignalInjectionPoint_lineedit->text() == "RUDDER")) {
        ui->Graph2->setVisible(false);
        ui->Graph3->setVisible(false);
        ui->Graph4->setVisible(false);

        ui->LabelGraph1->setVisible(true);
        ui->LabelGraph2->setVisible(false);
        ui->LabelGraph3->setVisible(false);
        ui->LabelGraph4->setVisible(false);
        if (g_WaveFormFile_pkt.CH5 == SET) {
            DisplayGraphName = "RUDDER";
            switch (signal) {
            case SQUARE_PULSE: {
                plotSquarePulse(*ui->Graph1,
                                *ui->LabelGraph1,
                                DisplayGraphName,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude1,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case SQUARE_DOUBLET: {
                plotSquareDoublet(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude1,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  3);
                break;
            }
            case HALF_SINE_PULSE: {
                plotHalfSinePulse(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                break;
            }
            case FULL_SINE_DOUBLET: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                break;
            }
            case PULSE_TRAIN_3_2_1_1: {
                plot3211PulseTrain(*ui->Graph1,
                                   *ui->LabelGraph1,
                                   DisplayGraphName,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude1,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case LINEAR_SINE_SWEEP: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                break;
            }
            case LOGARITHMIC_SINE_SWEEP: {
                //                plotFullSineDoublet(*ui->Graph1,*ui->LabelGraph1,DisplayGraphName,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude1,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,3);
                break;
            }
            case RANDOM_SIGNAL: {
                generateRandomNoise(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    g_WaveFormFile_pkt.Amplitude1,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            default: {
                break;
            }
            }
        }

        g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_WaveFormFile_pkt, sizeof(TestPoint_main));
        g_WaveFormFile_pkt.CRC_WORD = g_CRC_word;

        //        printStructure(g_WaveFormFile_pkt);

        //        saveWaveformDataToFile();
    }
}

void SignalGenerator::Canard_Single(uint8_t signal)
{
    if ((ui->SignalInjectionPoint_lineedit->text() == "CANARD_SYMMETRIC")
        || (ui->SignalInjectionPoint_lineedit->text() == "CANARD_ASYMMETRIC")) {
        ui->Graph2->setVisible(true);
        ui->Graph3->setVisible(false);
        ui->Graph4->setVisible(false);

        ui->LabelGraph1->setVisible(true);
        ui->LabelGraph2->setVisible(true);
        ui->LabelGraph3->setVisible(false);
        ui->LabelGraph4->setVisible(false);
        if (g_WaveFormFile_pkt.CH6 == SET) {
            if ((ui->SignalInjectionPoint_lineedit->text() == "CANARD_ASYMMETRIC")) {
                g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
                DisplayGraphName = "LEFT CANARD_ASYMMETRIC";
            } else {
                DisplayGraphName = "LEFT CANARD_SYMMETRIC";
            }
            switch (signal) {
            case SQUARE_PULSE: {
                plotSquarePulse(*ui->Graph1,
                                *ui->LabelGraph1,
                                DisplayGraphName,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude1,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case SQUARE_DOUBLET: {
                plotSquareDoublet(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude1,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  3);
                break;
            }
            case HALF_SINE_PULSE: {
                plotHalfSinePulse(*ui->Graph1,
                                  *ui->LabelGraph1,
                                  DisplayGraphName,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                break;
            }
            case FULL_SINE_DOUBLET: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                break;
            }
            case PULSE_TRAIN_3_2_1_1: {
                plot3211PulseTrain(*ui->Graph1,
                                   *ui->LabelGraph1,
                                   DisplayGraphName,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude1,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case LINEAR_SINE_SWEEP: {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (1),
                                    (0),
                                    (12));
                break;
            }
            case LOGARITHMIC_SINE_SWEEP: {
                //                plotFullSineDoublet(*ui->Graph1,*ui->LabelGraph1,DisplayGraphName,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude1,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,3);
                break;
            }
            case RANDOM_SIGNAL: {
                generateRandomNoise(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    g_WaveFormFile_pkt.Amplitude1,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            default: {
                break;
            }
            }
        }
        if (g_WaveFormFile_pkt.CH7 == SET) {
            if ((ui->SignalInjectionPoint_lineedit->text() == "CANARD_ASYMMETRIC")) {
                g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
                DisplayGraphName = "RIGHT CANARD_ASYMMETRIC";
            } else {
                DisplayGraphName = "RIGHT CANARD_SYMMETRIC";
            }
            switch (signal) {
            case SQUARE_PULSE: {
                plotSquarePulse(*ui->Graph2,
                                *ui->LabelGraph2,
                                DisplayGraphName,
                                g_WaveFormFile_pkt.StartFrequency,
                                g_WaveFormFile_pkt.Amplitude2,
                                g_WaveFormFile_pkt.RiseTime,
                                g_WaveFormFile_pkt.FallTime,
                                g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case SQUARE_DOUBLET: {
                plotSquareDoublet(*ui->Graph2,
                                  *ui->LabelGraph2,
                                  DisplayGraphName,
                                  g_WaveFormFile_pkt.StartFrequency,
                                  g_WaveFormFile_pkt.Amplitude2,
                                  g_WaveFormFile_pkt.RiseTime,
                                  g_WaveFormFile_pkt.FallTime,
                                  g_WaveFormFile_pkt.NumberOfSamples,
                                  4);
                break;
            }
            case HALF_SINE_PULSE: {
                plotHalfSinePulse(*ui->Graph2,
                                  *ui->LabelGraph2,
                                  DisplayGraphName,
                                  dataArray.Start_FreqHz,
                                  dataArray.Freq_StepHz,
                                  dataArray.End_FreqHz,
                                  QVector<double>{dataArray.DwellDuration_Secs},
                                  (100 * 100),
                                  HalfsineTable,
                                  (2048),
                                  (1),
                                  (0),
                                  (12));
                break;
            }
            case FULL_SINE_DOUBLET: {
                plotFullSineDoublet(*ui->Graph2,
                                    *ui->LabelGraph2,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2047.5),
                                    (-1),
                                    (0),
                                    (12));
                break;
            }
            case PULSE_TRAIN_3_2_1_1: {
                plot3211PulseTrain(*ui->Graph2,
                                   *ui->LabelGraph2,
                                   DisplayGraphName,
                                   g_WaveFormFile_pkt.StartFrequency,
                                   g_WaveFormFile_pkt.Amplitude2,
                                   g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            case LINEAR_SINE_SWEEP:

            {
                plotFullSineDoublet(*ui->Graph1,
                                    *ui->LabelGraph1,
                                    DisplayGraphName,
                                    dataArray.Start_FreqHz,
                                    dataArray.Freq_StepHz,
                                    dataArray.End_FreqHz,
                                    QVector<double>{dataArray.DwellDuration_Secs},
                                    (100 * 100),
                                    sineTable,
                                    (2048),
                                    (-1),
                                    (0),
                                    (12));
                break;
            }
            case LOGARITHMIC_SINE_SWEEP: {
                //                plotFullSineDoublet(*ui->Graph2,*ui->LabelGraph2,DisplayGraphName,
                //                                    g_WaveFormFile_pkt.StartFrequency,g_WaveFormFile_pkt.Amplitude2,
                //                                    g_WaveFormFile_pkt.NumberOfSamples,4);
                break;
            }
            case RANDOM_SIGNAL: {
                generateRandomNoise(*ui->Graph2,
                                    *ui->LabelGraph2,
                                    DisplayGraphName,
                                    g_WaveFormFile_pkt.Amplitude2,
                                    g_WaveFormFile_pkt.NumberOfSamples);
                break;
            }
            default: {
                break;
            }
            }
        }
        g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_WaveFormFile_pkt, sizeof(TestPoint_main));
        g_WaveFormFile_pkt.CRC_WORD = g_CRC_word;
        //        printStructure(g_WaveFormFile_pkt);
        //        saveWaveformDataToFile();
    }
}

void SignalGenerator::plotWaveforms(const QString text)
{
    switch (stringToSignalType(text)) {
    case (SQUARE_PULSE): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(SQUARE_PULSE);
            IO_ELEVON_Combined(SQUARE_PULSE);
            Rudder_single(SQUARE_PULSE);
            Canard_Single(SQUARE_PULSE);
        }
        break;
    }
    case (SQUARE_DOUBLET): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(SQUARE_DOUBLET);
            IO_ELEVON_Combined(SQUARE_DOUBLET);
            Rudder_single(SQUARE_DOUBLET);
            Canard_Single(SQUARE_DOUBLET);
        }
        break;
    }
    case (HALF_SINE_PULSE): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(HALF_SINE_PULSE);
            IO_ELEVON_Combined(HALF_SINE_PULSE);
            Rudder_single(HALF_SINE_PULSE);
            Canard_Single(HALF_SINE_PULSE);
        }
        break;
    }
    case (FULL_SINE_DOUBLET): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(FULL_SINE_DOUBLET);
            IO_ELEVON_Combined(FULL_SINE_DOUBLET);
            Rudder_single(FULL_SINE_DOUBLET);
            Canard_Single(FULL_SINE_DOUBLET);
        }
        break;
    }
    case (PULSE_TRAIN_3_2_1_1): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(PULSE_TRAIN_3_2_1_1);
            IO_ELEVON_Combined(PULSE_TRAIN_3_2_1_1);
            Rudder_single(PULSE_TRAIN_3_2_1_1);
            Canard_Single(PULSE_TRAIN_3_2_1_1);
        }
        break;
    }
    case (LINEAR_SINE_SWEEP): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(LINEAR_SINE_SWEEP);
            IO_ELEVON_Combined(LINEAR_SINE_SWEEP);
            Rudder_single(LINEAR_SINE_SWEEP);
            Canard_Single(LINEAR_SINE_SWEEP);
        }
        break;

        break;
    }
    case (LOGARITHMIC_SINE_SWEEP): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(LOGARITHMIC_SINE_SWEEP);
            IO_ELEVON_Combined(LOGARITHMIC_SINE_SWEEP);
            Rudder_single(LOGARITHMIC_SINE_SWEEP);
            Canard_Single(LOGARITHMIC_SINE_SWEEP);
        }
        break;

        break;
    }
    case (RANDOM_SIGNAL): {
        if (g_WaveFormFile_pkt.InvertFlag == true) {
            g_WaveFormFile_pkt.Amplitude1 = g_WaveFormFile_pkt.Amplitude1 * -1;
            g_WaveFormFile_pkt.Amplitude2 = g_WaveFormFile_pkt.Amplitude2 * -1;
        }
        if (ui->ProjectName->currentText() == "LCA AF MK2") {
            IO_ELEVON_Single(RANDOM_SIGNAL);
            IO_ELEVON_Combined(RANDOM_SIGNAL);
            Rudder_single(RANDOM_SIGNAL);
            Canard_Single(RANDOM_SIGNAL);
        }

        break;
    }
    default:
        break;
    }
}

void SignalGenerator::generateRandomNoise(
    QCustomPlot &plot, QLabel &Graphlabel, const QString GraphName, double amplitude, int numPoints)
{
    QVector<double> x(numPoints), y(numPoints);
    double halfAmplitude = amplitude / 2.0;

    QVector<double> y12(numPoints);
    // Seed the random generator
    std::srand(static_cast<unsigned int>(std::time(0)));
    // Generate random noise
    for (int i = 0; i < numPoints; ++i) {
        x[i] = i;
        y[i] = -halfAmplitude + static_cast<double>(std::rand()) / RAND_MAX * amplitude;
    }

    // Configure the plot
    plot.clearGraphs(); // Clear any existing plots
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend
                         | QCP::iSelectPlottables);
    plot.addGraph();
    plot.graph(0)->setData(x, y12);
    plot.xAxis->setLabel("Sample Index");
    plot.yAxis->setLabel("Voltage (V)");
    plot.xAxis->setRange(0, numPoints);
    plot.yAxis->setRange(-halfAmplitude, halfAmplitude);

    // Refresh the plot
    plot.replot();
    plot.xAxis->rescale();
    plot.update();
    Graphlabel.setText(GraphName);
}

void SignalGenerator::plot3211PulseTrain(QCustomPlot &plot,
                                         QLabel &Graphlabel,
                                         const QString GraphName,
                                         double frequency,
                                         double amplitude,
                                         int numSamples)
{
    // Total time for the pulse train
    double totalTime = 1.0 / frequency;

    double dt = totalTime / numSamples;

    numSamples += 1; // to match the 0
    // Time vector with linspace equivalent
    QVector<double> t(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        t[i] = i * dt;
    }

    // Initialize waveform vector
    QVector<double> waveform(numSamples, 0.0);

    // Define the time interval
    double timeInterval = totalTime / 27.0;

    // Generate waveform sections
    for (int i = 0; i < numSamples; ++i) {
        double currentTime = t[i];

        if (currentTime >= 0 && currentTime < timeInterval) {
            // Rising edge: 0 to time_interval
            waveform[i] = (1 / timeInterval) * currentTime;
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= timeInterval && currentTime < 9 * timeInterval) {
            // High: time_interval to 9*time_interval
            waveform[i] = 1.0;
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 9 * timeInterval && currentTime < 10 * timeInterval) {
            // Falling edge: 9*time_interval to 10*time_interval
            waveform[i] = 1.0 - (1 / timeInterval) * (currentTime - 9 * timeInterval);
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 10 * timeInterval && currentTime < 11 * timeInterval) {
            // Falling edge: 10*time_interval to 11*time_interval
            waveform[i] = -(1 / timeInterval) * (currentTime - 10 * timeInterval);
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 11 * timeInterval && currentTime < 16 * timeInterval) {
            // Low: 11*time_interval to 16*time_interval
            waveform[i] = -1.0;
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 16 * timeInterval && currentTime < 17 * timeInterval) {
            // Rising edge: 16*time_interval to 17*time_interval
            waveform[i] = -1.0 + (1 / timeInterval) * (currentTime - 16 * timeInterval);
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 17 * timeInterval && currentTime < 18 * timeInterval) {
            // Rising edge: 17*time_interval to 18*time_interval
            waveform[i] = (1 / timeInterval) * (currentTime - 17 * timeInterval);
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 18 * timeInterval && currentTime < 21 * timeInterval) {
            // High: 18*time_interval to 21*time_interval
            waveform[i] = 1.0;
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 21 * timeInterval && currentTime < 22 * timeInterval) {
            // Falling edge: 21*time_interval to 22*time_interval
            waveform[i] = 1.0 - (1 / timeInterval) * (currentTime - 21 * timeInterval);
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 22 * timeInterval && currentTime < 23 * timeInterval) {
            // Falling edge: 22*time_interval to 23*time_interval
            waveform[i] = -(1 / timeInterval) * (currentTime - 22 * timeInterval);
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 23 * timeInterval && currentTime < 26 * timeInterval) {
            // Low: 23*time_interval to 26*time_interval
            waveform[i] = -1.0;
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        } else if (currentTime >= 26 * timeInterval && currentTime < 27 * timeInterval) {
            // Rising edge: 26*time_interval to 27*time_interval
            waveform[i] = -1.0 + (1 / timeInterval) * (currentTime - 26 * timeInterval);
            //            g_WaveFormFile_pkt.waveformSamples[i] = waveform[i];
        }
    }

    // Scale waveform to amplitude
    QVector<double> y(numSamples);
    QVector<double> y12(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        y[i] = waveform[i] * (amplitude / 2.0);
    }

    // Plot the waveform
    plot.clearGraphs(); // Clear any existing plots
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend
                         | QCP::iSelectPlottables);
    plot.addGraph();
    plot.graph(0)->setData(t, y12);

    // Configure plot axes
    plot.xAxis->setLabel("Time (s)");
    plot.yAxis->setLabel("Amplitude");
    plot.xAxis->setRange(0, totalTime);
    plot.yAxis->setRange(-amplitude, amplitude);

    // Replot to display the graph
    plot.replot();
    plot.xAxis->rescale();
    plot.update();
    Graphlabel.setText(GraphName);
}

void SignalGenerator::plotFullSineDoublet(QCustomPlot &plot,
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
                                          int n_bits)
{
    //Fs = 128.0 * 100.0; // 12.8 kS/s
    SweepResult r2 = generateSineSweepCodes(freqStart,
                                            freqStep,
                                            freqStop,
                                            QVector<double>{
                                                durations}, // scalar duration applied to all freqs
                                            Fs,
                                            sineTable,
                                            (MID),
                                            (gain),
                                            (dcOffset),
                                            n_bits);

    QVector<double> x(r2.codes.size());
    for (int i = 0; i < x.size(); ++i) {
        x[i] = i / Fs; // seconds on x-axis
    }
    //    qDebug() << "number of samples : " << QString::number(r2.codes.size());
    QVector<double> y(r2.codes.size());
    for (int i = 0; i < y.size(); ++i) {
        y[i] = static_cast<double>(
            (r2.codes[i] * (0.000244140625))
            * (dataArray.C0 / 1000)); // dataArray.Amplitude_percent_of_stroke;

        y[i] -= ((dataArray.C0 / 1000) / 2);
    }

    // Plot the waveform using QCustomPlot
    plot.clearGraphs(); // Clear any existing plots
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend
                         | QCP::iSelectPlottables);
    plot.addGraph();
    plot.graph(0)->setData(x, y);
    plot.xAxis->setLabel("Time [s]");
    plot.yAxis->setLabel("Voltage [V]");
    plot.xAxis->setRange(0,
                         ((freqStop - freqStart) / (freqStep)) + 1); // X-axis range: one full period
    plot.yAxis->setRange(0, (dataArray.C0 / 1000) / 2); // Y-axis range based on amplitude
    plot.replot();
    plot.xAxis->rescale();
    plot.update();
    Graphlabel.setText(GraphName);
}

void SignalGenerator::plotHalfSinePulse(QCustomPlot &plot,
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
                                        int n_bits)

{
    //Fs = 128.0 * 100.0; // 12.8 kS/s
    SweepResult r2 = generateSineSweepCodes(freqStart,
                                            freqStep,
                                            freqStop,
                                            QVector<double>{
                                                durations}, // scalar duration applied to all freqs
                                            Fs,
                                            HalfsineTable,
                                            (MID),
                                            (gain),
                                            (dcOffset),
                                            n_bits);

    QVector<double> x(r2.codes.size());
    for (int i = 0; i < x.size(); ++i) {
        x[i] = i / Fs; // seconds on x-axis
    }
    //    qDebug() << "number of samples : " << QString::number(r2.codes.size());
    QVector<double> y(r2.codes.size());
    for (int i = 0; i < y.size(); ++i) {
        y[i] = static_cast<double>(
            (r2.codes[i] * (0.000244140625))
            * (dataArray.C0 / 1000)); // dataArray.Amplitude_percent_of_stroke;

        //y[i] -= ((dataArray.C0 / 1000) / 2);
        // y[i] += dcOffset;
    }

    // Plot the waveform using QCustomPlot
    plot.clearGraphs(); // Clear any existing plots
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend
                         | QCP::iSelectPlottables);
    plot.addGraph();
    plot.graph(0)->setData(x, y);
    plot.xAxis->setLabel("Time [s]");
    plot.yAxis->setLabel("Voltage [V]");
    plot.xAxis->setRange(0,
                         ((freqStop - freqStart) / (freqStep)) + 1); // X-axis range: one full period
    plot.yAxis->setRange(0, (dataArray.C0 / 1000) / 2);
    //  /* -((dataArray.C0 / 1000) / 2)*/); // Y-axis range based on amplitude

    plot.replot();
    plot.xAxis->rescale(true);
    plot.update();
    Graphlabel.setText(GraphName);
}

void SignalGenerator::plotSquareDoublet(QCustomPlot &plot,
                                        QLabel &Graphlabel,
                                        const QString GraphName,
                                        double frequency,
                                        double amplitude,
                                        double riseTime,
                                        double fallTime,
                                        int numSamples,
                                        uint8_t pktNo)
{
    if (frequency <= 0 || numSamples <= 1 || riseTime <= 0 || fallTime <= 0) {
        qWarning() << "Invalid parameters for square doublet!";
        return;
    }

    double T = 1.0 / frequency;
    double total_transition = riseTime + fallTime;
    double max_transition = T / 2.0;
    if (total_transition > max_transition) {
        double scale = max_transition / total_transition;
        riseTime *= scale;
        fallTime *= scale;
    }

    int start_sign = (amplitude < 0) ? -1 : 1;
    double A = std::abs(amplitude);

    QVector<double> t(numSamples), y(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        t[i] = (T * i) / (numSamples - 1); // include endpoint
        y[i] = 0.0;
    }

    int p1 = start_sign;
    int p2 = -start_sign;

    for (int i = 0; i < numSamples; ++i) {
        double ti = t[i];
        if (ti < riseTime) {
            y[i] = p1 * (A / riseTime) * ti;
        } else if (ti >= riseTime && ti < (T / 2.0 - fallTime)) {
            y[i] = p1 * A;
        } else if (ti >= (T / 2.0 - fallTime) && ti < (T / 2.0)) {
            y[i] = p1 * (A - (A / fallTime) * (ti - (T / 2.0 - fallTime)));
        } else if (ti >= (T / 2.0) && ti < (T / 2.0 + riseTime)) {
            y[i] = p2 * (A / riseTime) * (ti - (T / 2.0));
        } else if (ti >= (T / 2.0 + riseTime) && ti < (T - fallTime)) {
            y[i] = p2 * A;
        } else if (ti >= (T - fallTime) && ti <= T) {
            y[i] = p2 * (A - (A / fallTime) * (ti - (T - fallTime)));
        }
    }

    // Plotting
    plot.clearGraphs();
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend
                         | QCP::iSelectPlottables);
    plot.addGraph();
    plot.graph(0)->setData(t, y);
    plot.graph(0)->setName(QString("Square Doublet (Pkt %1)").arg(pktNo));
    plot.xAxis->setLabel("Time (s)");
    plot.yAxis->setLabel("Amplitude (mm)");

    plot.xAxis->setRange(0, T);
    plot.yAxis->rescale();
    plot.legend->setVisible(true);
    plot.replot();

    Graphlabel.setText(GraphName);

#if 0
    // Calculate the period based on frequency
    double T = 1.0 / frequency;

    // Validate the rise and fall times
    if (2 * (riseTime + fallTime) > T) {
        QMessageBox::critical(this, "Error", "The sum of rise and fall times, when doubled, should not exceed the period.");
        return;
    }

    // Time step and time vector
    double dt = T / numSamples;
    numSamples += 1; // to match the 0
    QVector<double> t(numSamples), y(numSamples);
    QVector<double> y12(numSamples);

    // Adjust amplitude to half
    double halfAmplitude = amplitude / 2.0;

    // Generate waveform data
    for (int i = 0; i < numSamples; ++i) {
        t[i] = i * dt; // Time vector

        if (t[i] < riseTime) {
            // Rise to +1
            y[i] = (halfAmplitude / riseTime) * t[i];
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else if (t[i] < T / 2 - fallTime) {
            // High at +1
            y[i] = halfAmplitude;
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else if (t[i] < T / 2) {
            // Fall to 0
            y[i] = halfAmplitude - (halfAmplitude / fallTime) * (t[i] - (T / 2 - fallTime));
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else if (t[i] < T / 2 + riseTime) {
            // Fall to -1
            y[i] = -(halfAmplitude / riseTime) * (t[i] - T / 2);
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else if (t[i] < T - fallTime) {
            // Low at -1
            y[i] = -halfAmplitude;
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else if (t[i] <= T) {
            // Rise to 0
            y[i] = -halfAmplitude + (halfAmplitude / riseTime) * (t[i] - (T - riseTime));
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        }
    }

    // Plot the waveform
    plot.clearGraphs(); // Clear any existing plots
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend
                         | QCP::iSelectPlottables);
    plot.addGraph();
    plot.graph(0)->setData(t, y12);

    // Configure the plot axes
    plot.xAxis->setLabel("Time (s)");
    plot.yAxis->setLabel("Amplitude");
    plot.xAxis->setRange(0, T);
    plot.yAxis->setRange(-amplitude, amplitude);

    // Replot to display the graph
    plot.replot();
    plot.xAxis->rescale();
    plot.update();

    Graphlabel.setText(GraphName);
#endif
}

void SignalGenerator::plotSquarePulse(QCustomPlot &plot,
                                      QLabel &Graphlabel,
                                      const QString GraphName,
                                      double frequency,
                                      double amplitude,
                                      double riseTime,
                                      double fallTime,
                                      int numSamples)
{
    // Calculate period of the waveform
    double T = 1.0 / frequency;
    // Validate riseTime and fallTime
    if (riseTime + fallTime > T / 2.0) {
        QMessageBox::critical(
            this, "Error", "The sum of rise time and fall time should not exceed half the period.");
        return;
    }
    // Time step for sampling
    double dt = T / numSamples;
    // Initialize time and waveform vectors
    numSamples += 1; // to match the 0
    QVector<double> t(numSamples), y(numSamples);
    QVector<double> y12(numSamples);
    // Calculate the waveform
    for (int i = 0; i < numSamples; ++i) {
        t[i] = i * dt;
        if (t[i] < riseTime) {
            // Rise phase
            y[i] = amplitude * (t[i] / riseTime);
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else if (t[i] < riseTime + (T / 2.0 - riseTime - fallTime)) {
            // High phase
            y[i] = amplitude;
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else if (t[i] < T / 2.0) {
            // Fall phase
            y[i] = amplitude
                   * (1.0 - (t[i] - riseTime - (T / 2.0 - riseTime - fallTime)) / fallTime);
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        } else {
            // Low phase (second half of the square pulse)
            y[i] = 0.0;
            //            y12[i] = Convert_Plot_Data_to_Rep_DAC(y[i]);
            //            DAC_WF_update(y[i], i, pktNo);
        }
    }

    // Plot the waveform using QCustomPlot
    plot.clearGraphs();
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend
                         | QCP::iSelectPlottables);
    plot.addGraph();
    plot.graph(0)->setData(t, y12);
    // Set axis labels
    plot.xAxis->setLabel("Time (s)");
    plot.yAxis->setLabel("Amplitude");
    // Set axis ranges
    plot.xAxis->setRange(0, T);                              // Full period on the x-axis
    plot.yAxis->setRange(-0.1 * amplitude, 1.1 * amplitude); // Slight padding for y-axis
    // Replot to update the graph
    plot.replot();
    plot.xAxis->rescale();
    plot.update();

    Graphlabel.setText(GraphName);
}

SignalType stringToSignalType(const QString &Signal_type)
{
    static QMap<QString, SignalType> commandMap = {{"SQUARE_PULSE", SQUARE_PULSE},
                                                   {"SQUARE_DOUBLET", SQUARE_DOUBLET},
                                                   {"HALF_SINE_PULSE", HALF_SINE_PULSE},
                                                   {"FULL_SINE_DOUBLET", FULL_SINE_DOUBLET},
                                                   {"PULSE_TRAIN_3_2_1_1", PULSE_TRAIN_3_2_1_1},
                                                   {"LINEAR_SINE_SWEEP", LINEAR_SINE_SWEEP},
                                                   {"LOGARITHMIC_SINE_SWEEP",
                                                    LOGARITHMIC_SINE_SWEEP},
                                                   {"RANDOM_SIGNAL", RANDOM_SIGNAL}};

    return commandMap.value(Signal_type);
}

SignalInjectionPoint stringToCommand(const QString &command)
{
    static QMap<QString, SignalInjectionPoint> commandMap
        = {{"INBOARD_ELEVON_SYMMETRIC", INBOARD_ELEVON_SYMMETRIC},
           {"OUTBOARD_ELEVON_SYMMETRIC", OUTBOARD_ELEVON_SYMMETRIC},
           {"INBOARD_ELEVON_ASYMMETRIC", INBOARD_ELEVON_ASYMMETRIC},
           {"OUTBOARD_ELEVON_ASYMMETRIC", OUTBOARD_ELEVON_ASYMMETRIC},
           {"INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC", INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC},
           {"INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC", INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC},
           {"RUDDER", RUDDER},
           {"CANARD_SYMMETRIC", CANARD_SYMMETRIC},
           {"CANARD_ASYMMETRIC", CANARD_ASYMMETRIC},
           {"PITCH_STICK_FTU_INPUT", PITCH_STICK_FTU_INPUT},
           {"ROLL_STICK_FTU_INPUT", ROLL_STICK_FTU_INPUT},
           {"RUDDER_PEDAL_FTU_INPUT", RUDDER_PEDAL_FTU_INPUT},
           {"SLAT_INPUT", SLAT_INPUT},
           {"AIRBRAKE_INPUT", AIRBRAKE_INPUT},
           {"STABILATORS_SYMMETRIC", STABILATORS_SYMMETRIC},
           {"STABILATORS_ASYMMETRIC", STABILATORS_ASYMMETRIC},
           {"AILERONS_SYMMETRIC", AILERONS_SYMMETRIC},
           {"AILERONS_ASYMMETRIC", AILERONS_ASYMMETRIC},
           {"RUDDER_SYMMETRIC", RUDDER_SYMMETRIC},
           {"RUDDER_ASYMMETRIC", RUDDER_ASYMMETRIC},
           {"TEF_SYMMETRIC", TEF_SYMMETRIC},
           {"TEF_ASYMMETRIC", TEF_ASYMMETRIC},
           {"LEF_ACTUATOR_INPUT", LEF_ACTUATOR_INPUT}};
    return commandMap.value(command);
}

QVector<double> sineTable = {
    2048, 2050, 2051, 2053, 2054, 2056, 2058, 2059, 2061, 2062, 2064, 2066, 2067, 2069, 2071, 2072,
    2074, 2075, 2077, 2079, 2080, 2082, 2083, 2085, 2087, 2088, 2090, 2091, 2093, 2095, 2096, 2098,
    2099, 2101, 2103, 2104, 2106, 2108, 2109, 2111, 2112, 2114, 2116, 2117, 2119, 2120, 2122, 2124,
    2125, 2127, 2128, 2130, 2132, 2133, 2135, 2136, 2138, 2140, 2141, 2143, 2144, 2146, 2148, 2149,
    2151, 2153, 2154, 2156, 2157, 2159, 2161, 2162, 2164, 2165, 2167, 2169, 2170, 2172, 2173, 2175,
    2177, 2178, 2180, 2181, 2183, 2185, 2186, 2188, 2189, 2191, 2193, 2194, 2196, 2197, 2199, 2201,
    2202, 2204, 2205, 2207, 2209, 2210, 2212, 2213, 2215, 2217, 2218, 2220, 2222, 2223, 2225, 2226,
    2228, 2230, 2231, 2233, 2234, 2236, 2238, 2239, 2241, 2242, 2244, 2246, 2247, 2249, 2250, 2252,
    2254, 2255, 2257, 2258, 2260, 2262, 2263, 2265, 2266, 2268, 2270, 2271, 2273, 2274, 2276, 2278,
    2279, 2281, 2282, 2284, 2286, 2287, 2289, 2290, 2292, 2294, 2295, 2297, 2298, 2300, 2301, 2303,
    2305, 2306, 2308, 2309, 2311, 2313, 2314, 2316, 2317, 2319, 2321, 2322, 2324, 2325, 2327, 2329,
    2330, 2332, 2333, 2335, 2337, 2338, 2340, 2341, 2343, 2345, 2346, 2348, 2349, 2351, 2352, 2354,
    2356, 2357, 2359, 2360, 2362, 2364, 2365, 2367, 2368, 2370, 2372, 2373, 2375, 2376, 2378, 2379,
    2381, 2383, 2384, 2386, 2387, 2389, 2391, 2392, 2394, 2395, 2397, 2399, 2400, 2402, 2403, 2405,
    2406, 2408, 2410, 2411, 2413, 2414, 2416, 2418, 2419, 2421, 2422, 2424, 2425, 2427, 2429, 2430,
    2432, 2433, 2435, 2436, 2438, 2440, 2441, 2443, 2444, 2446, 2448, 2449, 2451, 2452, 2454, 2455,
    2457, 2459, 2460, 2462, 2463, 2465, 2466, 2468, 2470, 2471, 2473, 2474, 2476, 2477, 2479, 2481,
    2482, 2484, 2485, 2487, 2488, 2490, 2492, 2493, 2495, 2496, 2498, 2499, 2501, 2503, 2504, 2506,
    2507, 2509, 2510, 2512, 2514, 2515, 2517, 2518, 2520, 2521, 2523, 2525, 2526, 2528, 2529, 2531,
    2532, 2534, 2535, 2537, 2539, 2540, 2542, 2543, 2545, 2546, 2548, 2550, 2551, 2553, 2554, 2556,
    2557, 2559, 2560, 2562, 2564, 2565, 2567, 2568, 2570, 2571, 2573, 2574, 2576, 2578, 2579, 2581,
    2582, 2584, 2585, 2587, 2588, 2590, 2592, 2593, 2595, 2596, 2598, 2599, 2601, 2602, 2604, 2605,
    2607, 2609, 2610, 2612, 2613, 2615, 2616, 2618, 2619, 2621, 2622, 2624, 2626, 2627, 2629, 2630,
    2632, 2633, 2635, 2636, 2638, 2639, 2641, 2643, 2644, 2646, 2647, 2649, 2650, 2652, 2653, 2655,
    2656, 2658, 2659, 2661, 2662, 2664, 2666, 2667, 2669, 2670, 2672, 2673, 2675, 2676, 2678, 2679,
    2681, 2682, 2684, 2685, 2687, 2689, 2690, 2692, 2693, 2695, 2696, 2698, 2699, 2701, 2702, 2704,
    2705, 2707, 2708, 2710, 2711, 2713, 2714, 2716, 2717, 2719, 2721, 2722, 2724, 2725, 2727, 2728,
    2730, 2731, 2733, 2734, 2736, 2737, 2739, 2740, 2742, 2743, 2745, 2746, 2748, 2749, 2751, 2752,
    2754, 2755, 2757, 2758, 2760, 2761, 2763, 2764, 2766, 2767, 2769, 2770, 2772, 2773, 2775, 2776,
    2778, 2779, 2781, 2782, 2784, 2785, 2787, 2788, 2790, 2791, 2793, 2794, 2796, 2797, 2799, 2800,
    2802, 2803, 2805, 2806, 2808, 2809, 2811, 2812, 2814, 2815, 2817, 2818, 2820, 2821, 2823, 2824,
    2826, 2827, 2829, 2830, 2832, 2833, 2835, 2836, 2838, 2839, 2841, 2842, 2844, 2845, 2847, 2848,
    2850, 2851, 2852, 2854, 2855, 2857, 2858, 2860, 2861, 2863, 2864, 2866, 2867, 2869, 2870, 2872,
    2873, 2875, 2876, 2878, 2879, 2881, 2882, 2883, 2885, 2886, 2888, 2889, 2891, 2892, 2894, 2895,
    2897, 2898, 2900, 2901, 2902, 2904, 2905, 2907, 2908, 2910, 2911, 2913, 2914, 2916, 2917, 2919,
    2920, 2921, 2923, 2924, 2926, 2927, 2929, 2930, 2932, 2933, 2935, 2936, 2937, 2939, 2940, 2942,
    2943, 2945, 2946, 2948, 2949, 2950, 2952, 2953, 2955, 2956, 2958, 2959, 2961, 2962, 2963, 2965,
    2966, 2968, 2969, 2971, 2972, 2973, 2975, 2976, 2978, 2979, 2981, 2982, 2984, 2985, 2986, 2988,
    2989, 2991, 2992, 2994, 2995, 2996, 2998, 2999, 3001, 3002, 3003, 3005, 3006, 3008, 3009, 3011,
    3012, 3013, 3015, 3016, 3018, 3019, 3021, 3022, 3023, 3025, 3026, 3028, 3029, 3030, 3032, 3033,
    3035, 3036, 3037, 3039, 3040, 3042, 3043, 3044, 3046, 3047, 3049, 3050, 3052, 3053, 3054, 3056,
    3057, 3059, 3060, 3061, 3063, 3064, 3065, 3067, 3068, 3070, 3071, 3072, 3074, 3075, 3077, 3078,
    3079, 3081, 3082, 3084, 3085, 3086, 3088, 3089, 3091, 3092, 3093, 3095, 3096, 3097, 3099, 3100,
    3102, 3103, 3104, 3106, 3107, 3108, 3110, 3111, 3113, 3114, 3115, 3117, 3118, 3119, 3121, 3122,
    3124, 3125, 3126, 3128, 3129, 3130, 3132, 3133, 3134, 3136, 3137, 3139, 3140, 3141, 3143, 3144,
    3145, 3147, 3148, 3149, 3151, 3152, 3154, 3155, 3156, 3158, 3159, 3160, 3162, 3163, 3164, 3166,
    3167, 3168, 3170, 3171, 3172, 3174, 3175, 3176, 3178, 3179, 3180, 3182, 3183, 3184, 3186, 3187,
    3188, 3190, 3191, 3192, 3194, 3195, 3196, 3198, 3199, 3200, 3202, 3203, 3204, 3206, 3207, 3208,
    3210, 3211, 3212, 3214, 3215, 3216, 3218, 3219, 3220, 3222, 3223, 3224, 3226, 3227, 3228, 3230,
    3231, 3232, 3233, 3235, 3236, 3237, 3239, 3240, 3241, 3243, 3244, 3245, 3247, 3248, 3249, 3250,
    3252, 3253, 3254, 3256, 3257, 3258, 3260, 3261, 3262, 3263, 3265, 3266, 3267, 3269, 3270, 3271,
    3273, 3274, 3275, 3276, 3278, 3279, 3280, 3282, 3283, 3284, 3285, 3287, 3288, 3289, 3290, 3292,
    3293, 3294, 3296, 3297, 3298, 3299, 3301, 3302, 3303, 3305, 3306, 3307, 3308, 3310, 3311, 3312,
    3313, 3315, 3316, 3317, 3318, 3320, 3321, 3322, 3323, 3325, 3326, 3327, 3328, 3330, 3331, 3332,
    3334, 3335, 3336, 3337, 3339, 3340, 3341, 3342, 3344, 3345, 3346, 3347, 3348, 3350, 3351, 3352,
    3353, 3355, 3356, 3357, 3358, 3360, 3361, 3362, 3363, 3365, 3366, 3367, 3368, 3369, 3371, 3372,
    3373, 3374, 3376, 3377, 3378, 3379, 3381, 3382, 3383, 3384, 3385, 3387, 3388, 3389, 3390, 3391,
    3393, 3394, 3395, 3396, 3398, 3399, 3400, 3401, 3402, 3404, 3405, 3406, 3407, 3408, 3410, 3411,
    3412, 3413, 3414, 3416, 3417, 3418, 3419, 3420, 3422, 3423, 3424, 3425, 3426, 3428, 3429, 3430,
    3431, 3432, 3433, 3435, 3436, 3437, 3438, 3439, 3441, 3442, 3443, 3444, 3445, 3446, 3448, 3449,
    3450, 3451, 3452, 3453, 3455, 3456, 3457, 3458, 3459, 3460, 3462, 3463, 3464, 3465, 3466, 3467,
    3469, 3470, 3471, 3472, 3473, 3474, 3476, 3477, 3478, 3479, 3480, 3481, 3482, 3484, 3485, 3486,
    3487, 3488, 3489, 3490, 3492, 3493, 3494, 3495, 3496, 3497, 3498, 3500, 3501, 3502, 3503, 3504,
    3505, 3506, 3507, 3509, 3510, 3511, 3512, 3513, 3514, 3515, 3516, 3518, 3519, 3520, 3521, 3522,
    3523, 3524, 3525, 3527, 3528, 3529, 3530, 3531, 3532, 3533, 3534, 3535, 3537, 3538, 3539, 3540,
    3541, 3542, 3543, 3544, 3545, 3546, 3548, 3549, 3550, 3551, 3552, 3553, 3554, 3555, 3556, 3557,
    3558, 3560, 3561, 3562, 3563, 3564, 3565, 3566, 3567, 3568, 3569, 3570, 3571, 3572, 3574, 3575,
    3576, 3577, 3578, 3579, 3580, 3581, 3582, 3583, 3584, 3585, 3586, 3587, 3588, 3590, 3591, 3592,
    3593, 3594, 3595, 3596, 3597, 3598, 3599, 3600, 3601, 3602, 3603, 3604, 3605, 3606, 3607, 3608,
    3609, 3611, 3612, 3613, 3614, 3615, 3616, 3617, 3618, 3619, 3620, 3621, 3622, 3623, 3624, 3625,
    3626, 3627, 3628, 3629, 3630, 3631, 3632, 3633, 3634, 3635, 3636, 3637, 3638, 3639, 3640, 3641,
    3642, 3643, 3644, 3645, 3646, 3647, 3648, 3649, 3650, 3651, 3652, 3653, 3654, 3655, 3656, 3657,
    3658, 3659, 3660, 3661, 3662, 3663, 3664, 3665, 3666, 3667, 3668, 3669, 3670, 3671, 3672, 3673,
    3674, 3675, 3676, 3677, 3678, 3679, 3680, 3681, 3682, 3683, 3684, 3685, 3686, 3687, 3688, 3689,
    3690, 3691, 3692, 3692, 3693, 3694, 3695, 3696, 3697, 3698, 3699, 3700, 3701, 3702, 3703, 3704,
    3705, 3706, 3707, 3708, 3709, 3710, 3711, 3711, 3712, 3713, 3714, 3715, 3716, 3717, 3718, 3719,
    3720, 3721, 3722, 3723, 3724, 3724, 3725, 3726, 3727, 3728, 3729, 3730, 3731, 3732, 3733, 3734,
    3735, 3736, 3736, 3737, 3738, 3739, 3740, 3741, 3742, 3743, 3744, 3745, 3745, 3746, 3747, 3748,
    3749, 3750, 3751, 3752, 3753, 3754, 3754, 3755, 3756, 3757, 3758, 3759, 3760, 3761, 3761, 3762,
    3763, 3764, 3765, 3766, 3767, 3768, 3769, 3769, 3770, 3771, 3772, 3773, 3774, 3775, 3775, 3776,
    3777, 3778, 3779, 3780, 3781, 3781, 3782, 3783, 3784, 3785, 3786, 3787, 3787, 3788, 3789, 3790,
    3791, 3792, 3793, 3793, 3794, 3795, 3796, 3797, 3798, 3798, 3799, 3800, 3801, 3802, 3803, 3803,
    3804, 3805, 3806, 3807, 3808, 3808, 3809, 3810, 3811, 3812, 3812, 3813, 3814, 3815, 3816, 3817,
    3817, 3818, 3819, 3820, 3821, 3821, 3822, 3823, 3824, 3825, 3825, 3826, 3827, 3828, 3829, 3829,
    3830, 3831, 3832, 3833, 3833, 3834, 3835, 3836, 3836, 3837, 3838, 3839, 3840, 3840, 3841, 3842,
    3843, 3843, 3844, 3845, 3846, 3847, 3847, 3848, 3849, 3850, 3850, 3851, 3852, 3853, 3853, 3854,
    3855, 3856, 3856, 3857, 3858, 3859, 3859, 3860, 3861, 3862, 3862, 3863, 3864, 3865, 3865, 3866,
    3867, 3868, 3868, 3869, 3870, 3871, 3871, 3872, 3873, 3874, 3874, 3875, 3876, 3876, 3877, 3878,
    3879, 3879, 3880, 3881, 3881, 3882, 3883, 3884, 3884, 3885, 3886, 3886, 3887, 3888, 3889, 3889,
    3890, 3891, 3891, 3892, 3893, 3893, 3894, 3895, 3896, 3896, 3897, 3898, 3898, 3899, 3900, 3900,
    3901, 3902, 3902, 3903, 3904, 3904, 3905, 3906, 3907, 3907, 3908, 3909, 3909, 3910, 3911, 3911,
    3912, 3913, 3913, 3914, 3915, 3915, 3916, 3917, 3917, 3918, 3919, 3919, 3920, 3920, 3921, 3922,
    3922, 3923, 3924, 3924, 3925, 3926, 3926, 3927, 3928, 3928, 3929, 3929, 3930, 3931, 3931, 3932,
    3933, 3933, 3934, 3935, 3935, 3936, 3936, 3937, 3938, 3938, 3939, 3939, 3940, 3941, 3941, 3942,
    3943, 3943, 3944, 3944, 3945, 3946, 3946, 3947, 3947, 3948, 3949, 3949, 3950, 3950, 3951, 3952,
    3952, 3953, 3953, 3954, 3955, 3955, 3956, 3956, 3957, 3957, 3958, 3959, 3959, 3960, 3960, 3961,
    3962, 3962, 3963, 3963, 3964, 3964, 3965, 3965, 3966, 3967, 3967, 3968, 3968, 3969, 3969, 3970,
    3971, 3971, 3972, 3972, 3973, 3973, 3974, 3974, 3975, 3975, 3976, 3977, 3977, 3978, 3978, 3979,
    3979, 3980, 3980, 3981, 3981, 3982, 3982, 3983, 3983, 3984, 3985, 3985, 3986, 3986, 3987, 3987,
    3988, 3988, 3989, 3989, 3990, 3990, 3991, 3991, 3992, 3992, 3993, 3993, 3994, 3994, 3995, 3995,
    3996, 3996, 3997, 3997, 3998, 3998, 3999, 3999, 4000, 4000, 4001, 4001, 4002, 4002, 4003, 4003,
    4004, 4004, 4005, 4005, 4005, 4006, 4006, 4007, 4007, 4008, 4008, 4009, 4009, 4010, 4010, 4011,
    4011, 4012, 4012, 4012, 4013, 4013, 4014, 4014, 4015, 4015, 4016, 4016, 4016, 4017, 4017, 4018,
    4018, 4019, 4019, 4020, 4020, 4020, 4021, 4021, 4022, 4022, 4023, 4023, 4023, 4024, 4024, 4025,
    4025, 4026, 4026, 4026, 4027, 4027, 4028, 4028, 4028, 4029, 4029, 4030, 4030, 4030, 4031, 4031,
    4032, 4032, 4032, 4033, 4033, 4034, 4034, 4034, 4035, 4035, 4036, 4036, 4036, 4037, 4037, 4038,
    4038, 4038, 4039, 4039, 4039, 4040, 4040, 4041, 4041, 4041, 4042, 4042, 4042, 4043, 4043, 4043,
    4044, 4044, 4045, 4045, 4045, 4046, 4046, 4046, 4047, 4047, 4047, 4048, 4048, 4048, 4049, 4049,
    4049, 4050, 4050, 4050, 4051, 4051, 4051, 4052, 4052, 4052, 4053, 4053, 4053, 4054, 4054, 4054,
    4055, 4055, 4055, 4056, 4056, 4056, 4057, 4057, 4057, 4058, 4058, 4058, 4059, 4059, 4059, 4059,
    4060, 4060, 4060, 4061, 4061, 4061, 4062, 4062, 4062, 4062, 4063, 4063, 4063, 4064, 4064, 4064,
    4064, 4065, 4065, 4065, 4066, 4066, 4066, 4066, 4067, 4067, 4067, 4067, 4068, 4068, 4068, 4068,
    4069, 4069, 4069, 4070, 4070, 4070, 4070, 4071, 4071, 4071, 4071, 4072, 4072, 4072, 4072, 4073,
    4073, 4073, 4073, 4073, 4074, 4074, 4074, 4074, 4075, 4075, 4075, 4075, 4076, 4076, 4076, 4076,
    4076, 4077, 4077, 4077, 4077, 4078, 4078, 4078, 4078, 4078, 4079, 4079, 4079, 4079, 4079, 4080,
    4080, 4080, 4080, 4080, 4081, 4081, 4081, 4081, 4081, 4082, 4082, 4082, 4082, 4082, 4083, 4083,
    4083, 4083, 4083, 4083, 4084, 4084, 4084, 4084, 4084, 4084, 4085, 4085, 4085, 4085, 4085, 4085,
    4086, 4086, 4086, 4086, 4086, 4086, 4087, 4087, 4087, 4087, 4087, 4087, 4088, 4088, 4088, 4088,
    4088, 4088, 4088, 4088, 4089, 4089, 4089, 4089, 4089, 4089, 4089, 4090, 4090, 4090, 4090, 4090,
    4090, 4090, 4090, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4092, 4092, 4092, 4092,
    4092, 4092, 4092, 4092, 4092, 4092, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093,
    4093, 4093, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096,
    4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096,
    4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096,
    4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4093,
    4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4092, 4092, 4092, 4092, 4092,
    4092, 4092, 4092, 4092, 4092, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4090, 4090,
    4090, 4090, 4090, 4090, 4090, 4090, 4089, 4089, 4089, 4089, 4089, 4089, 4089, 4088, 4088, 4088,
    4088, 4088, 4088, 4088, 4088, 4087, 4087, 4087, 4087, 4087, 4087, 4086, 4086, 4086, 4086, 4086,
    4086, 4085, 4085, 4085, 4085, 4085, 4085, 4084, 4084, 4084, 4084, 4084, 4084, 4083, 4083, 4083,
    4083, 4083, 4083, 4082, 4082, 4082, 4082, 4082, 4081, 4081, 4081, 4081, 4081, 4080, 4080, 4080,
    4080, 4080, 4079, 4079, 4079, 4079, 4079, 4078, 4078, 4078, 4078, 4078, 4077, 4077, 4077, 4077,
    4076, 4076, 4076, 4076, 4076, 4075, 4075, 4075, 4075, 4074, 4074, 4074, 4074, 4073, 4073, 4073,
    4073, 4073, 4072, 4072, 4072, 4072, 4071, 4071, 4071, 4071, 4070, 4070, 4070, 4070, 4069, 4069,
    4069, 4068, 4068, 4068, 4068, 4067, 4067, 4067, 4067, 4066, 4066, 4066, 4066, 4065, 4065, 4065,
    4064, 4064, 4064, 4064, 4063, 4063, 4063, 4062, 4062, 4062, 4062, 4061, 4061, 4061, 4060, 4060,
    4060, 4059, 4059, 4059, 4059, 4058, 4058, 4058, 4057, 4057, 4057, 4056, 4056, 4056, 4055, 4055,
    4055, 4054, 4054, 4054, 4053, 4053, 4053, 4052, 4052, 4052, 4051, 4051, 4051, 4050, 4050, 4050,
    4049, 4049, 4049, 4048, 4048, 4048, 4047, 4047, 4047, 4046, 4046, 4046, 4045, 4045, 4045, 4044,
    4044, 4043, 4043, 4043, 4042, 4042, 4042, 4041, 4041, 4041, 4040, 4040, 4039, 4039, 4039, 4038,
    4038, 4038, 4037, 4037, 4036, 4036, 4036, 4035, 4035, 4034, 4034, 4034, 4033, 4033, 4032, 4032,
    4032, 4031, 4031, 4030, 4030, 4030, 4029, 4029, 4028, 4028, 4028, 4027, 4027, 4026, 4026, 4026,
    4025, 4025, 4024, 4024, 4023, 4023, 4023, 4022, 4022, 4021, 4021, 4020, 4020, 4020, 4019, 4019,
    4018, 4018, 4017, 4017, 4016, 4016, 4016, 4015, 4015, 4014, 4014, 4013, 4013, 4012, 4012, 4012,
    4011, 4011, 4010, 4010, 4009, 4009, 4008, 4008, 4007, 4007, 4006, 4006, 4005, 4005, 4005, 4004,
    4004, 4003, 4003, 4002, 4002, 4001, 4001, 4000, 4000, 3999, 3999, 3998, 3998, 3997, 3997, 3996,
    3996, 3995, 3995, 3994, 3994, 3993, 3993, 3992, 3992, 3991, 3991, 3990, 3990, 3989, 3989, 3988,
    3988, 3987, 3987, 3986, 3986, 3985, 3985, 3984, 3983, 3983, 3982, 3982, 3981, 3981, 3980, 3980,
    3979, 3979, 3978, 3978, 3977, 3977, 3976, 3975, 3975, 3974, 3974, 3973, 3973, 3972, 3972, 3971,
    3971, 3970, 3969, 3969, 3968, 3968, 3967, 3967, 3966, 3965, 3965, 3964, 3964, 3963, 3963, 3962,
    3962, 3961, 3960, 3960, 3959, 3959, 3958, 3957, 3957, 3956, 3956, 3955, 3955, 3954, 3953, 3953,
    3952, 3952, 3951, 3950, 3950, 3949, 3949, 3948, 3947, 3947, 3946, 3946, 3945, 3944, 3944, 3943,
    3943, 3942, 3941, 3941, 3940, 3939, 3939, 3938, 3938, 3937, 3936, 3936, 3935, 3935, 3934, 3933,
    3933, 3932, 3931, 3931, 3930, 3929, 3929, 3928, 3928, 3927, 3926, 3926, 3925, 3924, 3924, 3923,
    3922, 3922, 3921, 3920, 3920, 3919, 3919, 3918, 3917, 3917, 3916, 3915, 3915, 3914, 3913, 3913,
    3912, 3911, 3911, 3910, 3909, 3909, 3908, 3907, 3907, 3906, 3905, 3904, 3904, 3903, 3902, 3902,
    3901, 3900, 3900, 3899, 3898, 3898, 3897, 3896, 3896, 3895, 3894, 3893, 3893, 3892, 3891, 3891,
    3890, 3889, 3889, 3888, 3887, 3886, 3886, 3885, 3884, 3884, 3883, 3882, 3881, 3881, 3880, 3879,
    3879, 3878, 3877, 3876, 3876, 3875, 3874, 3874, 3873, 3872, 3871, 3871, 3870, 3869, 3868, 3868,
    3867, 3866, 3865, 3865, 3864, 3863, 3862, 3862, 3861, 3860, 3859, 3859, 3858, 3857, 3856, 3856,
    3855, 3854, 3853, 3853, 3852, 3851, 3850, 3850, 3849, 3848, 3847, 3847, 3846, 3845, 3844, 3843,
    3843, 3842, 3841, 3840, 3840, 3839, 3838, 3837, 3836, 3836, 3835, 3834, 3833, 3833, 3832, 3831,
    3830, 3829, 3829, 3828, 3827, 3826, 3825, 3825, 3824, 3823, 3822, 3821, 3821, 3820, 3819, 3818,
    3817, 3817, 3816, 3815, 3814, 3813, 3812, 3812, 3811, 3810, 3809, 3808, 3808, 3807, 3806, 3805,
    3804, 3803, 3803, 3802, 3801, 3800, 3799, 3798, 3798, 3797, 3796, 3795, 3794, 3793, 3793, 3792,
    3791, 3790, 3789, 3788, 3787, 3787, 3786, 3785, 3784, 3783, 3782, 3781, 3781, 3780, 3779, 3778,
    3777, 3776, 3775, 3775, 3774, 3773, 3772, 3771, 3770, 3769, 3769, 3768, 3767, 3766, 3765, 3764,
    3763, 3762, 3761, 3761, 3760, 3759, 3758, 3757, 3756, 3755, 3754, 3754, 3753, 3752, 3751, 3750,
    3749, 3748, 3747, 3746, 3745, 3745, 3744, 3743, 3742, 3741, 3740, 3739, 3738, 3737, 3736, 3736,
    3735, 3734, 3733, 3732, 3731, 3730, 3729, 3728, 3727, 3726, 3725, 3724, 3724, 3723, 3722, 3721,
    3720, 3719, 3718, 3717, 3716, 3715, 3714, 3713, 3712, 3711, 3711, 3710, 3709, 3708, 3707, 3706,
    3705, 3704, 3703, 3702, 3701, 3700, 3699, 3698, 3697, 3696, 3695, 3694, 3693, 3692, 3692, 3691,
    3690, 3689, 3688, 3687, 3686, 3685, 3684, 3683, 3682, 3681, 3680, 3679, 3678, 3677, 3676, 3675,
    3674, 3673, 3672, 3671, 3670, 3669, 3668, 3667, 3666, 3665, 3664, 3663, 3662, 3661, 3660, 3659,
    3658, 3657, 3656, 3655, 3654, 3653, 3652, 3651, 3650, 3649, 3648, 3647, 3646, 3645, 3644, 3643,
    3642, 3641, 3640, 3639, 3638, 3637, 3636, 3635, 3634, 3633, 3632, 3631, 3630, 3629, 3628, 3627,
    3626, 3625, 3624, 3623, 3622, 3621, 3620, 3619, 3618, 3617, 3616, 3615, 3614, 3613, 3612, 3611,
    3609, 3608, 3607, 3606, 3605, 3604, 3603, 3602, 3601, 3600, 3599, 3598, 3597, 3596, 3595, 3594,
    3593, 3592, 3591, 3590, 3588, 3587, 3586, 3585, 3584, 3583, 3582, 3581, 3580, 3579, 3578, 3577,
    3576, 3575, 3574, 3572, 3571, 3570, 3569, 3568, 3567, 3566, 3565, 3564, 3563, 3562, 3561, 3560,
    3558, 3557, 3556, 3555, 3554, 3553, 3552, 3551, 3550, 3549, 3548, 3546, 3545, 3544, 3543, 3542,
    3541, 3540, 3539, 3538, 3537, 3535, 3534, 3533, 3532, 3531, 3530, 3529, 3528, 3527, 3525, 3524,
    3523, 3522, 3521, 3520, 3519, 3518, 3516, 3515, 3514, 3513, 3512, 3511, 3510, 3509, 3507, 3506,
    3505, 3504, 3503, 3502, 3501, 3500, 3498, 3497, 3496, 3495, 3494, 3493, 3492, 3490, 3489, 3488,
    3487, 3486, 3485, 3484, 3482, 3481, 3480, 3479, 3478, 3477, 3476, 3474, 3473, 3472, 3471, 3470,
    3469, 3467, 3466, 3465, 3464, 3463, 3462, 3460, 3459, 3458, 3457, 3456, 3455, 3453, 3452, 3451,
    3450, 3449, 3448, 3446, 3445, 3444, 3443, 3442, 3441, 3439, 3438, 3437, 3436, 3435, 3433, 3432,
    3431, 3430, 3429, 3428, 3426, 3425, 3424, 3423, 3422, 3420, 3419, 3418, 3417, 3416, 3414, 3413,
    3412, 3411, 3410, 3408, 3407, 3406, 3405, 3404, 3402, 3401, 3400, 3399, 3398, 3396, 3395, 3394,
    3393, 3391, 3390, 3389, 3388, 3387, 3385, 3384, 3383, 3382, 3381, 3379, 3378, 3377, 3376, 3374,
    3373, 3372, 3371, 3369, 3368, 3367, 3366, 3365, 3363, 3362, 3361, 3360, 3358, 3357, 3356, 3355,
    3353, 3352, 3351, 3350, 3348, 3347, 3346, 3345, 3344, 3342, 3341, 3340, 3339, 3337, 3336, 3335,
    3334, 3332, 3331, 3330, 3328, 3327, 3326, 3325, 3323, 3322, 3321, 3320, 3318, 3317, 3316, 3315,
    3313, 3312, 3311, 3310, 3308, 3307, 3306, 3305, 3303, 3302, 3301, 3299, 3298, 3297, 3296, 3294,
    3293, 3292, 3290, 3289, 3288, 3287, 3285, 3284, 3283, 3282, 3280, 3279, 3278, 3276, 3275, 3274,
    3273, 3271, 3270, 3269, 3267, 3266, 3265, 3263, 3262, 3261, 3260, 3258, 3257, 3256, 3254, 3253,
    3252, 3250, 3249, 3248, 3247, 3245, 3244, 3243, 3241, 3240, 3239, 3237, 3236, 3235, 3233, 3232,
    3231, 3230, 3228, 3227, 3226, 3224, 3223, 3222, 3220, 3219, 3218, 3216, 3215, 3214, 3212, 3211,
    3210, 3208, 3207, 3206, 3204, 3203, 3202, 3200, 3199, 3198, 3196, 3195, 3194, 3192, 3191, 3190,
    3188, 3187, 3186, 3184, 3183, 3182, 3180, 3179, 3178, 3176, 3175, 3174, 3172, 3171, 3170, 3168,
    3167, 3166, 3164, 3163, 3162, 3160, 3159, 3158, 3156, 3155, 3154, 3152, 3151, 3149, 3148, 3147,
    3145, 3144, 3143, 3141, 3140, 3139, 3137, 3136, 3134, 3133, 3132, 3130, 3129, 3128, 3126, 3125,
    3124, 3122, 3121, 3119, 3118, 3117, 3115, 3114, 3113, 3111, 3110, 3108, 3107, 3106, 3104, 3103,
    3102, 3100, 3099, 3097, 3096, 3095, 3093, 3092, 3091, 3089, 3088, 3086, 3085, 3084, 3082, 3081,
    3079, 3078, 3077, 3075, 3074, 3072, 3071, 3070, 3068, 3067, 3065, 3064, 3063, 3061, 3060, 3059,
    3057, 3056, 3054, 3053, 3052, 3050, 3049, 3047, 3046, 3044, 3043, 3042, 3040, 3039, 3037, 3036,
    3035, 3033, 3032, 3030, 3029, 3028, 3026, 3025, 3023, 3022, 3021, 3019, 3018, 3016, 3015, 3013,
    3012, 3011, 3009, 3008, 3006, 3005, 3003, 3002, 3001, 2999, 2998, 2996, 2995, 2994, 2992, 2991,
    2989, 2988, 2986, 2985, 2984, 2982, 2981, 2979, 2978, 2976, 2975, 2973, 2972, 2971, 2969, 2968,
    2966, 2965, 2963, 2962, 2961, 2959, 2958, 2956, 2955, 2953, 2952, 2950, 2949, 2948, 2946, 2945,
    2943, 2942, 2940, 2939, 2937, 2936, 2935, 2933, 2932, 2930, 2929, 2927, 2926, 2924, 2923, 2921,
    2920, 2919, 2917, 2916, 2914, 2913, 2911, 2910, 2908, 2907, 2905, 2904, 2902, 2901, 2900, 2898,
    2897, 2895, 2894, 2892, 2891, 2889, 2888, 2886, 2885, 2883, 2882, 2881, 2879, 2878, 2876, 2875,
    2873, 2872, 2870, 2869, 2867, 2866, 2864, 2863, 2861, 2860, 2858, 2857, 2855, 2854, 2852, 2851,
    2850, 2848, 2847, 2845, 2844, 2842, 2841, 2839, 2838, 2836, 2835, 2833, 2832, 2830, 2829, 2827,
    2826, 2824, 2823, 2821, 2820, 2818, 2817, 2815, 2814, 2812, 2811, 2809, 2808, 2806, 2805, 2803,
    2802, 2800, 2799, 2797, 2796, 2794, 2793, 2791, 2790, 2788, 2787, 2785, 2784, 2782, 2781, 2779,
    2778, 2776, 2775, 2773, 2772, 2770, 2769, 2767, 2766, 2764, 2763, 2761, 2760, 2758, 2757, 2755,
    2754, 2752, 2751, 2749, 2748, 2746, 2745, 2743, 2742, 2740, 2739, 2737, 2736, 2734, 2733, 2731,
    2730, 2728, 2727, 2725, 2724, 2722, 2721, 2719, 2717, 2716, 2714, 2713, 2711, 2710, 2708, 2707,
    2705, 2704, 2702, 2701, 2699, 2698, 2696, 2695, 2693, 2692, 2690, 2689, 2687, 2685, 2684, 2682,
    2681, 2679, 2678, 2676, 2675, 2673, 2672, 2670, 2669, 2667, 2666, 2664, 2662, 2661, 2659, 2658,
    2656, 2655, 2653, 2652, 2650, 2649, 2647, 2646, 2644, 2643, 2641, 2639, 2638, 2636, 2635, 2633,
    2632, 2630, 2629, 2627, 2626, 2624, 2622, 2621, 2619, 2618, 2616, 2615, 2613, 2612, 2610, 2609,
    2607, 2605, 2604, 2602, 2601, 2599, 2598, 2596, 2595, 2593, 2592, 2590, 2588, 2587, 2585, 2584,
    2582, 2581, 2579, 2578, 2576, 2574, 2573, 2571, 2570, 2568, 2567, 2565, 2564, 2562, 2560, 2559,
    2557, 2556, 2554, 2553, 2551, 2550, 2548, 2546, 2545, 2543, 2542, 2540, 2539, 2537, 2535, 2534,
    2532, 2531, 2529, 2528, 2526, 2525, 2523, 2521, 2520, 2518, 2517, 2515, 2514, 2512, 2510, 2509,
    2507, 2506, 2504, 2503, 2501, 2499, 2498, 2496, 2495, 2493, 2492, 2490, 2488, 2487, 2485, 2484,
    2482, 2481, 2479, 2477, 2476, 2474, 2473, 2471, 2470, 2468, 2466, 2465, 2463, 2462, 2460, 2459,
    2457, 2455, 2454, 2452, 2451, 2449, 2448, 2446, 2444, 2443, 2441, 2440, 2438, 2436, 2435, 2433,
    2432, 2430, 2429, 2427, 2425, 2424, 2422, 2421, 2419, 2418, 2416, 2414, 2413, 2411, 2410, 2408,
    2406, 2405, 2403, 2402, 2400, 2399, 2397, 2395, 2394, 2392, 2391, 2389, 2387, 2386, 2384, 2383,
    2381, 2379, 2378, 2376, 2375, 2373, 2372, 2370, 2368, 2367, 2365, 2364, 2362, 2360, 2359, 2357,
    2356, 2354, 2352, 2351, 2349, 2348, 2346, 2345, 2343, 2341, 2340, 2338, 2337, 2335, 2333, 2332,
    2330, 2329, 2327, 2325, 2324, 2322, 2321, 2319, 2317, 2316, 2314, 2313, 2311, 2309, 2308, 2306,
    2305, 2303, 2301, 2300, 2298, 2297, 2295, 2294, 2292, 2290, 2289, 2287, 2286, 2284, 2282, 2281,
    2279, 2278, 2276, 2274, 2273, 2271, 2270, 2268, 2266, 2265, 2263, 2262, 2260, 2258, 2257, 2255,
    2254, 2252, 2250, 2249, 2247, 2246, 2244, 2242, 2241, 2239, 2238, 2236, 2234, 2233, 2231, 2230,
    2228, 2226, 2225, 2223, 2222, 2220, 2218, 2217, 2215, 2213, 2212, 2210, 2209, 2207, 2205, 2204,
    2202, 2201, 2199, 2197, 2196, 2194, 2193, 2191, 2189, 2188, 2186, 2185, 2183, 2181, 2180, 2178,
    2177, 2175, 2173, 2172, 2170, 2169, 2167, 2165, 2164, 2162, 2161, 2159, 2157, 2156, 2154, 2153,
    2151, 2149, 2148, 2146, 2144, 2143, 2141, 2140, 2138, 2136, 2135, 2133, 2132, 2130, 2128, 2127,
    2125, 2124, 2122, 2120, 2119, 2117, 2116, 2114, 2112, 2111, 2109, 2108, 2106, 2104, 2103, 2101,
    2099, 2098, 2096, 2095, 2093, 2091, 2090, 2088, 2087, 2085, 2083, 2082, 2080, 2079, 2077, 2075,
    2074, 2072, 2071, 2069, 2067, 2066, 2064, 2062, 2061, 2059, 2058, 2056, 2054, 2053, 2051, 2050,
    2048, 2046, 2045, 2043, 2042, 2040, 2038, 2037, 2035, 2034, 2032, 2030, 2029, 2027, 2025, 2024,
    2022, 2021, 2019, 2017, 2016, 2014, 2013, 2011, 2009, 2008, 2006, 2005, 2003, 2001, 2000, 1998,
    1997, 1995, 1993, 1992, 1990, 1988, 1987, 1985, 1984, 1982, 1980, 1979, 1977, 1976, 1974, 1972,
    1971, 1969, 1968, 1966, 1964, 1963, 1961, 1960, 1958, 1956, 1955, 1953, 1952, 1950, 1948, 1947,
    1945, 1943, 1942, 1940, 1939, 1937, 1935, 1934, 1932, 1931, 1929, 1927, 1926, 1924, 1923, 1921,
    1919, 1918, 1916, 1915, 1913, 1911, 1910, 1908, 1907, 1905, 1903, 1902, 1900, 1899, 1897, 1895,
    1894, 1892, 1891, 1889, 1887, 1886, 1884, 1883, 1881, 1879, 1878, 1876, 1874, 1873, 1871, 1870,
    1868, 1866, 1865, 1863, 1862, 1860, 1858, 1857, 1855, 1854, 1852, 1850, 1849, 1847, 1846, 1844,
    1842, 1841, 1839, 1838, 1836, 1834, 1833, 1831, 1830, 1828, 1826, 1825, 1823, 1822, 1820, 1818,
    1817, 1815, 1814, 1812, 1810, 1809, 1807, 1806, 1804, 1802, 1801, 1799, 1798, 1796, 1795, 1793,
    1791, 1790, 1788, 1787, 1785, 1783, 1782, 1780, 1779, 1777, 1775, 1774, 1772, 1771, 1769, 1767,
    1766, 1764, 1763, 1761, 1759, 1758, 1756, 1755, 1753, 1751, 1750, 1748, 1747, 1745, 1744, 1742,
    1740, 1739, 1737, 1736, 1734, 1732, 1731, 1729, 1728, 1726, 1724, 1723, 1721, 1720, 1718, 1717,
    1715, 1713, 1712, 1710, 1709, 1707, 1705, 1704, 1702, 1701, 1699, 1697, 1696, 1694, 1693, 1691,
    1690, 1688, 1686, 1685, 1683, 1682, 1680, 1678, 1677, 1675, 1674, 1672, 1671, 1669, 1667, 1666,
    1664, 1663, 1661, 1660, 1658, 1656, 1655, 1653, 1652, 1650, 1648, 1647, 1645, 1644, 1642, 1641,
    1639, 1637, 1636, 1634, 1633, 1631, 1630, 1628, 1626, 1625, 1623, 1622, 1620, 1619, 1617, 1615,
    1614, 1612, 1611, 1609, 1608, 1606, 1604, 1603, 1601, 1600, 1598, 1597, 1595, 1593, 1592, 1590,
    1589, 1587, 1586, 1584, 1582, 1581, 1579, 1578, 1576, 1575, 1573, 1571, 1570, 1568, 1567, 1565,
    1564, 1562, 1561, 1559, 1557, 1556, 1554, 1553, 1551, 1550, 1548, 1546, 1545, 1543, 1542, 1540,
    1539, 1537, 1536, 1534, 1532, 1531, 1529, 1528, 1526, 1525, 1523, 1522, 1520, 1518, 1517, 1515,
    1514, 1512, 1511, 1509, 1508, 1506, 1504, 1503, 1501, 1500, 1498, 1497, 1495, 1494, 1492, 1491,
    1489, 1487, 1486, 1484, 1483, 1481, 1480, 1478, 1477, 1475, 1474, 1472, 1470, 1469, 1467, 1466,
    1464, 1463, 1461, 1460, 1458, 1457, 1455, 1453, 1452, 1450, 1449, 1447, 1446, 1444, 1443, 1441,
    1440, 1438, 1437, 1435, 1434, 1432, 1430, 1429, 1427, 1426, 1424, 1423, 1421, 1420, 1418, 1417,
    1415, 1414, 1412, 1411, 1409, 1407, 1406, 1404, 1403, 1401, 1400, 1398, 1397, 1395, 1394, 1392,
    1391, 1389, 1388, 1386, 1385, 1383, 1382, 1380, 1379, 1377, 1375, 1374, 1372, 1371, 1369, 1368,
    1366, 1365, 1363, 1362, 1360, 1359, 1357, 1356, 1354, 1353, 1351, 1350, 1348, 1347, 1345, 1344,
    1342, 1341, 1339, 1338, 1336, 1335, 1333, 1332, 1330, 1329, 1327, 1326, 1324, 1323, 1321, 1320,
    1318, 1317, 1315, 1314, 1312, 1311, 1309, 1308, 1306, 1305, 1303, 1302, 1300, 1299, 1297, 1296,
    1294, 1293, 1291, 1290, 1288, 1287, 1285, 1284, 1282, 1281, 1279, 1278, 1276, 1275, 1273, 1272,
    1270, 1269, 1267, 1266, 1264, 1263, 1261, 1260, 1258, 1257, 1255, 1254, 1252, 1251, 1249, 1248,
    1246, 1245, 1244, 1242, 1241, 1239, 1238, 1236, 1235, 1233, 1232, 1230, 1229, 1227, 1226, 1224,
    1223, 1221, 1220, 1218, 1217, 1215, 1214, 1213, 1211, 1210, 1208, 1207, 1205, 1204, 1202, 1201,
    1199, 1198, 1196, 1195, 1194, 1192, 1191, 1189, 1188, 1186, 1185, 1183, 1182, 1180, 1179, 1177,
    1176, 1175, 1173, 1172, 1170, 1169, 1167, 1166, 1164, 1163, 1161, 1160, 1159, 1157, 1156, 1154,
    1153, 1151, 1150, 1148, 1147, 1146, 1144, 1143, 1141, 1140, 1138, 1137, 1135, 1134, 1133, 1131,
    1130, 1128, 1127, 1125, 1124, 1123, 1121, 1120, 1118, 1117, 1115, 1114, 1112, 1111, 1110, 1108,
    1107, 1105, 1104, 1102, 1101, 1100, 1098, 1097, 1095, 1094, 1093, 1091, 1090, 1088, 1087, 1085,
    1084, 1083, 1081, 1080, 1078, 1077, 1075, 1074, 1073, 1071, 1070, 1068, 1067, 1066, 1064, 1063,
    1061, 1060, 1059, 1057, 1056, 1054, 1053, 1052, 1050, 1049, 1047, 1046, 1044, 1043, 1042, 1040,
    1039, 1037, 1036, 1035, 1033, 1032, 1031, 1029, 1028, 1026, 1025, 1024, 1022, 1021, 1019, 1018,
    1017, 1015, 1014, 1012, 1011, 1010, 1008, 1007, 1005, 1004, 1003, 1001, 1000, 999,  997,  996,
    994,  993,  992,  990,  989,  988,  986,  985,  983,  982,  981,  979,  978,  977,  975,  974,
    972,  971,  970,  968,  967,  966,  964,  963,  962,  960,  959,  957,  956,  955,  953,  952,
    951,  949,  948,  947,  945,  944,  942,  941,  940,  938,  937,  936,  934,  933,  932,  930,
    929,  928,  926,  925,  924,  922,  921,  920,  918,  917,  916,  914,  913,  912,  910,  909,
    908,  906,  905,  904,  902,  901,  900,  898,  897,  896,  894,  893,  892,  890,  889,  888,
    886,  885,  884,  882,  881,  880,  878,  877,  876,  874,  873,  872,  870,  869,  868,  866,
    865,  864,  863,  861,  860,  859,  857,  856,  855,  853,  852,  851,  849,  848,  847,  846,
    844,  843,  842,  840,  839,  838,  836,  835,  834,  833,  831,  830,  829,  827,  826,  825,
    823,  822,  821,  820,  818,  817,  816,  814,  813,  812,  811,  809,  808,  807,  806,  804,
    803,  802,  800,  799,  798,  797,  795,  794,  793,  791,  790,  789,  788,  786,  785,  784,
    783,  781,  780,  779,  778,  776,  775,  774,  773,  771,  770,  769,  768,  766,  765,  764,
    762,  761,  760,  759,  757,  756,  755,  754,  752,  751,  750,  749,  748,  746,  745,  744,
    743,  741,  740,  739,  738,  736,  735,  734,  733,  731,  730,  729,  728,  727,  725,  724,
    723,  722,  720,  719,  718,  717,  715,  714,  713,  712,  711,  709,  708,  707,  706,  705,
    703,  702,  701,  700,  698,  697,  696,  695,  694,  692,  691,  690,  689,  688,  686,  685,
    684,  683,  682,  680,  679,  678,  677,  676,  674,  673,  672,  671,  670,  668,  667,  666,
    665,  664,  663,  661,  660,  659,  658,  657,  655,  654,  653,  652,  651,  650,  648,  647,
    646,  645,  644,  643,  641,  640,  639,  638,  637,  636,  634,  633,  632,  631,  630,  629,
    627,  626,  625,  624,  623,  622,  620,  619,  618,  617,  616,  615,  614,  612,  611,  610,
    609,  608,  607,  606,  604,  603,  602,  601,  600,  599,  598,  596,  595,  594,  593,  592,
    591,  590,  589,  587,  586,  585,  584,  583,  582,  581,  580,  578,  577,  576,  575,  574,
    573,  572,  571,  569,  568,  567,  566,  565,  564,  563,  562,  561,  559,  558,  557,  556,
    555,  554,  553,  552,  551,  550,  548,  547,  546,  545,  544,  543,  542,  541,  540,  539,
    538,  536,  535,  534,  533,  532,  531,  530,  529,  528,  527,  526,  525,  524,  522,  521,
    520,  519,  518,  517,  516,  515,  514,  513,  512,  511,  510,  509,  508,  506,  505,  504,
    503,  502,  501,  500,  499,  498,  497,  496,  495,  494,  493,  492,  491,  490,  489,  488,
    487,  485,  484,  483,  482,  481,  480,  479,  478,  477,  476,  475,  474,  473,  472,  471,
    470,  469,  468,  467,  466,  465,  464,  463,  462,  461,  460,  459,  458,  457,  456,  455,
    454,  453,  452,  451,  450,  449,  448,  447,  446,  445,  444,  443,  442,  441,  440,  439,
    438,  437,  436,  435,  434,  433,  432,  431,  430,  429,  428,  427,  426,  425,  424,  423,
    422,  421,  420,  419,  418,  417,  416,  415,  414,  413,  412,  411,  410,  409,  408,  407,
    406,  405,  404,  404,  403,  402,  401,  400,  399,  398,  397,  396,  395,  394,  393,  392,
    391,  390,  389,  388,  387,  386,  385,  385,  384,  383,  382,  381,  380,  379,  378,  377,
    376,  375,  374,  373,  372,  372,  371,  370,  369,  368,  367,  366,  365,  364,  363,  362,
    361,  360,  360,  359,  358,  357,  356,  355,  354,  353,  352,  351,  351,  350,  349,  348,
    347,  346,  345,  344,  343,  342,  342,  341,  340,  339,  338,  337,  336,  335,  335,  334,
    333,  332,  331,  330,  329,  328,  327,  327,  326,  325,  324,  323,  322,  321,  321,  320,
    319,  318,  317,  316,  315,  315,  314,  313,  312,  311,  310,  309,  309,  308,  307,  306,
    305,  304,  303,  303,  302,  301,  300,  299,  298,  298,  297,  296,  295,  294,  293,  293,
    292,  291,  290,  289,  288,  288,  287,  286,  285,  284,  284,  283,  282,  281,  280,  279,
    279,  278,  277,  276,  275,  275,  274,  273,  272,  271,  271,  270,  269,  268,  267,  267,
    266,  265,  264,  263,  263,  262,  261,  260,  260,  259,  258,  257,  256,  256,  255,  254,
    253,  253,  252,  251,  250,  249,  249,  248,  247,  246,  246,  245,  244,  243,  243,  242,
    241,  240,  240,  239,  238,  237,  237,  236,  235,  234,  234,  233,  232,  231,  231,  230,
    229,  228,  228,  227,  226,  225,  225,  224,  223,  222,  222,  221,  220,  220,  219,  218,
    217,  217,  216,  215,  215,  214,  213,  212,  212,  211,  210,  210,  209,  208,  207,  207,
    206,  205,  205,  204,  203,  203,  202,  201,  200,  200,  199,  198,  198,  197,  196,  196,
    195,  194,  194,  193,  192,  192,  191,  190,  189,  189,  188,  187,  187,  186,  185,  185,
    184,  183,  183,  182,  181,  181,  180,  179,  179,  178,  177,  177,  176,  176,  175,  174,
    174,  173,  172,  172,  171,  170,  170,  169,  168,  168,  167,  167,  166,  165,  165,  164,
    163,  163,  162,  161,  161,  160,  160,  159,  158,  158,  157,  157,  156,  155,  155,  154,
    153,  153,  152,  152,  151,  150,  150,  149,  149,  148,  147,  147,  146,  146,  145,  144,
    144,  143,  143,  142,  141,  141,  140,  140,  139,  139,  138,  137,  137,  136,  136,  135,
    134,  134,  133,  133,  132,  132,  131,  131,  130,  129,  129,  128,  128,  127,  127,  126,
    125,  125,  124,  124,  123,  123,  122,  122,  121,  121,  120,  119,  119,  118,  118,  117,
    117,  116,  116,  115,  115,  114,  114,  113,  113,  112,  111,  111,  110,  110,  109,  109,
    108,  108,  107,  107,  106,  106,  105,  105,  104,  104,  103,  103,  102,  102,  101,  101,
    100,  100,  99,   99,   98,   98,   97,   97,   96,   96,   95,   95,   94,   94,   93,   93,
    92,   92,   91,   91,   91,   90,   90,   89,   89,   88,   88,   87,   87,   86,   86,   85,
    85,   84,   84,   84,   83,   83,   82,   82,   81,   81,   80,   80,   80,   79,   79,   78,
    78,   77,   77,   76,   76,   76,   75,   75,   74,   74,   73,   73,   73,   72,   72,   71,
    71,   70,   70,   70,   69,   69,   68,   68,   68,   67,   67,   66,   66,   66,   65,   65,
    64,   64,   64,   63,   63,   62,   62,   62,   61,   61,   60,   60,   60,   59,   59,   58,
    58,   58,   57,   57,   57,   56,   56,   55,   55,   55,   54,   54,   54,   53,   53,   53,
    52,   52,   51,   51,   51,   50,   50,   50,   49,   49,   49,   48,   48,   48,   47,   47,
    47,   46,   46,   46,   45,   45,   45,   44,   44,   44,   43,   43,   43,   42,   42,   42,
    41,   41,   41,   40,   40,   40,   39,   39,   39,   38,   38,   38,   37,   37,   37,   37,
    36,   36,   36,   35,   35,   35,   34,   34,   34,   34,   33,   33,   33,   32,   32,   32,
    32,   31,   31,   31,   30,   30,   30,   30,   29,   29,   29,   29,   28,   28,   28,   28,
    27,   27,   27,   26,   26,   26,   26,   25,   25,   25,   25,   24,   24,   24,   24,   23,
    23,   23,   23,   23,   22,   22,   22,   22,   21,   21,   21,   21,   20,   20,   20,   20,
    20,   19,   19,   19,   19,   18,   18,   18,   18,   18,   17,   17,   17,   17,   17,   16,
    16,   16,   16,   16,   15,   15,   15,   15,   15,   14,   14,   14,   14,   14,   13,   13,
    13,   13,   13,   13,   12,   12,   12,   12,   12,   12,   11,   11,   11,   11,   11,   11,
    10,   10,   10,   10,   10,   10,   9,    9,    9,    9,    9,    9,    8,    8,    8,    8,
    8,    8,    8,    8,    7,    7,    7,    7,    7,    7,    7,    6,    6,    6,    6,    6,
    6,    6,    6,    5,    5,    5,    5,    5,    5,    5,    5,    5,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    5,    5,    5,    5,    5,    5,    5,    5,    5,    6,    6,
    6,    6,    6,    6,    6,    6,    7,    7,    7,    7,    7,    7,    7,    8,    8,    8,
    8,    8,    8,    8,    8,    9,    9,    9,    9,    9,    9,    10,   10,   10,   10,   10,
    10,   11,   11,   11,   11,   11,   11,   12,   12,   12,   12,   12,   12,   13,   13,   13,
    13,   13,   13,   14,   14,   14,   14,   14,   15,   15,   15,   15,   15,   16,   16,   16,
    16,   16,   17,   17,   17,   17,   17,   18,   18,   18,   18,   18,   19,   19,   19,   19,
    20,   20,   20,   20,   20,   21,   21,   21,   21,   22,   22,   22,   22,   23,   23,   23,
    23,   23,   24,   24,   24,   24,   25,   25,   25,   25,   26,   26,   26,   26,   27,   27,
    27,   28,   28,   28,   28,   29,   29,   29,   29,   30,   30,   30,   30,   31,   31,   31,
    32,   32,   32,   32,   33,   33,   33,   34,   34,   34,   34,   35,   35,   35,   36,   36,
    36,   37,   37,   37,   37,   38,   38,   38,   39,   39,   39,   40,   40,   40,   41,   41,
    41,   42,   42,   42,   43,   43,   43,   44,   44,   44,   45,   45,   45,   46,   46,   46,
    47,   47,   47,   48,   48,   48,   49,   49,   49,   50,   50,   50,   51,   51,   51,   52,
    52,   53,   53,   53,   54,   54,   54,   55,   55,   55,   56,   56,   57,   57,   57,   58,
    58,   58,   59,   59,   60,   60,   60,   61,   61,   62,   62,   62,   63,   63,   64,   64,
    64,   65,   65,   66,   66,   66,   67,   67,   68,   68,   68,   69,   69,   70,   70,   70,
    71,   71,   72,   72,   73,   73,   73,   74,   74,   75,   75,   76,   76,   76,   77,   77,
    78,   78,   79,   79,   80,   80,   80,   81,   81,   82,   82,   83,   83,   84,   84,   84,
    85,   85,   86,   86,   87,   87,   88,   88,   89,   89,   90,   90,   91,   91,   91,   92,
    92,   93,   93,   94,   94,   95,   95,   96,   96,   97,   97,   98,   98,   99,   99,   100,
    100,  101,  101,  102,  102,  103,  103,  104,  104,  105,  105,  106,  106,  107,  107,  108,
    108,  109,  109,  110,  110,  111,  111,  112,  113,  113,  114,  114,  115,  115,  116,  116,
    117,  117,  118,  118,  119,  119,  120,  121,  121,  122,  122,  123,  123,  124,  124,  125,
    125,  126,  127,  127,  128,  128,  129,  129,  130,  131,  131,  132,  132,  133,  133,  134,
    134,  135,  136,  136,  137,  137,  138,  139,  139,  140,  140,  141,  141,  142,  143,  143,
    144,  144,  145,  146,  146,  147,  147,  148,  149,  149,  150,  150,  151,  152,  152,  153,
    153,  154,  155,  155,  156,  157,  157,  158,  158,  159,  160,  160,  161,  161,  162,  163,
    163,  164,  165,  165,  166,  167,  167,  168,  168,  169,  170,  170,  171,  172,  172,  173,
    174,  174,  175,  176,  176,  177,  177,  178,  179,  179,  180,  181,  181,  182,  183,  183,
    184,  185,  185,  186,  187,  187,  188,  189,  189,  190,  191,  192,  192,  193,  194,  194,
    195,  196,  196,  197,  198,  198,  199,  200,  200,  201,  202,  203,  203,  204,  205,  205,
    206,  207,  207,  208,  209,  210,  210,  211,  212,  212,  213,  214,  215,  215,  216,  217,
    217,  218,  219,  220,  220,  221,  222,  222,  223,  224,  225,  225,  226,  227,  228,  228,
    229,  230,  231,  231,  232,  233,  234,  234,  235,  236,  237,  237,  238,  239,  240,  240,
    241,  242,  243,  243,  244,  245,  246,  246,  247,  248,  249,  249,  250,  251,  252,  253,
    253,  254,  255,  256,  256,  257,  258,  259,  260,  260,  261,  262,  263,  263,  264,  265,
    266,  267,  267,  268,  269,  270,  271,  271,  272,  273,  274,  275,  275,  276,  277,  278,
    279,  279,  280,  281,  282,  283,  284,  284,  285,  286,  287,  288,  288,  289,  290,  291,
    292,  293,  293,  294,  295,  296,  297,  298,  298,  299,  300,  301,  302,  303,  303,  304,
    305,  306,  307,  308,  309,  309,  310,  311,  312,  313,  314,  315,  315,  316,  317,  318,
    319,  320,  321,  321,  322,  323,  324,  325,  326,  327,  327,  328,  329,  330,  331,  332,
    333,  334,  335,  335,  336,  337,  338,  339,  340,  341,  342,  342,  343,  344,  345,  346,
    347,  348,  349,  350,  351,  351,  352,  353,  354,  355,  356,  357,  358,  359,  360,  360,
    361,  362,  363,  364,  365,  366,  367,  368,  369,  370,  371,  372,  372,  373,  374,  375,
    376,  377,  378,  379,  380,  381,  382,  383,  384,  385,  385,  386,  387,  388,  389,  390,
    391,  392,  393,  394,  395,  396,  397,  398,  399,  400,  401,  402,  403,  404,  404,  405,
    406,  407,  408,  409,  410,  411,  412,  413,  414,  415,  416,  417,  418,  419,  420,  421,
    422,  423,  424,  425,  426,  427,  428,  429,  430,  431,  432,  433,  434,  435,  436,  437,
    438,  439,  440,  441,  442,  443,  444,  445,  446,  447,  448,  449,  450,  451,  452,  453,
    454,  455,  456,  457,  458,  459,  460,  461,  462,  463,  464,  465,  466,  467,  468,  469,
    470,  471,  472,  473,  474,  475,  476,  477,  478,  479,  480,  481,  482,  483,  484,  485,
    487,  488,  489,  490,  491,  492,  493,  494,  495,  496,  497,  498,  499,  500,  501,  502,
    503,  504,  505,  506,  508,  509,  510,  511,  512,  513,  514,  515,  516,  517,  518,  519,
    520,  521,  522,  524,  525,  526,  527,  528,  529,  530,  531,  532,  533,  534,  535,  536,
    538,  539,  540,  541,  542,  543,  544,  545,  546,  547,  548,  550,  551,  552,  553,  554,
    555,  556,  557,  558,  559,  561,  562,  563,  564,  565,  566,  567,  568,  569,  571,  572,
    573,  574,  575,  576,  577,  578,  580,  581,  582,  583,  584,  585,  586,  587,  589,  590,
    591,  592,  593,  594,  595,  596,  598,  599,  600,  601,  602,  603,  604,  606,  607,  608,
    609,  610,  611,  612,  614,  615,  616,  617,  618,  619,  620,  622,  623,  624,  625,  626,
    627,  629,  630,  631,  632,  633,  634,  636,  637,  638,  639,  640,  641,  643,  644,  645,
    646,  647,  648,  650,  651,  652,  653,  654,  655,  657,  658,  659,  660,  661,  663,  664,
    665,  666,  667,  668,  670,  671,  672,  673,  674,  676,  677,  678,  679,  680,  682,  683,
    684,  685,  686,  688,  689,  690,  691,  692,  694,  695,  696,  697,  698,  700,  701,  702,
    703,  705,  706,  707,  708,  709,  711,  712,  713,  714,  715,  717,  718,  719,  720,  722,
    723,  724,  725,  727,  728,  729,  730,  731,  733,  734,  735,  736,  738,  739,  740,  741,
    743,  744,  745,  746,  748,  749,  750,  751,  752,  754,  755,  756,  757,  759,  760,  761,
    762,  764,  765,  766,  768,  769,  770,  771,  773,  774,  775,  776,  778,  779,  780,  781,
    783,  784,  785,  786,  788,  789,  790,  791,  793,  794,  795,  797,  798,  799,  800,  802,
    803,  804,  806,  807,  808,  809,  811,  812,  813,  814,  816,  817,  818,  820,  821,  822,
    823,  825,  826,  827,  829,  830,  831,  833,  834,  835,  836,  838,  839,  840,  842,  843,
    844,  846,  847,  848,  849,  851,  852,  853,  855,  856,  857,  859,  860,  861,  863,  864,
    865,  866,  868,  869,  870,  872,  873,  874,  876,  877,  878,  880,  881,  882,  884,  885,
    886,  888,  889,  890,  892,  893,  894,  896,  897,  898,  900,  901,  902,  904,  905,  906,
    908,  909,  910,  912,  913,  914,  916,  917,  918,  920,  921,  922,  924,  925,  926,  928,
    929,  930,  932,  933,  934,  936,  937,  938,  940,  941,  942,  944,  945,  947,  948,  949,
    951,  952,  953,  955,  956,  957,  959,  960,  962,  963,  964,  966,  967,  968,  970,  971,
    972,  974,  975,  977,  978,  979,  981,  982,  983,  985,  986,  988,  989,  990,  992,  993,
    994,  996,  997,  999,  1000, 1001, 1003, 1004, 1005, 1007, 1008, 1010, 1011, 1012, 1014, 1015,
    1017, 1018, 1019, 1021, 1022, 1024, 1025, 1026, 1028, 1029, 1031, 1032, 1033, 1035, 1036, 1037,
    1039, 1040, 1042, 1043, 1044, 1046, 1047, 1049, 1050, 1052, 1053, 1054, 1056, 1057, 1059, 1060,
    1061, 1063, 1064, 1066, 1067, 1068, 1070, 1071, 1073, 1074, 1075, 1077, 1078, 1080, 1081, 1083,
    1084, 1085, 1087, 1088, 1090, 1091, 1093, 1094, 1095, 1097, 1098, 1100, 1101, 1102, 1104, 1105,
    1107, 1108, 1110, 1111, 1112, 1114, 1115, 1117, 1118, 1120, 1121, 1123, 1124, 1125, 1127, 1128,
    1130, 1131, 1133, 1134, 1135, 1137, 1138, 1140, 1141, 1143, 1144, 1146, 1147, 1148, 1150, 1151,
    1153, 1154, 1156, 1157, 1159, 1160, 1161, 1163, 1164, 1166, 1167, 1169, 1170, 1172, 1173, 1175,
    1176, 1177, 1179, 1180, 1182, 1183, 1185, 1186, 1188, 1189, 1191, 1192, 1194, 1195, 1196, 1198,
    1199, 1201, 1202, 1204, 1205, 1207, 1208, 1210, 1211, 1213, 1214, 1215, 1217, 1218, 1220, 1221,
    1223, 1224, 1226, 1227, 1229, 1230, 1232, 1233, 1235, 1236, 1238, 1239, 1241, 1242, 1244, 1245,
    1246, 1248, 1249, 1251, 1252, 1254, 1255, 1257, 1258, 1260, 1261, 1263, 1264, 1266, 1267, 1269,
    1270, 1272, 1273, 1275, 1276, 1278, 1279, 1281, 1282, 1284, 1285, 1287, 1288, 1290, 1291, 1293,
    1294, 1296, 1297, 1299, 1300, 1302, 1303, 1305, 1306, 1308, 1309, 1311, 1312, 1314, 1315, 1317,
    1318, 1320, 1321, 1323, 1324, 1326, 1327, 1329, 1330, 1332, 1333, 1335, 1336, 1338, 1339, 1341,
    1342, 1344, 1345, 1347, 1348, 1350, 1351, 1353, 1354, 1356, 1357, 1359, 1360, 1362, 1363, 1365,
    1366, 1368, 1369, 1371, 1372, 1374, 1375, 1377, 1379, 1380, 1382, 1383, 1385, 1386, 1388, 1389,
    1391, 1392, 1394, 1395, 1397, 1398, 1400, 1401, 1403, 1404, 1406, 1407, 1409, 1411, 1412, 1414,
    1415, 1417, 1418, 1420, 1421, 1423, 1424, 1426, 1427, 1429, 1430, 1432, 1434, 1435, 1437, 1438,
    1440, 1441, 1443, 1444, 1446, 1447, 1449, 1450, 1452, 1453, 1455, 1457, 1458, 1460, 1461, 1463,
    1464, 1466, 1467, 1469, 1470, 1472, 1474, 1475, 1477, 1478, 1480, 1481, 1483, 1484, 1486, 1487,
    1489, 1491, 1492, 1494, 1495, 1497, 1498, 1500, 1501, 1503, 1504, 1506, 1508, 1509, 1511, 1512,
    1514, 1515, 1517, 1518, 1520, 1522, 1523, 1525, 1526, 1528, 1529, 1531, 1532, 1534, 1536, 1537,
    1539, 1540, 1542, 1543, 1545, 1546, 1548, 1550, 1551, 1553, 1554, 1556, 1557, 1559, 1561, 1562,
    1564, 1565, 1567, 1568, 1570, 1571, 1573, 1575, 1576, 1578, 1579, 1581, 1582, 1584, 1586, 1587,
    1589, 1590, 1592, 1593, 1595, 1597, 1598, 1600, 1601, 1603, 1604, 1606, 1608, 1609, 1611, 1612,
    1614, 1615, 1617, 1619, 1620, 1622, 1623, 1625, 1626, 1628, 1630, 1631, 1633, 1634, 1636, 1637,
    1639, 1641, 1642, 1644, 1645, 1647, 1648, 1650, 1652, 1653, 1655, 1656, 1658, 1660, 1661, 1663,
    1664, 1666, 1667, 1669, 1671, 1672, 1674, 1675, 1677, 1678, 1680, 1682, 1683, 1685, 1686, 1688,
    1690, 1691, 1693, 1694, 1696, 1697, 1699, 1701, 1702, 1704, 1705, 1707, 1709, 1710, 1712, 1713,
    1715, 1717, 1718, 1720, 1721, 1723, 1724, 1726, 1728, 1729, 1731, 1732, 1734, 1736, 1737, 1739,
    1740, 1742, 1744, 1745, 1747, 1748, 1750, 1751, 1753, 1755, 1756, 1758, 1759, 1761, 1763, 1764,
    1766, 1767, 1769, 1771, 1772, 1774, 1775, 1777, 1779, 1780, 1782, 1783, 1785, 1787, 1788, 1790,
    1791, 1793, 1795, 1796, 1798, 1799, 1801, 1802, 1804, 1806, 1807, 1809, 1810, 1812, 1814, 1815,
    1817, 1818, 1820, 1822, 1823, 1825, 1826, 1828, 1830, 1831, 1833, 1834, 1836, 1838, 1839, 1841,
    1842, 1844, 1846, 1847, 1849, 1850, 1852, 1854, 1855, 1857, 1858, 1860, 1862, 1863, 1865, 1866,
    1868, 1870, 1871, 1873, 1874, 1876, 1878, 1879, 1881, 1883, 1884, 1886, 1887, 1889, 1891, 1892,
    1894, 1895, 1897, 1899, 1900, 1902, 1903, 1905, 1907, 1908, 1910, 1911, 1913, 1915, 1916, 1918,
    1919, 1921, 1923, 1924, 1926, 1927, 1929, 1931, 1932, 1934, 1935, 1937, 1939, 1940, 1942, 1943,
    1945, 1947, 1948, 1950, 1952, 1953, 1955, 1956, 1958, 1960, 1961, 1963, 1964, 1966, 1968, 1969,
    1971, 1972, 1974, 1976, 1977, 1979, 1980, 1982, 1984, 1985, 1987, 1988, 1990, 1992, 1993, 1995,
    1997, 1998, 2000, 2001, 2003, 2005, 2006, 2008, 2009, 2011, 2013, 2014, 2016, 2017, 2019, 2021,
    2022, 2024, 2025, 2027, 2029, 2030, 2032, 2034, 2035, 2037, 2038, 2040, 2042, 2043, 2045, 2046,
};

QVector<double> HalfSineTable = {};
void SignalGenerator::on_pbtn_FTU_TestNo_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,
                                                           "Select Folder to Save Files",
                                                           QDir::homePath());

    if (folderPath.isEmpty()) {
        return; // User canceled
    }

    // Save selected folder path for later use
    selectedFolderPath = folderPath;

    // Find all .bin files in the selected folder
    QDir dir(folderPath);
    QStringList filters;
    filters << "*.bin";
    QStringList binFiles = dir.entryList(filters, QDir::Files);

    // Clear old items and add new ones to comboBox
    ui->cmb_FTU_TestNo->clear();
    ui->cmb_FTU_TestNo->addItems(binFiles);

    if (binFiles.isEmpty()) {
        QMessageBox::information(this, "No Files", "No .bin files found in this folder.");
    }
}

void SignalGenerator::on_waveform_read_pbtn_clicked()
{
    QString fileName = ui->cmb_FTU_TestNo->currentText();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "No File Selected", "Please select a .bin file from the list.");
        return;
    }

    if (selectedFolderPath.isEmpty()) {
        QMessageBox::warning(this, "No Folder Selected", "Please browse and select a folder first.");
        return;
    }

    // Construct full path
    QString fullPath = QDir(selectedFolderPath).absoluteFilePath(fileName);

    QFile file(fullPath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + fullPath);
        return;
    }

    //    QByteArray fileData = file.readAll();
    //    file.close();

    //    const int structSize = sizeof(TestPoint_Table_Data);
    //    int count = fileData.size() / structSize;

    //    if (fileData.size() % structSize != 0) {
    //        QMessageBox::warning(this, "File Error", "File size is not aligned with struct size.");
    //        return;
    //    }

    //    dataArray = reinterpret_cast<const TestPoint_Table_Data *>(fileData.constData());
    if (file.read(reinterpret_cast<char *>(&dataArray), sizeof(TestPoint_Table_Data))
        != sizeof(TestPoint_Table_Data))
        file.close();
    //    qDebug() << "StartMsg:" << QString("0x%1").arg(dataArray.StartMsg, 2, 16, QLatin1Char('0'));
    //    qDebug() << "packetSize:" << dataArray.packetSize;
    //    qDebug() << "FTU_Test_No:" << dataArray.FTU_Test_No;
    //    qDebug() << "Signal_Type:"
    //             << QString("0x%1").arg(dataArray.Signal_Type, 2, 16, QLatin1Char('0'));
    //    qDebug() << "Signal_Injection_Point:"
    //             << QString("0x%1").arg(dataArray.Signal_Injection_Point, 2, 16, QLatin1Char('0'));
    //    qDebug() << "Safe_engage_Time_Secs:" << dataArray.Safe_engage_Time_Secs;
    //    qDebug() << "Invert_Flag:"
    //             << QString("0x%1").arg(dataArray.Invert_Flag, 2, 16, QLatin1Char('0'));
    //    qDebug() << "Slat_Input:" << dataArray.Slat_Input;
    //    qDebug() << "No_of_Repeats:"
    //             << QString("0x%1").arg(dataArray.No_of_Repeats, 2, 16, QLatin1Char('0'));
    //    qDebug() << "Time_Between_Repeats:" << dataArray.Time_Between_Repeats;
    //    qDebug() << "Amplitude:" << dataArray.Amplitude;
    //    qDebug() << "Pulse_Width_sec:" << dataArray.Pulse_Width_sec;
    //    qDebug() << "Type_of_Input:"
    //             << QString("0x%1").arg(dataArray.Type_of_Input, 2, 16, QLatin1Char('0'));
    //    qDebug() << "C0:" << dataArray.C0;
    //    qDebug() << "C1:" << dataArray.C1;
    //    qDebug() << "Amplitude_percent_of_stroke:" << dataArray.Amplitude_percent_of_stroke;
    //    qDebug() << "Start_FreqHz:" << dataArray.Start_FreqHz;
    //    qDebug() << "End_FreqHz:" << dataArray.End_FreqHz;
    //    qDebug() << "Freq_StepHz:" << dataArray.Freq_StepHz;
    //    qDebug() << "DwellDuration_Secs:" << dataArray.DwellDuration_Secs;
    //    qDebug() << "Max_Amplitude:" << dataArray.Max_Amplitude;
    //    qDebug() << "Impulse_Amplitude:" << dataArray.Impulse_Amplitude;
    //    qDebug() << "Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse:"
    //             << dataArray.Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse;
    //    qDebug() << "Wo:" << dataArray.Wo;
    //    qDebug() << "Wf:" << dataArray.Wf;
    //    qDebug() << "Sweep_Duration:" << dataArray.Sweep_Duration;
    //    qDebug() << "Pulse_Width:" << dataArray.Pulse_Width;
    //    qDebug() << "CRC_WORD:" << QString("0x%1").arg(dataArray.CRC_WORD, 4, 16, QLatin1Char('0'));
    //    qDebug() << "EndMsg:" << QString("0x%1").arg(dataArray.EndMsg, 4, 16, QLatin1Char('0'));

    ui->ProjectName->setCurrentIndex(1);

    if (dataArray.Invert_Flag == 0xFF) {
        ui->TransmissionMode_lineedit->clear();
        ui->TransmissionMode_lineedit->setText("ANALOG");
    } else {
        ui->TransmissionMode_lineedit->clear();
        ui->TransmissionMode_lineedit->setText("DIGITAL");
    }

    ui->lineEdit_FTU_TestNo->setText(QString("%1").arg(dataArray.FTU_Test_No, 3, 10, QChar('0')));

    if (dataArray.Signal_Type == 0x0) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("SQUARE_PULSE");
    } else if (dataArray.Signal_Type == 0x1) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("SQUARE_DOUBLET");
    } else if (dataArray.Signal_Type == 0x2) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("HALF_SINE_PULSE");
    } else if (dataArray.Signal_Type == 0x3) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("FULL_SINE_DOUBLET");
    } else if (dataArray.Signal_Type == 0x4) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("PULSE_TRAIN_3_2_1_1");
    } else if (dataArray.Signal_Type == 0x5) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("LINEAR_SINE_SWEEP");
    } else if (dataArray.Signal_Type == 0x6) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("LOGARITHMIC_SINE_SWEEP");
    } else if (dataArray.Signal_Type == 0x7) {
        ui->WaveFormSelect_lineedit->clear();
        ui->WaveFormSelect_lineedit->setText("RANDOM_SIGNAL");
    }

    if (dataArray.Signal_Injection_Point == 0x0) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("INBOARD_ELEVON_SYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x1) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("OUTBOARD_ELEVON_SYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x2) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("INBOARD_ELEVON_ASYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x3) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("OUTBOARD_ELEVON_ASYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x4) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x5) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x6) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("RUDDER");
    } else if (dataArray.Signal_Injection_Point == 0x7) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("CANARD_SYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x8) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("CANARD_ASYMMETRIC");
    } else if (dataArray.Signal_Injection_Point == 0x9) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("PITCH_STICK_FTU_INPUT");
    } else if (dataArray.Signal_Injection_Point == 0xA) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("ROLL_STICK_FTU_INPUT");
    } else if (dataArray.Signal_Injection_Point == 0xB) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("RUDDER_PEDAL_FTU_INPUT");
    } else if (dataArray.Signal_Injection_Point == 0xC) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("SLAT_INPUT");
    } else if (dataArray.Signal_Injection_Point == 0xD) {
        ui->SignalInjectionPoint_lineedit->clear();
        ui->SignalInjectionPoint_lineedit->setText("AIRBRAKE_INPUT");
    }

    // Amplitude_percent_of_stroke (float)
    if (dataArray.Amplitude_percent_of_stroke != 5432.1f) {
        ui->Amplitude_percent_of_stroke_LineEdit->setVisible(true);
        ui->Amplitude_percent_of_stroke_label->setVisible(true);
        ui->Amplitude_percent_of_stroke_LineEdit->setText(
            QString::number(dataArray.Amplitude_percent_of_stroke));
    } else {
        ui->Amplitude_percent_of_stroke_LineEdit->setVisible(false);
        ui->Amplitude_percent_of_stroke_label->setVisible(false);
    }

    // C0 (float)
    if (dataArray.C0 != 5432.1f) {
        ui->lineEdit_C0->setVisible(true);
        ui->label_C0->setVisible(true);
        ui->lineEdit_C0->setText(QString::number(dataArray.C0));
    } else {
        ui->lineEdit_C0->setVisible(false);
        ui->label_C0->setVisible(false);
    }

    // C1 (float)
    if (dataArray.C1 != 5432.1f) {
        ui->lineEdit_C1->setVisible(true);
        ui->label_C1->setVisible(true);
        ui->lineEdit_C1->setText(QString::number(dataArray.C1));
    } else {
        ui->lineEdit_C1->setVisible(false);
        ui->label_C1->setVisible(false);
    }

    // Start_FreqHz (float)
    if (dataArray.Start_FreqHz != 5432.1f) {
        ui->lineEditStartFreq->setVisible(true);
        ui->labelStartFreq->setVisible(true);
        ui->lineEditStartFreq->setText(QString::number(dataArray.Start_FreqHz));
    } else {
        ui->lineEditStartFreq->setVisible(false);
        ui->labelStartFreq->setVisible(false);
    }

    // End_FreqHz (float)
    if (dataArray.End_FreqHz != 5432.1f) {
        ui->lineEditEndFreq->setVisible(true);
        ui->labelEndFreq->setVisible(true);
        ui->lineEditEndFreq->setText(QString::number(dataArray.End_FreqHz));
    } else {
        ui->lineEditEndFreq->setVisible(false);
        ui->labelEndFreq->setVisible(false);
    }

    // Freq_StepHz (float)
    if (dataArray.Freq_StepHz != 5432.1f) {
        ui->lineEditFreqStep->setVisible(true);
        ui->labelFreqStep->setVisible(true);
        ui->lineEditFreqStep->setText(QString::number(dataArray.Freq_StepHz));
    } else {
        ui->lineEditFreqStep->setVisible(false);
        ui->labelFreqStep->setVisible(false);
    }

    // DwellDuration_Secs (float)
    if (dataArray.DwellDuration_Secs != 5432.1f) {
        ui->lineEdit_DwellDuration->setVisible(true);
        ui->labelDWell_Duration->setVisible(true);
        ui->lineEdit_DwellDuration->setText(QString::number(dataArray.DwellDuration_Secs));
    } else {
        ui->lineEdit_DwellDuration->setVisible(false);
        ui->labelDWell_Duration->setVisible(false);
    }

    // Safe_engage_Time_Secs (float)
    if (dataArray.Safe_engage_Time_Secs != 5432.1f) {
        ui->SafeEngageTime->setVisible(true);
        ui->label_SafeEngageTime->setVisible(true);
        ui->SafeEngageTime->setText(QString::number(dataArray.Safe_engage_Time_Secs));
    } else {
        ui->SafeEngageTime->setVisible(false);
        ui->label_SafeEngageTime->setVisible(false);
    }

    // Invert_Flag (uint8_t)
    if (dataArray.Invert_Flag != 0xFF) {
        ui->LIneEdit_InvertFlag->setVisible(true);
        ui->label_InvertFlag->setVisible(true);

        if (dataArray.Invert_Flag == 0) {
            ui->LIneEdit_InvertFlag->setText("FALSE");
        } else if (dataArray.Invert_Flag == 1) {
            ui->LIneEdit_InvertFlag->setText("TRUE");
        } else {
            ui->LIneEdit_InvertFlag->setText(
                QString::number(static_cast<int>(dataArray.Invert_Flag)));
        }

    } else {
        ui->LIneEdit_InvertFlag->setVisible(false);
        ui->label_InvertFlag->setVisible(false);
    }

    // Slat_Input (float)
    if (dataArray.Slat_Input != 5432.1f) {
        ui->lineEdit_SlateInput->setVisible(true);
        ui->label_SlateInput->setVisible(true);
        ui->lineEdit_SlateInput->setText(QString::number(dataArray.Slat_Input));
    } else {
        ui->lineEdit_SlateInput->setVisible(false);
        ui->label_SlateInput->setVisible(false);
    }

    // No_of_Repeats (uint8_t)
    if (dataArray.No_of_Repeats != 0xFF) {
        ui->lineEdit_Repeats->setVisible(true);
        ui->label_Repeats->setVisible(true);
        ui->lineEdit_Repeats->setText(QString::number(dataArray.No_of_Repeats));
    } else {
        ui->lineEdit_Repeats->setVisible(false);
        ui->label_Repeats->setVisible(false);
    }

    // Time_Between_Repeats (float)
    if (dataArray.Time_Between_Repeats != 5432.1f) {
        ui->lineEdit_Time_BW_Repeats->setVisible(true);
        ui->label_Time_BW_Repeats->setVisible(true);
        ui->lineEdit_Time_BW_Repeats->setText(QString::number(dataArray.Time_Between_Repeats));
    } else {
        ui->lineEdit_Time_BW_Repeats->setVisible(false);
        ui->label_Time_BW_Repeats->setVisible(false);
    }

    // Amplitude (float)
    if (dataArray.Amplitude != 5432.1f) {
        ui->Amplitude1_LineEdit->setVisible(true);
        ui->Amp1_label->setVisible(true);
        ui->Amplitude1_LineEdit->setText(QString::number(dataArray.Amplitude));
    } else {
        ui->Amplitude1_LineEdit->setVisible(false);
        ui->Amp1_label->setVisible(false);
    }

    // Pulse_Width_sec (float)
    if (dataArray.Pulse_Width_sec != 5432.1f) {
        ui->lineEdit_PulseWidth_Sec->setVisible(true);
        ui->label_PulseWidth_Sec->setVisible(true);
        ui->lineEdit_PulseWidth_Sec->setText(QString::number(dataArray.Pulse_Width_sec));
    } else {
        ui->lineEdit_PulseWidth_Sec->setVisible(false);
        ui->label_PulseWidth_Sec->setVisible(false);
    }

    // Type_of_Input (uint8_t)
    if (dataArray.Type_of_Input != 0xFF) {
        ui->lineEdit_TypeOfInput->setVisible(true);
        ui->label_TypeOfInput->setVisible(true);
        ui->lineEdit_TypeOfInput->setText(QString::number(dataArray.Type_of_Input));
    } else {
        ui->lineEdit_TypeOfInput->setVisible(false);
        ui->label_TypeOfInput->setVisible(false);
    }

    // Max_Amplitude (float)
    if (dataArray.Max_Amplitude != 5432.1f) {
        ui->lineEdit_Max_Amplitude->setVisible(true);
        ui->label_Max_Amplitude->setVisible(true);
        ui->lineEdit_Max_Amplitude->setText(QString::number(dataArray.Max_Amplitude));
    } else {
        ui->lineEdit_Max_Amplitude->setVisible(false);
        ui->label_Max_Amplitude->setVisible(false);
    }

    // Impulse_Amplitude (float)
    if (dataArray.Impulse_Amplitude != 5432.1f) {
        ui->lineEdit_Impulse_Amplitude->setVisible(true);
        ui->label_Impulse_Amplitude->setVisible(true);
        ui->lineEdit_Impulse_Amplitude->setText(QString::number(dataArray.Impulse_Amplitude));
    } else {
        ui->lineEdit_Impulse_Amplitude->setVisible(false);
        ui->label_Impulse_Amplitude->setVisible(false);
    }

    // Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse (float)
    if (dataArray.Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse != 5432.1f) {
        ui->lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setVisible(true);
        ui->label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setVisible(true);
        ui->lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setText(
            QString::number(dataArray.Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse));
    } else {
        ui->lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setVisible(false);
        ui->label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setVisible(false);
    }

    // Wo (float)
    if (dataArray.Wo != 5432.1f) {
        ui->lineEdit_Wo->setVisible(true);
        ui->label_Wo->setVisible(true);
        ui->lineEdit_Wo->setText(QString::number(dataArray.Wo));
    } else {
        ui->lineEdit_Wo->setVisible(false);
        ui->label_Wo->setVisible(false);
    }

    // Wf (float)
    if (dataArray.Wf != 5432.1f) {
        ui->lineEdit_Wf->setVisible(true);
        ui->label_Wf->setVisible(true);
        ui->lineEdit_Wf->setText(QString::number(dataArray.Wf));
    } else {
        ui->lineEdit_Wf->setVisible(false);
        ui->label_Wf->setVisible(false);
    }

    // Sweep_Duration (float)
    if (dataArray.Sweep_Duration != 5432.1f) {
        ui->lineEdit_Sweep_Duration->setVisible(true);
        ui->label_Sweep_Duration->setVisible(true);
        ui->lineEdit_Sweep_Duration->setText(QString::number(dataArray.Sweep_Duration));
    } else {
        ui->lineEdit_Sweep_Duration->setVisible(false);
        ui->label_Sweep_Duration->setVisible(false);
    }

    // Pulse_Width (float)
    if (dataArray.Pulse_Width != 5432.1f) {
        ui->lineEdit_PulseWidth->setVisible(true);
        ui->label_Sweep_Duration->setVisible(true);
        ui->label_PulseWidth->setText(QString::number(dataArray.Pulse_Width));
    } else {
        ui->lineEdit_PulseWidth->setVisible(false);
        ui->label_PulseWidth->setVisible(false);
    }
}

void SignalGenerator::on_PlotWaveforms_PB_clicked()
{
    if (dataArray.Signal_Injection_Point == INBOARD_ELEVON_SYMMETRIC
        || dataArray.Signal_Injection_Point == OUTBOARD_ELEVON_SYMMETRIC
        || dataArray.Signal_Injection_Point == INBOARD_ELEVON_ASYMMETRIC
        || dataArray.Signal_Injection_Point == OUTBOARD_ELEVON_ASYMMETRIC) {
        IO_ELEVON_Single(dataArray.Signal_Type);
    } else if (dataArray.Signal_Injection_Point == INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC
               || dataArray.Signal_Injection_Point == INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC) {
        IO_ELEVON_Combined(dataArray.Signal_Type);
    } else if (dataArray.Signal_Injection_Point == CANARD_SYMMETRIC
               || dataArray.Signal_Injection_Point == CANARD_ASYMMETRIC) {
        Canard_Single(dataArray.Signal_Type);
    } else if (dataArray.Signal_Injection_Point == RUDDER) {
        Rudder_single(dataArray.Signal_Type);
    }
}

QVector<double> HalfsineTable = {
    0,    3,    6,    10,   13,   16,   19,   23,   26,   29,   32,   35,   39,   42,   45,   48,
    51,   55,   58,   61,   64,   68,   71,   74,   77,   80,   84,   87,   90,   93,   97,   100,
    103,  106,  109,  113,  116,  119,  122,  125,  129,  132,  135,  138,  142,  145,  148,  151,
    154,  158,  161,  164,  167,  170,  174,  177,  180,  183,  187,  190,  193,  196,  199,  203,
    206,  209,  212,  215,  219,  222,  225,  228,  232,  235,  238,  241,  244,  248,  251,  254,
    257,  260,  264,  267,  270,  273,  276,  280,  283,  286,  289,  292,  296,  299,  302,  305,
    309,  312,  315,  318,  321,  325,  328,  331,  334,  337,  341,  344,  347,  350,  353,  357,
    360,  363,  366,  369,  373,  376,  379,  382,  385,  389,  392,  395,  398,  401,  405,  408,
    411,  414,  417,  421,  424,  427,  430,  433,  437,  440,  443,  446,  449,  453,  456,  459,
    462,  465,  469,  472,  475,  478,  481,  485,  488,  491,  494,  497,  501,  504,  507,  510,
    513,  517,  520,  523,  526,  529,  533,  536,  539,  542,  545,  548,  552,  555,  558,  561,
    564,  568,  571,  574,  577,  580,  584,  587,  590,  593,  596,  599,  603,  606,  609,  612,
    615,  619,  622,  625,  628,  631,  634,  638,  641,  644,  647,  650,  653,  657,  660,  663,
    666,  669,  673,  676,  679,  682,  685,  688,  692,  695,  698,  701,  704,  707,  711,  714,
    717,  720,  723,  726,  730,  733,  736,  739,  742,  745,  749,  752,  755,  758,  761,  764,
    768,  771,  774,  777,  780,  783,  786,  790,  793,  796,  799,  802,  805,  809,  812,  815,
    818,  821,  824,  827,  831,  834,  837,  840,  843,  846,  850,  853,  856,  859,  862,  865,
    868,  872,  875,  878,  881,  884,  887,  890,  894,  897,  900,  903,  906,  909,  912,  915,
    919,  922,  925,  928,  931,  934,  937,  941,  944,  947,  950,  953,  956,  959,  962,  966,
    969,  972,  975,  978,  981,  984,  987,  991,  994,  997,  1000, 1003, 1006, 1009, 1012, 1016,
    1019, 1022, 1025, 1028, 1031, 1034, 1037, 1040, 1044, 1047, 1050, 1053, 1056, 1059, 1062, 1065,
    1068, 1072, 1075, 1078, 1081, 1084, 1087, 1090, 1093, 1096, 1099, 1103, 1106, 1109, 1112, 1115,
    1118, 1121, 1124, 1127, 1130, 1133, 1137, 1140, 1143, 1146, 1149, 1152, 1155, 1158, 1161, 1164,
    1167, 1171, 1174, 1177, 1180, 1183, 1186, 1189, 1192, 1195, 1198, 1201, 1204, 1207, 1211, 1214,
    1217, 1220, 1223, 1226, 1229, 1232, 1235, 1238, 1241, 1244, 1247, 1250, 1253, 1257, 1260, 1263,
    1266, 1269, 1272, 1275, 1278, 1281, 1284, 1287, 1290, 1293, 1296, 1299, 1302, 1305, 1308, 1312,
    1315, 1318, 1321, 1324, 1327, 1330, 1333, 1336, 1339, 1342, 1345, 1348, 1351, 1354, 1357, 1360,
    1363, 1366, 1369, 1372, 1375, 1378, 1381, 1384, 1387, 1390, 1394, 1397, 1400, 1403, 1406, 1409,
    1412, 1415, 1418, 1421, 1424, 1427, 1430, 1433, 1436, 1439, 1442, 1445, 1448, 1451, 1454, 1457,
    1460, 1463, 1466, 1469, 1472, 1475, 1478, 1481, 1484, 1487, 1490, 1493, 1496, 1499, 1502, 1505,
    1508, 1511, 1514, 1517, 1520, 1523, 1526, 1529, 1532, 1535, 1538, 1541, 1544, 1547, 1550, 1553,
    1556, 1559, 1562, 1564, 1567, 1570, 1573, 1576, 1579, 1582, 1585, 1588, 1591, 1594, 1597, 1600,
    1603, 1606, 1609, 1612, 1615, 1618, 1621, 1624, 1627, 1630, 1633, 1636, 1639, 1641, 1644, 1647,
    1650, 1653, 1656, 1659, 1662, 1665, 1668, 1671, 1674, 1677, 1680, 1683, 1686, 1688, 1691, 1694,
    1697, 1700, 1703, 1706, 1709, 1712, 1715, 1718, 1721, 1724, 1726, 1729, 1732, 1735, 1738, 1741,
    1744, 1747, 1750, 1753, 1756, 1759, 1761, 1764, 1767, 1770, 1773, 1776, 1779, 1782, 1785, 1788,
    1790, 1793, 1796, 1799, 1802, 1805, 1808, 1811, 1814, 1816, 1819, 1822, 1825, 1828, 1831, 1834,
    1837, 1839, 1842, 1845, 1848, 1851, 1854, 1857, 1860, 1862, 1865, 1868, 1871, 1874, 1877, 1880,
    1882, 1885, 1888, 1891, 1894, 1897, 1900, 1902, 1905, 1908, 1911, 1914, 1917, 1919, 1922, 1925,
    1928, 1931, 1934, 1936, 1939, 1942, 1945, 1948, 1951, 1953, 1956, 1959, 1962, 1965, 1968, 1970,
    1973, 1976, 1979, 1982, 1984, 1987, 1990, 1993, 1996, 1999, 2001, 2004, 2007, 2010, 2013, 2015,
    2018, 2021, 2024, 2027, 2029, 2032, 2035, 2038, 2041, 2043, 2046, 2049, 2052, 2054, 2057, 2060,
    2063, 2066, 2068, 2071, 2074, 2077, 2079, 2082, 2085, 2088, 2091, 2093, 2096, 2099, 2102, 2104,
    2107, 2110, 2113, 2115, 2118, 2121, 2124, 2126, 2129, 2132, 2135, 2137, 2140, 2143, 2146, 2148,
    2151, 2154, 2157, 2159, 2162, 2165, 2167, 2170, 2173, 2176, 2178, 2181, 2184, 2187, 2189, 2192,
    2195, 2197, 2200, 2203, 2206, 2208, 2211, 2214, 2216, 2219, 2222, 2224, 2227, 2230, 2233, 2235,
    2238, 2241, 2243, 2246, 2249, 2251, 2254, 2257, 2259, 2262, 2265, 2268, 2270, 2273, 2276, 2278,
    2281, 2284, 2286, 2289, 2292, 2294, 2297, 2300, 2302, 2305, 2308, 2310, 2313, 2316, 2318, 2321,
    2323, 2326, 2329, 2331, 2334, 2337, 2339, 2342, 2345, 2347, 2350, 2353, 2355, 2358, 2360, 2363,
    2366, 2368, 2371, 2374, 2376, 2379, 2381, 2384, 2387, 2389, 2392, 2394, 2397, 2400, 2402, 2405,
    2408, 2410, 2413, 2415, 2418, 2420, 2423, 2426, 2428, 2431, 2433, 2436, 2439, 2441, 2444, 2446,
    2449, 2452, 2454, 2457, 2459, 2462, 2464, 2467, 2470, 2472, 2475, 2477, 2480, 2482, 2485, 2487,
    2490, 2493, 2495, 2498, 2500, 2503, 2505, 2508, 2510, 2513, 2515, 2518, 2521, 2523, 2526, 2528,
    2531, 2533, 2536, 2538, 2541, 2543, 2546, 2548, 2551, 2553, 2556, 2558, 2561, 2563, 2566, 2568,
    2571, 2573, 2576, 2578, 2581, 2583, 2586, 2588, 2591, 2593, 2596, 2598, 2601, 2603, 2606, 2608,
    2611, 2613, 2616, 2618, 2621, 2623, 2626, 2628, 2631, 2633, 2635, 2638, 2640, 2643, 2645, 2648,
    2650, 2653, 2655, 2658, 2660, 2662, 2665, 2667, 2670, 2672, 2675, 2677, 2680, 2682, 2684, 2687,
    2689, 2692, 2694, 2697, 2699, 2701, 2704, 2706, 2709, 2711, 2713, 2716, 2718, 2721, 2723, 2725,
    2728, 2730, 2733, 2735, 2737, 2740, 2742, 2745, 2747, 2749, 2752, 2754, 2757, 2759, 2761, 2764,
    2766, 2768, 2771, 2773, 2776, 2778, 2780, 2783, 2785, 2787, 2790, 2792, 2794, 2797, 2799, 2801,
    2804, 2806, 2808, 2811, 2813, 2815, 2818, 2820, 2822, 2825, 2827, 2829, 2832, 2834, 2836, 2839,
    2841, 2843, 2846, 2848, 2850, 2853, 2855, 2857, 2860, 2862, 2864, 2866, 2869, 2871, 2873, 2876,
    2878, 2880, 2882, 2885, 2887, 2889, 2892, 2894, 2896, 2898, 2901, 2903, 2905, 2908, 2910, 2912,
    2914, 2917, 2919, 2921, 2923, 2926, 2928, 2930, 2932, 2935, 2937, 2939, 2941, 2944, 2946, 2948,
    2950, 2952, 2955, 2957, 2959, 2961, 2964, 2966, 2968, 2970, 2972, 2975, 2977, 2979, 2981, 2983,
    2986, 2988, 2990, 2992, 2994, 2997, 2999, 3001, 3003, 3005, 3008, 3010, 3012, 3014, 3016, 3019,
    3021, 3023, 3025, 3027, 3029, 3032, 3034, 3036, 3038, 3040, 3042, 3044, 3047, 3049, 3051, 3053,
    3055, 3057, 3059, 3062, 3064, 3066, 3068, 3070, 3072, 3074, 3077, 3079, 3081, 3083, 3085, 3087,
    3089, 3091, 3093, 3096, 3098, 3100, 3102, 3104, 3106, 3108, 3110, 3112, 3114, 3117, 3119, 3121,
    3123, 3125, 3127, 3129, 3131, 3133, 3135, 3137, 3139, 3141, 3143, 3146, 3148, 3150, 3152, 3154,
    3156, 3158, 3160, 3162, 3164, 3166, 3168, 3170, 3172, 3174, 3176, 3178, 3180, 3182, 3184, 3186,
    3188, 3190, 3192, 3194, 3196, 3198, 3200, 3202, 3204, 3206, 3208, 3210, 3212, 3214, 3216, 3218,
    3220, 3222, 3224, 3226, 3228, 3230, 3232, 3234, 3236, 3238, 3240, 3242, 3244, 3246, 3248, 3250,
    3252, 3254, 3256, 3258, 3260, 3262, 3264, 3266, 3268, 3269, 3271, 3273, 3275, 3277, 3279, 3281,
    3283, 3285, 3287, 3289, 3291, 3293, 3294, 3296, 3298, 3300, 3302, 3304, 3306, 3308, 3310, 3312,
    3313, 3315, 3317, 3319, 3321, 3323, 3325, 3327, 3329, 3330, 3332, 3334, 3336, 3338, 3340, 3342,
    3343, 3345, 3347, 3349, 3351, 3353, 3355, 3356, 3358, 3360, 3362, 3364, 3366, 3367, 3369, 3371,
    3373, 3375, 3377, 3378, 3380, 3382, 3384, 3386, 3387, 3389, 3391, 3393, 3395, 3396, 3398, 3400,
    3402, 3404, 3405, 3407, 3409, 3411, 3413, 3414, 3416, 3418, 3420, 3421, 3423, 3425, 3427, 3428,
    3430, 3432, 3434, 3435, 3437, 3439, 3441, 3442, 3444, 3446, 3448, 3449, 3451, 3453, 3455, 3456,
    3458, 3460, 3462, 3463, 3465, 3467, 3468, 3470, 3472, 3473, 3475, 3477, 3479, 3480, 3482, 3484,
    3485, 3487, 3489, 3490, 3492, 3494, 3495, 3497, 3499, 3500, 3502, 3504, 3505, 3507, 3509, 3510,
    3512, 3514, 3515, 3517, 3519, 3520, 3522, 3524, 3525, 3527, 3529, 3530, 3532, 3533, 3535, 3537,
    3538, 3540, 3542, 3543, 3545, 3546, 3548, 3550, 3551, 3553, 3554, 3556, 3558, 3559, 3561, 3562,
    3564, 3566, 3567, 3569, 3570, 3572, 3573, 3575, 3577, 3578, 3580, 3581, 3583, 3584, 3586, 3587,
    3589, 3591, 3592, 3594, 3595, 3597, 3598, 3600, 3601, 3603, 3604, 3606, 3607, 3609, 3610, 3612,
    3614, 3615, 3617, 3618, 3620, 3621, 3623, 3624, 3626, 3627, 3629, 3630, 3632, 3633, 3634, 3636,
    3637, 3639, 3640, 3642, 3643, 3645, 3646, 3648, 3649, 3651, 3652, 3654, 3655, 3656, 3658, 3659,
    3661, 3662, 3664, 3665, 3667, 3668, 3669, 3671, 3672, 3674, 3675, 3677, 3678, 3679, 3681, 3682,
    3684, 3685, 3686, 3688, 3689, 3691, 3692, 3693, 3695, 3696, 3698, 3699, 3700, 3702, 3703, 3704,
    3706, 3707, 3708, 3710, 3711, 3713, 3714, 3715, 3717, 3718, 3719, 3721, 3722, 3723, 3725, 3726,
    3727, 3729, 3730, 3731, 3733, 3734, 3735, 3737, 3738, 3739, 3741, 3742, 3743, 3744, 3746, 3747,
    3748, 3750, 3751, 3752, 3754, 3755, 3756, 3757, 3759, 3760, 3761, 3762, 3764, 3765, 3766, 3768,
    3769, 3770, 3771, 3773, 3774, 3775, 3776, 3778, 3779, 3780, 3781, 3783, 3784, 3785, 3786, 3787,
    3789, 3790, 3791, 3792, 3794, 3795, 3796, 3797, 3798, 3800, 3801, 3802, 3803, 3804, 3806, 3807,
    3808, 3809, 3810, 3811, 3813, 3814, 3815, 3816, 3817, 3818, 3820, 3821, 3822, 3823, 3824, 3825,
    3827, 3828, 3829, 3830, 3831, 3832, 3833, 3834, 3836, 3837, 3838, 3839, 3840, 3841, 3842, 3843,
    3845, 3846, 3847, 3848, 3849, 3850, 3851, 3852, 3853, 3854, 3856, 3857, 3858, 3859, 3860, 3861,
    3862, 3863, 3864, 3865, 3866, 3867, 3868, 3869, 3870, 3871, 3873, 3874, 3875, 3876, 3877, 3878,
    3879, 3880, 3881, 3882, 3883, 3884, 3885, 3886, 3887, 3888, 3889, 3890, 3891, 3892, 3893, 3894,
    3895, 3896, 3897, 3898, 3899, 3900, 3901, 3902, 3903, 3904, 3905, 3906, 3907, 3908, 3909, 3910,
    3911, 3912, 3912, 3913, 3914, 3915, 3916, 3917, 3918, 3919, 3920, 3921, 3922, 3923, 3924, 3925,
    3926, 3926, 3927, 3928, 3929, 3930, 3931, 3932, 3933, 3934, 3935, 3935, 3936, 3937, 3938, 3939,
    3940, 3941, 3942, 3942, 3943, 3944, 3945, 3946, 3947, 3948, 3949, 3949, 3950, 3951, 3952, 3953,
    3954, 3954, 3955, 3956, 3957, 3958, 3959, 3959, 3960, 3961, 3962, 3963, 3963, 3964, 3965, 3966,
    3967, 3967, 3968, 3969, 3970, 3971, 3971, 3972, 3973, 3974, 3975, 3975, 3976, 3977, 3978, 3978,
    3979, 3980, 3981, 3981, 3982, 3983, 3984, 3984, 3985, 3986, 3987, 3987, 3988, 3989, 3990, 3990,
    3991, 3992, 3992, 3993, 3994, 3995, 3995, 3996, 3997, 3997, 3998, 3999, 3999, 4000, 4001, 4002,
    4002, 4003, 4004, 4004, 4005, 4006, 4006, 4007, 4008, 4008, 4009, 4010, 4010, 4011, 4011, 4012,
    4013, 4013, 4014, 4015, 4015, 4016, 4017, 4017, 4018, 4018, 4019, 4020, 4020, 4021, 4022, 4022,
    4023, 4023, 4024, 4025, 4025, 4026, 4026, 4027, 4027, 4028, 4029, 4029, 4030, 4030, 4031, 4031,
    4032, 4033, 4033, 4034, 4034, 4035, 4035, 4036, 4036, 4037, 4038, 4038, 4039, 4039, 4040, 4040,
    4041, 4041, 4042, 4042, 4043, 4043, 4044, 4044, 4045, 4045, 4046, 4046, 4047, 4047, 4048, 4048,
    4049, 4049, 4050, 4050, 4051, 4051, 4052, 4052, 4053, 4053, 4053, 4054, 4054, 4055, 4055, 4056,
    4056, 4057, 4057, 4057, 4058, 4058, 4059, 4059, 4060, 4060, 4060, 4061, 4061, 4062, 4062, 4062,
    4063, 4063, 4064, 4064, 4064, 4065, 4065, 4066, 4066, 4066, 4067, 4067, 4068, 4068, 4068, 4069,
    4069, 4069, 4070, 4070, 4070, 4071, 4071, 4071, 4072, 4072, 4072, 4073, 4073, 4073, 4074, 4074,
    4074, 4075, 4075, 4075, 4076, 4076, 4076, 4077, 4077, 4077, 4078, 4078, 4078, 4078, 4079, 4079,
    4079, 4080, 4080, 4080, 4080, 4081, 4081, 4081, 4081, 4082, 4082, 4082, 4082, 4083, 4083, 4083,
    4083, 4084, 4084, 4084, 4084, 4085, 4085, 4085, 4085, 4086, 4086, 4086, 4086, 4086, 4087, 4087,
    4087, 4087, 4087, 4088, 4088, 4088, 4088, 4088, 4089, 4089, 4089, 4089, 4089, 4089, 4090, 4090,
    4090, 4090, 4090, 4090, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4092, 4092, 4092, 4092, 4092,
    4092, 4092, 4092, 4092, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4094, 4094,
    4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094,
    4094, 4094, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4093, 4092, 4092, 4092, 4092,
    4092, 4092, 4092, 4092, 4092, 4091, 4091, 4091, 4091, 4091, 4091, 4091, 4090, 4090, 4090, 4090,
    4090, 4090, 4089, 4089, 4089, 4089, 4089, 4089, 4088, 4088, 4088, 4088, 4088, 4087, 4087, 4087,
    4087, 4087, 4086, 4086, 4086, 4086, 4086, 4085, 4085, 4085, 4085, 4084, 4084, 4084, 4084, 4083,
    4083, 4083, 4083, 4082, 4082, 4082, 4082, 4081, 4081, 4081, 4081, 4080, 4080, 4080, 4080, 4079,
    4079, 4079, 4078, 4078, 4078, 4078, 4077, 4077, 4077, 4076, 4076, 4076, 4075, 4075, 4075, 4074,
    4074, 4074, 4073, 4073, 4073, 4072, 4072, 4072, 4071, 4071, 4071, 4070, 4070, 4070, 4069, 4069,
    4069, 4068, 4068, 4068, 4067, 4067, 4066, 4066, 4066, 4065, 4065, 4064, 4064, 4064, 4063, 4063,
    4062, 4062, 4062, 4061, 4061, 4060, 4060, 4060, 4059, 4059, 4058, 4058, 4057, 4057, 4057, 4056,
    4056, 4055, 4055, 4054, 4054, 4053, 4053, 4053, 4052, 4052, 4051, 4051, 4050, 4050, 4049, 4049,
    4048, 4048, 4047, 4047, 4046, 4046, 4045, 4045, 4044, 4044, 4043, 4043, 4042, 4042, 4041, 4041,
    4040, 4040, 4039, 4039, 4038, 4038, 4037, 4036, 4036, 4035, 4035, 4034, 4034, 4033, 4033, 4032,
    4031, 4031, 4030, 4030, 4029, 4029, 4028, 4027, 4027, 4026, 4026, 4025, 4025, 4024, 4023, 4023,
    4022, 4022, 4021, 4020, 4020, 4019, 4018, 4018, 4017, 4017, 4016, 4015, 4015, 4014, 4013, 4013,
    4012, 4011, 4011, 4010, 4010, 4009, 4008, 4008, 4007, 4006, 4006, 4005, 4004, 4004, 4003, 4002,
    4002, 4001, 4000, 3999, 3999, 3998, 3997, 3997, 3996, 3995, 3995, 3994, 3993, 3992, 3992, 3991,
    3990, 3990, 3989, 3988, 3987, 3987, 3986, 3985, 3984, 3984, 3983, 3982, 3981, 3981, 3980, 3979,
    3978, 3978, 3977, 3976, 3975, 3975, 3974, 3973, 3972, 3971, 3971, 3970, 3969, 3968, 3967, 3967,
    3966, 3965, 3964, 3963, 3963, 3962, 3961, 3960, 3959, 3959, 3958, 3957, 3956, 3955, 3954, 3954,
    3953, 3952, 3951, 3950, 3949, 3949, 3948, 3947, 3946, 3945, 3944, 3943, 3942, 3942, 3941, 3940,
    3939, 3938, 3937, 3936, 3935, 3935, 3934, 3933, 3932, 3931, 3930, 3929, 3928, 3927, 3926, 3926,
    3925, 3924, 3923, 3922, 3921, 3920, 3919, 3918, 3917, 3916, 3915, 3914, 3913, 3912, 3912, 3911,
    3910, 3909, 3908, 3907, 3906, 3905, 3904, 3903, 3902, 3901, 3900, 3899, 3898, 3897, 3896, 3895,
    3894, 3893, 3892, 3891, 3890, 3889, 3888, 3887, 3886, 3885, 3884, 3883, 3882, 3881, 3880, 3879,
    3878, 3877, 3876, 3875, 3874, 3873, 3871, 3870, 3869, 3868, 3867, 3866, 3865, 3864, 3863, 3862,
    3861, 3860, 3859, 3858, 3857, 3856, 3854, 3853, 3852, 3851, 3850, 3849, 3848, 3847, 3846, 3845,
    3843, 3842, 3841, 3840, 3839, 3838, 3837, 3836, 3834, 3833, 3832, 3831, 3830, 3829, 3828, 3827,
    3825, 3824, 3823, 3822, 3821, 3820, 3818, 3817, 3816, 3815, 3814, 3813, 3811, 3810, 3809, 3808,
    3807, 3806, 3804, 3803, 3802, 3801, 3800, 3798, 3797, 3796, 3795, 3794, 3792, 3791, 3790, 3789,
    3787, 3786, 3785, 3784, 3783, 3781, 3780, 3779, 3778, 3776, 3775, 3774, 3773, 3771, 3770, 3769,
    3768, 3766, 3765, 3764, 3762, 3761, 3760, 3759, 3757, 3756, 3755, 3754, 3752, 3751, 3750, 3748,
    3747, 3746, 3744, 3743, 3742, 3741, 3739, 3738, 3737, 3735, 3734, 3733, 3731, 3730, 3729, 3727,
    3726, 3725, 3723, 3722, 3721, 3719, 3718, 3717, 3715, 3714, 3713, 3711, 3710, 3708, 3707, 3706,
    3704, 3703, 3702, 3700, 3699, 3698, 3696, 3695, 3693, 3692, 3691, 3689, 3688, 3686, 3685, 3684,
    3682, 3681, 3679, 3678, 3677, 3675, 3674, 3672, 3671, 3669, 3668, 3667, 3665, 3664, 3662, 3661,
    3659, 3658, 3656, 3655, 3654, 3652, 3651, 3649, 3648, 3646, 3645, 3643, 3642, 3640, 3639, 3637,
    3636, 3634, 3633, 3632, 3630, 3629, 3627, 3626, 3624, 3623, 3621, 3620, 3618, 3617, 3615, 3614,
    3612, 3610, 3609, 3607, 3606, 3604, 3603, 3601, 3600, 3598, 3597, 3595, 3594, 3592, 3591, 3589,
    3587, 3586, 3584, 3583, 3581, 3580, 3578, 3577, 3575, 3573, 3572, 3570, 3569, 3567, 3566, 3564,
    3562, 3561, 3559, 3558, 3556, 3554, 3553, 3551, 3550, 3548, 3546, 3545, 3543, 3542, 3540, 3538,
    3537, 3535, 3533, 3532, 3530, 3529, 3527, 3525, 3524, 3522, 3520, 3519, 3517, 3515, 3514, 3512,
    3510, 3509, 3507, 3505, 3504, 3502, 3500, 3499, 3497, 3495, 3494, 3492, 3490, 3489, 3487, 3485,
    3484, 3482, 3480, 3479, 3477, 3475, 3473, 3472, 3470, 3468, 3467, 3465, 3463, 3462, 3460, 3458,
    3456, 3455, 3453, 3451, 3449, 3448, 3446, 3444, 3442, 3441, 3439, 3437, 3435, 3434, 3432, 3430,
    3428, 3427, 3425, 3423, 3421, 3420, 3418, 3416, 3414, 3413, 3411, 3409, 3407, 3405, 3404, 3402,
    3400, 3398, 3396, 3395, 3393, 3391, 3389, 3387, 3386, 3384, 3382, 3380, 3378, 3377, 3375, 3373,
    3371, 3369, 3367, 3366, 3364, 3362, 3360, 3358, 3356, 3355, 3353, 3351, 3349, 3347, 3345, 3343,
    3342, 3340, 3338, 3336, 3334, 3332, 3330, 3329, 3327, 3325, 3323, 3321, 3319, 3317, 3315, 3313,
    3312, 3310, 3308, 3306, 3304, 3302, 3300, 3298, 3296, 3294, 3293, 3291, 3289, 3287, 3285, 3283,
    3281, 3279, 3277, 3275, 3273, 3271, 3269, 3268, 3266, 3264, 3262, 3260, 3258, 3256, 3254, 3252,
    3250, 3248, 3246, 3244, 3242, 3240, 3238, 3236, 3234, 3232, 3230, 3228, 3226, 3224, 3222, 3220,
    3218, 3216, 3214, 3212, 3210, 3208, 3206, 3204, 3202, 3200, 3198, 3196, 3194, 3192, 3190, 3188,
    3186, 3184, 3182, 3180, 3178, 3176, 3174, 3172, 3170, 3168, 3166, 3164, 3162, 3160, 3158, 3156,
    3154, 3152, 3150, 3148, 3146, 3143, 3141, 3139, 3137, 3135, 3133, 3131, 3129, 3127, 3125, 3123,
    3121, 3119, 3117, 3114, 3112, 3110, 3108, 3106, 3104, 3102, 3100, 3098, 3096, 3093, 3091, 3089,
    3087, 3085, 3083, 3081, 3079, 3077, 3074, 3072, 3070, 3068, 3066, 3064, 3062, 3059, 3057, 3055,
    3053, 3051, 3049, 3047, 3044, 3042, 3040, 3038, 3036, 3034, 3032, 3029, 3027, 3025, 3023, 3021,
    3019, 3016, 3014, 3012, 3010, 3008, 3005, 3003, 3001, 2999, 2997, 2994, 2992, 2990, 2988, 2986,
    2983, 2981, 2979, 2977, 2975, 2972, 2970, 2968, 2966, 2964, 2961, 2959, 2957, 2955, 2952, 2950,
    2948, 2946, 2944, 2941, 2939, 2937, 2935, 2932, 2930, 2928, 2926, 2923, 2921, 2919, 2917, 2914,
    2912, 2910, 2908, 2905, 2903, 2901, 2898, 2896, 2894, 2892, 2889, 2887, 2885, 2882, 2880, 2878,
    2876, 2873, 2871, 2869, 2866, 2864, 2862, 2860, 2857, 2855, 2853, 2850, 2848, 2846, 2843, 2841,
    2839, 2836, 2834, 2832, 2829, 2827, 2825, 2822, 2820, 2818, 2815, 2813, 2811, 2808, 2806, 2804,
    2801, 2799, 2797, 2794, 2792, 2790, 2787, 2785, 2783, 2780, 2778, 2776, 2773, 2771, 2768, 2766,
    2764, 2761, 2759, 2757, 2754, 2752, 2749, 2747, 2745, 2742, 2740, 2737, 2735, 2733, 2730, 2728,
    2725, 2723, 2721, 2718, 2716, 2713, 2711, 2709, 2706, 2704, 2701, 2699, 2697, 2694, 2692, 2689,
    2687, 2684, 2682, 2680, 2677, 2675, 2672, 2670, 2667, 2665, 2662, 2660, 2658, 2655, 2653, 2650,
    2648, 2645, 2643, 2640, 2638, 2635, 2633, 2631, 2628, 2626, 2623, 2621, 2618, 2616, 2613, 2611,
    2608, 2606, 2603, 2601, 2598, 2596, 2593, 2591, 2588, 2586, 2583, 2581, 2578, 2576, 2573, 2571,
    2568, 2566, 2563, 2561, 2558, 2556, 2553, 2551, 2548, 2546, 2543, 2541, 2538, 2536, 2533, 2531,
    2528, 2526, 2523, 2521, 2518, 2515, 2513, 2510, 2508, 2505, 2503, 2500, 2498, 2495, 2493, 2490,
    2487, 2485, 2482, 2480, 2477, 2475, 2472, 2470, 2467, 2464, 2462, 2459, 2457, 2454, 2452, 2449,
    2446, 2444, 2441, 2439, 2436, 2433, 2431, 2428, 2426, 2423, 2420, 2418, 2415, 2413, 2410, 2408,
    2405, 2402, 2400, 2397, 2394, 2392, 2389, 2387, 2384, 2381, 2379, 2376, 2374, 2371, 2368, 2366,
    2363, 2360, 2358, 2355, 2353, 2350, 2347, 2345, 2342, 2339, 2337, 2334, 2331, 2329, 2326, 2323,
    2321, 2318, 2316, 2313, 2310, 2308, 2305, 2302, 2300, 2297, 2294, 2292, 2289, 2286, 2284, 2281,
    2278, 2276, 2273, 2270, 2268, 2265, 2262, 2259, 2257, 2254, 2251, 2249, 2246, 2243, 2241, 2238,
    2235, 2233, 2230, 2227, 2224, 2222, 2219, 2216, 2214, 2211, 2208, 2206, 2203, 2200, 2197, 2195,
    2192, 2189, 2187, 2184, 2181, 2178, 2176, 2173, 2170, 2167, 2165, 2162, 2159, 2157, 2154, 2151,
    2148, 2146, 2143, 2140, 2137, 2135, 2132, 2129, 2126, 2124, 2121, 2118, 2115, 2113, 2110, 2107,
    2104, 2102, 2099, 2096, 2093, 2091, 2088, 2085, 2082, 2079, 2077, 2074, 2071, 2068, 2066, 2063,
    2060, 2057, 2054, 2052, 2049, 2046, 2043, 2041, 2038, 2035, 2032, 2029, 2027, 2024, 2021, 2018,
    2015, 2013, 2010, 2007, 2004, 2001, 1999, 1996, 1993, 1990, 1987, 1984, 1982, 1979, 1976, 1973,
    1970, 1968, 1965, 1962, 1959, 1956, 1953, 1951, 1948, 1945, 1942, 1939, 1936, 1934, 1931, 1928,
    1925, 1922, 1919, 1917, 1914, 1911, 1908, 1905, 1902, 1900, 1897, 1894, 1891, 1888, 1885, 1882,
    1880, 1877, 1874, 1871, 1868, 1865, 1862, 1860, 1857, 1854, 1851, 1848, 1845, 1842, 1839, 1837,
    1834, 1831, 1828, 1825, 1822, 1819, 1816, 1814, 1811, 1808, 1805, 1802, 1799, 1796, 1793, 1790,
    1788, 1785, 1782, 1779, 1776, 1773, 1770, 1767, 1764, 1761, 1759, 1756, 1753, 1750, 1747, 1744,
    1741, 1738, 1735, 1732, 1729, 1726, 1724, 1721, 1718, 1715, 1712, 1709, 1706, 1703, 1700, 1697,
    1694, 1691, 1688, 1686, 1683, 1680, 1677, 1674, 1671, 1668, 1665, 1662, 1659, 1656, 1653, 1650,
    1647, 1644, 1641, 1639, 1636, 1633, 1630, 1627, 1624, 1621, 1618, 1615, 1612, 1609, 1606, 1603,
    1600, 1597, 1594, 1591, 1588, 1585, 1582, 1579, 1576, 1573, 1570, 1567, 1564, 1562, 1559, 1556,
    1553, 1550, 1547, 1544, 1541, 1538, 1535, 1532, 1529, 1526, 1523, 1520, 1517, 1514, 1511, 1508,
    1505, 1502, 1499, 1496, 1493, 1490, 1487, 1484, 1481, 1478, 1475, 1472, 1469, 1466, 1463, 1460,
    1457, 1454, 1451, 1448, 1445, 1442, 1439, 1436, 1433, 1430, 1427, 1424, 1421, 1418, 1415, 1412,
    1409, 1406, 1403, 1400, 1397, 1394, 1390, 1387, 1384, 1381, 1378, 1375, 1372, 1369, 1366, 1363,
    1360, 1357, 1354, 1351, 1348, 1345, 1342, 1339, 1336, 1333, 1330, 1327, 1324, 1321, 1318, 1315,
    1312, 1308, 1305, 1302, 1299, 1296, 1293, 1290, 1287, 1284, 1281, 1278, 1275, 1272, 1269, 1266,
    1263, 1260, 1257, 1253, 1250, 1247, 1244, 1241, 1238, 1235, 1232, 1229, 1226, 1223, 1220, 1217,
    1214, 1211, 1207, 1204, 1201, 1198, 1195, 1192, 1189, 1186, 1183, 1180, 1177, 1174, 1171, 1167,
    1164, 1161, 1158, 1155, 1152, 1149, 1146, 1143, 1140, 1137, 1133, 1130, 1127, 1124, 1121, 1118,
    1115, 1112, 1109, 1106, 1103, 1099, 1096, 1093, 1090, 1087, 1084, 1081, 1078, 1075, 1072, 1068,
    1065, 1062, 1059, 1056, 1053, 1050, 1047, 1044, 1040, 1037, 1034, 1031, 1028, 1025, 1022, 1019,
    1016, 1012, 1009, 1006, 1003, 1000, 997,  994,  991,  987,  984,  981,  978,  975,  972,  969,
    966,  962,  959,  956,  953,  950,  947,  944,  941,  937,  934,  931,  928,  925,  922,  919,
    915,  912,  909,  906,  903,  900,  897,  894,  890,  887,  884,  881,  878,  875,  872,  868,
    865,  862,  859,  856,  853,  850,  846,  843,  840,  837,  834,  831,  827,  824,  821,  818,
    815,  812,  809,  805,  802,  799,  796,  793,  790,  786,  783,  780,  777,  774,  771,  768,
    764,  761,  758,  755,  752,  749,  745,  742,  739,  736,  733,  730,  726,  723,  720,  717,
    714,  711,  707,  704,  701,  698,  695,  692,  688,  685,  682,  679,  676,  673,  669,  666,
    663,  660,  657,  653,  650,  647,  644,  641,  638,  634,  631,  628,  625,  622,  619,  615,
    612,  609,  606,  603,  599,  596,  593,  590,  587,  584,  580,  577,  574,  571,  568,  564,
    561,  558,  555,  552,  548,  545,  542,  539,  536,  533,  529,  526,  523,  520,  517,  513,
    510,  507,  504,  501,  497,  494,  491,  488,  485,  481,  478,  475,  472,  469,  465,  462,
    459,  456,  453,  449,  446,  443,  440,  437,  433,  430,  427,  424,  421,  417,  414,  411,
    408,  405,  401,  398,  395,  392,  389,  385,  382,  379,  376,  373,  369,  366,  363,  360,
    357,  353,  350,  347,  344,  341,  337,  334,  331,  328,  325,  321,  318,  315,  312,  309,
    305,  302,  299,  296,  292,  289,  286,  283,  280,  276,  273,  270,  267,  264,  260,  257,
    254,  251,  248,  244,  241,  238,  235,  232,  228,  225,  222,  219,  215,  212,  209,  206,
    203,  199,  196,  193,  190,  187,  183,  180,  177,  174,  170,  167,  164,  161,  158,  154,
    151,  148,  145,  142,  138,  135,  132,  129,  125,  122,  119,  116,  113,  109,  106,  103,
    100,  97,   93,   90,   87,   84,   80,   77,   74,   71,   68,   64,   61,   58,   55,   51,
    48,   45,   42,   39,   35,   32,   29,   26,   23,   19,   16,   13,   10,   6,    3,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};
