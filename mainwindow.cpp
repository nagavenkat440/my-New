
#include "mainwindow.h"
#include "advantechcardsinterface.h"
#include "mainwindow.h"
#include "qserialwork_uport.h"
#include "reportgenerator.h"
#include "reporttemplates.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDesktopServices>
#include <QDial>
#include <QPainter>
#include <QProgressDialog>
#include <QSerialPortInfo>
#include <QStyleOptionSlider>
#include <QTimer>
#include <QUrl>
#define GBC "color: rgb(0,0,0); background-color: rgb(0,255,127);"
#define RBC "background-color:rgb(255, 7, 7);color:black"
#define YBC "color:black;background-color: rgb(255, 255, 0);color:rbg(0,0,0)"
#define Grey "color:black;background-color: rgb(232,232,232)"
#define blue "color: rgb(255, 255, 255);background-color: rgb(14, 120, 157); "
#include "QDir"
#include "bittest_logger.h"
#include "qdatetime.h"
#include "qserialwork_bittest.h"
#include "qserialwork_currentsensor.h"
#include "qthread.h"
#include "sru_logger.h"
#include <bdaqctrl.h>
//#include <cstring>
#include <niScope.h>
#include <windows.h>
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImage>
#include <QMessageBox>
#include <QMetaType>
#include <QPainter>
#include <QPixmap>
#include <QProcess>
#include <QScreen>
#include <QSerialPortInfo>
#include <QTimer>
#include <QVector>

#include "crcutility.h"
#include "qserialwork_uport.h"

#include <windows.h>
#include <QDateTime>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImage>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QScreen>

#include <QDebug>

#include <QDebug>

#include "qpainter.h"
#include "qtablewidget.h"
#include <QAxObject>
#include <QComboBox>
#include <QDoubleValidator>
#include <QHeaderView>
#include <QObject>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>

#include <QStyledItemDelegate>

#include "niScope.h" // NI-SCOPE API
//#include <visa.h>    // only for basic VISA types if you include them elsewhere

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <numeric>
#include <vector>

#include "qcustomplot.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

//#include "niScope.h"

using namespace Automation::BDaq;

#define TOLERANCE_1 0.1
#define TOLERANCE_2 0.2

Q_DECLARE_METATYPE(QVector<double>)

QString hexMessage, formattedUSBPat1, formattedUSBPat2;
QString ch1_tx, ch2_tx, ch1_rx, ch2_rx;
extern QByteArray fixedData, recv_data;
QString hexString1, hexString2;
QString CC_Ch1, CC_Ch2, RX1_Pat1, RX1_Pat2, RX2_Pat1, RX2_Pat2;
QString rs3, rs2, rs28, rs16, rs_32, rs_28, rs1, rs5, rs_5, rsplus5, rs422_r1, rs422_r2, Ex_28,
    rsV5, rsI5, rsNV5, rsNI5, rsV3, rsI3, ext_flash_crc, ext_flash_crc2, formatted, formatted2,
    Bit_usb_data, Bit_usb_data1;
QString DC_L10_5V, L10_I5V, DC_L100_5V, L100_I5V, DC_L10_N5V, L10_IN5V, DC_L100_N5V, L100_IN5V,
    DC_L10_3p3V, L10_I3p3V, DC_L100_3p3V, L100_I3p3V;
QString R1, R2, R3, R4;
QString ResultMax_5V, ResultMin_5V, ResultMax_N_5V, ResultMin_N_5V, ResultMax_3p3V, ResultMin_3p3V;
//QString CC_ISO_3p3, CC_ISO_5V, CC_ISO_N5V, Iso_3R, Iso_5R, Iso_N5R;
QString voltageValue, LRU_data, expectedBytes, observedBytes;
QString Rotary_S1, Rotary_S2, Rotary_S3, Rotary_S1_Result, Rotary_S2_Result, Rotary_S3_Result;
QString RotaryS1, RotaryS2, RotaryS3;
QString SRU_Dis_out1, SRU_Dis_out2, SRU_Dis_out3, SRU_Dis_out4, SRU_Dis_out5, Dis_Out1_ON,
    Dis_Out2_ON, Dis_Out3_ON, Dis_Out4_ON, Dis_Out5_ON, Dis_In1_ON, Dis_In2_ON, Dis_In3_ON;
QString SRU_Abort_ON, SRU_Abort_OFF, SRU_Abort_R, SRU_Prep_ON, SRU_Prep_OFF, SRU_Prep_R,
    SRU_ReadyI_ON, SRU_ReadyI_OFF, SRU_ReadyI_R;
QString Dis_Out_R1, Dis_Out_R2, Dis_Out_R3, Dis_Out_R4, Dis_Out_R5;
QString SRU_Dis_In1, SRU_Dis_In2, SRU_Dis_In3, Dis_In_R1, Dis_In_R2, Dis_In_R3;
QString rs422_result, ObservCRC, l_Usb_p1, l_Usb_p2;
QString Display1, Display2, Display3, D1_Status, D2_Status, D3_Status;
extern QString result;
QString str1, str2, str3, str4, str5V, str5I, strNV5, strNI5, strV3, strI3;
QString str1_I, str2_I, str3_I, str4_I;
QString maxResult5V, minResult5V, maxResultN5V, minResultN5V, maxResult3p3V, minResult3p3V;
extern uint32_t outputs, Inputs;
double card1op_ch1, card1op_ch2;
double card2op_ch1, card2op_ch2;
double ip_ch1, ip_ch2, ip_ch3, ip_ch4, ip_ch5, ip_ch6, ip_ch7, ip_ch8, ip_ch9;
int card1_5856, card2_5856;
int rep_flag, rep_flag1, rep_flag2, rep_flag3, rep_flag4, rep_flag5, rep_f;
BinFileTx g_BinFileTx;
TP_Config g_TP_Config;
Sty_in_Boot g_Sty_in_Boot;
FlashErase g_FlashErase;
AppSigDword g_AppSigDword;
AppCrcVerify g_AppCrcVerify;
ReadDataExtFlash g_ReadDataExtFlash;
ExtFlashCRC g_ExtFlashCRC;
SRU_SwitchSTS g_SRU_SwitchSTS;
SetDAC_Value g_SetDAC_Value;
Moxa_port g_Moxa_port1;
Moxa_port g_Moxa_port2;
RunningAverage g_RunningAverage;
ADC_BIT_TEST g_ADC_BIT_TEST;
ADC_SelfTest g_ADC_Card2_BitTest;
RS422_TestPacket g_RS422_TestPacket;
Momentary_Switch_Status g_Momentary_Switch_Status;
DIS_OutputsBIT_TEST g_DIS_OutputsBIT_TEST;
DIS_InputsBIT_TEST g_DIS_InputsBIT_TEST;
CRC_BIT_TEST g_CRC_BIT_TEST;
Post_Status_data g_Post_Status_data;
Time_counter g_Time_counter;
BitTestLogger_PassFailCount g_BitTestLogger_PassFailCount;
TestPoint_Table_Data g_TestPoint_Table_Data[1000];
TestPoint_Table_Data g_TestPoint_Table_Data_Read;
//QTimer *Timer_interrupt;
QTimer *Timer_SRU_DC_DC;
QTimer *Timer_interrupt_USB_Card_Status;
QTimer *Timer_interrupt_Dial1;
QTimer *Timer_interrupt_Dial2;
QTimer *Timer_interrupt_Dial3;
QTimer *StatusTimer;

uint8_t g_mode_flag = 0;
uint8_t g_failure_status_check = 0;
uint8_t g_initiate_sequence_counter = 0;
uint8_t g_SRU_CTRL_sequence_counter = 0;
uint8_t g_max_transmit_count_reach = 0;
//const uint8_t MAX_SEQUENCE_STEP = 10;
bool g_step_in_progress = false;
uint16_t g_Tp_pkt_max_size = 0;
uint16_t g_Tp_pkt_tx_cnt = 0;
uint16_t g_counter_Tp_status = 0;
uint16_t g_TestPointNo = 0;
QString dir;
uint16_t guiCRC_ATE = 0;
// Declare the progress dialog globally or as a member variable
QProgressDialog *progressDialog = nullptr;
QProgressDialog *progressDialog1 = nullptr;

QString html;
bool Bittest_flag = false;
QStringList knownDevices;
ViReal64 maxVal;
ViReal64 minVal;
uint8_t const1 = 0;
uint8_t g_ExternalFlashData[1025];

uint16_t l_counter = 0;
uint16_t l_counter2 = 0;

QVector<QLineEdit *> outputLines;
QVector<QLineEdit *> resultLines;
QVector<QLineEdit *> SRU_output;
QVector<QLineEdit *> SRU_result;
QString fullLogEntry;
QStringList items;

ViSession vi = VI_NULL;

// -------- Error helper (prints extended driver message) ----------
static void failEx(const char *where, ViSession vi, ViStatus st)
{
    char msg[1024] = {0};
    niScope_GetErrorMessage(vi, st, sizeof msg, msg);
    qDebug("%s failed\nstatus=0x%08X : %s\n", where, (unsigned) st, msg);
    ViStatus primary = 0;
    ViChar elaboration[1024] = {0};
    if (niScope_GetError(vi, &primary, sizeof(elaboration), elaboration) >= VI_SUCCESS) {
        qDebug("Detail: %s\n", elaboration);
    }
}

// -------- Frequency estimate via zero-crossing (sub-sample) ----------
static double estimateFreqZeroCrossing(
    const std::vector<double> &y, double t0, double dt, int startIdx, int endIdx)
{
    // Detrend using mean over [startIdx, endIdx)
    if (endIdx - startIdx < 4)
        return std::numeric_limits<double>::quiet_NaN();
    double mean = std::accumulate(y.begin() + startIdx, y.begin() + endIdx, 0.0)
                  / double(endIdx - startIdx);

    // Build (time, value-mean) and find zero crossings with linear interpolation
    struct Crossing
    {
        double t;
        int dir;
    };
    std::vector<Crossing> zc;
    zc.reserve((endIdx - startIdx) / 2);

    auto sgn = [](double v) { return (v > 0) - (v < 0); };

    int prevSign = 0;
    double prevVal = y[startIdx] - mean;
    prevSign = sgn(prevVal);

    for (int i = startIdx + 1; i < endIdx; ++i) {
        double v = y[i] - mean;
        int cs = sgn(v);
        if (cs == 0) { // exact zero - treat as crossing
            zc.push_back({t0 + i * dt, 0});
        } else if (prevSign != 0 && cs != prevSign) {
            // interpolate crossing between (i-1, prevVal) and (i, v)
            double t1 = t0 + (i - 1) * dt;
            double frac = std::fabs(v - prevVal) > 0 ? (0 - prevVal) / (v - prevVal) : 0.5;
            double tc = t1 + frac * dt;
            int dir = (v > prevVal) ? +1 : -1; // rising (+) or falling (-)
            zc.push_back({tc, dir});
        }
        prevVal = v;
        prevSign = cs;
    }
    if (zc.size() < 2)
        return std::numeric_limits<double>::quiet_NaN();

    // Use only same-direction crossings (rising→rising or falling→falling) to get full periods
    std::vector<double> riseTimes, fallTimes;
    for (size_t i = 1; i < zc.size(); ++i) {
        if (zc[i].dir != 0 && zc[i - 1].dir == zc[i].dir) {
            double T = zc[i].t - zc[i - 1].t;
            if (T > 0) {
                if (zc[i].dir > 0)
                    riseTimes.push_back(T);
                else
                    fallTimes.push_back(T);
            }
        }
    }
    auto avg = [](const std::vector<double> &v) -> double {
        if (v.empty())
            return std::numeric_limits<double>::quiet_NaN();
        double s = std::accumulate(v.begin(), v.end(), 0.0);
        return s / double(v.size());
    };
    double Tr = avg(riseTimes);
    double Tf = avg(fallTimes);

    double T = std::numeric_limits<double>::quiet_NaN();
    if (std::isfinite(Tr) && std::isfinite(Tf))
        T = 0.5 * (Tr + Tf);
    else if (std::isfinite(Tr))
        T = Tr;
    else if (std::isfinite(Tf))
        T = Tf;

    if (!std::isfinite(T) || T <= 0)
        return std::numeric_limits<double>::quiet_NaN();
    return 1.0 / T;
}

// 1–2–5 ladder
static double next125up(double v)
{
    if (v <= 0)
        return 0.1;
    double p = std::pow(10.0, std::floor(std::log10(v)));
    double m = v / p;
    double k = (m <= 1.0) ? 1.0 : (m <= 2.0) ? 2.0 : (m <= 5.0) ? 5.0 : 10.0;
    if (k < 10.0)
        k = (k == 1.0) ? 2.0 : (k == 2.0) ? 5.0 : 10.0;
    else {
        p *= 10.0;
        k = 1.0;
    }
    return k * p;
}
// -------- Plot & save PNG with scope styling and annotations ----------
void saveScopePNG(const std::vector<double> &y,
                  const niScope_wfmInfo &w,
                  const QString &outFile,
                  double voltsPerDiv = 0.010, // 10 mV/div (was 0.100)
                  double timePerDiv = 5e-6,   // 20 µs/div
                  double settleFrac = 0.20,   // ignore first 10%
                  int widthPx = 1400,
                  int heightPx = 700,
                  double *freqHzOut = nullptr,
                  double overrideFreqHz = std::numeric_limits<double>::quiet_NaN())
{
    //    if (y.empty())
    //        return false;

    const int n = w.actualSamples;
    const double t0 = w.relativeInitialX;
    const double dt = w.xIncrement;

    QVector<double> qx(n), qy(n);
    for (int i = 0; i < n; ++i) {
        qx[i] = t0 + i * dt;
        qy[i] = y[i];
    }

    // Post-settle stats
    int startIdx = std::min<int>(n - 1, std::max<int>(0, static_cast<int>(n * settleFrac)));
    int endIdx = static_cast<int>(n);

    auto mm = std::minmax_element(y.begin() + startIdx, y.begin() + endIdx);

    const double vmin = *mm.first;
    const double vmax = *mm.second;
    const double vpp = vmax - vmin;

    double mean = 0.0;
    if (endIdx > startIdx)
        mean = std::accumulate(y.begin() + startIdx, y.begin() + endIdx, 0.0)
               / double(endIdx - startIdx);

    // Frequency: prefer driver result if provided; else fall back to zero-crossing
    double fz = std::isfinite(overrideFreqHz)
                    ? overrideFreqHz
                    : estimateFreqZeroCrossing(y, t0, dt, startIdx, endIdx);
    if (freqHzOut)
        *freqHzOut = fz;

    // Scope-like 10 divisions
    const double totalTime = timePerDiv * 10.0; // 200 µs
    const double x0 = qx[0];
    const double x1 = x0 + totalTime;
    const double vHalfRange = (voltsPerDiv * 10.0) / 2.0; // ±50 mV about mean

    QCustomPlot plot;
    plot.setGeometry(0, 0, widthPx, heightPx);
    plot.addGraph();
    plot.graph(0)->setData(qx, qy);
    plot.xAxis->setLabel("Time (s)");
    plot.yAxis->setLabel("Voltage (V)");
    plot.xAxis->setRange(x0, x1);
    plot.yAxis->setRange(mean - vHalfRange, mean + vHalfRange);

    //    double margin = 0.10 * (vmax - vmin); // 10% margin
    //    plot.yAxis->setRange(vmin - margin, vmax + margin);

    // Grid (10 divisions)
    auto xTicker = QSharedPointer<QCPAxisTickerFixed>::create();
    xTicker->setTickStep(timePerDiv);
    plot.xAxis->setTicker(xTicker);
    plot.xAxis->grid()->setSubGridVisible(true);
    plot.xAxis->grid()->setPen(QPen(QColor(0, 0, 0, 60)));
    plot.xAxis->grid()->setSubGridPen(QPen(QColor(0, 0, 0, 30)));

    auto yTicker = QSharedPointer<QCPAxisTickerFixed>::create();
    yTicker->setTickStep(voltsPerDiv);
    plot.yAxis->setTicker(yTicker);
    plot.yAxis->grid()->setSubGridVisible(true);
    plot.yAxis->grid()->setPen(QPen(QColor(0, 0, 0, 60)));
    plot.yAxis->grid()->setSubGridPen(QPen(QColor(0, 0, 0, 30)));

    // Midline (mean)
    QCPItemStraightLine *midLine = new QCPItemStraightLine(&plot);
    midLine->point1->setType(QCPItemPosition::ptPlotCoords);
    midLine->point2->setType(QCPItemPosition::ptPlotCoords);
    midLine->point1->setCoords(x0, mean);
    midLine->point2->setCoords(x1, mean);
    midLine->setPen(QPen(Qt::DashLine));

    // Min/Max markers
    int idxMin = static_cast<int>(std::distance(y.begin(), mm.first));
    int idxMax = static_cast<int>(std::distance(y.begin(), mm.second));

    QCPItemTracer *trMin = new QCPItemTracer(&plot);
    trMin->setGraph(plot.graph(0));
    trMin->setGraphKey(qx[idxMin]);
    trMin->setInterpolating(false);
    trMin->setStyle(QCPItemTracer::tsCrosshair);
    trMin->setSize(7);

    QCPItemTracer *trMax = new QCPItemTracer(&plot);
    trMax->setGraph(plot.graph(0));
    trMax->setGraphKey(qx[idxMax]);
    trMax->setInterpolating(false);
    trMax->setStyle(QCPItemTracer::tsCrosshair);
    trMax->setSize(7);

    // Annotation (min/max/p-p/mean/freq)
    QCPItemText *txt = new QCPItemText(&plot);
    txt->position->setType(QCPItemPosition::ptAxisRectRatio);
    txt->position->setCoords(0.01, 0.02);
    txt->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    QString fstr = std::isfinite(fz) ? QString("%1 kHz").arg(fz / 1e3, 0, 'f', 2) : QString("N/A");
    txt->setText(QString("min = %1 V\nmax = %2 V\np-p = %3 V\nmean = %4 V")
                     .arg(vmin, 0, 'f', 6)
                     .arg(vmax, 0, 'f', 6)
                     .arg(vpp, 0, 'f', 6)
                     .arg(mean, 0, 'f', 6)/*
                     .arg(fstr)*/);
    txt->setPadding(QMargins(6, 4, 6, 4));
    txt->setBrush(QBrush(QColor(255, 255, 255, 200)));
    txt->setPen(QPen(QColor(0, 0, 0, 120)));

    plot.replot();
    plot.savePng(outFile, widthPx, heightPx, 1.0);
}

// thresholds
static constexpr double LIMIT_CAPTURE = 0.150; // capture only when <= ±0.100 V
static constexpr double LIMIT_HARD = 0.200;    // immediate FAIL if any |V| >= 1.000 V

static void acquireAndSaveScopePNG(const QString &pngPath,
                                   double *min,
                                   double *max,
                                   double *Vpp,
                                   double voltsPerDiv = 0.010,
                                   double timePerDiv = 20e-6,
                                   double settleFrac = 0.10)
{
    double vmin2 = 0;
    double vmax2 = 0;
    double vpp2 = 0;
    auto setNaN = [&](double *p) {
        if (p)
            *p = std::numeric_limits<double>::quiet_NaN();
    };

    ViSession vi = VI_NULL;
    char resourceName[] = "Dev1";
    const char *opts = "Simulate=0,RangeCheck=1,RecordCoercions=1";
    ViStatus st = niScope_InitWithOptions(resourceName, VI_TRUE, VI_TRUE, opts, &vi);
    if (st < VI_SUCCESS) {
        std::fprintf(stderr, "Init failed 0x%08X\n", (unsigned) st);
        setNaN(min);
        setNaN(max);
        setNaN(Vpp);
        return;
    }

    const char *ch = "0";
    const ViReal64 Fs = 50e6;
    const ViInt32 N = 10000; // ~200 us
    std::vector<double> y(N);
    niScope_wfmInfo info[1] = {};

    // start small, auto-range up if clipping
    double range = 0.1; // 0.1 V full-scale (10 mV/div × 10)
    const int MAX_RANGE_TRIES = 5;

    // wait until stable ≤ ±0.100 V (or fail if ≥1.0 V)
    const qint64 timeoutMs = 5000; // total wait budget
    const int maxAttempts = 2000;  // safety cap
    QElapsedTimer timer;
    timer.start();

    bool didCapture = false;

    for (int attempt = 0; attempt < maxAttempts && timer.elapsed() < timeoutMs; ++attempt) {
        // inner loop: do one acquisition, up-range if clipping
        for (int rtry = 0; rtry < MAX_RANGE_TRIES; ++rtry) {
            // vertical config
            st = niScope_ConfigureVertical(vi, ch, range, 0.0, NISCOPE_VAL_AC, 1.0, VI_TRUE);
            if (st < VI_SUCCESS)
                failEx("ConfigureVertical", vi, st);

            // horizontal config
            st = niScope_ConfigureHorizontalTiming(vi, Fs, N, 0.5, 1, VI_FALSE);
            if (st < VI_SUCCESS)
                failEx("ConfigureHorizontalTiming", vi, st);

            // acquire
            st = niScope_ConfigureTriggerImmediate(vi);
            if (st < VI_SUCCESS)
                failEx("ConfigureTriggerImmediate", vi, st);
            st = niScope_InitiateAcquisition(vi);
            if (st < VI_SUCCESS)
                failEx("InitiateAcquisition", vi, st);
            st = niScope_Fetch(vi, ch, 5.0, N, y.data(), info);
            if (st < VI_SUCCESS)
                failEx("Fetch", vi, st);

            // detect clipping
            const double rail = range * 0.5;
            const double eps = range * 0.005; // 0.5% FS
            auto mm = std::minmax_element(y.begin(), y.begin() + info[0].actualSamples);
            double vmin = *mm.first, vmax = *mm.second;

            bool clipped = (vmax >= (rail - eps)) || (vmin <= (-rail + eps));
            if (!clipped)
                break;

            //            double old = range;
            range = next125up(range);
            //            std::printf("Clipping (vmin=%.6f, vmax=%.6f @ ±%.3fmV) -> range up: %.3f -> %.3f V\n",
            //                        vmin,
            //                        vmax,
            //                        rail * 1e3,
            //                        old,
            //                        range);
        }

        // compute post-settle stats
        const int startIdx = std::min<int>(info[0].actualSamples - 1,
                                           std::max<int>(0,
                                                         int(info[0].actualSamples * settleFrac)));
        auto mm2 = std::minmax_element(y.begin() + startIdx, y.begin() + info[0].actualSamples);
        vmin2 = *mm2.first;
        vmax2 = *mm2.second;
        vpp2 = vmax2 - vmin2;

        double mean2 = 0.0;
        if (info[0].actualSamples > startIdx) {
            mean2 = std::accumulate(y.begin() + startIdx, y.begin() + info[0].actualSamples, 0.0)
                    / double(info[0].actualSamples - startIdx);
        }

        // immediate FAIL if any sample magnitude >= 1.0 V
        if (std::fabs(vmax2) >= LIMIT_HARD || std::fabs(vmin2) >= LIMIT_HARD) {
            qWarning("FAIL: observed >= 1.000 V (vmin=%.6f, vmax=%.6f). Not capturing.",
                     vmin2,
                     vmax2);
            //            setNaN(min);
            //            setNaN(max);
            //            setNaN(Vpp);
            if (min)
                *min = vmin2;
            if (max)
                *max = vmax2;
            if (Vpp)
                *Vpp = vpp2;
            niScope_close(vi);
            //            return;
        }

        // check stability against ±0.100 V band (use half-amplitude = max deviation from mean)
        const double devTop = vmax2 - mean2;
        const double devBot = mean2 - vmin2;
        const double max_dev = std::max(devTop, devBot);

        if (max_dev <= LIMIT_CAPTURE) {
            // PASS & capture exactly now
            if (min)
                *min = vmin2;
            if (max)
                *max = vmax2;
            if (Vpp)
                *Vpp = vpp2;

            double fHzUsed = std::numeric_limits<double>::quiet_NaN();
            // Hint the frequency if you like (optional): leave as NaN to auto-estimate in save
            /*bool ok = */ saveScopePNG(y,
                                        info[0],
                                        pngPath,
                                        /*voltsPerDiv*/ voltsPerDiv,
                                        /*timePerDiv*/ timePerDiv,
                                        /*settleFrac*/ settleFrac,
                                        /*width*/ 1400,
                                        /*height*/ 700,
                                        &fHzUsed,
                                        /*overrideFreqHz*/ std::numeric_limits<double>::quiet_NaN());
            //            if (ok)
            //                std::fprintf(stdout,
            //                             "PASS: Saved PNG: %s (max_dev=%.6f <= 0.100)\n",
            //                             pngPath.toUtf8().constData(),
            //                             max_dev);
            //            else
            //                std::fprintf(stderr, "PASS: PNG save failed (max_dev=%.6f)\n", max_dev);

            didCapture = true;
            break;
        }

        // not yet stable; brief pause to avoid hammering
        QThread::msleep(30);
    }

    if (!didCapture) {
        qWarning("Timed out waiting for ripple to settle within ±0.100 V. Not capturing.");
        //        setNaN(min);
        //        setNaN(max);
        //        setNaN(Vpp);
        if (min)
            *min = vmin2;
        if (max)
            *max = vmax2;
        if (Vpp)
            *Vpp = vpp2;
    }

    niScope_close(vi);
}

//    // Acquire with auto range-up if clipping is detected
//    static void acquireAndSaveScopePNG(const QString &pngPath,
//                                       double *min,
//                                       double *max,
//                                       double *Vpp,
//                                       double voltsPerDiv = 0.010, // 10 mV/div (desired view)
//                                       double timePerDiv = 20e-6,
//                                       double settleFrac = 0.10)
//    {
//        ViSession vi = VI_NULL;
//        char resourceName[] = "Dev1";
//        const char *opts = "Simulate=0,RangeCheck=1,RecordCoercions=1";
//        ViStatus st = niScope_InitWithOptions(resourceName, VI_TRUE, VI_TRUE, opts, &vi);
//        if (st < VI_SUCCESS) {
//            std::fprintf(stderr, "Init failed 0x%08X\n", (unsigned) st);
//            return;
//        }

//        const char *ch = "0";
//        const ViReal64 Fs = 50e6;
//        const ViInt32 N = 10000; // 200 µs total

//        // Start from 0.1 V total (10 mV/div × 10)
//        double range = 0.1;
//        const int MAX_TRIES = 5;

//        std::vector<double> y(N);
//        niScope_wfmInfo info[1] = {};
//        bool clipped = false;

//        for (int attempt = 0; attempt < MAX_TRIES; ++attempt) {
//            // Configure vertical with the current range (AC coupling, 1x)
//            st = niScope_ConfigureVertical(vi, ch, range, 0.0, NISCOPE_VAL_AC, 1.0, VI_TRUE);
//            if (st < VI_SUCCESS)
//                failEx("ConfigureVertical", vi, st);

//            // Horizontal
//            st = niScope_ConfigureHorizontalTiming(vi, Fs, N, 0.5, 1, VI_FALSE);
//            if (st < VI_SUCCESS)
//                failEx("ConfigureHorizontalTiming", vi, st);

//            // Trigger + acquire + fetch
//            st = niScope_ConfigureTriggerImmediate(vi);
//            if (st < VI_SUCCESS)
//                failEx("ConfigureTriggerImmediate", vi, st);
//            st = niScope_InitiateAcquisition(vi);
//            if (st < VI_SUCCESS)
//                failEx("InitiateAcquisition", vi, st);
//            st = niScope_Fetch(vi, ch, 5.0, N, y.data(), info);
//            if (st < VI_SUCCESS)
//                failEx("Fetch", vi, st);

//            // Check clipping near rails (±range/2). Use a small epsilon for floating compare.
//            const double rail = range * 0.5;
//            const double eps = range * 0.005; // 0.5% of full scale
//            auto mm = std::minmax_element(y.begin(), y.begin() + info[0].actualSamples);
//            double vmin = *mm.first, vmax = *mm.second;

//            clipped = (vmax >= (rail - eps)) || (vmin <= (-rail + eps));
//            if (!clipped) {
//                // good capture; continue to measurements/PNG below
//                break;
//            }

//            // Range up and retry
//            double old = range;
//            range = next125up(range);
//            std::printf("Clipping detected (vmin=%.6f, vmax=%.6f @ ±%.3fmV). "
//                        "Ranging up: %.3f V -> %.3f V\n",
//                        vmin,
//                        vmax,
//                        rail * 1e3,
//                        old,
//                        range);
//        }

//        //  read frequency from driver
//        ViReal64 freqHz_param = std::numeric_limits<double>::quiet_NaN();
//        st = niScope_FetchMeasurement(vi, ch, 5.0, NISCOPE_VAL_FREQUENCY, &freqHz_param);
//        if (st < VI_SUCCESS) {
//            char msg[256] = {0};
//            niScope_GetErrorMessage(vi, st, sizeof msg, msg);
//            std::fprintf(stderr, "FetchMeasurement(FREQUENCY) warn: 0x%08X : %s\n", (unsigned) st, msg);
//            freqHz_param = std::numeric_limits<double>::quiet_NaN();
//        }

//        // Stats for console
//        int startIdx = std::min<int>(info[0].actualSamples - 1,
//                                     std::max<int>(0,
//                                                   static_cast<int>(info[0].actualSamples
//                                                                    * settleFrac)));
//        auto mm2 = std::minmax_element(y.begin() + startIdx, y.begin() + info[0].actualSamples);
//        double vmin2 = *mm2.first, vmax2 = *mm2.second, vpp2 = vmax2 - vmin2;
//        double mean2 = 0.0;
//        *min = vmin2;
//        *max = vmax2;
//        *Vpp = vpp2;
//        if (info[0].actualSamples > startIdx) {
//            mean2 = std::accumulate(y.begin() + startIdx, y.begin() + info[0].actualSamples, 0.0)
//                    / double(info[0].actualSamples - startIdx);
//        }
//        qDebug("Final range used: %.3f V  -> Ripple: min=%.6f V, max=%.6f V, p-p=%.6f V, mean=%.6f V\n",
//               range,
//               vmin2,
//               vmax2,
//               vpp2,
//               mean2);

//        /////////----------------------------------------------------///////////------------////////
//        // --- choose display band (half-range) based on measured ripple ---
//        //    const double HALF_150 = 0.150; // ±150 mV
//        //    const double HALF_170 = 0.170; // ±170 mV
//        //    const double HALF_200 = 0.200; // ±200 mV (hard limit)

//        //    const double half_measured = 0.5 * vpp2;

//        //    double chosenHalf = HALF_150; // default
//        //    if (half_measured <= HALF_150) {
//        //        chosenHalf = HALF_150; // tightest band
//        //    } else if (half_measured <= HALF_170) {
//        //        chosenHalf = HALF_170; // give a little more
//        //    } else if (half_measured <= HALF_200) {
//        //        chosenHalf = HALF_200; // show full threshold
//        //    } else {
//        //        // Out of spec (> ±200 mV): show at threshold so it’s obvious it spills outside
//        //        chosenHalf = HALF_200;
//        //    }

//        //    // Convert band to volts/div for a 10-division vertical scale
//        //        double voltsPerDiv_for_band = (2.0 * chosenHalf) / 10.0; // e.g. 0.170*2 / 10 = 0.034 V/div

//        //    qDebug("Display band set to ±%.0f mV (%.3f V/div)\n", chosenHalf * 1e3, voltsPerDiv_for_band);

//        /////////----------------------------------------------------///////////------------////////
//        // Save PNG (shows full waveform; autoscale vertically to avoid clipping in the image)
//        double fHzUsed = std::numeric_limits<double>::quiet_NaN();
//        bool ok = saveScopePNG(y,
//                               info[0],
//                               pngPath,
//                               /*voltsPerDiv (for grid only)*/ voltsPerDiv,
//                               /*timePerDiv*/ timePerDiv,
//                               /*settleFrac*/ settleFrac,
//                               /*width*/ 1400,
//                               /*height*/ 700,
//                               &fHzUsed,
//                               /*overrideFreqHz*/ freqHz_param);

//        //    if (std::isfinite(fHzUsed))
//        //        qDebug("Ripple frequency ≈ %.2f kHz\n", fHzUsed / 1e3);
//        //        else
//        //        qDebug("Ripple frequency ≈ N/A\n");

//        if (!ok)
//            std::fprintf(stderr, "Failed to save PNG\n");
//        else
//            std::fprintf(stdout, "Saved PNG: %s\n", pngPath.toUtf8().constData());

//        niScope_close(vi);
//    }

class CenteredItemDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::initStyleOption(option, index);
        option->displayAlignment = Qt::AlignCenter;
    }
};

class DoubleRangeDelegate : public QStyledItemDelegate
{
public:
    explicit DoubleRangeDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {}

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        if (index.row() >= 1) { // from 2nd row onward
            QLineEdit *editor = new QLineEdit(parent);
            QDoubleValidator *validator = new QDoubleValidator(-2.0, 2.0, 2, editor);
            validator->setNotation(QDoubleValidator::StandardNotation);
            editor->setValidator(validator);
            return editor;
        }

        return QStyledItemDelegate::createEditor(parent, option, index);
    }
};

class TopBorderDelegate : public QStyledItemDelegate
{
public:
    TopBorderDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {}

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        QStyledItemDelegate::paint(painter, option, index);

        if (index.row() == 0) { // paint top border on first row only
            painter->save();
            painter->setPen(QPen(Qt::black, 1));
            painter->drawLine(option.rect.topLeft(), option.rect.topRight());
            painter->restore();
        }
    }
};

class FontRespectingDelegate : public QStyledItemDelegate
{
public:
    FontRespectingDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {}
    void paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &idx) const override
    {
        QStyleOptionViewItem option = opt;
        QVariant f = idx.data(Qt::FontRole);
        if (f.canConvert<QFont>())
            option.font = f.value<QFont>();
        QStyledItemDelegate::paint(p, option, idx);
    }
};

/**************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
//, usbPollTimer(new QTimer(this))
//, isUsb5132Connected(false)
//, usbDeviceName("")
{
    ui->setupUi(this);
    ui->groupBox_26->setHidden(true);
    ui->groupBox_DCDC_drop_down->setHidden(true);
    ui->grpbox_LRU->setHidden(true);
    ui->FRONTPANEL_PT->setHidden(false);
    ui->LRU_FPS_txt_gb->setHidden(true);
    ui->label_lru_checks->setHidden(true);
    ui->LRU_VoltageCB->setHidden(true);
    ui->LRU_VoltageCB->setCurrentIndex(2);
    //    ui->Discrete_Inputs_Pb->setHidden(true);
    ui->rd_btn_RotarySwitch_1_2_3->setHidden(true);
    ui->rd_btn_Prep_Switch->setHidden(true);
    ui->rd_btn_Ready_Init_Switch->setHidden(true);
    ui->rd_btn_Abort_Switch->setHidden(true);
    ui->pb_yes_RotarySwitch_1_2_3->setHidden(true);
    ui->pb_no_RotarySwitch_1_2_3->setHidden(true);
    ui->pb_yes_Prep_Switch->setHidden(true);
    ui->pb_no_Prep_Switch->setHidden(true);
    ui->pb_yes_Ready_Init_Switch->setHidden(true);
    ui->pb_no_Ready_Init_Switch->setHidden(true);
    ui->pb_yes_Abort_Switch->setHidden(true);
    ui->pb_no_Abort_Switch->setHidden(true);
    ui->FTU_LRUReport_pb->setHidden(true);
    //------SRU Level
    ui->ControllerCard_GroupBox->setEnabled(false);
    //    ui->plus5_groupBox->setEnabled(false);
    //    ui->minus5_groupBox->setEnabled(false);
    //    ui->groupBox_3P3->setEnabled(false);
    //    ui->displaycard_groupBox->setEnabled(false);
    //    ui->SRU_CTRL_Volt_pb->setEnabled(false);
    //    ui->USB_port->setEnabled(false);

    //    ui->groupBox_rotary_switch_test->setEnabled(false);
    //    ui->groupBox_rs422_loopback->setEnabled(false);
    //    ui->groupBox_abort_readyinit_prep->setEnabled(false);
    //    ui->groupBox_external_flash->setEnabled(false);
    //    ui->displaycard_groupBox->setEnabled(false);
    //    ui->SRU_DCDC_REPORT->setEnabled(false);
    //    ui->SRU_CntrlCard_Report->setEnabled(false);
    //    ui->groupBox_dip_dop_loopback->setEnabled(false);

    /******************** FOR Excel File *******************/
#if 1
    ui->table1_groupBox->setAlignment(Qt::AlignHCenter);
    ui->table2_groupBox->setAlignment(Qt::AlignHCenter);
    ui->table3_groupBox->setAlignment(Qt::AlignHCenter);
    ui->table4_groupBox->setAlignment(Qt::AlignHCenter);
    ui->table5_groupBox->setAlignment(Qt::AlignHCenter);
    ui->table6_groupBox->setAlignment(Qt::AlignHCenter);

    // Add all table widgets to the list, including xls_tableWidget9
    tableWidgets << ui->tableWidget_1 << ui->tableWidget_2 << ui->tableWidget_3 << ui->tableWidget_4
                 << ui->tableWidget_5 << ui->tableWidget_6;

    tableWidgets.clear();
    tableWidgets.append(ui->tableWidget_1); // Sheet 1
    tableWidgets.append(ui->tableWidget_2); // Sheet 2
    tableWidgets.append(ui->tableWidget_3); // Sheet 3
    tableWidgets.append(ui->tableWidget_4); // Sheet 4
    tableWidgets.append(ui->tableWidget_5); // Sheet 5
    tableWidgets.append(ui->tableWidget_6); // Sheet 6

    connect(ui->Import_pb, &QPushButton::clicked, this, &MainWindow::importExcelToMultipleTables);
    connect(ui->Export_pb, &QPushButton::clicked, this, &MainWindow::exportAllTablesToExcel);

    connect(ui->tableWidget_1, &QTableWidget::cellClicked, this, &MainWindow::onTable1CellClicked);
    connect(ui->tableWidget_2, &QTableWidget::cellClicked, this, &MainWindow::onTable2CellClicked);
    connect(ui->tableWidget_3, &QTableWidget::cellClicked, this, &MainWindow::onTable3CellClicked);
    connect(ui->tableWidget_4, &QTableWidget::cellClicked, this, &MainWindow::onTable4CellClicked);
    connect(ui->tableWidget_5, &QTableWidget::cellClicked, this, &MainWindow::onTable5CellClicked);
    connect(ui->tableWidget_6, &QTableWidget::cellClicked, this, &MainWindow::onTable6CellClicked);
#endif
    /***********************************************************/

    //-----temp--
    //    g_SignalGenerator.show();

    BittestLogTimer = new QTimer(this);
    connect(BittestLogTimer, &QTimer::timeout, this, &MainWindow::BittestLogUpdate);

    settingsMonitorTimer = new QTimer(this);
    connect(settingsMonitorTimer, &QTimer::timeout, this, &MainWindow::updateScopeMinMax);
    //  settingsMonitorTimer->start(1); // Poll every 1 second

    //------------------------------------------stm32 current sensor USB Connection--------------------------
    QString BitPortName;
    QStringList ststatus;

    // Scan for USB serial ports
    //    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    //        if (info.description().contains("STM", Qt::CaseInsensitive)
    //            || info.manufacturer().contains("STM", Qt::CaseInsensitive)) {
    //            BitPortName = info.portName();
    //            break; // Use the first matching USB port
    //        }
    //    }

    QString targetSerialNumber = "205038594633"; // set this to the serial you want to detect
                                                 //  ui->tabWidget->removeTab(7);
    ui->tabWidget->removeTab(8);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        // Optional: Print for debugging
        //        qDebug() << "Checking Port:" << info.portName() << "Description:" << info.description()
        //                 << "Manufacturer:" << info.manufacturer()
        //                 << "Serial Number:" << info.serialNumber();

        // Check STM32 description/manufacturer AND serial number
        if ((info.description().contains("STM", Qt::CaseInsensitive)
             || info.manufacturer().contains("STM", Qt::CaseInsensitive))
            && info.serialNumber() == targetSerialNumber) {
            BitPortName = info.portName(); // Store port name
            //            qDebug() << "STM32 device with serial" << targetSerialNumber << "found on port"
            //                     << BitPortName;
            break; // Use the first matching port with this serial
        }
    }

    if (BitPortName.isEmpty()) {
        ststatus << "❌ Not Connected";
    } else {
        //        qDebug() << "STM device found on port:" << BitPortName;
        ststatus << "✅ Connected & Initialized";
    }

    QString stsummary = "Current Monitoring Device Status at Startup:\n\n" + ststatus.join("\n");

    if (BitPortName.isEmpty())
        QMessageBox::warning(this, "Current Monitoring", stsummary);
    else
        QMessageBox::information(this, "Current Monitoring", stsummary);

    //    qDebug() << "Using USB port:" << BitPortName;
    //    QString COMPort = "COM18";
    BitWorker = new SerialWork_Bittest(BitPortName, true);

    connect(BitWorker, &SerialWork_Bittest::msg_process, this, &MainWindow::message_received);

    BitWorker->start();

    //------------------------------------------stm32 current sensor USB Connection--------------------------END--

#if 1
    //////////////////////////////MOXA 1250 /////////////////////////////
    QStringList moxaPorts, mxstatus;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.description().contains("Moxa", Qt::CaseInsensitive)) {
            moxaPorts << info.portName();
        }
    }

    if (moxaPorts.size() < 2) {
        mxstatus << "Not Connected";
        QString mxsummary = "MOXA 1250 Device Status at Startup:\n\n" + mxstatus.join("\n");
        QMessageBox::warning(this, "MOXA 1250 Status", mxsummary);

    } else {
        mxstatus << "✅ Connected & Initialized";
        QString mxsummary = "MOXA 1250 Device Status at Startup:\n\n" + mxstatus.join("\n");
        QMessageBox::information(this, "MOXA 1250 Status", mxsummary);

        QThread *Moxa_port1Thread = new QThread;
        QString port1 = moxaPorts[0];
        qSerialWorkMoxa *Moxa_Port1_worker = new qSerialWorkMoxa(port1);
        Moxa_Port1_worker->moveToThread(Moxa_port1Thread);
        //        connect(Moxa_Port1_worker, &qSerialWork::sig_SerialErrorOccurred, this, &MainWindow::M_SerialErrorOccurred, Qt::QueuedConnection);
        connect(Moxa_port1Thread, &QThread::started, Moxa_Port1_worker, &qSerialWorkMoxa::start);
        connect(Moxa_Port1_worker,
                &qSerialWorkMoxa::Moxa_finished,
                Moxa_port1Thread,
                &QThread::quit);
        connect(Moxa_Port1_worker,
                &qSerialWorkMoxa::Moxa_finished,
                Moxa_Port1_worker,
                &qSerialWorkMoxa::deleteLater);
        connect(Moxa_port1Thread, &QThread::finished, Moxa_port1Thread, &QThread::deleteLater);
        connect(this,
                SIGNAL(Moxa_Port1_serialWrite(const char *, qint64)),
                Moxa_Port1_worker,
                SLOT(Moxa_writeData(const char *, qint64)));
        connect(this,
                SIGNAL(Moxa_port1_sig_serialPort_Close()),
                Moxa_Port1_worker,
                SLOT(Moxa_serialPort_Close()));
        connect(Moxa_Port1_worker,
                &qSerialWorkMoxa::msg_process,
                this,
                &MainWindow::message_received);
        //---------------------------------------------------------------------------------------------
        connect(Moxa_Port1_worker,
                &qSerialWorkMoxa::Moxa_sig_SerialErrorOccurred,
                this,
                &MainWindow::M_SerialErrorOccurred);
        connect(Moxa_Port1_worker,
                &qSerialWorkMoxa::Moxa_sig_SerialAboutToClose,
                this,
                &MainWindow::M_SerialAboutToClose);

        //-------------------------------------------------------------------------------------------
        QThread *Moxa_port2Thread = new QThread;
        QString port2 = moxaPorts[1];
        qSerialWorkMoxa *Moxa_Port2_worker = new qSerialWorkMoxa(port2);
        Moxa_Port2_worker->moveToThread(Moxa_port2Thread);
        //        connect(Moxa_Port1_worker, &qSerialWork::sig_SerialErrorOccurred, this, &MainWindow::M_SerialErrorOccurred, Qt::QueuedConnection);
        connect(Moxa_port2Thread, &QThread::started, Moxa_Port2_worker, &qSerialWorkMoxa::start);
        connect(Moxa_Port2_worker,
                &qSerialWorkMoxa::Moxa_finished,
                Moxa_port2Thread,
                &QThread::quit);
        connect(Moxa_Port2_worker,
                &qSerialWorkMoxa::Moxa_finished,
                Moxa_Port2_worker,
                &qSerialWorkMoxa::deleteLater);
        connect(Moxa_port2Thread, &QThread::finished, Moxa_port2Thread, &QThread::deleteLater);
        connect(this,
                SIGNAL(Moxa_Port2_serialWrite(const char *, qint64)),
                Moxa_Port2_worker,
                SLOT(Moxa_writeData(const char *, qint64)));
        connect(this,
                SIGNAL(Moxa_port2_sig_serialPort_Close()),
                Moxa_Port2_worker,
                SLOT(Moxa_serialPort_Close()));
        connect(Moxa_Port2_worker,
                &qSerialWorkMoxa::msg_process,
                this,
                &MainWindow::message_received);
        //-------------------------------------------------------------------------------------------
        //        serialPort = new QSerialPort(this);
        //        connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(Moxa_Port2_worker,
                &qSerialWorkMoxa::Moxa_sig_SerialErrorOccurred,
                this,
                &MainWindow::M_SerialErrorOccurred);
        connect(Moxa_Port2_worker,
                &qSerialWorkMoxa::Moxa_sig_SerialAboutToClose,
                this,
                &MainWindow::M_SerialAboutToClose);
        Moxa_port1Thread->start();
        Moxa_port2Thread->start();
    }
    //*******************************Current Sensor Serial*************************/

#endif

#if 1
    QStringList statusListNI;

    if (findAllNIScopeDevices()) {
        statusListNI << QString("✅ %1: Connected & Initialized").arg(detectedDevice);
        usb5132_card_success = 1;
    } else {
        statusListNI << "❌ Not Connected";
        usb5132_card_success = 0;
    }

    QString summaryNI = "USB-5132 Device Status at Startup:\n\n" + statusListNI.join("\n");

    if (statusListNI.first().startsWith("✅"))
        QMessageBox::information(this, "USB-5132 Status", summaryNI);
    else
        QMessageBox::warning(this, "USB-5132 Status", summaryNI);
#endif

    QPixmap pixmap("refresh.png"); // Use your image path or Qt resource
    QIcon buttonIcon(pixmap);
    ui->refreshButton->setIcon(buttonIcon);
    ui->refreshButton->setIconSize(QSize(16, 16)); // Set icon size

    ui->bittest_refresh_pb->setIcon(buttonIcon);
    ui->bittest_refresh_pb->setIconSize(QSize(16, 16)); // Set icon size

    ui->refresh_SRU_CC_pb->setIcon(buttonIcon);
    ui->refresh_SRU_CC_pb->setIconSize(QSize(16, 16));

    ui->refresh_SRU_DC_pb->setIcon(buttonIcon);
    ui->refresh_SRU_DC_pb->setIconSize(QSize(16, 16));

    ui->FTU_LRU_SL_NO_le->setText("1");

    ui->ftu_mk2_lru_slno_le->setText("1");

    //  on_USB_4716_AE_CARD1_pb_toggled(true);
    ui->SerialPortSelect->clear();
    //    const auto infos = QSerialPortInfo::availablePorts();
    //    for (const QSerialPortInfo &info : infos)
    //        ui->SerialPortSelect->addItem(info.portName());

    /*----------------------------REFRESH BUTTON--------------------------*/

    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::on_refreshButton_clicked);
    connect(ui->refresh_SRU_CC_pb,
            &QPushButton::clicked,
            this,
            &MainWindow::on_refresh_SRU_CC_pb_clicked);

    //-----------------------------------USB_Monitor_Initialisation_start--------------//
    SerialTimer = new QTimer(this);
    connect(SerialTimer, &QTimer::timeout, this, &MainWindow::checkDevices);
    SerialTimer->start(1000); // Check for every 1000 msec
    lastKnownPorts = QSerialPortInfo::availablePorts();
    connect(this, &MainWindow::deviceConnected, this, &MainWindow::SerialConnected);
    connect(this, &MainWindow::deviceDisconnected, this, &MainWindow::SerialDisconnected);
    //-----------------------------------USB_Monitor_Initialisation_end--------------//
    /*----------------------------QTimer 1--------------------------*/
    Timer_stay_in_boot_mode = new QTimer(this);
    connect(Timer_stay_in_boot_mode, SIGNAL(timeout()), this, SLOT(on_Connect_to_UC_clicked()));
    /*----------------------------QTimer 2--------------------------*/
    TimeOutTimer = new QTimer(this);
    connect(TimeOutTimer, SIGNAL(timeout()), this, SLOT(TimeOutTimer_Indications()));
    //-------------------- Timer_Dial________________________
    Timer_interrupt_Dial1 = new QTimer(this);
    connect(Timer_interrupt_Dial1, &QTimer::timeout, this, [this]() {
        on_DISPLAY_C1_pb_clicked(true);
    });
    Timer_interrupt_Dial2 = new QTimer(this);
    connect(Timer_interrupt_Dial2, &QTimer::timeout, this, [this]() {
        on_DISPLAY_C2_pb_clicked(true);
    });
    Timer_interrupt_Dial3 = new QTimer(this);
    connect(Timer_interrupt_Dial3, &QTimer::timeout, this, [this]() {
        on_DISPLAY_C3_pb_clicked(true);
    });
    //---------------------SRU Timers----------------------------
    Timer_SRU_DC_DC = new QTimer(this);
    connect(Timer_SRU_DC_DC, &QTimer::timeout, this, &MainWindow::SRU_DC_DC_TimerUpdate);
    //---------------CRC_calculation of STM32 programmer GUI----------------//
    QFile inputFile("FTU_SRU_GUI.exe");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QByteArray guiFileData = inputFile.readAll(); // Read file as binary
        // Ensure the data is properly handled by using static_cast for type conversion
        const uint8_t *dataPtr = reinterpret_cast<const uint8_t *>(guiFileData.constData());
        guiCRC_ATE = CRCUtility::g_CRC_calc(dataPtr, static_cast<uint32_t>(guiFileData.size()));
        ui->listWidget->addItem("STM32 Programmer GUI CRC =  0x"
                                + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0'));
        ui->listWidget->scrollToBottom();
        ui->SoftwareTableWidget
            ->setItem(2,
                      0,
                      new QTableWidgetItem(
                          "    0x"
                          + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0')));
        ui->ATE_Cksum_le->setText(QString("0x%1").arg(guiCRC_ATE, 4, 16, QChar('0')).toUpper());
        ui->SRU_ATE_cksum_le->setText(
            "0x" + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0'));
        ui->BITTEST_ATE_Checksum_le->setText(
            "0x" + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0'));
        ui->SoftwareTableWidget
            ->setItem(2, 1, new QTableWidgetItem("     " + QString::number(GUI_VERSION, 'f', 1)));
        inputFile.close();
    } else {
        ui->listWidget->addItem("ERROR IN READING .EXE FILE");
        ui->listWidget->scrollToBottom();

        Logger::instance()->logText(
            QString("0x") + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0'));

        SruLogger::instance()->logText(
            QString("0x") + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0'));
    }
    /*---------------------------------------CRC GUI calculation END--------------------------------------------------------*/
    //initial com port status set to 0
    //default configurations
    ui->SoftwareTableWidget->setEnabled(false);
    ui->progressBar->setFormat("");
    ui->Browse->setEnabled(false);
    ui->FilePathDisplay->setEnabled(false);
    ui->Connect_to_UC->setEnabled(false);
    ui->EraseFlash->setEnabled(false);
    ui->Download_HexFile->setEnabled(false);
    ui->progressBar->setEnabled(false);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabEnabled(2, true);
    ui->tabWidget->setTabEnabled(3, true);
    //    ui->tabWidget->tabBar()->setTabTextColor(0,Qt::Key_Yellow);
    ui->tabWidget->tabBar()->setStyleSheet("QTabBar::tab:selected {\
                                           color: rgb(255,213,69);\
            background-color: rgb(25,49,61);\
}");
    //-------------------------------------------------------------------
    thread1 = new QThread();
    helloThread = new HelloThread();

    helloThread->moveToThread(thread1);
    connect(helloThread, SIGNAL(testSignal_1()), thread1, SLOT(start()));
    connect(thread1, SIGNAL(started()), helloThread, SLOT(display1()));

    thread1->start();
    //    qDebug() << "created thread" << thread1->currentThreadId();
    helloThread->call_thread();
    //---------------------------------------------------------------------
    //----------------------------------ADVTCH_INT_THREAD-----------------------------------
    //--------------------------------------------------------------------
    // ----- one-time thread wiring -----
    advThread = new QThread(this); // parent = this for auto-delete
    AdvWorker = new AdvantechCardsInterface;
    AdvWorker->moveToThread(advThread);
    connect(advThread, &QThread::started, AdvWorker, &AdvantechCardsInterface::start);
    connect(AdvWorker, &AdvantechCardsInterface::finished, advThread, &QThread::quit);
    connect(AdvWorker, &AdvantechCardsInterface::finished, AdvWorker, &QObject::deleteLater);
    connect(advThread, &QThread::finished, advThread, &QObject::deleteLater);
    advThread->start();
    connect(this,
            &MainWindow::ADV_InitailizationSignal,
            AdvWorker,
            &AdvantechCardsInterface::Initailization,
            Qt::QueuedConnection);
    emit ADV_InitailizationSignal();

    //    checkUsb5132Status(true);

    //    // 2. Start timer for periodic USB status checks every 1 second
    //    connect(usbPollTimer, &QTimer::timeout, this, [=]() {
    //        checkUsb5132Status(false);
    //        checkUsb5856Status();
    //        checkUsb4716Status();
    //    });
    //    usbPollTimer->start(1000);

    Timer_interrupt_USB_Card_Status = new QTimer(this);
    connect(Timer_interrupt_USB_Card_Status, &QTimer::timeout, this, [this]() {
        //        checkUsb5132Status(false);
        checkUsb5856Status();
        // checkUsb4716Status();
    });
    Timer_interrupt_USB_Card_Status->start(1000);

    connect(AdvWorker,
            &AdvantechCardsInterface::USB_5856_cards_status_signal,
            this,
            &MainWindow::USB_5856_cards_status,
            Qt::QueuedConnection);

    connect(AdvWorker,
            &AdvantechCardsInterface::USB_4716_cards_status_signal,
            this,
            &MainWindow::USB_4716_cards_status,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card1Signal_ON,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard1DO_ONButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card1Signal_OFF,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard1DO_OFFButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card2Signal_ON,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard2DO_ONButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card2Signal_OFF,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard2DO_OFFButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card3Signal_ON,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard3DO_ONButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card3Signal_OFF,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard3DO_OFFButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card4Signal_ON,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard4DO_ONButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::card4Signal_OFF,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard4DO_OFFButtonClicked_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::ADC_4716card2Signal,
            AdvWorker,
            &AdvantechCardsInterface::DAC_VOLTAGE_DAC_CH1,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::ADC_4716card2Signal_OFF,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard2AO_OFFButtonClicked_4716,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::RS422_card1Signal_ON,
            AdvWorker,
            &AdvantechCardsInterface::Rs422_CH1_CH2_ON_card3_5856,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::RS422_card1Signal_OFF,
            AdvWorker,
            &AdvantechCardsInterface::Rs422_CH1_CH2_OFF_card3_5856,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::ps4_VM,
            AdvWorker,
            &AdvantechCardsInterface::PS4_3_3_Voltage_Monitor,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::ps5_plus5_VM,
            AdvWorker,
            &AdvantechCardsInterface::PS5_plus_5_Voltage_monitor,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::ps6_minus5_VM,
            AdvWorker,
            &AdvantechCardsInterface::PS5_Negative_5_Voltage_monitor,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::PS7_VM,
            AdvWorker,
            &AdvantechCardsInterface::PS7_Power_on_LRU,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::ps3_VM,
            AdvWorker,
            &AdvantechCardsInterface::PS3_5V_Source_from_Power_Card,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::ps1_VM,
            AdvWorker,
            &AdvantechCardsInterface::PS1_28V_Source_from_Power_Card,
            Qt::QueuedConnection);
    connect(AdvWorker,
            &AdvantechCardsInterface::aoAiUpdated,
            this,
            &MainWindow::updateAoAiLineEdits,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::adcCard2TriggerSignal,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard2ADCCheck_4716,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::USB_5856_Conn_STS_Signal,
            AdvWorker,
            &AdvantechCardsInterface::isCardConnected,
            Qt::QueuedConnection);

    connect(AdvWorker,
            &AdvantechCardsInterface::USB_5856_Conn_STS_emit,
            this,
            &MainWindow::USB_5856_Conn_Status,
            Qt::QueuedConnection);
    connect(AdvWorker,
            &AdvantechCardsInterface::SRU_CTRL_AUTO_emit,
            this,
            &MainWindow::SRU_CTRL_AutoStepCompleted,
            Qt::QueuedConnection);

    connect(AdvWorker,
            &AdvantechCardsInterface::adcCard2Result,
            this,
            &MainWindow::onCard2ADCResult,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS1_Sig_MT,
            AdvWorker,
            &AdvantechCardsInterface::LOAD_MEASURMENT_PS1_28V,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS2_Sig_MT,
            AdvWorker,
            &AdvantechCardsInterface::LOAD_MEASURMENT_PS2_12V,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS3_Sig_MT,
            AdvWorker,
            &AdvantechCardsInterface::LOAD_MEASURMENT_5856_PS3_5V,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS4_Sig_MT,
            AdvWorker,
            &AdvantechCardsInterface::LOAD_MEASURMENT_5856_PS4,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS5_Sig_MT,
            AdvWorker,
            &AdvantechCardsInterface::LOAD_MEASURMENT_5856_PS5_5V,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS6_Sig_MT,
            AdvWorker,
            &AdvantechCardsInterface::LOAD_MEASURMENT_PS6_minus_5V,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS7_Sig_MT,
            AdvWorker,
            &AdvantechCardsInterface::Font_panel_load_on_PS7,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::LED_PS4_Sig,
            AdvWorker,
            &AdvantechCardsInterface::LED_5856_CNTRL_CARDS_PS4,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS5_Sig,
            AdvWorker,
            &AdvantechCardsInterface::LED_ON_OFF_CCARDS_PS5_plus_5V,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS6_Sig,
            AdvWorker,
            &AdvantechCardsInterface::LED_ON_CCARDS_PS6_minus5V,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::LED_PS7_Sig,
            AdvWorker,
            &AdvantechCardsInterface::LED_PS7_16V_ON_OFF,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::PS7_Sig,
            AdvWorker,
            &AdvantechCardsInterface::PS7_16V_28V_32V_Source_from_Power_Card,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::ADC_BitTest_Sig,
            AdvWorker,
            &AdvantechCardsInterface::onTriggerCard1AIButtonClicked,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::Discrete_Input_Ch1,
            AdvWorker,
            &AdvantechCardsInterface::handleDISCRETE_IN_CH1,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::Discrete_Input_Ch2,
            AdvWorker,
            &AdvantechCardsInterface::handleDISCRETE_IN_CH2,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::Discrete_Input_Ch3,
            AdvWorker,
            &AdvantechCardsInterface::handleDISCRETE_IN_CH3,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::Discrete_IN_OFF,
            AdvWorker,
            &AdvantechCardsInterface::handleDISCRETE_IN_OFF_CH,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::Display_Digit1,
            AdvWorker,
            &AdvantechCardsInterface::USB_4716_DisplayC1,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::Display_Digit2,
            AdvWorker,
            &AdvantechCardsInterface::USB_4716_DisplayC2,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::Display_Digit3,
            AdvWorker,
            &AdvantechCardsInterface::USB_4716_DisplayC3,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::Display_Dial1,
            AdvWorker,
            &AdvantechCardsInterface::USB_4716_DisplayCTRL_8421,
            Qt::QueuedConnection);

    //----------------------------------------------------
    connect(this,
            &MainWindow::DC_DC_3p3_SRU,
            AdvWorker,
            &AdvantechCardsInterface::DC_DC_3p3_Voltage_monitor,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_5_SRU,
            AdvWorker,
            &AdvantechCardsInterface::DC_DC_5_Voltage_monitor,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_N_5_SRU,
            AdvWorker,
            &AdvantechCardsInterface::DC_DC_Negative_5_Voltage_monitor,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_5_LED_Ripple,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_5V_InitialValues_LED_Ripple,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_5_L_10PER,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_5V_LOAD_MEASUREMENT_10_percent,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_5_L_100PER,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_5V_LOAD_MEASUREMENT_100_percent,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_N_5_LED_Ripple,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_MINUS_5V_InitialValues_LED_Ripple,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_N_5_L_10PER,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_MINUS_5V_LOAD_MEASUREMENT_10_percent,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::DC_DC_N_5_L_100PER,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_MINUS_5V_LOAD_MEASUREMENT_100_percent,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::DC_DC_3p3_LED_Ripple,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_3_3V_InitialValues_LED_Ripple,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::DC_DC_3p3_L_10PER,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_3_3V_LOAD_MEASUREMENT_10_percent,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_3p3_L_100PER,
            AdvWorker,
            &AdvantechCardsInterface::DC_CARD_3_3V_LOAD_MEASUREMENT_100_percent,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::DC_DC_N_5_Differential,
            AdvWorker,
            &AdvantechCardsInterface::read4716_Diff_CH0_CH1,
            Qt::QueuedConnection);

    //------------------------SRU-----------------------

    connect(this,
            &MainWindow::DIS_OUT_Read_USB_Card,
            AdvWorker,
            &AdvantechCardsInterface::DIS_OUT_Read_USB_Card_5856,
            Qt::QueuedConnection);

    connect(this,
            &MainWindow::SRU_AbortSwitch,
            AdvWorker,
            &AdvantechCardsInterface::handleAbortSwitch,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_PrepSwitch,
            AdvWorker,
            &AdvantechCardsInterface::handlePREP_Switch,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_ReadyInitSwitch,
            AdvWorker,
            &AdvantechCardsInterface::handleREADY_INIT_Switch,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_1,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_1,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_2,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_2,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_3,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_3,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_4,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_4,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_5,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_5,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_6,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_6,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_7,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_7,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_8,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_8,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_9,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_9,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D1_Sig_10,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D1_10,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_1,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_1,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_2,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_2,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_3,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_3,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_4,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_4,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_5,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_5,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_6,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_6,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_7,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_7,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_8,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_8,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_9,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_9,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D2_Sig_10,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D2_10,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_1,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_1,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_2,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_2,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_3,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_3,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_4,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_4,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_5,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_5,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_6,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_6,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_7,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_7,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_8,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_8,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_9,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_9,
            Qt::QueuedConnection);
    connect(this,
            &MainWindow::SRU_TPS_D3_Sig_10,
            AdvWorker,
            &AdvantechCardsInterface::handleTPS_D3_10,
            Qt::QueuedConnection);

    /*----------------------------QTimer3---------------------------*/
    ADC_BitTestTim = new QTimer(this);
    connect(ADC_BitTestTim, SIGNAL(timeout()), this, SLOT(ADC_BitTestTimer()));

    //-------------------------card3_5856_ ch30, ch31 default ON--------------------
    emit RS422_card1Signal_ON();

    //---------------------------------------------------------------------
    //---------------Timer_interrupt configuration----------------//

    //    Timer_interrupt = new QTimer(this);
    //    connect(Timer_interrupt, &QTimer::timeout, this, &MainWindow::Sequence_TimerInterrupt);

    //-----------------------
    ui->SoftwareTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SoftwareTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->TestPointDatatableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
    ui->TestPointDatatableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    thread2 = new QThread();
    TestPointDataFramming *testPointDataFramming = new TestPointDataFramming();

    testPointDataFramming->moveToThread(thread2);

    //connect(this, &MainWindow::LoadWaveform_into_GUI,testPointDataFramming, &TestPointDataFramming::process);
    //connect(testPointDataFramming, &TestPointDataFramming::requestDirectorySelection, this, &MainWindow::onRequestDirectorySelection);
    //connect(this, &MainWindow::LoadWaveform_into_GUI,this, &MainWindow::onRequestDirectorySelection);

    connect(this,
            &MainWindow::directorySelected,
            testPointDataFramming,
            &TestPointDataFramming::SlotdirectorySelected);

    connect(testPointDataFramming,
            &TestPointDataFramming::update_waveform_table,
            this,
            &MainWindow::updateFromTestPoint);
    //connect(this,&MainWindow::sigTransferInit,testPointDataFramming,&TestPointDataFramming::slotTransferInit);
    connect(testPointDataFramming,
            &TestPointDataFramming::testPointsUpdated,
            this,
            &MainWindow::handleTestPointsData);
    connect(this, &MainWindow::Stop_TP, testPointDataFramming, &TestPointDataFramming::stop);
    connect(testPointDataFramming, &TestPointDataFramming::finished, thread2, &QThread::quit);
    connect(testPointDataFramming,
            &TestPointDataFramming::finished,
            testPointDataFramming,
            &TestPointDataFramming::deleteLater);
    connect(thread2, &QThread::finished, thread2, &QThread::deleteLater);

    thread2->start();

    QButtonGroup *group = new QButtonGroup(this);
    group->setExclusive(true);

    graphWidget = new GraphWidget(this, this);
    //graphWidget->setupWavefomrSiumlation();
    connect(this, &MainWindow::sigWaveformProcess, graphWidget, &GraphWidget::slotWaveformProcess);

    ui->SoftwareTableWidget->resizeColumnsToContents();
    ui->SoftwareTableWidget->resizeRowsToContents();

    //--------------Timer for status Update on SELF TEST WINDOW-----------------
    StatusTimer = new QTimer;
    connect(StatusTimer, SIGNAL(timeout()), this, SLOT(SelfTest_StatusUpdate()));
    StatusTimer->start(100);

    //************************************** BIT TSET SERIAL ************************************

    //test graphs
    //    ui->label_9->setFixedHeight(0);
    //    ui->label_11->setFixedHeight(0);
    //    ui->label_12->setFixedHeight(0);
    //    ui->label_13->setFixedHeight(0);
    //    ui->label_14->setFixedHeight(0);
    //    ui->label_15->setFixedHeight(0);
    //    ui->label_16->setFixedHeight(0);
    //    ui->Graph1->setVisible(false);
    //    ui->horizontalLayout_18->removeItem();
    //    ui->widget->setVisible(false);

    ui->Graph1->installEventFilter(this);
    ui->Graph2->installEventFilter(this);
    ui->Graph3->installEventFilter(this);
    ui->Graph4->installEventFilter(this);
    ui->Graph5->installEventFilter(this);
    ui->Graph6->installEventFilter(this);
    ui->Graph7->installEventFilter(this);
    ui->Graph8->installEventFilter(this);

    //--------------------Graph-----------------------------------------
    on_GraphStop_toggled(true);
    ui->ControllerCard_GroupBox->setVisible(false);
    ui->DC_DC_GroupBox->setVisible(false);
    ui->DisplayCard_groupBox->setVisible(false);

    //    g_ADC_BIT_TEST.averagedAi_test1.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test2.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test3.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test4.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test5.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test6.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test7.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test8.resize(8);
    //    g_ADC_BIT_TEST.averagedAi_test9.resize(8);

    g_ADC_Card2_BitTest.averagedAi_test1.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test2.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test3.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test4.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test5.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test6.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test7.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test8.resize(8);
    g_ADC_Card2_BitTest.averagedAi_test9.resize(8);

    outputLines.resize(8);
    resultLines.resize(8);
    SRU_output.resize(8);
    SRU_result.resize(8);

    //---------------------------------------------------------------------
    ui->Display_Card_Dial1->setEnabled(false);
    ui->Display_Card_Dial2->setEnabled(false);
    ui->Display_Card_Dial3->setEnabled(false);
    ui->displaycard_groupBox->setEnabled(false);
    ui->groupBox_135->setEnabled(false);
    ui->groupBox_138->setEnabled(false);
    //default state of ATE SELF Test buttons
    on_refreshButton_clicked();
    ui->Discrete_Inputs_Pb->setHidden(true);
}

MainWindow::~MainWindow()
{
    emit PS7_VM(5);
    //hello Thread stop
    helloThread->stopThread();
    // Assuming you have a mechanism to signal your thread to stop
    //    qDebug() << "thread to stop"
    //             << helloThread->thread()
    //                    ->currentThreadId(); // This is hypothetical; you need to implement this based on your application's logic
    thread1->quit(); // Request the thread to quit
    thread1->wait(); // Wait for the thread to actually finish
    delete thread1;
    delete helloThread;

    advThread->quit();
    advThread->wait();
    //    ADC_BitTestTim->stop();
    thread2->quit();
    thread2->wait();

    emit Stop_TP();
    on_SRU_CTRL_Volt_pb_clicked(false);
    if (usb5856Manager) {
        usb5856Manager->dispose();
        delete usb5856Manager;
        usb5856Manager = nullptr;
    }

    delete ui;
}

void MainWindow::ADC_BitTestTimer()
{
    const int aiChannelCount = 8;
    const int avgSamples = 300;           // Number of samples for moving average
    double sumData[aiChannelCount] = {0}; // Initialize per-channel sum
    emit sigWaveformProcess();
    emit ADC_BitTest_Sig();
    // packet counts       8    7     6     5     4    3    2    1    0
    double voltages[] = {-2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0};

    // Loop through all 8 channels
    switch (g_ADC_BIT_TEST.packetCount) {
    case 0: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }
        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
            // qDebug().nospace() << "  AI CH" << (ch + 1) << " : " << QString::number(avg, 'f', 4)<< " V";

            //            qDebug().noquote() << line;
            //            logBit.append(line);
        }
        //        QString logLine = logBit.join(", ");
        //        BitTestLogger::instance()->logText(logLine);

        g_ADC_Card2_BitTest.averagedAi_test1 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[8] - (voltages[8] * TOLERANCE_1);
            float upperBound = voltages[8] + (voltages[8] * TOLERANCE_1);
            g_ADC_Card2_BitTest.test1Status[i] = (g_ADC_Card2_BitTest.averagedAi_test1[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test1[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test1Status[i] ? " PASS" : " FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test1Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 2Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test1Status[i] ? "PASS" : "FAIL"));

            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 ADC-DAC:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test1Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_2V[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_2V[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test1Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test1Status[i] ? "color: green;"
                                                                            : "color: red;");
        }
        break;
    }
    case 1: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }
        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
        }
        g_ADC_Card2_BitTest.averagedAi_test2 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[7] - (voltages[7] * TOLERANCE_1);
            float upperBound = voltages[7] + (voltages[7] * TOLERANCE_1);
            g_ADC_Card2_BitTest.test2Status[i] = (g_ADC_Card2_BitTest.averagedAi_test2[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test2[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test2Status[i] ? " PASS" : " FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test2Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString(" Channel :%1 1.5Volts :%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test2Status[i] ? "PASS" : "FAIL"));
            //            BitTestLogger::instance()->logText(
            //                QString(" Channel :%1 ADC_DAC Count :%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test2Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_1p5V[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_1p5V[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test2Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test2Status[i] ? "color: green;"
                                                                            : "color: red;");
        }
        // BitTestLogger::instance()->logText("");

        break;
    }

    case 2: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }
        QVector<double> averagedAi;
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
        }

        g_ADC_Card2_BitTest.averagedAi_test3 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[6] - (voltages[6] * TOLERANCE_1);
            float upperBound = voltages[6] + (voltages[6] * TOLERANCE_1);
            g_ADC_Card2_BitTest.test3Status[i] = (g_ADC_Card2_BitTest.averagedAi_test3[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test3[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
            //            if (g_ADC_Card2_BitTest.test3Status[i] == 0x01) {
            //                g_BitTestLogger_PassFailCount.passCount_ADC_DAC_1V[i]++;
            //                BitTestLogger::instance()->logText(
            //                    QString("Channel: %1 ADC-DAC Count:%2")
            //                        .arg(i + 1)
            //                        .arg(g_BitTestLogger_PassFailCount.passCount_ADC_DAC_1V[i]));
            //            } else {
            //                g_BitTestLogger_PassFailCount.failCount_ADC_DAC_1V[i]++;
            //                BitTestLogger::instance()->logText(
            //                    QString("Channel: %1 ADC-DAC Count:%2")
            //                        .arg(i + 1)
            //                        .arg(g_BitTestLogger_PassFailCount.failCount_ADC_DAC_1V[i]));
            //            }
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};
        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test3Status[i] ? "PASS" : "FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test3Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString(" Channel :%1 1Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test3Status[i] ? "PASS" : "FAIL"));
            //            BitTestLogger::instance()->logText(
            //                QString("Channel: %1 ADC-DAC Count:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test3Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_1V[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_1V[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test3Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test3Status[i] ? "color: green;"
                                                                            : "color: red;");
        }
        break;
    }

    case 3: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }

        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
        }

        g_ADC_Card2_BitTest.averagedAi_test4 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[5] - (voltages[5] * TOLERANCE_2);
            float upperBound = voltages[5] + (voltages[5] * TOLERANCE_2);
            g_ADC_Card2_BitTest.test4Status[i] = (g_ADC_Card2_BitTest.averagedAi_test4[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test4[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test4Status[i] ? "PASS" : " FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test4Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 0.5Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test4Status[i] ? "PASS" : "FAIL"));
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 0.5Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test4Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_0p5V[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_0p5V[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));

            SRU_result[i]->setText(g_ADC_Card2_BitTest.test4Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test4Status[i] ? "color: green;"
                                                                            : "color: red;");
        }

        break;
    }
    case 4: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }

        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
        }

        g_ADC_Card2_BitTest.averagedAi_test5 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[4] - (TOLERANCE_2);
            float upperBound = voltages[4] + (TOLERANCE_2);
            g_ADC_Card2_BitTest.test5Status[i] = (g_ADC_Card2_BitTest.averagedAi_test5[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test5[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test5Status[i] ? " PASS" : "FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test5Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 0Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test5Status[i] ? "PASS" : "FAIL"));

            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 0Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test5Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_0V[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_0V[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test5Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test5Status[i] ? "color: green;"
                                                                            : "color: red;");
        }
        break;
    }

    case 5: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }
        //        qDebug() << "g_ADC_BIT_TEST.packetCount" << g_ADC_BIT_TEST.packetCount;
        //        qDebug() << "g_ADC_BIT_TEST.voltage" << QString::number(g_ADC_BIT_TEST.voltage, 'f', 4);
        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
            // qDebug().nospace() << "  AI CH" << (ch + 1) << " : " << QString::number(avg, 'f', 4)<< " V";

            // qDebug().noquote() << line;
            //            logParts.append(line);
        }

        g_ADC_Card2_BitTest.averagedAi_test6 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[3] + (voltages[3] * TOLERANCE_2);
            float upperBound = voltages[3] - (voltages[3] * TOLERANCE_2);
            g_ADC_Card2_BitTest.test6Status[i] = (g_ADC_Card2_BitTest.averagedAi_test6[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test6[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test6Status[i] ? " PASS" : " FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test6Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 0.5Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test6Status[i] ? "PASS" : "FAIL"));

            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 0.5Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test6Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N0p5[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N0p5[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test6Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test6Status[i] ? "color: green;"
                                                                            : "color: red;");
        }
        break;
    }

    case 6: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }
        QVector<double> averagedAi;
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
            // qDebug().nospace() << "  AI CH" << (ch + 1) << " : " << QString::number(avg, 'f', 4)<< " V";

            // qDebug().noquote() << line;
            //            logParts.append(line);
        }

        g_ADC_Card2_BitTest.averagedAi_test7 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[2] + (voltages[2] * TOLERANCE_1);
            float upperBound = voltages[2] - (voltages[2] * TOLERANCE_1);
            g_ADC_Card2_BitTest.test7Status[i] = (g_ADC_Card2_BitTest.averagedAi_test7[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test7[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test7Status[i] ? " PASS" : " FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test7Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 1Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test7Status[i] ? "PASS" : "FAIL"));

            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 1Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test7Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N1[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N1[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test7Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test7Status[i] ? "color: green;"
                                                                            : "color: red;");
        }
        break;
    }
    case 7: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }
        //        qDebug() << "g_ADC_BIT_TEST.packetCount" << g_ADC_BIT_TEST.packetCount;
        //        qDebug() << "g_ADC_BIT_TEST.voltage" << QString::number(g_ADC_BIT_TEST.voltage, 'f', 4);
        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
            // qDebug().nospace() << "  AI CH" << (ch + 1) << " : " << QString::number(avg, 'f', 4)<< " V";

            // qDebug().noquote() << line;
            //            logParts.append(line);
        }

        g_ADC_Card2_BitTest.averagedAi_test8 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[1] + (voltages[1] * TOLERANCE_1);
            float upperBound = voltages[1] - (voltages[1] * TOLERANCE_1);
            g_ADC_Card2_BitTest.test8Status[i] = (g_ADC_Card2_BitTest.averagedAi_test8[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test8[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test8Status[i] ? " PASS" : " FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test8Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 1.5Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test8Status[i] ? "PASS" : "FAIL"));

            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 1.5Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test8Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N1p5[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N1p5[i]++));
            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test8Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test8Status[i] ? "color: green;"
                                                                            : "color: red;");
        }
        break;
    }
    case 8: {
        for (int sample = 0; sample < avgSamples; ++sample) {
            for (int ch = 0; ch < aiChannelCount; ++ch) {
                sumData[ch] += g_ADC_BitTest.CH_data[ch]; // Accumulate each channel individually
            }
        }
        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
            // qDebug().nospace() << "  AI CH" << (ch + 1) << " : " << QString::number(avg, 'f', 4)<< " V";

            // qDebug().noquote() << line;
            //            logParts.append(line);
        }

        g_ADC_Card2_BitTest.averagedAi_test9 = averagedAi;
        for (int i = 0; i < 8; i++) {
            float lowerBound = voltages[0] + (voltages[0] * TOLERANCE_1);
            float upperBound = voltages[0] - (voltages[0] * TOLERANCE_1);
            g_ADC_Card2_BitTest.test9Status[i] = (g_ADC_Card2_BitTest.averagedAi_test9[i]
                                                      >= lowerBound
                                                  && g_ADC_Card2_BitTest.averagedAi_test9[i]
                                                         <= upperBound)
                                                     ? 1
                                                     : 0;
        }

        outputLines = {ui->ADC_DAC_output_Ch1_le,
                       ui->ADC_DAC_output_Ch2_le,
                       ui->ADC_DAC_output_Ch3_le,
                       ui->ADC_DAC_output_Ch4_le,
                       ui->ADC_DAC_output_Ch5_le,
                       ui->ADC_DAC_output_Ch6_le,
                       ui->ADC_DAC_output_Ch7_le,
                       ui->ADC_DAC_output_Ch8_le};

        resultLines = {ui->ADC_DAC_result_Ch1_le,
                       ui->ADC_DAC_result_Ch2_le,
                       ui->ADC_DAC_result_Ch3_le,
                       ui->ADC_DAC_result_Ch4_le,
                       ui->ADC_DAC_result_Ch5_le,
                       ui->ADC_DAC_result_Ch6_le,
                       ui->ADC_DAC_result_Ch7_le,
                       ui->ADC_DAC_result_Ch8_le};

        SRU_output = {ui->DAC_op_ch1_le,
                      ui->DAC_op_ch2_le,
                      ui->DAC_op_ch3_le,
                      ui->DAC_op_ch4_le,
                      ui->DAC_op_ch5_le,
                      ui->DAC_op_ch6_le,
                      ui->DAC_op_ch7_le,
                      ui->DAC_op_ch8_le};

        SRU_result = {ui->DAC_Result_ch1_le,
                      ui->DAC_Result_ch2_le,
                      ui->DAC_Result_ch3_le,
                      ui->DAC_Result_ch4_le,
                      ui->DAC_Result_ch5_le,
                      ui->DAC_Result_ch6_le,
                      ui->DAC_Result_ch7_le,
                      ui->DAC_Result_ch8_le};

        for (int i = 0; i < 8; ++i) {
            outputLines[i]->setText(QString::number(averagedAi[i], 'f', 4));
            resultLines[i]->setText(g_ADC_Card2_BitTest.test9Status[i] ? " PASS" : " FAIL");
            resultLines[i]->setStyleSheet(g_ADC_Card2_BitTest.test9Status[i] ? "color: green;"
                                                                             : "color: red;");
            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 2Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test9Status[i] ? "PASS" : "FAIL"));

            //            BitTestLogger::instance()->logText(
            //                QString("Channel:%1 Negative 2Volts:%2")
            //                    .arg(i + 1)
            //                    .arg(g_ADC_Card2_BitTest.test9Status[i]
            //                             ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N2[i]++
            //                             : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N2[i]++));

            SRU_output[i]->setText(QString::number(averagedAi[i], 'f', 4));
            SRU_result[i]->setText(g_ADC_Card2_BitTest.test9Status[i] ? " PASS" : " FAIL");
            SRU_result[i]->setStyleSheet(g_ADC_Card2_BitTest.test9Status[i] ? "color: green;"
                                                                            : "color: red;");
        }

        break;
    }
    default: {
        break;
    }
    }

    if (isFirstADCTrigger) {
        // qDebug() << "ADC Bit Test Triggered";

        // isFirstADCTrigger = false;
        //        ADC_BitTestTim->setInterval(60); // Change to 1ms after first timeout
    }
}

///*--------Private helpers-- ------*/
//uint16_t MainWindow::next_idx(uint16_t idx, uint16_t cap)
//{
//    return (idx + 1u) >= cap ? 0u : (uint16_t) (idx + 1u);
//}

/* -------- API -------- */
void MainWindow::RA_Init(RunningAverage *ra, float *storage, uint16_t len)
{
    ra->buf = storage;
    ra->capacity = len;
    RA_Reset(ra);
}

void MainWindow::RA_Reset(RunningAverage *ra)
{
    ra->head = 0u;
    ra->count = 0u;
    ra->sum = 0.0f;
}

void MainWindow::RA_Push(RunningAverage *ra, float sample)
{
    if (ra->count == ra->capacity) /* FIFO already full → drop oldest */
    {
        /* subtract value that is about to be overwritten from running sum */
        ra->sum -= ra->buf[ra->head];
    } else {
        ra->count++;
    }

    /* write new sample */
    ra->buf[ra->head] = sample;
    ra->sum += sample;

    /* advance circular index */
    ra->head = next_idx(ra->head, ra->capacity);
}

float MainWindow::RA_GetMean(const RunningAverage *ra)
{
    return (ra->count == 0u) ? 0.0f : (ra->sum / (float) ra->count);
}

uint16_t MainWindow::RA_Size(const RunningAverage *ra)
{
    return ra->count;
}
uint16_t MainWindow::RA_Cap(const RunningAverage *ra)
{
    return ra->capacity;
}

void MainWindow::message_received(const QByteArray &message)
{
    // qDebug() << "###message received and processing in main:" << message.toHex();
    QByteArray rx_data = message;
    uint16_t l_size = rx_data.size();
    uint16_t l_CRC_higherByte = l_size - 3;
    uint16_t l_CRC_lowerByte = l_size - 4;

    //    // Ensure rx_data is large enough for the operations to follow
    if (rx_data.size() >= 4) {
        g_checkCRC_word = (rx_data[l_CRC_lowerByte] & 0xFF);
        g_checkCRC_word |= ((rx_data[l_CRC_higherByte] & 0xFF) << 8);
        //    // Overwrite the CRC bytes in the message to 0
        rx_data[l_CRC_lowerByte] = 0;
        rx_data[l_CRC_higherByte] = 0;
    } else {
        //        qDebug() << "Received message is too short to contain CRC bytes.";
    }
    g_CRC_word = CRCUtility::g_CRC_calc(reinterpret_cast<uint8_t *>(rx_data.data()), rx_data.size());
    //    qDebug() << "g_CRC_word" << g_CRC_word;
    //    qDebug() << "g_checkCRC_word" << g_checkCRC_word;
    //    qDebug() << "rx_data" << rx_data;
    if ((g_checkCRC_word == g_CRC_word) && (rx_data.at(2) != WAVEFORM_DISPLAY_ID)) {
        switch (rx_data.at(1)) {
        case (CONTROLLER_IN_BOOTMODE): {
            uint16_t l_crc_byte = 0;
            Timer_stay_in_boot_mode->stop();
            g_boot_timer_status = 1;
            ui->listWidget->addItem("RX:Waiting In BOOTLOADER MODE........");
            ui->Connect_to_UC->setStyleSheet("background-color: rgb(8, 102, 70)"); //green
            ui->Connect_to_UC->setEnabled(false);
            ui->listWidget->scrollToBottom();
            ui->Browse->setEnabled(true);
            ui->FilePathDisplay->setEnabled(true);
            l_crc_byte = rx_data.at(3) & 0xFF;
            //                qDebug() << QString::number(l_crc_byte,16);
            l_crc_byte |= (uint16_t) ((rx_data.at(4) << 8) & 0xFF00);
            //                qDebug() << QString::number(l_crc_byte,16);

            ui->SoftwareTableWidget
                ->setItem(0,
                          0,
                          new QTableWidgetItem(
                              "    0x"
                              + QString::number(l_crc_byte, 16).toUpper().rightJustified(4, '0')));
            ui->SoftwareTableWidget->setItem(0,
                                             1,
                                             new QTableWidgetItem(
                                                 "     " + QString::number(rx_data.at(5), 10) + "."
                                                 + QString::number(rx_data.at(6), 10)));
            break;
        }
        case (UC_FLASH_ERASE_SUCCESS): {
            ui->listWidget->addItem("RX:UC_SECTOR_FLASH_ERASE_SUCCESS");
            ui->listWidget->scrollToBottom();
            ui->EraseFlash->setStyleSheet("background-color: rgb(0, 255, 127)"); //green
            g_time_out_flag = 0;
            ui->EraseFlash->setEnabled(false);
            ui->Download_HexFile->setEnabled(true);

            break;
        }
        case (UC_FLASH_ERASE_FAIL): {
            ui->listWidget->addItem("RX:UC_SECTOR_FLASH_ERASE_FAILUR");
            ui->listWidget->scrollToBottom();
            ui->EraseFlash->setStyleSheet("background-color: rgb(255, 7, 7)"); //red
            g_time_out_flag = 1;
            ui->EraseFlash->setEnabled(false);

            break;
        }
        case (APP_WR_DATA_PKT_ACK_PASS): {
            ui->listWidget->addItem("RX:APP_WR_DATA_PKT_ACK_PASS");
            ui->listWidget->scrollToBottom();
            g_time_out_flag = 0;
            on_Download_HexFile_clicked();

            break;
        }
        case (APP_WR_DATA_PKT_ACK_FAIL): {
            ui->listWidget->addItem("RX:APP_WR_DATA_PKT_ACK_FAIL");
            ui->listWidget->scrollToBottom();
            g_time_out_flag = 1;
            ui->Download_HexFile->setStyleSheet("background-color: rgb(255, 7, 7)"); //red

            break;
        }
        case (APP_SIG_DWORD_WR_PASS): {
            ui->listWidget->addItem("APP_SIG_DWORD_WR_PASS");
            ui->listWidget->scrollToBottom();
            g_time_out_flag = 0;

            AppCRC_Verify();
            break;
        }
        case (APP_SIG_DWORD_WR_FAIL): {
            ui->listWidget->addItem("APP_SIG_DWORD_WR_FAIL");
            ui->listWidget->scrollToBottom();
            g_time_out_flag = 1;
            ui->Download_HexFile->setStyleSheet("background-color: rgb(255, 7, 7)"); //red

            break;
        }
        case (APP_CRC_VERIFY): {
            uint16_t l_crc_byte = 0;
            l_crc_byte = rx_data.at(3) & 0xFF;
            //                qDebug() << QString::number(l_crc_byte,16);
            l_crc_byte |= (uint16_t) ((rx_data.at(4) << 8) & 0xFF00);
            //                qDebug() << QString::number(l_crc_byte,16);
            ui->SoftwareTableWidget
                ->setItem(1,
                          0,
                          new QTableWidgetItem(
                              "    0x"
                              + QString::number(l_crc_byte, 16).toUpper().rightJustified(4, '0')));
            ui->SoftwareTableWidget->setItem(1,
                                             1,
                                             new QTableWidgetItem(
                                                 "     " + QString::number(rx_data.at(5), 10) + "."
                                                 + QString::number(rx_data.at(6), 10)));

            ui->listWidget->addItem("Calculated CRC from UC: 0x"
                                    + QString::number(l_crc_byte, 16).toUpper());
            ui->listWidget->scrollToBottom();
            g_CRC_check_UC = l_crc_byte;
            if (g_CRC_check_UC == g_CRC_check_GUI) {
                ui->listWidget->addItem("Programmed code verification successful");
                ui->listWidget->scrollToBottom();
            } else {
                ui->listWidget->addItem("Programmed code verification Failed");
                ui->listWidget->scrollToBottom();
                ui->Download_HexFile->setStyleSheet("background-color: rgb(255, 7, 7)"); //red*
            }
            g_time_out_flag = 0;
            break;
        }
        case (ACK_TP_PKT_ID): {
            //            qDebug() << "TP data rx: Success";
            QProgressBar *progressBar = new QProgressBar(this);
            progressBar->setRange(0, 100); // Set the range
            bool ok;
            ok = true;
            if (ok == true) {
                progressBar->setValue(100); // Set the current value
            } else {
                progressBar->setValue(0); // Set the current value
            }
            ui->TestPointDatatableWidget->setCellWidget(g_counter_Tp_status, 3, progressBar);
            ui->TestPointDatatableWidget->scrollTo(
                ui->TestPointDatatableWidget->model()->index(g_counter_Tp_status, 1));
            g_counter_Tp_status++;
            if (g_Tp_pkt_tx_cnt < g_Tp_pkt_max_size) {
                sendTP_data_to_UC();
            } else {
                g_ExtFlashCRC.startByte = '$';
                g_ExtFlashCRC.MsgID = EXT_FLASH_CRC;
                g_ExtFlashCRC.packetSize = sizeof(g_ExtFlashCRC);
                g_ExtFlashCRC.extFlash_CRC = 0;
                g_ExtFlashCRC.CRC_WORD = 0;
                g_ExtFlashCRC.endByte = 0x233B;

                g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_ExtFlashCRC,
                                                    g_ExtFlashCRC.packetSize);
                g_ExtFlashCRC.CRC_WORD = g_CRC_word;
                emit serialWrite((char *) &g_ExtFlashCRC, g_ExtFlashCRC.packetSize);
            }
            break;
        }
        case (EXT_FLASH_CRC_TX): {
            //            qDebug() << "received EXT Flash crc";
            memcpy(&g_ExtFlashCRC, (uint8_t *) &rx_data, sizeof(ExtFlashCRC));
            //            qDebug() << QString::number(g_ExtFlashCRC.extFlash_CRC, 10);
            break;
        }
        case (WAVEFORM_CONFIG_ID): {
            break;
        }
        case (ACK_WAVEFORM_CONFIG_ID): {
            //            QMessageBox::information(this,tr("Information"),"WAVEFOMR Configured");
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Information,
                                                  "Info",
                                                  "WAVEFOMR Configured ",
                                                  QMessageBox::Ok);
            QTimer *msgBoxCloseTimer = new QTimer(this);
            msgBoxCloseTimer->setInterval(500);
            msgBoxCloseTimer->setSingleShot(true);
            connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject())); //or accept()

            msgBoxCloseTimer->start();

            msgBox->exec();
            //            qDebug() << "received from ACK_WAVEFORM_CONFIG_ID";
            break;
        }
        case (EXT_FLASH_ERASE_SUCESS): {
            QMessageBox::information(this,
                                     tr("Information"),
                                     "EXTERNAL FLASH ERASE OPERATION IS SUCCESSFUL");
            break;
        }
        case (EXT_FLASH_ERASE_FAIL): {
            QMessageBox::information(this,
                                     tr("Information"),
                                     "EXTERNAL FLASH ERASE OPERATION IS FAILED");
            break;
        }
        case (EXT_FLASH_NOT_EMPTY): {
            QMessageBox::information(this,
                                     tr("Information"),
                                     "EXTERNAL FLASH LOCATION IS NOT EMPTY, TRY WRITING TO ANOTHER "
                                     "LOCATION OR ERASE EXTERNAL FLASH ");
            break;
        }
        case (CRC_CHECK_FAIL): {
            QMessageBox::information(this,
                                     tr("Information"),
                                     "CRC CHECK FAILED MSG RECEIVED.CHECK THE MESSAGE TRANSMITTED");
            break;
        }
            // Updated READ_EXT_FLASH_DATA case
        case (READ_EXT_FLASH_DATA): {
            static uint8_t message_started = 0;
            QString filePath;

            // Copy data from received buffer to structure
            memcpy(&g_ReceivedTestPoint, rx_data.data(), sizeof(TestPoint_main));
            g_ReceivedTestPoint.MsgID = SEND_TP_PKT_ID;
            g_ReceivedTestPoint.CRC_WORD = 0;
            uint16_t calculate_CRC = CRCUtility::g_CRC_calc((uint8_t *) &g_ReceivedTestPoint,
                                                            g_ReceivedTestPoint.packetSize);
            g_ReceivedTestPoint.CRC_WORD = calculate_CRC;

            if (g_ReceivedTestPoint.FTU_TestNo <= 1001) {
                if (!message_started) {
                    message_started = 1;

                    // Select directory
                    QFileDialog fileDialog;
                    dir = fileDialog.getExistingDirectory(this,
                                                          "Select Directory to Save Files",
                                                          QDir::homePath());
                    if (dir.isEmpty()) {
                        return; // User canceled the directory selection
                    }

                    // Initialize progress dialog
                    progressDialog = new QProgressDialog("Saving files...", "Cancel", 0, 999, this);
                    progressDialog->setWindowModality(Qt::WindowModal);
                    progressDialog->setValue(0);
                }
                if (g_ReceivedTestPoint.FTU_TestNo != 1001) {
                    // Format the file name
                    QString fileName = QString("%1.bin").arg(g_ReceivedTestPoint.FTU_TestNo,
                                                             3,
                                                             10,
                                                             QChar('0'));

                    // Construct the full file path
                    filePath = QDir(dir).filePath(fileName);

                    // Open the file for writing
                    QFile file(filePath);
                    if (!file.open(QIODevice::WriteOnly)) {
                        QMessageBox::critical(this, "Error", "Could not open file for writing.");
                        return;
                    }

                    // Write the structure to the file
                    file.write(reinterpret_cast<char *>(&g_ReceivedTestPoint),
                               sizeof(TestPoint_main));
                    file.close();
                }
                // Update progress dialog
                progressDialog->setValue(g_TestPointNo);
                QCoreApplication::processEvents(); // Keep GUI responsive

                // Check if user canceled the operation
                if (progressDialog->wasCanceled()) {
                    QMessageBox::information(this,
                                             "Canceled",
                                             "Operation was canceled by the user.");
                    delete progressDialog;
                    progressDialog = nullptr;
                    message_started = 0;
                    g_TestPointNo = 0;
                    return;
                }
            }

            if (g_TestPointNo == 999) {
                QMessageBox::information(this, "Success", QString("All data saved to: %1").arg(dir));
                delete progressDialog; // Clean up progress dialog
                progressDialog = nullptr;
                message_started = 0;
                g_TestPointNo = 0;
            } else {
                g_TestPointNo++;
                //                qDebug() << QString::number(g_TestPointNo, 10);
                on_ReadDataFromFlash_clicked(); // Trigger the next read
            }
            break;
        }
            //----
        case (ABORT_SWITCH): {
            memcpy(&g_Momentary_Switch_Status, rx_data.data(), sizeof(g_Momentary_Switch_Status));
            if (g_Momentary_Switch_Status.Abort_Status == 1) {
                //                qDebug() << " ABORT SWITCH ON" << g_Momentary_Switch_Status.Abort_Status;
                ui->SRU_AbortSwitch_le->setText(
                    QString::number(g_Momentary_Switch_Status.Abort_Status));
                SRU_Abort_ON = QString::number(g_Momentary_Switch_Status.Abort_Status);

                if (g_Momentary_Switch_Status.Abort_Status == 1) {
                    ui->AbortSwitch_result_le->setText("PASS");
                    ui->AbortSwitch_result_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_Momentary_Switch_Status.Abort_Status == 0) {
                    SRU_Abort_ON = QString::number(g_Momentary_Switch_Status.Abort_Status);
                    ui->AbortSwitch_result_le->setText("FAIL");
                    ui->AbortSwitch_result_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Abort Switch Value ON Status: %1 Result:%2")
                                                   .arg(SRU_Abort_ON)
                                                   .arg(ui->AbortSwitch_result_le->text()));
            } else {
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                //                qDebug() << " ABORT SWITCH OFF" << g_Momentary_Switch_Status.Abort_Status;
                ui->SRU_AbortSwitch_le->setText(
                    QString::number(g_Momentary_Switch_Status.Abort_Status));

                if (g_Momentary_Switch_Status.Abort_Status == 0) {
                    SRU_Abort_OFF = QString::number(g_Momentary_Switch_Status.Abort_Status);
                    ui->AbortSwitch_result_le->setText("PASS");
                    ui->AbortSwitch_result_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_Momentary_Switch_Status.Abort_Status == 1) {
                    ui->AbortSwitch_result_le->setText("FAIL");
                    ui->AbortSwitch_result_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Abort Switch Value OFF Status: %1 Result:%2")
                        .arg(SRU_Abort_OFF)
                        .arg(ui->AbortSwitch_result_le->text()));
            }
            if ((SRU_Abort_ON == "1") && (SRU_Abort_OFF == "0")) {
                SRU_Abort_R = "PASS";
            } else {
                SRU_Abort_R = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Abort Switch ON OFF Result: %1").arg(SRU_Abort_ON));
            break;
        }
        case (PREP_SWITCH): {
            memcpy(&g_Momentary_Switch_Status, rx_data.data(), sizeof(g_Momentary_Switch_Status));
            if (g_Momentary_Switch_Status.Prep_Status == 1) {
                //                qDebug() << " PREP SWITCH ON" << g_Momentary_Switch_Status.Prep_Status;
                ui->SRU_PrepSwitch_le->setText(
                    QString::number(g_Momentary_Switch_Status.Prep_Status));
                SRU_Prep_ON = QString::number(g_Momentary_Switch_Status.Prep_Status);

                if (g_Momentary_Switch_Status.Prep_Status == 1) {
                    ui->PrepSwitch_result_le->setText("PASS");
                    ui->PrepSwitch_result_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_Momentary_Switch_Status.Prep_Status == 0) {
                    SRU_Prep_ON = QString::number(g_Momentary_Switch_Status.Prep_Status);

                    ui->PrepSwitch_result_le->setText("FAIL");
                    ui->PrepSwitch_result_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Prep Switch Value ON Status: %1 Result:%2")
                                                   .arg(SRU_Prep_ON)
                                                   .arg(ui->PrepSwitch_result_le->text()));
            } else {
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                //                qDebug() << "PREP SWITCH OFF" << g_Momentary_Switch_Status.Prep_Status;
                ui->SRU_PrepSwitch_le->setText(
                    QString::number(g_Momentary_Switch_Status.Prep_Status));
                if (g_Momentary_Switch_Status.Prep_Status == 0) {
                    SRU_Prep_OFF = QString::number(g_Momentary_Switch_Status.Prep_Status);

                    ui->PrepSwitch_result_le->setText("PASS");
                    ui->PrepSwitch_result_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_Momentary_Switch_Status.Prep_Status == 1) {
                    ui->PrepSwitch_result_le->setText("FAIL");
                    ui->PrepSwitch_result_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Prep Switch Value OFF Status: %1 Result:%2")
                                                   .arg(SRU_Prep_OFF)
                                                   .arg(ui->PrepSwitch_result_le->text()));
            }
            if ((SRU_Prep_ON == "1") && (SRU_Prep_OFF == "0")) {
                SRU_Prep_R = "PASS";
            } else {
                SRU_Prep_R = "FAIL";
            }
            SruLogger::instance()->logText(QString("Prep Switch ON OFF Result: %1").arg(SRU_Prep_R));
            break;
        }
        case (READY_INIT_SWITCH): {
            memcpy(&g_Momentary_Switch_Status, rx_data.data(), sizeof(g_Momentary_Switch_Status));
            if (g_Momentary_Switch_Status.Ready_Init_Status == 1) {
                //                qDebug() << " READY_INIT_SWITCH ON" << g_Momentary_Switch_Status.Ready_Init_Status;
                ui->SRU_ReadyInitSwitch_le->setText(
                    QString::number(g_Momentary_Switch_Status.Ready_Init_Status));
                if (g_Momentary_Switch_Status.Ready_Init_Status == 1) {
                    SRU_ReadyI_ON = QString::number(g_Momentary_Switch_Status.Ready_Init_Status);
                    ui->ReadyInitSwitch_result_le->setText("PASS");
                    ui->ReadyInitSwitch_result_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_Momentary_Switch_Status.Ready_Init_Status == 0) {
                    SRU_ReadyI_ON = QString::number(g_Momentary_Switch_Status.Ready_Init_Status);

                    ui->ReadyInitSwitch_result_le->setText("FAIL");
                    ui->ReadyInitSwitch_result_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Ready Init Switch Value ON Status: %1 Result:%2")
                        .arg(SRU_ReadyI_ON)
                        .arg(ui->ReadyInitSwitch_result_le->text()));
            } else {
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                //                qDebug() << "READY_INIT_SWITCH OFF" << g_Momentary_Switch_Status.Ready_Init_Status;
                ui->SRU_ReadyInitSwitch_le->setText(
                    QString::number(g_Momentary_Switch_Status.Ready_Init_Status));
                if (g_Momentary_Switch_Status.Prep_Status == 0) {
                    SRU_ReadyI_OFF = QString::number(g_Momentary_Switch_Status.Ready_Init_Status);

                    ui->ReadyInitSwitch_result_le->setText("PASS");
                    ui->ReadyInitSwitch_result_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_Momentary_Switch_Status.Ready_Init_Status == 1) {
                    ui->ReadyInitSwitch_result_le->setText("FAIL");
                    ui->ReadyInitSwitch_result_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Ready Init Switch Value OFF Status: %1 Result:%2")
                        .arg(SRU_ReadyI_OFF)
                        .arg(ui->ReadyInitSwitch_result_le->text()));
            }
            if ((SRU_ReadyI_ON == "1") && (SRU_ReadyI_OFF == "0")) {
                SRU_ReadyI_R = "PASS";
            } else {
                SRU_ReadyI_R = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Ready Init Switch ON OFF Result: %1").arg(SRU_ReadyI_R));
            break;
        }

        case (DISCRETE_IN_CH1): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_IN_CH1 ON";

            } else {
                //                qDebug() << "DISCRETE_IN_CH1 OFF";
            }
            break;
        }

        case (DISCRETE_IN_CH2): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_IN_CH2 ON";

            } else {
                //                qDebug() << "DISCRETE_IN_CH2 OFF";
            }
            break;
        }

        case (DISCRETE_IN_CH3): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_IN_CH3 ON";

            } else {
                //                qDebug() << "DISCRETE_IN_CH3 OFF";
            }
            break;
        }
        case (DISCRETE_OUT_CH1): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_OUT_CH1 ON";

            } else {
                //                qDebug() << "DISCRETE_OUT_CH1 OFF";
            }
            break;
        }

        case (DISCRETE_OUT_CH2): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_OUT_CH2 ON";

            } else {
                //                qDebug() << "DISCRETE_OUT_CH2 OFF";
            }
            break;
        }

        case (DISCRETE_OUT_CH3): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_OUT_CH3 ON";

            } else {
                //                qDebug() << "DISCRETE_OUT_CH3 OFF";
            }
            break;
        }

        case (DISCRETE_OUT_CH4): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_OUT_CH4 ON";

            } else {
                //                qDebug() << "DISCRETE_OUT_CH4 OFF";
            }
            break;
        }

        case (DISCRETE_OUT_CH5): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " DISCRETE_OUT_CH5 ON";

            } else {
                //                qDebug() << "DISCRETE_OUT_CH5 OFF";
            }
            break;
        }

        case (TPS_D1_1): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_1 ON";

            } else {
                //                qDebug() << "TPS_D1_1 OFF";
            }
            break;
        }

        case (TPS_D1_2): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_2 ON";

            } else {
                //                qDebug() << "TPS_D1_2 OFF";
            }
            break;
        }

        case (TPS_D1_3): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_3 ON";

            } else {
                //                qDebug() << "TPS_D1_3 OFF";
            }
            break;
        }

        case (TPS_D1_4): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_4 ON";

            } else {
                //                qDebug() << "TPS_D1_4 OFF";
            }
            break;
        }

        case (TPS_D1_5): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_5 ON";

            } else {
                //                qDebug() << "TPS_D1_5 OFF";
            }
            break;
        }

        case (TPS_D1_6): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_6 ON";

            } else {
                //                qDebug() << "TPS_D1_6 OFF";
            }
            break;
        }
        case (TPS_D1_7): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_7 ON";

            } else {
                //                qDebug() << "TPS_D1_7 OFF";
            }
            break;
        }

        case (TPS_D1_8): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_8 ON";

            } else {
                //                qDebug() << "TPS_D1_8 OFF";
            }
            break;
        }

        case (TPS_D1_9): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_9 ON";

            } else {
                //                qDebug() << "TPS_D1_9 OFF";
            }
            break;
        }

        case (TPS_D1_10): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D1_10 ON";

            } else {
                //                qDebug() << "TPS_D1_10 OFF";
            }
            break;
        }

        case (TPS_D2_1): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_1 ON";
            } else {
                //                qDebug() << " TPS_D2_1 OFF";
            }
            break;
        }

        case (TPS_D2_2): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_2 ON";
            } else {
                //                qDebug() << " TPS_D2_2 OFF";
            }
            break;
        }

        case (TPS_D2_3): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_3 ON";
            } else {
                //                qDebug() << " TPS_D2_3 OFF";
            }
            break;
        }
        case (TPS_D2_4): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_4 ON";
            } else {
                //                qDebug() << " TPS_D2_4 OFF";
            }
            break;
        }

        case (TPS_D2_5): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_5 ON";
            } else {
                //                qDebug() << " TPS_D2_5 OFF";
            }
            break;
        }
        case (TPS_D2_6): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_6 ON";
            } else {
                //                qDebug() << " TPS_D2_6 OFF";
            }
            break;
        }
        case (TPS_D2_7): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_7 ON";
            } else {
                //                qDebug() << " TPS_D2_7 OFF";
            }
            break;
        }
        case (TPS_D2_8): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_8 ON";
            } else {
                //                qDebug() << " TPS_D2_8 OFF";
            }
            break;
        }
        case (TPS_D2_9): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_9 ON";
            } else {
                //                qDebug() << " TPS_D2_9 OFF";
            }
            break;
        }
        case (TPS_D2_10): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D2_10 ON";
            } else {
                //                qDebug() << " TPS_D2_10 OFF";
            }
            break;
        }
        case (TPS_D3_1): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_1 ON";
            } else {
                //                qDebug() << " TPS_D3_1 OFF";
            }
            break;
        }

        case (TPS_D3_2): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_2 ON";
            } else {
                //                qDebug() << " TPS_D3_2 OFF";
            }
            break;
        }

        case (TPS_D3_3): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_3 ON";
            } else {
                //                qDebug() << " TPS_D3_3 OFF";
            }
            break;
        }

        case (TPS_D3_4): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_4 ON";
            } else {
                //                qDebug() << " TPS_D3_4 OFF";
            }
            break;
        }

        case (TPS_D3_5): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_5 ON";
            } else {
                //                qDebug() << " TPS_D3_5 OFF";
            }
            break;
        }

        case (TPS_D3_6): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_6 ON";
            } else {
                //                qDebug() << " TPS_D3_6 OFF";
            }
            break;
        }
        case (TPS_D3_7): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_7 ON";
            } else {
                //                qDebug() << " TPS_D3_7 OFF";
            }
            break;
        }
        case (TPS_D3_8): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_8 ON";
            } else {
                //                qDebug() << " TPS_D3_8 OFF";
            }
            break;
        }
        case (TPS_D3_9): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_9 ON";
            } else {
                //                qDebug() << " TPS_D3_9 OFF";
            }
            break;
        }
        case (TPS_D3_10): {
            if (g_SRU_SwitchSTS.SwitchSTS == 1) {
                //                qDebug() << " TPS_D3_10 ON";
            } else {
                //                qDebug() << " TPS_D3_10 OFF";
            }
            break;
        }
        case (CURRENT_SENSOR): {
            //  ProcessCurrentSensorData(rx_data);

            //            qDebug() << "CURRENT_SENSOR";
            memcpy(&g_CurrentSensorData, rx_data.data(), sizeof(CurrentSensorData));

            if (g_CurrentSensorData.curr_PS1 < 0)
                g_CurrentSensorData.curr_PS1 = 0;
            if (g_CurrentSensorData.curr_PS3 < 0)
                g_CurrentSensorData.curr_PS3 = 0;
            if (g_CurrentSensorData.curr_PS4 < 0)
                g_CurrentSensorData.curr_PS4 = 0;
            if (g_CurrentSensorData.curr_PS5 < 0)
                g_CurrentSensorData.curr_PS5 = 0;
            if (g_CurrentSensorData.curr_PS6 < 0)
                g_CurrentSensorData.curr_PS6 = 0;
            if (g_CurrentSensorData.curr_PS7 < 0)
                g_CurrentSensorData.curr_PS7 = 0;
            //            qDebug() << "in case" << rx_data;
            //------------CONTROLLER CARDS voltages, current-----------------//
            ui->CC_5V_Current_le->setText(QString::number(g_CurrentSensorData.curr_PS5, 'f', 4));
            str5I = ui->CC_5V_Current_le->text();
            float fixed_I5 = 0.300, I_5 = 0.0; //0.300A ±0.100A
            float I5 = ui->CC_5V_Current_le->text().toFloat();
            I_5 = I5 - fixed_I5;
            if ((I_5 >= -(0.100)) && (I_5 <= (0.100))) {
                rsI5 = "PASS";
            } else {
                rsI5 = "FAIL";
            }
            ui->CC_5V_le->setText(QString::number(g_Direct_Monitor.Input_Ch11));

            str5V = ui->CC_5V_le->text();
            float fixed_v5 = 5.0, d_5 = 0.0;
            float v5 = ui->CC_5V_le->text().toFloat();
            d_5 = v5 - fixed_v5;
            if ((d_5 >= -(0.20)) && (d_5 <= (0.20))) {
                rsV5 = "PASS";
            } else {
                rsV5 = "FAIL";
            }

            ui->CC_N_5v_Current_le->setText(QString::number(g_CurrentSensorData.curr_PS6, 'f', 4));

            strNI5 = ui->CC_N_5v_Current_le->text();
            float fixed_NI5 = 0.300, NI_5 = 0.0; //0.300A ±0.100A
            float NI5 = ui->CC_N_5v_Current_le->text().toFloat();
            NI_5 = NI5 - fixed_NI5;
            if ((NI_5 >= -(0.100)) && (NI_5 <= (0.100))) {
                rsNI5 = "PASS";
            } else {
                rsNI5 = "FAIL";
            }
            ui->CC_N_5v_le->setText(QString::number(g_Direct_Monitor.Input_Ch12));
            strNV5 = ui->CC_N_5v_le->text();
            float fixed_NV5 = -5.0, NV_5 = 0.0;
            float NV5 = ui->CC_N_5v_le->text().toFloat();
            NV_5 = NV5 - fixed_NV5;
            if ((NV_5 >= -(0.20)) && (NV_5 <= (0.20))) {
                rsNV5 = "PASS";
            } else {
                rsNV5 = "FAIL";
            }
            ui->CC_3p3_Current_Dig_le->setText(
                QString::number(g_CurrentSensorData.curr_PS4, 'f', 4));
            strI3 = ui->CC_3p3_Current_Dig_le->text();
            float fixed_I3 = 0.40, NI_3 = 0.0; //0.4A ±0.100A
            float NI3 = ui->CC_3p3_Current_Dig_le->text().toFloat();
            NI_3 = NI3 - fixed_I3;
            if ((NI_3 >= -(0.100)) && (NI_3 <= (0.100))) {
                rsI3 = "PASS";
            } else {
                rsI3 = "FAIL";
            }
            ui->CC_3p3_V_Dig_le->setText(QString::number(g_Direct_Monitor.Input_Ch10));
            strV3 = ui->CC_3p3_V_Dig_le->text();
            float fixed_V3 = 3.3, V_3 = 0.0;
            float V3 = ui->CC_3p3_V_Dig_le->text().toFloat();
            V_3 = V3 - fixed_V3;
            if ((V_3 >= -(0.20)) && (V_3 <= (0.20))) {
                rsV3 = "PASS";
            } else {
                rsV3 = "FAIL";
            }
            //-----------------------------------
            ui->Volt_3_3_current_le->setText(QString::number(g_CurrentSensorData.curr_PS4, 'f', 4));
            on_Volt_3_3_pb_clicked(true);

            ui->Volt_plus_5_current_le->setText(
                QString::number(g_CurrentSensorData.curr_PS5, 'f', 4));
            on_Volts_plus_5_pb_clicked();

            ui->Volt_minus_5_current_le->setText(
                QString::number(g_CurrentSensorData.curr_PS6, 'f', 4));
            on_Volts_minus_5_pb_clicked(true);

            ui->Volts_5_current_le->setText(QString::number(g_CurrentSensorData.curr_PS3, 'f', 4));
            on_Volt_5_pb_clicked(true);

            ui->Volt_28_current_le->setText(QString::number(g_CurrentSensorData.curr_PS1, 'f', 4));
            on_Volt_28_pb_clicked();

            ui->Volt_16_28_32_current_le->setText(
                QString::number(g_CurrentSensorData.curr_PS7, 'f', 4));
            ui->SRU_I_le->setText(
                QString::number(g_CurrentSensorData.curr_PS7, 'f', 4)); // SRU Current
            ui->Ip_Current_le->setText(
                QString::number(g_CurrentSensorData.curr_PS7, 'f', 4)); // BitTest Current

            emit PS7_Sig(ui->Volt_28_16_32_Cmb->currentIndex());
            if (ui->Volt_28_16_32_Cmb->currentIndex() == 1) {
                ui->Volt_16_28_32_le->setText(
                    QString::number(g_Direct_Monitor.Input_Ch6_16, 'f', 3));

                ui->LRU_VoltageLE->setText(QString::number(g_Direct_Monitor.Input_Ch6_16, 'f', 3));
                ui->SRU_V_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_16, 'f', 3));

                str1 = ui->Volt_16_28_32_le->text();
                str1_I = ui->Volt_16_28_32_current_le->text();
                //                qDebug() << "str1" << str1;
                float fixed_v16 = 16.0, d_16 = 0.0;
                float v16 = ui->Volt_16_28_32_le->text().toFloat();
                d_16 = v16 - fixed_v16;
                if ((d_16 >= -(1.00)) && (d_16 <= (1.00))) {
                    rs16 = "PASS";
                } else {
                    rs16 = "FAIL";
                }
            } else if (ui->Volt_28_16_32_Cmb->currentIndex() == 2) {
                ui->Volt_16_28_32_le->setText(
                    QString::number(g_Direct_Monitor.Input_Ch6_28, 'f', 3));

                ui->LRU_VoltageLE->setText(QString::number(g_Direct_Monitor.Input_Ch6_28, 'f', 3));
                ui->SRU_V_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_28, 'f', 3));
                str2 = ui->Volt_16_28_32_le->text();
                str2_I = ui->Volt_16_28_32_current_le->text();
                //                qDebug() << "str2" << str2;
                float fixed_v28 = 28.0, d_28 = 0.0;
                float v28 = ui->Volt_16_28_32_le->text().toFloat();
                d_28 = v28 - fixed_v28;
                if ((d_28 >= -(1.00)) && (d_28 <= (1.00))) {
                    rs_28 = "PASS";
                } else {
                    rs_28 = "FAIL";
                }
            } else if (ui->Volt_28_16_32_Cmb->currentIndex() == 3) {
                ui->Volt_16_28_32_le->setText(
                    QString::number(g_Direct_Monitor.Input_Ch6_32, 'f', 3));
                ui->LRU_VoltageLE->setText(QString::number(g_Direct_Monitor.Input_Ch6_32, 'f', 3));
                ui->SRU_V_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_32, 'f', 3));
                str3 = ui->Volt_16_28_32_le->text();
                str3_I = ui->Volt_16_28_32_current_le->text();
                //                qDebug() << "str3" << str3;
                float fixed_v32 = 32.0, diff_32 = 0.0;
                float v32 = ui->Volt_16_28_32_le->text().toFloat();
                diff_32 = v32 - fixed_v32;
                if ((diff_32 >= -(1.00)) && (diff_32 <= (1.00))) {
                    rs_32 = "PASS";
                } else {
                    rs_32 = "FAIL";
                }
            } else if (ui->Volt_28_16_32_Cmb->currentIndex() == 4) {
                ui->Volt_16_28_32_le->setText(
                    QString::number(g_Direct_Monitor.Input_ch6_Ext, 'f', 3));

                ui->LRU_VoltageLE->setText(QString::number(g_Direct_Monitor.Input_ch6_Ext, 'f', 3));
                ui->SRU_V_le->setText(QString::number(g_Direct_Monitor.Input_ch6_Ext, 'f', 3));
                str4 = ui->Volt_16_28_32_le->text();
                str4_I = ui->Volt_16_28_32_current_le->text();
                float f_28vol = 28.0, d_28vol = 0.0;
                float vol28 = ui->Volt_16_28_32_le->text().toFloat();
                d_28vol = vol28 - f_28vol;
                if ((d_28vol >= -(1.00)) && (d_28vol <= (1.00))) {
                    Ex_28 = "PASS";
                } else {
                    Ex_28 = "FAIL";
                }
            } else {
                ui->Volt_16_28_32_le->setText("OFF");

                ui->LRU_VoltageLE->setText("OFF");
                ui->SRU_V_le->setText("OFF");
            }

            SruLogger::instance()->logText("DC DC Voltage: " + ui->SRU_V_le->text());
            SruLogger::instance()->logText("DC DC Current: " + ui->SRU_I_le->text());

            break;
        }
        case (BITTEST): {
            break;
        }
        case (MOXA_Tx_1_RX_2): {
            hexString1 = message.toHex(' ').toUpper() + "  TS  "
                         + QDateTime::currentDateTime().toString("hh:mm:ss.zzz");

            uint8_t data[128] = {0};
            memcpy(&data[0], &g_Moxa_port1.data[0], 128 * sizeof(uint8_t));
            memcpy(&g_Moxa_port1, rx_data.data(), sizeof(g_Moxa_port1));
            if (memcmp(&data, &g_Moxa_port1.data, 128 * sizeof(uint8_t)) == 0) {
                //                qDebug() << "Rx ch2: timestamp data" << hexString1;
                //  ui->RS422_LOOP_BACK_le2->setText(hexString);
                rs422_r1 = "PASS";
                ui->RS422_LOOP_BACK_le1->setText(" PASS");
                ui->RS422_LOOP_BACK_le1->setStyleSheet("color:White");
                ui->RS422_LOOP_BACK_pb_1->setStyleSheet(GBC);
                ui->RS422_LOOP_BACK_pb_1->setChecked(false);
                if (g_mode_flag == AUTOMATIC_MODE) {
                    QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
                }
            }
            break;
        }
        case (MOXA_Tx_2_RX_1): {
            hexString2 = message.toHex(' ').toUpper() + "  TS  "
                         + QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
            //  qDebug() << "Rx ch1: timestamp data" << hexString2;

            uint8_t data[128] = {0};
            memcpy(&data[0], &g_Moxa_port2.data[0], 128 * sizeof(uint8_t));
            memcpy(&g_Moxa_port2, rx_data.data(), sizeof(g_Moxa_port2));
            if (memcmp(&data, &g_Moxa_port2.data, 128 * sizeof(uint8_t)) == 0) {
                rs422_r2 = "PASS";
                //                ui->RS422_LOOP_BACK_le1->setText(hexString2);
                ui->RS422_LOOP_BACK_le2->setText(" PASS");
                ui->RS422_LOOP_BACK_le2->setStyleSheet("color:White");
                ui->RS422_LOOP_BACK_pb_2->setStyleSheet(GBC);
                ui->RS422_LOOP_BACK_pb_2->setChecked(false);
                if (g_mode_flag == AUTOMATIC_MODE) {
                    QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
                }
            }
            break;
        }
        case (LRU_ADC_BIT_TEST): {
            if (Bittest_flag == true) {
                memcpy(&g_ADC_BIT_TEST, rx_data.data(), sizeof(ADC_BIT_TEST));
            }
            break;
        }
        case (LRU_RS422_BIT_TEST): {
            //            BitTestLogger::instance()->logText(
            //                "--------------Starting RS422 BIT Test.---------------");
            //            static bool data_received = false;
            memcpy(&g_RS422_TestPacket, rx_data.data(), sizeof(g_RS422_TestPacket));
            if (Bittest_flag == true) {
                static uint8_t count = 0;
                static QStringList last1Packets;
                auto formatPacket = [](const QString &hex) -> QString {
                    QString formatted1;
                    for (int i = 0; i < hex.length(); i += 80) {
                        formatted1 += hex.mid(i, 80) + "\n"; // Wrap at 80 chars
                    }
                    return formatted1.trimmed();
                };
                // ==== CRC CHECK ===
                // qDebug("g_checkCRC_word=%x\n", g_checkCRC_word);
                if (g_checkCRC_word == 0x967E) {
                    ObservCRC = "0x" + QString::number(g_checkCRC_word, 16).toUpper();
                }
                //===========Byte count=====
                l_counter = 0;
                l_counter2 = 0;
                for (uint16_t i = 0;
                     i < sizeof(g_RS422_TestPacket.payload) / sizeof(g_RS422_TestPacket.payload[0]);
                     i++) {
                    if (g_RS422_TestPacket.payload[i] == 0x55) {
                        l_counter++;
                    }

                    if (g_RS422_TestPacket.payload[i] == 0xaa) {
                        l_counter2++;
                    }
                }

                if ((g_checkCRC_word == 0x967E) && (l_counter == 512) && (l_counter2 == 512)) {
                    rs422_result = "PASS";
                    // BitTestLogger::instance()->logText("RS422 BIT Result: PASS");
                    g_BitTestLogger_PassFailCount.passCount_RS422++;

                } else {
                    rs422_result = "FAIL";
                    // BitTestLogger::instance()->logText("RS422 BIT Result: FAIL");
                    g_BitTestLogger_PassFailCount.failCount_RS422++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("RS422 Loop Back FAIL Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.failCount_RS422++));
                }

                if (count == 5) {
                    count = 0;
                    LRU_data.clear();
                    for (const QString &packet : last1Packets) {
                        LRU_data = formatPacket(packet) + "\n\n";
                    }

                    ui->RS422_listwidget->clear();
                    last1Packets.clear();
                    //                    data_received = false;
                } else {
                    count++;
                }
                if (!message.isEmpty()) {
                    hexMessage = message.toHex();
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("RS422 Message Received: %1").arg(hexMessage));

                    ui->RS422_listwidget->addItem(hexMessage);
                    ui->RS422_listwidget->scrollToBottom();
                    if (last1Packets.size() >= 5) {
                        last1Packets.pop_front();
                    }
                    last1Packets.append(hexMessage);
                    //                    data_received = true;
                    if (ui->checkBox_front_panel_lru_checks->isChecked()) {
                        if (g_USB_Port_Connect) {
                            g_USB_Port_Connect = false;
                            on_Bit_USB_port_clicked(true);
                            ui->Bit_USB_port->setChecked(false);
                            //                            emit Discrete_Input_Ch1(true);
                            //                            emit Discrete_Input_Ch2(true);
                            //                            emit Discrete_Input_Ch3(true);
                        }
                    }
                }
            }
            break;
        }
        case (LRU_MOM_ROT_BIT_TEST): {
            if (Bittest_flag == true) {
                //                BitTestLogger::instance()->logText(QString(
                //                    "-------------------[INFO] FRONT PANEL SWITCH STATUS:-------------------- "));
                memcpy(&g_Momentary_Switch_Status, rx_data.data(), sizeof(Momentary_Switch_Status));

                ui->Rotary_Update_Switch_Value_le->setText(
                    QString::number(g_Momentary_Switch_Status.Rotary_Update, 10)
                        .rightJustified(3, '0')); // Add leading zeros if necessary

                ui->Prep_Switch_value_le->setText(
                    QString::number(g_Momentary_Switch_Status.Prep_Status, 10));

                ui->Abort_Switch_value_le->setText(
                    QString::number(g_Momentary_Switch_Status.Abort_Status, 10));

                ui->Ready_Init_Switch_value_le->setText(
                    QString::number(g_Momentary_Switch_Status.Ready_Init_Status, 10));

                //                BitTestLogger::instance()->logText(
                //                    QString("Rotary switches 1 2 3 status: %1")
                //                        .arg(QString::number(g_Momentary_Switch_Status.Rotary_Update, 10)));
                if (ui->checkBox_front_panel_lru_checks->isChecked()) {
                } else {
                    if (g_Momentary_Switch_Status.Rotary_Update == 0) {
                        ui->Rotary_Update_Switch_status_le->setText("PASS");
                        ui->Rotary_Update_Switch_status_le->setStyleSheet("color : green");
                        g_BitTestLogger_PassFailCount.passCount_FrontPanel[0]++;
                    }

                    else {
                        ui->Rotary_Update_Switch_status_le->setText("FAIL");
                        ui->Rotary_Update_Switch_status_le->setStyleSheet("color : red");
                        g_BitTestLogger_PassFailCount.failCount_FrontPanel[0]++;
                        BitTestLogger::instance()->logText(
                            QString("Rotary_Update Switch Test FAIL Count: %1")
                                .arg(g_BitTestLogger_PassFailCount.failCount_FrontPanel[0]));
                    }

                    if (g_Momentary_Switch_Status.Abort_Status == 0) {
                        ui->Abort_Switch_status_le->setText("PASS");
                        ui->Abort_Switch_status_le->setStyleSheet("color : green");
                        g_BitTestLogger_PassFailCount.passCount_FrontPanel[1]++;

                    } else {
                        ui->Abort_Switch_status_le->setText("FAIL");
                        ui->Abort_Switch_status_le->setStyleSheet("color : red");
                        g_BitTestLogger_PassFailCount.failCount_FrontPanel[1]++;
                    }

                    if (g_Momentary_Switch_Status.Prep_Status == 0) {
                        ui->Prep_Switch_status_le->setText("PASS");
                        ui->Prep_Switch_status_le->setStyleSheet("color : green");

                        g_BitTestLogger_PassFailCount.passCount_FrontPanel[2]++;

                    } else {
                        ui->Prep_Switch_status_le->setText("FAIL");
                        ui->Prep_Switch_status_le->setStyleSheet("color : red");

                        g_BitTestLogger_PassFailCount.failCount_FrontPanel[2]++;
                    }

                    if (g_Momentary_Switch_Status.Ready_Init_Status == 0) {
                        ui->Ready_Init_Switch_status_le->setText("PASS");
                        ui->Ready_Init_Switch_status_le->setStyleSheet("color : green");

                        g_BitTestLogger_PassFailCount.passCount_FrontPanel[3]++;

                    } else {
                        ui->Ready_Init_Switch_status_le->setText("FAIL");
                        ui->Ready_Init_Switch_status_le->setStyleSheet("color : red");
                        g_BitTestLogger_PassFailCount.failCount_FrontPanel[3]++;
                    }
                }
            }
            break;
        }
        case (LRU_DIS_OUTS_BIT_TEST): {
            //qDebug() << "LRU_DIS_OUTS_BIT_TEST message" << message.toHex();
            //static uint8_t value[5] = {0};
            if (Bittest_flag == true) {
                //                BitTestLogger::instance()->logText(
                //                    QString("-----------------[INFO] Discrete Output Status:-----------------"));
                memcpy(&g_DIS_OutputsBIT_TEST, rx_data.data(), sizeof(g_DIS_OutputsBIT_TEST));
                emit DIS_OUT_Read_USB_Card();
                if (Input_5856_Card_2.Input_CH30
                    == 1 /*g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts == 1*/) {
                    ui->Discrete_op_result_Ch1_le->setText("PASS");
                    ui->Discrete_op_result_Ch1_le->setStyleSheet("color : green");
                    ui->Discrete_output_Ch1_pb->setChecked(false);
                    ui->Discrete_op_value_Ch1_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts));
                    g_BitTestLogger_PassFailCount.passCount_DOP[0]++;

                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 1 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.passCount_DOP[0]));

                } else {
                    ui->Discrete_op_result_Ch1_le->setText("FAIL");
                    ui->Discrete_op_result_Ch1_le->setStyleSheet("color : red");
                    ui->Discrete_output_Ch1_pb->setChecked(false);
                    ui->Discrete_op_value_Ch1_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts));
                    g_BitTestLogger_PassFailCount.failCount_DOP[0]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 1 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.failCount_DOP[0]));
                }
                //                BitTestLogger::instance()->logText(
                //                    QString("Output Channel 1 :%1 Status:[%2]")
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts)
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts == 1 ? "PASS" : "FAIL"));

                if (Input_5856_Card_2.Input_CH31
                    == 1 /*g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts == 1*/) {
                    ui->Discrete_op_result_Ch2_le->setText("PASS");
                    ui->Discrete_op_result_Ch2_le->setStyleSheet("color : green");
                    ui->Discrete_op_value_Ch2_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts));
                    g_BitTestLogger_PassFailCount.passCount_DOP[1]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 2 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.passCount_DOP[1]));

                } else {
                    ui->Discrete_op_result_Ch2_le->setText("FAIL");
                    ui->Discrete_op_result_Ch2_le->setStyleSheet("color : red");
                    ui->Discrete_op_value_Ch2_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts));
                    g_BitTestLogger_PassFailCount.failCount_DOP[1]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 2 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.failCount_DOP[1]));
                }
                //                BitTestLogger::instance()->logText(
                //                    QString("Output Channel 2 :%1 Status:[%2]")
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts)
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts == 1 ? "PASS" : "FAIL"));

                if (Input_5856_Card_2.Input_CH14
                    == 1 /*g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts == 1*/) {
                    ui->Discrete_op_result_Ch3_le->setText("PASS");
                    ui->Discrete_op_result_Ch3_le->setStyleSheet("color : green");
                    ui->Discrete_op_value_Ch3_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts));
                    g_BitTestLogger_PassFailCount.passCount_DOP[2]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 3 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.passCount_DOP[2]));
                } else {
                    ui->Discrete_op_result_Ch3_le->setText("FAIL");
                    ui->Discrete_op_result_Ch3_le->setStyleSheet("color : red");
                    ui->Discrete_op_value_Ch3_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts));
                    g_BitTestLogger_PassFailCount.failCount_DOP[2]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 3 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.failCount_DOP[2]));
                }
                //                BitTestLogger::instance()->logText(
                //                    QString("Output Channel 3 :%1  Status:[%2]")
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts)
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts == 1 ? "PASS" : "FAIL"));

                if (Input_5856_Card_2.Input_CH13
                    == 1 /*g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts == 1*/) {
                    ui->Discrete_op_result_Ch4_le->setText("PASS");
                    ui->Discrete_op_result_Ch4_le->setStyleSheet("color : green");
                    ui->Discrete_op_value_Ch4_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts));
                    g_BitTestLogger_PassFailCount.passCount_DOP[3]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 4 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.passCount_DOP[3]));

                } else {
                    ui->Discrete_op_result_Ch4_le->setText("FAIL");
                    ui->Discrete_op_result_Ch4_le->setStyleSheet("color : red");
                    ui->Discrete_op_value_Ch4_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts));
                    g_BitTestLogger_PassFailCount.failCount_DOP[3]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 4 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.failCount_DOP[3]));
                }

                //                BitTestLogger::instance()->logText(
                //                    QString("Output Channel 4: %1 Status:[%2]")
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts)
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts == 1 ? "PASS" : "FAIL"));

                if (Input_5856_Card_2.Input_CH12
                    == 1 /*g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts == 1*/) {
                    ui->Discrete_op_result_Ch5_le->setText("PASS");
                    ui->Discrete_op_result_Ch5_le->setStyleSheet("color : green");
                    ui->Discrete_op_value_Ch5_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts));
                    g_BitTestLogger_PassFailCount.passCount_DOP[4]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 5 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.passCount_DOP[4]));
                } else {
                    ui->Discrete_op_result_Ch5_le->setText("FAIL");
                    ui->Discrete_op_result_Ch5_le->setStyleSheet("color : red");
                    ui->Discrete_op_value_Ch5_le->setText(
                        QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts));
                    g_BitTestLogger_PassFailCount.failCount_DOP[4]++;
                    //                    BitTestLogger::instance()->logText(
                    //                        QString("Discrete Output Channel 5 Count: %1")
                    //                            .arg(g_BitTestLogger_PassFailCount.failCount_DOP[4]));
                }
                //                BitTestLogger::instance()->logText(
                //                    QString("Output Channel 5: %1 Status:[%2]")
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts)
                //                        .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts == 1 ? "PASS" : "FAIL"));
            }
            break;
        }
        case (LRU_DIS_INS_BIT_TEST): {
            if (Bittest_flag == true) {
                //                BitTestLogger::instance()->logText(
                //                    QString("--------------[INFO] Discrete Input channel status ---------------"));

                memcpy(&g_DIS_InputsBIT_TEST, rx_data.data(), sizeof(g_DIS_InputsBIT_TEST));
                //                emit Discrete_Input_Ch1(true);

                if (g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1) {
                    ui->Discrete_Ip_result_Ch1_le->setStyleSheet("color : green");
                    ui->Discrete_Ip_result_Ch1_le->setText("PASS");
                    g_BitTestLogger_PassFailCount.passCount_DIP[0]++;
                    //                    ui->Discrete_ip_value_Ch1_le->setText(
                    //                        QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts));
                } else {
                    ui->Discrete_Ip_result_Ch1_le->setText("FAIL");
                    ui->Discrete_Ip_result_Ch1_le->setStyleSheet("color : red");
                    g_BitTestLogger_PassFailCount.failCount_DIP[0]++;

                    //                    ui->Discrete_ip_value_Ch1_le->setText(
                    //                        QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts));
                }
                ui->Discrete_ip_value_Ch1_le->setText(
                    QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts));
                //                BitTestLogger::instance()->logText(
                //                    QString("Input Channel 1:%1 Status:[%2]")
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts)
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1 ? "PASS" : "FAIL"));
                //                BitTestLogger::instance()->logText(
                //                    QString("Input Channel 1:%1 Count:[%2]")
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts)
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1
                //                                 ? g_BitTestLogger_PassFailCount.passCount_DIP[0]
                //                                 : g_BitTestLogger_PassFailCount.failCount_DIP[0]));

                if (g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1) {
                    ui->Discrete_Ip_result_Ch2_le->setText("PASS");

                    ui->Discrete_Ip_result_Ch2_le->setStyleSheet("color : green");
                    ui->Discrete_ip_value_Ch2_le->setText(
                        QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts));
                    g_BitTestLogger_PassFailCount.passCount_DIP[1]++;

                } else {
                    ui->Discrete_Ip_result_Ch2_le->setText("FAIL");

                    ui->Discrete_Ip_result_Ch2_le->setStyleSheet("color : red");
                    ui->Discrete_ip_value_Ch2_le->setText(
                        QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts));
                    g_BitTestLogger_PassFailCount.failCount_DIP[1]++;
                }
                //                BitTestLogger::instance()->logText(
                //                    QString("Input Channel 2: %1  Status:[%2]")
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts)
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1 ? "PASS" : "FAIL"));
                //                BitTestLogger::instance()->logText(
                //                    QString("Input Channel 2: %1  Count:[%2]")
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts)
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1
                //                                 ? g_BitTestLogger_PassFailCount.passCount_DIP[1]
                //                                 : g_BitTestLogger_PassFailCount.failCount_DIP[1]));

                if (g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1) {
                    ui->Discrete_Ip_result_Ch3_le->setText("PASS");
                    ui->Discrete_Ip_result_Ch3_le->setStyleSheet("color : green");
                    ui->Discrete_ip_value_Ch3_le->setText(
                        QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts));

                    g_BitTestLogger_PassFailCount.passCount_DIP[2]++;
                } else {
                    ui->Discrete_Ip_result_Ch3_le->setText("FAIL");

                    ui->Discrete_Ip_result_Ch3_le->setStyleSheet("color : red");
                    ui->Discrete_ip_value_Ch3_le->setText(
                        QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts));
                    g_BitTestLogger_PassFailCount.failCount_DIP[2]++;
                }
                //                BitTestLogger::instance()->logText(
                //                    QString("Input Channel 3: %1 Status:[%2]")
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts)
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1 ? "PASS" : "FAIL"));
                //                BitTestLogger::instance()->logText(
                //                    QString("Input Channel 3: %1 Count:[%2]")
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts)
                //                        .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1
                //                                 ? g_BitTestLogger_PassFailCount.passCount_DIP[2]
                //                                 : g_BitTestLogger_PassFailCount.failCount_DIP[2]));
            }
            break;
        }
        case (LRU_CRC_BIT_TEST): {
            //            qDebug() << "received EXT Flash crc" << rx_data.data();

            memcpy(&g_CRC_BIT_TEST, rx_data.data(), sizeof(g_CRC_BIT_TEST));
            //            qDebug() << "InternalFlash_CRC"
            //                     << QString::number(g_CRC_BIT_TEST.InternalFlash_CRC, 16);
            //           qDebug() << "ExternalFlash_CRC"
            //                     << QString::number(g_CRC_BIT_TEST.ExternalFlash_CRC, 16); //e089

            //            ui->LRU_Checksum_le->setText("0x"
            //                                         + QString::number(g_Post_Status_data.AppFlash_SW_CRC, 16)
            //                                               .toUpper()
            //                                               .rightJustified(4, '0'));

            ui->LRU_Checksum_le->setText(
                QString("0x%1")
                    .arg(g_CRC_BIT_TEST.InternalFlash_CRC, 4, 16, QLatin1Char('0'))
                    .toUpper());
            //            ui->CC_cksum_le->setText(QString::number(g_CRC_BIT_TEST.ExternalFlash_CRC, 16));
            ui->CC_cksum_le->setText(
                "0x" + QString::number(g_Post_Status_data.AppFlash_SW_CRC, 16).toUpper());
            SruLogger::instance()->logText(
                QString("0x") + QString::number(g_Post_Status_data.AppFlash_SW_CRC, 16).toUpper());
            break;
        }
        case (LRU_POST_STATUS_BIT_TEST): {
            //            if (Bittest_flag == true) {

            memcpy(&g_Post_Status_data, rx_data.data(), sizeof(g_Post_Status_data));
            //items;
            items.clear();
            ui->POST_listW->clear();
            ui->CC_POST_listw->clear();
            items << " -------------POST DATA ---------------------- "
                  << "Serviceability of display elements   "
                         + QString::number(g_Post_Status_data.Display_status_1, 16).toUpper()
                  << "Software Identification  0x"
                         + QString::number(g_Post_Status_data.App_SW_Idetification, 16).toUpper()
                  << "Software CRC  "
                         + QString::number(g_Post_Status_data.AppFlash_SW_CRC, 16).toUpper()
                  << "External Flash software Identification  "
                         + QString::number(g_Post_Status_data.EXT_Flash_SW_Idetification, 16)
                               .toUpper()

                  << "Device :S25FL512S"
                  << "Manufacturer ID(hex): "
                         + QString::number(g_Post_Status_data.EXT_Flash_SW_CRC & 0x00FF, 16)
                               .toUpper()
                               .rightJustified(2, '0')
                  << "Device ID(hex): "
                         + QString::number(g_Post_Status_data.EXT_Flash_SW_CRC >> 8 & 0xFF, 16)
                               .toUpper()
                  << "Hardware Self Test in Progress  "
                         + QString::number(g_Post_Status_data.Display_status_2, 16).toUpper()
                  << "Ready Init LED blink Status ON-OFF  "
                         + QString::number(g_Post_Status_data.ABORT_READY_INIT_LED_BLINK_STATUS, 2)
                               .toUpper();
            QString rs422Line = "RS422 Loop Back: \n";

            auto appendArray = [&](const QString &label, const uint8_t *arr) {
                rs422Line += label + " : ";
                for (int i = 0; i < 5; ++i) {
                    rs422Line += QString::number(arr[i]) + "   ";
                }
                rs422Line += "\n";
            };

            appendArray("TX1 - Transmit Data channel 1 ", g_Post_Status_data.TX1); //12345
            appendArray("RX2 - Received Data channel 2 ", g_Post_Status_data.RX2); //12345
            appendArray("TX2 - Transmit Data channel 2 ", g_Post_Status_data.TX2); //678910
            appendArray("RX1 - Received Data channel 1 ", g_Post_Status_data.RX1); //678910

            rs422Line = rs422Line.trimmed(); // remove trailing space
            items << rs422Line;

            items << "Displays all Measured Voltages    "
                  << "At 5V Observed " + QString::number(g_Post_Status_data.P5V, 'f', 4) + "    "
                  << "Analog 3.3V Observed " + QString::number(g_Post_Status_data.ANA_3p3V, 'f', 4)
                         + "     "
                  << "At -5V Observed " + QString::number(g_Post_Status_data.N5V, 'f', 4) + "    "
                  << "At -4.6V Observed " + QString::number(g_Post_Status_data.N4P6, 'f', 4)
                         + "    "
                  << "At 4.6V Observed " + QString::number(g_Post_Status_data.P4P6, 'f', 4) + "    "
                  << "Digital 3.3V Observed " + QString::number(g_Post_Status_data.DIG_3p3, 'f', 4);
            float vol = 4.6f;

            items << "DAC Voltages      "

                  << "DAC 1: " + QString::number(g_Post_Status_data.DAC1_1V * vol, 'f', 2) + "   "
                  << "DAC 2: " + QString::number(g_Post_Status_data.DAC2_1V * vol, 'f', 2) + "   "
                  << "DAC 3: " + QString::number(g_Post_Status_data.DAC3_1V * vol, 'f', 2) + "   "
                  << "DAC 4: " + QString::number(g_Post_Status_data.DAC4_1V * vol, 'f', 2) + "   "
                  << "DAC 5: " + QString::number(g_Post_Status_data.DAC5_1V * vol, 'f', 2) + "   "
                  << "DAC 6: " + QString::number(g_Post_Status_data.DAC6_1V * vol, 'f', 2) + "   "
                  << "DAC 7: " + QString::number(g_Post_Status_data.DAC7_1V * vol, 'f', 2) + "   "
                  << "DAC 8: " + QString::number(g_Post_Status_data.DAC8_1V * vol, 'f', 2);

            ui->POST_listW->addItems(items);
            QString fullLogEntry = items.join("\n");
            // BitTestLogger::instance()->logText(fullLogEntry);
            //            BitTestLogger::instance()->logText(
            //                QString("POST pass count incremented to %1")
            //                    .arg(g_BitTestLogger_PassFailCount.passCount_post++));

            ui->CC_POST_listw->addItems(items);
            SruLogger::instance()->logText(fullLogEntry);
            if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                g_SRU_CTRL_sequence_counter = 1;
                QMetaObject::invokeMethod(this, "SRU_CTRL_AutoStepCompleted", Qt::QueuedConnection);
            }
            break;
        }
        case (BIT_TEST_USB_PORT_P1): {
            bool formated = false;
            memcpy(&g_Moxa_port1, rx_data.data(), sizeof(g_Moxa_port1));
            g_Moxa_port1.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port1,
                                                           sizeof(Moxa_port));
            QString USBPat1 = message.toHex(); // Converts binary data to hex
            formattedUSBPat1.clear();
            if (!formated) {
                int lineLength = 80;

                for (int i = 0; i < USBPat1.length(); i += lineLength) {
                    formattedUSBPat1 += USBPat1.mid(i, lineLength) + "<br>";
                }
                formated = true;
            }
            Bit_usb_data
                = "512 bytes of pattern 0xA5, observed CrcCheckSum = "
                  + QString("0x%1").arg(g_Moxa_port1.CRC_WORD, 4, 16, QLatin1Char('0')).toUpper();
            ui->USB_Pat1_Data_LE->setText(Bit_usb_data);
            if (g_Moxa_port1.CRC_WORD == 0x3A92) {
                l_Usb_p1 = "PASS";
            } else {
                l_Usb_p1 = "FAIL";
            }
            break;
        }
        case (BIT_TEST_USB_PORT_P2): {
            memcpy(&g_Moxa_port1, rx_data.data(), sizeof(g_Moxa_port1));
            g_Moxa_port1.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port1,
                                                           sizeof(Moxa_port));
            bool formated = false;
            QString USBPat2 = message.toHex(); // Converts binary data to hex
            formattedUSBPat2.clear();
            if (!formated) {
                int lineLength = 80;

                for (int i = 0; i < USBPat2.length(); i += lineLength) {
                    formattedUSBPat2 += USBPat2.mid(i, lineLength) + "<br>";
                }
                formated = true;
            }
            Bit_usb_data1
                = "512 bytes of pattern 0xF5, observed CrcCheckSum = "
                  + QString("0x%1").arg(g_Moxa_port1.CRC_WORD, 4, 16, QLatin1Char('0')).toUpper();
            ui->USB_Pat2_Data_LE->setText(Bit_usb_data1);
            if (g_Moxa_port1.CRC_WORD == 0xD7CF) {
                l_Usb_p2 = "PASS";

            } else {
                l_Usb_p2 = "FAIL";
            }
            break;
        }
        case (SRUCTRL_Rx1): {
            // qDebug() << "SRUCTRL_Rx1 message" << message.toHex();
            RX1_Pat1 = message.toHex(' ').toUpper();
            uint8_t data[5] = {0};
            memcpy(&data[0], &g_Moxa_port1.data[0], 5 * sizeof(uint8_t));
            memcpy(&g_Moxa_port1, rx_data.data(), sizeof(g_Moxa_port1));
            if (memcmp(&data, &g_Moxa_port1.data, 5 * sizeof(uint8_t)) == 0) {
                // They are equal

                ui->CC_CH1_TX_le->setText("Transmitted pattern 0xA5A5 of 128 Bytes and verified");
                SruLogger::instance()->logText(QString("Channel 1 Recevied Data:%1").arg(RX1_Pat1));
                ui->CC_CH1_TX_le->setStyleSheet("background-color:#ffffff;color:black");
                // ui->CC_Status_CH1_le->setText(" PASS");
                ui->CC_Ch1_TX_pb->setStyleSheet(GBC);
                CC_Ch1 = "PASS";
                SruLogger::instance()->logText(QString("Channel 1 Result:%1").arg(CC_Ch1));
                ui->CC_Ch1_TX_pb->setChecked(false);
                TimeOutTimer->stop();

                //tx-----------------second pattern
                g_Moxa_port1.StartMsg = 0x24;
                g_Moxa_port1.MsgID = SRUCTRL_Rx1;
                g_time_out_state = SRUCTRL_Rx1;
                g_time_out_flag = 1;
                g_Moxa_port1.packetSize = sizeof(Moxa_port);
                for (int i = 0; i < 128; i++) {
                    g_Moxa_port1.data[i] = 0xF5AF;
                }
                g_Moxa_port1.CRC_WORD = 0;
                g_Moxa_port1.EndMsg = 0x233B;
                g_Moxa_port1.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port1,
                                                               sizeof(Moxa_port));
                // emit SRU_CTRL_USB_Write((char *) &g_Moxa_port1, sizeof(Moxa_port));
                QByteArray packet(reinterpret_cast<const char *>(&g_Moxa_port1),
                                  sizeof(g_Moxa_port1));
                emit serialWrite(packet, packet.size());
            }
            break;
        }
        case (SRUCTRL_Rx1_PAT2): {
            RX1_Pat2 = message.toHex(' ').toUpper();

            uint8_t data[5] = {0};
            memcpy(&data[0], &g_Moxa_port1.data[0], 5 * sizeof(uint8_t));
            memcpy(&g_Moxa_port1, rx_data.data(), sizeof(g_Moxa_port1));
            if (memcmp(&data, &g_Moxa_port1.data, 5 * sizeof(uint8_t)) == 0) {
                // They are equal

                ui->CC_CH1_RX_le->setText("Transmitted pattern 0xF5F5 of 128 Bytes and verified");
                //   Transmission and verification of 512 bytes of 0xF5F5 pattern completed successfully."
                SruLogger::instance()->logText(QString("Channel 1 Recevied Data:%1").arg(RX1_Pat2));
                ui->CC_CH1_RX_le->setStyleSheet("background-color:#ffffff;color:blue");
                // ui->CC_Status_CH1_le->setText(" PASS");
                ui->CC_Ch1_TX_pb->setStyleSheet(GBC);
                CC_Ch1 = "PASS";
                SruLogger::instance()->logText(QString("Channel 1 Result:%1").arg(CC_Ch1));
                ui->CC_Ch1_TX_pb->setChecked(false);
                TimeOutTimer->stop();
            }
            if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                QMetaObject::invokeMethod(this, "SRU_CTRL_AutoStepCompleted", Qt::QueuedConnection);
            }
            break;
        }
        case (SRUCTRL_Rx2): {
            RX2_Pat1 = message.toHex(' ').toUpper();
            //            qDebug() << "Rx2_pat1" << RX2_Pat1;
            uint8_t data[5] = {0};
            memcpy(&data[0], &g_Moxa_port2.data[0], 5 * sizeof(uint8_t));
            memcpy(&g_Moxa_port2, rx_data.data(), sizeof(g_Moxa_port2));
            if (memcmp(&data, &g_Moxa_port2.data, 5 * sizeof(uint8_t)) == 0) {
                // qDebug() << "Rx ch2: timestamp data" << RX2;
                ui->CC_CH2_TX_le->setText("Transmitted pattern 0xA5A5 of 128 Bytes and verified");
                SruLogger::instance()->logText(QString("Channel 2 Recevied Data:%1").arg(RX2_Pat1));
                ui->CC_CH2_TX_le->setStyleSheet("background-color:#ffffff;color:black");
                // ui->CC_Status_CH2_le->setText(" PASS");
                ui->CC_Ch2_TX_pb->setStyleSheet(GBC);
                CC_Ch2 = "PASS";
                SruLogger::instance()->logText(QString("Channel 2 Result:%1").arg(CC_Ch2));
                ui->CC_Ch2_TX_pb->setChecked(false);
                TimeOutTimer->stop();
                // ch2 tx------------------second pattern
                g_Moxa_port2.StartMsg = 0x24;
                g_Moxa_port2.MsgID = SRUCTRL_Rx2;
                g_time_out_state = SRUCTRL_Rx2;
                g_time_out_flag = 1;
                g_Moxa_port2.packetSize = sizeof(Moxa_port);
                for (int i = 0; i < 128; i++) {
                    g_Moxa_port2.data[i] = 0xF5AF;
                }
                g_Moxa_port2.CRC_WORD = 0;
                g_Moxa_port2.EndMsg = 0x233B;
                g_Moxa_port2.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port2,
                                                               sizeof(Moxa_port));
                QByteArray packet(reinterpret_cast<const char *>(&g_Moxa_port2),
                                  sizeof(g_Moxa_port2));
                emit serialWrite(packet, packet.size());
            }
            break;
        }
        case (SRUCTRL_Rx2_PAT2): {
            RX2_Pat2 = message.toHex(' ').toUpper();

            //            qDebug() << "pattern2 ch2" << RX2_Pat2;
            uint8_t data[5] = {0};
            memcpy(&data[0], &g_Moxa_port2.data[0], 5 * sizeof(uint8_t));
            memcpy(&g_Moxa_port2, rx_data.data(), sizeof(g_Moxa_port2));
            if (memcmp(&data, &g_Moxa_port2.data, 5 * sizeof(uint8_t)) == 0) {
                //                 qDebug() << "Rx ch2: timestamp data" << RX2;
                ui->CC_CH2_RX_le->setText("Transmitted pattern 0xFAF5 of 128 Bytes and verified");
                SruLogger::instance()->logText(QString("Channel 2 Recevied Data:%1").arg(RX2_Pat2));
                ui->CC_CH2_RX_le->setStyleSheet("background-color:#ffffff;color:blue");
                // ui->CC_Status_CH2_le->setText(" PASS");
                ui->CC_Ch2_TX_pb->setStyleSheet(GBC);
                CC_Ch2 = "PASS";
                SruLogger::instance()->logText(QString("Channel 2 Result:%1").arg(CC_Ch2));
                ui->CC_Ch2_TX_pb->setChecked(false);
                TimeOutTimer->stop();
            }
            if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                QMetaObject::invokeMethod(this, "SRU_CTRL_AutoStepCompleted", Qt::QueuedConnection);
            }
            break;
        }
        case (SRU_DIS_OUT1_STS): {
            emit DIS_OUT_Read_USB_Card();
            QThread::msleep(1);
            //            memcpy(&g_DIS_OutputsBIT_TEST, rx_data.data(), sizeof(g_DIS_OutputsBIT_TEST));

            if ((Input_5856_Card_2.Input_CH30 == 1)
                && (g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts == 1)) {
                Dis_Out1_ON.clear();
                SRU_Dis_out1.clear();

                //                qDebug() << "SRU_DIS_OUT1_STS" << Input_5856_Card_2.Input_CH30;
                ui->CC_Discrete_ch1_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH30));
                Dis_Out1_ON = QString::number(Input_5856_Card_2.Input_CH30);
                ui->CC_Discrete_OP_ch1_R_le->setText("PASS");
                ui->CC_Discrete_OP_ch1_R_le->setStyleSheet(GBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 1 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out1_ON)
                        .arg(ui->CC_Discrete_OP_ch1_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else if ((Input_5856_Card_2.Input_CH30 == 0)
                       && (g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts == 1)) {
                ui->CC_Discrete_ch1_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH30));
                Dis_Out1_ON = QString::number(Input_5856_Card_2.Input_CH30);
                ui->CC_Discrete_OP_ch1_R_le->setText("FAIL");
                ui->CC_Discrete_OP_ch1_R_le->setStyleSheet(RBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 1 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out1_ON)
                        .arg(ui->CC_Discrete_OP_ch1_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else {
                ui->CC_Discrete_ch1_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH30));
                SRU_Dis_out1 = QString::number(Input_5856_Card_2.Input_CH30);
                //                qDebug() << "SRU_Dis_out1" << SRU_Dis_out1;
                if (Input_5856_Card_2.Input_CH30 == 0) {
                    ui->CC_Discrete_OP_ch1_R_le->setText("PASS");
                    ui->CC_Discrete_OP_ch1_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Discrete_OP_ch1_R_le->setText("FAIL");
                    ui->CC_Discrete_OP_ch1_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete Channel 1 Output Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_out1)
                        .arg(ui->CC_Discrete_OP_ch1_R_le->text()));
            }
            if ((Dis_Out1_ON == "1") && (SRU_Dis_out1 == "0")) {
                Dis_Out_R1 = "PASS";
            } else {
                Dis_Out_R1 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Channel 1 Output ON OFF Result:%1").arg(Dis_Out_R1));
            break;
        }
        case (SRU_DIS_OUT2_STS): {
            emit DIS_OUT_Read_USB_Card();
            QThread::msleep(1);
            if ((Input_5856_Card_2.Input_CH31 == 1)
                && (g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts == 1)) {
                Dis_Out2_ON.clear();
                SRU_Dis_out2.clear();
                //                qDebug() << "SRU_DIS_OUT2_STS" << Input_5856_Card_2.Input_CH31;
                Dis_Out2_ON = QString::number(Input_5856_Card_2.Input_CH31);
                ui->CC_Discrete_ch2_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH31));
                ui->CC_Discrete_OP_ch2_R_le->setText("PASS");
                ui->CC_Discrete_OP_ch2_R_le->setStyleSheet(GBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 2 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out2_ON)
                        .arg(ui->CC_Discrete_OP_ch2_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else if ((Input_5856_Card_2.Input_CH31 == 0)
                       && (g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts == 1)) {
                ui->CC_Discrete_ch2_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH31));
                Dis_Out2_ON = QString::number(Input_5856_Card_2.Input_CH31);
                ui->CC_Discrete_OP_ch2_R_le->setText("FAIL");
                ui->CC_Discrete_OP_ch2_R_le->setStyleSheet(RBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 2 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out2_ON)
                        .arg(ui->CC_Discrete_OP_ch2_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else {
                //                qDebug() << "SRU_DIS_OUT2_STS" << Input_5856_Card_2.Input_CH31;
                ui->CC_Discrete_ch2_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH31));
                SRU_Dis_out2 = QString::number(Input_5856_Card_2.Input_CH31);
                if (Input_5856_Card_2.Input_CH31 == 0) {
                    ui->CC_Discrete_OP_ch2_R_le->setText("PASS");
                    ui->CC_Discrete_OP_ch2_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Discrete_OP_ch2_R_le->setText("FAIL");
                    ui->CC_Discrete_OP_ch2_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete Channel 2 Output Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_out2)
                        .arg(ui->CC_Discrete_OP_ch2_R_le->text()));
            }
            if ((Dis_Out2_ON == "1") && (SRU_Dis_out2 == "0")) {
                Dis_Out_R2 = "PASS";
            } else {
                Dis_Out_R2 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Channel 2 Output ON OFF Result:%1").arg(Dis_Out_R2));
            break;
        }
        case (SRU_DIS_OUT3_STS): {
            emit DIS_OUT_Read_USB_Card();
            QThread::msleep(1);
            //            memcpy(&g_DIS_OutputsBIT_TEST, rx_data.data(), sizeof(g_DIS_OutputsBIT_TEST));

            if ((Input_5856_Card_2.Input_CH14 == 1)
                && (g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts == 1)) {
                Dis_Out3_ON.clear();
                SRU_Dis_out3.clear();
                //                qDebug() << "SRU_DIS_OUT3_STS" << Input_5856_Card_2.Input_CH14;
                ui->CC_Discrete_ch3_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH14));
                Dis_Out3_ON = QString::number(Input_5856_Card_2.Input_CH14);
                ui->CC_Discrete_OP_ch3_R_le->setText("PASS");
                ui->CC_Discrete_OP_ch3_R_le->setStyleSheet(GBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 3 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out3_ON)
                        .arg(ui->CC_Discrete_OP_ch3_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else if ((Input_5856_Card_2.Input_CH14 == 0)
                       && (g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts == 1)) {
                ui->CC_Discrete_ch3_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH14));
                Dis_Out3_ON = QString::number(Input_5856_Card_2.Input_CH14);
                ui->CC_Discrete_OP_ch3_R_le->setText("FAIL");
                ui->CC_Discrete_OP_ch3_R_le->setStyleSheet(RBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 3 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out3_ON)
                        .arg(ui->CC_Discrete_OP_ch3_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else {
                ui->CC_Discrete_ch3_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH14));
                SRU_Dis_out3 = QString::number(Input_5856_Card_2.Input_CH14);
                if (Input_5856_Card_2.Input_CH14 == 0) {
                    ui->CC_Discrete_OP_ch3_R_le->setText("PASS");
                    ui->CC_Discrete_OP_ch3_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Discrete_OP_ch3_R_le->setText("FAIL");
                    ui->CC_Discrete_OP_ch3_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete Channel 3 Output Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_out3)
                        .arg(ui->CC_Discrete_OP_ch3_R_le->text()));
            }
            if ((Dis_Out3_ON == "1") && (SRU_Dis_out3 == "0")) {
                Dis_Out_R3 = "PASS";
            } else {
                Dis_Out_R3 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Channel 3 Output ON OFF Result:%1").arg(Dis_Out_R3));
            break;
        }
        case (SRU_DIS_OUT4_STS): {
            emit DIS_OUT_Read_USB_Card();
            QThread::msleep(1);
            //            memcpy(&g_DIS_OutputsBIT_TEST, rx_data.data(), sizeof(g_DIS_OutputsBIT_TEST));

            if ((Input_5856_Card_2.Input_CH13 == 1)
                && (g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts == 1)) {
                Dis_Out4_ON.clear();
                SRU_Dis_out4.clear();
                //                qDebug() << "SRU_DIS_OUT4_STS" << Input_5856_Card_2.Input_CH13;
                ui->CC_Discrete_ch4_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH13));
                Dis_Out4_ON = QString::number(Input_5856_Card_2.Input_CH13);

                ui->CC_Discrete_OP_ch4_R_le->setText("PASS");
                ui->CC_Discrete_OP_ch4_R_le->setStyleSheet(GBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 4 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out4_ON)
                        .arg(ui->CC_Discrete_OP_ch4_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else if ((Input_5856_Card_2.Input_CH13 == 0)
                       && (g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts == 1)) {
                ui->CC_Discrete_ch4_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH13));
                Dis_Out4_ON = QString::number(Input_5856_Card_2.Input_CH13);
                ui->CC_Discrete_OP_ch4_R_le->setText("FAIL");
                ui->CC_Discrete_OP_ch4_R_le->setStyleSheet(RBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 4 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out4_ON)
                        .arg(ui->CC_Discrete_OP_ch4_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else {
                //                qDebug() << "SRU_DIS_OUT4_STS" << Input_5856_Card_2.Input_CH13;
                ui->CC_Discrete_ch4_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH13));
                SRU_Dis_out4 = QString::number(Input_5856_Card_2.Input_CH13);
                if (Input_5856_Card_2.Input_CH13 == 0) {
                    ui->CC_Discrete_OP_ch4_R_le->setText("PASS");
                    ui->CC_Discrete_OP_ch4_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Discrete_OP_ch4_R_le->setText("FAIL");
                    ui->CC_Discrete_OP_ch4_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete Channel 4 Output Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_out4)
                        .arg(ui->CC_Discrete_OP_ch4_R_le->text()));
            }
            if ((Dis_Out4_ON == "1") && (SRU_Dis_out4 == "0")) {
                Dis_Out_R4 = "PASS";
            } else {
                Dis_Out_R4 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Channel 4 Output ON OFF Result:%1").arg(Dis_Out_R4));
            break;
        }
        case (SRU_DIS_OUT5_STS): {
            emit DIS_OUT_Read_USB_Card();
            QThread::msleep(1);
            //            memcpy(&g_DIS_OutputsBIT_TEST, rx_data.data(), sizeof(g_DIS_OutputsBIT_TEST));

            if ((Input_5856_Card_2.Input_CH12 == 1)
                && (g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts == 1)) {
                Dis_Out5_ON.clear();
                SRU_Dis_out5.clear();

                //                qDebug() << "SRU_DIS_OUT5_STS" << Input_5856_Card_2.Input_CH12;
                ui->CC_Discrete_ch5_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH12));
                Dis_Out5_ON = QString::number(Input_5856_Card_2.Input_CH12);
                ui->CC_Discrete_OP_ch5_R_le->setText("PASS");
                ui->CC_Discrete_OP_ch5_R_le->setStyleSheet(GBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 5 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out5_ON)
                        .arg(ui->CC_Discrete_OP_ch5_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else if ((Input_5856_Card_2.Input_CH12 == 0)
                       && (g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts == 1)) {
                ui->CC_Discrete_ch5_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH12));
                Dis_Out5_ON = QString::number(Input_5856_Card_2.Input_CH12);

                ui->CC_Discrete_OP_ch5_R_le->setText("FAIL");
                ui->CC_Discrete_OP_ch5_R_le->setStyleSheet(RBC);
                SruLogger::instance()->logText(
                    QString("Discrete Channel 5 Output Status ON:%1 Result:%2")
                        .arg(Dis_Out5_ON)
                        .arg(ui->CC_Discrete_OP_ch5_R_le->text()));
                //-auto sequence
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    QMetaObject::invokeMethod(this,
                                              "SRU_CTRL_AutoStepCompleted",
                                              Qt::QueuedConnection);
                }
            } else {
                ui->CC_Discrete_ch5_OP_Value_le->setText(
                    QString::number(Input_5856_Card_2.Input_CH12));
                SRU_Dis_out5 = QString::number(Input_5856_Card_2.Input_CH12);
                if (Input_5856_Card_2.Input_CH12 == 0) {
                    ui->CC_Discrete_OP_ch5_R_le->setText("PASS");
                    ui->CC_Discrete_OP_ch5_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Discrete_OP_ch5_R_le->setText("FAIL");
                    ui->CC_Discrete_OP_ch5_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete Channel 5 Output Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_out5)
                        .arg(ui->CC_Discrete_OP_ch5_R_le->text()));
            }
            if ((Dis_Out5_ON == "1") && (SRU_Dis_out5 == "0")) {
                Dis_Out_R5 = "PASS";
            } else {
                Dis_Out_R5 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Channel 5 Output ON OFF Result:%1").arg(Dis_Out_R5));
            break;
        }
        case (SRU_DIS_IN1_STS): {
            if (g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1) {
                Dis_In1_ON.clear();
                SRU_Dis_In1.clear();
                memcpy(&g_DIS_InputsBIT_TEST, rx_data.data(), sizeof(g_DIS_InputsBIT_TEST));
                //                qDebug() << "SRU_DIS_IN1_STS" << g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts;
                ui->CC_Discrete_ch1_IP_Value_le->setText(
                    QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts));
                Dis_In1_ON = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts);

                if (g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1) {
                    ui->CC_Discrete_IP_ch1_R_le->setText("PASS");
                    ui->CC_Discrete_IP_ch1_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }

                } else if (g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 0) {
                    Dis_In1_ON = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts);
                    ui->CC_Discrete_IP_ch1_R_le->setText("FAIL");
                    ui->CC_Discrete_IP_ch1_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete Channel 1 Input Status ON:%1 Result:%2")
                        .arg(Dis_In1_ON)
                        .arg(ui->CC_Discrete_IP_ch1_R_le->text()));
            } else {
                memcpy(&g_DIS_InputsBIT_TEST, rx_data.data(), sizeof(g_DIS_InputsBIT_TEST));
                ui->CC_Discrete_ch1_IP_Value_le->setText(
                    QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts));
                SRU_Dis_In1 = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts);
                if (g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 0) {
                    ui->CC_Discrete_IP_ch1_R_le->setText("PASS");
                    ui->CC_Discrete_IP_ch1_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1) {
                    ui->CC_Discrete_IP_ch1_R_le->setText("FAIL");
                    ui->CC_Discrete_IP_ch1_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete Channel 1 Input Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_In1)
                        .arg(ui->CC_Discrete_IP_ch1_R_le->text()));
            }
            if ((Dis_In1_ON == "1") && (SRU_Dis_In1 == "0")) {
                Dis_In_R1 = "PASS";
            } else {
                Dis_In_R1 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Input Channel 1 ON OFF Result ").arg(Dis_In_R1));
            break;
        }
        case (SRU_DIS_IN2_STS): {
            if (g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1) {
                Dis_In2_ON.clear();
                SRU_Dis_In2.clear();

                memcpy(&g_DIS_InputsBIT_TEST, rx_data.data(), sizeof(g_DIS_InputsBIT_TEST));
                //                qDebug() << "SRU_DIS_IN2_STS" << g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts;
                ui->CC_Discrete_ch2_IP_Value_le->setText(
                    QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts));
                Dis_In2_ON = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts);

                if (g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1) {
                    ui->CC_Discrete_IP_ch2_R_le->setText("PASS");
                    ui->CC_Discrete_IP_ch2_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 0) {
                    Dis_In2_ON = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts);
                    ui->CC_Discrete_IP_ch2_R_le->setText("FAIL");
                    ui->CC_Discrete_IP_ch2_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete input channel 2 Status ON:%1 Result:%2")
                        .arg(Dis_In2_ON)
                        .arg(ui->CC_Discrete_IP_ch2_R_le->text()));

            } else {
                memcpy(&g_DIS_InputsBIT_TEST, rx_data.data(), sizeof(g_DIS_InputsBIT_TEST));
                //                qDebug() << "SRU_DIS_IN2_STS----------" << g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts;
                ui->CC_Discrete_ch2_IP_Value_le->setText(
                    QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts));
                SRU_Dis_In2 = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts);
                if (g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 0) {
                    ui->CC_Discrete_IP_ch2_R_le->setText("PASS");
                    ui->CC_Discrete_IP_ch2_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1) {
                    ui->CC_Discrete_IP_ch2_R_le->setText("FAIL");
                    ui->CC_Discrete_IP_ch2_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete input channel 2 Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_In2)
                        .arg(ui->CC_Discrete_IP_ch2_R_le->text()));
            }
            if ((Dis_In2_ON == "1") && (SRU_Dis_In2 == "0")) {
                Dis_In_R2 = "PASS";
            } else {
                Dis_In_R2 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Input Channel 2 ON OFF Result ").arg(Dis_In_R2));
            break;
        }
        case (SRU_DIS_IN3_STS): {
            if (g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1) {
                Dis_In3_ON.clear();
                SRU_Dis_In3.clear();
                memcpy(&g_DIS_InputsBIT_TEST, rx_data.data(), sizeof(g_DIS_InputsBIT_TEST));
                //                qDebug() << "SRU_DIS_IN3_STS" << g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts;
                ui->CC_Discrete_ch3_IP_Value_le->setText(
                    QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts));
                Dis_In3_ON = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts);

                if (g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1) {
                    ui->CC_Discrete_IP_ch3_R_le->setText("PASS");
                    ui->CC_Discrete_IP_ch3_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 0) {
                    Dis_In3_ON = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts);
                    ui->CC_Discrete_IP_ch3_R_le->setText("FAIL");
                    ui->CC_Discrete_IP_ch3_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete input channel 3 Status ON:%1 Result:%2")
                        .arg(Dis_In3_ON)
                        .arg(ui->CC_Discrete_IP_ch3_R_le->text()));
            } else {
                memcpy(&g_DIS_InputsBIT_TEST, rx_data.data(), sizeof(g_DIS_InputsBIT_TEST));
                //                qDebug() << "SRU_DIS_IN3_STS" << g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts;
                ui->CC_Discrete_ch3_IP_Value_le->setText(
                    QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts));
                SRU_Dis_In3 = QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts);
                if (g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 0) {
                    ui->CC_Discrete_IP_ch3_R_le->setText("PASS");
                    ui->CC_Discrete_IP_ch3_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else if (g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1) {
                    ui->CC_Discrete_IP_ch3_R_le->setText("FAIL");
                    ui->CC_Discrete_IP_ch3_R_le->setStyleSheet(RBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(
                    QString("Discrete input channel 3 Status OFF:%1 Result:%2")
                        .arg(SRU_Dis_In3)
                        .arg(ui->CC_Discrete_IP_ch3_R_le->text()));
            }
            if ((Dis_In3_ON == "1") && (SRU_Dis_In3 == "0")) {
                Dis_In_R3 = "PASS";
            } else {
                Dis_In_R3 = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Discrete Input Channel 3 ON OFF Result ").arg(Dis_In_R3));
            break;
        }
        case (SRU_ROT1_STS): {
            if (g_Momentary_Switch_Status.Rotary_Update == 1) {
                RotaryS1.clear();
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                RotaryS1 = QString("00")
                           + QString::number(g_Momentary_Switch_Status.Rotary_Update, 2);
                ui->CC_Rotary1_le->setText(
                    QString("00") + QString::number(g_Momentary_Switch_Status.Rotary_Update, 2));
                if (RotaryS1 == "001111111111") {
                    ui->CC_Rotary1_R_le->setText("PASS");
                    ui->CC_Rotary1_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Rotary1_R_le->setText("FAIL");
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Rotaty Switch 1 ON status :%1 Result:%2")
                                                   .arg(RotaryS1)
                                                   .arg(ui->CC_Rotary1_R_le->text()));
            } else {
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                Rotary_S1 = QString::number(g_Momentary_Switch_Status.Rotary_Update, 2);
                ui->CC_Rotary1_le->setText(
                    QString::number(g_Momentary_Switch_Status.Rotary_Update, 2));
                if (Rotary_S1 == "0") {
                    ui->CC_Rotary1_R_le->setText("PASS");
                    ui->CC_Rotary1_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Rotary1_R_le->setText("FAIL");
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Rotaty Switch 1 OFF Status :%1 Result:%2")
                                                   .arg(RotaryS1)
                                                   .arg(ui->CC_Rotary1_R_le->text()));
            }
            if ((RotaryS1 == "001111111111") && (Rotary_S1 == "0")) {
                Rotary_S1_Result = "PASS";
            } else {
                Rotary_S1_Result = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Rotary Switch1 ON OFF state Result:%1 ").arg(Rotary_S1_Result));
            break;
        }
        case (SRU_ROT2_STS): {
            if (g_Momentary_Switch_Status.Rotary_Update == 2) {
                RotaryS2.clear();
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                //                qDebug() << "g_Momentary_Switch_Status" << g_Momentary_Switch_Status.Rotary_Update;
                ui->CC_Rotary2_le->setText(
                    QString("00") + QString::number(g_Momentary_Switch_Status.Rotary_Update, 2));
                RotaryS2 = QString("00")
                           + QString::number(g_Momentary_Switch_Status.Rotary_Update, 2);
                if (RotaryS2 == "001111111111") {
                    ui->CC_Rotary2_R_le->setText("PASS");
                    ui->CC_Rotary2_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Rotary2_R_le->setText("FAIL");
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Rotaty Switch 2 ON status :%1 Result:%2")
                                                   .arg(RotaryS2)
                                                   .arg(ui->CC_Rotary2_R_le->text()));
            } else {
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                ui->CC_Rotary2_le->setText(
                    QString::number(g_Momentary_Switch_Status.Rotary_Update, 2));
                Rotary_S2 = QString::number(g_Momentary_Switch_Status.Rotary_Update, 2);
                if (Rotary_S2 == "0") {
                    ui->CC_Rotary2_R_le->setText("PASS");
                    ui->CC_Rotary2_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Rotary2_R_le->setText("FAIL");
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Rotaty Switch 2 OFF status :%1 Result:%2")
                                                   .arg(RotaryS2)
                                                   .arg(ui->CC_Rotary2_R_le->text()));
            }
            if ((RotaryS2 == "001111111111") && (Rotary_S2 == "0")) {
                Rotary_S2_Result = "PASS";
            } else {
                Rotary_S2_Result = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Rotary Switch2 ON OFF state Result:%1 ").arg(Rotary_S2_Result));
            break;
        }
        case (SRU_ROT3_STS): {
            if (g_Momentary_Switch_Status.Rotary_Update == 3) {
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                //                qDebug() << "g_Momentary_Switch_Status" << g_Momentary_Switch_Status.Rotary_Update;
                ui->CC_Rotary3_le->setText(
                    QString("00") + QString::number(g_Momentary_Switch_Status.Rotary_Update, 2));
                RotaryS3 = QString("00")
                           + QString::number(g_Momentary_Switch_Status.Rotary_Update, 2);
                if (RotaryS3 == "001111111111") {
                    ui->CC_Rotary3_R_le->setText("PASS");
                    ui->CC_Rotary3_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Rotary3_R_le->setText("FAIL");
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Rotaty Switch 3 ON status :%1 Result:%2")
                                                   .arg(RotaryS2)
                                                   .arg(ui->CC_Rotary3_R_le->text()));
            } else {
                memcpy(&g_Momentary_Switch_Status,
                       rx_data.data(),
                       sizeof(g_Momentary_Switch_Status));
                ui->CC_Rotary3_le->setText(
                    QString::number(g_Momentary_Switch_Status.Rotary_Update, 2));
                Rotary_S3 = QString::number(g_Momentary_Switch_Status.Rotary_Update, 2);
                if (Rotary_S3 == "0") {
                    ui->CC_Rotary3_R_le->setText("PASS");
                    ui->CC_Rotary3_R_le->setStyleSheet(GBC);
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                } else {
                    ui->CC_Rotary3_R_le->setText("FAIL");
                    //-auto sequence
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        QMetaObject::invokeMethod(this,
                                                  "SRU_CTRL_AutoStepCompleted",
                                                  Qt::QueuedConnection);
                    }
                }
                SruLogger::instance()->logText(QString("Rotaty Switch 3 OFF status :%1 Result:%2")
                                                   .arg(RotaryS2)
                                                   .arg(ui->CC_Rotary3_R_le->text()));
            }
            if ((RotaryS3 == "001111111111") && (Rotary_S3 == "0")) {
                Rotary_S3_Result = "PASS";

            } else {
                Rotary_S3_Result = "FAIL";
            }
            SruLogger::instance()->logText(
                QString("Rotary Switch3 ON OFF state Result:%1 ").arg(Rotary_S3_Result));
            break;
        }
        default: {
            ui->listWidget->addItem("RX:MESSAGE ID NOT MATCHED");
            ui->listWidget->scrollToBottom();
            break;
        }
        }
        rx_data.clear();
    } else if (rx_data.at(1) == WAVEFORM_DISPLAY_ID) {
        //            memcpy(&g_waveform_plot,reinterpret_cast<uint8_t *>(rx_data.at(0)),rx_data.size());
        if (rx_data.size() == sizeof(WaveForm_Plot)) {
            memcpy(&g_waveform_plot, rx_data.data(), sizeof(WaveForm_Plot));
        } else {
            // Handle error: data size mismatch
            //            qDebug() << "Error: Data size mismatch.";
        }
        emit sigWaveformProcess();
        //                    qDebug() << "WAVEFORM_DISPLAY_ID";
    } else {
        //        ui->listWidget->addItem("CRC CHECK FAIL");
        //        ui->listWidget->scrollToBottom();
        //        qDebug() << "CRC CHECK FAIL";
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,
                             tr("Information"),
                             "\n GUI\tVersion 1.0 \n APOLLO MICRO SYSTEMS \n ");
    //    QMessageBox::information(this,"About","Version: " + QString::number(GUI_VERSION,'f',1) + "\n\n" + "GUI CRC value: 0x" /*+ QString::number(gui_CRC,16));
}

void MainWindow::M_SerialErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
    }
    if (error == QSerialPort::ResourceError) {
        //        qDebug() << "Serial port disconnected or other resource error.";
        // Handle disconnection or other error
        emit deviceDisconnected(ui->SerialPortSelect->text());

        ui->OpenPort->setText("USB DISCONNECTED");
        ui->OpenPort->setStyleSheet("background-color: rgb(232,232,232)"); /*grey*/
        //        QMessageBox::information(this, tr("Information"), "COM PORT ERROR RECONNECT COM PORT");
    }
    if (error == QSerialPort::UnknownError) {
        //        QMessageBox::information(this, tr("Information"), "COM PORT ERROR RECONNECT COM PORT");
    }
    //    qDebug() << "print from Mainwindow " << error;
}

void MainWindow::M_SerialAboutToClose()
{
    //    qDebug() << "Serial port about to close.";
    Timer_stay_in_boot_mode->stop();
    g_boot_timer_status = 1;
    g_Dword_cnt = 0;
    ui->progressBar->setValue(0);
    ui->Connect_to_UC->setEnabled(false);
    // Handle the closing of the port
}

// Function to find the STM32 virtual COM port
QString MainWindow::findSTM32Port()
{
    QString targetSerialNumber1 = "204D31715041"; // set this to the serial you want to detect

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        // Optional: Print for debugging
        //        qDebug() << "Checking Port:" << info.portName() << "Description:" << info.description()
        //                 << "Manufacturer:" << info.manufacturer()
        //                 << "Serial Number:" << info.serialNumber();

        // Check STM32 description/manufacturer AND serial number
        if ((info.description().contains("STM", Qt::CaseInsensitive)
             || info.manufacturer().contains("STM", Qt::CaseInsensitive))
            && info.serialNumber() == targetSerialNumber1) {
            return info.portName(); // Store port name
            //            qDebug() << "STM32 device with serial" << targetSerialNumber1 << "found on port";
            break; // Use the first matching port with this serial
        }
    }
    //    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
    //        // Check if the description matches "STMicroelectronics Virtual COM Port"
    //        //        if (portInfo.description() == "HHD Software Bridged Serial Port")
    //        if (portInfo.description() == "STMicroelectronics Virtual COM Port") {
    //            qDebug() << "Found STM32 on port:" << portInfo.portName();
    //            return portInfo.portName();
    //        }
    //    }
    return QString(); // Return an empty string if not found
}

void MainWindow::on_OpenPort_toggled(bool checked)
{
    //    qDebug() << "Serial thread already running!";
    //    if (checked) {
    //        if (serialThread) {
    //
    //            return;
    //        }

    //        QString USB_portName = findSTM32Port();
    //        if (USB_portName.isEmpty()) {
    //            QMessageBox::warning(this, "Error", "STM32 device not found.");
    //            ui->OpenPort->setChecked(false);
    //            return;
    //        }

    //        worker = new qSerialWork(USB_portName);
    //        serialThread = new QThread;

    //        worker->moveToThread(serialThread);

    //        // Signal-slot connections
    //        connect(serialThread, &QThread::started, worker, &qSerialWork::start);
    //        connect(worker, &qSerialWork::finished, serialThread, &QThread::quit);
    //        connect(worker, &qSerialWork::finished, worker, &qSerialWork::deleteLater);
    //        connect(serialThread, &QThread::finished, serialThread, &QThread::deleteLater);

    //        connect(this,
    //                SIGNAL(serialWrite(const char *, qint64)),
    //                worker,
    //                SLOT(writeData(const char *, qint64)));
    //        connect(this, SIGNAL(sig_serialPort_Close()), worker, SLOT(serialPort_Close()));

    //        connect(worker, &qSerialWork::msg_process, this, &MainWindow::message_received);
    //        connect(worker,
    //                &qSerialWork::sig_SerialErrorOccurred,
    //                this,
    //                &MainWindow::M_SerialErrorOccurred);
    //        connect(worker,
    //                &qSerialWork::sig_SerialAboutToClose,
    //                this,
    //                &MainWindow::M_SerialAboutToClose);

    //        // Start thread
    //        serialThread->start();

    //        // Update GUI
    //        ui->SerialPortSelect->clear();
    //        ui->SerialPortSelect->setText(USB_portName);
    //        ui->USB_Status->setText(USB_portName);
    //        ui->BITTEST_USB_STATUS_LE->setText(USB_portName);

    //        ui->SerialPortSelect->setDisabled(true);
    //        ui->OpenPort->setText("CLOSE PORT");
    //        ui->Connect_to_UC->setEnabled(true);

    //        QFont font = ui->OpenPort->font();
    //        font.setPointSize(12);
    //        font.setBold(true);
    //        font.setFamily("Bookman Old Style");
    //        ui->OpenPort->setFont(font);
    //        ui->OpenPort->setStyleSheet("background-color: rgb(255,7,7)");
    //        ui->OpenPort->setCheckable(true);
    //    } else {
    //        // Close port
    //        emit sig_serialPort_Close();

    //        if (serialThread) {
    //            serialThread->quit();
    //            serialThread->wait();
    //            delete serialThread;
    //            serialThread = nullptr;
    //            worker = nullptr;
    //        }

    //        // Reset GUI
    //        ui->OpenPort->setText("OPEN PORT");
    //        ui->OpenPort->setStyleSheet("background-color: rgb(8, 102, 70)");
    //        ui->SerialPortSelect->clear();
    //        ui->SerialPortSelect->setDisabled(false);

    //        ui->Browse->setEnabled(false);
    //        ui->FilePathDisplay->setEnabled(false);
    //        ui->FilePathDisplay->clear();

    //        ui->EraseFlash->setEnabled(false);
    //        ui->EraseFlash->setStyleSheet("background-color: rgb(232,232,232)");

    //        ui->Download_HexFile->setEnabled(false);
    //        ui->Download_HexFile->setStyleSheet("background-color: rgb(232,232,232)");

    //        ui->Connect_to_UC->setStyleSheet("background-color: rgb(232,232,232)");
    //        ui->Connect_to_UC->setEnabled(false);

    //        g_mode_flag = 0;
    //    }

    if (checked == true) {
        //        SerialWork = new qSerialWork(ui->SerialPortSelect->currentText());
        //--------------------------------------------------------------------
        QThread *thread3 = new QThread;
        QString USB_portName = findSTM32Port();
        qSerialWork *worker = new qSerialWork(USB_portName);
        ui->SerialPortSelect->clear();
        ui->SerialPortSelect->setText(USB_portName);
        ui->USB_Status->setText(USB_portName);
        ui->BITTEST_USB_STATUS_LE->setText(USB_portName);

        worker->moveToThread(thread3);
        //        connect(worker, &qSerialWork::sig_SerialErrorOccurred, this, &MainWindow::M_SerialErrorOccurred, Qt::QueuedConnection);
        connect(thread3, &QThread::started, worker, &qSerialWork::start);
        connect(worker, &qSerialWork::finished, thread3, &QThread::quit);
        connect(worker, &qSerialWork::finished, worker, &qSerialWork::deleteLater);
        connect(thread3, &QThread::finished, thread3, &QThread::deleteLater);
        connect(this,
                SIGNAL(serialWrite(const char *, qint64)),
                worker,
                SLOT(writeData(const char *, qint64)));
        connect(this, SIGNAL(sig_serialPort_Close()), worker, SLOT(serialPort_Close()));
        connect(worker, &qSerialWork::msg_process, this, &MainWindow::message_received);
        //-------------------------------------------------------------------------------------------
        //        serialPort = new QSerialPort(this);
        //        connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(worker,
                &qSerialWork::sig_SerialErrorOccurred,
                this,
                &MainWindow::M_SerialErrorOccurred);
        connect(worker,
                &qSerialWork::sig_SerialAboutToClose,
                this,
                &MainWindow::M_SerialAboutToClose);
        thread3->start();

        //        qDebug() << "serial thread opened" <<thread2->currentThreadId();
        //        serialPort->setPortName(ui->SerialPortSelect->currentText());
        //        serialPort->setBaudRate(QSerialPort::Baud57600);
        //        serialPort->setDataBits(QSerialPort::Data8);
        //        serialPort->setParity(QSerialPort::NoParity);
        //        serialPort->setStopBits(QSerialPort::OneStop);
        //        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        //        serialPort->setReadBufferSize(255);
        //        if(serialPort->open(QIODevice::ReadWrite))
        //        if((SerialWork->m_serialPort_OpenSTS) == true)
        {
            ui->SerialPortSelect->setDisabled(true);
            ui->OpenPort->setText("CLOSE PORT");
            ui->Connect_to_UC->setEnabled(true);
            QFont font = ui->OpenPort->font();
            font.setPointSize(12);
            font.setBold(true);
            font.setFamily("Bookman Old Style");
            ui->OpenPort->setFont(font);
            ui->OpenPort->setStyleSheet("background-color: rgb(255,7,7)");
        }
        //        else
        //        {
        //            QMessageBox::information(this,tr("Error"),"Cannot Open Serial Port");
        //            ui->OpenPort->setCheckable(false);
        //        }
        ui->OpenPort->setCheckable(true);
    } else if (checked == false) {
        ui->OpenPort->setText("OPEN PORT");
        ui->OpenPort->setStyleSheet("background-color: rgb(8, 102, 70)");
        ui->SerialPortSelect->clear();
        emit sig_serialPort_Close();
        ui->SerialPortSelect->setDisabled(false);
        ui->Browse->setEnabled(false);
        ui->FilePathDisplay->setEnabled(false);
        ui->FilePathDisplay->clear();
        ui->EraseFlash->setEnabled(false);
        ui->EraseFlash->setStyleSheet("background-color: rgb(232,232,232)"); /*grey*/
        ui->Download_HexFile->setEnabled(false);
        ui->Download_HexFile->setStyleSheet("background-color: rgb(232,232,232)"); /*grey*/
        ui->Connect_to_UC->setStyleSheet("background-color: rgb(232,232,232)");    /*grey*/
        ui->Connect_to_UC->setEnabled(false);
        g_mode_flag = 0;
    }
}

void MainWindow::on_SAVE_clicked()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this, "SaveFile", "", "Text File(*.txt)");
    if (fileName == "") {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    } else {
        QTextStream textStream(&file);
        //Write list items to file by line
        for (int i = 0; i < ui->listWidget->count(); i++) {
            textStream << ui->listWidget->item(i)->text() + '\n';
        }
        QMessageBox::information(this, "Saved", "the File Has been Saved");
        file.close();
    }
}

void MainWindow::on_OpenSavedFile_clicked()
{
    QFileDialog openFile;
    QString fileName = openFile.getOpenFileName(this, "OpenFile", " ", "Text File(*.txt)");
    if (fileName == "") {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    } else {
        QTextStream textStream(&file);
        /*Create a list of strings and a string line, the latter as an intermediate variable of the textStream.readline() function*/
        QStringList list;
        QString line;
        while (!textStream.atEnd()) {
            line = textStream.readLine().remove('\n') /*.remove(" ")*/;
            /*Add items to the list*/
            list << line;
        }
        /*Add the list to listWidget*/
        ui->listWidget->addItems(list);
        file.close();
    }
}

void MainWindow::on_ClearButton_clicked()
{
    ui->listWidget->clear();
}

void MainWindow::on_Browse_clicked()
{
    FILE *Fptr = NULL;
    //    if(get_OpenPortStatus() == 1)
    //    if(SerialWork->get_serialPort_openSTS())
    {
        QString binfile = QFileDialog::getOpenFileName(this,
                                                       tr("Open File"),
                                                       "C://",
                                                       "bin file (*.bin);");
        if (binfile == NULL) {
            //            qDebug() << "load file error";
        } else {
            ui->FilePathDisplay->setText(binfile);
            char test[1024];
            QByteArray ba = binfile.toUtf8();
            const char *c_str2 = ba.constData();
            strncpy(test, c_str2, sizeof(test));
            test[sizeof(test) - 1] = '\0';
            // strcpy(test, binfile);
            //            qDebug() << ("Opening Binary file " + binfile);
            ui->listWidget->addItem("Opening Binary file " + binfile);
            ui->listWidget->scrollToBottom();
            Fptr = fopen(test, "rb");
            if (Fptr == NULL) {
                //                qDebug() << ("Can not open" + binfile);
                ui->listWidget->addItem("Can not open" + binfile);
                ui->listWidget->scrollToBottom();
            }
            fseek(Fptr, 0L, SEEK_END);
            g_binFileSize = ftell(Fptr);
            fseek(Fptr, 0L, SEEK_SET);

            //            qDebug()<< ("File size = "+ QString::number(g_binFileSize,10) + "Bytes");
            ui->listWidget->addItem("File size = " + QString::number(g_binFileSize, 10) + "Bytes");
            ui->listWidget->scrollToBottom();

            if (g_binFileSize > MAX_FW_SIZE) {
                //                qDebug() << ("Application Size is more than the Maximum Size" + QString::number(MAX_FW_SIZE/MAX_BLOCK_SIZE) + "Bytes");
                ui->listWidget->addItem("Application Size is more than the Maximum Size"
                                        + QString::number(MAX_FW_SIZE / MAX_BLOCK_SIZE) + "Bytes");
                ui->listWidget->scrollToBottom();
            }
            //read the full image
            if (fread(APP_BIN, 1, g_binFileSize, Fptr) != g_binFileSize) {
                //                qDebug() << ("App/FW read Error");
                ui->listWidget->addItem("App/FW read Error");
                ui->listWidget->scrollToBottom();
            }
            //                        for(uint32_t i=0;i<=g_binFileSize;i++)
            //                        {            qDebug("%x",APP_BIN[i]);
            //                                           ui->listWidget->addItem(QString::number(APP_BIN[i],16).toUpper().rightJustified(2,'0'));
            //                        }
            //                        ui->listWidget->scrollToBottom();
            if (Fptr) {
                fclose(Fptr);
            }
            //converting APP_BIN array byte data to DoubleWord data
            for (uint64_t i = 0, j = 0; i <= (g_binFileSize);) {
                uint64_t l_Dword = 0;
                l_Dword = (uint64_t) APP_BIN[i];
                l_Dword |= (uint64_t) APP_BIN[++i] << 8;
                l_Dword |= (uint64_t) APP_BIN[++i] << 16;
                l_Dword |= (uint64_t) APP_BIN[++i] << 24;
                l_Dword |= (uint64_t) APP_BIN[++i] << 32;
                l_Dword |= (uint64_t) APP_BIN[++i] << 40;
                l_Dword |= (uint64_t) APP_BIN[++i] << 48;
                l_Dword |= (uint64_t) APP_BIN[++i] << 56;
                i++;
                g_Dword_app_bin[j] = l_Dword;
                //                                qDebug() << QString::number(l_Dword,16).rightJustified(8,'0') << "--" <<QString::number(i,10) << "----" << QString::number(g_Dword_app_bin[j],16).rightJustified(8,'0') << "--" << QString::number(j,10);
                j++;
            }

            ui->listWidget->addItem("HEX FILE LOADED INTO GUI");
            ui->listWidget->scrollToBottom();
            ui->progressBar->setMaximum(g_binFileSize);
            ui->progressBar->setValue(0);
            ui->EraseFlash->setStyleSheet("background-color: rgb(232,232,232)");       /*greay*/
            ui->Download_HexFile->setStyleSheet("background-color: rgb(232,232,232)"); /*grey*/
            ui->EraseFlash->setEnabled(true);
            //            qDebug() << QString::number((g_binFileSize/8),10);
        }
    }
    //    else
    //    {
    //        QMessageBox::information(this,tr("Error"),"Open Serial Port");
    //    }
}

void MainWindow::on_Connect_to_UC_clicked()
{
    g_Sty_in_Boot.startByte = 0x24;
    g_Sty_in_Boot.MsgID = STAY_IN_BOOTLOADER_MODE;
    g_Sty_in_Boot.packetSize = sizeof(Sty_in_Boot);
    g_Sty_in_Boot.CRC_WORD = 0;
    g_Sty_in_Boot.endByte = 0x233B;

    g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_Sty_in_Boot, g_Sty_in_Boot.packetSize);
    g_Sty_in_Boot.CRC_WORD = g_CRC_word;
    //    if(SerialWork->get_serialPort_openSTS())
    {
        emit serialWrite((char *) &g_Sty_in_Boot, g_Sty_in_Boot.packetSize);
        ui->listWidget->addItem("TX:waiting to connect to UNIT...........................");
        ui->listWidget->scrollToBottom();
        ui->Connect_to_UC->setStyleSheet("background-color: rgb(85,170,255)"); /*blue*/
        if (g_boot_timer_status == 1) {
            g_boot_timer_status = 0;
            Timer_stay_in_boot_mode->start(300);
        }
    }
}

void MainWindow::on_EraseFlash_clicked()
{
    g_FlashErase.startByte = '$';
    g_FlashErase.packetSize = sizeof(FlashErase);
    g_FlashErase.MsgID = UC_FLASH_ERASE;
    g_FlashErase.CRC_WORD = 0;
    g_FlashErase.endByte = 0x233B;

    g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_FlashErase, g_FlashErase.packetSize);
    g_FlashErase.CRC_WORD = g_CRC_word;
    //    if(SerialWork->get_serialPort_openSTS())
    {
        emit serialWrite((char *) &g_FlashErase, g_FlashErase.packetSize);
        ui->listWidget->addItem(
            "TX:CMD SENT FOR MICROCONTROLLER FLASH ERASE Please wait...........................");
        ui->listWidget->scrollToBottom();
        ui->EraseFlash->setEnabled(false);
        ui->EraseFlash->setStyleSheet("background-color: rgb(85,170,255)"); /*blue*/
    }
    //    else
    //    {
    //        QMessageBox::information(this,tr("Error"),"Open Serial Port");
    //    }

    g_time_out_flag = 0;
    TimeOutTimer->start(10000);
    g_time_out_flag = 1;
    g_time_out_state = UC_ERASE;
}

void MainWindow::TimeOutTimer_Indications()
{
    if (g_time_out_flag == 1) {
        ui->listWidget->addItem("time out occured");
        ui->listWidget->scrollToBottom();
        TimeOutTimer->stop();
        switch (g_time_out_state) {
        case UC_ERASE: {
            ui->EraseFlash->setStyleSheet("background-color: rgb(255, 7, 7)"); /*red*/
            ui->listWidget->addItem("UC_ERASE time out occured");
            break;
        }
        case APP_WRT_TIMEOUT: {
            ui->Download_HexFile->setStyleSheet("background-color: rgb(255, 7, 7)"); /*red*/
            ui->listWidget->addItem("APP_WRT_TIMEOUT time out occured");

            break;
        }
        case APP_SIG_WRT_TIMEOUT: {
            ui->Download_HexFile->setStyleSheet("background-color: rgb(255, 7, 7)"); /*red*/
            ui->listWidget->addItem("APP_SIG_WRT_TIMEOUT time out occured");
            break;
        }
        case APP_CRC_WRT_TIMEOUT: {
            ui->Download_HexFile->setStyleSheet("background-color: rgb(255, 7, 7)"); /*red*/
            ui->listWidget->addItem("APP_CRC_WRT_TIMEOUT time out occured");
            break;
        }
        case SRUCTRL_Rx1_PAT2: {
            g_time_out_state = 0;
            g_time_out_flag = 0;
            ui->CC_CH1_RX_le->setText("FAIL");
            CC_Ch1 = "FAIL";
            SruLogger::instance()->logText(QString("Channel 1 Result:%1").arg(CC_Ch1));
            ui->CC_CH1_RX_le->setStyleSheet("color: red;background-color:#ffffff;");
            ui->CC_Ch1_TX_pb->setStyleSheet(RBC);
            ui->CC_Ch1_TX_pb->setChecked(false);

            if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                QMetaObject::invokeMethod(this, "SRU_CTRL_AutoStepCompleted", Qt::QueuedConnection);
            }

            break;
        }
        case MOXA_Tx_2_RX_1: {
            break;
        }
        case SRUCTRL_Rx2_PAT2: {
            g_time_out_state = 0;
            g_time_out_flag = 0;
            ui->CC_CH2_RX_le->setText("FAIL");
            CC_Ch2 = "FAIL";
            SruLogger::instance()->logText(QString("Channel 1 Result:%1").arg(CC_Ch2));
            ui->CC_CH2_RX_le->setStyleSheet("color: red;background-color:#ffffff;");
            ui->CC_Ch2_TX_pb->setStyleSheet(RBC);
            ui->CC_Ch2_TX_pb->setChecked(false);

            if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                QMetaObject::invokeMethod(this, "SRU_CTRL_AutoStepCompleted", Qt::QueuedConnection);
            }
            break;
        }
        case SELF_TEST_28V: {
            g_time_out_flag = 0;
            TimeOutTimer->start(4000);
            g_time_out_state = SELF_TEST_32V;
            g_time_out_flag = 1;
            ui->Volt_28_16_32_Cmb->setCurrentIndex(2);
            break;
        }
        case SELF_TEST_32V: {
            g_time_out_flag = 0;
            TimeOutTimer->start(4000);
            g_time_out_state = SELF_TEST_OFF;
            g_time_out_flag = 1;
            ui->Volt_28_16_32_Cmb->setCurrentIndex(3);
            break;
        }
            //        case SELF_TEST_EXT_V: {
            //            g_time_out_flag = 0;
            //            TimeOutTimer->start(4000);
            //            g_time_out_state = SELF_TEST_OFF;
            //            g_time_out_flag = 1;
            //            ui->Volt_28_16_32_Cmb->setCurrentIndex(4);
            //
            //            break;
            //        }
        case SELF_TEST_OFF: {
            g_time_out_flag = 0;
            g_time_out_state = 0;
            g_time_out_flag = 0;
            ui->Volt_28_16_32_Cmb->setCurrentIndex(5);
            if (g_mode_flag == AUTOMATIC_MODE) {
                QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
            }
            break;
        }
        case RIPPLE_P5V_DELAY: {
            on_Open_Oscilloscope_PB_clicked(); //Ripple
            break;
        }
        case RIPPLE_N5V_DELAY: {
            on_Ripple_N5V_pb_clicked(); //Ripple
            break;
        }
        case RIPPLE_P3P3V_DELAY: {
            on_Ripple_3p3V_pb_clicked(); //Ripple
            break;
        }
        case SRU_DIP1: {
            //            g_time_out_state = 0;
            //            g_time_out_flag = 0;
            //            ui->CC_Discrete_OP_ch1_R_le->setText("FAIL");

            //            ui->CC_Discrete_OP_ch1_R_le->setStyleSheet("color: red;background-color:#ffffff;");
            //            ui->CC_Discrete_ch1_OP_pb->setStyleSheet(RBC);
            //            ui->CC_Discrete_ch1_OP_pb->setChecked(false);

            break;
        }
        default:
            break;
        }
    }
    if (g_time_out_flag == 0) {
        TimeOutTimer->stop();
    }
}

void MainWindow::on_Download_HexFile_clicked()
{
    g_BinFileTx.StartMsg = '$';
    g_BinFileTx.packetSize = sizeof(g_BinFileTx);
    g_BinFileTx.MsgID = APPLICATION_DATA;
    g_BinFileTx.Dword_cnt = NUM_OF_DWORDS - 1;
    ui->progressBar->setFormat(".bin FILE LOADING");
    ui->Download_HexFile->setStyleSheet("background-color: rgb(85,170,255)"); /*blue*/
    //sending 7 64 bit data to UC of .bin file in every packet
    for (uint64_t i = g_Dword_cnt, j = 0; i <= (g_binFileSize / 8) && j < NUM_OF_DWORDS; i++, j++) {
        g_BinFileTx.Dword[j] = g_Dword_app_bin[i];
        g_Dword_cnt++;
        //                qDebug() << QString::number(g_BinFileTx.Dword[j],16).rightJustified(16,'0') <<"--" << QString::number(j,10) << "---" << QString::number(g_Dword_app_bin[i],16).rightJustified(16,'0') <<"--" << QString::number(i,10);
    }
    g_BinFileTx.CRC_WORD = 0;
    g_BinFileTx.EndMsg = 0x233B;
    g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_BinFileTx, g_BinFileTx.packetSize);
    g_BinFileTx.CRC_WORD = g_CRC_word;

    if ((g_Dword_cnt) == ((g_binFileSize / 8) + 1)) {
        ui->Download_HexFile->setStyleSheet("background-color: rgb(0, 255, 127)"); /*green*/
        ui->Download_HexFile->setEnabled(false);
        //        qDebug() << "BIN FILE TRANSFER COMPLETED";
        ui->listWidget->addItem("BIN FILE TRANSFER COMPLETED");
        ui->listWidget->scrollToBottom();
        ui->progressBar->setValue(g_binFileSize);
        //------sending signature byte --------//
        g_AppSigDword.startByte = '$';
        g_AppSigDword.packetSize = sizeof(AppSigDword);
        g_AppSigDword.MsgID = APP_SIG_DWORD;
        g_AppSigDword.SOFT_VER = 0xC00;
        g_AppSigDword.CRC_WORD = 0;
        g_AppSigDword.endByte = 0x233B;

        g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_AppSigDword, g_AppSigDword.packetSize);
        g_AppSigDword.CRC_WORD = g_CRC_word;
        //        if(SerialWork->get_serialPort_openSTS())
        {
            emit serialWrite((char *) &g_AppSigDword, g_AppSigDword.packetSize);
            ui->listWidget->addItem("APP SIGNATURE DWORD SENT");
            ui->listWidget->scrollToBottom();
            g_time_out_flag = 0;
            TimeOutTimer->start(5000);
            g_time_out_flag = 1;
            g_time_out_state = APP_SIG_WRT_TIMEOUT;
        }
        //        else
        //        {
        //            QMessageBox::information(this,tr("Error"),"Open Serial Port");
        //        }

        //------sending signature byte END --------//
    } else {
        //        if(SerialWork->get_serialPort_openSTS())
        {
            emit serialWrite((char *) &g_BinFileTx, g_BinFileTx.packetSize);
            //             qDebug() << "Packet No:" + QString::number(g_Dword_cnt);
            //             uint8_t *test = (uint8_t *)&g_BinFileTx;
            //            for( uint32_t i = 0; i<=g_BinFileTx.packetSize;i++)
            //            {
            //                qDebug() << QString::number(test[i],16);
            //            }
            g_packet_no_sent = g_Dword_cnt;
            ui->listWidget->addItem("Packet No:" + QString::number(g_Dword_cnt));
            ui->listWidget->scrollToBottom();
            ui->progressBar->setValue(g_Dword_cnt * (NUM_OF_DWORDS + 1));
            ui->Download_HexFile->setEnabled(false);
            g_time_out_flag = 0;
            TimeOutTimer->start(5000);
            g_time_out_flag = 1;
            g_time_out_state = APP_WRT_TIMEOUT;
            uint8_t static l_disCounter = 0;
            if (l_disCounter == 20) {
                ui->listWidget->clear();
                l_disCounter = 0;
            } else {
                l_disCounter++;
            }
        }
        //        else
        //        {
        //            QMessageBox::information(this,tr("Error"),"Open Serial Port");
        //        }
    }
}

void MainWindow::AppCRC_Verify(void)
{
    uint32_t static l_app_size = (g_packet_no_sent * 8);
    g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_Dword_app_bin[0], l_app_size);
    g_CRC_check_GUI = g_CRC_word;
    ui->listWidget->addItem("CRC of .bin loaded into GUI:  0x"
                            + QString::number(g_CRC_word, 16).toUpper());
    ui->listWidget->scrollToBottom();
    //    qDebug() << QString::number(g_CRC_word,16);

    //-----------------------------------command to UC to calculate CRC of APP code--------------------//
    g_AppCrcVerify.startByte = '$';
    g_AppCrcVerify.packetSize = sizeof(AppCrcVerify);
    g_AppCrcVerify.MsgID = APP_CRC_VERIFY;
    g_AppCrcVerify.appCode_size = l_app_size;
    g_AppCrcVerify.CRC_WORD = 0;
    g_AppCrcVerify.endByte = 0x233B;

    g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_AppCrcVerify, g_AppCrcVerify.packetSize);
    g_AppCrcVerify.CRC_WORD = g_CRC_word;
    //    if(SerialWork->get_serialPort_openSTS())
    {
        emit serialWrite((char *) &g_AppCrcVerify, g_AppCrcVerify.packetSize);
        ui->listWidget->addItem("APP SIGNATURE DWORD SENT");
        ui->listWidget->scrollToBottom();
        g_time_out_flag = 0;
        TimeOutTimer->start(5000);
        g_time_out_flag = 1;
        g_time_out_state = APP_CRC_WRT_TIMEOUT;
    }
    //    else
    //    {
    //        QMessageBox::information(this,tr("Error"),"Open Serial Port");
    //    }
}

void MainWindow::on_OpenWaveFormGenerator_clicked()
{
    g_SignalGenerator.show();
}

void MainWindow::checkDevices()
{
    auto currentPorts = QSerialPortInfo::availablePorts();
    QStringList currentPortNames;
    QStringList lastPortNames;

    for (const auto &info : qAsConst(currentPorts)) {
        currentPortNames.append(info.portName());
    }

    for (const auto &info : qAsConst(lastKnownPorts)) {
        lastPortNames.append(info.portName());
    }

    // Detect new devices
    for (const auto &portName : currentPortNames) {
        if (!lastPortNames.contains(portName)) {
            emit deviceConnected(portName);
        }
    }

    // Detect removed devices
    for (const auto &portName : lastPortNames) {
        if (!currentPortNames.contains(portName)) {
            emit deviceDisconnected(portName);
        }
    }

    lastKnownPorts = currentPorts;
}

void MainWindow::SerialConnected(const QString &portName)
{
    //    qDebug() << "Device Connected:" << portName;
    ui->listWidget->addItem("USB Connected Port:" + portName);
    ui->listWidget->scrollToBottom();
    ui->SerialPortSelect->clear();
    ui->SerialPortSelect->setText(portName);
    //    const auto infos = QSerialPortInfo::availablePorts();
    //    for (const QSerialPortInfo &info : infos)
    //        ui->SerialPortSelect->addItem(info.portName());

    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
    } else {
        if (portName.contains("COM18", Qt::CaseInsensitive)) {
            QMessageBox::information(this,
                                     "STM32 Connected",
                                     "STM32 device connected on port: " + portName);
        } else {
            //            QString message = "MOXA Connected on port: " + portName;
            //            QMessageBox::information(this, "connection", message);
        }
    }
}

void MainWindow::SerialDisconnected(const QString &portName)
{
    //    qDebug() << "Device Disconnected:" << portName;
    ui->listWidget->addItem("USB Disconnected Port:" + portName);

    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
    } else {
        if (portName.contains("COM18", Qt::CaseInsensitive)) {
            QMessageBox::warning(this,
                                 "STM32 Disconnected",
                                 "STM32 device disconnected from port: " + portName);
        } else {
            //        QString message = "MOXA Disconnected on port: " + portName;
            //        QMessageBox::information(this, "Disconnection", message);
        }
    }
}

void MainWindow::on_LoadWaveform_inti_GUI_clicked()
{
    ui->TestPointDatatableWidget->setRowCount(0);

    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Select Directory"),
                                                          "C://",
                                                          QFileDialog::ShowDirsOnly
                                                              | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        emit directorySelected(directory);
    } else {
        //        qDebug() << "No directory selected.";
    }
}

void MainWindow::updateFromTestPoint(uint16_t counter,
                                     int testPointNum,
                                     QString TestPointfileName,
                                     bool ok)
{
    //    qDebug() << "testPointNum" << QString::number(testPointNum) << TestPointfileName;

    ui->TestPointDatatableWidget->setRowCount(counter);
    ui->TestPointDatatableWidget->setItem(counter - 1,
                                          0,
                                          new QTableWidgetItem(QString::number(testPointNum)));
    ui->TestPointDatatableWidget->setItem(counter - 1, 1, new QTableWidgetItem(TestPointfileName));
    QProgressBar *progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100); // Set the range
    if (ok == true) {
        progressBar->setValue(100); // Set the current value
    } else {
        progressBar->setValue(0); // Set the current value
    }
    ui->TestPointDatatableWidget->setCellWidget(counter - 1, 2, progressBar);
    ui->TestPointDatatableWidget->scrollToBottom();
}

void MainWindow::onRequestDirectorySelection() {}

void MainWindow::on_TransferTestPointData_clicked()
{
    ui->TestPointDatatableWidget->scrollToTop();
    sendTP_data_to_UC();
}

void MainWindow::sendTP_data_to_UC()
{
    if (g_Tp_pkt_tx_cnt < g_Tp_pkt_max_size) {
        //        qDebug() << "g_Tp_pkt_tx_cnt" << QString::number(g_Tp_pkt_tx_cnt) << "g_Tp_pkt_max_size"
        //        << QString::number(g_Tp_pkt_max_size);
        //        qDebug() << "1";
        testPointMain[g_Tp_pkt_tx_cnt].CRC_WORD = 0;
        uint16_t crc_calc = CRCUtility::g_CRC_calc(reinterpret_cast<uint8_t *>(
                                                       &testPointMain[g_Tp_pkt_tx_cnt]),
                                                   sizeof(TestPoint_main));
        //        qDebug() << "2";
        testPointMain[g_Tp_pkt_tx_cnt].CRC_WORD = crc_calc;
        //        qDebug() << "3";
        QByteArray test = serializeTestPoint(testPointMain[g_Tp_pkt_tx_cnt]);
        //        qDebug() << "4";
        //        qDebug() << test.toHex();
        //        qDebug() << "test.size" << QString::number(test.size(), 10);
        emit serialWrite(test, test.size());
        g_Tp_pkt_tx_cnt++;
    } else {
        //        qDebug() << "tx COmplete TP kjashgkjahskjha...........18476823798298787%$#";
    }
}

void MainWindow::handleTestPointsData(QVector<TestPoint_main> receivedTestPoints)
{
    //    qDebug() << "Received total number of test poin" << receivedTestPoints.size();
    g_Tp_pkt_max_size = receivedTestPoints.size();
    g_Tp_pkt_tx_cnt = 0;
    g_counter_Tp_status = 0;
    // Clear the existing data in testPointMain
    testPointMain.clear();
    for (uint16_t i = 0; i < receivedTestPoints.size();
         ++i) { // Assuming receivedTestPointsCount is known
        TestPoint_main tmp = {};
        // Assuming direct copy is possible due to identical layout; otherwise, copy field by field.
        memcpy(&tmp, &receivedTestPoints[i], sizeof(TestPoint_main));
        testPointMain.append(tmp);
        // Usage
    } //    sendTP_data_to_UC();
}

QByteArray MainWindow::serializeTestPoint(const TestPoint_main &test_Point)
{
    QByteArray packet(reinterpret_cast<const char *>(&test_Point), sizeof(TestPoint_main));
    return packet;
    //    QByteArray byteArray;
    //    byteArray.reserve(sizeof(TestPoint_main)); // Pre-allocate memory for efficiency

    //    // Append each field to the QByteArray. This requires converting non-byte types.
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.startByte), sizeof(test_Point.startByte));
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.MsgID), sizeof(test_Point.MsgID));
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.packetSize), sizeof(test_Point.packetSize));
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.testPointNumber), sizeof(test_Point.testPointNumber));

    //    // For the array, we directly copy the memory
    //    byteArray.append(reinterpret_cast<const char*>(test_Point.TestPointData), sizeof(uint16_t) * 256);
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.Frequency), sizeof(test_Point.Frequency));
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.CH1_to_8_Amplitude), sizeof(float) * 8);
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.eraseCMD), sizeof(test_Point.eraseCMD));
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.CRC_WORD), sizeof(test_Point.CRC_WORD));
    //    byteArray.append(reinterpret_cast<const char*>(&test_Point.endByte), sizeof(test_Point.endByte));

    //    return byteArray;
}

QCustomPlot *MainWindow::getGraph1() const
{
    return ui->Graph1; // Assuming Graph1 is the name of the QCustomPlot widget in  UI
}

QCustomPlot *MainWindow::getGraph2() const
{
    return ui->Graph2; // Assuming Graph2 is the name of the QCustomPlot widget in  UI
}

QCustomPlot *MainWindow::getGraph3() const
{
    return ui->Graph3; // Assuming Graph2 is the name of the QCustomPlot widget in  UI
}

QCustomPlot *MainWindow::getGraph4() const
{
    return ui->Graph4; // Assuming Graph2 is the name of the QCustomPlot widget in  UI
}

QCustomPlot *MainWindow::getGraph5() const
{
    return ui->Graph5; // Assuming Graph2 is the name of the QCustomPlot widget in  UI
}

QCustomPlot *MainWindow::getGraph6() const
{
    return ui->Graph6; // Assuming Graph2 is the name of the QCustomPlot widget in  UI
}

QCustomPlot *MainWindow::getGraph7() const
{
    return ui->Graph7; // Assuming Graph2 is the name of the QCustomPlot widget in  UI
}

QCustomPlot *MainWindow::getGraph8() const
{
    return ui->Graph8; // Assuming Graph2 is the name of the QCustomPlot widget in  UI
}

void MainWindow::on_GraphSave_clicked()
{
    graphWidget->SaveGraph();
}

void MainWindow::on_GraphStop_toggled(bool checked)
{
    if (checked == true) {
        graphWidget->Stop_button_Clicked(checked);
        ui->GraphStop->setText("RUN");
    } else if (checked == false) {
        graphWidget->Stop_button_Clicked(checked);
        ui->GraphStop->setText("STOP");
    }
}

void MainWindow::on_EraseExtFlash_clicked()
{
    // Create a message box
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation");
    msgBox.setText("Do you want to proceed?This Action will Erase the Complete Test Point Data.");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    // Show the message box and get the user's response
    int ret = msgBox.exec();

    // Handle the user's response
    if (ret == QMessageBox::Ok) {
        qDebug("User clicked OK.");
        g_FlashErase.startByte = '$';
        g_FlashErase.packetSize = sizeof(FlashErase);
        g_FlashErase.MsgID = EXT_FLASH_ERASE;
        g_FlashErase.CRC_WORD = 0;
        g_FlashErase.endByte = 0x233B;
        g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_FlashErase, g_FlashErase.packetSize);
        g_FlashErase.CRC_WORD = g_CRC_word;
        emit serialWrite((char *) &g_FlashErase, g_FlashErase.packetSize);
    } else if (ret == QMessageBox::Cancel) {
        qDebug("User clicked Cancel.");
    }
}

void MainWindow::on_ReadDataFromFlash_clicked()
{
    g_ReadDataExtFlash.startByte = '$';
    g_ReadDataExtFlash.packetSize = sizeof(ReadDataExtFlash);
    g_ReadDataExtFlash.MsgID = READ_EXT_FLASH;
    g_ReadDataExtFlash.FTU_TestNo = g_TestPointNo;
    g_ReadDataExtFlash.CRC_WORD = 0;
    g_ReadDataExtFlash.endByte = 0x233B;
    g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_ReadDataExtFlash,
                                        g_ReadDataExtFlash.packetSize);
    g_ReadDataExtFlash.CRC_WORD = g_CRC_word;
    emit serialWrite((char *) &g_ReadDataExtFlash, g_ReadDataExtFlash.packetSize);
}

void MainWindow::on_USB_5856_AE_Card1_pb_clicked(bool checked)
{
    Logger::instance()->logText(QString("[INFO] USB_5856_AE_Card1:%1").arg(checked ? 1 : 0));

#if 1
    if (!usb5856_card1_success) {
        Logger::instance()->logText("[ERROR] Card1 is not initialized or failed.");

        if (!autoMode) {
            QMessageBox::warning(this, "Card Error", "Card1 is not initialized or failed.");
            ui->USB_5856_AE_Card1_pb->setChecked(false);
        } else {
            // Auto mode: non-blocking warning and auto skip
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning,
                                                  "Card Error",
                                                  "Card1 is not initialized or failed.",
                                                  QMessageBox::Ok,
                                                  this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setModal(false);
            msgBox->show();
            QTimer::singleShot(1500, msgBox, &QMessageBox::close); // Show for info only
        }

        if (g_mode_flag == AUTOMATIC_MODE) {
            QTimer::singleShot(10, this, SLOT(AutoStepCompleted())); // Go to next step
        }
        return;
    }
#endif
    if (checked) {
        ui->USB_5856_AE_Card1_pb->setEnabled(true);
        ui->USB_5856_AE_Card2_pb->setEnabled(false);
        ui->USB_5856_AE_Card3_pb->setEnabled(false);
        ui->USB_5856_AE_Card4_pb->setEnabled(false);
        emit card1Signal_ON(); // fire the cross-thread call
        ui->USB_5856_AE_Card1_pb->setStyleSheet(YBC);
    } else {
        emit card1Signal_OFF();
    }
}

void MainWindow::on_USB_5856_AE_Card2_pb_clicked(bool checked)
{
    Logger::instance()->logText(QString("[INFO] USB_5856_AE_Card2:%1").arg(checked ? 1 : 0));

    if (!usb5856_card2_success) {
        Logger::instance()->logText("[ERROR] Card2 is not initialized or failed.");

        if (!autoMode) {
            QMessageBox::warning(this, "Card Error", "Card2 is not initialized or failed.");
            ui->USB_5856_AE_Card2_pb->setChecked(false);
        } else {
            // Auto mode: non-blocking warning and auto skip
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning,
                                                  "Card Error",
                                                  "Card2 is not initialized or failed.",
                                                  QMessageBox::Ok,
                                                  this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setModal(false);
            msgBox->show();
            QTimer::singleShot(1500, msgBox, &QMessageBox::close); // Show for info only
        }

        if (g_mode_flag == AUTOMATIC_MODE) {
            QTimer::singleShot(10, this, SLOT(AutoStepCompleted())); // Go to next step
        }

        return;
    }

    if (checked) {
        ui->USB_5856_AE_Card1_pb->setEnabled(false);
        ui->USB_5856_AE_Card2_pb->setEnabled(true);
        ui->USB_5856_AE_Card3_pb->setEnabled(false);
        ui->USB_5856_AE_Card4_pb->setEnabled(false);
        emit card2Signal_ON();
        ui->USB_5856_AE_Card2_pb->setStyleSheet(YBC);
    } else {
        emit card2Signal_OFF();
    }
}

void MainWindow::on_USB_5856_AE_Card3_pb_clicked(bool checked)
{
    Logger::instance()->logText(QString("[INFO] USB_5856_AE_Card3:%1").arg(checked ? 1 : 0));

    if (!usb5856_card3_success) {
        Logger::instance()->logText("[ERROR] Card3 is not initialized or failed.");

        if (!autoMode) {
            QMessageBox::warning(this, "Card Error", "Card3 is not initialized or failed.");
            ui->USB_5856_AE_Card3_pb->setChecked(false);
        } else {
            // Auto mode: non-blocking warning and auto skip
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning,
                                                  "Card Error",
                                                  "Card3 is not initialized or failed.",
                                                  QMessageBox::Ok,
                                                  this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setModal(false);
            msgBox->show();
            QTimer::singleShot(1500, msgBox, &QMessageBox::close); // Show for info only
        }

        if (g_mode_flag == AUTOMATIC_MODE) {
            QTimer::singleShot(10, this, SLOT(AutoStepCompleted())); // Go to next step
        }

        return;
    }

    if (checked) {
        ui->USB_5856_AE_Card1_pb->setEnabled(false);
        ui->USB_5856_AE_Card2_pb->setEnabled(false);
        ui->USB_5856_AE_Card3_pb->setEnabled(true);
        ui->USB_5856_AE_Card4_pb->setEnabled(false);
        emit card3Signal_ON();
        ui->USB_5856_AE_Card3_pb->setStyleSheet(
            "color:black;background-color: rgb(255, 255, 0)"); /*YELLOW*/

    } else {
        emit card3Signal_OFF();
    }
}

void MainWindow::on_USB_5856_AE_Card4_pb_clicked(bool checked)
{
    Logger::instance()->logText(QString("[INFO] USB_5856_AE_Card4:%1").arg(checked ? 1 : 0));

    if (!usb5856_card2_success) {
        Logger::instance()->logText("[ERROR] Card4 is not initialized or failed.");

        if (!autoMode) {
            QMessageBox::warning(this, "Card Error", "Card4 is not initialized or failed.");
            ui->USB_5856_AE_Card4_pb->setChecked(false);
        } else {
            // Auto mode: non-blocking warning and auto skip
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning,
                                                  "Card Error",
                                                  "Card4 is not initialized or failed.",
                                                  QMessageBox::Ok,
                                                  this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setModal(false);
            msgBox->show();
            QTimer::singleShot(1500, msgBox, &QMessageBox::close); // Show for info only
        }

        if (g_mode_flag == AUTOMATIC_MODE) {
            QTimer::singleShot(10, this, SLOT(AutoStepCompleted())); // Go to next step
        }

        return;
    }

    if (checked) {
        ui->USB_5856_AE_Card1_pb->setEnabled(false);
        ui->USB_5856_AE_Card2_pb->setEnabled(false);
        ui->USB_5856_AE_Card3_pb->setEnabled(false);
        ui->USB_5856_AE_Card4_pb->setEnabled(true);
        ui->USB_5856_AE_Card4_pb->setStyleSheet(YBC);
        emit card4Signal_ON();

    } else {
        emit card4Signal_OFF();
    }
}
void MainWindow::on_USB_4716_AE_CARD2_pb_clicked(bool checked)
{
    Logger::instance()->logText(QString("[INFO] USB_4716_AE_CARD2:%1").arg(checked ? 1 : 0));

    if (checked) {
        ui->USB_4716_AE_CARD2_pb->setStyleSheet(YBC);

        emit adcCard2TriggerSignal(); // Signal to AdvWorker
    } else {
        emit ADC_4716card2Signal();
    }
}
void MainWindow::onCard2ADCResult(bool pass)
{
    ui->USB_4716_AE_CARD2_pb->setStyleSheet(pass ? GBC : RBC);
    ui->USB_4716_AE_CARD2_pb->setChecked(false);
    if (g_mode_flag == AUTOMATIC_MODE) {
        //g_initiate_sequence_counter++;
        //        qDebug() << "[RESULT] USB_4716 AE CARD2 Test:" << (pass ? "PASS" : "FAIL");

        QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
    }
}

//void MainWindow::on_USB_4716_AE_CARD2_pb_toggled(bool checked)
//{
//    Logger::instance()->logText(QString("[INFO] USB_4716_AE_CARD2:%1").arg(checked ? 1 : 0));
//    QString failedTests;
//    uint8_t voltage[9] = {0};
//    if (checked) {
//        ui->USB_4716_AE_CARD2_pb->setStyleSheet(YBC);
//        // g_AdvantechCardsInterface->DAC_VOLTAGE_DAC_CH1();
//        emit ADC_4716card2Signal();
//        for (int i = 0; i < 8; i++) {
//            voltage[0] |= (g_ADC_SelfTest.test1Status[i] & 0x01) << i;
//            voltage[1] |= (g_ADC_SelfTest.test2Status[i] & 0x01) << i;
//            voltage[2] |= (g_ADC_SelfTest.test3Status[i] & 0x01) << i;
//            voltage[3] |= (g_ADC_SelfTest.test4Status[i] & 0x01) << i;
//            voltage[4] |= (g_ADC_SelfTest.test5Status[i] & 0x01) << i;
//            voltage[5] |= (g_ADC_SelfTest.test6Status[i] & 0x01) << i;
//            voltage[6] |= (g_ADC_SelfTest.test7Status[i] & 0x01) << i;
//            voltage[7] |= (g_ADC_SelfTest.test8Status[i] & 0x01) << i;
//            voltage[8] |= (g_ADC_SelfTest.test9Status[i] & 0x01) << i;

//            bool allPass = true;
//            for (int i = 0; i < 9; ++i) {
//                if (voltage[i] != 0xFF) {
//                    allPass = false;

//                    //  break; // stop checking once you find one that isn't 0xFF
//                }
//            }

//            ui->USB_4716_AE_CARD2_pb->setStyleSheet(allPass ? GBC : RBC);
//            ui->USB_4716_AE_CARD2_pb->setChecked(false);
//        }

//    } else {
//        emit ADC_4716card2Signal();
//        //        ui->USB_4716_AE_CARD2_pb->setStyleSheet(
//        //            "background-color: rgb(232,232,232);color :rgb(0,0,0)"); //Greay
//    }
//    qDebug() << QString::number(voltage[0], 16);
//    qDebug() << QString::number(voltage[1], 16);
//    qDebug() << QString::number(voltage[2], 16);
//    qDebug() << QString::number(voltage[3], 16);
//    qDebug() << QString::number(voltage[4], 16);
//    qDebug() << QString::number(voltage[5], 16);
//    qDebug() << QString::number(voltage[6], 16);
//    qDebug() << QString::number(voltage[7], 16);
//    qDebug() << QString::number(voltage[8], 16);
//}

void MainWindow::updateLoopBackStatus(const QString &status)
{
    Logger::instance()->logText(QString("[INFO] LoopBack status: %1").arg(status));
    ui->RS422_LOOP_BACK_le1->setStyleSheet(YBC); /*YELLOW*/
    ui->RS422_LOOP_BACK_le1->setText(status);    // Set status to label
    //if (status == "PASS")
    //{
    //       ui-> RS422_LOOP_BACK_le1->setStyleSheet("color: green; font-weight: bold;");
    //  } else {

    //}
    //      ui->  RS422_LOOP_BACK_le1->setStyleSheet("color: red; font-weight: bold;");
    //    }
}

void MainWindow::on_REPORT_pb_clicked()
{
    onGenerateReportClicked();
    //    DC_DC_Report();
    //    Controller_Report();
    //    Display_Report();
}

void MainWindow::onGenerateReportClicked()
{
    QString outputDir = QFileDialog::getExistingDirectory(this, "Select Output Directory");

    if (outputDir.isEmpty())
        return;

    QString currentDate = QDate::currentDate().toString("dd-MM-yyyy");
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    // QString number = QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0');
    QString::number(Inputs, 16);

    QMap<QString, QString> Ate_Self_Test_Params{
        {"DD-MM-YYYY", currentDate},
        {"HH:MM:SEC", currentTime},
        {"xxxxx", QString("0x") + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0')},
        {"TESTED_BY", ui->tested_by_le->text()},
        {"Fsl_no", "1"},
        {"Remarks", ui->ATE_user_remarks_le->text()},
        {"ATE_SN", "001"},
        {"LV1_OBS", str1},
        {"I_16v", str1_I},
        {"R_1", rs16},
        {"LV2_OBS", str2},
        {"I_28v", str2_I},
        {"R_2", rs_28},
        {"LV3_OBS", str3},
        {"I_32v", str3_I},
        {"R_32", rs_32},
        {"28V Internal", ui->Volt_28_le->text()},
        {"I_28vInt", QString::number(g_CurrentSensorData.curr_PS1, 'f', 4)},
        {"R_PS1", rs28},
        {"IV1_OBS", ui->Volts_5_le->text()},
        {"I_5v", QString::number(g_CurrentSensorData.curr_PS3, 'f', 4)},
        {"R_PS3", rs5},
        {"SV1_OBS", ui->Volt_plus_5_le->text()},
        {"I_+5v", QString::number(g_CurrentSensorData.curr_PS5, 'f', 4)},
        {"R_PS5", rsplus5},
        {"SV2_OBS", ui->Volt_minus_5_le->text()},
        {"I_-5v", QString::number(g_CurrentSensorData.curr_PS6, 'f', 4)},
        {"R_PS6", rs_5},
        {"SV3_OBS", ui->Volt_3_3_le->text()},
        {"I_3.3v", QString::number(g_CurrentSensorData.curr_PS4, 'f', 4)},
        {"R_3", rs3},
        // {"EXT_VOl", str4},
        {"I_28vExt", str4_I},
        {"EXT_Res", Ex_28},
        {"op_C1", ui->USB_5856_output1_Card1_le->text()},
        {"r1_c", R1},
        {"op_C2", ui->USB_5856_output2_Card2_le->text()},
        {"r2_c", R2},
        {"op_C3", ui->USB_5856_output3_Card3_le->text()},
        {"r3_c", R3},
        {"op_C4", ui->USB_5856_output4_Card4_le->text()},
        {"r4_c", R4},
        {"ip_C1", ui->USB_5856_input1_Card1_le->text()},
        {"ip_C2", ui->USB_5856_input2_Card2_le->text()},
        {"ip_C3", ui->USB_5856_input3_Card3_le->text()},
        {"ip_C4", ui->USB_5856_input4_Card4_le->text()},
        {"tx1_data", ch1_tx},
        {"rx1_data", hexString2},
        {"CH1_RES", rs422_r1},
        {"tx2_data", ch2_tx},
        {"rx2_data", hexString1},
        {"CH2_RES", rs422_r2},
        {"led_status", ui->led_display_le->text()},
        {"Amp_Osc", ui->USB_5132_Oscilloscope_output_Card_le->text()},

        {"ch_1", QString::number(g_ADC_SelfTest.averagedAi_test1[0], 'f', 2)},
        {"ch_2", QString::number(g_ADC_SelfTest.averagedAi_test1[1], 'f', 2)},
        {"ch_3", QString::number(g_ADC_SelfTest.averagedAi_test1[2], 'f', 2)},
        {"ch_4", QString::number(g_ADC_SelfTest.averagedAi_test1[3], 'f', 2)},
        {"ch_5", QString::number(g_ADC_SelfTest.averagedAi_test1[4], 'f', 2)},
        {"ch_6", QString::number(g_ADC_SelfTest.averagedAi_test1[5], 'f', 2)},
        {"ch_7", QString::number(g_ADC_SelfTest.averagedAi_test1[6], 'f', 2)},
        {"ch_8", QString::number(g_ADC_SelfTest.averagedAi_test1[7], 'f', 2)},
        {"1pass_1", g_ADC_SelfTest.test1Status[0] == 1 ? "PASS" : "FAIL"},
        {"1pass_2", g_ADC_SelfTest.test1Status[1] == 1 ? "PASS" : "FAIL"},
        {"1pass_3", g_ADC_SelfTest.test1Status[2] == 1 ? "PASS" : "FAIL"},
        {"1pass_4", g_ADC_SelfTest.test1Status[3] == 1 ? "PASS" : "FAIL"},
        {"1pass_5", g_ADC_SelfTest.test1Status[4] == 1 ? "PASS" : "FAIL"},
        {"1pass_6", g_ADC_SelfTest.test1Status[5] == 1 ? "PASS" : "FAIL"},
        {"1pass_7", g_ADC_SelfTest.test1Status[6] == 1 ? "PASS" : "FAIL"},
        {"1pass_8", g_ADC_SelfTest.test1Status[7] == 1 ? "PASS" : "FAIL"},
        {"2ch_1", QString::number(g_ADC_SelfTest.averagedAi_test2[0], 'f', 2)},
        {"2ch_2", QString::number(g_ADC_SelfTest.averagedAi_test2[1], 'f', 2)},
        {"2ch_3", QString::number(g_ADC_SelfTest.averagedAi_test2[2], 'f', 2)},
        {"2ch_4", QString::number(g_ADC_SelfTest.averagedAi_test2[3], 'f', 2)},
        {"2ch_5", QString::number(g_ADC_SelfTest.averagedAi_test2[4], 'f', 2)},
        {"2ch_6", QString::number(g_ADC_SelfTest.averagedAi_test2[5], 'f', 2)},
        {"2ch_7", QString::number(g_ADC_SelfTest.averagedAi_test2[6], 'f', 2)},
        {"2ch_8", QString::number(g_ADC_SelfTest.averagedAi_test2[7], 'f', 2)},
        {"2pass_1", g_ADC_SelfTest.test2Status[0] == 1 ? "PASS" : "FAIL"},
        {"2pass_2", g_ADC_SelfTest.test2Status[1] == 1 ? "PASS" : "FAIL"},
        {"2pass_3", g_ADC_SelfTest.test2Status[2] == 1 ? "PASS" : "FAIL"},
        {"2pass_4", g_ADC_SelfTest.test2Status[3] == 1 ? "PASS" : "FAIL"},
        {"2pass_5", g_ADC_SelfTest.test2Status[4] == 1 ? "PASS" : "FAIL"},
        {"2pass_6", g_ADC_SelfTest.test2Status[5] == 1 ? "PASS" : "FAIL"},
        {"2pass_7", g_ADC_SelfTest.test2Status[6] == 1 ? "PASS" : "FAIL"},
        {"2pass_8", g_ADC_SelfTest.test2Status[7] == 1 ? "PASS" : "FAIL"},
        {"3ch_1", QString::number(g_ADC_SelfTest.averagedAi_test3[0], 'f', 2)},
        {"3ch_2", QString::number(g_ADC_SelfTest.averagedAi_test3[1], 'f', 2)},
        {"3ch_3", QString::number(g_ADC_SelfTest.averagedAi_test3[2], 'f', 2)},
        {"3ch_4", QString::number(g_ADC_SelfTest.averagedAi_test3[3], 'f', 2)},
        {"3ch_5", QString::number(g_ADC_SelfTest.averagedAi_test3[4], 'f', 2)},
        {"3ch_6", QString::number(g_ADC_SelfTest.averagedAi_test3[5], 'f', 2)},
        {"3ch_7", QString::number(g_ADC_SelfTest.averagedAi_test3[6], 'f', 2)},
        {"3ch_8", QString::number(g_ADC_SelfTest.averagedAi_test3[7], 'f', 2)},
        {"3pass_1", g_ADC_SelfTest.test3Status[0] == 1 ? "PASS" : "FAIL"},
        {"3pass_2", g_ADC_SelfTest.test3Status[1] == 1 ? "PASS" : "FAIL"},
        {"3pass_3", g_ADC_SelfTest.test3Status[2] == 1 ? "PASS" : "FAIL"},
        {"3pass_4", g_ADC_SelfTest.test3Status[3] == 1 ? "PASS" : "FAIL"},
        {"3pass_5", g_ADC_SelfTest.test3Status[4] == 1 ? "PASS" : "FAIL"},
        {"3pass_6", g_ADC_SelfTest.test3Status[5] == 1 ? "PASS" : "FAIL"},
        {"3pass_7", g_ADC_SelfTest.test3Status[6] == 1 ? "PASS" : "FAIL"},
        {"3pass_8", g_ADC_SelfTest.test3Status[7] == 1 ? "PASS" : "FAIL"},
        {"4ch_1", QString::number(g_ADC_SelfTest.averagedAi_test4[0], 'f', 2)},
        {"4ch_2", QString::number(g_ADC_SelfTest.averagedAi_test4[1], 'f', 2)},
        {"4ch_3", QString::number(g_ADC_SelfTest.averagedAi_test4[2], 'f', 2)},
        {"4ch_4", QString::number(g_ADC_SelfTest.averagedAi_test4[3], 'f', 2)},
        {"4ch_5", QString::number(g_ADC_SelfTest.averagedAi_test4[4], 'f', 2)},
        {"4ch_6", QString::number(g_ADC_SelfTest.averagedAi_test4[5], 'f', 2)},
        {"4ch_7", QString::number(g_ADC_SelfTest.averagedAi_test4[6], 'f', 2)},
        {"4ch_8", QString::number(g_ADC_SelfTest.averagedAi_test4[7], 'f', 2)},
        {"4pass_1", g_ADC_SelfTest.test4Status[0] == 1 ? "PASS" : "FAIL"},
        {"4pass_2", g_ADC_SelfTest.test4Status[1] == 1 ? "PASS" : "FAIL"},
        {"4pass_3", g_ADC_SelfTest.test4Status[2] == 1 ? "PASS" : "FAIL"},
        {"4pass_4", g_ADC_SelfTest.test4Status[3] == 1 ? "PASS" : "FAIL"},
        {"4pass_5", g_ADC_SelfTest.test4Status[4] == 1 ? "PASS" : "FAIL"},
        {"4pass_6", g_ADC_SelfTest.test4Status[5] == 1 ? "PASS" : "FAIL"},
        {"4pass_7", g_ADC_SelfTest.test4Status[6] == 1 ? "PASS" : "FAIL"},
        {"4pass_8", g_ADC_SelfTest.test4Status[7] == 1 ? "PASS" : "FAIL"},
        {"5ch_1", QString::number(g_ADC_SelfTest.averagedAi_test5[0], 'f', 2)},
        {"5ch_2", QString::number(g_ADC_SelfTest.averagedAi_test5[1], 'f', 2)},
        {"5ch_3", QString::number(g_ADC_SelfTest.averagedAi_test5[2], 'f', 2)},
        {"5ch_4", QString::number(g_ADC_SelfTest.averagedAi_test5[3], 'f', 2)},
        {"5ch_5", QString::number(g_ADC_SelfTest.averagedAi_test5[4], 'f', 2)},
        {"5ch_6", QString::number(g_ADC_SelfTest.averagedAi_test5[5], 'f', 2)},
        {"5ch_7", QString::number(g_ADC_SelfTest.averagedAi_test5[6], 'f', 2)},
        {"5ch_8", QString::number(g_ADC_SelfTest.averagedAi_test5[7], 'f', 2)},
        {"5pass_1", g_ADC_SelfTest.test5Status[0] == 1 ? "PASS" : "FAIL"},
        {"5pass_2", g_ADC_SelfTest.test5Status[1] == 1 ? "PASS" : "FAIL"},
        {"5pass_3", g_ADC_SelfTest.test5Status[2] == 1 ? "PASS" : "FAIL"},
        {"5pass_4", g_ADC_SelfTest.test5Status[3] == 1 ? "PASS" : "FAIL"},
        {"5pass_5", g_ADC_SelfTest.test5Status[4] == 1 ? "PASS" : "FAIL"},
        {"5pass_6", g_ADC_SelfTest.test5Status[5] == 1 ? "PASS" : "FAIL"},
        {"5pass_7", g_ADC_SelfTest.test5Status[6] == 1 ? "PASS" : "FAIL"},
        {"5pass_8", g_ADC_SelfTest.test5Status[7] == 1 ? "PASS" : "FAIL"},
        {"6ch_1", QString::number(g_ADC_SelfTest.averagedAi_test6[0], 'f', 2)},
        {"6ch_2", QString::number(g_ADC_SelfTest.averagedAi_test6[1], 'f', 2)},
        {"6ch_3", QString::number(g_ADC_SelfTest.averagedAi_test6[2], 'f', 2)},
        {"6ch_4", QString::number(g_ADC_SelfTest.averagedAi_test6[3], 'f', 2)},
        {"6ch_5", QString::number(g_ADC_SelfTest.averagedAi_test6[4], 'f', 2)},
        {"6ch_6", QString::number(g_ADC_SelfTest.averagedAi_test6[5], 'f', 2)},
        {"6ch_7", QString::number(g_ADC_SelfTest.averagedAi_test6[6], 'f', 2)},
        {"6ch_8", QString::number(g_ADC_SelfTest.averagedAi_test6[7], 'f', 2)},
        {"6pass_1", g_ADC_SelfTest.test6Status[0] == 1 ? "PASS" : "FAIL"},
        {"6pass_2", g_ADC_SelfTest.test6Status[1] == 1 ? "PASS" : "FAIL"},
        {"6pass_3", g_ADC_SelfTest.test6Status[2] == 1 ? "PASS" : "FAIL"},
        {"6pass_4", g_ADC_SelfTest.test6Status[3] == 1 ? "PASS" : "FAIL"},
        {"6pass_5", g_ADC_SelfTest.test6Status[4] == 1 ? "PASS" : "FAIL"},
        {"6pass_6", g_ADC_SelfTest.test6Status[5] == 1 ? "PASS" : "FAIL"},
        {"6pass_7", g_ADC_SelfTest.test6Status[6] == 1 ? "PASS" : "FAIL"},
        {"6pass_8", g_ADC_SelfTest.test6Status[7] == 1 ? "PASS" : "FAIL"},
        {"7ch_1", QString::number(g_ADC_SelfTest.averagedAi_test7[0], 'f', 2)},
        {"7ch_2", QString::number(g_ADC_SelfTest.averagedAi_test7[1], 'f', 2)},
        {"7ch_3", QString::number(g_ADC_SelfTest.averagedAi_test7[2], 'f', 2)},
        {"7ch_4", QString::number(g_ADC_SelfTest.averagedAi_test7[3], 'f', 2)},
        {"7ch_5", QString::number(g_ADC_SelfTest.averagedAi_test7[4], 'f', 2)},
        {"7ch_6", QString::number(g_ADC_SelfTest.averagedAi_test7[5], 'f', 2)},
        {"7ch_7", QString::number(g_ADC_SelfTest.averagedAi_test7[6], 'f', 2)},
        {"7ch_8", QString::number(g_ADC_SelfTest.averagedAi_test7[7], 'f', 2)},
        {"7pass_1", g_ADC_SelfTest.test7Status[0] == 1 ? "PASS" : "FAIL"},
        {"7pass_2", g_ADC_SelfTest.test7Status[1] == 1 ? "PASS" : "FAIL"},
        {"7pass_3", g_ADC_SelfTest.test7Status[2] == 1 ? "PASS" : "FAIL"},
        {"7pass_4", g_ADC_SelfTest.test7Status[3] == 1 ? "PASS" : "FAIL"},
        {"7pass_5", g_ADC_SelfTest.test7Status[4] == 1 ? "PASS" : "FAIL"},
        {"7pass_6", g_ADC_SelfTest.test7Status[5] == 1 ? "PASS" : "FAIL"},
        {"7pass_7", g_ADC_SelfTest.test7Status[6] == 1 ? "PASS" : "FAIL"},
        {"7pass_8", g_ADC_SelfTest.test7Status[7] == 1 ? "PASS" : "FAIL"},
        {"8ch_1", QString::number(g_ADC_SelfTest.averagedAi_test8[0], 'f', 2)},
        {"8ch_2", QString::number(g_ADC_SelfTest.averagedAi_test8[1], 'f', 2)},
        {"8ch_3", QString::number(g_ADC_SelfTest.averagedAi_test8[2], 'f', 2)},
        {"8ch_4", QString::number(g_ADC_SelfTest.averagedAi_test8[3], 'f', 2)},
        {"8ch_5", QString::number(g_ADC_SelfTest.averagedAi_test8[4], 'f', 2)},
        {"8ch_6", QString::number(g_ADC_SelfTest.averagedAi_test8[5], 'f', 2)},
        {"8ch_7", QString::number(g_ADC_SelfTest.averagedAi_test8[6], 'f', 2)},
        {"8ch_8", QString::number(g_ADC_SelfTest.averagedAi_test8[7], 'f', 2)},
        {"8pass_1", g_ADC_SelfTest.test8Status[0] == 1 ? "PASS" : "FAIL"},
        {"8pass_2", g_ADC_SelfTest.test8Status[1] == 1 ? "PASS" : "FAIL"},
        {"8pass_3", g_ADC_SelfTest.test8Status[2] == 1 ? "PASS" : "FAIL"},
        {"8pass_4", g_ADC_SelfTest.test8Status[3] == 1 ? "PASS" : "FAIL"},
        {"8pass_5", g_ADC_SelfTest.test8Status[4] == 1 ? "PASS" : "FAIL"},
        {"8pass_6", g_ADC_SelfTest.test8Status[5] == 1 ? "PASS" : "FAIL"},
        {"8pass_7", g_ADC_SelfTest.test8Status[6] == 1 ? "PASS" : "FAIL"},
        {"8pass_8", g_ADC_SelfTest.test8Status[7] == 1 ? "PASS" : "FAIL"},
        {"9ch_1", QString::number(g_ADC_SelfTest.averagedAi_test9[0], 'f', 2)},
        {"9ch_2", QString::number(g_ADC_SelfTest.averagedAi_test9[1], 'f', 2)},
        {"9ch_3", QString::number(g_ADC_SelfTest.averagedAi_test9[2], 'f', 2)},
        {"9ch_4", QString::number(g_ADC_SelfTest.averagedAi_test9[3], 'f', 2)},
        {"9ch_5", QString::number(g_ADC_SelfTest.averagedAi_test9[4], 'f', 2)},
        {"9ch_6", QString::number(g_ADC_SelfTest.averagedAi_test9[5], 'f', 2)},
        {"9ch_7", QString::number(g_ADC_SelfTest.averagedAi_test9[6], 'f', 2)},
        {"9ch_8", QString::number(g_ADC_SelfTest.averagedAi_test9[7], 'f', 2)},
        {"9pass_1", g_ADC_SelfTest.test9Status[0] == 1 ? "PASS" : "FAIL"},
        {"9pass_2", g_ADC_SelfTest.test9Status[1] == 1 ? "PASS" : "FAIL"},
        {"9pass_3", g_ADC_SelfTest.test9Status[2] == 1 ? "PASS" : "FAIL"},
        {"9pass_4", g_ADC_SelfTest.test9Status[3] == 1 ? "PASS" : "FAIL"},
        {"9pass_5", g_ADC_SelfTest.test9Status[4] == 1 ? "PASS" : "FAIL"},
        {"9pass_6", g_ADC_SelfTest.test9Status[5] == 1 ? "PASS" : "FAIL"},
        {"9pass_7", g_ADC_SelfTest.test9Status[6] == 1 ? "PASS" : "FAIL"},
        {"9pass_8", g_ADC_SelfTest.test9Status[7] == 1 ? "PASS" : "FAIL"}};

    QString Ate_Self_Test_Report_HTML
        = ReportTemplates::populateTemplate(ReportTemplates::Ate_Self_Test_Report(),
                                            Ate_Self_Test_Params);

    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString pdfPath = outputDir + "/self_test_report_" + timestamp + ".pdf";
    QString odtPath = outputDir + "/self_test_report_" + timestamp + ".odt";

    ReportGenerator gen;
    gen.generateReport(Ate_Self_Test_Report_HTML, pdfPath);

    QMessageBox::information(this,
                             "Success",
                             "ATE SELF-TEST Report generated successfully:\n" + pdfPath);
    ui->REPORT_pb->setStyleSheet(GBC);
    ui->REPORT_pb->setChecked(false);
}

QString getLatestScopeCaptureFile(const QString &folderPath)
{
    QDir dir(folderPath);
    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << folderPath;
        return QString();
    }

    // Filter only PNG files that match the pattern
    QStringList filters;
    filters << "scope_capture_*.png";
    QFileInfoList files = dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot, QDir::Name);

    QRegularExpression re(R"(scope_capture_(\d{4})-(\d{2})-(\d{2})_(\d{2})-(\d{2})-(\d{2})\.png)");

    QDateTime latestDateTime;
    QString latestFilePath;

    for (const QFileInfo &file : files) {
        QRegularExpressionMatch match = re.match(file.fileName());
        if (match.hasMatch()) {
            int year = match.captured(1).toInt();
            int month = match.captured(2).toInt();
            int day = match.captured(3).toInt();
            int hour = match.captured(4).toInt();
            int minute = match.captured(5).toInt();
            int second = match.captured(6).toInt();

            QDateTime dt(QDate(year, month, day), QTime(hour, minute, second));
            if (!latestDateTime.isValid() || dt > latestDateTime) {
                latestDateTime = dt;
                latestFilePath = file.absoluteFilePath();
            }
        }
    }

    if (latestFilePath.isEmpty())
        qWarning() << "No valid scope_capture_*.png files found in" << folderPath;

    return latestFilePath;
}

void MainWindow::DC_DC_Report()
{
    SruLogger::instance()->logText(QString("DCDC Sl No.").arg(ui->DC_DCslno_le->text()));
    SruLogger::instance()->logText(QString("Display Sl No.").arg(ui->Displayslno_le->text()));
    QString DC_DC = QFileDialog::getExistingDirectory(this, "Select Output Directory");
    if (DC_DC.isEmpty())
        return;
    QString baseFolder = "C:/FTU_ATE/Ripple_Images";

    QString path_5V = getLatestScopeCaptureFile(baseFolder + "/Plus5V");
    QString path_N_5V = getLatestScopeCaptureFile(baseFolder + "/Minus5V");
    QString path_3p3V = getLatestScopeCaptureFile(baseFolder + "/3P3");

    QString currentDate = QDate::currentDate().toString("dd-MM-yyyy");
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString number = "0x" + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0');
    QString::number(Inputs, 16);

    QMap<QString, QString> isolation_Params{
        {"DD-MM-YYYY", currentDate},
        {"HH:MM:SEC", currentTime},
        {"ATE_cksum", number},
        {"test_name", ui->SRU_Test_Name->text()},
        {"TESTED_BY", ui->SRU_TestedBy->text()},
        {"ATE_SLNO", "001"},
        {"DC_Remarks", ui->Sru_UR->text()},
        {"DC_DC slno", ui->DC_DCslno_le->text()},
        {"Display slno", ui->Displayslno_le->text()},
        //        {"v3.3_exp_R", "4.737k&Omega; &plusmn; 0.737k&Omega;"},
        //        {"v3.3_Result", Iso_3R},
        //        {"v+5_exp_R", "6.0602k&Omega; &plusmn; 0.606k&Omega;"},
        //        {"v+5_Result", Iso_5R},
        //        {"v-5_exp_R", "4.926k&Omega; &plusmn; 0.926k&Omega;"},
        //        {"v-5_Result", Iso_N5R},
        {"vol_obs", ui->SRU_V_le->text()},
        {"Curr_Obs", ui->SRU_I_le->text()},
        {"ov_10l_3p3", ui->Load10_3_3V_le->text()},
        {"ov_100l_3p3", ui->Load100_3_3V_le->text()},
        {"res_v1_3p3", DC_L10_3p3V},
        {"oi_10l_3p3", ui->Load10_3_3v_Current_le->text()},
        {"oi_100l_3p3", ui->Load100_3_3v_Current_le->text()},
        {"res_I1_3p3", L10_I3p3V},
        {"ov_10l_5V", ui->Load10_5V_le->text()},
        {"ov_100l_5V", ui->Load100_5V_le->text()},
        {"res_v2_5V", DC_L10_5V},
        {"oi_10l_5V", ui->Load10_5v_I_le->text()},
        {"oi_100l_5V", ui->Load100_5v_I_op_le->text()},
        {"res_I2_5V", L10_I5V},
        {"ov_10l_N_5V", ui->Load10_minus5V_le->text()},
        {"ov_100l_N_5V", ui->Load100_N_5V_le->text()},
        {"res_v3_N_5V", DC_L10_N5V},
        {"oi_10l_N_5V", ui->Load10_minus5v_I_le->text()},
        {"oi_100l_N_5V", ui->Load100_N_5v_I_op_le->text()},
        {"res_I3_N_5V", L10_IN5V},

        {"res_v100_3p3", DC_L100_3p3V},
        {"res_I100_3p3", L100_I3p3V},
        {"res_v100_5v", DC_L100_5V},
        {"res_I100_5V", L100_I5V},
        {"res_V100_N_5v", DC_L100_N5V},
        {"res_I100_N5V", L100_IN5V},
        {"Max_3.3Obs", ui->MAX_R_3p3V_LE->text()},
        {"Max_3.3Exp", "0.200V"},
        {"Res_Max3.3", maxResult3p3V},
        {"Min_3.3Obs", ui->MIN_R_3p3V_LE->text()},
        {"Min_3.3Exp", "-0.200V"},
        {"Res_Min3.3", minResult3p3V},
        {"Max_+5VObs", ui->MAX_R_p5V_LE->text()},
        {"Max_+5VExp", "0.200V"},
        {"Res_Max5", maxResult5V},
        {"Min_+5VObs", ui->MIN_R_p5V_LE->text()},
        {"Min_+5VExp", "-0.200V"},
        {"Res_Min5", minResult5V},
        {"Max_-5VObs", ui->MAX_R_N5V_LE->text()},
        {"Max_-5VExp", "0.200V"},
        {"Res_MaxN5", maxResultN5V},
        {"Min_-5VObs", ui->MIN_R_N5V_LE->text()},
        {"Min_-5VExp", "-0.200V"},
        {"Res_MinN5", minResultN5V},
        {"Graph_Image_5",
         !path_5V.isEmpty()
             ? QString("<img src='file:///%1' width='700'/>").arg(path_5V.replace("\\", "/"))
             : "<p>No +5V image found.</p>"},

        {"Graph_Image_N_5",
         !path_N_5V.isEmpty()
             ? QString("<img src='file:///%1' width='700'/>").arg(path_N_5V.replace("\\", "/"))
             : "<p>No -5V image found.</p>"},

        {"Graph_Image_3p3",
         !path_3p3V.isEmpty()
             ? QString("<img src='file:///%1' width='700'/>").arg(path_3p3V.replace("\\", "/"))
             : "<p>No 3.3V ripple image found.</p>"},
        {"Dis_obs1", Display1},
        {"Res_Dis1", D1_Status},
        {"Dis_obs2", Display2},
        {"Res_Dis2", D2_Status},
        {"Dis_obs3", Display3},
        {"Res_Dis3", D3_Status}};

    QString DC_DC_Report_HTML = ReportTemplates::populateTemplate(ReportTemplates::DC_DC_Report(),
                                                                  isolation_Params);

    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString pdfPath = DC_DC + "/DC-DC & Display Module_Report_" + timestamp + ".pdf";

    ReportGenerator gen;
    gen.generateReport(DC_DC_Report_HTML, pdfPath);

    QMessageBox::information(this,
                             "Success",
                             "DC DC & Display Module Report generated successfully:\n" + pdfPath);
    ui->SRU_DCDC_REPORT->setStyleSheet(GBC);
    ui->SRU_DCDC_REPORT->setChecked(false);
}

void MainWindow::Controller_Report()
{
    QString cntrller = QFileDialog::getExistingDirectory(this, "Select Output Directory");
    if (cntrller.isEmpty())
        return;
    QString currentDate = QDate::currentDate().toString("dd-MM-yyyy");
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString number = "0x" + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0');
    QString::number(Inputs, 16);

    //    CC_ISO_3p3 = ui->CC_Dig_Iso_3p3V_le->text(); //4.737kΩ ± 0.737kΩ
    //    float fixed_Iso3 = 4.737, I_3p3 = 0.0;
    //    float CI3V = ui->CC_Dig_Iso_3p3V_le->text().toFloat();
    //    I_3p3 = CI3V - fixed_Iso3;
    //    if (ui->CC_Dig_Iso_3p3V_le->text().isEmpty()) {
    //        Iso_3R = " ";
    //    } else if ((I_3p3 >= -(0.737)) && (I_3p3 <= (0.737))) {
    //        Iso_3R = "PASS";
    //    } else {
    //        Iso_3R = "FAIL";
    //    }

    //    CC_ISO_5V = ui->CC_Iso_5V_le->text(); //6.0602kΩ ± 0.606kΩ
    //    float fixed_Iso5 = 6.0602, I_5 = 0.0;
    //    float CI5V = ui->CC_Iso_5V_le->text().toFloat();
    //    I_5 = CI5V - fixed_Iso5;
    //    // if (ui->CC_Iso_5V_le->text().isEmpty())

    //    if ((I_5 >= -(0.606)) && (I_5 <= (0.606))) {
    //        Iso_5R = "PASS";
    //    } else {
    //        Iso_5R = "FAIL";
    //    }

    //    CC_ISO_N5V = ui->CC_Iso_N_5V_le->text(); //4.926kΩ ± 0.926kΩ
    //    float fixed_IsoN5 = 4.926, I_N5 = 0.0;
    //    float CIN5V = ui->CC_Iso_N_5V_le->text().toFloat();
    //    I_N5 = CIN5V - fixed_IsoN5;
    //    if (ui->CC_Iso_N_5V_le->text().isEmpty()) {
    //    }
    //    if ((I_N5 >= -(0.926)) && (I_N5 <= (0.926))) {
    //        Iso_N5R = "PASS";
    //    } else {
    //        Iso_N5R = "FAIL";
    //    }

    QMap<QString, QString>
        cntrl_card{{"Fsl_no", "001"},
                   {"DD-MM-YYYY", currentDate},
                   {"HH:MM:SEC", currentTime},
                   {"test_name", ui->SRU_Test_Name->text()},
                   {"TESTED_BY", ui->SRU_TestedBy->text()},
                   {"ATE_SLNO", "1 "},
                   {"cntrl_Remarks", ui->cntrl_URemarks->text()},
                   {"ATE_cksum", number},
                   {"CC_cksum", QString::number(g_Post_Status_data.AppFlash_SW_CRC, 16)},
                   {"CC_slno", ui->CCardslno_le->text()},
                   //                   {"v3.3_E_R", "4.737k&Omega; &plusmn; 0.737k&Omega;"},
                   //                   {"v3.3_Res", /*Iso_3R*/ ""},
                   //                   {"v+5_E_R", "6.0602k&Omega;&plusmn; 0.606k&Omega;"},
                   //                   {"v+5_Res", /*Iso_5R*/ ""},
                   //                   {"v-5_E_R", "4.926k&Omega; &plusmn; 0.926k&Omega;"},
                   //                   {"v-5_Res", /*Iso_N5R*/ ""},
                   {"ov_3p3", ui->CC_3p3_V_Dig_le->text()},
                   {"res_3p3v", rsV3},
                   {"oi_3p3", ui->CC_3p3_Current_Dig_le->text()},
                   {"res_C1", rsI3},
                   {"ov_+5V", ui->CC_5V_le->text()},
                   {"res_+5v", rsV5},
                   {"oi_+5v", ui->CC_5V_Current_le->text()},
                   {"res_C2", rsI5},
                   {"ov_N5v", ui->CC_N_5v_le->text()},
                   {"res_N5v", rsNV5},
                   {"oi_N5V", ui->CC_N_5v_Current_le->text()},
                   {"res_C3", rsNI5},
                   {"CH1_TX", RX1_Pat1},
                   {"CH1_RX", RX1_Pat2},
                   {"C1_RES", CC_Ch1},
                   {"CH2_TX", RX2_Pat1},
                   {"CH2_RX", RX2_Pat2},
                   {"C2_RES", CC_Ch2},
                   {"Rot_Obs_1", RotaryS1},
                   {"Rotrary_R1", Rotary_S1_Result /*ui->CC_Rotary1_R_le->text()*/},
                   {"Rot_Obs_2", RotaryS2},
                   {"Rotrary_R2", ui->CC_Rotary2_R_le->text()},
                   {"Rotrary_R3", ui->CC_Rotary3_R_le->text()},
                   {"Rot_Obs_3", RotaryS3},
                   {"Ob_Rot_ObsOFF_1", Rotary_S1},
                   {"Ob_Rot_ObsOFF_2", Rotary_S2},
                   {"Ob_Rot_ObsOFF_3", Rotary_S3},
                   {"Ob_Prep", SRU_Prep_ON},
                   {"Prep_R", SRU_Prep_R},
                   {"Ob_ReadyI", SRU_ReadyI_ON},
                   {"RInit_R", SRU_ReadyI_R},
                   {"Ob_Abort", SRU_Abort_ON},
                   {"Abort_R", SRU_Abort_R},
                   {"D_Obs_C1", Dis_Out1_ON},
                   {"Dis_O_Re1", Dis_Out_R1},
                   {"D_Obs_C2", Dis_Out2_ON},
                   {"Dis_O_Re2", Dis_Out_R2},
                   {"D_Obs_C3", Dis_Out3_ON},
                   {"Dis_O_Re3", Dis_Out_R3},
                   {"D_Obs_C4", Dis_Out4_ON},
                   {"Dis_O_Re4", Dis_Out_R4},
                   {"D_Obs_C5", Dis_Out5_ON},
                   {"Dis_O_Re5", Dis_Out_R5},
                   {"Obs_ch1", Dis_In1_ON},
                   {"Res_I_ch1", Dis_In_R1},
                   {"Obs_ch2", Dis_In2_ON},
                   {"Res_I_ch2", Dis_In_R2},
                   {"Obs_ch3", Dis_In3_ON},
                   {"Res_I_ch3", Dis_In_R3},
                   {"chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[0], 'f', 2)},
                   {"chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[1], 'f', 2)},
                   {"chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[2], 'f', 2)},
                   {"chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[3], 'f', 2)},
                   {"chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[4], 'f', 2)},
                   {"chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[5], 'f', 2)},
                   {"chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[6], 'f', 2)},
                   {"chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[7], 'f', 2)},
                   {"1passC_1", g_ADC_Card2_BitTest.test1Status[0] == 1 ? "PASS" : "FAIL"},
                   {"1passC_2", g_ADC_Card2_BitTest.test1Status[1] == 1 ? "PASS" : "FAIL"},
                   {"1passC_3", g_ADC_Card2_BitTest.test1Status[2] == 1 ? "PASS" : "FAIL"},
                   {"1passC_4", g_ADC_Card2_BitTest.test1Status[3] == 1 ? "PASS" : "FAIL"},
                   {"1passC_5", g_ADC_Card2_BitTest.test1Status[4] == 1 ? "PASS" : "FAIL"},
                   {"1passC_6", g_ADC_Card2_BitTest.test1Status[5] == 1 ? "PASS" : "FAIL"},
                   {"1passC_7", g_ADC_Card2_BitTest.test1Status[6] == 1 ? "PASS" : "FAIL"},
                   {"1passC_8", g_ADC_Card2_BitTest.test1Status[7] == 1 ? "PASS" : "FAIL"},
                   {"2chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[0], 'f', 2)},
                   {"2chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[1], 'f', 2)},
                   {"2chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[2], 'f', 2)},
                   {"2chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[3], 'f', 2)},
                   {"2chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[4], 'f', 2)},
                   {"2chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[5], 'f', 2)},
                   {"2chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[6], 'f', 2)},
                   {"2chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[7], 'f', 2)},
                   {"2passC_1", g_ADC_Card2_BitTest.test2Status[0] == 1 ? "PASS" : "FAIL"},
                   {"2passC_2", g_ADC_Card2_BitTest.test2Status[1] == 1 ? "PASS" : "FAIL"},
                   {"2passC_3", g_ADC_Card2_BitTest.test2Status[2] == 1 ? "PASS" : "FAIL"},
                   {"2passC_4", g_ADC_Card2_BitTest.test2Status[3] == 1 ? "PASS" : "FAIL"},
                   {"2passC_5", g_ADC_Card2_BitTest.test2Status[4] == 1 ? "PASS" : "FAIL"},
                   {"2passC_6", g_ADC_Card2_BitTest.test2Status[5] == 1 ? "PASS" : "FAIL"},
                   {"2passC_7", g_ADC_Card2_BitTest.test2Status[6] == 1 ? "PASS" : "FAIL"},
                   {"2passC_8", g_ADC_Card2_BitTest.test2Status[7] == 1 ? "PASS" : "FAIL"},
                   {"3chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[0], 'f', 2)},
                   {"3chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[1], 'f', 2)},
                   {"3chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[2], 'f', 2)},
                   {"3chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[3], 'f', 2)},
                   {"3chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[4], 'f', 2)},
                   {"3chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[5], 'f', 2)},
                   {"3chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[6], 'f', 2)},
                   {"3chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[7], 'f', 2)},
                   {"3passC_1", g_ADC_Card2_BitTest.test3Status[0] == 1 ? "PASS" : "FAIL"},
                   {"3passC_2", g_ADC_Card2_BitTest.test3Status[1] == 1 ? "PASS" : "FAIL"},
                   {"3passC_3", g_ADC_Card2_BitTest.test3Status[2] == 1 ? "PASS" : "FAIL"},
                   {"3passC_4", g_ADC_Card2_BitTest.test3Status[3] == 1 ? "PASS" : "FAIL"},
                   {"3passC_5", g_ADC_Card2_BitTest.test3Status[4] == 1 ? "PASS" : "FAIL"},
                   {"3passC_6", g_ADC_Card2_BitTest.test3Status[5] == 1 ? "PASS" : "FAIL"},
                   {"3passC_7", g_ADC_Card2_BitTest.test3Status[6] == 1 ? "PASS" : "FAIL"},
                   {"3passC_8", g_ADC_Card2_BitTest.test3Status[7] == 1 ? "PASS" : "FAIL"},
                   {"4chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[0], 'f', 2)},
                   {"4chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[1], 'f', 2)},
                   {"4chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[2], 'f', 2)},
                   {"4chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[3], 'f', 2)},
                   {"4chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[4], 'f', 2)},
                   {"4chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[5], 'f', 2)},
                   {"4chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[6], 'f', 2)},
                   {"4chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[7], 'f', 2)},
                   {"4passC_1", g_ADC_Card2_BitTest.test4Status[0] == 1 ? "PASS" : "FAIL"},
                   {"4passC_2", g_ADC_Card2_BitTest.test4Status[1] == 1 ? "PASS" : "FAIL"},
                   {"4passC_3", g_ADC_Card2_BitTest.test4Status[2] == 1 ? "PASS" : "FAIL"},
                   {"4passC_4", g_ADC_Card2_BitTest.test4Status[3] == 1 ? "PASS" : "FAIL"},
                   {"4passC_5", g_ADC_Card2_BitTest.test4Status[4] == 1 ? "PASS" : "FAIL"},
                   {"4passC_6", g_ADC_Card2_BitTest.test4Status[5] == 1 ? "PASS" : "FAIL"},
                   {"4passC_7", g_ADC_Card2_BitTest.test4Status[6] == 1 ? "PASS" : "FAIL"},
                   {"4passC_8", g_ADC_Card2_BitTest.test4Status[7] == 1 ? "PASS" : "FAIL"},
                   {"5chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[0], 'f', 2)},
                   {"5chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[1], 'f', 2)},
                   {"5chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[2], 'f', 2)},
                   {"5chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[3], 'f', 2)},
                   {"5chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[4], 'f', 2)},
                   {"5chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[5], 'f', 2)},
                   {"5chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[6], 'f', 2)},
                   {"5chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[7], 'f', 2)},
                   {"5passC_1", g_ADC_Card2_BitTest.test5Status[0] == 1 ? "PASS" : "FAIL"},
                   {"5passC_2", g_ADC_Card2_BitTest.test5Status[1] == 1 ? "PASS" : "FAIL"},
                   {"5passC_3", g_ADC_Card2_BitTest.test5Status[2] == 1 ? "PASS" : "FAIL"},
                   {"5passC_4", g_ADC_Card2_BitTest.test5Status[3] == 1 ? "PASS" : "FAIL"},
                   {"5passC_5", g_ADC_Card2_BitTest.test5Status[4] == 1 ? "PASS" : "FAIL"},
                   {"5passC_6", g_ADC_Card2_BitTest.test5Status[5] == 1 ? "PASS" : "FAIL"},
                   {"5passC_7", g_ADC_Card2_BitTest.test5Status[6] == 1 ? "PASS" : "FAIL"},
                   {"5passC_8", g_ADC_Card2_BitTest.test5Status[7] == 1 ? "PASS" : "FAIL"},
                   {"6chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[0], 'f', 2)},
                   {"6chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[1], 'f', 2)},
                   {"6chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[2], 'f', 2)},
                   {"6chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[3], 'f', 2)},
                   {"6chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[4], 'f', 2)},
                   {"6chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[5], 'f', 2)},
                   {"6chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[6], 'f', 2)},
                   {"6chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[7], 'f', 2)},
                   {"6passC_1", g_ADC_Card2_BitTest.test6Status[0] == 1 ? "PASS" : "FAIL"},
                   {"6passC_2", g_ADC_Card2_BitTest.test6Status[1] == 1 ? "PASS" : "FAIL"},
                   {"6passC_3", g_ADC_Card2_BitTest.test6Status[2] == 1 ? "PASS" : "FAIL"},
                   {"6passC_4", g_ADC_Card2_BitTest.test6Status[3] == 1 ? "PASS" : "FAIL"},
                   {"6passC_5", g_ADC_Card2_BitTest.test6Status[4] == 1 ? "PASS" : "FAIL"},
                   {"6passC_6", g_ADC_Card2_BitTest.test6Status[5] == 1 ? "PASS" : "FAIL"},
                   {"6passC_7", g_ADC_Card2_BitTest.test6Status[6] == 1 ? "PASS" : "FAIL"},
                   {"6passC_8", g_ADC_Card2_BitTest.test6Status[7] == 1 ? "PASS" : "FAIL"},
                   {"7chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[0], 'f', 2)},
                   {"7chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[1], 'f', 2)},
                   {"7chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[2], 'f', 2)},
                   {"7chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[3], 'f', 2)},
                   {"7chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[4], 'f', 2)},
                   {"7chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[5], 'f', 2)},
                   {"7chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[6], 'f', 2)},
                   {"7chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[7], 'f', 2)},
                   {"7passC_1", g_ADC_Card2_BitTest.test7Status[0] == 1 ? "PASS" : "FAIL"},
                   {"7passC_2", g_ADC_Card2_BitTest.test7Status[1] == 1 ? "PASS" : "FAIL"},
                   {"7passC_3", g_ADC_Card2_BitTest.test7Status[2] == 1 ? "PASS" : "FAIL"},
                   {"7passC_4", g_ADC_Card2_BitTest.test7Status[3] == 1 ? "PASS" : "FAIL"},
                   {"7passC_5", g_ADC_Card2_BitTest.test7Status[4] == 1 ? "PASS" : "FAIL"},
                   {"7passC_6", g_ADC_Card2_BitTest.test7Status[5] == 1 ? "PASS" : "FAIL"},
                   {"7passC_7", g_ADC_Card2_BitTest.test7Status[6] == 1 ? "PASS" : "FAIL"},
                   {"7passC_8", g_ADC_Card2_BitTest.test7Status[7] == 1 ? "PASS" : "FAIL"},
                   {"8chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[0], 'f', 2)},
                   {"8chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[1], 'f', 2)},
                   {"8chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[2], 'f', 2)},
                   {"8chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[3], 'f', 2)},
                   {"8chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[4], 'f', 2)},
                   {"8chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[5], 'f', 2)},
                   {"8chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[6], 'f', 2)},
                   {"8chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[7], 'f', 2)},
                   {"8passC_1", g_ADC_Card2_BitTest.test8Status[0] == 1 ? "PASS" : "FAIL"},
                   {"8passC_2", g_ADC_Card2_BitTest.test8Status[1] == 1 ? "PASS" : "FAIL"},
                   {"8passC_3", g_ADC_Card2_BitTest.test8Status[2] == 1 ? "PASS" : "FAIL"},
                   {"8passC_4", g_ADC_Card2_BitTest.test8Status[3] == 1 ? "PASS" : "FAIL"},
                   {"8passC_5", g_ADC_Card2_BitTest.test8Status[4] == 1 ? "PASS" : "FAIL"},
                   {"8passC_6", g_ADC_Card2_BitTest.test8Status[5] == 1 ? "PASS" : "FAIL"},
                   {"8passC_7", g_ADC_Card2_BitTest.test8Status[6] == 1 ? "PASS" : "FAIL"},
                   {"8passC_8", g_ADC_Card2_BitTest.test8Status[7] == 1 ? "PASS" : "FAIL"},
                   {"9chC_1", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[0], 'f', 2)},
                   {"9chC_2", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[1], 'f', 2)},
                   {"9chC_3", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[2], 'f', 2)},
                   {"9chC_4", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[3], 'f', 2)},
                   {"9chC_5", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[4], 'f', 2)},
                   {"9chC_6", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[5], 'f', 2)},
                   {"9chC_7", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[6], 'f', 2)},
                   {"9chC_8", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[7], 'f', 2)},
                   {"9passC_1", g_ADC_Card2_BitTest.test9Status[0] == 1 ? "PASS" : "FAIL"},
                   {"9passC_2", g_ADC_Card2_BitTest.test9Status[1] == 1 ? "PASS" : "FAIL"},
                   {"9passC_3", g_ADC_Card2_BitTest.test9Status[2] == 1 ? "PASS" : "FAIL"},
                   {"9passC_4", g_ADC_Card2_BitTest.test9Status[3] == 1 ? "PASS" : "FAIL"},
                   {"9passC_5", g_ADC_Card2_BitTest.test9Status[4] == 1 ? "PASS" : "FAIL"},
                   {"9passC_6", g_ADC_Card2_BitTest.test9Status[5] == 1 ? "PASS" : "FAIL"},
                   {"9passC_7", g_ADC_Card2_BitTest.test9Status[6] == 1 ? "PASS" : "FAIL"},
                   {"9passC_8", g_ADC_Card2_BitTest.test9Status[7] == 1 ? "PASS" : "FAIL"},
                   {"Exter_CCksum", formatted},
                   {"Exter_CCksum_2", formatted2},
                   {"ExtFlash_Result", ext_flash_crc},
                   {"ExtFlash_Result_2", ext_flash_crc2},
                   {"D_ObsOFF_C1", SRU_Dis_out1},
                   {"D_ObsOFF_C2", SRU_Dis_out2},
                   {"D_ObsOFF_C3", SRU_Dis_out3},
                   {"D_ObsOFF_C4", SRU_Dis_out4},
                   {"D_ObsOFF_C5", SRU_Dis_out5},
                   {"Ob_PrepOFF", SRU_Prep_OFF},
                   {"Ob_ReadyIOFF", SRU_ReadyI_OFF},
                   {"Ob_AbortOFF", SRU_Abort_OFF},
                   {"ObsOff_ch1", SRU_Dis_In1},
                   {"ObsOff_ch2", SRU_Dis_In2},
                   {"ObsOff_ch3", SRU_Dis_In3}

        };

    QString ControllerCard = ReportTemplates::populateTemplate(ReportTemplates::cntrl_cards(),
                                                               cntrl_card);

    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString pdfPath = cntrller + "/Controller Module_Report" + timestamp + ".pdf";

    ReportGenerator gen;
    gen.generateReport(ControllerCard, pdfPath);

    QMessageBox::information(this,
                             "Success",
                             "Controller Report generated successfully:\n" + pdfPath);
    ui->SRU_CntrlCard_Report->setStyleSheet(GBC);
    ui->SRU_CntrlCard_Report->setChecked(false);
}

void MainWindow::FTU_LRU_Checks()
{
    QString lru = QFileDialog::getExistingDirectory(this, "Select Output Directory");

    if (lru.isEmpty())
        return;

    QString currentDate = QDate::currentDate().toString("dd-MM-yyyy");
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString number = "0x" + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0');
    QString::number(Inputs, 16);
    QMap<QString, QString> LRU_IF_params{
        {"DD-MM-YYYY", currentDate},
        {"HH:MM:SEC", currentTime},
        {"Fsl_no", ui->FTU_LRU_SL_NO_le->text()},
        {"tester_name", ui->bit_test_tester_name_le->text()},
        {"TESTED_BY", ui->bit_test_testedby_name->text()},
        {"ATE_SLNO", "1"},
        {"Remarks", ui->BT_Remarks->text()},
        {"internal_c",
         QString("0x%1").arg(g_CRC_BIT_TEST.InternalFlash_CRC, 4, 16, QLatin1Char('0')).toUpper()},
        {"external_c",
         QString("0x%1").arg(g_CRC_BIT_TEST.ExternalFlash_CRC, 4, 16, QLatin1Char('0')).toUpper()},
        {"ATE_c", number},
        {"vol_obs", ui->LRU_VoltageLE->text()},
        {"current", QString::number(g_CurrentSensorData.curr_PS7, 'f', 4)},
        {"ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[0], 'f', 2)},
        {"ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[1], 'f', 2)},
        {"ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[2], 'f', 2)},
        {"ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[3], 'f', 2)},
        {"ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[4], 'f', 2)},
        {"ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[5], 'f', 2)},
        {"ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[6], 'f', 2)},
        {"ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[7], 'f', 2)},
        {"r_c1", g_ADC_Card2_BitTest.test1Status[0] == 1 ? "PASS" : "FAIL"},
        {"r_c2", g_ADC_Card2_BitTest.test1Status[1] == 1 ? "PASS" : "FAIL"},
        {"r_c3", g_ADC_Card2_BitTest.test1Status[2] == 1 ? "PASS" : "FAIL"},
        {"r_c4", g_ADC_Card2_BitTest.test1Status[3] == 1 ? "PASS" : "FAIL"},
        {"r_c5", g_ADC_Card2_BitTest.test1Status[4] == 1 ? "PASS" : "FAIL"},
        {"r_c6", g_ADC_Card2_BitTest.test1Status[5] == 1 ? "PASS" : "FAIL"},
        {"r_c7", g_ADC_Card2_BitTest.test1Status[6] == 1 ? "PASS" : "FAIL"},
        {"r_c8", g_ADC_Card2_BitTest.test1Status[7] == 1 ? "PASS" : "FAIL"},
        {"2ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[0], 'f', 2)},
        {"2ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[1], 'f', 2)},
        {"2ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[2], 'f', 2)},
        {"2ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[3], 'f', 2)},
        {"2ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[4], 'f', 2)},
        {"2ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[5], 'f', 2)},
        {"2ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[6], 'f', 2)},
        {"2ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[7], 'f', 2)},
        {"2r_c1", g_ADC_Card2_BitTest.test2Status[0] == 1 ? "PASS" : "FAIL"},
        {"2r_c2", g_ADC_Card2_BitTest.test2Status[1] == 1 ? "PASS" : "FAIL"},
        {"2r_c3", g_ADC_Card2_BitTest.test2Status[2] == 1 ? "PASS" : "FAIL"},
        {"2r_c4", g_ADC_Card2_BitTest.test2Status[3] == 1 ? "PASS" : "FAIL"},
        {"2r_c5", g_ADC_Card2_BitTest.test2Status[4] == 1 ? "PASS" : "FAIL"},
        {"2r_c6", g_ADC_Card2_BitTest.test2Status[5] == 1 ? "PASS" : "FAIL"},
        {"2r_c7", g_ADC_Card2_BitTest.test2Status[6] == 1 ? "PASS" : "FAIL"},
        {"2r_c8", g_ADC_Card2_BitTest.test2Status[7] == 1 ? "PASS" : "FAIL"},
        {"3ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[0], 'f', 2)},
        {"3ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[1], 'f', 2)},
        {"3ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[2], 'f', 2)},
        {"3ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[3], 'f', 2)},
        {"3ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[4], 'f', 2)},
        {"3ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[5], 'f', 2)},
        {"3ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[6], 'f', 2)},
        {"3ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[7], 'f', 2)},
        {"3r_c1", g_ADC_Card2_BitTest.test3Status[0] == 1 ? "PASS" : "FAIL"},
        {"3r_c2", g_ADC_Card2_BitTest.test3Status[1] == 1 ? "PASS" : "FAIL"},
        {"3r_c3", g_ADC_Card2_BitTest.test3Status[2] == 1 ? "PASS" : "FAIL"},
        {"3r_c4", g_ADC_Card2_BitTest.test3Status[3] == 1 ? "PASS" : "FAIL"},
        {"3r_c5", g_ADC_Card2_BitTest.test3Status[4] == 1 ? "PASS" : "FAIL"},
        {"3r_c6", g_ADC_Card2_BitTest.test3Status[5] == 1 ? "PASS" : "FAIL"},
        {"3r_c7", g_ADC_Card2_BitTest.test3Status[6] == 1 ? "PASS" : "FAIL"},
        {"3r_c8", g_ADC_Card2_BitTest.test3Status[7] == 1 ? "PASS" : "FAIL"},
        {"4ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[0], 'f', 2)},
        {"4ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[1], 'f', 2)},
        {"4ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[2], 'f', 2)},
        {"4ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[3], 'f', 2)},
        {"4ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[4], 'f', 2)},
        {"4ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[5], 'f', 2)},
        {"4ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[6], 'f', 2)},
        {"4ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[7], 'f', 2)},
        {"4r_c1", g_ADC_Card2_BitTest.test4Status[0] == 1 ? "PASS" : "FAIL"},
        {"4r_c2", g_ADC_Card2_BitTest.test4Status[1] == 1 ? "PASS" : "FAIL"},
        {"4r_c3", g_ADC_Card2_BitTest.test4Status[2] == 1 ? "PASS" : "FAIL"},
        {"4r_c4", g_ADC_Card2_BitTest.test4Status[3] == 1 ? "PASS" : "FAIL"},
        {"4r_c5", g_ADC_Card2_BitTest.test4Status[4] == 1 ? "PASS" : "FAIL"},
        {"4r_c6", g_ADC_Card2_BitTest.test4Status[5] == 1 ? "PASS" : "FAIL"},
        {"4r_c7", g_ADC_Card2_BitTest.test4Status[6] == 1 ? "PASS" : "FAIL"},
        {"4r_c8", g_ADC_Card2_BitTest.test4Status[7] == 1 ? "PASS" : "FAIL"},
        {"5ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[0], 'f', 2)},
        {"5ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[1], 'f', 2)},
        {"5ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[2], 'f', 2)},
        {"5ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[3], 'f', 2)},
        {"5ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[4], 'f', 2)},
        {"5ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[5], 'f', 2)},
        {"5ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[6], 'f', 2)},
        {"5ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[7], 'f', 2)},
        {"5r_c1", g_ADC_Card2_BitTest.test5Status[0] == 1 ? "PASS" : "FAIL"},
        {"5r_c2", g_ADC_Card2_BitTest.test5Status[1] == 1 ? "PASS" : "FAIL"},
        {"5r_c3", g_ADC_Card2_BitTest.test5Status[2] == 1 ? "PASS" : "FAIL"},
        {"5r_c4", g_ADC_Card2_BitTest.test5Status[3] == 1 ? "PASS" : "FAIL"},
        {"5r_c5", g_ADC_Card2_BitTest.test5Status[4] == 1 ? "PASS" : "FAIL"},
        {"5r_c6", g_ADC_Card2_BitTest.test5Status[5] == 1 ? "PASS" : "FAIL"},
        {"5r_c7", g_ADC_Card2_BitTest.test5Status[6] == 1 ? "PASS" : "FAIL"},
        {"5r_c8", g_ADC_Card2_BitTest.test5Status[7] == 1 ? "PASS" : "FAIL"},
        {"6ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[0], 'f', 2)},
        {"6ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[1], 'f', 2)},
        {"6ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[2], 'f', 2)},
        {"6ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[3], 'f', 2)},
        {"6ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[4], 'f', 2)},
        {"6ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[5], 'f', 2)},
        {"6ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[6], 'f', 2)},
        {"6ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[7], 'f', 2)},
        {"6r_c1", g_ADC_Card2_BitTest.test6Status[0] == 1 ? "PASS" : "FAIL"},
        {"6r_c2", g_ADC_Card2_BitTest.test6Status[1] == 1 ? "PASS" : "FAIL"},
        {"6r_c3", g_ADC_Card2_BitTest.test6Status[2] == 1 ? "PASS" : "FAIL"},
        {"6r_c4", g_ADC_Card2_BitTest.test6Status[3] == 1 ? "PASS" : "FAIL"},
        {"6r_c5", g_ADC_Card2_BitTest.test6Status[4] == 1 ? "PASS" : "FAIL"},
        {"6r_c6", g_ADC_Card2_BitTest.test6Status[5] == 1 ? "PASS" : "FAIL"},
        {"6r_c7", g_ADC_Card2_BitTest.test6Status[6] == 1 ? "PASS" : "FAIL"},
        {"6r_c8", g_ADC_Card2_BitTest.test6Status[7] == 1 ? "PASS" : "FAIL"},
        {"7ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[0], 'f', 2)},
        {"7ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[1], 'f', 2)},
        {"7ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[2], 'f', 2)},
        {"7ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[3], 'f', 2)},
        {"7ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[4], 'f', 2)},
        {"7ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[5], 'f', 2)},
        {"7ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[6], 'f', 2)},
        {"7ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[7], 'f', 2)},
        {"7r_c1", g_ADC_Card2_BitTest.test7Status[0] == 1 ? "PASS" : "FAIL"},
        {"7r_c2", g_ADC_Card2_BitTest.test7Status[1] == 1 ? "PASS" : "FAIL"},
        {"7r_c3", g_ADC_Card2_BitTest.test7Status[2] == 1 ? "PASS" : "FAIL"},
        {"7r_c4", g_ADC_Card2_BitTest.test7Status[3] == 1 ? "PASS" : "FAIL"},
        {"7r_c5", g_ADC_Card2_BitTest.test7Status[4] == 1 ? "PASS" : "FAIL"},
        {"7r_c6", g_ADC_Card2_BitTest.test7Status[5] == 1 ? "PASS" : "FAIL"},
        {"7r_c7", g_ADC_Card2_BitTest.test7Status[6] == 1 ? "PASS" : "FAIL"},
        {"7r_c8", g_ADC_Card2_BitTest.test7Status[7] == 1 ? "PASS" : "FAIL"},
        {"8ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[0], 'f', 2)},
        {"8ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[1], 'f', 2)},
        {"8ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[2], 'f', 2)},
        {"8ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[3], 'f', 2)},
        {"8ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[4], 'f', 2)},
        {"8ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[5], 'f', 2)},
        {"8ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[6], 'f', 2)},
        {"8ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[7], 'f', 2)},
        {"8r_c1", g_ADC_Card2_BitTest.test8Status[0] == 1 ? "PASS" : "FAIL"},
        {"8r_c2", g_ADC_Card2_BitTest.test8Status[1] == 1 ? "PASS" : "FAIL"},
        {"8r_c3", g_ADC_Card2_BitTest.test8Status[2] == 1 ? "PASS" : "FAIL"},
        {"8r_c4", g_ADC_Card2_BitTest.test8Status[3] == 1 ? "PASS" : "FAIL"},
        {"8r_c5", g_ADC_Card2_BitTest.test8Status[4] == 1 ? "PASS" : "FAIL"},
        {"8r_c6", g_ADC_Card2_BitTest.test8Status[5] == 1 ? "PASS" : "FAIL"},
        {"8r_c7", g_ADC_Card2_BitTest.test8Status[6] == 1 ? "PASS" : "FAIL"},
        {"8r_c8", g_ADC_Card2_BitTest.test8Status[7] == 1 ? "PASS" : "FAIL"},
        {"9ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[0], 'f', 2)},
        {"9ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[1], 'f', 2)},
        {"9ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[2], 'f', 2)},
        {"9ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[3], 'f', 2)},
        {"9ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[4], 'f', 2)},
        {"9ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[5], 'f', 2)},
        {"9ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[6], 'f', 2)},
        {"9ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[7], 'f', 2)},
        {"9r_c1", g_ADC_Card2_BitTest.test9Status[0] == 1 ? "PASS" : "FAIL"},
        {"9r_c2", g_ADC_Card2_BitTest.test9Status[1] == 1 ? "PASS" : "FAIL"},
        {"9r_c3", g_ADC_Card2_BitTest.test9Status[2] == 1 ? "PASS" : "FAIL"},
        {"9r_c4", g_ADC_Card2_BitTest.test9Status[3] == 1 ? "PASS" : "FAIL"},
        {"9r_c5", g_ADC_Card2_BitTest.test9Status[4] == 1 ? "PASS" : "FAIL"},
        {"9r_c6", g_ADC_Card2_BitTest.test9Status[5] == 1 ? "PASS" : "FAIL"},
        {"9r_c7", g_ADC_Card2_BitTest.test9Status[6] == 1 ? "PASS" : "FAIL"},
        {"9r_c8", g_ADC_Card2_BitTest.test9Status[7] == 1 ? "PASS" : "FAIL"},
        {"Outval_1", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts)},
        {"D1_O_r", ui->Discrete_op_result_Ch1_le->text()},
        {"Outval_2", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts)},
        {"D2_O_r", ui->Discrete_op_result_Ch2_le->text()},
        {"Outval_3", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts)},
        {"D3_O_r", ui->Discrete_op_result_Ch3_le->text()},
        {"Outval_4", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts)},
        {"D4_O_r", ui->Discrete_op_result_Ch4_le->text()},
        {"Outval_5", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts)},
        {"D5_O_r", ui->Discrete_op_result_Ch5_le->text()},
        {"Inputval_1", QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts)},
        {"D1_I_r", ui->Discrete_Ip_result_Ch1_le->text()},
        {"Inputval_2", QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts)},
        {"D2_I_r", ui->Discrete_Ip_result_Ch2_le->text()},
        {"Inputval_3", QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts)},

        {"D3_I_r", ui->Discrete_Ip_result_Ch3_le->text()},
        {"Rotary_Status",
         QString::number(g_Momentary_Switch_Status.Rotary_Update, 10).rightJustified(3, '0')},
        {"RS_r", ui->Rotary_Update_Switch_status_le->text()},
        {"Prep_Status", QString::number(g_Momentary_Switch_Status.Prep_Status, 10)},
        {"PS_r", ui->Prep_Switch_status_le->text()},
        {"RInit_Status", QString::number(g_Momentary_Switch_Status.Ready_Init_Status, 10)},
        {"RIS_r", ui->Ready_Init_Switch_status_le->text()},
        {"Abort_Status", QString::number(g_Momentary_Switch_Status.Abort_Status, 10)},
        {"AS_r", ui->Abort_Switch_status_le->text()},
        {"Pat1_data", LRU_data},
        {"Obs_bytes_55", QString::number(l_counter)},
        {"Obs_bytes_aa", QString::number(l_counter2)},
        {"Obs_bytes", QString::number(l_counter)},
        {"EXP_checksum", "0x967E"},
        {"Obs_checksum", ObservCRC},
        {"Port_r", rs422_result}};
    QString FTU_LRUHTMl = ReportTemplates::populateTemplate(ReportTemplates::Bit_Test_Report(),
                                                            LRU_IF_params);
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString pdfPath = lru + "/BitTest_report_" + timestamp + ".pdf";

    ReportGenerator gen;
    gen.generateReport(FTU_LRUHTMl, pdfPath);
    QMessageBox::information(this, "Success", "BIT TEST Report generated successfully:\n" + pdfPath);
    ui->FTU_BitTest_Report->setStyleSheet(GBC);
    ui->FTU_BitTest_Report->setChecked(false);
}

void MainWindow::FTULRU_Report()
{
    {
        QString FTU_lru = QFileDialog::getExistingDirectory(this, "Select Output Directory");

        if (FTU_lru.isEmpty())
            return;

        QString currentDate = QDate::currentDate().toString("dd-MM-yyyy");
        QString currentTime = QTime::currentTime().toString("hh:mm:ss");
        QString number = "0x" + QString::number(guiCRC_ATE, 16).toUpper().rightJustified(4, '0');
        QString::number(Inputs, 16);
        QMap<QString, QString> FTULRU_IF_params{
            {"DD-MM-YYYY", currentDate},
            {"HH:MM:SEC", currentTime},
            {"Fsl_no", ui->FTU_LRU_SL_NO_le->text()},
            {"tester_name", ui->bit_test_tester_name_le->text()},
            {"TESTED_BY", ui->bit_test_testedby_name->text()},
            {"ATE_SLNO", "1"},
            {"Remarks", ui->BT_Remarks->text()},
            {"internal_c",
             QString("0x%1").arg(g_CRC_BIT_TEST.InternalFlash_CRC, 4, 16, QLatin1Char('0')).toUpper()},
            {"external_c",
             QString("0x%1").arg(g_CRC_BIT_TEST.ExternalFlash_CRC, 4, 16, QLatin1Char('0')).toUpper()},
            {"ATE_c", number},
            {"vol_obs", ui->LRU_VoltageLE->text()},
            {"current", QString::number(g_CurrentSensorData.curr_PS7, 'f', 4)},
            {"ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[0], 'f', 2)},
            {"ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[1], 'f', 2)},
            {"ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[2], 'f', 2)},
            {"ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[3], 'f', 2)},
            {"ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[4], 'f', 2)},
            {"ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[5], 'f', 2)},
            {"ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[6], 'f', 2)},
            {"ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test1[7], 'f', 2)},
            {"r_c1", g_ADC_Card2_BitTest.test1Status[0] == 1 ? "PASS" : "FAIL"},
            {"r_c2", g_ADC_Card2_BitTest.test1Status[1] == 1 ? "PASS" : "FAIL"},
            {"r_c3", g_ADC_Card2_BitTest.test1Status[2] == 1 ? "PASS" : "FAIL"},
            {"r_c4", g_ADC_Card2_BitTest.test1Status[3] == 1 ? "PASS" : "FAIL"},
            {"r_c5", g_ADC_Card2_BitTest.test1Status[4] == 1 ? "PASS" : "FAIL"},
            {"r_c6", g_ADC_Card2_BitTest.test1Status[5] == 1 ? "PASS" : "FAIL"},
            {"r_c7", g_ADC_Card2_BitTest.test1Status[6] == 1 ? "PASS" : "FAIL"},
            {"r_c8", g_ADC_Card2_BitTest.test1Status[7] == 1 ? "PASS" : "FAIL"},
            {"2ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[0], 'f', 2)},
            {"2ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[1], 'f', 2)},
            {"2ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[2], 'f', 2)},
            {"2ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[3], 'f', 2)},
            {"2ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[4], 'f', 2)},
            {"2ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[5], 'f', 2)},
            {"2ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[6], 'f', 2)},
            {"2ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test2[7], 'f', 2)},
            {"2r_c1", g_ADC_Card2_BitTest.test2Status[0] == 1 ? "PASS" : "FAIL"},
            {"2r_c2", g_ADC_Card2_BitTest.test2Status[1] == 1 ? "PASS" : "FAIL"},
            {"2r_c3", g_ADC_Card2_BitTest.test2Status[2] == 1 ? "PASS" : "FAIL"},
            {"2r_c4", g_ADC_Card2_BitTest.test2Status[3] == 1 ? "PASS" : "FAIL"},
            {"2r_c5", g_ADC_Card2_BitTest.test2Status[4] == 1 ? "PASS" : "FAIL"},
            {"2r_c6", g_ADC_Card2_BitTest.test2Status[5] == 1 ? "PASS" : "FAIL"},
            {"2r_c7", g_ADC_Card2_BitTest.test2Status[6] == 1 ? "PASS" : "FAIL"},
            {"2r_c8", g_ADC_Card2_BitTest.test2Status[7] == 1 ? "PASS" : "FAIL"},
            {"3ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[0], 'f', 2)},
            {"3ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[1], 'f', 2)},
            {"3ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[2], 'f', 2)},
            {"3ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[3], 'f', 2)},
            {"3ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[4], 'f', 2)},
            {"3ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[5], 'f', 2)},
            {"3ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[6], 'f', 2)},
            {"3ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test3[7], 'f', 2)},
            {"3r_c1", g_ADC_Card2_BitTest.test3Status[0] == 1 ? "PASS" : "FAIL"},
            {"3r_c2", g_ADC_Card2_BitTest.test3Status[1] == 1 ? "PASS" : "FAIL"},
            {"3r_c3", g_ADC_Card2_BitTest.test3Status[2] == 1 ? "PASS" : "FAIL"},
            {"3r_c4", g_ADC_Card2_BitTest.test3Status[3] == 1 ? "PASS" : "FAIL"},
            {"3r_c5", g_ADC_Card2_BitTest.test3Status[4] == 1 ? "PASS" : "FAIL"},
            {"3r_c6", g_ADC_Card2_BitTest.test3Status[5] == 1 ? "PASS" : "FAIL"},
            {"3r_c7", g_ADC_Card2_BitTest.test3Status[6] == 1 ? "PASS" : "FAIL"},
            {"3r_c8", g_ADC_Card2_BitTest.test3Status[7] == 1 ? "PASS" : "FAIL"},
            {"4ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[0], 'f', 2)},
            {"4ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[1], 'f', 2)},
            {"4ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[2], 'f', 2)},
            {"4ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[3], 'f', 2)},
            {"4ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[4], 'f', 2)},
            {"4ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[5], 'f', 2)},
            {"4ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[6], 'f', 2)},
            {"4ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test4[7], 'f', 2)},
            {"4r_c1", g_ADC_Card2_BitTest.test4Status[0] == 1 ? "PASS" : "FAIL"},
            {"4r_c2", g_ADC_Card2_BitTest.test4Status[1] == 1 ? "PASS" : "FAIL"},
            {"4r_c3", g_ADC_Card2_BitTest.test4Status[2] == 1 ? "PASS" : "FAIL"},
            {"4r_c4", g_ADC_Card2_BitTest.test4Status[3] == 1 ? "PASS" : "FAIL"},
            {"4r_c5", g_ADC_Card2_BitTest.test4Status[4] == 1 ? "PASS" : "FAIL"},
            {"4r_c6", g_ADC_Card2_BitTest.test4Status[5] == 1 ? "PASS" : "FAIL"},
            {"4r_c7", g_ADC_Card2_BitTest.test4Status[6] == 1 ? "PASS" : "FAIL"},
            {"4r_c8", g_ADC_Card2_BitTest.test4Status[7] == 1 ? "PASS" : "FAIL"},
            {"5ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[0], 'f', 2)},
            {"5ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[1], 'f', 2)},
            {"5ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[2], 'f', 2)},
            {"5ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[3], 'f', 2)},
            {"5ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[4], 'f', 2)},
            {"5ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[5], 'f', 2)},
            {"5ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[6], 'f', 2)},
            {"5ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test5[7], 'f', 2)},
            {"5r_c1", g_ADC_Card2_BitTest.test5Status[0] == 1 ? "PASS" : "FAIL"},
            {"5r_c2", g_ADC_Card2_BitTest.test5Status[1] == 1 ? "PASS" : "FAIL"},
            {"5r_c3", g_ADC_Card2_BitTest.test5Status[2] == 1 ? "PASS" : "FAIL"},
            {"5r_c4", g_ADC_Card2_BitTest.test5Status[3] == 1 ? "PASS" : "FAIL"},
            {"5r_c5", g_ADC_Card2_BitTest.test5Status[4] == 1 ? "PASS" : "FAIL"},
            {"5r_c6", g_ADC_Card2_BitTest.test5Status[5] == 1 ? "PASS" : "FAIL"},
            {"5r_c7", g_ADC_Card2_BitTest.test5Status[6] == 1 ? "PASS" : "FAIL"},
            {"5r_c8", g_ADC_Card2_BitTest.test5Status[7] == 1 ? "PASS" : "FAIL"},
            {"6ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[0], 'f', 2)},
            {"6ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[1], 'f', 2)},
            {"6ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[2], 'f', 2)},
            {"6ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[3], 'f', 2)},
            {"6ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[4], 'f', 2)},
            {"6ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[5], 'f', 2)},
            {"6ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[6], 'f', 2)},
            {"6ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test6[7], 'f', 2)},
            {"6r_c1", g_ADC_Card2_BitTest.test6Status[0] == 1 ? "PASS" : "FAIL"},
            {"6r_c2", g_ADC_Card2_BitTest.test6Status[1] == 1 ? "PASS" : "FAIL"},
            {"6r_c3", g_ADC_Card2_BitTest.test6Status[2] == 1 ? "PASS" : "FAIL"},
            {"6r_c4", g_ADC_Card2_BitTest.test6Status[3] == 1 ? "PASS" : "FAIL"},
            {"6r_c5", g_ADC_Card2_BitTest.test6Status[4] == 1 ? "PASS" : "FAIL"},
            {"6r_c6", g_ADC_Card2_BitTest.test6Status[5] == 1 ? "PASS" : "FAIL"},
            {"6r_c7", g_ADC_Card2_BitTest.test6Status[6] == 1 ? "PASS" : "FAIL"},
            {"6r_c8", g_ADC_Card2_BitTest.test6Status[7] == 1 ? "PASS" : "FAIL"},
            {"7ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[0], 'f', 2)},
            {"7ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[1], 'f', 2)},
            {"7ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[2], 'f', 2)},
            {"7ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[3], 'f', 2)},
            {"7ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[4], 'f', 2)},
            {"7ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[5], 'f', 2)},
            {"7ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[6], 'f', 2)},
            {"7ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test7[7], 'f', 2)},
            {"7r_c1", g_ADC_Card2_BitTest.test7Status[0] == 1 ? "PASS" : "FAIL"},
            {"7r_c2", g_ADC_Card2_BitTest.test7Status[1] == 1 ? "PASS" : "FAIL"},
            {"7r_c3", g_ADC_Card2_BitTest.test7Status[2] == 1 ? "PASS" : "FAIL"},
            {"7r_c4", g_ADC_Card2_BitTest.test7Status[3] == 1 ? "PASS" : "FAIL"},
            {"7r_c5", g_ADC_Card2_BitTest.test7Status[4] == 1 ? "PASS" : "FAIL"},
            {"7r_c6", g_ADC_Card2_BitTest.test7Status[5] == 1 ? "PASS" : "FAIL"},
            {"7r_c7", g_ADC_Card2_BitTest.test7Status[6] == 1 ? "PASS" : "FAIL"},
            {"7r_c8", g_ADC_Card2_BitTest.test7Status[7] == 1 ? "PASS" : "FAIL"},
            {"8ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[0], 'f', 2)},
            {"8ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[1], 'f', 2)},
            {"8ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[2], 'f', 2)},
            {"8ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[3], 'f', 2)},
            {"8ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[4], 'f', 2)},
            {"8ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[5], 'f', 2)},
            {"8ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[6], 'f', 2)},
            {"8ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test8[7], 'f', 2)},
            {"8r_c1", g_ADC_Card2_BitTest.test8Status[0] == 1 ? "PASS" : "FAIL"},
            {"8r_c2", g_ADC_Card2_BitTest.test8Status[1] == 1 ? "PASS" : "FAIL"},
            {"8r_c3", g_ADC_Card2_BitTest.test8Status[2] == 1 ? "PASS" : "FAIL"},
            {"8r_c4", g_ADC_Card2_BitTest.test8Status[3] == 1 ? "PASS" : "FAIL"},
            {"8r_c5", g_ADC_Card2_BitTest.test8Status[4] == 1 ? "PASS" : "FAIL"},
            {"8r_c6", g_ADC_Card2_BitTest.test8Status[5] == 1 ? "PASS" : "FAIL"},
            {"8r_c7", g_ADC_Card2_BitTest.test8Status[6] == 1 ? "PASS" : "FAIL"},
            {"8r_c8", g_ADC_Card2_BitTest.test8Status[7] == 1 ? "PASS" : "FAIL"},
            {"9ch1", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[0], 'f', 2)},
            {"9ch2", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[1], 'f', 2)},
            {"9ch3", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[2], 'f', 2)},
            {"9ch4", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[3], 'f', 2)},
            {"9ch5", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[4], 'f', 2)},
            {"9ch6", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[5], 'f', 2)},
            {"9ch7", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[6], 'f', 2)},
            {"9ch8", QString::number(g_ADC_Card2_BitTest.averagedAi_test9[7], 'f', 2)},
            {"9r_c1", g_ADC_Card2_BitTest.test9Status[0] == 1 ? "PASS" : "FAIL"},
            {"9r_c2", g_ADC_Card2_BitTest.test9Status[1] == 1 ? "PASS" : "FAIL"},
            {"9r_c3", g_ADC_Card2_BitTest.test9Status[2] == 1 ? "PASS" : "FAIL"},
            {"9r_c4", g_ADC_Card2_BitTest.test9Status[3] == 1 ? "PASS" : "FAIL"},
            {"9r_c5", g_ADC_Card2_BitTest.test9Status[4] == 1 ? "PASS" : "FAIL"},
            {"9r_c6", g_ADC_Card2_BitTest.test9Status[5] == 1 ? "PASS" : "FAIL"},
            {"9r_c7", g_ADC_Card2_BitTest.test9Status[6] == 1 ? "PASS" : "FAIL"},
            {"9r_c8", g_ADC_Card2_BitTest.test9Status[7] == 1 ? "PASS" : "FAIL"},
            {"Outval_1", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts)},
            {"D1_O_r", ui->Discrete_op_result_Ch1_le->text()},
            {"Outval_2", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts)},
            {"D2_O_r", ui->Discrete_op_result_Ch2_le->text()},
            {"Outval_3", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts)},
            {"D3_O_r", ui->Discrete_op_result_Ch3_le->text()},
            {"Outval_4", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts)},
            {"D4_O_r", ui->Discrete_op_result_Ch4_le->text()},
            {"Outval_5", QString::number(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts)},
            {"D5_O_r", ui->Discrete_op_result_Ch5_le->text()},
            {"Inputval_1", QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts)},
            {"D1_I_r", ui->Discrete_Ip_result_Ch1_le->text()},
            {"Inputval_2", QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts)},
            {"D2_I_r", ui->Discrete_Ip_result_Ch2_le->text()},
            {"Inputval_3", QString::number(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts)},

            {"D3_I_r", ui->Discrete_Ip_result_Ch3_le->text()},
            {"Rotary_Status",
             QString::number(g_Momentary_Switch_Status.Rotary_Update, 10).rightJustified(3, '0')},
            {"RS_r", ui->Rotary_Update_Switch_status_le->text()},
            {"Prep_Status", QString::number(g_Momentary_Switch_Status.Prep_Status, 10)},
            {"PS_r", ui->Prep_Switch_status_le->text()},
            {"RInit_Status", QString::number(g_Momentary_Switch_Status.Ready_Init_Status, 10)},
            {"RIS_r", ui->Ready_Init_Switch_status_le->text()},
            {"Abort_Status", QString::number(g_Momentary_Switch_Status.Abort_Status, 10)},
            {"AS_r", ui->Abort_Switch_status_le->text()},
            {"Pat1_data", LRU_data},
            {"Obs_bytes_55", QString::number(l_counter)},
            {"Obs_bytes_aa", QString::number(l_counter2)},
            {"USB_cksum1", Bit_usb_data},
            {"USBPat1_data", formattedUSBPat1},
            {"USB_cksum2", Bit_usb_data1},
            {"USBPat2_data", formattedUSBPat2},
            {"USB_R1", l_Usb_p1},
            {"USB_R2", l_Usb_p2},
            {"EXP_checksum", "0x967E"},
            {"Obs_checksum", ObservCRC},
            {"Port_r", rs422_result}};
        QString FTU_LRU = ReportTemplates::populateTemplate(ReportTemplates::LRU_Test_Report(),
                                                            FTULRU_IF_params);
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
        QString pdfPath = FTU_lru + "/LRU_Test_Report_" + timestamp + ".pdf";

        ReportGenerator gen;
        gen.generateReport(FTU_LRU, pdfPath);
        QMessageBox::information(this,
                                 "Success",
                                 "LRU TEST Report generated successfully:\n" + pdfPath);
        ui->FTU_BitTest_Report->setStyleSheet(GBC);
        ui->FTU_BitTest_Report->setChecked(false);
    }
}

//void MainWindow::handleSerialMessage(const QByteArray &message)
//{
//    //    qDebug() << "Received:" << message;
//    //   ui->textEdit->append("Received: " + message);
//}

void MainWindow::handleSerialError(QSerialPort::SerialPortError error)
{
    //    qDebug() << "Serial Error:" << error;
    QMessageBox::warning(this, "Serial Error", QString("Error: %1").arg(error));
}

void MainWindow::handleSerialClose()
{
    //    qDebug() << "Serial Port Closing";
    QMessageBox::information(this, "Serial Port", "Serial port is closing.");
}

void MainWindow::onSerialDataReceived(const QByteArray &data)
{
    //    qDebug() << "Received from serial:" << data;

    if (!data.startsWith(0x24)) {
        //        qDebug() << "⚠️ Garbage received (no start byte):" << data.toHex(' ');
        return;
    }
    if (!data.endsWith(QByteArray::fromHex("3B23"))) {
        //        qDebug() << "⚠️ Incomplete/invalid frame:" << data.toHex(' ');
        return;
    }
    // Process valid data
    //    qDebug() << "✅ Received valid data:" << data.toHex(' ').toUpper();
}

void MainWindow::on_pushButton_clicked()
{
    // advInterface->logSelfTestText("Button clicked — log from AdvInterface");
    // Log directly from MainWindow
    Logger::instance()->logText("Button clicked — log from MainWindow");
}
void MainWindow::on_RS422_LOOP_BACK_pb_1_clicked(bool checked)
{
    Logger::instance()->logText(
        QString("-----RS422_LOOP_BACK_pb_1 toggled: %1-----------").arg(checked ? "ON" : "OFF"));
    if (checked) {
        ui->RS422_LOOP_BACK_pb_1->setStyleSheet(YBC); /*YELLOW*/
                                                      //        g_initiate_sequence_counter = 6;

        QThread::msleep(500);
        // data1 = QByteArray::fromHex("24 9 8 7 6 5 4 3 2 1 0 3B 23");
        g_Moxa_port1.StartMsg = 0x24;
        g_Moxa_port1.MsgID = MOXA_Tx_1_RX_2;
        g_Moxa_port1.packetSize = sizeof(Moxa_port);
        for (int i = 0; i < 128; i++) {
            g_Moxa_port1.data[i] = 0xA5A5;
        }
        g_Moxa_port1.CRC_WORD = 0;
        g_Moxa_port1.EndMsg = 0x233B;
        g_Moxa_port1.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port1, sizeof(Moxa_port));
        emit Moxa_Port1_serialWrite((char *) &g_Moxa_port1, sizeof(Moxa_port));
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        //        qDebug() << "[TX] Time:" << ch1_tx;
        Logger::instance()->logText(QString("[TX] Time: %1").arg(time));
        QByteArray rawData(reinterpret_cast<const char *>(&g_Moxa_port1), sizeof(Moxa_port));
        ch1_tx = rawData.toHex(' ').toUpper() + " TS " + time;
        //        qDebug() << "timestamp data" << hexString1;
        // ui->RS422_LOOP_BACK_le1->setText(hexString);

        Logger::instance()->logText(QString("[TX] Data: %1").arg(hexString1));

        QTimer::singleShot(1000, this, [this]() {
            if (rs422_r1 != "PASS") {
                rs422_r1 = "FAIL";
                ui->RS422_LOOP_BACK_le1->setText("FAIL");
                ui->RS422_LOOP_BACK_le1->setStyleSheet("color: red ");
                ui->RS422_LOOP_BACK_pb_1->setStyleSheet(RBC);
                ui->RS422_LOOP_BACK_pb_1->setChecked(false);

                Logger::instance()->logText("[FAIL] RS422 CH1->CH2 loopback failed (timeout)");

                if (g_mode_flag == AUTOMATIC_MODE) {
                    g_step_in_progress = false;
                    QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
                }
            }
        });
    }
}

void MainWindow::on_RS422_LOOP_BACK_pb_2_clicked(bool checked)
{
    Logger::instance()->logText(
        QString("---------RS422_LOOP_BACK_pb_2 toggled: %1-------").arg(checked ? "ON" : "OFF"));

    if (checked) {
        //        g_initiate_sequence_counter = 7;
        ui->RS422_LOOP_BACK_pb_2->setStyleSheet(YBC); /*YELLOW*/
        // g_AdvantechCardsInterface->Rs422_CH1_CH2_ON_card3_5856();

        QThread::msleep(500);
        g_Moxa_port2.StartMsg = 0x24;
        g_Moxa_port2.MsgID = MOXA_Tx_2_RX_1;
        g_Moxa_port2.packetSize = sizeof(Moxa_port);
        for (int i = 0; i < 128; i++) {
            g_Moxa_port2.data[i] = 0xF5F5;
        }
        g_Moxa_port2.CRC_WORD = 0;
        g_Moxa_port2.EndMsg = 0x233B;
        g_Moxa_port2.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port2, sizeof(Moxa_port));
        emit Moxa_Port2_serialWrite((char *) &g_Moxa_port2, sizeof(Moxa_port));
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        //        qDebug() << "[TX] Time:" << ch2_tx;
        Logger::instance()->logText(QString("[TX] Time: %1").arg(time));
        QByteArray rawData(reinterpret_cast<const char *>(&g_Moxa_port2), sizeof(Moxa_port));
        ch2_tx = rawData.toHex(' ').toUpper() + " TS " + time;
        //        qDebug() << "timestamp data" << hexString2;
        //ui->RS422_LOOP_BACK_le2->setText(hexString);
        Logger::instance()->logText(QString("[TX] Data: %1").arg(hexString2));

        Logger::instance()->logText("[PASS] RS422 Loopback on COM6 successful");
    }
    QTimer::singleShot(1000, this, [this]() {
        if (rs422_r2 != "PASS") {
            rs422_r2 = "FAIL";
            ui->RS422_LOOP_BACK_le2->setText("FAIL");
            ui->RS422_LOOP_BACK_le2->setStyleSheet("color: red;");
            ui->RS422_LOOP_BACK_pb_2->setStyleSheet(RBC);
            ui->RS422_LOOP_BACK_pb_2->setChecked(false);

            Logger::instance()->logText("[FAIL] RS422 CH2->CH1 loopback failed (timeout)");

            if (g_mode_flag == AUTOMATIC_MODE) {
                g_step_in_progress = false;
                QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
            }
        }
    });
}

void MainWindow::SelfTest_StatusUpdate()
{
    // R1 = "";
    if (g_SelfTestStatus.USB_5856_Card1_STS) {
        uint64_t outputs = 0;
        uint32_t Inputs = 0;
        g_SelfTestStatus.USB_5856_Card1_STS = 0;
        memcpy(&outputs, &Output_5856_Card_1, sizeof(Output_5856_Card_1));
        memcpy(&Inputs, &Input_5856_Card_1, sizeof(Input_5856_Card_1));

        ui->USB_5856_output1_Card1_le->setText(QString::number(outputs, 16).toUpper());
        ui->USB_5856_input1_Card1_le->setText(QString::number(Inputs, 16).toUpper());

        //        qDebug() << "card1output" << QString::number(outputs, 16);
        //        qDebug() << "card1Inputs" << QString::number(Inputs, 16);
        memset(&Output_5856_Card_1, 0, sizeof(Output_5856_Card_1));
        memset(&Input_5856_Card_1, 0, sizeof(Input_5856_Card_1));

        if ((outputs == 0x13bdedd) && (Inputs == 0x5)) {
            R1 = "PASS";
            ui->USB_5856_AE_Card1_pb->setStyleSheet(GBC);
            ui->USB_5856_AE_Card1_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(false);
            ui->USB_5856_AE_Card2_pb->setEnabled(true);
            ui->USB_5856_AE_Card3_pb->setEnabled(false);
            ui->USB_5856_AE_Card4_pb->setEnabled(false);
        } else {
            R1 = "FAIL";
            ui->USB_5856_AE_Card1_pb->setStyleSheet(RBC);
            ui->USB_5856_AE_Card1_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(false);
            ui->USB_5856_AE_Card2_pb->setEnabled(true);
            ui->USB_5856_AE_Card3_pb->setEnabled(false);
            ui->USB_5856_AE_Card4_pb->setEnabled(false);
        }
        if (g_mode_flag == AUTOMATIC_MODE)
            QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
    }

    if (g_SelfTestStatus.USB_5856_Card2_STS) {
        uint64_t outputs = 0;
        uint32_t Inputs = 0;
        g_SelfTestStatus.USB_5856_Card2_STS = 0;
        memcpy(&outputs, &Output_5856_Card_2, sizeof(Output_5856_Card_2));
        memcpy(&Inputs, &Input_5856_Card_2, sizeof(Input_5856_Card_2));
        //        qDebug() << "card2outputs" << QString::number(outputs, 16);
        //        qDebug() << "card2Inputs" << QString::number(Inputs, 16);

        ui->USB_5856_output2_Card2_le->setText(QString::number(outputs, 16).toUpper());
        ui->USB_5856_input2_Card2_le->setText(QString::number(Inputs, 16).toUpper());

        memset(&Output_5856_Card_2, 0, sizeof(Output_5856_Card_2));
        memset(&Input_5856_Card_2, 0, sizeof(Input_5856_Card_2));

        if ((outputs == 0x3FFFF3FF) && (Inputs == 0x3FFFF3FF)) {
            R2 = "PASS";
            ui->USB_5856_AE_Card2_pb->setStyleSheet(GBC);
            ui->USB_5856_AE_Card2_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(false);
            ui->USB_5856_AE_Card2_pb->setEnabled(false);
            ui->USB_5856_AE_Card3_pb->setEnabled(true);
            ui->USB_5856_AE_Card4_pb->setEnabled(false);
        } else {
            R2 = "FAIL";
            ui->USB_5856_AE_Card2_pb->setStyleSheet(RBC);
            ui->USB_5856_AE_Card2_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(false);
            ui->USB_5856_AE_Card2_pb->setEnabled(false);
            ui->USB_5856_AE_Card3_pb->setEnabled(true);
            ui->USB_5856_AE_Card4_pb->setEnabled(false);
        }
        if (g_mode_flag == AUTOMATIC_MODE)
            QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
    }

    if (g_SelfTestStatus.USB_5856_Card3_STS) {
        uint64_t outputs = 0;
        uint32_t Inputs = 0;
        g_SelfTestStatus.USB_5856_Card3_STS = 0;
        memcpy(&outputs, &Output_5856_Card_3, sizeof(Output_5856_Card_3));
        memcpy(&Inputs, &Input_5856_Card_3, sizeof(Input_5856_Card_3));

        ui->USB_5856_output3_Card3_le->setText(QString::number(outputs, 16).toUpper());
        ui->USB_5856_input3_Card3_le->setText(QString::number(Inputs, 16).toUpper());

        //        qDebug() << "card3outputs" << QString::number(outputs, 16);
        //        qDebug() << "card3Inputs" << QString::number(Inputs, 16);
        memset(&Output_5856_Card_3, 0, sizeof(Output_5856_Card_3));
        memset(&Input_5856_Card_3, 0, sizeof(Input_5856_Card_3));

        if ((outputs == 0x3FFFFFFF) && (Inputs == 0x3FFFFFFF)) {
            R3 = "PASS";

            ui->USB_5856_AE_Card3_pb->setStyleSheet(GBC);
            ui->USB_5856_AE_Card3_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(false);
            ui->USB_5856_AE_Card2_pb->setEnabled(false);
            ui->USB_5856_AE_Card3_pb->setEnabled(false);
            ui->USB_5856_AE_Card4_pb->setEnabled(true);

        } else {
            R3 = "FAIL";
            ui->USB_5856_AE_Card3_pb->setStyleSheet(RBC);
            ui->USB_5856_AE_Card3_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(false);
            ui->USB_5856_AE_Card2_pb->setEnabled(false);
            ui->USB_5856_AE_Card3_pb->setEnabled(false);
            ui->USB_5856_AE_Card4_pb->setEnabled(true);
        }
        if (g_mode_flag == AUTOMATIC_MODE)
            QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
    }
    if (g_SelfTestStatus.USB_5856_Card4_STS) {
        uint64_t outputs = 0;
        uint32_t Inputs = 0;
        g_SelfTestStatus.USB_5856_Card4_STS = 0;

        memcpy(&outputs, &Output_5856_Card_4, sizeof(Output_5856_Card_4));
        memcpy(&Inputs, &Input_5856_Card_4, sizeof(Input_5856_Card_4));
        ui->USB_5856_input4_Card4_le->setText(QString::number(Inputs, 16).toUpper());
        ui->USB_5856_output4_Card4_le->setText(QString::number(outputs, 16).toUpper());
        //        qDebug() << "card4outputs" << QString::number(outputs, 16);
        //        qDebug() << "card4Inputs" << QString::number(Inputs, 16);
        memset(&Output_5856_Card_4, 0, sizeof(Output_5856_Card_4));
        memset(&Input_5856_Card_4, 0, sizeof(Input_5856_Card_4));
        if ((outputs == 0xFF4C075F) && (Inputs == 0x20043)) {
            R4 = "PASS";
            ui->USB_5856_AE_Card4_pb->setStyleSheet(GBC);
            ui->USB_5856_AE_Card4_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(true);
            ui->USB_5856_AE_Card2_pb->setEnabled(false);
            ui->USB_5856_AE_Card3_pb->setEnabled(false);
            ui->USB_5856_AE_Card4_pb->setEnabled(false);
        } else {
            R4 = "FAIL";
            ui->USB_5856_AE_Card4_pb->setStyleSheet(RBC);
            ui->USB_5856_AE_Card4_pb->setChecked(false);
            ui->USB_5856_AE_Card1_pb->setEnabled(true);
            ui->USB_5856_AE_Card2_pb->setEnabled(false);
            ui->USB_5856_AE_Card3_pb->setEnabled(false);
            ui->USB_5856_AE_Card4_pb->setEnabled(false);
        }
        if (g_mode_flag == AUTOMATIC_MODE)
            QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
    }
}

void MainWindow::on_Volt_28_pb_clicked()
{
    emit ps1_VM();
    ui->Volt_28_le->setText(QString::number(g_Direct_Monitor.Input_Ch8));
    float fixed_val28 = 28.0, diff_28 = 0.0;

    float val28 = ui->Volt_28_le->text().toFloat();
    diff_28 = val28 - fixed_val28;

    //if (rep_flag1 == 1) {
    if ((diff_28 >= -(2.00)) && (diff_28 <= (2.00))) {
        rs28 = "PASS";
        ui->Volt_28_pb->setStyleSheet(GBC);
        ui->Volt_28_pb->setChecked(false);
    } else {
        rs28 = "FAIL";
        ui->Volt_28_pb->setStyleSheet(RBC);
        ui->Volt_28_pb->setChecked(false);
    }
}

void MainWindow::on_Volt_5_pb_clicked(bool checked)
{
    rep_flag2 = checked;
    emit ps3_VM();

    ui->Volts_5_le->setText(QString::number(g_Direct_Monitor.Input_Ch9));
    float fixed_val5 = 5.0, diff5 = 0.0;

    float val5 = ui->Volts_5_le->text().toFloat();

    diff5 = val5 - fixed_val5;

    if ((diff5 >= -(0.50)) && (diff5 <= (0.50))) {
        rs5 = "PASS";
        ui->Volt_5_pb->setStyleSheet(GBC);
        ui->Volt_5_pb->setChecked(false);
    } else {
        rs5 = "FAIL";
        ui->Volt_5_pb->setStyleSheet(RBC);
        ui->Volt_5_pb->setChecked(false);
    }
}

void MainWindow::on_Volt_3_3_pb_clicked(bool checked)
{
    if (checked)
        ui->Volt_3_3_pb->setStyleSheet(YBC); /*YELLOW*/
    emit ps4_VM();

    ui->Volt_3_3_le->setText(QString::number(g_Direct_Monitor.Input_Ch10));

    float fixed_val3 = 3.3, diff3 = 0.0;
    float val3 = ui->Volt_3_3_le->text().toFloat();
    diff3 = val3 - fixed_val3;
    if ((diff3 >= -(0.20)) && (diff3 <= (0.20))) {
        rs3 = "PASS";

        ui->Volt_3_3_pb->setStyleSheet(GBC);
        ui->Volt_3_3_pb->setChecked(false);
    } else {
        rs3 = "FAIL";
        ui->Volt_3_3_pb->setStyleSheet(RBC);
        ui->Volt_3_3_pb->setChecked(false);
    }
}
void MainWindow::on_Volts_plus_5_pb_clicked()
{
    ui->Volts_plus_5_pb->setStyleSheet(YBC); /*YELLOW*/

    emit ps5_plus5_VM();
    ui->Volt_plus_5_le->setText(QString::number(g_Direct_Monitor.Input_Ch11));

    float fixed_val_plus5 = 5.0, diff_plus5 = 0.0;
    float val_plus5 = ui->Volt_plus_5_le->text().toFloat();

    diff_plus5 = val_plus5 - fixed_val_plus5;

    if ((diff_plus5 >= -(0.20)) && (diff_plus5 <= (0.20))) {
        rsplus5 = "PASS";
        ui->Volts_plus_5_pb->setStyleSheet(GBC);
        ui->Volts_plus_5_pb->setChecked(false);
    } else {
        rsplus5 = "FAIL";
        ui->Volts_plus_5_pb->setStyleSheet(RBC);
        ui->Volts_plus_5_pb->setChecked(false);
    }
}

void MainWindow::on_Volts_minus_5_pb_clicked(bool checked)
{
    rep_flag3 = checked;
    emit ps6_minus5_VM();
    ui->Volt_minus_5_le->setText(QString::number(g_Direct_Monitor.Input_Ch12));
    float fixed_val_5 = -5.0, diff_5 = 0.0;

    float val_5 = ui->Volt_minus_5_le->text().toFloat();
    diff_5 = val_5 - fixed_val_5;

    if ((diff_5 >= -(0.20)) && (diff_5 <= (0.20))) {
        rs_5 = "PASS";
        ui->Volts_minus_5_pb->setStyleSheet(GBC);
        ui->Volts_minus_5_pb->setChecked(false);
    } else {
        rs_5 = "FAIL";
        ui->Volts_minus_5_pb->setStyleSheet(RBC);
        ui->Volts_minus_5_pb->setChecked(false);
    }
}

void MainWindow::on_Volt_28_16_32_Cmb_currentIndexChanged(int index)
{
    //rep_f = checked;
    emit PS7_VM(index);

    if (index == 1) {
        ui->Volt_16_28_32_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_16));
        str1 = ui->Volt_16_28_32_le->text();
        float fixed_v16 = 16.0, d_16 = 0.0;
        float v16 = ui->Volt_16_28_32_le->text().toFloat();
        d_16 = v16 - fixed_v16;
        if ((d_16 >= -(1.00)) && (d_16 <= (1.00))) {
            rs16 = "PASS";
        } else {
            rs16 = "FAIL";
        }
        //        Logger::instance()->logText("g_Direct_Monitor.Input_Ch6_16");
    }
    if (index == 2) {
        ui->Volt_16_28_32_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_28));
        str2 = ui->Volt_16_28_32_le->text();
        //        qDebug() << "str2" << str2;
        float fixed_v28 = 28.0, d_28 = 0.0;
        float v28 = ui->Volt_16_28_32_le->text().toFloat();
        d_28 = v28 - fixed_v28;
        if ((d_28 >= -(1.00)) && (d_28 <= (1.00))) {
            rs_28 = "PASS";
        } else {
            rs_28 = "FAIL";
        }
        //        Logger::instance()->logText("g_Direct_Monitor.Input_Ch6_16");
    }
    if (index == 3) {
        ui->Volt_16_28_32_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_32));
        str3 = ui->Volt_16_28_32_le->text();
        //        qDebug() << "str3" << str3;
        float fixed_v32 = 32.0, diff_32 = 0.0;
        float v32 = ui->Volt_16_28_32_le->text().toFloat();
        diff_32 = v32 - fixed_v32;
        if ((diff_32 >= -(1.00)) && (diff_32 <= (1.00))) {
            rs_32 = "PASS";
        } else {
            rs_32 = "FAIL";
        }
        //        Logger::instance()->logText("g_Direct_Monitor.Input_Ch6_32");
    }
    if (index == 4) {
        ui->Volt_16_28_32_le->setText(QString::number(g_Direct_Monitor.Input_ch6_Ext));
        ui->Volt_16_28_32_le->text();
        str4 = ui->Volt_16_28_32_le->text();
        //        qDebug() << "str4" << str4;
        float f_28vol = 28.0, d_28vol = 0.0;
        float vol28 = ui->Volt_16_28_32_le->text().toFloat();
        d_28vol = vol28 - f_28vol;
        if ((d_28vol >= -(1.00)) && (d_28vol <= (1.00))) {
            Ex_28 = "PASS";
        } else {
            Ex_28 = "FAIL";
        }
    }
    if (index == 5) {
        //        g_AdvantechCardsInterface->voltages_16_28_32_OFF();
        //        ui->Volt_16_28_32_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_16));
        //        ui->Volt_16_28_32_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_28));
        //        ui->Volt_16_28_32_le->setText(QString::number(g_Direct_Monitor.Input_Ch6_32));
    }
}
//void MainWindow::on_Volt_28_16_32_pb_toggled(bool checked) {}

//bool MainWindow::findAllNIScopeDevices()
//{
//    Logger::instance()->logText("Starting NI Scope device scan...");

//    QStringList foundDevices;
//    QStringList knownDevices = {"Dev1", "Dev2", "Dev3", "Dev4"};

//    for (const QString &dev : knownDevices) {
//        Logger::instance()->logText(QString(" Checking device: %1").arg(dev));

//        ViSession session = VI_NULL;
//        ViStatus status = niScope_init(dev.toLatin1().data(), VI_FALSE, VI_FALSE, &session);
//        if (status == VI_SUCCESS) {
//            //            foundDevices.append(dev);
//            niScope_close(session);
//            usbDeviceName = dev;
//            detectedDevice = dev;

//            return true;
//        }
//    }
//    Logger::instance()->logText(
//        QString(" Device scan complete. Found %1 device(s)").arg(foundDevices.size()));
//    usbDeviceName = "";

//    // return foundDevices;
//    return false;
//}

bool MainWindow::findAllNIScopeDevices()
{
    Logger::instance()->logText("Starting NI Scope device scan...");

    QStringList knownDevices = {"Dev1", "Dev2", "Dev3", "Dev4"};

    for (const QString &dev : knownDevices) {
        Logger::instance()->logText(QString(" Checking device: %1").arg(dev));

        ViSession session = VI_NULL;

        QByteArray devName = dev.toLatin1(); // Keep it alive
        ViStatus status = niScope_init(dev.toLatin1().data(), VI_FALSE, VI_FALSE, &session);

        if (status == VI_SUCCESS) {
            niScope_close(session);
            usbDeviceName = dev;
            detectedDevice = dev;
            return true;
        }
    }

    Logger::instance()->logText(" Device scan complete. No devices found.");
    usbDeviceName = "";
    return false;
}

void MainWindow::on_USB_5132_OSCILLOSCOPE_CARD_pb_toggled(bool checked)
{
    Logger::instance()->logText(
        QString("-----USB_5132_OSCILLOSCOPE_CARD_pb toggled: %1----").arg(checked ? "ON" : "OFF"));

    if (!usb5132_card_success) {
        Logger::instance()->logText("[ERROR] USB5132 is not initialized or failed.");

        if (!autoMode) {
            QMessageBox::warning(this, "Card Error", "USB5132 is not initialized or failed.");
            ui->USB_5132_OSCILLOSCOPE_CARD_pb->setChecked(false);
        } else {
            // Auto mode: non-blocking warning and auto skip
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning,
                                                  "Card Error",
                                                  "USB5132 is not initialized or failed.",
                                                  QMessageBox::Ok,
                                                  this);
            msgBox->setAttribute(Qt::WA_DeleteOnClose);
            msgBox->setModal(false);
            msgBox->show();
            QTimer::singleShot(1500, msgBox, &QMessageBox::close); // Show for info only
        }

        if (g_mode_flag == AUTOMATIC_MODE) {
            QTimer::singleShot(10, this, SLOT(AutoStepCompleted())); // Go to next step
        }

        return;
    }

    QString resultText;
    ViStatus status;
    if (checked) {
        ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(YBC); //*YELLOW*/

        QString devNameStr = "Dev1";              // <-- Explicitly define which device you're using
        QByteArray devName = devNameStr.toUtf8(); // creates a modifiable buffer
        ViSession session;
        status = niScope_init(devName.data(), VI_FALSE, VI_FALSE, &session);

        if (status < 0) {
            QMessageBox::critical(this, "Self Test", "Failed to open NI-SCOPE session.");
            ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(RBC);
            ui->USB_5132_OSCILLOSCOPE_CARD_pb->setChecked(false);
            //return;
        }

        ViInt16 testResult;
        char testMessage[256] = {};
        status = niScope_self_test(session, &testResult, testMessage);
        niScope_close(session);

        if (status == VI_SUCCESS) {
            if (testResult == 0) {
                resultText = QString("%1 : PASS").arg(devNameStr); // <-- use devNameStr here
                ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(GBC);
                ui->USB_5132_OSCILLOSCOPE_CARD_pb->blockSignals(true);
                ui->USB_5132_OSCILLOSCOPE_CARD_pb->setChecked(false);
                ui->USB_5132_OSCILLOSCOPE_CARD_pb->blockSignals(false);
            } else {
                resultText = QString("%1 : FAIL - %2").arg(devNameStr).arg(testMessage);
                ui->USB_5132_Oscilloscope_output_Card_le->setStyleSheet("color: white;");
                ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(RBC);
            }
        } else {
            resultText = QString("Self-test failed: Status = %1").arg(status);
            ui->USB_5132_Oscilloscope_output_Card_le->setStyleSheet("color: white;");
            ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(RBC);
            ui->USB_5132_OSCILLOSCOPE_CARD_pb->setChecked(false);
        }

        ui->USB_5132_Oscilloscope_output_Card_le->setText(resultText);
        //        qDebug() << resultText;
        Logger::instance()->logText(resultText);

        Logger::instance()->logText("niScope session closed");
    }

    if (g_mode_flag == AUTOMATIC_MODE) {
        QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
    }
}

//void MainWindow::performSelfTest(const QString &resourceName)
//{
//    ViSession vi = VI_NULL;
//    ViStatus status;
//    ViInt16 selfTestResult = 0;
//    ViChar selfTestMessage[256] = {0};

//    //    QByteArray deviceNameBytes = resourceName.toLocal8Bit();
//    //    char *deviceName = deviceNameBytes.data();
//    //    Logger::instance()->logText(QString(" Starting self-test for: %1").arg(resourceName));

//    //  Try to initialize the NI Scope device

//    status = niScope_init("Dev1", VI_TRUE, VI_TRUE, &vi);
//    if (status != VI_SUCCESS) {
//        QString err = QString(" Init failed: Status = %1").arg(status);
//        qDebug() << err;
//        Logger::instance()->logText(err);
//    }

//    // Perform self-test
//    status = niScope_self_test(vi, &selfTestResult, selfTestMessage);

//    QString resultText;
//    if (status == VI_SUCCESS) {
//        if (selfTestResult == 0) {
//            resultText = QString(" %1 : PASS").arg(resourceName);

//            ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(GBC);
//            ui->USB_5132_OSCILLOSCOPE_CARD_pb->blockSignals(true);
//            ui->USB_5132_OSCILLOSCOPE_CARD_pb->setChecked(false);
//            ui->USB_5132_OSCILLOSCOPE_CARD_pb->blockSignals(false);
//        } else {
//            resultText = QString(" %1 : FAIL - %2").arg(resourceName).arg(selfTestMessage);
//            ui->USB_5132_Oscilloscope_output_Card_le->setStyleSheet("color: white;");
//        }
//    } else {
//        resultText = QString("Self-test failed: Status = %1").arg(status);
//        ui->USB_5132_Oscilloscope_output_Card_le->setStyleSheet("color: white;");
//        ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(RBC);
//        ui->USB_5132_OSCILLOSCOPE_CARD_pb->setChecked(false);
//    }

//    ui->USB_5132_Oscilloscope_output_Card_le->setText(resultText);
//    qDebug() << resultText;
//    Logger::instance()->logText(resultText);

//    niScope_close(vi);
//    Logger::instance()->logText(" niScope session closed ");
//    if (g_mode_flag == AUTOMATIC_MODE) {
//        QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
//    }
//}

void MainWindow::on_LED_DISPLAY_STATUS_pb_toggled(bool checked)
{
    //    qDebug() << "[LED TEST] Running LED Display Status Logic" << checked;

    if (checked) {
        ui->LED_DISPLAY_STATUS_pb->setStyleSheet(YBC);
        emit LED_PS4_Sig(checked);
        emit LED_PS5_Sig(checked);
        emit LED_PS6_Sig(checked);
        emit LED_PS7_Sig(checked);

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,
                                      "Check the glowing state of",
                                      "LEDs PS1,PS2, PS3, PS4, PS5, PS6, "
                                      "PS7......IF found ok click \"Yes\" else \"NO\"?",
                                      QMessageBox::Yes | QMessageBox::No);

        //        QSignalBlocker blocker(ui->LED_DISPLAY_STATUS_pb); // Prevent toggled recursion

        if (reply == QMessageBox::Yes) {
            //            qDebug() << "User clicked Yes";
            ui->led_display_le->setText(
                "Checked LEDs PS1,PS2, PS3, PS4, PS5, PS6,PS7 — all are glowing correctly.");
            ui->LED_DISPLAY_STATUS_pb->setStyleSheet(GBC);
            Logger::instance()->logText(
                "Checked LEDs PS1,PS2, PS3, PS4, PS5, PS6,PS7 — all are glowing correctly.");
        } else {
            //            qDebug() << "User clicked No";
            ui->led_display_le->setText(
                "IF any LED/LED's PS1,PS2, PS3, PS4, PS5, PS6, PS7 are not glowing");
            ui->LED_DISPLAY_STATUS_pb->setStyleSheet(RBC);
            Logger::instance()->logText(
                "IF any LED/LED's PS1,PS2, PS3, PS4, PS5, PS6, PS7 are not glowing");
        }
        ui->LED_DISPLAY_STATUS_pb->setChecked(false); // Uncheck manually, safely
        on_LED_DISPLAY_STATUS_pb_toggled(false);
        if (g_mode_flag == AUTOMATIC_MODE) {
            QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
        }

    } else {
        // If unchecked manually or programmatically
        emit LED_PS4_Sig(checked);
        emit LED_PS5_Sig(checked);
        emit LED_PS6_Sig(checked);
        emit LED_PS7_Sig(checked);
    }
}

void MainWindow::updateAoAiLineEdits(double ao, const QVector<double> &ai)
{
    ui->USB_4716_op1_Card2_le->setText(QString::number(ao, 'f', 2));
    //    qDebug() << QString::number(ao, 'f', 2) << "in updateAoAiLineEdits";
    if (ai.size() >= 8) {
        ui->USB_4716_input1_Card2_le->setText(QString::number(ai[0], 'f', 4));
        ui->USB_4716_input2_Card2_le->setText(QString::number(ai[1], 'f', 4));
        ui->USB_4716_input3_Card2_le->setText(QString::number(ai[2], 'f', 4));
        ui->USB_4716_input4_Card2_le->setText(QString::number(ai[3], 'f', 4));
        ui->USB_4716_input5_Card2_le->setText(QString::number(ai[4], 'f', 4));
        ui->USB_4716_input6_Card2_le->setText(QString::number(ai[5], 'f', 4));
        ui->USB_4716_input7_Card2_le->setText(QString::number(ai[6], 'f', 4));
        ui->USB_4716_input8_Card2_le->setText(QString::number(ai[7], 'f', 4));

        //        ui->USB_4716_AE_CARD2_pb->setStyleSheet(
        //            "color:black;background-color: rgb(0, 255, 127)"); /*YELLOW*/
        //        ui->USB_4716_AE_CARD2_pb->setChecked(false);
    }
}

void MainWindow::on_refreshButton_clicked()
{
    ui->ATE_user_remarks_le->clear();
    ui->USB_5856_output1_Card1_le->clear();
    ui->USB_5856_input1_Card1_le->clear();
    ui->USB_5856_output2_Card2_le->clear();
    ui->USB_5856_input2_Card2_le->clear();
    ui->USB_5856_output3_Card3_le->clear();
    ui->USB_5856_input3_Card3_le->clear();
    ui->USB_5856_output4_Card4_le->clear();
    ui->USB_5856_input4_Card4_le->clear();

    g_SelfTestStatus.USB_5856_Card1_STS = 0;
    g_SelfTestStatus.USB_5856_Card2_STS = 0;
    g_SelfTestStatus.USB_5856_Card3_STS = 0;
    g_SelfTestStatus.USB_5856_Card4_STS = 0;
    ui->USB_5856_AE_Card1_pb->setChecked(false);
    ui->USB_5856_AE_Card2_pb->setChecked(false);
    ui->USB_5856_AE_Card3_pb->setChecked(false);
    ui->USB_5856_AE_Card4_pb->setChecked(false);
    ui->USB_5856_AE_Card1_pb->setEnabled(true);
    ui->USB_5856_AE_Card2_pb->setEnabled(true);
    ui->USB_5856_AE_Card3_pb->setEnabled(true);
    ui->USB_5856_AE_Card4_pb->setEnabled(true);

    ui->USB_5856_AE_Card1_pb->setStyleSheet(Grey);
    ui->USB_5856_AE_Card2_pb->setStyleSheet(Grey);
    ui->USB_5856_AE_Card3_pb->setStyleSheet(Grey);
    ui->USB_5856_AE_Card4_pb->setStyleSheet(Grey);

    ui->Volt_28_le->clear();
    ui->Volts_5_le->clear();
    ui->Volt_3_3_le->clear();
    ui->Volt_plus_5_le->clear();
    ui->Volt_minus_5_le->clear();
    ui->Volt_16_28_32_le->clear();
    // Now just call the voltage test functions with false (unchecked) or true (checked) as needed
    ui->Volt_3_3_pb->setStyleSheet(Grey);
    ui->Volt_28_pb->setStyleSheet(Grey);
    ui->Volt_5_pb->setStyleSheet(Grey);
    ui->Volts_plus_5_pb->setStyleSheet(Grey);
    ui->Volts_minus_5_pb->setStyleSheet(Grey);
    //ui->Volt_28_16_32_Cmb->setCurrentIndex(5);

    ui->USB_5132_OSCILLOSCOPE_CARD_pb->setStyleSheet(Grey);
    ui->USB_5132_Oscilloscope_output_Card_le->clear();

    ui->RS422_LOOP_BACK_pb_1->setStyleSheet(Grey);
    ui->RS422_LOOP_BACK_le1->clear();
    ui->RS422_LOOP_BACK_le1->setStyleSheet("");
    ui->RS422_LOOP_BACK_pb_2->setStyleSheet(Grey);
    ui->RS422_LOOP_BACK_le2->clear();
    ui->RS422_LOOP_BACK_le2->setStyleSheet("");
    ui->USB_4716_AE_CARD2_pb->setStyleSheet(Grey);

    ui->USB_4716_input1_Card2_le->clear();
    ui->USB_4716_input2_Card2_le->clear();
    ui->USB_4716_input3_Card2_le->clear();
    ui->USB_4716_input4_Card2_le->clear();
    ui->USB_4716_input5_Card2_le->clear();
    ui->USB_4716_input6_Card2_le->clear();
    ui->USB_4716_input7_Card2_le->clear();
    ui->USB_4716_input8_Card2_le->clear();

    ui->LED_DISPLAY_STATUS_pb->setStyleSheet(Grey);
    ui->led_display_le->clear();
    ui->tested_by_le->clear();
    ui->REPORT_pb->setStyleSheet(Grey);
    //    ui->Auto_mode_rb->setEnabled(true);
    //    ui->Auto_mode_rb->setChecked(true);
    ui->Auto_mode_rb->setStyleSheet("");

    //    ui->Manual_mode_rb->setEnabled(true);
    //    ui->Manual_mode_rb->setChecked(true);
    ui->Manual_mode_rb->setStyleSheet("");
    //    Timer_interrupt->stop();
    g_mode_flag = 0;
    g_step_in_progress = false;
    g_initiate_sequence_counter = 0;
    g_max_transmit_count_reach = 0;
    g_failure_status_check = 0;

    // ui->Manual_mode_rb->setDisabled(false);
    ui->Auto_mode_rb->setDisabled(false);
    ui->Start_PB->setDisabled(false);
    ui->Start_PB->setChecked(false);
    //    qDebug() << "UI and test status have been reset.";
    //    Timer_interrupt->stop();
    ui->Start_PB->setStyleSheet(Grey);

    ui->Auto_mode_rb->setAutoExclusive(false);
    ui->Manual_mode_rb->setAutoExclusive(false);

    //    ui->Auto_mode_rb->setChecked(false);
    ui->Auto_mode_rb->setEnabled(true);
    ui->Manual_mode_rb->setEnabled(true);

    ui->Auto_mode_rb->setChecked(false);
    ui->Manual_mode_rb->setChecked(false);

    //    ui->Auto_mode_rb->setAutoExclusive(false);
    //    ui->Manual_mode_rb->setAutoExclusive(false);

    ui->groupBox_14->setEnabled(false);
    ui->groupBox_18->setEnabled(false);
    ui->groupBox_19->setEnabled(false);
    ui->groupBox_13->setEnabled(false);
    ui->groupBox_24->setEnabled(false);
    ui->groupBox_25->setEnabled(false);
}

void MainWindow::on_LRU_VoltagePB_toggled(bool checked)
{
    Logger::instance()->logText(QString("----------STARTS LRU BIT TEST ----------- "));
    if (checked) {
        // voltage = ui->LRU_VoltageCB->currentText();

        if (!ui->checkBox_front_panel_lru_checks->isChecked()) {
            ui->LRU_VoltageCB->setCurrentIndex(2);
        }
        int index = ui->LRU_VoltageCB->currentIndex();
        ui->Volt_28_16_32_Cmb->setCurrentIndex(index);
        on_Volt_28_16_32_Cmb_currentIndexChanged(index); // update voltage + current UI
        ui->LRU_VoltageLE->setText(ui->LRU_VoltageCB->currentText());

        // ui->LRU_VoltageLE->setText(voltage);
        if (g_CurrentSensorData.curr_PS7 < 0)
            g_CurrentSensorData.curr_PS7 = 0;
        ui->Ip_Current_le->setText(QString::number(g_CurrentSensorData.curr_PS7, 'f', 4));
        Logger::instance()->logText(QString(" LRU Voltage: %1| Current: %2 A")
                                        .arg(voltageValue)
                                        .arg(QString::number(g_CurrentSensorData.curr_PS7, 'f', 4)));
        ;
    } else {
        ui->LRU_VoltageCB->setCurrentIndex(5);
        on_Volt_28_16_32_Cmb_currentIndexChanged(5);
        ui->LRU_VoltageLE->setText(ui->LRU_VoltageCB->currentText());
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {      // <-- double-click
        if (auto *plot = qobject_cast<QCustomPlot *>(obj)) { // confirm sender
            if (plot->objectName() == "Graph1") {
                //                qDebug() << "Double-clicked on" << plot->objectName();
                ui->Graph1_widget->setVisible(true);
                ui->Graph2_widget->setVisible(false);
                ui->Graph3_widget->setVisible(false);
                ui->Graph4_widget->setVisible(false);
                ui->Graph5_widget->setVisible(false);
                ui->Graph6_widget->setVisible(false);
                ui->Graph7_widget->setVisible(false);
                ui->Graph8_widget->setVisible(false);
                ui->GraphSet1_widget->setVisible(true);
                ui->GraphSet2_widget->setVisible(false);
            } else if (plot->objectName() == "Graph2") {
                ui->Graph1_widget->setVisible(false);
                ui->Graph2_widget->setVisible(true);
                ui->Graph3_widget->setVisible(false);
                ui->Graph4_widget->setVisible(false);
                ui->Graph5_widget->setVisible(false);
                ui->Graph6_widget->setVisible(false);
                ui->Graph7_widget->setVisible(false);
                ui->Graph8_widget->setVisible(false);
                ui->GraphSet1_widget->setVisible(false);
                ui->GraphSet2_widget->setVisible(true);
            } else if (plot->objectName() == "Graph3") {
                ui->Graph1_widget->setVisible(false);
                ui->Graph2_widget->setVisible(false);
                ui->Graph3_widget->setVisible(true);
                ui->Graph4_widget->setVisible(false);
                ui->Graph5_widget->setVisible(false);
                ui->Graph6_widget->setVisible(false);
                ui->Graph7_widget->setVisible(false);
                ui->Graph8_widget->setVisible(false);
                ui->GraphSet1_widget->setVisible(true);
                ui->GraphSet2_widget->setVisible(false);
            } else if (plot->objectName() == "Graph4") {
                ui->Graph1_widget->setVisible(false);
                ui->Graph2_widget->setVisible(false);
                ui->Graph3_widget->setVisible(false);
                ui->Graph4_widget->setVisible(true);
                ui->Graph5_widget->setVisible(false);
                ui->Graph6_widget->setVisible(false);
                ui->Graph7_widget->setVisible(false);
                ui->Graph8_widget->setVisible(false);
                ui->GraphSet1_widget->setVisible(false);
                ui->GraphSet2_widget->setVisible(true);
            } else if (plot->objectName() == "Graph5") {
                ui->Graph1_widget->setVisible(false);
                ui->Graph2_widget->setVisible(false);
                ui->Graph3_widget->setVisible(false);
                ui->Graph4_widget->setVisible(false);
                ui->Graph5_widget->setVisible(true);
                ui->Graph6_widget->setVisible(false);
                ui->Graph7_widget->setVisible(false);
                ui->Graph8_widget->setVisible(false);
                ui->GraphSet1_widget->setVisible(true);
                ui->GraphSet2_widget->setVisible(false);
            } else if (plot->objectName() == "Graph6") {
                ui->Graph1_widget->setVisible(false);
                ui->Graph2_widget->setVisible(false);
                ui->Graph3_widget->setVisible(false);
                ui->Graph4_widget->setVisible(false);
                ui->Graph5_widget->setVisible(false);
                ui->Graph6_widget->setVisible(true);
                ui->Graph7_widget->setVisible(false);
                ui->Graph8_widget->setVisible(false);
                ui->GraphSet1_widget->setVisible(false);
                ui->GraphSet2_widget->setVisible(true);
            } else if (plot->objectName() == "Graph7") {
                ui->Graph1_widget->setVisible(false);
                ui->Graph2_widget->setVisible(false);
                ui->Graph3_widget->setVisible(false);
                ui->Graph4_widget->setVisible(false);
                ui->Graph5_widget->setVisible(false);
                ui->Graph6_widget->setVisible(false);
                ui->Graph7_widget->setVisible(true);
                ui->Graph8_widget->setVisible(false);
                ui->GraphSet1_widget->setVisible(true);
                ui->GraphSet2_widget->setVisible(false);
            } else if (plot->objectName() == "Graph8") {
                ui->Graph1_widget->setVisible(false);
                ui->Graph2_widget->setVisible(false);
                ui->Graph3_widget->setVisible(false);
                ui->Graph4_widget->setVisible(false);
                ui->Graph5_widget->setVisible(false);
                ui->Graph6_widget->setVisible(false);
                ui->Graph7_widget->setVisible(false);
                ui->Graph8_widget->setVisible(true);
                ui->GraphSet1_widget->setVisible(false);
                ui->GraphSet2_widget->setVisible(true);
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event); // default handling
}

void MainWindow::on_RESTORE_clicked()
{
    ui->Graph1_widget->setVisible(true);
    ui->Graph2_widget->setVisible(true);
    ui->Graph3_widget->setVisible(true);
    ui->Graph4_widget->setVisible(true);
    ui->Graph5_widget->setVisible(true);
    ui->Graph6_widget->setVisible(true);
    ui->Graph7_widget->setVisible(true);
    ui->Graph8_widget->setVisible(true);
    ui->GraphSet1_widget->setVisible(true);
    ui->GraphSet2_widget->setVisible(true);
}

void MainWindow::on_Bittest_Start_Pb_toggled(bool checked)
{
    if (checked) {
        //        QMessageBox::StandardButton reply;
        //        reply
        //            = QMessageBox::question(this,
        //                                    " Voltages",
        //                                    "Select the voltages in the comboBox,and click PushButton "
        //                                    "IF found ok click \"Yes\" else \"Please select the voltage\"?",
        //                                    QMessageBox::Yes | QMessageBox::No);
        //        if (reply == QMessageBox::Yes) {
        //            //            qDebug() << "User clicked Yes";

        //        } else {
        //            //            qDebug() << "User clicked No";
        //        }
        Bittest_flag = true;

        on_Discrete_Inputs_Pb_toggled(true);

        ADC_BitTestTim->start(1);

        BittestLogTimer->start(10000);

        g_USB_Port_Connect = true;

        ui->Bittest_Start_Pb->setText("STOP");
        ui->LRU_VoltagePB->setDisabled(true);
        ui->LRU_VoltageCB->setDisabled(true);

        //        ui->POST_listW->setEnabled(false);
        ui->groupBox_60->setEnabled(false);
        ui->groupBox_62->setEnabled(false);
        if (ui->checkBox_front_panel_lru_checks->isChecked()) {
            ui->groupBox_64->setEnabled(true);

        } else {
            // ui->groupBox_64->setEnabled(false);
        }
        // ui->groupBox_17->setEnabled(false);
        //  ui->FTU_BitTest_Report->setEnabled(false);
        ui->LRU_Checksum_le->setEnabled(false);
        ui->BITTEST_ATE_Checksum_le->setEnabled(false);
    } else {
        Bittest_flag = false;
        ADC_BitTestTim->stop();

        ui->Bittest_Start_Pb->setText("START");
        ui->LRU_VoltagePB->setEnabled(true);
        ui->LRU_VoltageCB->setEnabled(true);

        emit Discrete_Input_Ch1(false);
        emit Discrete_Input_Ch2(false);
        emit Discrete_Input_Ch3(false);

        //        ui->POST_listW->setEnabled(true);
        ui->groupBox_60->setEnabled(true);
        ui->groupBox_62->setEnabled(true);
        ui->groupBox_64->setEnabled(true);
        ui->groupBox_17->setEnabled(true);
        //  ui->FTU_BitTest_Report->setEnabled(true);
        ui->LRU_Checksum_le->setEnabled(false);
        ui->BITTEST_ATE_Checksum_le->setEnabled(false);

        // on_Discrete_Inputs_Pb_toggled(false);
    }
}

void MainWindow::on_Discrete_Inputs_Pb_toggled(bool checked)
{
    emit Discrete_IN_OFF();
    if (checked) {
        emit Discrete_Input_Ch1(checked);
        emit Discrete_Input_Ch2(checked);
        emit Discrete_Input_Ch3(checked);
        //        qDebug() << "on_Discrete_Inputs_Pb_toggled";
    } else {
        //        ui->Discrete_ip_value_Ch2_le->setText("0");
        //        ui->Discrete_Ip_result_Ch2_le->setText("FAIL");
        //        ui->Discrete_Ip_result_Ch2_le->setStyleSheet("color : red");
        emit Discrete_Input_Ch1(checked);
        emit Discrete_Input_Ch2(checked);
        emit Discrete_Input_Ch3(checked);
    }
}
void MainWindow::on_FTU_BitTest_Report_clicked()
{
    FTU_LRU_Checks();
}
void MainWindow::on_FTU_LRUReport_pb_clicked()
{
    FTULRU_Report();
}
void MainWindow::on_bittest_refresh_pb_clicked()
{
    ui->BT_Remarks->clear();
    ui->LRU_VoltageLE->clear();
    ui->Ip_Current_le->clear();
    ui->ADC_DAC_output_Ch1_le->clear();
    ui->ADC_DAC_output_Ch2_le->clear();
    ui->ADC_DAC_output_Ch3_le->clear();
    ui->ADC_DAC_output_Ch4_le->clear();
    ui->ADC_DAC_output_Ch5_le->clear();
    ui->ADC_DAC_output_Ch6_le->clear();
    ui->ADC_DAC_output_Ch7_le->clear();
    ui->ADC_DAC_output_Ch8_le->clear();
    ui->ADC_DAC_result_Ch1_le->clear();
    ui->ADC_DAC_result_Ch2_le->clear();
    ui->ADC_DAC_result_Ch3_le->clear();
    ui->ADC_DAC_result_Ch4_le->clear();
    ui->ADC_DAC_result_Ch5_le->clear();
    ui->ADC_DAC_result_Ch6_le->clear();
    ui->ADC_DAC_result_Ch7_le->clear();
    ui->ADC_DAC_result_Ch8_le->clear();
    ui->ADC_DAC_result_Ch1_le->setStyleSheet("");
    ui->ADC_DAC_result_Ch2_le->setStyleSheet("");
    ui->ADC_DAC_result_Ch3_le->setStyleSheet("");
    ui->ADC_DAC_result_Ch4_le->setStyleSheet("");
    ui->ADC_DAC_result_Ch5_le->setStyleSheet("");
    ui->ADC_DAC_result_Ch6_le->setStyleSheet("");
    ui->ADC_DAC_result_Ch7_le->setStyleSheet("");
    ui->ADC_DAC_result_Ch8_le->setStyleSheet("");

    ui->Discrete_op_value_Ch1_le->clear();
    ui->Discrete_op_value_Ch2_le->clear();
    ui->Discrete_op_value_Ch3_le->clear();
    ui->Discrete_op_value_Ch4_le->clear();
    ui->Discrete_op_value_Ch5_le->clear();
    ui->Discrete_op_result_Ch1_le->clear();
    ui->Discrete_op_result_Ch2_le->clear();
    ui->Discrete_op_result_Ch3_le->clear();
    ui->Discrete_op_result_Ch4_le->clear();
    ui->Discrete_op_result_Ch5_le->clear();
    ui->Discrete_op_result_Ch1_le->setStyleSheet("");
    ui->Discrete_op_result_Ch2_le->setStyleSheet("");
    ui->Discrete_op_result_Ch3_le->setStyleSheet("");
    ui->Discrete_op_result_Ch4_le->setStyleSheet("");
    ui->Discrete_op_result_Ch5_le->setStyleSheet("");

    ui->Discrete_ip_value_Ch1_le->clear();
    ui->Discrete_ip_value_Ch2_le->clear();
    ui->Discrete_ip_value_Ch3_le->clear();
    ui->Discrete_Ip_result_Ch1_le->clear();
    ui->Discrete_Ip_result_Ch2_le->clear();
    ui->Discrete_Ip_result_Ch3_le->clear();
    ui->Discrete_Ip_result_Ch1_le->setStyleSheet("");
    ui->Discrete_Ip_result_Ch2_le->setStyleSheet("");
    ui->Discrete_Ip_result_Ch3_le->setStyleSheet("");

    ui->Rotary_Update_Switch_Value_le->clear();
    ui->Rotary_Update_Switch_status_le->setStyleSheet("");
    ui->Rotary_Update_Switch_status_le->clear();
    ui->Prep_Switch_value_le->clear();
    ui->Prep_Switch_status_le->clear();
    ui->Prep_Switch_status_le->setStyleSheet("color:black");

    //  ui->Prep_Switch_value_le->setStyleSheet("QLineEdit::placeholder { color: #ebebeb; }");
    ui->Ready_Init_Switch_value_le->clear();
    ui->Ready_Init_Switch_status_le->setStyleSheet("");
    ui->Ready_Init_Switch_status_le->clear();
    ui->Abort_Switch_value_le->clear();
    ui->Abort_Switch_status_le->clear();
    ui->Abort_Switch_status_le->setStyleSheet("");
    ui->RS422_listwidget->clear();
    ui->FTU_BitTest_Report->setStyleSheet(blue);

    ui->Discrete_Inputs_Pb->setChecked(false);
    ui->LRU_VoltagePB->setChecked(false);
    ui->LRU_VoltageCB->setCurrentIndex(5);
    on_Volt_28_16_32_Cmb_currentIndexChanged(5);
    ui->LRU_VoltageLE->setText(ui->LRU_VoltageCB->currentText());
    ui->POST_listW->clear();
    ui->LRU_Checksum_le->clear();
    // ui->BITTEST_ATE_Checksum_le->clear();
    // ui->Bit_USB_Status->clear();
    ui->Bittest_Start_Pb->setChecked(false);
    ui->BITTEST_USB_STATUS_LE->clear();
    items.clear();
    ui->USB_Pat1_Data_LE->clear();
    ui->USB_Pat2_Data_LE->clear();
    //ui->bit_test_testedby_name->clear();
    //ui->bit_test_tester_name_le->clear();
}

void MainWindow::checkUsb5856Status()
{
    emit USB_5856_Conn_STS_Signal(0);
    emit USB_5856_Conn_STS_Signal(1);
    emit USB_5856_Conn_STS_Signal(2);
    emit USB_5856_Conn_STS_Signal(3);
}

void MainWindow::checkUsb4716Status() {}

//void MainWindow::checkUsb5132Status(bool initial)
//{
//    bool usbNow = findAllNIScopeDevices();

//    if (usbNow && !isUsb5132Connected) {
//        isUsb5132Connected = true;
//        if (!initial)
//            QMessageBox::information(this, "USB-5132 Connected", "USB-5132 Oscilloscope connected.");
//    } else if (!usbNow && isUsb5132Connected) {
//        isUsb5132Connected = false;
//        if (!initial)
//            QMessageBox::critical(this,
//                                  "USB-5132 Disconnected",
//                                  "USB-5132 Oscilloscope disconnected.");
//    }
//}

void MainWindow::checkUsb5132Status(bool initial)
{
    //    qDebug() << "Checking USB-5132 status...";
    bool usbNow = findAllNIScopeDevices();
    //    qDebug() << "USB-5132 currently connected? " << usbNow;

    if (usbNow && !isUsb5132Connected) {
        isUsb5132Connected = true;
        if (!initial)
            QMessageBox::information(this, "USB-5132 Connected", "USB-5132 Oscilloscope connected.");
    } else if (!usbNow && isUsb5132Connected) {
        isUsb5132Connected = false;
        if (!initial)
            QMessageBox::critical(this,
                                  "USB-5132 Disconnected",
                                  "USB-5132 Oscilloscope disconnected.");
    }
}

QStringList MainWindow::findMoxaPorts()
{
    QStringList ports;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.description().contains("MOXA", Qt::CaseInsensitive)
            || info.manufacturer().contains("MOXA", Qt::CaseInsensitive)) {
            ports << info.portName();
        }
    }
    return ports;
}

bool MainWindow::connectToPort(QSerialPort *port, const QString &portName, int index)
{
    if (port->isOpen())
        port->close(); // ensure clean start

    port->setPortName(portName);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if (port->open(QIODevice::ReadWrite)) {
        //        qDebug() << "MOXA" << index << "connected on port:" << portName;

        // Clear old connections (if any)
        disconnect(port, nullptr, nullptr, nullptr);

        connect(port, &QSerialPort::readyRead, this, [=]() {
            QByteArray data = port->readAll();
            //            qDebug() << "MOXA" << index << "received:" << data;
        });

        connect(port, &QSerialPort::errorOccurred, this, [=](QSerialPort::SerialPortError error) {
            if (error == QSerialPort::NoError)
                return;

            //            qDebug() << "MOXA" << index << "error:" << error << "-" << port->errorString();

            if (port->isOpen())
                port->close();

            switch (index) {
            case 1:
                isMoxa1Connected = false;
                popupShownForDisconnectMoxa1 = false; // allow disconnect popup again
                break;
            case 2:
                isMoxa2Connected = false;
                popupShownForDisconnectMoxa2 = false;
                break;
            }

            // Optional popup: handled in checkSerialStatus()
        });

        port->write("ping\n");
        port->flush();
        return true;
    } else {
        //        qDebug() << "Failed to open MOXA" << index << "on port:" << portName << "-"
        //                 << port->errorString();
    }

    return false;
}

void MainWindow::on_Manual_mode_rb_clicked()
{
    on_refreshButton_clicked();
    ui->Manual_mode_rb->setChecked(true);
    ui->Auto_mode_rb->setChecked(false);
    g_mode_flag = MANUAL_MODE;

    ui->Manual_mode_rb->setStyleSheet("QRadioButton::indicator:checked { "
                                      "background-color:#32CD32;border: 1px solid #ffffff; }");

    ui->groupBox_14->setEnabled(true);
    ui->groupBox_18->setEnabled(true);
    ui->groupBox_19->setEnabled(true);
    ui->groupBox_13->setEnabled(true);
    ui->groupBox_24->setEnabled(true);
    ui->groupBox_25->setEnabled(true);
    ui->REPORT_pb->setEnabled(true);
}

void MainWindow::on_Auto_mode_rb_clicked()
{
    on_refreshButton_clicked();
    ui->Manual_mode_rb->setChecked(false);
    ui->Auto_mode_rb->setChecked(true);
    g_mode_flag = AUTOMATIC_MODE;
    ui->Auto_mode_rb->setStyleSheet("QRadioButton::indicator:checked { "
                                    "background-color:#32CD32;border: 1px solid #ffffff; }");

    ui->REPORT_pb->setEnabled(false);
}

void MainWindow::on_Emergency_Stop_PB_clicked()
{
    //    qDebug() << "on_Emergency_Stop_PB_clicked";
    emit card1Signal_OFF();
    emit card2Signal_OFF();
    emit card3Signal_OFF();
    emit card4Signal_OFF();

    emit ADC_4716card2Signal_OFF();

    emit LED_PS4_Sig(false);
    emit LED_PS5_Sig(false);
    emit LED_PS6_Sig(false);
    emit LED_PS7_Sig(false);

    //    Timer_interrupt->stop();
    g_initiate_sequence_counter = 20;
    TimeOutTimer->stop();
    //    qDebug() << "on_Emergency_Stop_PB_clicked11111111111111111";
}

void MainWindow::on_Start_PB_clicked()
{
    //    qDebug() << "on_Start_PB_clicked";
    ui->Manual_mode_rb->setDisabled(true);
    ui->Auto_mode_rb->setDisabled(true);
    ui->Start_PB->setDisabled(true);
    //    qDebug() << "Start_PB  -----Auto_mode_rb-  ";
    ui->Start_PB->setStyleSheet(YBC);

    autoMode = ui->Auto_mode_rb->isChecked();

    //    qDebug() << "[MODE] autoMode =" << autoMode;

    //    g_step_in_progress = false;
    g_max_transmit_count_reach = 0;
    g_failure_status_check = 0;
    if (ui->Auto_mode_rb->isChecked()) {
        g_initiate_sequence_counter = 0;
        QMetaObject::invokeMethod(this, "AutoStepCompleted", Qt::QueuedConnection);
        //        Timer_interrupt->start(200);
        //        qDebug() << "[AUTO MODE] Started.";
    }
}

void MainWindow::Sequence_TimerInterrupt()
{
    //    qDebug() << "Sequence_TimerInterrupt";
    //    qDebug() << "g_initiate_sequence_counter" << g_initiate_sequence_counter;
    //    qDebug() << "g_step_in_progress" << g_step_in_progress;

    if (g_mode_flag != AUTOMATIC_MODE) {
        //        qDebug() << "1st return";

        return;
    }

    if (g_step_in_progress) {
        //        qDebug() << "return......................";
        return; // Wait until the current step is marked complete
    }

    switch (g_initiate_sequence_counter) {
    case 1:
        //        qDebug() << "[AUTO] Step 1: USB_5856_AE_Card1_STATUS";

        on_USB_5856_AE_Card1_pb_clicked(true);
        break;
    case 2:
        //        qDebug() << "[AUTO] Step 2: USB_5856_AE_Card2_STATUS";

        on_USB_5856_AE_Card2_pb_clicked(true);
        break;
    case 3:
        //        qDebug() << "[AUTO] Step 3: USB_5856_AE_Card3_STATUS";

        on_USB_5856_AE_Card3_pb_clicked(true);
        break;
    case 4:

        //        qDebug() << "[AUTO] Step 4: USB_5856_AE_Card4_STATUS";

        on_USB_5856_AE_Card4_pb_clicked(true);
        break;
    case 5: {
        ui->Volt_28_16_32_Cmb->setCurrentIndex(1);
        g_time_out_flag = 0;
        TimeOutTimer->start(4000);
        g_time_out_state = SELF_TEST_28V;
        g_time_out_flag = 1;
        break;
    }
    case 6:
        //        qDebug() << "[AUTO] Step 5: USB_5132_OSCILLOSCOPE_CARD";

        on_USB_5132_OSCILLOSCOPE_CARD_pb_toggled(true);
        break;
    case 7:
        //        qDebug() << "[AUTO] Step 6: RS422_LOOP_BACK_1";

        on_RS422_LOOP_BACK_pb_1_clicked(true);

        break;
    case 8:
        //        qDebug() << "[AUTO] Step 7: RS422_LOOP_BACK_2";

        on_RS422_LOOP_BACK_pb_2_clicked(true);
        break;
    case 9:
        //        qDebug() << "[AUTO] Step 8: USB_4716 AE CARD2";

        on_USB_4716_AE_CARD2_pb_clicked(true);

        break;

    case 10:
        //        qDebug() << "[AUTO] Step 9: LED_DISPLAY_STATUS";
        on_LED_DISPLAY_STATUS_pb_toggled(true);

        break;
    case 11:
        //        qDebug() << "[AUTO] Step 10: REPORT STATUS";
        on_REPORT_pb_clicked();
        g_mode_flag = 0;
        //        Timer_interrupt->stop();
        //        qDebug() << "[AUTO MODE COMPLETED]";
        ui->Start_PB->setStyleSheet(GBC);

        //         ui->Start_PB->setEnabled(true);

        //        ui->Start_PB->setChecked(false);
        //        ui->Start_PB->setEnabled(true);

        //        ui->Manual_mode_rb->setEnabled(true);
        //        ui->Auto_mode_rb->setEnabled(true);

        //        return;
        break;
    default:
        //        Timer_interrupt->stop();

        g_mode_flag = 0;
        break;
        //        return;
    }
    g_step_in_progress = true; // Mark the step as started
}

void MainWindow::AutoStepCompleted()
{
    //    qDebug() << "[STEP COMPLETE] Proceeding to next step.";
    g_step_in_progress = false;
    g_initiate_sequence_counter++;
    Sequence_TimerInterrupt();
}

//--------------------SRU LEVEL---------------------------//
//----------------DISPLAY_FUNCTION________________________//
void MainWindow::on_DISPLAY_C1_pb_clicked(bool checked)
{
    SruLogger::instance()->logText(
        QString("------------------[INFO] Display  1 %1-------------").arg(checked));

    if (checked) {
        uint8_t static value = 8;
        ui->Display_Card_Dial1->setEnabled(false);
        ui->DISPLAY_C1_pb->setEnabled(false);
        ui->DISPLAY_C2_pb->setEnabled(false);
        ui->DISPLAY_C3_pb->setEnabled(false);
        switch (value) {
        case 8: {
            ui->Display_Card_Dial1->setSliderPosition(8);
            value = 9;
            Timer_interrupt_Dial1->start(500);
            break;
        }
        case 9: {
            ui->Display_Card_Dial1->setSliderPosition(9);
            value = 10;
            break;
        }
        case 10: {
            ui->Display_Card_Dial1->setSliderPosition(10);
            value = 11;
            break;
        }
        case 11: {
            ui->Display_Card_Dial1->setSliderPosition(11);
            value = 12;
            break;
        }
        case 12: {
            ui->Display_Card_Dial1->setSliderPosition(12);
            value = 13;
            break;
        }
        case 13: {
            ui->Display_Card_Dial1->setSliderPosition(13);
            value = 14;
            break;
        }
        case 14: {
            ui->Display_Card_Dial1->setSliderPosition(14);
            value = 15;
            break;
        }
        case 15: {
            ui->Display_Card_Dial1->setSliderPosition(15);
            value = 0;
            break;
        }
        case 0: {
            ui->Display_Card_Dial1->setSliderPosition(0);
            value = 1;
            break;
        }
        case 1: {
            ui->Display_Card_Dial1->setSliderPosition(1);
            value = 2;
            break;
        }
        case 2: {
            ui->Display_Card_Dial1->setSliderPosition(2);
            value = 3;
            break;
        }
        case 3: {
            ui->Display_Card_Dial1->setSliderPosition(3);
            value = 4;
            break;
        }
        case 4: {
            ui->Display_Card_Dial1->setSliderPosition(4);
            value = 5;
            break;
        }
        case 5: {
            ui->Display_Card_Dial1->setSliderPosition(5);
            value = 6;
            break;
        }
        case 6: {
            ui->Display_Card_Dial1->setSliderPosition(6);
            value = 7;
            break;
        }
        case 7: {
            ui->Display_Card_Dial1->setSliderPosition(7);
            value = 16;
            break;
        }
        case 16: {
            ui->Display_Card_Dial1->setSliderPosition(8);
            value = 8;
            Timer_interrupt_Dial1->stop();
            ui->DISPLAY_C1_pb->setChecked(false);
            ui->DISPLAY_C1_pb->setEnabled(true);
            ui->DISPLAY_C2_pb->setEnabled(true);
            ui->DISPLAY_C3_pb->setEnabled(true);
            emit Display_Digit1(false);

            //            QMessageBox::StandardButton reply;
            //            reply = QMessageBox::question(this,
            //                                          "Display  1",
            //                                          "Press button Yes if all the Digits from 0-F have "
            //                                          "been Display on the First Digit"
            //                                          " else \"NO\"?",
            //                                          QMessageBox::Yes | QMessageBox::No);
            //            if (reply == QMessageBox::Yes) {
            //                ui->DISPLAY_C1_pb->setStyleSheet(GBC);
            //                Display1 = "0-F";
            //                D1_Status = "PASS";
            //                SruLogger::instance()->logText("Display  1 Observed all the Digits from 0-F "
            //                                               "have been Display on the First Digit");

            //            } else {
            //                ui->DISPLAY_C1_pb->setStyleSheet(RBC);
            //                Display1 = "NULL";
            //                D1_Status = "FAIL";
            //                SruLogger::instance()->logText("Display  1 Not Observed all the  Digits from "
            //                                               "0-F on Display Panel of First Digit");
            //            }

            QMessageBox msgBox(
                QMessageBox::Question,
                "Display 1",
                "Press \"Yes\" if all the Digits from 0-F have been observed on the First Digit "
                "of Display Module else press \"No\".",
                QMessageBox::Yes | QMessageBox::No,
                this);

            msgBox.setDefaultButton(QMessageBox::No);

            // Timer to close the box after 10 seconds as Cancel
            QTimer::singleShot(10000, &msgBox, [&msgBox]() {
                if (msgBox.isVisible()) {
                    msgBox.done(QMessageBox::Cancel);
                }
            });

            QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(
                msgBox.exec());

            if (reply == QMessageBox::Yes) {
                ui->DISPLAY_C1_pb->setStyleSheet(GBC);
                Display1 = "0-F";
                D1_Status = "PASS";
                SruLogger::instance()->logText("Display  1 Observed all the Digits from 0-F "
                                               "have been Display on the First Digit");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_DISPLAY_C2_pb_clicked(1);
                }
            } else if (reply == QMessageBox::No) {
                ui->DISPLAY_C1_pb->setStyleSheet(RBC);
                Display1 = "NULL";
                D1_Status = "FAIL";
                SruLogger::instance()->logText("Display  1 Not Observed all the Digits from "
                                               "0-F on Display Panel of First Digit");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_DISPLAY_C2_pb_clicked(1);
                }
            } else if (reply == QMessageBox::Cancel) {
                D1_Status = "------";
                Display1 = "Note: No Response from User, after the test has been completed.";
                SruLogger::instance()->logText(
                    "Display  1: User did not respond within 10s → Unable to do Test");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_DISPLAY_C2_pb_clicked(1);
                }
            }

            break;
        }
        default: {
            break;
        }
        }
    } else {
        emit Display_Digit1(checked);
    }
}

void MainWindow::on_Display_Card_Dial1_valueChanged(int value)
{
    emit Display_Digit1(false);
    emit Display_Dial1((uint16_t) value);
    emit Display_Digit1(true);
    //    qDebug() << QString::number(value);
}

void MainWindow::on_DISPLAY_C2_pb_clicked(bool checked)
{
    SruLogger::instance()->logText(
        QString("------------------[INFO] Display  2 %1-------------").arg(checked));

    if (checked) {
        uint8_t static value = 8;
        ui->Display_Card_Dial2->setEnabled(false);

        ui->DISPLAY_C1_pb->setEnabled(false);
        ui->DISPLAY_C2_pb->setEnabled(false);
        ui->DISPLAY_C3_pb->setEnabled(false);
        switch (value) {
        case 8: {
            ui->Display_Card_Dial2->setSliderPosition(8);
            value = 9;
            Timer_interrupt_Dial2->start(500);
            break;
        }
        case 9: {
            ui->Display_Card_Dial2->setSliderPosition(9);
            value = 10;
            break;
        }
        case 10: {
            ui->Display_Card_Dial2->setSliderPosition(10);
            value = 11;
            break;
        }
        case 11: {
            ui->Display_Card_Dial2->setSliderPosition(11);
            value = 12;
            break;
        }
        case 12: {
            ui->Display_Card_Dial2->setSliderPosition(12);
            value = 13;
            break;
        }
        case 13: {
            ui->Display_Card_Dial2->setSliderPosition(13);
            value = 14;
            break;
        }
        case 14: {
            ui->Display_Card_Dial2->setSliderPosition(14);
            value = 15;
            break;
        }
        case 15: {
            ui->Display_Card_Dial2->setSliderPosition(15);
            value = 0;
            break;
        }
        case 0: {
            ui->Display_Card_Dial2->setSliderPosition(0);
            value = 1;
            break;
        }
        case 1: {
            ui->Display_Card_Dial2->setSliderPosition(1);
            value = 2;
            break;
        }
        case 2: {
            ui->Display_Card_Dial2->setSliderPosition(2);
            value = 3;
            break;
        }
        case 3: {
            ui->Display_Card_Dial2->setSliderPosition(3);
            value = 4;
            break;
        }
        case 4: {
            ui->Display_Card_Dial2->setSliderPosition(4);
            value = 5;
            break;
        }
        case 5: {
            ui->Display_Card_Dial2->setSliderPosition(5);
            value = 6;
            break;
        }
        case 6: {
            ui->Display_Card_Dial2->setSliderPosition(6);
            value = 7;
            break;
        }
        case 7: {
            ui->Display_Card_Dial2->setSliderPosition(7);
            value = 16;
            break;
        }
        case 16: {
            ui->Display_Card_Dial2->setSliderPosition(8);
            value = 8;
            Timer_interrupt_Dial2->stop();
            ui->DISPLAY_C2_pb->setChecked(false);
            ui->DISPLAY_C2_pb->setEnabled(true);
            ui->DISPLAY_C1_pb->setEnabled(true);
            ui->DISPLAY_C3_pb->setEnabled(true);
            emit Display_Digit2(false);

            QMessageBox msgBox(
                QMessageBox::Question,
                "Display  2",
                "Press \"Yes\" if all the Digits from 0-F have been observed on the Second Digit "
                "of Display Module else press \"No\".",
                QMessageBox::Yes | QMessageBox::No,
                this);

            msgBox.setDefaultButton(QMessageBox::No);

            // Timer to close the box after 10 seconds as Cancel
            QTimer::singleShot(10000, &msgBox, [&msgBox]() {
                if (msgBox.isVisible()) {
                    msgBox.done(QMessageBox::Cancel);
                }
            });

            QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(
                msgBox.exec());

            if (reply == QMessageBox::Yes) {
                ui->DISPLAY_C2_pb->setStyleSheet(GBC);
                Display2 = "0-F";
                D2_Status = "PASS";
                SruLogger::instance()->logText("Display  2 Observed all the Digits from 0-F "
                                               "have been Display on the Second Digit");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_DISPLAY_C3_pb_clicked(1);
                }
            } else if (reply == QMessageBox::No) {
                ui->DISPLAY_C2_pb->setStyleSheet(RBC);
                Display2 = "NULL";
                D2_Status = "FAIL";
                SruLogger::instance()->logText("Display  2 Not Observed all the Digits from "
                                               "0-F on Display Panel of Second Digit");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_DISPLAY_C3_pb_clicked(1);
                }
            } else if (reply == QMessageBox::Cancel) {
                D2_Status = "------";
                Display2 = "Note: No Response from User, after the test has been completed.";
                SruLogger::instance()->logText(
                    "Display Card 2: User did not respond within 10s → Unable to do Test");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_DISPLAY_C3_pb_clicked(1);
                }
            }

            break;
        }
        default: {
            break;
        }
        }
    } else {
        emit Display_Digit2(checked);
        //        emit Display_Digit1(true);
        // emit Display_Digit3(true);
    }
}
void MainWindow::on_Display_Card_Dial2_valueChanged(int value)
{
    emit Display_Digit2(false);
    emit Display_Dial1((uint16_t) value);
    emit Display_Digit2(true);
}

void MainWindow::on_DISPLAY_C3_pb_clicked(bool checked)
{
    SruLogger::instance()->logText(
        QString("------------------[INFO] Display  3 %1-------------").arg(checked));

    //    emit Display_Digit1(false);
    //    emit Display_Digit2(false);
    if (checked) {
        uint8_t static value = 8;
        ui->Display_Card_Dial3->setEnabled(false);
        ui->DISPLAY_C1_pb->setEnabled(false);
        ui->DISPLAY_C2_pb->setEnabled(false);
        ui->DISPLAY_C3_pb->setEnabled(false);

        switch (value) {
        case 8: {
            ui->Display_Card_Dial3->setSliderPosition(8);
            value = 9;
            Timer_interrupt_Dial3->start(500);
            break;
        }
        case 9: {
            ui->Display_Card_Dial3->setSliderPosition(9);
            value = 10;
            break;
        }
        case 10: {
            ui->Display_Card_Dial3->setSliderPosition(10);
            value = 11;
            break;
        }
        case 11: {
            ui->Display_Card_Dial3->setSliderPosition(11);
            value = 12;
            break;
        }
        case 12: {
            ui->Display_Card_Dial3->setSliderPosition(12);
            value = 13;
            break;
        }
        case 13: {
            ui->Display_Card_Dial3->setSliderPosition(13);
            value = 14;
            break;
        }
        case 14: {
            ui->Display_Card_Dial3->setSliderPosition(14);
            value = 15;
            break;
        }
        case 15: {
            ui->Display_Card_Dial3->setSliderPosition(15);
            value = 0;
            break;
        }
        case 0: {
            ui->Display_Card_Dial3->setSliderPosition(0);
            value = 1;
            break;
        }
        case 1: {
            ui->Display_Card_Dial3->setSliderPosition(1);
            value = 2;
            break;
        }
        case 2: {
            ui->Display_Card_Dial3->setSliderPosition(2);
            value = 3;
            break;
        }
        case 3: {
            ui->Display_Card_Dial3->setSliderPosition(3);
            value = 4;
            break;
        }
        case 4: {
            ui->Display_Card_Dial3->setSliderPosition(4);
            value = 5;
            break;
        }
        case 5: {
            ui->Display_Card_Dial3->setSliderPosition(5);
            value = 6;
            break;
        }
        case 6: {
            ui->Display_Card_Dial3->setSliderPosition(6);

            value = 7;
            break;
        }
        case 7: {
            ui->Display_Card_Dial3->setSliderPosition(7);
            value = 16;
            break;
        }
        case 16: {
            ui->Display_Card_Dial3->setSliderPosition(8);
            value = 8;
            Timer_interrupt_Dial3->stop();
            ui->DISPLAY_C3_pb->setChecked(false);
            ui->DISPLAY_C3_pb->setEnabled(true);
            ui->DISPLAY_C2_pb->setEnabled(true);
            ui->DISPLAY_C1_pb->setEnabled(true);
            emit Display_Digit3(false);
            QMessageBox msgBox(
                QMessageBox::Question,
                "Display  3",
                "Press \"Yes\" if all the Digits from 0-F have been observed on the Third Digit "
                "of Display Module else press \"No\".",
                QMessageBox::Yes | QMessageBox::No,
                this);

            msgBox.setDefaultButton(QMessageBox::No);

            // Timer to close the box after 10 seconds as Cancel
            QTimer::singleShot(10000, &msgBox, [&msgBox]() {
                if (msgBox.isVisible()) {
                    msgBox.done(QMessageBox::Cancel);
                }
            });

            QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(
                msgBox.exec());

            if (reply == QMessageBox::Yes) {
                ui->DISPLAY_C3_pb->setStyleSheet(GBC);
                Display3 = "0-F";
                D3_Status = "PASS";
                SruLogger::instance()->logText("Display  3 Observed all the Digits from 0-F "
                                               "have been Display on the third Digit");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_SRU_DCDC_REPORT_clicked();
                }
            } else if (reply == QMessageBox::No) {
                ui->DISPLAY_C3_pb->setStyleSheet(RBC);
                Display3 = "NULL";
                D3_Status = "FAIL";
                SruLogger::instance()->logText("Display  3 Not Observed all the Digits from "
                                               "0-F on Display Panel of third Digit");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_SRU_DCDC_REPORT_clicked();
                }
            } else if (reply == QMessageBox::Cancel) {
                D3_Status = "------";
                Display3 = "Note: No Response from User, after the test has been completed.";
                SruLogger::instance()->logText(
                    "Display  3: User did not respond within 10s → Unable to do Test");
                if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                    on_SRU_DCDC_REPORT_clicked();
                }
            }

            break;
        }
        default: {
            break;
        }
        }
    } else {
        emit Display_Digit3(checked);
        //        emit Display_Digit1(true);
        //        emit Display_Digit2(true);
    }
}

void MainWindow::on_Display_Card_Dial3_valueChanged(int value)
{
    emit Display_Digit3(false);
    emit Display_Dial1((uint16_t) value);
    emit Display_Digit3(true);
}

void MainWindow::SRU_ADC_DAC_Loop_Back() {}

void MainWindow::USB_5856_Conn_Status(const QString &Devicename, int value, bool status)
{
    uint8_t static test1 = 0;
    uint8_t static test2 = 0;
    uint8_t static test3 = 0;
    uint8_t static test4 = 0;

    //    qDebug() << "USB_5856_Conn_Status" << Devicename << value << status;

    //    // ... inside a function or slot where you want to show the message
    //    QMessageBox *msgBox = new QMessageBox(
    //        this); // Parent widget can be 'this' if in a QWidget subclass
    //    msgBox->setWindowTitle(tr("Information"));
    //    msgBox->setText("This message will disappear in 3 seconds.");
    //    msgBox->setStandardButtons(QMessageBox::NoButton); // No buttons needed for auto-closing
    //    msgBox->show();

    //    QTimer::singleShot(1000, msgBox, &QMessageBox::hide); // 3000 milliseconds = 3 seconds

    if (const1 == 1) {
        const1 = 0;
    } else {
        if ((value == 0) && (status == false) && (test1 == 0)) {
            test1 = 1;
            usb5856_card1_success = value;

            QMessageBox::warning(this, "Not Connected", Devicename);
        }
        if ((value == 0) && (status == false) && (test2 == 0)) {
            test2 = 1;
            usb5856_card2_success = value;
            QMessageBox::warning(this, "Not Connected", Devicename);
        }
        if ((value == 0) && (status == false) && (test3 == 0)) {
            test3 = 1;
            usb5856_card3_success = value;
            QMessageBox::warning(this, "Not Connected", Devicename);
        }
        if ((value == 0) && (status == false) && (test4 == 0)) {
            test4 = 1;
            usb5856_card4_success = value;
            QMessageBox::warning(this, "Not Connected", Devicename);
        }
    }
}

void MainWindow::USB_5856_cards_status(
    int value1, int value2, int value3, int value4, const QString &devicename)

{
    usb5856_card1_success = value1;
    usb5856_card2_success = value2;
    usb5856_card3_success = value3;
    usb5856_card4_success = value4;

    const1 = 1;
    //    qDebug() << "USB_5856_cards_status" << value1 << value2 << value3 << value4 << devicename;
    QMessageBox::information(this, "USB-5856 Device Status at Startup:\n\n", devicename);
}

void MainWindow::USB_4716_cards_status(const QString &Dev_Info_4716)
{
    // qDebug() << "USB_4716_cards_status" << value1 << value2 << Dev_Info_4716;

    QMessageBox::information(this, "USB-4716 Device Status at Startup:\n\n", Dev_Info_4716);
}

//-------------DC_DC CARDS-------------------------------
void MainWindow::on_DC_DC_Card__DISP_PB_clicked(bool checked)
{
    if (checked) {
        ui->SRU_Start_pb->setStyleSheet("background-color:white;color:black");
        ui->CTRL_Card_PB->setChecked(false);
        ui->ControllerCard_GroupBox->setVisible(false);
        ui->DC_DC_GroupBox->setVisible(true);
        ui->DisplayCard_groupBox->setVisible(true);
        //        ui->DC_DC_Card__DISP_PB->setChecked(false);

        ui->DCDC_Manual_RB->setAutoExclusive(false);
        ui->DCDC_Manual_RB->setChecked(false);
        ui->DCDC_Manual_RB->setAutoExclusive(true);

        ui->DCDC_CTRL_Auto_RB->setAutoExclusive(false);
        ui->DCDC_CTRL_Auto_RB->setChecked(false);
        ui->DCDC_CTRL_Auto_RB->setAutoExclusive(true);

        ui->groupBox_26->setHidden(false);
        ui->groupBox_DCDC_drop_down->setHidden(false);

    } else {
        ui->ControllerCard_GroupBox->setVisible(true);
        ui->DC_DC_GroupBox->setVisible(false);
        ui->DisplayCard_groupBox->setVisible(false);
        //        ui->DC_DC_Card__DISP_PB->setChecked(true);
        // ui->groupBox_26->setHidden(true);
    }
}

void MainWindow::on_CTRL_Card_PB_clicked(bool checked)
{
    if (checked) {
        on_SRU_VoltagePB_toggled(false);

        ui->SRU_Start_pb->setStyleSheet("background-color:white;color:black");
        ui->DC_DC_Card__DISP_PB->setChecked(false);
        ui->DC_DC_GroupBox->setVisible(false);
        ui->DisplayCard_groupBox->setVisible(false);
        ui->ControllerCard_GroupBox->setVisible(true);

        ui->DCDC_Manual_RB->setAutoExclusive(false);
        ui->DCDC_Manual_RB->setChecked(false);
        ui->DCDC_Manual_RB->setAutoExclusive(true);

        ui->DCDC_CTRL_Auto_RB->setAutoExclusive(false);
        ui->DCDC_CTRL_Auto_RB->setChecked(false);
        ui->DCDC_CTRL_Auto_RB->setAutoExclusive(true);

        ui->SRU_Start_pb->setEnabled(true);
        ui->groupBox_26->setEnabled(true);
        ui->groupBox_26->setHidden(false);
        ui->groupBox_DCDC_drop_down->setHidden(true);

    } else {
        ui->DC_DC_GroupBox->setVisible(true);
        ui->DisplayCard_groupBox->setVisible(true);
        ui->ControllerCard_GroupBox->setVisible(false);
        //        ui->groupBox_26->setEnabled(false);
        //        ui->groupBox_26->setHidden(true);
    }
}

void MainWindow::setDCDC_TimerValue(uint8_t value)
{
    DCDC_TimerValue = value;
}
uint8_t MainWindow::getDCDC_TimerValue()
{
    return DCDC_TimerValue;
}

void MainWindow::on_SRU_Start_pb_toggled(bool checked)
{
    uint8_t l_voltageSetFlag = 0;
    if (checked) {
        ui->ControllerCard_GroupBox->setEnabled(true);
        // power off voltage in DCDC
        ui->SRU_Start_pb->setStyleSheet(YBC);
        Bittest_flag = true;
        isFirstADCTrigger = true;
        if (ui->CTRL_Card_PB->isChecked()) {
            ADC_BitTestTim->setInterval(1); // Initial delay
            ADC_BitTestTim->start();        // Will fire after 100ms
            if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                on_SRU_CTRL_Volt_pb_clicked(true);
            }
        }
        ui->SRU_Start_pb->setText("STOP");
        ui->SRU_Volts_CB->setDisabled(true);
        ui->SRU_VoltagePB->setDisabled(true);
        if (ui->DC_DC_Card__DISP_PB->isChecked()) {
            uint8_t PS7_voltages = ui->Volt_28_16_32_Cmb->currentIndex();
            if (PS7_voltages == 1) {
                if (g_Direct_Monitor.Input_Ch6_16 >= 14) {
                    l_voltageSetFlag = 1;
                }
            } else if (PS7_voltages == 2) {
                if (g_Direct_Monitor.Input_Ch6_28 >= 27) {
                    l_voltageSetFlag = 1;
                }
            } else if (PS7_voltages == 3) {
                if (g_Direct_Monitor.Input_Ch6_32 >= 31) {
                    l_voltageSetFlag = 1;
                }
            } else if (PS7_voltages == 3) {
                if (g_Direct_Monitor.Input_ch6_Ext >= 14) {
                    l_voltageSetFlag = 1;
                }
            }

            if (l_voltageSetFlag == 1) {
                l_voltageSetFlag = 0;

                ui->displaycard_groupBox->setEnabled(true);
                ui->groupBox_135->setEnabled(true);
                ui->groupBox_138->setEnabled(true);

                //--------------------------------
                ui->plus5_groupBox->setEnabled(true);
                ui->minus5_groupBox->setEnabled(true);
                ui->groupBox_3P3->setEnabled(true);
                ui->displaycard_groupBox->setEnabled(true);
                ui->SRU_CTRL_Volt_pb->setEnabled(true);
                ui->USB_port->setEnabled(true);

                //            ui->groupBox_rotary_switch_test->setEnabled(true);
                //            ui->groupBox_rs422_loopback->setEnabled(true);
                //            ui->groupBox_abort_readyinit_prep->setEnabled(true);
                //            ui->groupBox_external_flash->setEnabled(true);
                //            ui->displaycard_groupBox->setEnabled(true);
                //            ui->SRU_DCDC_REPORT->setEnabled(true);
                //            ui->SRU_CntrlCard_Report->setEnabled(true);
                //            ui->groupBox_dip_dop_loopback->setEnabled(true);
                //-------------------------------------------------------------

                if (ui->DC_DC_Card__DISP_PB->isChecked()) {
                    Timer_SRU_DC_DC->start(1);
                    //            setDCDC_TimerValue(1);
                    on_SRU_DC_5V_IV_PB_clicked(true);
                }

                ui->SRU_Start_pb->setText("STOP");
                ui->SRU_Volts_CB->setDisabled(true);
                ui->SRU_VoltagePB->setDisabled(true);
            } else {
                QMessageBox::warning(this, "Switch ON Power Supply", "NULL");
            }
        }
    } else {
        Bittest_flag = false;
        ADC_BitTestTim->stop();
        Timer_SRU_DC_DC->stop();
        ui->SRU_Start_pb->setText("START");
        ui->SRU_Volts_CB->setEnabled(true);
        ui->SRU_VoltagePB->setEnabled(true);
        on_SRU_DC_5V_IV_PB_clicked(false);
        on_SRU_DC_3p3V_IV_PB_clicked(false);
        Volage_5V_Combine(false);
        on_SRU_DC_5V_L10_PB_clicked(false);
        on_SRU_DC_N_5V_L10_PB_clicked(false);
        Volage_5V_L100_Combine(false);
        on_SRU_DC_5V_L100_PB_clicked(false);
        on_SRU_DC_N_5V_L100_PB_clicked(false);
        on_SRU_DC_3p3V_L10_PB_clicked(false);
        on_SRU_DC_3p3V_L100_PB_clicked(false);
        //-----CTRL off commands
        if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
            on_SRU_CTRL_Volt_pb_clicked(false);
        }
    }
}

void MainWindow::on_SRU_DC_5V_IV_PB_clicked(bool checked)
{
    if (checked) {
        on_SRU_DC_N_5V_IV_PB_clicked(false);
        on_SRU_DC_3p3V_IV_PB_clicked(false);
        ui->SRU_DC_N_5V_IV_PB->setChecked(false);
        ui->SRU_DC_3p3V_IV_PB->setChecked(false);
        setDCDC_TimerValue(1);
        emit DC_DC_5_LED_Ripple(checked);
        if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
            ui->SRU_DC_5V_IV_PB->setChecked(false);
            if (g_time_out_state != RIPPLE_P5V_DELAY) {
                g_time_out_flag = 0;
                TimeOutTimer->start(4000);
                g_time_out_state = RIPPLE_P5V_DELAY;
                g_time_out_flag = 1;
            }
        }
    } else {
        emit DC_DC_5_LED_Ripple(checked);
        setDCDC_TimerValue(1);
    }
}
void MainWindow::on_SRU_DC_N_5V_IV_PB_clicked(bool checked)
{
    if (checked) {
        ui->SRU_DC_5V_L100_PB->setChecked(false);
        on_SRU_DC_3p3V_IV_PB_clicked(false);
        ui->SRU_DC_3p3V_IV_PB->setChecked(false);
        on_SRU_DC_5V_IV_PB_clicked(false);
        ui->SRU_DC_5V_IV_PB->setChecked(false);

        ui->SRU_DC_3p3V_L100_PB->setChecked(false);
        ui->SRU_DC_3p3V_L10_PB->setChecked(false);
        setDCDC_TimerValue(4);
        emit DC_DC_N_5_LED_Ripple(checked);

        if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
            if (g_time_out_state != RIPPLE_N5V_DELAY) {
                g_time_out_flag = 0;
                TimeOutTimer->start(4000);
                g_time_out_state = RIPPLE_N5V_DELAY;
                g_time_out_flag = 1;
            }
        }
    } else {
        emit DC_DC_N_5_LED_Ripple(checked);
        emit DC_DC_5_LED_Ripple(checked);
        setDCDC_TimerValue(4);
    }
}
void MainWindow::on_SRU_DC_3p3V_IV_PB_clicked(bool checked)
{
    if (checked) {
        on_SRU_DC_N_5V_IV_PB_clicked(false);
        ui->SRU_DC_N_5V_IV_PB->setChecked(false);
        on_SRU_DC_5V_IV_PB_clicked(false);
        ui->SRU_DC_5V_IV_PB->setChecked(false);

        ui->SRU_DC_N_5V_L100_PB->setChecked(false);
        ui->SRU_DC_5V_L100_PB->setChecked(false);
        ui->SRU_DC_N_5V_L10_PB->setChecked(false);
        ui->SRU_DC_5V_L10_PB->setChecked(false);
        setDCDC_TimerValue(7);
        emit DC_DC_3p3_LED_Ripple(checked);

        if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
            if (g_time_out_state != RIPPLE_P3P3V_DELAY) {
                g_time_out_flag = 0;
                TimeOutTimer->start(4000);
                g_time_out_state = RIPPLE_P3P3V_DELAY;
                g_time_out_flag = 1;
            }
            ui->IV_3p3V_Current_le->setText(QString::number(g_CurrentSensorData.curr_DC3p3, 'f', 4));
            //         emit DC_DC_3p3_SRU();
            ui->IV_3p3_Volt_le->setText(QString::number(g_Direct_Monitor.Input_Ch13));
        }
    } else {
        emit DC_DC_3p3_LED_Ripple(checked);
        setDCDC_TimerValue(7);
    }
}
//-------------------------------------------------------------

void MainWindow::Volage_5V_Combine(bool checked)
{
    if (checked) {
        g_Time_counter.seconds = 10;
        g_Time_counter.minutes = 0;
        on_SRU_DC_5V_IV_PB_clicked(false);
        ui->SRU_DC_5V_IV_PB->setChecked(false);
        on_SRU_DC_5V_L100_PB_clicked(false);
        ui->SRU_DC_5V_L100_PB->setChecked(false);
        on_SRU_DC_N_5V_IV_PB_clicked(false);
        ui->SRU_DC_N_5V_IV_PB->setChecked(false);
        on_SRU_DC_N_5V_L100_PB_clicked(false);
        ui->SRU_DC_N_5V_L100_PB->setChecked(false);
        QThread::msleep(100);
        emit DC_DC_5_L_10PER(checked);
        emit DC_DC_N_5_L_10PER(checked);
        QThread::msleep(3000);
        setDCDC_TimerValue(2);
    } else {
        emit DC_DC_5_L_10PER(checked);
        emit DC_DC_N_5_L_10PER(checked);
    }
}
void MainWindow::on_SRU_DC_5V_L10_PB_clicked(bool checked)
{
    Volage_5V_Combine(checked);

    // ui->SRU_DC_5V_IV_PB->setChecked(false);
}

void MainWindow::on_SRU_DC_N_5V_L10_PB_clicked(bool checked)
{
    Volage_5V_Combine(checked);

    //    if (checked) {
    //        g_Time_counter.seconds = 10;
    //        g_Time_counter.minutes = 0;
    //        on_SRU_DC_N_5V_IV_PB_clicked(false);
    //        on_SRU_DC_N_5V_L100_PB_clicked(false);
    //        QThread::msleep(100);
    //        setDCDC_TimerValue(5);
    //        emit DC_DC_N_5_L_10PER(checked);
    //    } else {
    //        emit DC_DC_N_5_L_10PER(checked);
    //    }
}
//----------------------------------------------------------------

void MainWindow::Volage_5V_L100_Combine(bool checked)
{
    if (checked) {
        g_Time_counter.seconds = 10;
        g_Time_counter.minutes = 0;

        on_SRU_DC_5V_IV_PB_clicked(false);
        ui->SRU_DC_5V_IV_PB->setChecked(false);
        on_SRU_DC_5V_L10_PB_clicked(false);
        ui->SRU_DC_5V_L10_PB->setChecked(false);
        on_SRU_DC_N_5V_IV_PB_clicked(false);
        ui->SRU_DC_N_5V_IV_PB->setChecked(false);
        on_SRU_DC_N_5V_L10_PB_clicked(false);
        ui->SRU_DC_N_5V_L10_PB->setChecked(false);
        QThread::msleep(100);
        emit DC_DC_5_L_100PER(checked);
        emit DC_DC_N_5_L_100PER(checked);
        QThread::msleep(3000);
        setDCDC_TimerValue(3);
    } else {
        emit DC_DC_5_L_100PER(checked);
        emit DC_DC_N_5_L_100PER(checked);
    }
}
void MainWindow::on_SRU_DC_5V_L100_PB_clicked(bool checked)
{
    Volage_5V_L100_Combine(checked);

    //    if (checked) {
    //        g_Time_counter.seconds = 10;
    //        g_Time_counter.minutes = 2;

    //        on_SRU_DC_5V_IV_PB_clicked(false);
    //        on_SRU_DC_5V_L10_PB_clicked(false);
    //        setDCDC_TimerValue(3);
    //        QThread::msleep(100);
    //        emit DC_DC_5_L_100PER(checked);
    //    } else {
    //        emit DC_DC_5_L_100PER(checked);
    //    }
}

void MainWindow::on_SRU_DC_N_5V_L100_PB_clicked(bool checked)
{
    Volage_5V_L100_Combine(checked);

    //    if (checked) {
    //        g_Time_counter.seconds = 10;
    //        g_Time_counter.minutes = 0;
    //        on_SRU_DC_N_5V_IV_PB_clicked(false);
    //        on_SRU_DC_N_5V_L10_PB_clicked(false);
    //        QThread::msleep(100);
    //        emit DC_DC_N_5_L_100PER(checked);
    //        setDCDC_TimerValue(6);
    //    } else {
    //        emit DC_DC_N_5_L_100PER(checked);
    //    }
}

void MainWindow::on_SRU_DC_3p3V_L10_PB_clicked(bool checked)
{
    if (checked) {
        g_Time_counter.seconds = 10;
        g_Time_counter.minutes = 0;
        on_SRU_DC_3p3V_IV_PB_clicked(false);
        ui->SRU_DC_3p3V_IV_PB->setChecked(false);
        on_SRU_DC_3p3V_L100_PB_clicked(false);
        ui->SRU_DC_3p3V_L100_PB->setChecked(false);
        QThread::msleep(100);
        emit DC_DC_3p3_L_10PER(checked);
        QThread::msleep(3000);
        setDCDC_TimerValue(8);

    } else {
        emit DC_DC_3p3_L_10PER(checked);
    }
}

void MainWindow::on_SRU_DC_3p3V_L100_PB_clicked(bool checked)
{
    if (checked) {
        g_Time_counter.seconds = 10;
        g_Time_counter.minutes = 0;
        on_SRU_DC_3p3V_IV_PB_clicked(false);
        ui->SRU_DC_3p3V_IV_PB->setChecked(false);
        on_SRU_DC_3p3V_L10_PB_clicked(false);
        ui->SRU_DC_3p3V_L10_PB->setChecked(false);
        QThread::msleep(100);
        emit DC_DC_3p3_L_100PER(checked);
        QThread::msleep(3000);
        setDCDC_TimerValue(9);

    } else {
        emit DC_DC_3p3_L_100PER(checked);
        ui->SRU_DC_3p3V_L100_PB->setChecked(false);
        ui->SRU_DC_3p3V_L100_PB->setChecked(false);
    }
}
void MainWindow::SRU_DC_DC_TimerUpdate()
{
    emit DC_DC_5_SRU();
    emit DC_DC_N_5_SRU();
    emit DC_DC_3p3_SRU();
    //    qDebug() << "1";
    static uint16_t l_counter = 0;
    if (l_counter == 2000) {
        //        qDebug() << "2";
        l_counter = 0;
        //static double arr = NULL;
        switch (getDCDC_TimerValue()) {
        case 1: {
            //            qDebug() << "3";
            ui->IV_5V_Current_le->setText(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4));
            ui->IV_5Volt_le->setText(QString::number(g_Direct_Monitor.Input_Ch14));
            ui->IV_N_5V_Current_le->setText(QString::number(g_CurrentSensorData.curr_DCn5V, 'f', 4));
            //            emit DC_DC_N_5_SRU();
            ui->IV_N_5Volt_le->setText(QString::number(g_Direct_Monitor.Input_Ch15));
            ui->IV_5V_Current_le->setText(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4));
            ui->IV_5Volt_le->setText(QString::number(g_Direct_Monitor.Input_Ch14));
            if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                //                ui->SRU_DC_5V_IV_PB->setChecked(true);
                //                on_SRU_DC_5V_IV_PB_clicked(true); //Initial
            }
            break;
        }
        case 2: {
            if (g_Time_counter.seconds == 0) {
                if (g_Time_counter.minutes != 0) {
                    g_Time_counter.minutes--;
                    g_Time_counter.seconds = 60;
                } else if ((g_Time_counter.minutes == 0) && (g_Time_counter.seconds == 0)) {
                    on_SRU_DC_5V_L10_PB_clicked(false);
                    on_SRU_DC_5V_IV_PB_clicked(false);
                    on_SRU_DC_N_5V_L10_PB_clicked(false);
                    on_SRU_DC_N_5V_IV_PB_clicked(false);
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        on_SRU_DC_5V_L100_PB_clicked(1);
                    }
                }
            } else {
                if (g_Time_counter.seconds != 0) {
                    g_Time_counter.seconds--;
                }
                ui->txt_countdown_5V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                              + QString::number(g_Time_counter.seconds, 10));
                ui->txt_countdown_N_5V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                                + QString::number(g_Time_counter.seconds, 10));
            }
            ui->Load10_5v_I_le->setText(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4));
            ui->Load10_minus5v_I_le->setText(
                QString::number(g_CurrentSensorData.curr_DCn5V, 'f', 4));

            float fixedI_val5V = 0.1, diffI_5V = 0.0; //0.1A ±0.050A
            //        float valI5V = ui->Load10_5v_I_le->text().toFloat();
            //        diffI_5V = valI5V - fixedI_val5V;

            diffI_5V = g_CurrentSensorData.curr_DCp5V - fixedI_val5V;

            if ((diffI_5V >= -(0.100)) && (diffI_5V <= (0.100))) {
                L10_I5V = "PASS";
                ui->Load10_5v_I_Result_le->setText("PASS");
                ui->Load10_5v_I_Result_le->setStyleSheet("color:black; background-color:green");
            } else {
                L10_I5V = "FAIL";
                ui->Load10_5v_I_Result_le->setText("FAIL");
                ui->Load10_5v_I_Result_le->setStyleSheet("color:black; background-color:red");
            }
            //-------------------------------------------------------------------
            float fixedI_valN5V = 0.1, diffI_N5V = 0.0; //0.1A ±0.050A
            //            float valIN5V = ui->Load10_minus5v_I_le->text().toFloat();
            diffI_N5V = g_CurrentSensorData.curr_DCn5V - fixedI_valN5V;
            if ((diffI_N5V >= -(0.100)) && (diffI_N5V <= (0.100))) {
                L10_IN5V = "PASS";
                ui->Load10_N5v_Current_Result_le->setText("PASS");
                ui->Load10_N5v_Current_Result_le->setStyleSheet(
                    "color:black;background-color:green");
            } else {
                L10_IN5V = "FAIL";
                ui->Load10_N5v_Current_Result_le->setText("FAIL");
                ui->Load10_N5v_Current_Result_le->setStyleSheet("color:black;background-color:red");
            }
            //-------------------------------------------------------------------------------------
            //            emit DC_DC_5_SRU();
            ui->Load10_5V_le->setText(QString::number(g_Direct_Monitor.Input_Ch14));
            float Load10_5v = 5.3, L_5V = 0.0;
            //        float L10_5V = ui->Load10_5V_le->text().toFloat();
            //        L_5V = L10_5V - Load10_5v;
            L_5V = g_Direct_Monitor.Input_Ch14 - Load10_5v;
            if ((L_5V >= -(0.125)) && (L_5V <= (0.125))) {
                DC_L10_5V = "PASS";
                ui->Load10_5V_Result_le->setText("PASS");
                ui->Load10_5V_Result_le->setStyleSheet("color:black; background-color:green");
            } else {
                DC_L10_5V = "FAIL";
                ui->Load10_5V_Result_le->setText("FAIL");
                ui->Load10_5V_Result_le->setStyleSheet("color: black; background-color:red");
            }
            SruLogger::instance()->logText(QString("SRU DCDC Load10 5V Voltage:%1 Result:%2")
                                               .arg(QString::number(g_Direct_Monitor.Input_Ch14))
                                               .arg(ui->Load10_5V_Result_le->text()));
            SruLogger::instance()->logText(
                QString("SRU DCDC Load10 5V Current:%1 Result:%2")
                    .arg(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4))
                    .arg(ui->Load10_5v_I_Result_le->text()));

            //--------------------
            ui->Load10_minus5V_le->setText(QString::number(g_Direct_Monitor.Input_Ch15));
            //-5.3V±0.125V
            float Load10_N5v = -5.3, L_N5V = 0.0;
            //        float L10_N5V = ui->Load10_minus5V_le->text().toFloat();
            //        L_N5V = L10_N5V - Load10_N5v;
            L_N5V = g_Direct_Monitor.Input_Ch15 - Load10_N5v;
            if ((L_N5V >= -(0.125)) && (L_N5V <= (0.125))) {
                DC_L10_N5V = "PASS";
                ui->Load10_minus5v_result_le->setText("PASS");
                ui->Load10_minus5v_result_le->setStyleSheet("color:black; background-color:green");
            } else {
                DC_L10_N5V = "FAIL";
                ui->Load10_minus5v_result_le->setText("FAIL");
                ui->Load10_minus5v_result_le->setStyleSheet("color: black; background-color:red");
            }

            SruLogger::instance()->logText(
                QString("SRU DCDC Load10 Negative 5Volts Voltage:%1 Result:%2")
                    .arg(QString::number(g_Direct_Monitor.Input_Ch15))
                    .arg(ui->Load10_minus5v_result_le->text()));

            //            SruLogger::instance()->logText(
            //                QString("SRU DCDC Load10 Negative 5Volts Current:%1 Result:%2")
            //                    .arg(QString::number(arr / (float) 0.03768, 'f', 4))
            //                    .arg(ui->Load10_N5v_Current_Result_le->text()));
            break;
        }
        case 3: {
            if (g_Time_counter.seconds == 0) {
                if (g_Time_counter.minutes != 0) {
                    g_Time_counter.minutes--;
                    g_Time_counter.seconds = 60;
                } else if ((g_Time_counter.minutes == 0) && (g_Time_counter.seconds == 0)) {
                    on_SRU_DC_5V_L100_PB_clicked(false);
                    on_SRU_DC_5V_IV_PB_clicked(false);
                    on_SRU_DC_N_5V_L100_PB_clicked(false);
                    on_SRU_DC_N_5V_IV_PB_clicked(false);
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        on_SRU_DC_3p3V_IV_PB_clicked(true);
                    }
                }
            } else {
                if (g_Time_counter.seconds != 0) {
                    g_Time_counter.seconds--;
                }
            }

            ui->txt_countdown_5V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                          + QString::number(g_Time_counter.seconds, 10));
            ui->txt_countdown_N_5V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                            + QString::number(g_Time_counter.seconds, 10));

            ui->Load100_5v_I_op_le->setText(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4));

            //1A ±0.100A
            float fixedI100_val5V = 1.0, diffI100_5V = 0.0;
            // float I100_5V = ui->Load100_5v_I_op_le->text().toFloat(); //-------check
            //diffI100_5V = I100_5V - fixedI100_val5V;
            diffI100_5V = g_CurrentSensorData.curr_DCp5V - fixedI100_val5V;
            if ((diffI100_5V >= -(0.100)) && (diffI100_5V <= (0.100))) {
                L100_I5V = "PASS";
                ui->Load100_5v_I_Result->setText("PASS");
                ui->Load100_5v_I_Result->setStyleSheet("color:black;background-color:green");
            } else {
                L100_I5V = "FAIL";
                ui->Load100_5v_I_Result->setText("FAIL");
                ui->Load100_5v_I_Result->setStyleSheet("color:black;background-color:red");
            }
            //            emit DC_DC_5_SRU();
            ui->Load100_5V_le->setText(QString::number(g_Direct_Monitor.Input_Ch14));

            float fixedL100_5v = 5.0, diffL100_5V = 0.0;
            //        float valL100_5V = ui->Load100_5V_le->text().toFloat();
            //        diffL100_5V = valL100_5V - fixedL100_5v;
            diffL100_5V = g_Direct_Monitor.Input_Ch14 - fixedL100_5v;
            if ((diffL100_5V >= -(0.125)) && (diffL100_5V <= (0.125))) {
                DC_L100_5V = "PASS";
                ui->Load100_5V_Result->setText("PASS");
                ui->Load100_5V_Result->setStyleSheet("color:black; background-color:green");
            } else {
                DC_L100_5V = "FAIL";
                ui->Load100_5V_Result->setText("FAIL");
                ui->Load100_5V_Result->setStyleSheet("color: black; background-color:red");
            }

            SruLogger::instance()->logText(QString("SRU DCDC Load100 5V Voltage:%1 Result:%2")
                                               .arg(QString::number(g_Direct_Monitor.Input_Ch14))
                                               .arg(ui->Load100_5V_Result->text()));
            SruLogger::instance()->logText(
                QString("SRU DCDC Load100 5V Current:%1 Result:%2")
                    .arg(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4))
                    .arg(ui->Load100_5v_I_Result->text()));

            //----------------------------------------------------------
            ui->Load100_N_5v_I_op_le->setText(
                QString::number(g_CurrentSensorData.curr_DCn5V, 'f', 4));

            float fixedI_valN5V = 1.0, diffI_N5V = 0.0; //1A ±0.100A
            //            float valIN5V = ui->Load100_N_5v_I_op_le->text().toFloat(); //---check
            diffI_N5V = g_CurrentSensorData.curr_DCn5V - fixedI_valN5V;
            if ((diffI_N5V >= -(0.100)) && (diffI_N5V <= (0.100))) {
                L100_IN5V = "PASS";
                ui->Load100_N_5V_I_Result->setText("PASS");
                ui->Load100_N_5V_I_Result->setStyleSheet("color:black;background-color:green");
            } else {
                L100_IN5V = "FAIL";
                ui->Load100_N_5V_I_Result->setText("FAIL");
                ui->Load100_N_5V_I_Result->setStyleSheet("color:black;background-color:red");
            }

            ui->Load100_N_5V_le->setText(QString::number(g_Direct_Monitor.Input_Ch15));

            float fixedL100_N5v = -5.0, diffL100_N5V = 0.0;
            //float valL100_N5V = ui->Load100_N_5V_le->text().toFloat();
            //        diffL100_N5V = valL100_N5V - fixedL100_N5v;
            diffL100_N5V = g_Direct_Monitor.Input_Ch15 - fixedL100_N5v;
            if ((diffL100_N5V >= -(0.125)) && (diffL100_N5V <= (0.125))) {
                DC_L100_N5V = "PASS";
                ui->Load100_N_5v_Result->setText("PASS");
                ui->Load100_N_5v_Result->setStyleSheet("color:black; background-color:green");
            } else {
                DC_L100_N5V = "FAIL";
                ui->Load100_N_5v_Result->setText("FAIL");
                ui->Load100_N_5v_Result->setStyleSheet("color: black; background-color:red");
            }
            SruLogger::instance()->logText(
                QString("SRU DCDC Load100 Negative 5Volts Voltage:%1 Result:%2")
                    .arg(QString::number(g_Direct_Monitor.Input_Ch15))
                    .arg(ui->Load100_N_5v_Result->text()));

            //            SruLogger::instance()->logText(
            //                QString("SRU DCDC Load100 Negative 5Volts Current:%1 Result:%2")
            //                    .arg(QString::number(arr / (float) 0.03768, 'f', 4))
            //                    .arg(ui->Load100_N_5V_I_Result->text()));

            break;
        }
        case 4: {
            ui->IV_N_5V_Current_le->setText(QString::number(g_CurrentSensorData.curr_DCn5V, 'f', 4));
            //            emit DC_DC_N_5_SRU();
            ui->IV_N_5Volt_le->setText(QString::number(g_Direct_Monitor.Input_Ch15));
            ui->IV_5V_Current_le->setText(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4));
            ui->IV_5Volt_le->setText(QString::number(g_Direct_Monitor.Input_Ch14));
            break;
        }
        case 5: {
            if (g_Time_counter.seconds == 0) {
                if (g_Time_counter.minutes != 0) {
                    g_Time_counter.minutes--;
                    g_Time_counter.seconds = 60;
                } else if ((g_Time_counter.minutes == 0) && (g_Time_counter.seconds == 0)) {
                    on_SRU_DC_N_5V_L10_PB_clicked(false);
                    on_SRU_DC_N_5V_IV_PB_clicked(false);
                }
            } else {
                if (g_Time_counter.seconds != 0) {
                    g_Time_counter.seconds--;
                }
                ui->txt_countdown_N_5V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                                + QString::number(g_Time_counter.seconds, 10));
            }
            //            emit DC_DC_N_5_Differential(&arr);
            //             ui->Load10_5v_I_le->setText(QString::number(g_CurrentSensorData.curr_DCp5V, 'f', 4));
            ui->Load10_minus5v_I_le->setText(
                QString::number(g_CurrentSensorData.curr_DCn5V, 'f', 4));
            //            ui->Load10_minus5v_I_le->setText(QString::number(arr / (float) 0.03768, 'f', 4));

            float fixedI_valN5V = 0.1, diffI_N5V = 0.0; //0.1A ±0.050A
            float valIN5V = ui->Load10_minus5v_I_le->text().toFloat();
            diffI_N5V = valIN5V - fixedI_valN5V;
            if ((diffI_N5V >= -(0.100)) && (diffI_N5V <= (0.100))) {
                L10_IN5V = "PASS";
                ui->Load10_N5v_Current_Result_le->setText("PASS");
                ui->Load10_N5v_Current_Result_le->setStyleSheet(
                    "color:black;background-color:green");
            } else {
                L10_IN5V = "FAIL";
                ui->Load10_N5v_Current_Result_le->setText("FAIL");
                ui->Load10_N5v_Current_Result_le->setStyleSheet("color:black;background-color:red");
            }

            //            emit DC_DC_N_5_SRU();
            ui->Load10_minus5V_le->setText(QString::number(g_Direct_Monitor.Input_Ch15));
            //-5V±200mV
            float Load10_N5v = 5.0, L_N5V = 0.0;
            //        float L10_N5V = ui->Load10_minus5V_le->text().toFloat();
            //        L_N5V = L10_N5V - Load10_N5v;
            L_N5V = g_Direct_Monitor.Input_Ch15 - Load10_N5v;
            if ((L_N5V >= -(0.20)) && (L_N5V <= (0.20))) {
                DC_L10_N5V = "PASS";
                ui->Load10_minus5v_result_le->setText("PASS");
                ui->Load10_minus5v_result_le->setStyleSheet("color:green; background-color:white");
            } else {
                DC_L10_N5V = "FAIL";
                ui->Load10_minus5v_result_le->setText("FAIL");
                ui->Load10_minus5v_result_le->setStyleSheet("color: red; background-color:white");
            }
            SruLogger::instance()->logText(
                QString("SRU DCDC Load10 Negative 5Volts Voltage:%1 Result:%2")
                    .arg(QString::number(g_Direct_Monitor.Input_Ch15))
                    .arg(ui->Load10_minus5v_result_le->text()));

            //            SruLogger::instance()->logText(
            //                QString("SRU DCDC Load10 Negative 5Volts Current:%1 Result:%2")
            //                    .arg(QString::number(arr / (float) 0.03768, 'f', 4))
            //                    .arg(ui->Load10_N5v_Current_Result_le->text()));
            break;
        }
        case 6: {
            if (g_Time_counter.seconds == 0) {
                if (g_Time_counter.minutes != 0) {
                    g_Time_counter.minutes--;
                    g_Time_counter.seconds = 60;
                } else if ((g_Time_counter.minutes == 0) && (g_Time_counter.seconds == 0)) {
                    on_SRU_DC_N_5V_L100_PB_clicked(false);
                    on_SRU_DC_N_5V_IV_PB_clicked(false);
                }
            } else {
                if (g_Time_counter.seconds != 0) {
                    g_Time_counter.seconds--;
                }
            }

            ui->txt_countdown_N_5V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                            + QString::number(g_Time_counter.seconds, 10));
            //            emit DC_DC_N_5_Differential(&arr);
            //            ui->Load100_N_5v_I_op_le->setText(QString::number(arr / (float) 0.03768, 'f', 4));

            ui->Load100_N_5v_I_op_le->setText(
                QString::number(g_CurrentSensorData.curr_DCn5V, 'f', 4));
            float fixedI_valN5V = 1, diffI_N5V = 0.0;                   //1A ±0.100A
            float valIN5V = ui->Load100_N_5v_I_op_le->text().toFloat(); //---check
            diffI_N5V = valIN5V - fixedI_valN5V;
            if ((diffI_N5V >= -(0.100)) && (diffI_N5V <= (0.100))) {
                L100_IN5V = "PASS";
                ui->Load100_N_5V_I_Result->setText("PASS");
                ui->Load100_N_5V_I_Result->setStyleSheet("color:black;background-color:green");
            } else {
                L100_IN5V = "FAIL";
                ui->Load100_N_5V_I_Result->setText("FAIL");
                ui->Load100_N_5V_I_Result->setStyleSheet("color:black;background-color:red");
            }

            //            emit DC_DC_N_5_SRU();
            ui->Load100_N_5V_le->setText(QString::number(g_Direct_Monitor.Input_Ch15));

            float fixedL100_N5v = 5.0, diffL100_N5V = 0.0;
            //float valL100_N5V = ui->Load100_N_5V_le->text().toFloat();
            //        diffL100_N5V = valL100_N5V - fixedL100_N5v;
            diffL100_N5V = g_Direct_Monitor.Input_Ch15 - fixedL100_N5v;
            if ((diffL100_N5V >= -(0.20)) && (diffL100_N5V <= (0.20))) {
                DC_L100_N5V = "PASS";
                ui->Load100_N_5v_Result->setText("PASS");
                ui->Load100_N_5v_Result->setStyleSheet("color:green; background-color:white");
            } else {
                DC_L100_N5V = "FAIL";
                ui->Load100_N_5v_Result->setText("FAIL");
                ui->Load100_N_5v_Result->setStyleSheet("color: red; background-color:white");
            }
            SruLogger::instance()->logText(
                QString("SRU DCDC Load100 Negative 5Volts Voltage:%1 Result:%2")
                    .arg(QString::number(g_Direct_Monitor.Input_Ch15))
                    .arg(ui->Load100_N_5v_Result->text()));

            //            SruLogger::instance()->logText(
            //                QString("SRU DCDC Load100 Negative 5Volts Current:%1 Result:%2")
            //                    .arg(QString::number(arr / (float) 0.03768, 'f', 4))
            //                    .arg(ui->Load100_N_5V_I_Result->text()));
            break;
        }
        case 7: {
            //            qDebug() << "Case 7";
            ui->IV_3p3V_Current_le->setText(QString::number(g_CurrentSensorData.curr_DC3p3, 'f', 4));
            //         emit DC_DC_3p3_SRU();
            ui->IV_3p3_Volt_le->setText(QString::number(g_Direct_Monitor.Input_Ch13));

            break;
        }
        case 8: {
            if (g_Time_counter.seconds == 0) {
                if (g_Time_counter.minutes != 0) {
                    g_Time_counter.minutes--;
                    g_Time_counter.seconds = 60;
                } else if ((g_Time_counter.minutes == 0) && (g_Time_counter.seconds == 0)) {
                    on_SRU_DC_3p3V_L10_PB_clicked(false);
                    on_SRU_DC_3p3V_IV_PB_clicked(false);
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        on_SRU_DC_3p3V_L100_PB_clicked(1);
                    }
                }
            } else {
                if (g_Time_counter.seconds != 0) {
                    g_Time_counter.seconds--;
                }
                ui->txt_countdown_3p3V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                                + QString::number(g_Time_counter.seconds, 10));
            }
            ui->Load10_3_3v_Current_le->setText(
                QString::number(g_CurrentSensorData.curr_DC3p3, 'f', 4));

            float fixedI_3p3V = 0.2, diffI_3p3V = 0.0; //0.2A ±0.060A
            //        float I_3p3V = ui->Load10_3_3v_Current_le->text().toFloat();
            //        diffI_3p3V = I_3p3V - fixedI_3p3V;
            diffI_3p3V = g_CurrentSensorData.curr_DC3p3 - fixedI_3p3V;
            if ((diffI_3p3V >= -(0.100)) && (diffI_3p3V <= (0.100))) {
                L10_I3p3V = "PASS";
                ui->Load10_3_3v_I_Result->setText("PASS");
                ui->Load10_3_3v_I_Result->setStyleSheet("color:black;background-color:green");
            } else {
                L10_I3p3V = "FAIL";
                ui->Load10_3_3v_I_Result->setText("FAIL");
                ui->Load10_3_3v_I_Result->setStyleSheet("color:black;background-color:red");
            }
            //            emit DC_DC_3p3_SRU();
            ui->Load10_3_3V_le->setText(QString::number(g_Direct_Monitor.Input_Ch13));

            //3.3V±200mV
            float Load10_3p3v = 3.6, L_3p3V = 0.0;
            //        float L10_3p3V = ui->Load10_3_3V_le->text().toFloat();
            //        L_3p3V = L10_3p3V - Load10_3p3v;
            L_3p3V = g_Direct_Monitor.Input_Ch13 - Load10_3p3v;
            if ((L_3p3V >= -(0.125)) && (L_3p3V <= (0.125))) {
                DC_L10_3p3V = "PASS";
                ui->Load10_3_3V_Result->setText("PASS");
                ui->Load10_3_3V_Result->setStyleSheet("color:black; background-color:green");
            } else {
                DC_L10_3p3V = "FAIL";
                ui->Load10_3_3V_Result->setText("FAIL");
                ui->Load10_3_3V_Result->setStyleSheet("color: black; background-color:red");
            }
            SruLogger::instance()->logText(QString("SRU DCDC Load10 3.3V Voltage:%1 Result :%2")
                                               .arg(QString::number(g_Direct_Monitor.Input_Ch13))
                                               .arg(ui->Load10_3_3V_Result->text()));

            SruLogger::instance()->logText(
                QString("SRU DCDC Load10  3.3V Current:%1 Result:%2")
                    .arg(QString::number(g_CurrentSensorData.curr_DC3p3, 'f', 4))
                    .arg(ui->Load10_3_3v_I_Result->text()));
            break;
        }
        case 9: {
            if (g_Time_counter.seconds == 0) {
                if (g_Time_counter.minutes != 0) {
                    g_Time_counter.minutes--;
                    g_Time_counter.seconds = 60;
                } else if ((g_Time_counter.minutes == 0) && (g_Time_counter.seconds == 0)) {
                    on_SRU_DC_3p3V_L100_PB_clicked(false);
                    on_SRU_DC_3p3V_IV_PB_clicked(false);
                    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
                        on_DISPLAY_C1_pb_clicked(1);
                    }
                }
            } else {
                if (g_Time_counter.seconds != 0) {
                    g_Time_counter.seconds--;
                }
            }
            ui->txt_countdown_3p3V->setText(QString::number(g_Time_counter.minutes, 10) + ":"
                                            + QString::number(g_Time_counter.seconds, 10));

            ui->Load100_3_3v_Current_le->setText(
                QString::number(g_CurrentSensorData.curr_DC3p3, 'f', 4));

            float fixedI100_3p3V = 2.0, diffI100_3p3V = 0.0; //0.2A ±0.1A
            //        float I100_3p3V = ui->Load10_3_3v_Current_le->text().toFloat();
            //        diffI100_3p3V = I100_3p3V - fixedI100_3p3V;
            diffI100_3p3V = g_CurrentSensorData.curr_DC3p3 - fixedI100_3p3V;
            if ((diffI100_3p3V >= -(0.100)) && (diffI100_3p3V <= (0.100))) {
                L100_I3p3V = "PASS";
                ui->Load100_3_3v_I_Result->setText("PASS");
                ui->Load100_3_3v_I_Result->setStyleSheet("color:black;background-color:green");
            } else {
                L100_I3p3V = "FAIL";
                ui->Load100_3_3v_I_Result->setText("FAIL");
                ui->Load100_3_3v_I_Result->setStyleSheet("color:black;background-color:red");
            }
            //            emit DC_DC_3p3_SRU();
            ui->Load100_3_3V_le->setText(QString::number(g_Direct_Monitor.Input_Ch13));
            //3.3V±200mV
            float Load100_3V = 3.3, L_3V = 0.0;
            //        float L100_3p3V = ui->Load10_3_3V_le->text().toFloat();
            //        L_3V = L100_3p3V - Load100_3V;
            L_3V = g_Direct_Monitor.Input_Ch13 - Load100_3V;
            if ((L_3V >= -(0.125)) && (L_3V <= (0.125))) {
                DC_L100_3p3V = "PASS";
                ui->Load100_3_3V_Result->setText("PASS");
                ui->Load100_3_3V_Result->setStyleSheet("color:black; background-color:green");
            } else {
                DC_L100_3p3V = "FAIL";
                ui->Load100_3_3V_Result->setText("FAIL");
                ui->Load100_3_3V_Result->setStyleSheet("color: black; background-color:red");
            }
            SruLogger::instance()->logText(QString("SRU DCDC Load100 3.3V Voltage:%1 Result:%2")
                                               .arg(QString::number(g_Direct_Monitor.Input_Ch13))
                                               .arg(ui->Load100_3_3V_Result->text()));

            SruLogger::instance()->logText(
                QString("SRU DCDC Load100  3.3V Current:%1 Result:%2")
                    .arg(QString::number(g_CurrentSensorData.curr_DC3p3, 'f', 4))
                    .arg(ui->Load100_3_3v_I_Result->text()));
            break;
        }
        default: {
            break;
        }
        }
    } else {
        l_counter++;
        //        qDebug() << "4";
    }
}

//void MainWindow::on_SCOPE_pushButton_clicked()
//{
//    //    QString sessionPath = "C:/FTU_ATE/Oscilloscope/Ripple_DC-DC_Card.instudioproj";
//    QString sessionPath = "F:/Krishna/DUAL_CHANNELS_APP/Ripple_DC-DC_Card.instudioproj";
//    //    QString sessionPath = "F:/Krishna/DUAL_CHANNELS_APP/DualChannelSession.nisession/"
//    //                          "DualChannelSession.nisession.instudioproj";

//    sessionPath = QDir::toNativeSeparators(sessionPath);

//    if (!QFile::exists(sessionPath)) {
//        QMessageBox::warning(this,
//                             "Error",
//                             "InstrumentStudio session file not found:\n" + sessionPath);
//        return;
//    }

//    int result = (int) ShellExecuteW(nullptr,
//                                     L"open",
//                                     (LPCWSTR) sessionPath.utf16(),
//                                     nullptr,
//                                     nullptr,
//                                     SW_SHOWNORMAL);
//    if (result <= 32) {
//        QMessageBox::critical(this,
//                              "Launch Failed",
//                              "Failed to launch InstrumentStudio.\nError code: "
//                                  + QString::number(result));
//    } else {
//        qDebug() << "InstrumentStudio session launched successfully.";
//    }
//}

//void MainWindow::updateScopeSettings()
//{
//    if (!is5132Initialized)
//        return;

//    // Re-initiate acquisition to make sure settings are up-to-date
//    ViStatus acqStatus = niScope_InitiateAcquisition(session_5132);
//    if (acqStatus < 0) {
//        qDebug() << "[Error] Failed to initiate acquisition. Status:" << acqStatus;
//        return;
//    }

//    ViReal64 actualRange = 0.0;
//    ViReal64 actualSampleRate = 0.0;
//    ViInt32 actualRecordLength = 0;

//    ViStatus status1 = niScope_GetAttributeViReal64(session_5132,
//                                                    "0",
//                                                    NISCOPE_ATTR_VERTICAL_RANGE,
//                                                    &actualRange);
//    ViStatus status2 = niScope_GetAttributeViReal64(session_5132,
//                                                    "",
//                                                    NISCOPE_ATTR_HORZ_SAMPLE_RATE,
//                                                    &actualSampleRate);
//    ViStatus status3 = niScope_GetAttributeViInt32(session_5132,
//                                                   "",
//                                                   NISCOPE_ATTR_HORZ_RECORD_LENGTH,
//                                                   &actualRecordLength);

//    if (status1 < 0 || status2 < 0 || status3 < 0) {
//        qDebug() << "[Error] Failed to fetch scope attributes";
//        return;
//    }

//    ViReal64 voltsPerDiv = actualRange / 8.0;
//    ViReal64 timePerDiv = ((ViReal64) actualRecordLength / actualSampleRate) / 10.0;

//    static ViReal64 lastTPD = -1;
//    static ViReal64 lastVPD = -1;

//    qDebug() << "Fetched Time/Div:" << timePerDiv << " Volts/Div:" << voltsPerDiv;

//    if (std::abs(timePerDiv - lastTPD) > 1e-9) {
//        ui->lineEdit_timePerDiv->setText(QString::number(timePerDiv, 'e', 3) + " s/div");
//        lastTPD = timePerDiv;
//        qDebug() << "[TPD Update] Changed:" << timePerDiv;
//    }

//    if (std::abs(voltsPerDiv - lastVPD) > 1e-6) {
//        ui->lineEdit_voltsPerDiv->setText(QString::number(voltsPerDiv, 'f', 3) + " V/div");
//        lastVPD = voltsPerDiv;
//        qDebug() << "[VPD Update] Changed:" << voltsPerDiv;
//    }
//}

void MainWindow::updateScopeMinMax()
{
    if (!is5132Initialized)
        return;

    ViStatus status = niScope_InitiateAcquisition(session_5132);
    if (status < 0) {
        //        qDebug() << "Acquisition initiation failed. Status:" << status;
        return;
    }

    const int numSamples = 1000;
    ViReal64 waveform[numSamples] = {0};
    niScope_wfmInfo wfmInfo = {};

    status = niScope_Fetch(session_5132, "0", 1.0, numSamples, waveform, &wfmInfo);
    if (status < 0 || wfmInfo.actualSamples == 0) {
        //        qDebug() << "Failed to fetch waveform. Status:" << status
        //                 << "Samples:" << wfmInfo.actualSamples;
        return;
    }

    ViReal64 maxVal = waveform[0];
    ViReal64 minVal = waveform[0];

    //    qDebug() << "Start.................";

    for (int i = 1; i < wfmInfo.actualSamples; ++i) {
        if (waveform[i] > maxVal) {
            ui->MAX_R_p5V_LE->setText(QString::number(waveform[i] * 1000, 'f', 3));
            maxVal = waveform[i];
        }
        if (waveform[i] < minVal) {
            ui->MIN_R_p5V_LE->setText(QString::number(waveform[i] * 1000, 'f', 3));
            minVal = waveform[i];
        }

        //                qDebug() << "" << QString::number(waveform[i], 'f', 3);
    }
    //    qDebug() << "END.................";

    //    qDebug() << "[Live] Max:" << maxVal * 1000 << "Min:" << minVal * 1000;
}

//QPixmap hBitmapToQPixmap(HBITMAP hBitmap, int width, int height)
//{
//    BITMAPINFOHEADER bi = {0};
//    bi.biSize = sizeof(BITMAPINFOHEADER);
//    bi.biWidth = width;
//    bi.biHeight = -height; // negative for top-down DIB
//    bi.biPlanes = 1;
//    bi.biBitCount = 32;
//    bi.biCompression = BI_RGB;

//    QImage image(width, height, QImage::Format_ARGB32);
//    HDC hdc = GetDC(NULL);
//    GetDIBits(hdc, hBitmap, 0, height, image.bits(), (BITMAPINFO *) &bi, DIB_RGB_COLORS);
//    ReleaseDC(NULL, hdc);

//    return QPixmap::fromImage(image);
//}

QString MainWindow::getLatestImageFromFolder(const QString &folderPath)
{
    QDir dir(folderPath);
    dir.setNameFilters(QStringList() << "*.png");
    dir.setSorting(QDir::Time | QDir::Reversed); // Newest first
    QFileInfoList fileList = dir.entryInfoList(QDir::Files);

    if (!fileList.isEmpty()) {
        return fileList.first().absoluteFilePath(); // Latest file
    }
    return ""; // No image found
}

void MainWindow::on_SRU_CTRL_Volt_pb_clicked(bool checked)
{
    g_SRU_CTRL_sequence_counter = 0;
    if (checked) {
        //        ui->SRU_CTRL_Volt_pb->setStyleSheet(YBC);
        emit LED_PS4_Sig(checked);
        emit LED_PS5_Sig(checked);
        emit LED_PS6_Sig(checked);
    } else {
        emit LED_PS4_Sig(checked);
        emit LED_PS5_Sig(checked);
        emit LED_PS6_Sig(checked);
    }
}

void MainWindow::on_CC_Ch1_TX_pb_clicked(bool checked)
{
    //    qDebug() << "on_CC_Ch1_TX_pb_clicked";
    if (checked) {
        g_Moxa_port1.StartMsg = 0x24;
        g_Moxa_port1.MsgID = MOXA_Tx_1_RX_2;

        g_Moxa_port1.packetSize = sizeof(Moxa_port);
        for (int i = 0; i < 128; i++) {
            g_Moxa_port1.data[i] = 0xA5A5;
        }
        g_Moxa_port1.CRC_WORD = 0;
        g_Moxa_port1.EndMsg = 0x233B;
        g_Moxa_port1.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port1, sizeof(Moxa_port));
        //        if (BitWorker1 && BitWorker1->isConnected())
        {
            //            emit SRU_CTRL_USB_Write((char *) &g_Moxa_port1, sizeof(Moxa_port));
            QByteArray packet(reinterpret_cast<const char *>(&g_Moxa_port1), sizeof(g_Moxa_port1));

            emit serialWrite(packet, packet.size());
        }
        //        else {
        //            qDebug() << "Serial port is not connected!";
        //            QMessageBox::warning(this, "Serial Error", "Serial port is not connected!");
        //        }
        //        qDebug() << g_Moxa_port1.StartMsg;
        //        qDebug() << g_Moxa_port1.data;
        //        qDebug() << g_Moxa_port1.CRC_WORD;
        //        qDebug() << g_Moxa_port1.EndMsg;
        //        QByteArray rawData(reinterpret_cast<const char *>(&g_Moxa_port1), sizeof(Moxa_port));
        //        QString ch1_tx = rawData.toHex(' ').toUpper();
        // ui->CC_CH1_TX_le->setText(ch1_tx);
        //        SruLogger::instance()->logText(QString("Channel 1 Transmit Data:%1").arg(ch1_tx));
        g_time_out_flag = 0;
        TimeOutTimer->start(1000);
        g_time_out_flag = 1;
        g_time_out_state = MOXA_Tx_1_RX_2;
    }
}

void MainWindow::on_CC_Ch2_TX_pb_clicked(bool checked)
{
    if (checked) {
        g_Moxa_port2.StartMsg = 0x24;
        g_Moxa_port2.MsgID = MOXA_Tx_2_RX_1;
        g_time_out_state = MOXA_Tx_2_RX_1;
        g_time_out_flag = 1;
        g_Moxa_port2.packetSize = sizeof(Moxa_port);
        for (int i = 0; i < 128; i++) {
            g_Moxa_port2.data[i] = 0xA5A5;
        }
        g_Moxa_port2.CRC_WORD = 0;
        g_Moxa_port2.EndMsg = 0x233B;
        g_Moxa_port2.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_Moxa_port2, sizeof(Moxa_port));
        QByteArray packet(reinterpret_cast<const char *>(&g_Moxa_port2), sizeof(g_Moxa_port2));
        emit serialWrite(packet, packet.size());

        //        QByteArray rawData(reinterpret_cast<const char *>(&g_Moxa_port2), sizeof(Moxa_port));
        //        QString ch2_tx = rawData.toHex(' ').toUpper();
        //        ui->CC_CH2_TX_le->setText(ch2_tx);
        //        SruLogger::instance()->logText(QString("Channel 2 Transmit Data:%1").arg(ch2_tx));

        //        g_time_out_flag = 0;
        //        TimeOutTimer->start(1000);
        //        g_time_out_flag = 1;
        //        g_time_out_state = MOXA_Tx_1_RX_2;
    }
}

void MainWindow::on_CC_Discrete_ch1_OP_pb_clicked(bool checked)
{
    //    qDebug() << "checked" << checked;
    if (checked) {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT1_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 1;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));

    } else {
        //        qDebug() << "g_DIS_OutputsBIT_TEST.StartMsg = 0x24;---------------";

        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT1_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));
        //        emit DIS_OUT_Read_USB_Card();
        //        qDebug() << "DIS_OUT_Read_USB_Card---------------";
    }
}

void MainWindow::on_CC_Discrete_ch2_OP_pb_clicked(bool checked)
{
    if (checked) {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT2_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 1;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));

    } else {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT2_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));
    }
}

void MainWindow::on_CC_Discrete_ch3_OP_pb_clicked(bool checked)
{
    if (checked) {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT3_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 1;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));

    } else {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT3_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));
    }
}

void MainWindow::on_CC_Discrete_ch4_OP_pb_clicked(bool checked)
{
    if (checked) {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT4_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 1;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));

    } else {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT4_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));
    }
}
void MainWindow::on_CC_Discrete_ch5_OP_pb_clicked(bool checked)
{
    if (checked) {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT5_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 1;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));

    } else {
        g_DIS_OutputsBIT_TEST.StartMsg = 0x24;
        g_DIS_OutputsBIT_TEST.MsgID = SRU_DIS_OUT5_STS;
        g_DIS_OutputsBIT_TEST.packetSize = sizeof(g_DIS_OutputsBIT_TEST);
        g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts = 0;
        g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts = 0;
        g_DIS_OutputsBIT_TEST.CRC_WORD = 0;
        g_DIS_OutputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_OutputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_OutputsBIT_TEST,
                                                                sizeof(g_DIS_OutputsBIT_TEST));
        emit serialWrite((char *) &g_DIS_OutputsBIT_TEST, sizeof(g_DIS_OutputsBIT_TEST));
    }
}
void MainWindow::on_CC_Discrete_ch1_IP_pb_clicked(bool checked)
{
    if (checked) {
        g_DIS_InputsBIT_TEST.StartMsg = 0x24;
        g_DIS_InputsBIT_TEST.MsgID = SRU_DIS_IN1_STS;
        g_DIS_InputsBIT_TEST.packetSize = sizeof(g_DIS_InputsBIT_TEST);
        g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts = 1;
        g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts = 0;
        g_DIS_InputsBIT_TEST.CRC_WORD = 0;
        g_DIS_InputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_InputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_InputsBIT_TEST,
                                                               sizeof(g_DIS_InputsBIT_TEST));
        //        emit Discrete_IN_OFF();
        emit Discrete_Input_Ch1(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_DIS_InputsBIT_TEST, sizeof(g_DIS_InputsBIT_TEST));

    } else {
        g_DIS_InputsBIT_TEST.StartMsg = 0x24;
        g_DIS_InputsBIT_TEST.MsgID = SRU_DIS_IN1_STS;
        g_DIS_InputsBIT_TEST.packetSize = sizeof(g_DIS_InputsBIT_TEST);
        g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts = 0;
        g_DIS_InputsBIT_TEST.CRC_WORD = 0;
        g_DIS_InputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_InputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_InputsBIT_TEST,
                                                               sizeof(g_DIS_InputsBIT_TEST));
        emit Discrete_Input_Ch1(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_DIS_InputsBIT_TEST, sizeof(g_DIS_InputsBIT_TEST));
    }
}
void MainWindow::on_CC_Discrete_ch2_IP_pb_clicked(bool checked)
{
    if (checked) {
        g_DIS_InputsBIT_TEST.StartMsg = 0x24;
        g_DIS_InputsBIT_TEST.MsgID = SRU_DIS_IN2_STS;
        g_DIS_InputsBIT_TEST.packetSize = sizeof(g_DIS_InputsBIT_TEST);
        g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts = 1;
        g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts = 0;
        g_DIS_InputsBIT_TEST.CRC_WORD = 0;
        g_DIS_InputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_InputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_InputsBIT_TEST,
                                                               sizeof(g_DIS_InputsBIT_TEST));

        // emit Discrete_IN_OFF();
        emit Discrete_Input_Ch2(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_DIS_InputsBIT_TEST, sizeof(g_DIS_InputsBIT_TEST));

    } else {
        g_DIS_InputsBIT_TEST.StartMsg = 0x24;
        g_DIS_InputsBIT_TEST.MsgID = SRU_DIS_IN2_STS;
        g_DIS_InputsBIT_TEST.packetSize = sizeof(g_DIS_InputsBIT_TEST);
        g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts = 0;
        g_DIS_InputsBIT_TEST.CRC_WORD = 0;
        g_DIS_InputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_InputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_InputsBIT_TEST,
                                                               sizeof(g_DIS_InputsBIT_TEST));
        //emit Discrete_IN_OFF();
        emit Discrete_Input_Ch2(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_DIS_InputsBIT_TEST, sizeof(g_DIS_InputsBIT_TEST));
    }
}
void MainWindow::on_CC_Discrete_ch3_IP_pb_clicked(bool checked)
{
    if (checked) {
        g_DIS_InputsBIT_TEST.StartMsg = 0x24;
        g_DIS_InputsBIT_TEST.MsgID = SRU_DIS_IN3_STS;
        g_DIS_InputsBIT_TEST.packetSize = sizeof(g_DIS_InputsBIT_TEST);
        g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts = 1;
        g_DIS_InputsBIT_TEST.CRC_WORD = 0;
        g_DIS_InputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_InputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_InputsBIT_TEST,
                                                               sizeof(g_DIS_InputsBIT_TEST));

        //        emit Discrete_IN_OFF();
        emit Discrete_Input_Ch3(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_DIS_InputsBIT_TEST, sizeof(g_DIS_InputsBIT_TEST));

    } else {
        g_DIS_InputsBIT_TEST.StartMsg = 0x24;
        g_DIS_InputsBIT_TEST.MsgID = SRU_DIS_IN3_STS;
        g_DIS_InputsBIT_TEST.packetSize = sizeof(g_DIS_InputsBIT_TEST);
        g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts = 0;
        g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts = 0;
        g_DIS_InputsBIT_TEST.CRC_WORD = 0;
        g_DIS_InputsBIT_TEST.EndMsg = 0x233B;
        g_DIS_InputsBIT_TEST.CRC_WORD = CRCUtility::g_CRC_calc((uint8_t *) &g_DIS_InputsBIT_TEST,
                                                               sizeof(g_DIS_InputsBIT_TEST));
        //        emit Discrete_IN_OFF();
        emit Discrete_Input_Ch3(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_DIS_InputsBIT_TEST, sizeof(g_DIS_InputsBIT_TEST));
    }
}

void MainWindow::on_CC_PropSwitch_Pb_clicked(bool checked)
{
    if (checked) {
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = PREP_SWITCH;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 1;
        g_Momentary_Switch_Status.Rotary_Update = 0;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit SRU_PrepSwitch(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));

    } else {
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = PREP_SWITCH;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 0;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit SRU_PrepSwitch(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));
    }
}

void MainWindow::on_CC_InitSwitch_pb_clicked(bool checked)
{
    if (checked) {
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = READY_INIT_SWITCH;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 1;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 0;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit SRU_ReadyInitSwitch(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));

    } else {
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = READY_INIT_SWITCH;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 0;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit SRU_ReadyInitSwitch(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));
    }
}

void MainWindow::on_CC_AbortSwitch_Pb_clicked(bool checked)
{
    if (checked) {
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = ABORT_SWITCH;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 1;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 0;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit SRU_AbortSwitch(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));

        //        qDebug() << "g_Momentary_Switch_Status.Abort_Status if  "
        //                 << g_Momentary_Switch_Status.Abort_Status;

    } else {
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = ABORT_SWITCH;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 0;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));

        emit SRU_AbortSwitch(checked);
        QThread::msleep(1);
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));
        //        qDebug() << "g_Momentary_Switch_Status.Abort_Status else "
        //                 << g_Momentary_Switch_Status.Abort_Status;
    }
}

void MainWindow::on_RotarySwitch1_pb_clicked(bool checked)
{
    if (checked) {
        emit SRU_TPS_D1_Sig_1(true);
        emit SRU_TPS_D1_Sig_2(true);
        emit SRU_TPS_D1_Sig_3(true);
        emit SRU_TPS_D1_Sig_4(true);
        emit SRU_TPS_D1_Sig_5(true);
        emit SRU_TPS_D1_Sig_6(true);
        emit SRU_TPS_D1_Sig_7(true);
        emit SRU_TPS_D1_Sig_8(true);
        emit SRU_TPS_D1_Sig_9(true);
        emit SRU_TPS_D1_Sig_10(true);
        QThread::msleep(1000);
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = SRU_ROT1_STS;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 1;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));

        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));

    } else {
        emit SRU_TPS_D1_Sig_1(false);
        emit SRU_TPS_D1_Sig_2(false);
        emit SRU_TPS_D1_Sig_3(false);
        emit SRU_TPS_D1_Sig_4(false);
        emit SRU_TPS_D1_Sig_5(false);
        emit SRU_TPS_D1_Sig_6(false);
        emit SRU_TPS_D1_Sig_7(false);
        emit SRU_TPS_D1_Sig_8(false);
        emit SRU_TPS_D1_Sig_9(false);
        emit SRU_TPS_D1_Sig_10(false);
        QThread::msleep(1000);
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = SRU_ROT1_STS;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 11;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));
        //        ui->CC_Rotary1_R_le->setText("PASS");
        //        ui->CC_Rotary1_R_le->setStyleSheet(GBC);
        //        ui->CC_Rotary1_R_le->clear();
    }
}

void MainWindow::on_RotarySwitch2_pb_clicked(bool checked)
{
    if (checked) {
        emit SRU_TPS_D2_Sig_1(true);
        emit SRU_TPS_D2_Sig_2(true);
        emit SRU_TPS_D2_Sig_3(true);
        emit SRU_TPS_D2_Sig_4(true);
        emit SRU_TPS_D2_Sig_5(true);
        emit SRU_TPS_D2_Sig_6(true);
        emit SRU_TPS_D2_Sig_7(true);
        emit SRU_TPS_D2_Sig_8(true);
        emit SRU_TPS_D2_Sig_9(true);
        emit SRU_TPS_D2_Sig_10(true);
        QThread::msleep(1000);
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = SRU_ROT2_STS;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 2;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));

        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));

    } else {
        emit SRU_TPS_D2_Sig_1(false);
        emit SRU_TPS_D2_Sig_2(false);
        emit SRU_TPS_D2_Sig_3(false);
        emit SRU_TPS_D2_Sig_4(false);
        emit SRU_TPS_D2_Sig_5(false);
        emit SRU_TPS_D2_Sig_6(false);
        emit SRU_TPS_D2_Sig_7(false);
        emit SRU_TPS_D2_Sig_8(false);
        emit SRU_TPS_D2_Sig_9(false);
        emit SRU_TPS_D2_Sig_10(false);
        QThread::msleep(1000);
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = SRU_ROT2_STS;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 12;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));
        //        ui->CC_Rotary2_R_le->setText("PASS");
        //        ui->CC_Rotary2_R_le->setStyleSheet(GBC);
    }
}

void MainWindow::on_RotarySwitch3_pb_clicked(bool checked)
{
    if (checked) {
        emit SRU_TPS_D3_Sig_1(true);
        emit SRU_TPS_D3_Sig_2(true);
        emit SRU_TPS_D3_Sig_3(true);
        emit SRU_TPS_D3_Sig_4(true);
        emit SRU_TPS_D3_Sig_5(true);
        emit SRU_TPS_D3_Sig_6(true);
        emit SRU_TPS_D3_Sig_7(true);
        emit SRU_TPS_D3_Sig_8(true);
        emit SRU_TPS_D3_Sig_9(true);
        emit SRU_TPS_D3_Sig_10(true);
        QThread::msleep(1000);
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = SRU_ROT3_STS;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 3;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));

    } else {
        emit SRU_TPS_D3_Sig_1(false);
        emit SRU_TPS_D3_Sig_2(false);
        emit SRU_TPS_D3_Sig_3(false);
        emit SRU_TPS_D3_Sig_4(false);
        emit SRU_TPS_D3_Sig_5(false);
        emit SRU_TPS_D3_Sig_6(false);
        emit SRU_TPS_D3_Sig_7(false);
        emit SRU_TPS_D3_Sig_8(false);
        emit SRU_TPS_D3_Sig_9(false);
        emit SRU_TPS_D3_Sig_10(false);
        QThread::msleep(1000);
        g_Momentary_Switch_Status.StartMsg = 0x24;
        g_Momentary_Switch_Status.MsgID = SRU_ROT3_STS;
        g_Momentary_Switch_Status.packetSize = sizeof(g_Momentary_Switch_Status);
        g_Momentary_Switch_Status.Abort_Status = 0;
        g_Momentary_Switch_Status.Ready_Init_Status = 0;
        g_Momentary_Switch_Status.Prep_Status = 0;
        g_Momentary_Switch_Status.Rotary_Update = 13;
        g_Momentary_Switch_Status.CRC_WORD = 0;
        g_Momentary_Switch_Status.EndMsg = 0x233B;
        g_Momentary_Switch_Status.CRC_WORD
            = CRCUtility::g_CRC_calc((uint8_t *) &g_Momentary_Switch_Status,
                                     sizeof(g_Momentary_Switch_Status));
        emit serialWrite((char *) &g_Momentary_Switch_Status, sizeof(g_Momentary_Switch_Status));
        //        ui->CC_Rotary3_R_le->setText("PASS");
        //        ui->CC_Rotary3_R_le->setStyleSheet(GBC);
    }
}
void MainWindow::on_refresh_SRU_DC_pb_clicked()
{
    ui->Sru_UR->clear();
    ui->txt_countdown_5V->clear();
    ui->IV_5Volt_le->clear();
    ui->IV_5V_Current_le->clear();
    ui->Load10_5V_le->clear();
    ui->Load10_5v_I_le->clear();
    ui->Load10_5V_Result_le->clear();
    ui->Load10_5v_I_Result_le->clear();
    ui->Load100_5V_le->clear();
    ui->Load100_5v_I_op_le->clear();
    ui->Load100_5V_Result->clear();
    ui->Load100_5v_I_Result->clear();
    ui->MAX_R_p5V_LE->clear();
    ui->MIN_R_p5V_LE->clear();
    ui->Result_P5V->clear();
    ui->Load10_5V_Result_le->setStyleSheet("background-color:white");
    ui->Load10_5v_I_Result_le->setStyleSheet("background-color:white");
    ui->Load100_5V_Result->setStyleSheet("background-color:white");
    ui->Load100_5v_I_Result->setStyleSheet("background-color:white");
    ui->Result_P5V->setStyleSheet("background-color:white");

    ui->txt_countdown_N_5V->clear();
    ui->IV_N_5Volt_le->clear();
    ui->IV_N_5V_Current_le->clear();
    ui->Load10_minus5V_le->clear();
    ui->Load10_minus5v_I_le->clear();
    ui->Load10_minus5v_result_le->clear();
    ui->Load10_N5v_Current_Result_le->clear();
    ui->Load100_N_5V_le->clear();
    ui->Load100_N_5v_I_op_le->clear();
    ui->Load100_N_5v_Result->clear();
    ui->Load100_N_5V_I_Result->clear();
    ui->MAX_R_N5V_LE->clear();
    ui->MIN_R_N5V_LE->clear();
    ui->Result_N5V->clear();

    ui->Load10_minus5v_result_le->setStyleSheet("background-color:white");
    ui->Load10_N5v_Current_Result_le->setStyleSheet("background-color:white");
    ui->Load100_N_5v_Result->setStyleSheet("background-color:white");
    ui->Load100_N_5V_I_Result->setStyleSheet("background-color:white");
    ui->Result_N5V->setStyleSheet("background-color:white");

    ui->txt_countdown_3p3V->clear();
    ui->IV_3p3_Volt_le->clear();
    ui->IV_3p3V_Current_le->clear();
    ui->Load10_3_3V_le->clear();
    ui->Load10_3_3v_Current_le->clear();
    ui->Load10_3_3V_Result->clear();
    ui->Load10_3_3v_I_Result->clear();
    ui->Load100_3_3V_le->clear();
    ui->Load100_3_3v_Current_le->clear();
    ui->Load100_3_3V_Result->clear();
    ui->Load100_3_3v_I_Result->clear();
    ui->MAX_R_3p3V_LE->clear();
    ui->MIN_R_3p3V_LE->clear();
    ui->Result_3p3V->clear();

    ui->Load10_3_3V_Result->setStyleSheet("background-color:white");
    ui->Load10_3_3v_I_Result->setStyleSheet("background-color:white");
    ui->Load100_3_3V_Result->setStyleSheet("background-color:white");
    ui->Load100_3_3v_I_Result->setStyleSheet("background-color:white");
    ui->Result_3p3V->setStyleSheet("background-color:white");

    ui->DCDC_Manual_RB->setChecked(false);
    ui->DCDC_CTRL_Auto_RB->setChecked(false);
    ui->SRU_Start_pb->setChecked(false);

    ui->DCDC_Manual_RB->setAutoExclusive(false);
    ui->DCDC_Manual_RB->setChecked(false);
    ui->DCDC_Manual_RB->setAutoExclusive(true);

    ui->DCDC_CTRL_Auto_RB->setAutoExclusive(false);
    ui->DCDC_CTRL_Auto_RB->setChecked(false);
    ui->DCDC_CTRL_Auto_RB->setAutoExclusive(true);

    ui->SRU_Start_pb->setStyleSheet("background-color:white");

    ui->DISPLAY_C1_pb->setStyleSheet("background-color: rgb(83, 162, 171);");
    ui->DISPLAY_C2_pb->setStyleSheet("background-color: rgb(83, 162, 171);");
    ui->DISPLAY_C3_pb->setStyleSheet("background-color: rgb(83, 162, 171);");
    ui->SRU_DCDC_REPORT->setStyleSheet("background-color: rgb(77, 109, 186);");
    on_SRU_VoltagePB_toggled(false);
}

void MainWindow::on_refresh_SRU_CC_pb_clicked()
{
    ui->SRU_CntrlCard_Report->setStyleSheet("");
    ui->cntrl_URemarks->clear();
    ui->CC_Ch1_TX_pb->setStyleSheet(
        "background-color:rgb(83, 162, 171); color: rgb(255, 255, 255);");

    ui->CC_CH1_RX_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Ch2_TX_pb->setStyleSheet(
        "background-color:rgb(83, 162, 171); color: rgb(255, 255, 255);");

    ui->CC_CH2_RX_le->setStyleSheet("background-color: rgb(255, 255, 255);");

    ui->CC_CH1_TX_le->clear();
    ui->CC_CH1_RX_le->clear();
    ui->CC_CH2_RX_le->clear();
    ui->CC_CH2_TX_le->clear();

    ui->CC_Rotary1_le->clear();
    ui->CC_Rotary2_le->clear();
    ui->CC_Rotary3_le->clear();
    ui->RotarySwitch1_pb->setStyleSheet("background-color: rgb(127, 127, 190); color:rgb(0,0,0)");
    ui->RotarySwitch2_pb->setStyleSheet("background-color: rgb(127, 127, 190); color:rgb(0,0,0)");
    ui->RotarySwitch3_pb->setStyleSheet("background-color: rgb(127, 127, 190); color:rgb(0,0,0)");
    ui->RotarySwitch1_pb->setChecked(false);
    ui->RotarySwitch2_pb->setChecked(false);
    ui->RotarySwitch3_pb->setChecked(false);

    ui->CC_Discrete_ch1_OP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");
    ui->CC_Discrete_ch2_OP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");
    ui->CC_Discrete_ch3_OP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");
    ui->CC_Discrete_ch4_OP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");
    ui->CC_Discrete_ch5_OP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");
    ui->CC_Discrete_ch1_OP_Value_le->clear();
    ui->CC_Discrete_ch2_OP_Value_le->clear();
    ui->CC_Discrete_ch3_OP_Value_le->clear();
    ui->CC_Discrete_ch4_OP_Value_le->clear();
    ui->CC_Discrete_ch5_OP_Value_le->clear();
    ui->CC_Discrete_ch1_IP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");
    ui->CC_Discrete_ch2_IP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");
    ui->CC_Discrete_ch3_IP_pb->setStyleSheet(
        "color: rgb(255, 255, 255); background-color:rgb(200, 118, 168)");

    ui->CC_Discrete_ch1_IP_pb->setChecked(false);
    ui->CC_Discrete_ch2_IP_pb->setChecked(false);
    ui->CC_Discrete_ch3_IP_pb->setChecked(false);

    ui->CC_Discrete_ch1_IP_Value_le->clear();
    ui->CC_Discrete_ch2_IP_Value_le->clear();
    ui->CC_Discrete_ch3_IP_Value_le->clear();
    ui->CC_Discrete_IP_ch1_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_IP_ch2_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_IP_ch3_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_IP_ch1_R_le->clear();
    ui->CC_Discrete_IP_ch2_R_le->clear();
    ui->CC_Discrete_IP_ch3_R_le->clear();

    ui->CC_Discrete_OP_ch1_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_OP_ch2_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_OP_ch3_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_OP_ch4_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_OP_ch5_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Discrete_OP_ch1_R_le->clear();
    ui->CC_Discrete_OP_ch2_R_le->clear();
    ui->CC_Discrete_OP_ch3_R_le->clear();
    ui->CC_Discrete_OP_ch4_R_le->clear();
    ui->CC_Discrete_OP_ch5_R_le->clear();
    ui->CC_AbortSwitch_Pb->setStyleSheet("background-color: rgb(153, 153, 229);");
    ui->CC_PropSwitch_Pb->setStyleSheet("background-color: rgb(153, 153, 229);");
    ui->CC_InitSwitch_pb->setStyleSheet("background-color: rgb(153, 153, 229);");
    ui->SRU_AbortSwitch_le->clear();
    ui->SRU_PrepSwitch_le->clear();
    ui->SRU_ReadyInitSwitch_le->clear();
    ui->AbortSwitch_result_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->PrepSwitch_result_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->ReadyInitSwitch_result_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->AbortSwitch_result_le->clear();
    ui->PrepSwitch_result_le->clear();
    ui->ReadyInitSwitch_result_le->clear();
    ui->DAC_op_ch1_le->clear();
    ui->DAC_op_ch2_le->clear();
    ui->DAC_op_ch3_le->clear();
    ui->DAC_op_ch4_le->clear();
    ui->DAC_op_ch5_le->clear();
    ui->DAC_op_ch6_le->clear();
    ui->DAC_op_ch7_le->clear();
    ui->DAC_op_ch8_le->clear();

    ui->DAC_Result_ch1_le->clear();
    ui->DAC_Result_ch2_le->clear();
    ui->DAC_Result_ch3_le->clear();
    ui->DAC_Result_ch4_le->clear();
    ui->DAC_Result_ch5_le->clear();
    ui->DAC_Result_ch6_le->clear();
    ui->DAC_Result_ch7_le->clear();
    ui->DAC_Result_ch8_le->clear();
    ui->SRU_ExternalFlash_pb->setStyleSheet("background-color:rgb(200, 118, 168)");
    ui->SRU_ExternalFlash_pb->setChecked(false);
    ui->SRU_ExternalFlash_le->clear();
    ui->SRU_ExternalFlash2_le->clear();

    ui->SRU_ExternalFlash_result_le->clear();
    ui->SRU_ExternalFlash_result2_le->clear();

    ui->SRU_ExternalFlash_result_le->setStyleSheet("background-color:white");
    ui->SRU_ExternalFlash_result2_le->setStyleSheet("background-color:white");

    ui->CC_AbortSwitch_Pb->setChecked(false);
    ui->CC_PropSwitch_Pb->setChecked(false);
    ui->CC_InitSwitch_pb->setChecked(false);
    //    ui->SRU_CTRL_Volt_pb->setStyleSheet("background-color: rgb(171, 212, 255);color:rgb(0,0,0)");
    //    ui->SRU_CTRL_Volt_pb->setChecked("false");
    ui->CC_POST_listw->clear();
    //    ui->CC_cksum_le->clear();
    ui->DAC_Result_ch1_le->setStyleSheet("");
    ui->DAC_Result_ch2_le->setStyleSheet("");
    ui->DAC_Result_ch3_le->setStyleSheet("");
    ui->DAC_Result_ch4_le->setStyleSheet("");
    ui->DAC_Result_ch5_le->setStyleSheet("");
    ui->DAC_Result_ch6_le->setStyleSheet("");
    ui->DAC_Result_ch7_le->setStyleSheet("");
    ui->DAC_Result_ch8_le->setStyleSheet("");
    ui->CC_Rotary1_R_le->clear();
    ui->CC_Rotary2_R_le->clear();
    ui->CC_Rotary3_R_le->clear();
    ui->CC_Rotary1_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Rotary2_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->CC_Rotary3_R_le->setStyleSheet("background-color: rgb(255, 255, 255);");

    items.clear();

    ui->DCDC_Manual_RB->setAutoExclusive(false);
    ui->DCDC_Manual_RB->setChecked(false);
    ui->DCDC_Manual_RB->setAutoExclusive(true);

    ui->DCDC_CTRL_Auto_RB->setAutoExclusive(false);
    ui->DCDC_CTRL_Auto_RB->setChecked(false);
    ui->DCDC_CTRL_Auto_RB->setAutoExclusive(true);
    ui->SRU_Start_pb->setChecked(false);
    ui->USB_port->setChecked(false);

    ui->USB_Status->clear();
    // ui->SRU_CTRL_Volt_pb->setChecked(false);

    ui->SRU_Start_pb->setStyleSheet("background-color:white");
}
void MainWindow::on_SRU_DCDC_REPORT_clicked()
{
    DC_DC_Report();
    //ui->SRU_Start_pb->setEnabled(true);
    on_SRU_Start_pb_toggled(false);
    on_SRU_VoltagePB_toggled(false);
    ui->SRU_Start_pb->setStyleSheet("background-color:white;color:black;");
    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
        ui->SRU_Start_pb->setStyleSheet(GBC);
    }

    ui->SRU_Start_pb->setChecked(false);
}

void MainWindow::on_SRU_CntrlCard_Report_clicked()
{
    Controller_Report();
    on_SRU_CTRL_Volt_pb_clicked(false);
    ui->SRU_CTRL_Volt_pb->setChecked(false);
    ui->SRU_CTRL_Volt_pb->setStyleSheet("background-color: rgb(171, 212, 255);color: rgb(0, 0, 0)");
    for (int i = 0; i < 8; i++) {
        SruLogger::instance()->logText(
            QString("--------------[INFO] ADC_DAC Loop back ---------------"));
        SruLogger::instance()->logText(
            QString("Channel:%1 2Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test1Status[i] ? "PASS" : "FAIL"));
        SruLogger::instance()->logText(
            QString(" Channel :%1 1.5Volts :%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test2Status[i] ? "PASS" : "FAIL"));

        SruLogger::instance()->logText(
            QString(" Channel :%1 1Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test3Status[i] ? "PASS" : "FAIL"));

        SruLogger::instance()->logText(
            QString("Channel:%1 0.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test4Status[i] ? "PASS" : "FAIL"));
        SruLogger::instance()->logText(
            QString("Channel:%1 0Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test5Status[i] ? "PASS" : "FAIL"));
        SruLogger::instance()->logText(
            QString("Channel:%1 Negative 0.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test6Status[i] ? "PASS" : "FAIL"));
        SruLogger::instance()->logText(
            QString("Channel:%1 Negative 1Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test7Status[i] ? "PASS" : "FAIL"));
        SruLogger::instance()->logText(
            QString("Channel:%1 Negative 1.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test8Status[i] ? "PASS" : "FAIL"));
        SruLogger::instance()->logText(
            QString("Channel:%1 Negative 2Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test9Status[i] ? "PASS" : "FAIL"));
    }

    on_SRU_Start_pb_toggled(false);
    ui->SRU_Start_pb->setChecked(false);
    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
        ui->SRU_Start_pb->setStyleSheet(GBC);
    }
}

void MainWindow::on_SRU_ExternalFlash_pb_clicked()
{
    for (int i = 0; i <= 512; i++) {
        g_ExternalFlashData[i] = 0xA5;
    }
    for (int i = 513; i <= 1024; i++) {
        g_ExternalFlashData[i] = 0xF5;
    }
    uint16_t extFlash_CRC_Check = CRCUtility::g_CRC_calc(&g_ExternalFlashData[0], 512);
    uint16_t extFlash_CRC_Check2 = CRCUtility::g_CRC_calc(&g_ExternalFlashData[513], 512);
    //    qDebug() << "extFlash_CRC_Check:"
    //             << QString("0x%1").arg(extFlash_CRC_Check, 4, 16, QLatin1Char('0')).toUpper();
    //    qDebug() << "g_CRC_BIT_TEST.ExternalFlash_CRC:"
    //             << QString("0x%1")
    //                    .arg(g_CRC_BIT_TEST.ExternalFlash_CRC, 4, 16, QLatin1Char('0'))
    //                    .toUpper();
    //    qDebug() << "extFlash_CRC_Check2:"
    //             << QString("0x%1").arg(extFlash_CRC_Check2, 4, 16, QLatin1Char('0')).toUpper();
    //    qDebug() << "g_CRC_BIT_TEST.ExternalFlash_CRC2:"
    //             << QString("0x%1")
    //                    .arg(g_CRC_BIT_TEST.ExternalFlash_CRC2, 4, 16, QLatin1Char('0'))
    //                    .toUpper();
    formatted
        = "512 bytes of pattern 0xA5A5, observed CrcCheckSum = "
          + QString("0x%1").arg(g_CRC_BIT_TEST.ExternalFlash_CRC, 4, 16, QLatin1Char('0')).toUpper();
    ui->SRU_ExternalFlash_le->setText(formatted);

    formatted2 = "512 bytes of pattern 0xF5F5, observed CrcCheckSum = "
                 + QString("0x%1")
                       .arg(g_CRC_BIT_TEST.ExternalFlash_CRC2, 4, 16, QLatin1Char('0'))
                       .toUpper();
    ui->SRU_ExternalFlash2_le->setText(formatted2);

    if ((extFlash_CRC_Check == g_CRC_BIT_TEST.ExternalFlash_CRC)
        && (extFlash_CRC_Check2 == g_CRC_BIT_TEST.ExternalFlash_CRC2)) {
        ext_flash_crc = "PASS";
        ui->SRU_ExternalFlash_result_le->setText("PASS");
        ui->SRU_ExternalFlash_result_le->setStyleSheet(GBC);
        ext_flash_crc2 = "PASS";
        ui->SRU_ExternalFlash_result2_le->setText("PASS");
        ui->SRU_ExternalFlash_result2_le->setStyleSheet(GBC);
        //        qDebug() << "ExternalFlash PASS";
        //-auto sequence
        if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
            QMetaObject::invokeMethod(this, "SRU_CTRL_AutoStepCompleted", Qt::QueuedConnection);
        }
    } else {
        ext_flash_crc = "FAIL";
        ui->SRU_ExternalFlash_result_le->setText("FAIL");
        ui->SRU_ExternalFlash_result_le->setStyleSheet(RBC);
        ext_flash_crc2 = "FAIL";
        ui->SRU_ExternalFlash_result2_le->setText("FAIL");
        ui->SRU_ExternalFlash_result2_le->setStyleSheet(RBC);
        //        qDebug() << "ExternalFlash FAIL";
        //-auto sequence
        if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
            QMetaObject::invokeMethod(this, "SRU_CTRL_AutoStepCompleted", Qt::QueuedConnection);
        }
    }
    SruLogger::instance()->logText(
        QString("External Flash checksum:0X%1 Result:%2")
            .arg(QString::number(g_CRC_BIT_TEST.ExternalFlash_CRC, 16).toUpper())
            .arg(ext_flash_crc));
    SruLogger::instance()->logText(
        QString("External Flash checksum2:0X%1 Result:%2")
            .arg(QString::number(g_CRC_BIT_TEST.ExternalFlash_CRC2, 16).toUpper())
            .arg(ext_flash_crc));

    // qDebug() << "ExternalFlash_CRC" << QString::number(g_CRC_BIT_TEST.ExternalFlash_CRC, 16);

    //    bool mismatch = false;
    //    for (size_t i = 0; i < sizeof(g_ExternalFlashData); i++) {
    //        if (g_ExternalFlashData[i] != 0xAA) {
    //            qDebug() << "Mismatch at index" << i
    //                     << ", value:" << QString::number(g_ExternalFlashData[i], 16);
    //            mismatch = true;
    //            break;
    //        }
    //    }
    //    if (!mismatch) {
    //        qDebug() << "Buffer filled with 0xAA";
    //    }
}

void MainWindow::on_USB_port_clicked(bool checked)
{
    on_OpenPort_toggled(checked);
    //    if (checked) {
    //        //------------------------------------------stm32 CTRL CARD SRU  USB Connection--------------------------
    //        QString BitPortName1;
    //        QStringList ststatus1;

    //        // Scan for USB serial ports
    //        //    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    //        //        if (info.description().contains("STM", Qt::CaseInsensitive)
    //        //            || info.manufacturer().contains("STM", Qt::CaseInsensitive)) {
    //        //            BitPortName = info.portName();
    //        //            break; // Use the first matching USB port
    //        //        }
    //        //    }

    //        QString targetSerialNumber1 = "204D31715041"; // set this to the serial you want to detect

    //        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    //            // Optional: Print for debugging
    //            qDebug() << "Checking Port:" << info.portName() << "Description:" << info.description()
    //                     << "Manufacturer:" << info.manufacturer()
    //                     << "Serial Number:" << info.serialNumber();

    //            // Check STM32 description/manufacturer AND serial number
    //            if ((info.description().contains("STM", Qt::CaseInsensitive)
    //                 || info.manufacturer().contains("STM", Qt::CaseInsensitive))
    //                && info.serialNumber() == targetSerialNumber1) {
    //                BitPortName1 = info.portName(); // Store port name
    //                qDebug() << "STM32 device with serial" << targetSerialNumber1 << "found on port"
    //                         << BitPortName1;
    //                break; // Use the first matching port with this serial
    //            }
    //        }

    //        if (BitPortName1.isEmpty()) {
    //            ststatus1 << "❌ Not Connected";
    //            ui->USB_Status->setText(BitPortName1);
    //        } else {
    //            qDebug() << "STM device found on port:" << BitPortName1;
    //            ststatus1 << "✅ Connected & Initialized";
    //            ui->USB_Status->setText(BitPortName1);
    //        }

    //        QString stsummary1 = "STM32 Device SRU Status at Startup:\n\n" + ststatus1.join("\n");

    //        if (BitPortName1.isEmpty())
    //            QMessageBox::warning(this, "STM32 SRU Status", stsummary1);
    //        else
    //            QMessageBox::information(this, "STM32 SRU Status", stsummary1);

    //        qDebug() << "Using USB port:" << BitPortName1;
    //        //    QString COMPort = "COM18";
    //        BitWorker1 = new SerialWork_Bittest(BitPortName1, true);

    //        connect(BitWorker1, &SerialWork_Bittest::msg_process, this, &MainWindow::message_received);

    //        BitWorker1->start();

    //        connect(this,
    //                &MainWindow::SRU_CTRL_USB_Write,
    //                BitWorker1,
    //                &SerialWork_Bittest::writeData,
    //                Qt::QueuedConnection);
    //        //------------------------------------------stm32 current sensor USB Connection--------------------------END--

    //    } else {
    //    }
}

void MainWindow::on_SRU_VoltagePB_toggled(bool checked)
{
    SruLogger::instance()->logText(QString("----------STARTS SRU LEVEL TEST ----------- "));
    if (checked) {
        // voltage = ui->LRU_VoltageCB->currentText();
        int index = ui->SRU_Volts_CB->currentIndex();
        SruLogger::instance()->logText(QString::number(index));
        ui->Volt_28_16_32_Cmb->setCurrentIndex(index);
        on_Volt_28_16_32_Cmb_currentIndexChanged(index); // update voltage + current UI

        //  ui->LRU_VoltageLE->setText(ui->Volt_16_28_32_le->text());
        // ui->LRU_VoltageLE->setText(voltage);
        if (g_CurrentSensorData.curr_PS7 < 0)
            g_CurrentSensorData.curr_PS7 = 0;
        ui->Ip_Current_le->setText(QString::number(g_CurrentSensorData.curr_PS7, 'f', 4));
        SruLogger::instance()->logText(
            QString(" SRU Voltage: %1| Current: %2 A")
                .arg(voltageValue)
                .arg(QString::number(g_CurrentSensorData.curr_PS7, 'f', 4)));

    } else {
        ui->SRU_Volts_CB->setCurrentIndex(5);
        on_Volt_28_16_32_Cmb_currentIndexChanged(5);
        ui->SRU_V_le->setText(ui->SRU_Volts_CB->currentText());
        ui->SRU_VoltagePB->setChecked(false);
    }
}

void MainWindow::BittestLogUpdate()
{
    /*****************POST*******************************/
    BitTestLogger::instance()->logText("Updates every 10s--------------------");
    BitTestLogger::instance()->logText(" POST Data ");
    fullLogEntry = items.join("\n");
    BitTestLogger::instance()->logText(fullLogEntry);
    BitTestLogger::instance()->logText("--------------Starting RS422 BIT Test.---------------");
    BitTestLogger::instance()->logText(LRU_data);
    BitTestLogger::instance()->logText(QString("Result: %1").arg(rs422_result));

    //BitTestLogger::instance()->logText(
    //                                    QString("RS422 Message Received: %1").arg(hexMessage));
    BitTestLogger::instance()->logText(QString("RS422 Loop Back PASS Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.passCount_RS422));

    BitTestLogger::instance()->logText(QString("RS422 Loop Back FAIL Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.failCount_RS422));

    BitTestLogger::instance()->logText(
        QString("Observed Bytes: %1").arg(QString::number(l_counter)));
    BitTestLogger::instance()->logText(
        QString("Observed CRC Word: 0x%1").arg(QString::number(g_checkCRC_word, 16).toUpper()));

    /********************[INFO] FRONT PANEL SWITCH STATUS:****************/

    BitTestLogger::instance()->logText(QString("-------------------[INFO] FRONT PANEL "
                                               "SWITCH STATUS: "
                                               "%1-----------------------")
                                           .arg(true));

    BitTestLogger::instance()->logText(
        QString("Rotary switches 1 2 3 status: %1")
            .arg(QString::number(g_Momentary_Switch_Status.Rotary_Update, 10)));

    BitTestLogger::instance()->logText(
        QString("Rotary_Update Switch Test PASS Count: %1")
            .arg(g_BitTestLogger_PassFailCount.passCount_FrontPanel[0]));

    BitTestLogger::instance()->logText(
        QString("Rotary_Update Switch Test FAIL Count: %1")
            .arg(g_BitTestLogger_PassFailCount.failCount_FrontPanel[0]));

    BitTestLogger::instance()->logText(
        QString("Abort Status: %1").arg(QString::number(g_Momentary_Switch_Status.Abort_Status, 16)));

    BitTestLogger::instance()->logText(
        QString("Abort Switch status PASS Count: %1")
            .arg(g_BitTestLogger_PassFailCount.passCount_FrontPanel[1]));

    BitTestLogger::instance()->logText(
        QString("Abort Switch status FAIL Count: %1")
            .arg(g_BitTestLogger_PassFailCount.failCount_FrontPanel[1]));

    BitTestLogger::instance()->logText(
        QString("Prep Status: %1").arg(QString::number(g_Momentary_Switch_Status.Prep_Status, 16)));

    BitTestLogger::instance()->logText(
        QString("Abort Switch status PASS Count: %1")
            .arg(g_BitTestLogger_PassFailCount.passCount_FrontPanel[2]));

    BitTestLogger::instance()->logText(
        QString("Prep Switch status FAIL Count: %1")
            .arg(g_BitTestLogger_PassFailCount.failCount_FrontPanel[2]));

    BitTestLogger::instance()->logText(
        QString("Ready Init Status: %1")
            .arg(QString::number(g_Momentary_Switch_Status.Ready_Init_Status, 16)));

    BitTestLogger::instance()->logText(
        QString("ReadyInit Switch status PASS Count: %1")
            .arg(g_BitTestLogger_PassFailCount.passCount_FrontPanel[3]));

    BitTestLogger::instance()->logText(
        QString("ReadyInit Switch status FAIL Count: %1")
            .arg(g_BitTestLogger_PassFailCount.failCount_FrontPanel[3]));

    /**********************[INFO] Discrete Output Status***********/

    //    BitTestLogger::instance()->logText(QString("-----------------[INFO] Discrete Output "
    //                                               "Status:-----------------"));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 1 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.passCount_DOP[0]));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 1 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.failCount_DOP[0]));

    BitTestLogger::instance()->logText(
        QString("Output Channel 1 :%1 Status:[%2]")
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts)
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH1_Sts == 1 ? "PASS" : "FAIL"));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 2 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.passCount_DOP[1]));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 2 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.failCount_DOP[1]));

    BitTestLogger::instance()->logText(
        QString("Output Channel 2 :%1 Status:[%2]")
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts)
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH2_Sts == 1 ? "PASS" : "FAIL"));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 3 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.passCount_DOP[2]));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 3 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.failCount_DOP[2]));

    BitTestLogger::instance()->logText(
        QString("Output Channel 3 :%1  Status:[%2]")
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts)
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH3_Sts == 1 ? "PASS" : "FAIL"));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 4 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.passCount_DOP[3]));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 4 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.failCount_DOP[3]));

    BitTestLogger::instance()->logText(
        QString("Output Channel 4: %1 Status:[%2]")
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts)
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH4_Sts == 1 ? "PASS" : "FAIL"));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 5 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.passCount_DOP[4]));

    BitTestLogger::instance()->logText(QString("Discrete Output Channel 5 Count: %1")
                                           .arg(g_BitTestLogger_PassFailCount.failCount_DOP[4]));

    BitTestLogger::instance()->logText(
        QString("Output Channel 5: %1 Status:[%2]")
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts)
            .arg(g_DIS_OutputsBIT_TEST.Dis_out_CH5_Sts == 1 ? "PASS" : "FAIL"));

    /**************************Discrete Input channel status***************/

    //    BitTestLogger::instance()->logText(QString("--------------[INFO] Discrete Input "
    //                                               "channel status ---------------")
    //                                           .arg(true));

    BitTestLogger::instance()->logText(
        QString("Input Channel 1:%1 Status:[%2]")
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts)
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1 ? "PASS" : "FAIL"));
    BitTestLogger::instance()->logText(
        QString("Input Channel 1:%1 Count:[%2]")
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts)
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH1_Sts == 1
                     ? g_BitTestLogger_PassFailCount.passCount_DIP[0]
                     : g_BitTestLogger_PassFailCount.failCount_DIP[0]));

    BitTestLogger::instance()->logText(
        QString("Input Channel 2: %1  Status:[%2]")
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts)
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1 ? "PASS" : "FAIL"));
    BitTestLogger::instance()->logText(
        QString("Input Channel 2: %1  Count:[%2]")
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts)
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH2_Sts == 1
                     ? g_BitTestLogger_PassFailCount.passCount_DIP[1]
                     : g_BitTestLogger_PassFailCount.failCount_DIP[1]));

    BitTestLogger::instance()->logText(
        QString("Input Channel 3: %1 Status:[%2]")
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts)
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1 ? "PASS" : "FAIL"));
    BitTestLogger::instance()->logText(
        QString("Input Channel 3: %1 Count:[%2]")
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts)
            .arg(g_DIS_InputsBIT_TEST.Dis_IN_CH3_Sts == 1
                     ? g_BitTestLogger_PassFailCount.passCount_DIP[2]
                     : g_BitTestLogger_PassFailCount.failCount_DIP[2]));

    //******************ADC**********************//

    for (int i = 0; i < 8; ++i) {
        BitTestLogger::instance()->logText(
            QString("--------------[INFO] ADC_DAC Loop back ---------------"));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 2Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test1Status[i] ? "PASS" : "FAIL"));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 ADC-DAC:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test1Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_2V[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_2V[i]++));

        BitTestLogger::instance()->logText(
            QString(" Channel :%1 1.5Volts :%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test2Status[i] ? "PASS" : "FAIL"));
        BitTestLogger::instance()->logText(
            QString(" Channel :%1 ADC_DAC Count :%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test2Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_1p5V[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_1p5V[i]++));

        BitTestLogger::instance()->logText(
            QString(" Channel :%1 1Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test3Status[i] ? "PASS" : "FAIL"));
        BitTestLogger::instance()->logText(
            QString("Channel: %1 ADC-DAC Count:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test3Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_1V[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_1V[i]++));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 0.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test4Status[i] ? "PASS" : "FAIL"));
        BitTestLogger::instance()->logText(
            QString("Channel:%1 0.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test4Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_0p5V[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_0p5V[i]++));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 0Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test5Status[i] ? "PASS" : "FAIL"));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 0Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test5Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_0V[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_0V[i]++));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 0.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test6Status[i] ? "PASS" : "FAIL"));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 0.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test6Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N0p5[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N0p5[i]++));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 1Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test7Status[i] ? "PASS" : "FAIL"));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 1Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test7Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N1[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N1[i]++));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 1.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test8Status[i] ? "PASS" : "FAIL"));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 1.5Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test8Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N1p5[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N1p5[i]++));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 2Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test9Status[i] ? "PASS" : "FAIL"));

        BitTestLogger::instance()->logText(
            QString("Channel:%1 Negative 2Volts:%2")
                .arg(i + 1)
                .arg(g_ADC_Card2_BitTest.test9Status[i]
                         ? g_BitTestLogger_PassFailCount.passCount_ADC_DAC_N2[i]++
                         : g_BitTestLogger_PassFailCount.failCount_ADC_DAC_N2[i]++));
    }
}

void MainWindow::on_Open_Oscilloscope_PB_clicked()
{
    double l_min = 0;
    double l_max = 0;
    double l_Vpp = 0;
    // const QString outPng = QDir::currentPath() + "/scope_capture.png";

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");

    QString folderPath = "C:/FTU_ATE/Ripple_Images/Plus5V";
    QDir dir;
    if (!dir.exists(folderPath)) {
        if (!dir.mkpath(folderPath)) {
            return; // exit if folder creation fails
        }
    }
    QString outPng = folderPath + "/scope_capture_" + timestamp + ".png";

    // const QString outPng = "C:/FTU_ATE/Ripple_Images/Plus5V/scope_capture_" + timestamp + ".png";

    acquireAndSaveScopePNG(outPng,
                           &l_min,
                           &l_max,
                           &l_Vpp,
                           /*voltsPerDiv*/ 0.100,
                           /*timePerDiv*/ 2e-6,
                           /*settleFrac*/ 0.10);
    ui->MAX_R_p5V_LE->setText(QString::number(l_max, 'f', 4));
    ui->MIN_R_p5V_LE->setText(QString::number(l_min, 'f', 4));

    maxResult5V = (l_max < 0.200) ? "PASS" : "FAIL";
    minResult5V = (l_min > -0.200) ? "PASS" : "FAIL";
    QString Result5V = (maxResult5V == "PASS" && minResult5V == "PASS") ? "PASS" : "FAIL";
    ui->Result_P5V->setText(Result5V);
    ui->Result_P5V->setStyleSheet(Result5V == "PASS" ? "color: black; background-color: green;"
                                                     : "color: black"
                                                       "; background-color: red;");

    //    qDebug() << "Max Result:" << maxResult5V << ", Value:" << l_max;
    //    qDebug() << "Min Result:" << minResult5V << ", Value:" << l_min;
    //    qDebug() << "Overall Result:" << Result5V;

    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
        on_SRU_DC_N_5V_IV_PB_clicked(1);
    }
    //    QPixmap pm(outPng);
    //    ui->Ripple_graph5V->setPixmap(
    //        pm.scaled(ui->Ripple_graph5V->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void MainWindow::on_Ripple_N5V_pb_clicked()
{
    double l_min = 0;
    double l_max = 0;
    double l_Vpp = 0;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");
    QString folderPath2 = "C:/FTU_ATE/Ripple_Images/Minus5V";
    QDir dir;
    if (!dir.exists(folderPath2)) {
        if (!dir.mkpath(folderPath2)) {
            return; // exit if folder creation fails
        }
    }
    QString outPng = folderPath2 + "/scope_capture_" + timestamp + ".png";
    //    const QString outPng = "C:/FTU_ATE/Ripple_Images/Minus5V/scope_capture_" + timestamp + ".png";
    //    std::vector<double> y;
    //    niScope_wfmInfo info;
    acquireAndSaveScopePNG(outPng, &l_min, &l_max, &l_Vpp, 0.100, 2e-6, 0.10);

    ui->MAX_R_N5V_LE->setText(QString::number(l_max, 'f', 4));
    ui->MIN_R_N5V_LE->setText(QString::number(l_min, 'f', 4));

    maxResultN5V = (l_max < 0.200) ? "PASS" : "FAIL";

    minResultN5V = (l_min > -0.200) ? "PASS" : "FAIL";

    QString ResultN5V = (maxResultN5V == "PASS" && minResultN5V == "PASS") ? "PASS" : "FAIL";

    ui->Result_N5V->setText(ResultN5V);
    ui->Result_N5V->setStyleSheet(ResultN5V == "PASS" ? "color: black; background-color: green;"
                                                      : "color: black; background-color: red;");
    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
        on_SRU_DC_5V_L10_PB_clicked(1);
    }
    //    QPixmap pm(outPng);
    //    ui->Ripple_graphN5V->setPixmap(
    //        pm.scaled(ui->Ripple_graphN5V->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::on_Ripple_3p3V_pb_clicked()
{
    double l_min = 0;
    double l_max = 0;
    double l_Vpp = 0;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");

    QString folderPath3 = "C:/FTU_ATE/Ripple_Images/3P3";
    QDir dir;
    if (!dir.exists(folderPath3)) {
        if (!dir.mkpath(folderPath3)) {
            return; // exit if folder creation fails
        }
    }
    QString outPng = folderPath3 + "/scope_capture_" + timestamp + ".png";

    //const QString outPng = "C:/FTU_ATE/Ripple_Images/3P3/scope_capture_" + timestamp + ".png";
    acquireAndSaveScopePNG(outPng,
                           &l_min,
                           &l_max,
                           &l_Vpp,
                           /*voltsPerDiv*/ 0.100,
                           /*timePerDiv*/ 2e-6,
                           /*settleFrac*/ 0.10);
    //    ui->MAX_R_3p3V_LE->setText(QString::number((int) (l_max * 1000)));
    //    ui->MIN_R_3p3V_LE->setText(QString::number((int) (l_min * 1000)));

    ui->MAX_R_3p3V_LE->setText(QString::number(l_max, 'f', 4));
    ui->MIN_R_3p3V_LE->setText(QString::number(l_min, 'f', 4));

    maxResult3p3V = (l_max < 0.200) ? "PASS" : "FAIL";
    minResult3p3V = (l_min > -0.200) ? "PASS" : "FAIL";
    QString Result3p3V = (maxResult3p3V == "PASS" && minResult3p3V == "PASS") ? "PASS" : "FAIL";

    ui->Result_3p3V->setText(Result3p3V);
    ui->Result_3p3V->setStyleSheet(Result3p3V == "PASS" ? "color: black; background-color: green;"
                                                        : "color: black; background-color: red;");
    //    QPixmap pm(outPng);
    //    ui->Ripple_graph3p3V->setPixmap(
    //        pm.scaled(QSize(700, 120), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //    QPixmap scaledPm = pm.scaled(QSize(1118, 120), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //    ui->Ripple_graph3p3V->setPixmap(scaledPm);

    /***************************1***********************************/

    //    QSize labelSize = ui->Ripple_graph3p3V->size();
    //    QPixmap scaledPm = pm.scaled(labelSize,
    //                                 Qt::KeepAspectRatioByExpanding,
    //                                 Qt::SmoothTransformation);
    //    QRect rect((scaledPm.width() - labelSize.width()) / 2,
    //               (scaledPm.height() - labelSize.height()) / 2,
    //               labelSize.width(),
    //               labelSize.height());
    //    QPixmap croppedPm = scaledPm.copy(rect);
    //    ui->Ripple_graph3p3V->setPixmap(croppedPm);
    //    ui->Ripple_graph3p3V->setAlignment(Qt::AlignCenter);

    /*****************************2*********************************/

    //    QSize labelSize = ui->Ripple_graph3p3V->size();
    //    QPixmap scaledPm = pm.scaled(labelSize,
    //                                 Qt::KeepAspectRatioByExpanding,
    //                                 Qt::SmoothTransformation);
    //    ui->Ripple_graph3p3V->setPixmap(scaledPm);
    //    ui->Ripple_graph3p3V->setAlignment(Qt::AlignCenter);

    /*****************************3*********************************/

    //    QSize labelSize = ui->Ripple_graph3p3V->size();
    //    QPixmap scaledPm = pm.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //    ui->Ripple_graph3p3V->setPixmap(scaledPm);
    //    ui->Ripple_graph3p3V->setAlignment(Qt::AlignCenter);

    //    ui->Ripple_graph3p3V->setScaledContents(true);
    //    ui->Ripple_graph3p3V->setPixmap(pm);

    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
        on_SRU_DC_3p3V_L10_PB_clicked(1);
    }
}

void MainWindow::on_PS1_28V_pb_clicked(bool checked)
{
    if (checked) {
        emit LED_PS1_Sig_MT(checked);
        ui->PS1_28V_le->setText("Observed Voltages on banana Sokect");
    } else {
        emit LED_PS1_Sig_MT(checked);
    }
}

void MainWindow::on_PS2_12_pb_clicked(bool checked)
{
    if (checked) {
        emit LED_PS2_Sig_MT(checked);
        ui->PS2_12_le->setText("Observed Voltages on banana Socket");
    } else {
        emit LED_PS2_Sig_MT(checked);
    }
}

void MainWindow::on_PS3_5V_pb_clicked(bool checked)
{
    if (checked) {
        emit LED_PS3_Sig_MT(checked);
        ui->PS3_5V_le->setText("Observed Voltages on banana Socket");
    } else {
        emit LED_PS3_Sig_MT(checked);
    }
}

void MainWindow::on_PS4_3p3V_pb_clicked(bool checked)
{
    if (checked) {
        emit LED_PS4_Sig_MT(checked);
        ui->PS4_3p3V_le->setText("Observed Voltages on banana Socket");
    } else {
        emit LED_PS4_Sig_MT(checked);
    }
}

void MainWindow::on_PS5_plus5V_pb_clicked(bool checked)
{
    if (checked) {
        emit LED_PS5_Sig_MT(checked);
        ui->PS5_plus5V_le->setText("Observed Voltages on banana Socket");
    } else {
        emit LED_PS5_Sig_MT(checked);
    }
}

void MainWindow::on_PS6_N_5V_pb_clicked(bool checked)
{
    if (checked) {
        emit LED_PS6_Sig_MT(checked);
        ui->PS6_N_5V_le->setText("Observed Voltages on banana Socket");
    } else {
        emit LED_PS6_Sig_MT(checked);
    }
}

void MainWindow::on_PS7_External_V_pb_clicked(bool checked)
{
    if (checked) {
        emit LED_PS7_Sig_MT(checked);
        ui->PS7_External_V_le->setText("Observed Voltages on banana Socket");
    } else {
        emit LED_PS7_Sig_MT(checked);
    }
}

void MainWindow::on_RS422_ch1_pb_clicked(bool checked)
{
    if (checked) {
        emit RS422_card1Signal_OFF();
        ui->RS422_ch1_le->setText("Obseverd voltages on banana sockect");
    } else {
        emit RS422_card1Signal_ON();
    }
}

void MainWindow::onTable1CellClicked(int row, int column)
{
    int lastRow = ui->tableWidget_1->rowCount() - 1;
    if (row == lastRow && column == 0) {
        ui->tableWidget_1->removeRow(lastRow);

        insertEmployeeRowAbove(ui->tableWidget_1, ui->tableWidget_1->rowCount(), importedFont);
        addPlusRow(ui->tableWidget_1, importedFont);
    }
}
void MainWindow::onTable2CellClicked(int row, int column)
{
    int lastRow = ui->tableWidget_2->rowCount() - 1;
    if (row == lastRow && column == 0) {
        ui->tableWidget_2->removeRow(lastRow);

        // Insert new employee row at the end (after removal)
        insertEmployeeRowAbove(ui->tableWidget_2, ui->tableWidget_2->rowCount(), importedFont);

        addPlusRow(ui->tableWidget_2, importedFont);
    }
}
void MainWindow::onTable3CellClicked(int row, int column)
{
    int lastRow = ui->tableWidget_3->rowCount() - 1;
    if (row == lastRow && column == 0) {
        ui->tableWidget_3->removeRow(lastRow);

        // Insert new employee row at the end (after removal)
        insertEmployeeRowAbove(ui->tableWidget_3, ui->tableWidget_3->rowCount(), importedFont);

        addPlusRow(ui->tableWidget_3, importedFont);
    }
}
void MainWindow::onTable4CellClicked(int row, int column)
{
    int lastRow = ui->tableWidget_4->rowCount() - 1;
    if (row == lastRow && column == 0) {
        ui->tableWidget_4->removeRow(lastRow);

        // Insert new employee row at the end (after removal)
        insertEmployeeRowAbove(ui->tableWidget_4, ui->tableWidget_4->rowCount(), importedFont);

        addPlusRow(ui->tableWidget_4, importedFont);
    }
}
void MainWindow::onTable5CellClicked(int row, int column)
{
    int lastRow = ui->tableWidget_5->rowCount() - 1;
    if (row == lastRow && column == 0) {
        ui->tableWidget_5->removeRow(lastRow);

        // Insert new employee row at the end (after removal)
        insertEmployeeRowAbove(ui->tableWidget_5, ui->tableWidget_5->rowCount(), importedFont);

        addPlusRow(ui->tableWidget_5, importedFont);
    }
}
void MainWindow::onTable6CellClicked(int row, int column)
{
    int lastRow = ui->tableWidget_6->rowCount() - 1;
    if (row == lastRow && column == 0) {
        ui->tableWidget_6->removeRow(lastRow);

        // Insert new employee row at the end (after removal)
        insertEmployeeRowAbove(ui->tableWidget_6, ui->tableWidget_6->rowCount(), importedFont);

        addPlusRow(ui->tableWidget_6, importedFont);
    }
}
void MainWindow::insertEmployeeRowAbove(QTableWidget *table, int clickedRow, const QFont &font)
{
    QFont dataFont = font;
    dataFont.setBold(false); // Ensure consistent font across all cells

    int rowCount = table->rowCount();
    if (clickedRow < 0 || clickedRow > rowCount) {
        qWarning() << "Invalid clickedRow:" << clickedRow << "rowCount:" << rowCount;
        return;
    }

    table->insertRow(clickedRow);
    int sourceRow = (clickedRow == rowCount) ? clickedRow - 1 : clickedRow + 1;

    if (sourceRow < 0 || sourceRow >= table->rowCount()) {
        qWarning() << "Source row out of bounds:" << sourceRow;
        return;
    }

    // --- Define combo box columns based on table ---
    QSet<int> comboBoxColumns;
    if (table == ui->tableWidget_1) {
        comboBoxColumns = {1, 2};
    } else if (table == ui->tableWidget_2) {
        comboBoxColumns = {1, 2, 6};
    } else if (table == ui->tableWidget_3) {
        comboBoxColumns = {1, 2, 8};
    } else if (table == ui->tableWidget_4) {
        comboBoxColumns = {3, 4, 9};
    } else if (table == ui->tableWidget_5) {
        comboBoxColumns = {1, 9};
    } else if (table == ui->tableWidget_6) {
        comboBoxColumns = {3, 4, 9};
    } else {
        comboBoxColumns = {};
    }

    for (int col = 0; col < table->columnCount(); ++col) {
        if (comboBoxColumns.contains(col)) {
            QComboBox *sourceCombo = qobject_cast<QComboBox *>(table->cellWidget(sourceRow, col));
            QComboBox *newCombo = new QComboBox();
            newCombo->setEditable(true);

            if (sourceCombo) {
                for (int i = 0; i < sourceCombo->count(); ++i)
                    newCombo->addItem(sourceCombo->itemText(i));

                QString currentText = sourceCombo->currentText();
                if (!currentText.isEmpty() && newCombo->findText(currentText) == -1)
                    newCombo->addItem(currentText);

                newCombo->setCurrentText(currentText);
            }

            dataFont = font;
            dataFont.setBold(false);

            newCombo->setFont(dataFont);
            if (newCombo->lineEdit()) {
                newCombo->lineEdit()->setFont(dataFont);
                newCombo->lineEdit()->setAlignment(Qt::AlignCenter);
            }

            table->setCellWidget(clickedRow, col, newCombo);
        } else {
            QTableWidgetItem *emptyItem = new QTableWidgetItem("");
            emptyItem->setTextAlignment(Qt::AlignCenter);
            emptyItem->setFont(dataFont);
            emptyItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
            table->setItem(clickedRow, col, emptyItem);
        }
    }

    table->update();
}
void MainWindow::addPlusRow(QTableWidget *table, const QFont &importedFont)
{
    int newRow = table->rowCount();
    table->insertRow(newRow);

    //    qDebug() << "[addPlusRow] Using font:" << importedFont.family()
    //             << "Size:" << importedFont.pointSize() << "Bold:" << importedFont.bold();

    QTableWidgetItem *plusItem = new QTableWidgetItem("+");
    plusItem->setTextAlignment(Qt::AlignCenter);
    plusItem->setFont(importedFont);
    plusItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    table->setItem(newRow, 0, plusItem);
    table->setSpan(newRow, 0, 1, table->columnCount());

    for (int col = 1; col < table->columnCount(); ++col) {
        QTableWidgetItem *emptyItem = new QTableWidgetItem("");
        emptyItem->setFont(importedFont);
        emptyItem->setTextAlignment(Qt::AlignCenter);
        emptyItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
        table->setItem(newRow, col, emptyItem);
    }

    table->viewport()->update();
}

void MainWindow::importExcelToMultipleTables()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Open Excel File",
                                                    "",
                                                    "Excel Files (*.xls *.xlsx)");
    if (filePath.isEmpty())
        return;

    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);

    QAxObject *workbooks = excel.querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", filePath);

    if (!workbook) {
        QMessageBox::warning(this, "Error", "Failed to open Excel file.");
        delete workbooks;
        excel.dynamicCall("Quit()");
        return;
    }

    QAxObject *worksheets = workbook->querySubObject("Worksheets");
    if (!worksheets) {
        QMessageBox::warning(this, "Error", "No worksheets found.");
        workbook->dynamicCall("Close()");
        delete workbook;
        delete workbooks;
        excel.dynamicCall("Quit()");
        return;
    }

    for (uint16_t i = 0; i < 1000; i++) {
        g_TestPoint_Table_Data[i].StartMsg = 0x24;
        g_TestPoint_Table_Data[i].packetSize = sizeof(TestPoint_Table_Data);
        g_TestPoint_Table_Data[i].FTU_Test_No = 0xFFFF;
        g_TestPoint_Table_Data[i].Signal_Type = 0xFF;
        g_TestPoint_Table_Data[i].Signal_Injection_Point = 0xFF;
        g_TestPoint_Table_Data[i].Safe_engage_Time_Secs = 5432.1;
        g_TestPoint_Table_Data[i].Invert_Flag = 0xFF;
        g_TestPoint_Table_Data[i].Slat_Input = 5432.1;
        g_TestPoint_Table_Data[i].No_of_Repeats = 0xFF;
        g_TestPoint_Table_Data[i].Time_Between_Repeats = 5432.1;
        g_TestPoint_Table_Data[i].Amplitude = 5432.1;
        g_TestPoint_Table_Data[i].Pulse_Width_sec = 5432.1;
        g_TestPoint_Table_Data[i].Type_of_Input = 0xFF;
        g_TestPoint_Table_Data[i].C0 = 5432.1;
        g_TestPoint_Table_Data[i].C1 = 5432.1;
        g_TestPoint_Table_Data[i].Amplitude_percent_of_stroke = 5432.1;
        g_TestPoint_Table_Data[i].Start_FreqHz = 5432.1;
        g_TestPoint_Table_Data[i].End_FreqHz = 5432.1;
        g_TestPoint_Table_Data[i].Freq_StepHz = 5432.1;
        g_TestPoint_Table_Data[i].DwellDuration_Secs = 5432.1;
        g_TestPoint_Table_Data[i].Max_Amplitude = 5432.1;
        g_TestPoint_Table_Data[i].Impulse_Amplitude = 5432.1;
        g_TestPoint_Table_Data[i].Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse = 5432.1;
        g_TestPoint_Table_Data[i].Wo = 5432.1;
        g_TestPoint_Table_Data[i].Wf = 5432.1;
        g_TestPoint_Table_Data[i].Sweep_Duration = 5432.1;
        g_TestPoint_Table_Data[i].Pulse_Width = 5432.1;
        g_TestPoint_Table_Data[i].CRC_WORD = 0xFFFF;
        g_TestPoint_Table_Data[i].EndMsg = 0xFFFF;
    }

    int sheetCount = worksheets->property("Count").toInt();
    int tableCount = tableWidgets.size();
    int maxCount = qMin(sheetCount, tableCount);

    for (int i = 1; i <= maxCount; ++i) {
        QTableWidget *table = tableWidgets[i - 1];
        if (!table)
            continue;

        QAxObject *sheet = worksheets->querySubObject("Item(int)", i);
        if (!sheet)
            continue;

        importedFont = extractFontFromExcel(sheet);
        QFont headerFont = importedFont;
        headerFont.setBold(true);
        QFont dataFont = importedFont;
        dataFont.setBold(false);

        QAxObject *usedRange = sheet->querySubObject("UsedRange");
        QAxObject *rows = usedRange->querySubObject("Rows");
        QAxObject *cols = usedRange->querySubObject("Columns");

        int rowCount = rows->property("Count").toInt();
        int colCount = cols->property("Count").toInt();

        if (isSpecialTable(table)) {
            if (rowCount < 2)
                continue;

            int headerRow = 2;
            int maxHeaderCols = 0;

            for (int c = colCount; c >= 1; --c) {
                QAxObject *cell = sheet->querySubObject("Cells(int,int)", headerRow, c);
                QString val = cell ? cell->property("Value").toString().trimmed() : QString();
                if (cell)
                    delete cell;
                if (!val.isEmpty()) {
                    maxHeaderCols = c;
                    break;
                }
            }

            if (maxHeaderCols == 0)
                maxHeaderCols = colCount;

            QStringList headers;
            for (int c = 1; c <= maxHeaderCols; ++c) {
                QAxObject *cell = sheet->querySubObject("Cells(int,int)", headerRow, c);
                QString val = cell ? cell->property("Value").toString().trimmed() : QString();
                if (cell)
                    delete cell;
                headers << val;
            }

            // --- Step 2: Find max data columns ---
            int maxDataCols = maxHeaderCols;
            for (int r = headerRow + 1; r <= rowCount; ++r) {
                int lastCol = 0;
                for (int c = colCount; c >= 1; --c) {
                    QAxObject *cell = sheet->querySubObject("Cells(int,int)", r, c);
                    QString val = cell ? cell->property("Value").toString().trimmed() : QString();
                    if (cell)
                        delete cell;
                    if (!val.isEmpty()) {
                        lastCol = c;
                        break;
                    }
                }
                if (lastCol > maxDataCols)
                    maxDataCols = lastCol;
            }

            // --- Step 3: Final column count ---
            int finalColumnCount = qMax(maxHeaderCols, maxDataCols);

            // --- Step 4: Pad headers to finalColumnCount ---
            while (headers.size() < finalColumnCount)
                headers << "";

            // --- Step 5: Setup table columns ---
            table->clearContents();
            table->setRowCount(0);
            table->setColumnCount(finalColumnCount);
            table->setHorizontalHeaderLabels(headers);

            // Set bold headers
            for (int c = 0; c < headers.size(); ++c) {
                QTableWidgetItem *headerItem = new QTableWidgetItem(headers[c]);
                headerItem->setFont(headerFont);
                headerItem->setTextAlignment(Qt::AlignCenter);
                table->setHorizontalHeaderItem(c, headerItem);
            }

            // --- Step 6: Insert data rows using finalColumnCount ---
            for (int r = headerRow + 1; r <= rowCount; ++r) {
                int lastCol = 0;
                for (int c = finalColumnCount; c >= 1; --c) {
                    QAxObject *cell = sheet->querySubObject("Cells(int,int)", r, c);
                    QString val = cell ? cell->property("Value").toString().trimmed() : QString();
                    if (cell)
                        delete cell;
                    if (!val.isEmpty()) {
                        lastCol = c;
                        break;
                    }
                }
                if (lastCol == 0)
                    continue;

                QStringList rowData;
                for (int c = 1; c <= lastCol; ++c) {
                    QAxObject *cell = sheet->querySubObject("Cells(int,int)", r, c);
                    QString val = cell ? cell->property("Value").toString().trimmed() : QString();
                    if (cell)
                        delete cell;
                    rowData << val;
                }

                while (rowData.size() < finalColumnCount)
                    rowData << "";

                int newRow = table->rowCount();
                table->insertRow(newRow);

                const QStringList booleanOptions = {"FALSE", "TRUE"};

                for (int c = 0; c < rowData.size(); ++c) {
                    const QStringList signalTypes = {"SQUARE_PULSE",
                                                     "SQUARE_DOUBLET",
                                                     "HALF_SINE_PULSE",
                                                     "FULL_SINE_DOUBLET",
                                                     "PULSE_TRAIN_3_2_1_1",
                                                     "LINEAR_SINE_SWEEP",
                                                     "LOGARITHMIC_SINE_SWEEP",
                                                     "RANDOM_SIGNAL"};

                    const QStringList controlSurfaces = {"INBOARD_ELEVON_SYMMETRIC",
                                                         "OUTBOARD_ELEVON_SYMMETRIC",
                                                         "INBOARD_ELEVON_ASYMMETRIC",
                                                         "OUTBOARD_ELEVON_ASYMMETRIC",
                                                         "INBOARD_AND_OUTBOARD_ELEVON_SYMMETRIC",
                                                         "INBOARD_AND_OUTBOARD_ELEVON_ASYMMETRIC",
                                                         "RUDDER",
                                                         "CANARD_SYMMETRIC",
                                                         "CANARD_ASYMMETRIC",
                                                         "PITCH_STICK_FTU_INPUT",
                                                         "ROLL_STICK_FTU_INPUT",
                                                         "RUDDER_PEDAL_FTU_INPUT",
                                                         "SLAT_INPUT",
                                                         "AIRBRAKE_INPUT"};

                    if (QWidget *w = table->cellWidget(newRow, c))
                        w->deleteLater();
                    if (QTableWidgetItem *item = table->takeItem(newRow, c))
                        delete item;

                    QString value = rowData[c];

                    bool isComboBoxColumn = false;
                    bool useCombo = false;

                    if (table == ui->tableWidget_1) {
                        isComboBoxColumn = (c == 1 || c == 2);
                        useCombo = (newRow >= 0) && isComboBoxColumn;
                    } else if (table == ui->tableWidget_2) {
                        isComboBoxColumn = (c == 1 || c == 2 || c == 6);
                        useCombo = (newRow >= 0) && isComboBoxColumn;
                    } else if (table == ui->tableWidget_3) {
                        isComboBoxColumn = (c == 1 || c == 2 || c == 8);
                        useCombo = (newRow >= 0) && isComboBoxColumn;
                    } else if (table == ui->tableWidget_4) {
                        isComboBoxColumn = (c == 3 || c == 4 || c == 9);
                        useCombo = (newRow >= 0) && isComboBoxColumn;
                    } else if (table == ui->tableWidget_5) {
                        isComboBoxColumn = (c == 1 || c == 3 || c == 9);
                        useCombo = (newRow >= 0) && isComboBoxColumn;
                    } else if (table == ui->tableWidget_6) {
                        isComboBoxColumn = (c == 3 || c == 4 || c == 9);
                        useCombo = (newRow >= 0) && isComboBoxColumn;
                    }

                    // Example of mapping table pointer and column index to which list to add
                    if (useCombo) {
                        QComboBox *combo = new QComboBox(table);
                        combo->setEditable(true);
                        //if (combo->lineEdit())
                        // combo->lineEdit()->setAlignment(Qt::AlignCenter);

                        QObject::connect(combo,
                                         QOverload<int>::of(&QComboBox::currentIndexChanged),
                                         this,
                                         [combo]() {
                                             QString currentText = combo->currentText().trimmed();
                                             // Always keep editable = true
                                             combo->setEditable(true);

                                             // Center text in line edit
                                             // if (combo->lineEdit())
                                             // combo->lineEdit()->setAlignment(Qt::AlignCenter);
                                         });

                        if (combo->lineEdit()) {
                            combo->lineEdit()->setFont(dataFont);
                            //ombo->lineEdit()->setAlignment(Qt::AlignCenter);
                        }

                        //                        combo->setItemDelegate(new CenteredItemDelegate(combo));

                        //                        if (table == ui->tableWidget_1) {
                        //                            table->setItemDelegateForColumn(3, new DoubleRangeDelegate(this));
                        //                        }

                        if (table == ui->tableWidget_1) {
                            if (c == 1)
                                addComboBoxItems(combo, signalTypes, value);
                            else if (c == 2)
                                addComboBoxItems(combo, controlSurfaces, value);
                        } else if (table == ui->tableWidget_2) {
                            if (c == 1)
                                addComboBoxItems(combo, signalTypes, value);
                            else if (c == 2)
                                addComboBoxItems(combo, controlSurfaces, value);
                            else if (c == 6) {
                                if (value == "TRUE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                } else if (value == "FALSE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                }
                            }
                        } else if (table == ui->tableWidget_3) {
                            if (c == 1)
                                addComboBoxItems(combo, signalTypes, value);
                            else if (c == 2)
                                addComboBoxItems(combo, controlSurfaces, value);
                            else if (c == 8) {
                                if (value == "TRUE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                } else if (value == "FALSE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                }
                            }
                        } else if (table == ui->tableWidget_4) {
                            if (c == 3)
                                addComboBoxItems(combo, signalTypes, value);
                            else if (c == 4)
                                addComboBoxItems(combo, controlSurfaces, value);
                            else if (c == 9) {
                                if (value == "TRUE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                } else if (value == "FALSE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                }
                            }
                        } else if (table == ui->tableWidget_5) {
                            if (c == 1)
                                addComboBoxItems(combo, signalTypes, value);
                            else if (c == 3)
                                addComboBoxItems(combo, controlSurfaces, value);
                            else if (c == 9) {
                                if (value == "TRUE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                } else if (value == "FALSE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                }
                            }
                        } else if (table == ui->tableWidget_6) {
                            if (c == 3)
                                addComboBoxItems(combo, signalTypes, value);
                            else if (c == 4)
                                addComboBoxItems(combo, controlSurfaces, value);
                            else if (c == 9) {
                                if (value == "TRUE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                } else if (value == "FALSE") {
                                    addComboBoxItems(combo, booleanOptions, value);
                                }
                            }
                        }

                        //if (combo->lineEdit())
                        // combo->lineEdit()->setAlignment(Qt::AlignCenter);

                        combo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
                        combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

                        table->setCellWidget(newRow, c, combo);
                    } else {
                        if (table == ui->tableWidget_1 && (newRow >= 0)
                            && (c >= 3 && c <= 10)) // Covers columns 3 through 10
                        {
                            QLineEdit *editor = new QLineEdit(table);
                            QRegularExpression regExp;

                            // Choose regex based on column
                            switch (c) {
                            case 3:
                                regExp = QRegularExpression(
                                    "^(2(\\.0*)?|1(\\.\\d+)?|0(\\.\\d+)?)$"); // 0 to 2
                                break;
                            case 4:
                                regExp = QRegularExpression(
                                    "^(4(\\.0*)?|[0-3](\\.\\d+)?|0(\\.\\d+)?)$"); // 0 to 4
                                break;
                            case 5:
                            case 6:
                            case 7:
                            case 8:
                            case 9:
                            case 10:
                                regExp = QRegularExpression("^\\d+\\.\\d+$");
                                break;
                            default:
                                break;
                            }

                            QRegularExpressionValidator *validator
                                = new QRegularExpressionValidator(regExp, editor);
                            editor->setValidator(validator);
                            editor->setFont(dataFont);
                            editor->setAlignment(Qt::AlignCenter);
                            editor->setText(value); // Make sure 'value' is declared in scope
                            table->setCellWidget(newRow, c, editor);
                        } else {
                            QTableWidgetItem *item = new QTableWidgetItem(value);
                            item->setFont(dataFont);
                            item->setTextAlignment(Qt::AlignCenter);
                            table->setItem(newRow, c, item);
                        }
                        QTableWidgetItem *item = new QTableWidgetItem(value);
                        item->setFont(dataFont);
                        item->setTextAlignment(Qt::AlignCenter);
                        table->setItem(newRow, c, item);
                    }
                }
            }

            table->horizontalHeader()->setStyleSheet(
                "QHeaderView::section { border-bottom: 1px solid black; }");
            table->setShowGrid(true);
            table->setStyleSheet("QTableView { gridline-color: black; }");
            table->setItemDelegate(new TopBorderDelegate(table));

            QHeaderView *header = table->horizontalHeader();
            table->verticalHeader()->setVisible(false);

            header->setVisible(true);
            header->setSectionsClickable(true);
            header->setHighlightSections(true);
            for (int c = 0; c < table->columnCount(); ++c)
                header->setSectionResizeMode(c, QHeaderView::Interactive);

            table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
            table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

            adjustTableToLayoutSize(table);
            addPlusRow(table, dataFont);

            table->setItemDelegate(new FontRespectingDelegate(table));
            table->update();

        } else {
            table->clearContents();
            table->setRowCount(0);
            table->setColumnCount(colCount);

            QFont dataFont = importedFont;
            dataFont.setBold(false);

            for (int r = 1; r <= rowCount; ++r) {
                int newRow = table->rowCount();
                table->insertRow(newRow);

                for (int c = 1; c <= colCount; ++c) {
                    QAxObject *cell = sheet->querySubObject("Cells(int,int)", r, c);
                    QString val = cell ? cell->property("Value").toString().trimmed() : QString();
                    if (cell)
                        delete cell;

                    QTableWidgetItem *item = new QTableWidgetItem(val);
                    item->setFont(dataFont);
                    item->setTextAlignment(Qt::AlignCenter);
                    table->setItem(newRow, c - 1, item);
                }
            }

            QHeaderView *header = table->horizontalHeader();
            for (int c = 0; c < table->columnCount(); ++c)
                header->setSectionResizeMode(c, QHeaderView::Interactive);
            header->setStretchLastSection(false);

            table->setItemDelegate(new FontRespectingDelegate(table));
            table->update();
        }

        delete rows;
        delete cols;
        delete usedRange;
        delete sheet;
    }

    workbook->dynamicCall("Close()");
    delete worksheets;
    delete workbook;
    delete workbooks;
    excel.dynamicCall("Quit()");

    //    qDebug() << "Excel import completed.";
}

bool MainWindow::isSpecialTable(QTableWidget *table)
{
    return table == ui->tableWidget_1 || table == ui->tableWidget_2 || table == ui->tableWidget_3
           || table == ui->tableWidget_4 || table == ui->tableWidget_5
           || table == ui->tableWidget_6;
}
void MainWindow::adjustTableToLayoutSize(QTableWidget *table)
{
    if (!table)
        return;

    int totalWidth = table->viewport()->width(); // width of the visible area inside the table widget

    int colCount = table->columnCount();
    if (colCount == 0)
        return;

    // For example, distribute widths evenly:
    int colWidth = totalWidth / colCount;

    for (int i = 0; i < colCount; ++i) {
        table->setColumnWidth(i, colWidth);
    }
}

QFont MainWindow::extractFontFromExcel(QAxObject *sheet)
{
    QString fontName = "Calibri";
    int fontSize = 11;
    bool fontBold = false;

    QAxObject *row = sheet->querySubObject("Rows(int)", 1); // First row
    if (row) {
        QAxObject *fontObj = row->querySubObject("Font");
        if (fontObj) {
            QVariant boldVal = fontObj->property("Bold");
            if (!boldVal.isNull()) {
                fontName = fontObj->property("Name").toString();
                fontSize = fontObj->property("Size").toInt();
                fontBold = boldVal.toBool();
            }
            delete fontObj;
        }
        delete row;
    }

    if (!fontBold) {
        for (int c = 1; c <= 10; ++c) {
            QAxObject *cell = sheet->querySubObject("Cells(int,int)", 1, c);
            if (!cell)
                continue;

            QString val = cell->property("Value").toString();
            if (!val.isEmpty()) {
                cell->dynamicCall("Select()"); // Help Excel refresh formatting

                QAxObject *fontObj = cell->querySubObject("Font");
                if (fontObj) {
                    QVariant boldVal = fontObj->property("Bold");
                    if (!boldVal.isNull() && boldVal.toBool()) {
                        fontName = fontObj->property("Name").toString();
                        fontSize = fontObj->property("Size").toInt();
                        fontBold = true;
                        delete fontObj;
                        delete cell;
                        break;
                    }
                    delete fontObj;
                }
            }
            delete cell;
        }
    }

    QFont importedFont(fontName, fontSize);
    importedFont.setBold(fontBold);

    //    qDebug() << "Extracted Header Font:" << fontName << fontSize << (fontBold ? "Bold" : "Regular");

    return importedFont;
}

void MainWindow::exportAllTablesToExcel()
{
    QStringList groupBoxTitles = {ui->table1_groupBox->title(),
                                  ui->table2_groupBox->title(),
                                  ui->table3_groupBox->title(),
                                  ui->table4_groupBox->title(),
                                  ui->table5_groupBox->title(),
                                  ui->table6_groupBox->title()};

    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Save Excel File",
                                                    "",
                                                    "Excel Files (*.xlsx *.xls)");
    if (filePath.isEmpty())
        return;

    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);

    QAxObject *workbooks = excel.querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add()");
    QAxObject *sheets = workbook->querySubObject("Worksheets");

    int existingSheetCount = sheets->property("Count").toInt();

    while (existingSheetCount > 10) {
        QAxObject *sheetToDelete = sheets->querySubObject("Item(int)", existingSheetCount);
        if (sheetToDelete) {
            sheetToDelete->dynamicCall("Delete()");
            delete sheetToDelete;
        }
        existingSheetCount--;
    }

    while (existingSheetCount < tableWidgets.size()) {
        QAxObject *newSheet = sheets->querySubObject("Add()");
        if (newSheet) {
            int lastIndex = sheets->property("Count").toInt();
            QAxObject *lastSheet = sheets->querySubObject("Item(int)", lastIndex);
            if (lastSheet) {
                newSheet->dynamicCall("Move(QVariant)", lastSheet->asVariant());
                delete lastSheet;
            }
            delete newSheet;
            existingSheetCount++;
        } else {
            break;
        }
    }

    // Rename sheets
    for (int i = 1; i <= existingSheetCount; ++i) {
        QAxObject *sheet = sheets->querySubObject("Item(int)", i);
        if (sheet) {
            sheet->setProperty("Name", QString("Sheet%1").arg(i));
            delete sheet;
        }
    }

    // Fix sheet order if needed
    QAxObject *firstSheet = sheets->querySubObject("Item(int)", 1);
    QAxObject *lastSheet = sheets->querySubObject("Item(int)", sheets->property("Count").toInt());
    if (lastSheet && firstSheet && lastSheet->property("Name").toString() == "Sheet1") {
        lastSheet->dynamicCall("Move(QVariant)", firstSheet->asVariant());
    }
    delete firstSheet;
    delete lastSheet;

    int count = qMin(tableWidgets.size(), existingSheetCount);
    for (int i = 0; i < count; ++i) {
        QTableWidget *table = tableWidgets[i];
        QAxObject *sheet = sheets->querySubObject("Item(int)", i + 1);
        if (!sheet)
            continue;

        QAxObject *usedRange = sheet->querySubObject("UsedRange");
        if (usedRange) {
            usedRange->dynamicCall("ClearContents()");
            delete usedRange;
        }

        int rowCount = table->rowCount();
        int colCount = table->columnCount();

        // Use group box title
        QString groupBoxTitle = (i < groupBoxTitles.size()) ? groupBoxTitles[i] : "";

        // Merge first row and center title
        QChar lastColChar = QChar('A' + colCount - 1);
        QString rangeStr = QString("A1:%1%2").arg(lastColChar).arg(1);
        QAxObject *range = sheet->querySubObject("Range(const QString&)", rangeStr);
        if (range) {
            range->dynamicCall("Merge()");
            range->setProperty("Value", groupBoxTitle);
            range->setProperty("HorizontalAlignment", -4108); // Center alignment
            delete range;
        }

        // Export headers in row 2
        for (int col = 0; col < colCount; ++col) {
            QString headerText = table->horizontalHeaderItem(col)
                                     ? table->horizontalHeaderItem(col)->text()
                                     : "";
            sheet->querySubObject("Cells(int,int)", 2, col + 1)->setProperty("Value", headerText);
        }

        // Export data from row 3
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < colCount; ++col) {
                QString text;

                QWidget *widget = table->cellWidget(row, col);
                if (widget) {
                    if (QComboBox *combo = qobject_cast<QComboBox *>(widget)) {
                        text = combo->currentText();
                    } else if (QLineEdit *edit = qobject_cast<QLineEdit *>(widget)) {
                        text = edit->text();
                    } else {
                        text = widget->property("text").toString();
                    }
                } else {
                    QTableWidgetItem *item = table->item(row, col);
                    text = item ? item->text() : "";
                }

                sheet->querySubObject("Cells(int,int)", row + 3, col + 1)->setProperty("Value", text);
            }
        }

        delete sheet;
    }

    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
    workbook->dynamicCall("Close()");
    excel.dynamicCall("Quit()");

    delete sheets;
    delete workbook;
    delete workbooks;
}

void MainWindow::addComboBoxItems(QComboBox *combo,
                                  const QStringList &items,
                                  const QString &initialValue)
{
    if (!initialValue.isEmpty())
        combo->addItem(initialValue);

    for (const QString &item : items) {
        if (item != initialValue)
            combo->addItem(item);
    }

    // Add empty placeholders

    combo->addItem("");
    combo->addItem("");

    if (initialValue.isEmpty())
        combo->setCurrentIndex(combo->count() - 1);
}

QString getTextFromCell(QTableWidget *table, int row, int column)
{
    if (QComboBox *combo = qobject_cast<QComboBox *>(table->cellWidget(row, column))) {
        return combo->currentText().trimmed();
    }
    if (QTableWidgetItem *item = table->item(row, column)) {
        return item->text().trimmed();
    }
    return {};
}

SignalType signalTypeFromString(const QString &str)
{
    static const QMap<QString, SignalType> map = {{"SQUARE_PULSE", SQUARE_PULSE},
                                                  {"SQUARE_DOUBLET", SQUARE_DOUBLET},
                                                  {"HALF_SINE_PULSE", HALF_SINE_PULSE},
                                                  {"FULL_SINE_DOUBLET", FULL_SINE_DOUBLET},
                                                  {"PULSE_TRAIN_3_2_1_1", PULSE_TRAIN_3_2_1_1},
                                                  {"LINEAR_SINE_SWEEP", LINEAR_SINE_SWEEP},
                                                  {"LOGARITHMIC_SINE_SWEEP", LOGARITHMIC_SINE_SWEEP},
                                                  {"RANDOM_SIGNAL", RANDOM_SIGNAL}};
    return map.value(str, SQUARE_PULSE);
}

Signal_Injection_Point signalInjectionPointFromString(const QString &str)
{
    static const QMap<QString, Signal_Injection_Point> map
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
           {"AIRBRAKE_INPUT", AIRBRAKE_INPUT}};
    return map.value(str, INBOARD_ELEVON_SYMMETRIC);
}

void MainWindow::on_Generate_Pbtn_clicked()
{
    int rowCount1 = ui->tableWidget_1->rowCount();
    int rowCount2 = ui->tableWidget_2->rowCount();
    //    int rowCount3 = ui->tableWidget_3->rowCount();
    //    int rowCount4 = ui->tableWidget_4->rowCount();
    //    int rowCount5 = ui->tableWidget_5->rowCount();
    //    int rowCount6 = ui->tableWidget_6->rowCount();

    //    int totalRowCount = rowCount1 + rowCount2 + rowCount3 + rowCount4 + rowCount5 + rowCount6;

    //  g_TestPoint_Table_Data.resize(totalRowCount);

    //    auto getUInt8 = [](QTableWidget *table, int row, int col) -> uint8_t {
    //        QTableWidgetItem *item = table->item(row, col);
    //        if (item) {
    //            bool ok;
    //            unsigned int val = item->text().toUInt(&ok);
    //            if (ok)
    //                return static_cast<uint8_t>(val);
    //        }
    //        return 0;
    //    };

    auto getUInt16 = [](QTableWidget *table, int row, int col) -> uint16_t {
        QTableWidgetItem *item = table->item(row, col);
        if (item) {
            bool ok;
            unsigned int val = item->text().toUInt(&ok);
            if (ok)
                return static_cast<uint16_t>(val);
        }
        return 0;
    };

    auto getFloat = [](QTableWidget *table, int row, int col) -> float {
        QTableWidgetItem *item = table->item(row, col);
        if (item) {
            bool ok;
            float val = item->text().toFloat(&ok);
            if (ok)
                return val;
        }
        return 0.0f;
    };

    // ------------------ Table 1 ------------------
    //    qDebug() << "========== Table 1 Data ==========";
    //    for (int row = 0, column = 0; row < rowCount1; ++row, ++column) {
    //        //auto &data = g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)];

    //        QModelIndex index = ui->tableWidget_1->model()->index(row, column);
    //        QWidget *editor = ui->tableWidget_1->indexWidget(index); // Might be null

    //        // If indexWidget doesn't return the editor (likely null), fallback:
    //        if (!editor) {
    //            editor = QApplication::focusWidget(); // Try this fallback
    //        }

    //        // Force commit if editor found
    //        if (editor) {
    //            QAbstractItemDelegate *delegate = ui->tableWidget_1->itemDelegate(index);
    //            if (delegate) {
    //                delegate->commitData(editor);
    //                delegate->closeEditor(editor);
    //            }
    //        }

    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].FTU_Test_No
    //            = getUInt16(ui->tableWidget_1, row, column);

    //        QString sigTypeText = getTextFromCell(ui->tableWidget_1, row, column);
    //        bool ok = false;
    //        int val = sigTypeText.toInt(&ok);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Signal_Type
    //            = signalTypeFromString(sigTypeText);

    //        QString injPointText = getTextFromCell(ui->tableWidget_1, row, column);
    //        val = injPointText.toInt(&ok);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Signal_Injection_Point
    //            = signalInjectionPointFromString(injPointText);

    //        //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Amplitude_percent_of_stroke
    //        //            = getFloat(ui->tableWidget_1, row, 3);

    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Amplitude_percent_of_stroke
    //            = getFloat(ui->tableWidget_1, row, column);

    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].C0 = getFloat(ui->tableWidget_1,
    //                                                                                   row,
    //                                                                                   column);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].C1 = getFloat(ui->tableWidget_1,
    //                                                                                   row,
    //                                                                                   column);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Start_FreqHz
    //            = getFloat(ui->tableWidget_1, row, column);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].End_FreqHz
    //            = getFloat(ui->tableWidget_1, row, column);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Freq_StepHz
    //            = getFloat(ui->tableWidget_1, row, column);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].DwellDuration_Secs
    //            = getFloat(ui->tableWidget_1, row, column);
    //        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Safe_engage_Time_Secs
    //            = getFloat(ui->tableWidget_1, row, column);

    //        qDebug() << "Row" << row << ", FTU_Test_No ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].FTU_Test_No
    //                 << ", Signal_Type ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Signal_Type
    //                 << ", Signal_Injection_Point ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Signal_Injection_Point
    //                 << ", @@Amplitude_percent_of_stroke ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)]
    //                        .Amplitude_percent_of_stroke
    //                 << ", C0 =" << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].C0
    //                 << ", C1 =" << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].C1
    //                 << ", Start_FreqHz ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Start_FreqHz
    //                 << ", End_FreqHz ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].End_FreqHz
    //                 << ", Freq_StepHz ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].Freq_StepHz
    //                 << ", DwellDuration_Secs ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)].DwellDuration_Secs
    //                 << ", Safe_engage_Time_Secs ="
    //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_1, row, 0)]
    //                        .Safe_engage_Time_Secs;
    //    }

    for (int row = 0; row < rowCount1 - 1; ++row) {
        // Commit editors for all relevant columns (0 to 10)
        for (int col = 0; col <= 10; ++col) {
            QModelIndex index = ui->tableWidget_1->model()->index(row, col);
            QWidget *editor = ui->tableWidget_1->indexWidget(index);
            if (!editor) {
                editor = QApplication::focusWidget();
            }
            if (editor) {
                QAbstractItemDelegate *delegate = ui->tableWidget_1->itemDelegate(index);
                if (delegate) {
                    delegate->commitData(editor);
                    delegate->closeEditor(editor);
                }
            }
        }
        int key = getUInt16(ui->tableWidget_1, row, 0);

        // Now update your data structure with the correct column values
        g_TestPoint_Table_Data[key].FTU_Test_No = getUInt16(ui->tableWidget_1, row, 0);

        QString sigTypeText = getTextFromCell(ui->tableWidget_1, row, 1);
        g_TestPoint_Table_Data[key].Signal_Type = signalTypeFromString(sigTypeText);

        QString injPointText = getTextFromCell(ui->tableWidget_1, row, 2);
        g_TestPoint_Table_Data[key].Signal_Injection_Point = signalInjectionPointFromString(
            injPointText);

        g_TestPoint_Table_Data[key].Amplitude_percent_of_stroke = getFloat(ui->tableWidget_1,
                                                                           row,
                                                                           3);
        g_TestPoint_Table_Data[key].C0 = getFloat(ui->tableWidget_1, row, 4);
        g_TestPoint_Table_Data[key].C1 = getFloat(ui->tableWidget_1, row, 5);
        g_TestPoint_Table_Data[key].Start_FreqHz = getFloat(ui->tableWidget_1, row, 6);
        g_TestPoint_Table_Data[key].End_FreqHz = getFloat(ui->tableWidget_1, row, 7);
        g_TestPoint_Table_Data[key].Freq_StepHz = getFloat(ui->tableWidget_1, row, 8);
        g_TestPoint_Table_Data[key].DwellDuration_Secs = getFloat(ui->tableWidget_1, row, 9);
        g_TestPoint_Table_Data[key].Safe_engage_Time_Secs = getFloat(ui->tableWidget_1, row, 10);

        //        qDebug() << "Row" << row << ", FTU_Test_No =" << g_TestPoint_Table_Data[key].FTU_Test_No
        //                 << ", Signal_Type =" << g_TestPoint_Table_Data[key].Signal_Type
        //                 << ", Signal_Injection_Point ="
        //                 << g_TestPoint_Table_Data[key].Signal_Injection_Point
        //                 << ", Amplitude_percent_of_stroke ="
        //                 << g_TestPoint_Table_Data[key].Amplitude_percent_of_stroke
        //                 << ", C0 =" << g_TestPoint_Table_Data[key].C0
        //                 << ", C1 =" << g_TestPoint_Table_Data[key].C1
        //                 << ", Start_FreqHz =" << g_TestPoint_Table_Data[key].Start_FreqHz
        //                 << ", End_FreqHz =" << g_TestPoint_Table_Data[key].End_FreqHz
        //                 << ", Freq_StepHz =" << g_TestPoint_Table_Data[key].Freq_StepHz
        //                 << ", DwellDuration_Secs =" << g_TestPoint_Table_Data[key].DwellDuration_Secs
        //                 << ", Safe_engage_Time_Secs ="
        //                 << g_TestPoint_Table_Data[key].Safe_engage_Time_Secs;
    }

    // ------------------ Table 2 ------------------
    //    qDebug() << "========== Table 2 Data ==========";

    for (int row = 0; row < rowCount2 - 1; ++row) {
        //        int index = rowCount1 + row;
        //auto &data = g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)];

        // Commit editors for all relevant columns (0 to 10)
        for (int col = 0; col <= 10; ++col) {
            QModelIndex index = ui->tableWidget_2->model()->index(row, col);
            QWidget *editor = ui->tableWidget_2->indexWidget(index);
            if (!editor) {
                editor = QApplication::focusWidget();
            }
            if (editor) {
                QAbstractItemDelegate *delegate = ui->tableWidget_2->itemDelegate(index);
                if (delegate) {
                    delegate->commitData(editor);
                    delegate->closeEditor(editor);
                }
            }
        }
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].FTU_Test_No
            = getUInt16(ui->tableWidget_2, row, 0);

        QString sigTypeText = getTextFromCell(ui->tableWidget_2, row, 1);
        //        bool ok = false;
        //        int val = sigTypeText.toInt(&ok);
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Signal_Type
            = signalTypeFromString(sigTypeText);

        QString injPointText = getTextFromCell(ui->tableWidget_2, row, 2);
        //        val = injPointText.toInt(&ok);
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Signal_Injection_Point
            = signalInjectionPointFromString(injPointText);

        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Impulse_Amplitude
            = getFloat(ui->tableWidget_2, row, 4);
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Pulse_Width_sec
            = getFloat(ui->tableWidget_2, row, 5);

        // Invert_Flag reading from ComboBox in column 6 (TRUE/FALSE)
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Invert_Flag
            = 0; // default to false
        if (QComboBox *combo = qobject_cast<QComboBox *>(ui->tableWidget_2->cellWidget(row, 6))) {
            QString invertText = combo->currentText().toUpper();
            g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Invert_Flag = (invertText
                                                                                        == "TRUE")
                                                                                           ? 1
                                                                                           : 0;
        } else {
            // fallback: try reading as integer or string from item if needed
            if (QTableWidgetItem *item = ui->tableWidget_2->item(row, 6)) {
                QString itemText = item->text().toUpper();
                g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Invert_Flag
                    = (itemText == "TRUE" || itemText == "1") ? 1 : 0;
            }
        }

        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Safe_engage_Time_Secs
            = getFloat(ui->tableWidget_2, row, 7);

        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].StartMsg = 0x24;
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].packetSize = sizeof(
            TestPoint_Table_Data);
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].CRC_WORD = 0;
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].EndMsg = 0x233B;
        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].CRC_WORD = CRCUtility::
            g_CRC_calc((uint8_t *) &g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)],
                       sizeof(g_TestPoint_Table_Data));

        //        qDebug() << "Row" << index << "FTU_Test_No ="
        //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].FTU_Test_No
        //                 << ", Signal_Type ="
        //                 << static_cast<int>(
        //                        g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Signal_Type)
        //                 << ", Signal_Injection_Point ="
        //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Signal_Injection_Point
        //                 << ", Impulse_Amplitude ="
        //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Impulse_Amplitude
        //                 << ", Pulse_Width ="
        //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Pulse_Width_sec
        //                 << ", Invert_Flag ="
        //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)].Invert_Flag
        //                 << ", Safe_engage_Time_Secs ="
        //                 << g_TestPoint_Table_Data[getUInt16(ui->tableWidget_2, row, 0)]
        //                        .Safe_engage_Time_Secs;
    }

    //  printStructure(g_TestPoint_Table_Data[index]);
    saveWaveformTableDataToBinFile();
    // Call update once at the end
    // update();
}

void MainWindow::saveWaveformTableDataToBinFile()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,
                                                           "Select Folder to Save Files",
                                                           QDir::homePath());

    if (folderPath.isEmpty()) {
        return; // User canceled
    }

    for (uint16_t i = 1; i < 1000; i++) {
        if (g_TestPoint_Table_Data[i].FTU_Test_No != 0xFFFF) {
            // File name uses i, so "001.bin" = g_TestPoint_Table_Data[1]
            QString fileName = QString("%1/%2.bin").arg(folderPath).arg(i, 3, 10, QChar('0'));

            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reinterpret_cast<char *>(&g_TestPoint_Table_Data[i]),
                           sizeof(TestPoint_Table_Data));
                file.close();
            } else {
                QMessageBox::critical(this,
                                      "Error",
                                      QString("Could not open file: %1").arg(fileName));
            }
        } else {
            //            qDebug() << "g_TestPoint_Table_Data[" << i << "].FTU_Test_No"
            //                     << g_TestPoint_Table_Data[i].FTU_Test_No;

            //            qDebug() << "g_TestPoint_Table_Data[" << i << "].Pulse_Width_sec"
            //                     << g_TestPoint_Table_Data[i].Pulse_Width_sec;
        }
    }

    QMessageBox::information(this,
                             "Completed",
                             "All valid TestPoint data files have been saved successfully.");
}

void MainWindow::update()
{
    int rowCount1 = ui->tableWidget_1->rowCount();
    int rowCount2 = ui->tableWidget_2->rowCount();
    int rowCount3 = ui->tableWidget_3->rowCount();
    int rowCount4 = ui->tableWidget_4->rowCount();
    int rowCount5 = ui->tableWidget_5->rowCount();
    int rowCount6 = ui->tableWidget_6->rowCount();

    int totalRowCount = rowCount1 + rowCount2 + rowCount3 + rowCount4 + rowCount5 + rowCount6;

    //    qDebug() << "========== Update() - Parsed Data ==========";

    for (int i = 0; i < totalRowCount; ++i) {
        //        const auto &data = g_TestPoint_Table_Data[i];

        //        qDebug() << "Row" << i << ", FTU_Test_No =" << data.FTU_Test_No
        //                 << ", Signal_Type =" << static_cast<int>(data.Signal_Type)
        //                 << ", Signal_Injection_Point =" << data.Signal_Injection_Point
        //                 << ", Amplitude_percent_of_stroke =" << data.Amplitude_percent_of_stroke
        //                 << ", C0 =" << data.C0 << ", C1 =" << data.C1
        //                 << ", Start_FreqHz =" << data.Start_FreqHz << ", End_FreqHz =" << data.End_FreqHz
        //                 << ", Freq_StepHz =" << data.Freq_StepHz
        //                 << ", DwellDuration_Secs =" << data.DwellDuration_Secs
        //                 << ", Impulse_Amplitude =" << data.Impulse_Amplitude
        //                 << ", Pulse_Width =" << data.Pulse_Width << ", Invert_Flag =" << data.Invert_Flag
        //                 << ", Safe_engage_Time_Secs =" << data.Safe_engage_Time_Secs;
    }
}

void MainWindow::on_DCDC_CTRL_Auto_RB_clicked()
{
    ui->plus5_groupBox->setEnabled(false);
    ui->minus5_groupBox->setEnabled(false);
    ui->groupBox_3P3->setEnabled(false);
    ui->displaycard_groupBox->setEnabled(false);
    ui->SRU_CTRL_Volt_pb->setEnabled(false);
    ui->USB_port->setEnabled(false);

    ui->groupBox_rotary_switch_test->setEnabled(false);
    ui->groupBox_rs422_loopback->setEnabled(false);
    ui->groupBox_abort_readyinit_prep->setEnabled(false);
    ui->groupBox_external_flash->setEnabled(false);
    ui->displaycard_groupBox->setEnabled(false);
    ui->SRU_DCDC_REPORT->setEnabled(false);
    ui->SRU_CntrlCard_Report->setEnabled(false);
    ui->groupBox_dip_dop_loopback->setEnabled(false);
}

void MainWindow::on_DCDC_Manual_RB_clicked()
{
    //    ui->plus5_groupBox->setEnabled(true);
    //    ui->minus5_groupBox->setEnabled(true);
    //    ui->groupBox_3P3->setEnabled(true);
    //    ui->displaycard_groupBox->setEnabled(true);
    //    ui->SRU_CTRL_Volt_pb->setEnabled(true);
    //    ui->USB_port->setEnabled(true);

    //    ui->groupBox_rotary_switch_test->setEnabled(true);
    //    ui->groupBox_rs422_loopback->setEnabled(true);
    //    ui->groupBox_abort_readyinit_prep->setEnabled(true);
    //    ui->groupBox_external_flash->setEnabled(true);
    //    ui->displaycard_groupBox->setEnabled(true);
    //    ui->SRU_DCDC_REPORT->setEnabled(true);
    //    ui->SRU_CntrlCard_Report->setEnabled(true);
    //    ui->groupBox_dip_dop_loopback->setEnabled(true);
    ui->plus5_groupBox->setEnabled(false);
    ui->minus5_groupBox->setEnabled(false);
    ui->groupBox_3P3->setEnabled(false);
    ui->displaycard_groupBox->setEnabled(false);
    ui->SRU_CTRL_Volt_pb->setEnabled(false);
    ui->USB_port->setEnabled(false);

    ui->groupBox_rotary_switch_test->setEnabled(false);
    ui->groupBox_rs422_loopback->setEnabled(false);
    ui->groupBox_abort_readyinit_prep->setEnabled(false);
    ui->groupBox_external_flash->setEnabled(false);
    ui->displaycard_groupBox->setEnabled(false);
    ui->SRU_DCDC_REPORT->setEnabled(false);
    ui->SRU_CntrlCard_Report->setEnabled(false);
    ui->groupBox_dip_dop_loopback->setEnabled(false);
}

void MainWindow::DCDC_AutoModeConfig() {}

void MainWindow::CTRL_AutoModeConfig()
{
    //    qDebug() << "CTRL_AutoModeConfig" << g_SRU_CTRL_sequence_counter;

    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
        switch (g_SRU_CTRL_sequence_counter) {
        case 1: {
            on_USB_port_clicked(true);
            break;
        }
        case 2: {
            on_RotarySwitch1_pb_clicked(true);

            break;
        }
        case 3: {
            on_RotarySwitch1_pb_clicked(false);

            break;
        }
        case 4: {
            on_RotarySwitch2_pb_clicked(true);
            break;
        }
        case 5: {
            on_RotarySwitch2_pb_clicked(false);
            break;
        }
        case 6: {
            on_RotarySwitch3_pb_clicked(true);
            break;
        }
        case 7: {
            on_RotarySwitch3_pb_clicked(false);
            break;
        }
        case 8: {
            on_CC_Ch1_TX_pb_clicked(true);
            break;
        }
        case 9: {
            on_CC_Ch2_TX_pb_clicked(true);
            break;
        }

        case 10: {
            on_CC_Discrete_ch1_OP_pb_clicked(true);
            break;
        }
        case 11: {
            on_CC_Discrete_ch1_OP_pb_clicked(false);
            break;
        }
        case 12: {
            on_CC_Discrete_ch2_OP_pb_clicked(true);
            break;
        }
        case 13: {
            on_CC_Discrete_ch2_OP_pb_clicked(false);
            break;
        }
        case 14: {
            on_CC_Discrete_ch3_OP_pb_clicked(true);
            break;
        }
        case 15: {
            on_CC_Discrete_ch3_OP_pb_clicked(false);
            break;
        }
        case 16: {
            on_CC_Discrete_ch4_OP_pb_clicked(true);
            break;
        }
        case 17: {
            on_CC_Discrete_ch4_OP_pb_clicked(false);
            break;
        }
        case 18: {
            on_CC_Discrete_ch5_OP_pb_clicked(true);
            break;
        }
        case 19: {
            on_CC_Discrete_ch5_OP_pb_clicked(false);
            break;
        }
        case 20: {
            on_CC_Discrete_ch1_IP_pb_clicked(true);
            break;
        }
        case 21: {
            on_CC_Discrete_ch1_IP_pb_clicked(false);
            break;
        }
        case 22: {
            on_CC_Discrete_ch2_IP_pb_clicked(true);
            break;
        }
        case 23: {
            on_CC_Discrete_ch2_IP_pb_clicked(false);
            break;
        }
        case 24: {
            on_CC_Discrete_ch3_IP_pb_clicked(true);
            break;
        }
        case 25: {
            on_CC_Discrete_ch3_IP_pb_clicked(false);
            break;
        }
        case 26: {
            on_CC_AbortSwitch_Pb_clicked(true);
            QThread::msleep(500);
            break;
        }
        case 27: {
            on_CC_AbortSwitch_Pb_clicked(false);
            break;
        }
        case 28: {
            on_CC_InitSwitch_pb_clicked(true);
            break;
        }
        case 29: {
            on_CC_InitSwitch_pb_clicked(false);
            break;
        }
        case 30: {
            on_CC_PropSwitch_Pb_clicked(true);
            break;
        }
        case 31: {
            on_CC_PropSwitch_Pb_clicked(false);
            break;
        }
        case 32: {
            on_SRU_ExternalFlash_pb_clicked();
            break;
        }
        case 33: {
            on_SRU_CntrlCard_Report_clicked();
            break;
        }

        default: {
            break;
        }
        }
    }
}

void MainWindow::SRU_CTRL_AutoStepCompleted()
{
    if (ui->DCDC_CTRL_Auto_RB->isChecked()) {
        //        qDebug() << "[STEP COMPLETE] Proceeding to next step.";
        //    g_step_in_progress = false;
        g_SRU_CTRL_sequence_counter++;
        CTRL_AutoModeConfig();
    } else {
        //do nothing
    }
}

void MainWindow::on_checkBox_front_panel_lru_checks_clicked(bool checked)
{
    if (checked) {
        ui->grpbox_LRU->setHidden(false);
        ui->LRU_FPS_txt_gb->setHidden(false);
        ui->FRONTPANEL_PT->setHidden(true);

        ui->rd_btn_RotarySwitch_1_2_3->setHidden(false);
        ui->rd_btn_Prep_Switch->setHidden(false);
        ui->rd_btn_Ready_Init_Switch->setHidden(false);
        ui->rd_btn_Abort_Switch->setHidden(false);
        ui->pb_yes_RotarySwitch_1_2_3->setHidden(false);
        ui->pb_no_RotarySwitch_1_2_3->setHidden(false);
        ui->pb_yes_Prep_Switch->setHidden(false);
        ui->pb_no_Prep_Switch->setHidden(false);
        ui->pb_yes_Ready_Init_Switch->setHidden(false);
        ui->pb_no_Ready_Init_Switch->setHidden(false);
        ui->pb_yes_Abort_Switch->setHidden(false);
        ui->pb_no_Abort_Switch->setHidden(false);
        ui->label_lru_checks->setHidden(false);
        ui->FTU_LRUReport_pb->setHidden(false);
        ui->FTU_BitTest_Report->setHidden(true);
        ui->LRU_VoltageCB->setHidden(false);
        ui->LRU_VoltageCB->setCurrentIndex(0);

        ui->Rotary_Update_Switch_status_le->clear();
        ui->Prep_Switch_status_le->clear();
        ui->Ready_Init_Switch_status_le->clear();
        ui->Abort_Switch_status_le->clear();
        ui->Rotary_Update_Switch_status_le->setStyleSheet("");
        ui->Prep_Switch_status_le->setStyleSheet("");
        ui->Ready_Init_Switch_status_le->setStyleSheet("");
        ui->Abort_Switch_status_le->setStyleSheet("");
        // ui->Rotary_Update_Switch_status_le->setHidden(true);
        //  ui->Prep_Switch_status_le->setHidden(true);
        //  ui->Ready_Init_Switch_status_le->setHidden(true);
        // ui->Abort_Switch_status_le->setHidden(true);
    } else {
        ui->grpbox_LRU->setHidden(true);
        ui->FRONTPANEL_PT->setHidden(false);
        ui->LRU_FPS_txt_gb->setHidden(true);
        ui->rd_btn_RotarySwitch_1_2_3->setHidden(true);
        ui->rd_btn_Prep_Switch->setHidden(true);
        ui->rd_btn_Ready_Init_Switch->setHidden(true);
        ui->rd_btn_Abort_Switch->setHidden(true);
        ui->pb_yes_RotarySwitch_1_2_3->setHidden(true);
        ui->pb_no_RotarySwitch_1_2_3->setHidden(true);
        ui->pb_yes_Prep_Switch->setHidden(true);
        ui->pb_no_Prep_Switch->setHidden(true);
        ui->pb_yes_Ready_Init_Switch->setHidden(true);
        ui->pb_no_Ready_Init_Switch->setHidden(true);
        ui->pb_yes_Abort_Switch->setHidden(true);
        ui->pb_no_Abort_Switch->setHidden(true);
        ui->label_lru_checks->setHidden(true);
        ui->LRU_VoltageCB->setHidden(true);
        ui->FTU_LRUReport_pb->setHidden(true);
        ui->FTU_BitTest_Report->setHidden(false);
        ui->LRU_VoltageCB->setCurrentIndex(2);

        // ui->Rotary_Update_Switch_status_le->setHidden(false);
        // ui->Prep_Switch_status_le->setHidden(false);
        // ui->Ready_Init_Switch_status_le->setHidden(false);
        // ui->Abort_Switch_status_le->setHidden(false);
    }
}
void MainWindow::on_Bit_USB_port_clicked(bool checked)
{
    on_OpenPort_toggled(checked);

    //    if (ui->Bit_USB_port->isChecked()) {
    //        g_Sty_in_Boot.startByte = 0x24;
    //        g_Sty_in_Boot.MsgID = BIT_TEST_USB_PORT_P1;
    //        g_Sty_in_Boot.packetSize = sizeof(Sty_in_Boot);
    //        g_Sty_in_Boot.CRC_WORD = 0;
    //        g_Sty_in_Boot.endByte = 0x233B;

    //        g_CRC_word = CRCUtility::g_CRC_calc((uint8_t *) &g_Sty_in_Boot, g_Sty_in_Boot.packetSize);
    //        g_Sty_in_Boot.CRC_WORD = g_CRC_word;
    //        //    if(SerialWork->get_serialPort_openSTS())
    //        {
    //            emit serialWrite((char *) &g_Sty_in_Boot, g_Sty_in_Boot.packetSize);
    //        }
    //    }
}

void MainWindow::on_rd_btn_RotarySwitch_1_2_3_clicked(bool checked)
{
    if (checked) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Rotary Switch 123");
        msgBox.setText("To test the rotary switches, rotate the dials on the LRU. Verify that the "
                       "value displayed on the LRU's display module matches the value shown in the "
                       "GUI's line edit. If the rotation sequence is accurately reflected on both "
                       "displays, press \"Yes.\" If a discrepancy is observed, press \"No.\"");
        msgBox.setInformativeText("Press OK to confirm.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

    } else {
    }
}

void MainWindow::on_rd_btn_Prep_Switch_clicked(bool checked)
{
    if (checked) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Prep Switch");
        msgBox.setText("To test the prep switch, press the button on the LRU. If the button is "
                       "pressed \"1\" is displayed else \"0\" is displayed on the "
                       "GUI's line edit. If the value is accurately reflected same as our action,"
                       "press \"Yes.\" If a discrepancy is observed, press \"No.\"");
        msgBox.setInformativeText("Press OK to confirm.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

    } else {
    }
}

void MainWindow::on_rd_btn_Ready_Init_Switch_clicked(bool checked)
{
    if (checked) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ready_Init_Switch");
        msgBox.setText(
            "To test the Ready_Init_Switch, press the button on the LRU. If the button is "
            "pressed \"1\" is displayed else \"0\" is displayed on the "
            "GUI's line edit. If the value is accurately reflected same as our action,"
            "press \"Yes.\" If a discrepancy is observed, press \"No.\"");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

    } else {
    }
}

void MainWindow::on_rd_btn_Abort_Switch_clicked(bool checked)
{
    if (checked) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Abort_Switch");
        msgBox.setText("To test the Abort_Switch, press the button on the LRU. If the button is "
                       "pressed \"1\" is displayed else \"0\" is displayed on the "
                       "GUI's line edit. If the value is accurately reflected same as our action,"
                       "press \"Yes.\" If a discrepancy is observed, press \"No.\"");
        msgBox.setInformativeText("Press OK to confirm.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

    } else {
    }
}

void MainWindow::on_pb_yes_RotarySwitch_1_2_3_clicked()
{
    if (ui->rd_btn_RotarySwitch_1_2_3->isChecked()) {
        ui->Rotary_Update_Switch_status_le->setText("PASS");
        ui->Rotary_Update_Switch_status_le->setStyleSheet("color : green");
    }
}

void MainWindow::on_pb_no_RotarySwitch_1_2_3_clicked()
{
    if (ui->rd_btn_RotarySwitch_1_2_3->isChecked()) {
        ui->Rotary_Update_Switch_status_le->setText("FAIL");
        ui->Rotary_Update_Switch_status_le->setStyleSheet("color : red");
    }
}

void MainWindow::on_pb_yes_Prep_Switch_clicked()
{
    if (ui->rd_btn_Prep_Switch->isChecked()) {
        ui->Prep_Switch_status_le->setText("PASS");
        ui->Prep_Switch_status_le->setStyleSheet("color : green");
    }
}

void MainWindow::on_pb_no_Prep_Switch_clicked()
{
    if (ui->rd_btn_Prep_Switch->isChecked()) {
        ui->Prep_Switch_status_le->setText("FAIL");
        ui->Prep_Switch_status_le->setStyleSheet("color : red");
    }
}

void MainWindow::on_pb_yes_Ready_Init_Switch_clicked()
{
    if (ui->rd_btn_Ready_Init_Switch->isChecked()) {
        ui->Ready_Init_Switch_status_le->setText("PASS");
        ui->Ready_Init_Switch_status_le->setStyleSheet("color : green");
    }
}

void MainWindow::on_pb_no_Ready_Init_Switch_clicked()
{
    if (ui->rd_btn_Ready_Init_Switch->isChecked()) {
        ui->Ready_Init_Switch_status_le->setText("FAIL");
        ui->Ready_Init_Switch_status_le->setStyleSheet("color : red");
    }
}

void MainWindow::on_pb_yes_Abort_Switch_clicked()
{
    if (ui->rd_btn_Abort_Switch->isChecked()) {
        ui->Abort_Switch_status_le->setText("PASS");
        ui->Abort_Switch_status_le->setStyleSheet("color : green");
    }
}

void MainWindow::on_pb_no_Abort_Switch_clicked()
{
    if (ui->rd_btn_Abort_Switch->isChecked()) {
        ui->Abort_Switch_status_le->setText("FAIL");
        ui->Abort_Switch_status_le->setStyleSheet("color : red");
    }
}
