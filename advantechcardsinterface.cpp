#include "advantechcardsinterface.h"
#include "bittest_logger.h"
#include "qthread.h"
#include "sru_logger.h"
#include <string.h>
#include <QDebug>
#define DELAY 100
#include "bdaqctrl.h"
#include <cmath>
#include <QCoreApplication>
#include <QSet>
#include <QThread>
#define TOLERANCE 0.4
using namespace Automation::BDaq;

Output_5856 Output_5856_Card_1;
Output_5856 Output_5856_Card_2;
Output_5856 Output_5856_Card_3;
Output_5856 Output_5856_Card_4;
Input_5856 Input_5856_Card_1;
Input_5856 Input_5856_Card_2;
Input_5856 Input_5856_Card_3;
Input_5856 Input_5856_Card_4;
Output_4716 Output_4716_Card_1;
Input_4716 Input_4716_Card_1;
SelfTestStatus g_SelfTestStatus;
Direct_Monitor g_Direct_Monitor;
CurrentSensorData g_CurrentSensorData;
ADC_BitTest g_ADC_BitTest;
ADC_SelfTest g_ADC_SelfTest;

extern double card1op_ch1, card1op_ch2;
extern double card2op_ch1, card2op_ch2;
extern double ip_ch1, ip_ch2, ip_ch3, ip_ch4, ip_ch5, ip_ch6, ip_ch7, ip_ch8, ip_ch9;
extern int card1_5856, card2_5856;

uint32_t outputs = 0;
uint32_t Inputs = 0;

//QTimer *checkTimer1_5856 =new QTimer;

AdvantechCardsInterface::~AdvantechCardsInterface()
{
    dispose();
}

AdvantechCardsInterface::AdvantechCardsInterface()
    : doCtrl(nullptr)
    , diCtrl(nullptr)
{
    //AdvantechCardsInterface::AdvantechCardsInterface()
    //    : instantDoCtrl2(nullptr), instantDiCtrl2(nullptr)
    //{
    //AdvantechCardsInterface::AdvantechCardsInterface(QObject *parent)
    //    : QObject(parent)
    //{
    //connect(advantechInterface, &AdvantechCardsInterface::card2FailureDetected,this, &YourUIClass::handleCard2Failure);
    // void YourUIClass::handleCard2Failure() {

    //    QMessageBox::warning(this, "Card 2 Failure", "A failure occurred during the card 2 self-test.");
    //}

    // Connect signal to Logger singleton
    connect(this, &AdvantechCardsInterface::newSelfTestlog, Logger::instance(), &Logger::logText);

    g_ADC_SelfTest.averagedAi_test1.resize(8);
    g_ADC_SelfTest.averagedAi_test2.resize(8);
    g_ADC_SelfTest.averagedAi_test3.resize(8);
    g_ADC_SelfTest.averagedAi_test4.resize(8);
    g_ADC_SelfTest.averagedAi_test5.resize(8);
    g_ADC_SelfTest.averagedAi_test6.resize(8);
    g_ADC_SelfTest.averagedAi_test7.resize(8);
    g_ADC_SelfTest.averagedAi_test8.resize(8);
    g_ADC_SelfTest.averagedAi_test9.resize(8);

    //    // Still during start-up
    //    Advantech_thread = new QThread(this);
    //    g_AdvantechCardsInterface = new AdvantechCardsInterface;

    //    g_AdvantechCardsInterface->moveToThread(Advantech_thread);
    //    connect(Advantech_thread, &QThread::finished, g_AdvantechCardsInterface, &QObject::deleteLater);

    //    Advantech_thread->start();

    //    qRegisterMetaType<QVector<TestPoint_main>>("QVector<TestPoint_main>");
    qRegisterMetaType<uint16_t>("int32_t");
}

void AdvantechCardsInterface::start()
{
    Logger::instance()->logText(
        "-------------------------ATE SELF TEST LOGGING STARTED.------------------------");
    // qDebug() << "hello";
}
void AdvantechCardsInterface::stop()
{
    //    qDebug() << "serial port stop pressed;";
    //    serialPort->close();
    emit finished(); // Notify that the worker is finished
}

void AdvantechCardsInterface::stopThread()
{
    running = false;
}

CardInitResult AdvantechCardsInterface::initializeCard_4716(const QString &bid,
                                                            InstantAiCtrl *&aiCtrl,
                                                            InstantDiCtrl *&diCtrl,
                                                            InstantAoCtrl *&aoCtrl,
                                                            InstantDoCtrl *&doCtrl)
{
    aiCtrl = InstantAiCtrl::Create();
    diCtrl = InstantDiCtrl::Create();
    aoCtrl = InstantAoCtrl::Create();
    doCtrl = InstantDoCtrl::Create();

    if (!aiCtrl || !diCtrl || !aoCtrl || !doCtrl) {
        return {bid, false, "Failed to create controller objects."};
    }

    Array<DeviceTreeNode> *supportedDevices = aiCtrl->getSupportedDevices();
    bool found = false;
    DeviceTreeNode target;

    for (int i = 0; i < supportedDevices->getCount(); ++i) {
        const DeviceTreeNode &node = supportedDevices->getItem(i);
        if (QString::fromWCharArray(node.Description) == bid) {
            target = node;
            found = true;
            break;
        }
    }

    supportedDevices->Dispose();

    if (!found) {
        return {bid, false, "Device not found."};
    }

    DeviceInformation info(target.DeviceNumber);

    if (aiCtrl->setSelectedDevice(info) != Success || !aiCtrl->getInitialized())
        return {bid, false, "AI controller failed to initialize."};
    if (diCtrl->setSelectedDevice(info) != Success || !diCtrl->getInitialized())
        return {bid, false, "DI controller failed to initialize."};
    if (aoCtrl->setSelectedDevice(info) != Success || !aoCtrl->getInitialized())
        return {bid, false, "AO controller failed to initialize."};
    if (doCtrl->setSelectedDevice(info) != Success || !doCtrl->getInitialized())
        return {bid, false, "DO controller failed to initialize."};
    //    qDebug() << QString("✅ %1 initialized").arg(bid);
    return {bid, true, "Initialized successfully."};
}

void AdvantechCardsInterface::InitializeDevice_4716()
{
    CardInitResult card1 = initializeCard_4716("USB-4716,BID#0",
                                               instantAiCtrl1,
                                               instantDiCtrl1_ADC,
                                               instantAoCtrl1,
                                               instantDoCtrl1_ADC);
    CardInitResult card2 = initializeCard_4716("USB-4716,BID#1",
                                               instantAiCtrl2,
                                               instantDiCtrl2_ADC,
                                               instantAoCtrl2,
                                               instantDoCtrl2_ADC);

    //    qDebug() << (card1.success ? "SUCCESS" : "FAIL") << card1.devicename << ":"
    //             << card1.errorMessage;
    //    qDebug() << (card2.success ? "SUCCESS" : "FAIL") << card2.devicename << ":"
    //             << card2.errorMessage;

    QString Dev_info_4716;

    card1.success ? Dev_info_4716.append("✅") : Dev_info_4716.append("❌");
    Dev_info_4716.append(card1.devicename);
    Dev_info_4716.append(card1.errorMessage);
    Dev_info_4716.append("\n");

    card2.success ? Dev_info_4716.append("✅") : Dev_info_4716.append("❌");
    Dev_info_4716.append(card2.devicename);
    Dev_info_4716.append(card2.errorMessage);
    Dev_info_4716.append("\n");

    if (card1.success && card2.success) {
        emit newSelfTestlog("\nBoth USB-4716 cards initialized successfully.\n");
        emit USB_4716_cards_status_signal(Dev_info_4716);
    } else {
        emit newSelfTestlog("\nOne or both USB-4716 cards failed to initialize.\n");
        emit USB_4716_cards_status_signal(Dev_info_4716);
    }
}

void AdvantechCardsInterface::InitializeDevice_5856()
{
    CardInitResult card1 = initializeCard_5856("USB-5856,BID#0", instantDiCtrl1, instantDoCtrl1);
    CardInitResult card2 = initializeCard_5856("USB-5856,BID#1", instantDiCtrl2, instantDoCtrl2);
    CardInitResult card3 = initializeCard_5856("USB-5856,BID#2", instantDiCtrl3, instantDoCtrl3);
    CardInitResult card4 = initializeCard_5856("USB-5856,BID#3", instantDiCtrl4, instantDoCtrl4);

    QString Dev_info;

    for (const CardInitResult &card : {card1, card2, card3, card4}) {
        //        qDebug() << (card.success ? "SUCCESS" : "FAIL") << card.devicename << ":"
        //                 << card.errorMessage;

        card.success ? Dev_info.append("✅") : Dev_info.append("❌");
        Dev_info.append(card.devicename);
        Dev_info.append(card.errorMessage);
        Dev_info.append("\n");
    }

    if (card1.success && card2.success && card3.success && card4.success) {
        emit newSelfTestlog("\nAll USB-5856 cards initialized successfully.\n");
        emit USB_5856_cards_status_signal(card1.success,
                                          card2.success,
                                          card3.success,
                                          card4.success,
                                          Dev_info);

    } else {
        emit newSelfTestlog("\nOne or more USB-5856 cards failed to initialize.\n");
        emit USB_5856_cards_status_signal(card1.success,
                                          card2.success,
                                          card3.success,
                                          card4.success,
                                          Dev_info);
    }
}
CardInitResult AdvantechCardsInterface::initializeCard_5856(const QString &bid,
                                                            InstantDiCtrl *&diCtrl,
                                                            InstantDoCtrl *&doCtrl)
{
    dispose();

    QThread::msleep(500);

    diCtrl = InstantDiCtrl::Create();
    doCtrl = InstantDoCtrl::Create();
    // currentDevice = deviceName;

    if (!diCtrl || !doCtrl) {
        return {bid, false, "Failed to create controller objects."};
    }

    Array<DeviceTreeNode> *supportedDevices = diCtrl->getSupportedDevices();
    bool found = false;
    DeviceTreeNode target;

    for (int i = 0; i < supportedDevices->getCount(); ++i) {
        const DeviceTreeNode &node = supportedDevices->getItem(i);
        if (QString::fromWCharArray(node.Description) == bid) {
            target = node;
            found = true;
            break;
        }
    }
    supportedDevices->Dispose();

    if (!found) {
        return {bid, false, "Device not found."};
    }

    DeviceInformation info(target.DeviceNumber);

    if (diCtrl->setSelectedDevice(info) != Success || !diCtrl->getInitialized())
        return {bid, false, "DI controller failed to initialize."};
    if (doCtrl->setSelectedDevice(info) != Success || !doCtrl->getInitialized())
        return {bid, false, "DO controller failed to initialize."};
    Logger::instance()->logText(QString("✅ %1 initialized").arg(bid));
    return {bid, true, "Initialized successfully."};
}
void AdvantechCardsInterface::onTriggerCard1AOButtonClicked()
{
    ValueRange desiredRange = V_Neg5To5; // ±5V range (check if your card supports this)

    for (int ch = 0; ch < 2; ++ch) {
        instantAoCtrl1->getChannels()->getItem(ch).setValueRange(desiredRange);
    }

    instantAoCtrl1->Write(0, (double) card1op_ch1);
    instantAoCtrl1->Write(1, card1op_ch2);

    //    qDebug() << "AO written -> CH0:" << card1op_ch1 << "V, CH1:" << card1op_ch2 << "V";
    Logger::instance()->logText(
        QString(" AO Write Complete - CH0: %1 V, CH1: %2 V").arg(card1op_ch1).arg(card1op_ch2));
}

void AdvantechCardsInterface::onTriggerCard2AOButtonClicked()
{
    //    ValueRange desiredRange = V_Neg5To5; // ±5V range (check if your card supports this)

    //    qDebug() << "it is fun 1...............";
    //    for (int ch = 0; ch < 2; ++ch) {
    //        qDebug() << "in 1111...............";

    //        instantAoCtrl2->getChannels()->getItem(ch).setValueRange(desiredRange);
    //        qDebug() << "end 1111...............";
    //    }

    //    qDebug() << "it is fun 2...............";

    //    instantAoCtrl2->Write(0, card2op_ch1);
    //    qDebug() << "it is fun 3...............";

    //    instantAoCtrl2->Write(1, card2op_ch2);

    //    qDebug() << "AO written -> CH0:" << card2op_ch1 << "V, CH1:" << card2op_ch2 << "V";

    ValueRange desiredRange = V_Neg5To5;

    //    qDebug() << "it is fun 1...............";

    if (!instantAoCtrl2) {
        //        qDebug() << "[ERROR] instantAoCtrl2 is NULL!";
        Logger::instance()->logText("[ERROR] instantAoCtrl2 is NULL!");

        return;
    }

    auto channels = instantAoCtrl2->getChannels();
    if (!channels) {
        //        qDebug() << "[ERROR] Channels list is NULL!";
        Logger::instance()->logText("[ERROR] Channels list is NULL!");

        return;
    }

    for (int ch = 0; ch < 2; ++ch) {
        //        qDebug() << "in channel loop: ch =" << ch;

        if (ch >= channels->getCount()) {
            //            qDebug() << "[WARN] Channel index" << ch << "out of range!";
            Logger::instance()->logText(
                QString("[WARN] Channel index %1 is out of range. Skipping.").arg(ch));

            continue;
        }

        ErrorCode err = channels->getItem(ch).setValueRange(desiredRange);
        if (err != Success) {
            //            qDebug() << "[ERROR] Failed to set range for channel" << ch << "ErrorCode:" << err;
            Logger::instance()->logText(
                QString("[ERROR] Failed to set value range for channel %1. Error code: %2")
                    .arg(ch)
                    .arg(desiredRange));
        } else {
            //            qDebug() << "Range set successfully for channel" << ch;
            Logger::instance()->logText(
                QString("[INFO] Value range set successfully for channel %1.").arg(ch));
        }
    }

    //    qDebug() << "it is fun 2...............";

    ErrorCode err0 = instantAoCtrl2->Write(0, card2op_ch1);
    ErrorCode err1 = instantAoCtrl2->Write(1, card2op_ch2);

    //    qDebug() << "it is fun 3...............";

    //    qDebug() << "AO written -> CH0:" << card2op_ch1 << "V, CH1:" << card2op_ch2 << "V";
    //    qDebug() << "Write errors: CH0 =" << err0 << ", CH1 =" << err1;

    Logger::instance()->logText(
        QString("[INFO] AO Write Complete - CH0: %1 V, CH1: %2 V").arg(card2op_ch1).arg(card2op_ch2));
    Logger::instance()->logText(
        QString("[INFO] Write Status - CH0: %1, CH1: %2").arg(err0).arg(err1));

    Logger::instance()->logText("[INFO] TriggerCard2 AO operation completed.\n");
}

void AdvantechCardsInterface::onTriggerCard1AO_refresh()
{
    card1op_ch1 = 0.0, card1op_ch2 = 0.0;
    instantAoCtrl1->Write(0, card1op_ch1);
    instantAoCtrl1->Write(1, card1op_ch2);
    //    qDebug() << "Card1AO written -> CH0:" << card1op_ch1 << "V, CH1:" << card1op_ch2 << "V";
    Logger::instance()->logText(
        QString("Card1AO written - CH0: %1 V, CH1: %2 V").arg(card1op_ch1).arg(card1op_ch2));
}

void AdvantechCardsInterface::onTriggerCard2AO_refresh()
{
    card2op_ch1 = 0.0, card2op_ch2 = 0.0;
    instantAoCtrl2->Write(0, card2op_ch1);
    instantAoCtrl2->Write(1, card2op_ch2);
    //    qDebug() << "Card2AO written -> CH0:" << card2op_ch1 << "V, CH1:" << card2op_ch2 << "V";
    Logger::instance()->logText(
        QString("[INFO] Card2AO written -> CH0: %1 V, CH1: %2 V").arg(card2op_ch1).arg(card2op_ch2));
}

void AdvantechCardsInterface::onTriggerCard1AI_refresh()
{
    ip_ch1 = 0.0, ip_ch2 = 0.0, ip_ch3 = 0.0, ip_ch4 = 0.0, ip_ch5 = 0.0, ip_ch6 = 0.0,
    ip_ch7 = 0.0, ip_ch8 = 0.0;
    instantAoCtrl1->Write(0, ip_ch1);
    instantAoCtrl1->Write(1, ip_ch2);
    instantAoCtrl1->Write(2, ip_ch3);
    instantAoCtrl1->Write(3, ip_ch4);
    instantAoCtrl1->Write(4, ip_ch5);
    instantAoCtrl1->Write(5, ip_ch6);
    instantAoCtrl1->Write(6, ip_ch7);
    instantAoCtrl1->Write(7, ip_ch8);
    //    qDebug() << "AO written -> CH0:" << card1op_ch1 << "V, CH1:" << card1op_ch2 << "V";
    Logger::instance()->logText(
        QString("[INFO] AO written -> CH0: %1 V, CH1: %2 V").arg(card1op_ch1).arg(card1op_ch2));
}

void AdvantechCardsInterface::onTriggerCard2AI_refresh()
{
    ip_ch1 = 0.0, ip_ch2 = 0.0, ip_ch3 = 0.0, ip_ch4 = 0.0, ip_ch5 = 0.0, ip_ch6 = 0.0,
    ip_ch7 = 0.0, ip_ch8 = 0.0;
    instantAoCtrl2->Write(0, ip_ch1);
    instantAoCtrl2->Write(1, ip_ch2);
    instantAoCtrl2->Write(2, ip_ch3);
    instantAoCtrl2->Write(3, ip_ch4);
    instantAoCtrl2->Write(4, ip_ch5);
    instantAoCtrl2->Write(5, ip_ch6);
    instantAoCtrl2->Write(6, ip_ch7);
    instantAoCtrl2->Write(7, ip_ch8);
    //    qDebug() << "Card2AO written -> CH0:" << card2op_ch1 << "V, CH1:" << card2op_ch2 << "V";
    Logger::instance()->logText(
        QString("[INFO]Card2AO written -> CH0: %1 V, CH1: %2 V").arg(card2op_ch1).arg(card2op_ch2));
}

void AdvantechCardsInterface::onTriggerCard1AIButtonClicked()
{
    ValueRange desiredRange = V_Neg2pt5To2pt5;

    // Configure AO channel range
    for (int ch = 0; ch < 8; ++ch) {
        instantAiCtrl2->getChannels()->getItem(ch).setValueRange(desiredRange);
    }
    instantAiCtrl2->Read(1, 9, &g_ADC_BitTest.CH_data[0]);
    // ADC_CARD2_CH1_to_CH8();

    g_ADC_BitTest.time += 0.001;
}

void AdvantechCardsInterface::ADC_CARD2_CH1_to_CH8()

{
    //    const int aiStartChannel = 0; // AI CH1 (channel 0-based index)
    //    const int aiChannelCount = 8;
    //    const int avgSamples = 10; // Number of samples for moving average

    //    double voltages[] = {-2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0};
    //    double lowers[] = {-2.1, -1.7, -1.2, -0.65, -0.15, 0.39, 0.88, 1.42, 1.87};
    //    double uppers[] = {-1.8, -1.4, -0.95, -0.45, 0.05, 0.55, 1.85, 1.55, 2.05};
    //    QVector<double> avgAi;
    //    //  qDebug() << "Averaged AI Readings:";
    //    double sumData[aiChannelCount] = {0};
    //    // ✅ Read and average AI data
    //    for (int sample = 0; sample < avgSamples; ++sample) {
    //        double aiData[aiChannelCount] = {0};

    //        //        if (instantAiCtrl2->Read(aiStartChannel, aiChannelCount, aiData) == Success) {
    //        for (int ch = 0; ch < aiChannelCount; ++ch) {
    //            sumData[ch] += g_ADC_BitTest.CH_data[ch];
    //        }
    //        //        } else {
    //        //            qDebug() << "AI read failed at sample #" << sample + 1;
    //        //        }

    //        //        QThread::msleep(50);
    //    }

    //    qDebug() << "Averaged AI Readings:";

    //    for (int ch = 0; ch < aiChannelCount; ++ch) {
    //        double avg = sumData[ch] / avgSamples;
    //        avgAi.append(avg); // ✅ Append to correct QVector
    //        QVector<QString> logParts;
    //        QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
    //        qDebug().noquote() << line;
    //        logParts.append(line);
    //    }

    //    QString logLine = logParts.join(", ");
    //    Logger::instance()->logText(logLine);

    //    static int ch = 0;
    //    for (; ch < 9;) {
    //        switch (ch)

    //        {
    //        case 0: {
    //            g_ADC_Card2_BitTest.avg_ch1 = avgAi;
    //            //    qDebug() << "in case 1" << g_ADC_Card2_BitTest.avg_ch1;
    //            //2v_
    //            for (int i = 0; i < 8; i++) {
    //                float lowerBound = lowers[i];
    //                float upperBound = uppers[i];
    //                g_ADC_Card2_BitTest.ch1Status[i] = (g_ADC_Card2_BitTest.avg_ch1[i] >= lowerBound
    //                                                    && g_ADC_Card2_BitTest.avg_ch1[i] <= upperBound)
    //                                                       ? 1
    //                                                       : 0;
    //            }
    //            ch++;
    //            break;
    //        }
    //        default:
    //            ch++;
    //            break;
    //        }
    //    }
    //    qDebug() << "CH1 All 8 averaged voltages:";
    //    for (int i = 0; i < aiChannelCount; ++i) {
    //        qDebug() << QString("  CH%1: %2 V  [Expected: %3 V]")
    //                        .arg(i + 1)
    //                        .arg(g_ADC_Card2_BitTest.avg_ch1[i], 0, 'f', 4)
    //                        .arg(voltages[i], 0, 'f', 2);
    //    }
}

void AdvantechCardsInterface::PS1_28V_Source_from_Power_Card()
{
    instantAiCtrl1->Read(8, g_Direct_Monitor.Input_Ch8);
    g_Direct_Monitor.Input_Ch8 *= 7;
}

void AdvantechCardsInterface::PS2_12V_Source_from_Power_Card()
{
    instantAiCtrl1->Read(9, g_Direct_Monitor.Input_Ch9);
    g_Direct_Monitor.Input_Ch9 *= 7;
}

void AdvantechCardsInterface::PS3_5V_Source_from_Power_Card()
{
    //    instantAiCtrl1->Read(10, g_Direct_Monitor.Input_Ch10);
    //    g_Direct_Monitor.Input_Ch10 *= 7;
    instantAiCtrl1->Read(9, g_Direct_Monitor.Input_Ch9);
}

void AdvantechCardsInterface::PS7_16V_28V_32V_Source_from_Power_Card(int index)
{
    switch (index) {
    case 1: // 16V
    {
        //if (checked)
        {
            //            qDebug() << "Case 16";
            instantAiCtrl1->Read(6, g_Direct_Monitor.Input_Ch6_16);
            g_Direct_Monitor.Input_Ch6_16 *= 7;
            //            qDebug() << g_Direct_Monitor.Input_Ch6_16;
        } // else
        {
            //  qDebug() << "Case 16";
            //  g_Direct_Monitor.Input_Ch6_16 = 0;
        }
        break;
    }
    case 2: // 28V
    {
        //        qDebug() << "Case 28";
        instantAiCtrl1->Read(6, g_Direct_Monitor.Input_Ch6_28);
        g_Direct_Monitor.Input_Ch6_28 *= 7;
        break;
    }
    case 3: // 32V
    {
        //        qDebug() << "Case 32";
        instantAiCtrl1->Read(6, g_Direct_Monitor.Input_Ch6_32);
        g_Direct_Monitor.Input_Ch6_32 *= 7;
        break;
    }
    case 4: //EXTERNAL V
    {
        //        qDebug() << "Case EXT";
        instantAiCtrl1->Read(6, g_Direct_Monitor.Input_ch6_Ext);
        g_Direct_Monitor.Input_ch6_Ext *= 7;
        break;
    }
    default:
        //        qDebug() << "default case ";
        return;
    }
}

void AdvantechCardsInterface::LED_5856_ON_PS1_28V(bool value)
{
    Logger::instance()->logText(
        QString("[INFO] LED_5856_ON_PS1_28V called with value: %1").arg(value));

    Automation::BDaq::uint8 portdata = 0;
    if (value == true) {
        Output_5856_Card_1.Output_CH0 = 0;
        Logger::instance()->logText(
            QString("[INFO] Setting DO CH0 to: %1").arg(Output_5856_Card_1.Output_CH0));
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH0 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl1->ReadBit(0, 0, &portdata);
        Input_5856_Card_1.Input_CH0 = portdata;
        //        qDebug() << "DO CH0:" << Output_5856_Card_1.Output_CH0
        //                 << ", DI CH0:" << static_cast<int>(Input_5856_Card_1.Input_CH0);
        Logger::instance()->logText(QString("[INFO] Final DO CH0: %1, DI CH0: %2")
                                        .arg(Output_5856_Card_1.Output_CH0)
                                        .arg(static_cast<int>(Input_5856_Card_1.Input_CH0)));

    } else {
        Output_5856_Card_1.Output_CH0 = 1;
        Logger::instance()->logText(
            QString("[INFO] Setting DO CH0 to: %1").arg(Output_5856_Card_1.Output_CH0));
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH0 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl1->ReadBit(0, 0, &portdata);
        Input_5856_Card_1.Input_CH0 = portdata;
        //        qDebug() << "DO CH0:" << Output_5856_Card_1.Output_CH0
        //                 << ", DI CH0:" << static_cast<int>(Input_5856_Card_1.Input_CH0);
        Logger::instance()->logText(QString("[INFO] Final DO CH0: %1, DI CH0: %2")
                                        .arg(Output_5856_Card_1.Output_CH0)
                                        .arg(static_cast<int>(Input_5856_Card_1.Input_CH0)));
    }
}

void AdvantechCardsInterface::LOAD_MEASURMENT_PS1_28V(bool value)
{
    //    qDebug() << "LOAD_MEASUREMENT_PS1_28V";
    Logger::instance()->logText(QString("[INFO] LOAD_MEASUREMENT_PS1_28V: %1").arg(value));

    Automation::BDaq::uint8 portdata = 0;
    if (value == true) {
        Output_5856_Card_1.Output_CH0 = 1;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH0 << 0));
        QThread::msleep(DELAY);

        // Read current DI CH0 state
        instantDiCtrl1->ReadBit(0, 0, &portdata);
        Input_5856_Card_1.Input_CH0 = portdata;
        //        qDebug() << "DO CH0:" << Output_5856_Card_1.Output_CH0
        //                 << ", DI CH0:" << static_cast<int>(Input_5856_Card_1.Input_CH0);
        Logger::instance()->logText(QString(" Final DO CH0: %1, DI CH0: %2")
                                        .arg(Output_5856_Card_1.Output_CH0)
                                        .arg(static_cast<int>(Input_5856_Card_1.Input_CH0)));
    } else {
        // If DI is 0, set DO OFF (0)
        Output_5856_Card_1.Output_CH0 = 0;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH0 << 0));

        QThread::msleep(DELAY);
        // Re-read DI CH0 after setting DO
        instantDiCtrl1->ReadBit(0, 0, &portdata);
        Input_5856_Card_1.Input_CH0 = portdata;
        //        qDebug() << "DO CH0:" << Output_5856_Card_1.Output_CH0
        //                 << ", DI CH0:" << static_cast<int>(Input_5856_Card_1.Input_CH0);

        Logger::instance()->logText(QString(" Final DO CH0: %1, DI CH0: %2")
                                        .arg(Output_5856_Card_1.Output_CH0)
                                        .arg(static_cast<int>(Input_5856_Card_1.Input_CH0)));
    }
}

void AdvantechCardsInterface::LOAD_MEASURMENT_PS2_12V(bool value)
{
    Logger::instance()->logText(QString("[INFO] LOAD_MEASURMENT_PS2_12V: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;
    if (value == true) {
        Output_5856_Card_1.Output_CH1 = 1;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH1 << 1)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait

        Input_5856_Card_1.Input_CH1 = portData;
        instantDiCtrl1->ReadBit(0, 1, &portData);
        //        qDebug() << "DO CH1:" << Output_5856_Card_1.Output_CH1
        //                 << ", DI CH1:" << static_cast<int>(Input_5856_Card_1.Input_CH1);
        Logger::instance()->logText(QString("[INFO] Final DO CH1: %1, DI CH1: %2")
                                        .arg(Output_5856_Card_1.Output_CH1)
                                        .arg(static_cast<int>(Input_5856_Card_1.Input_CH1)));
    } else {
        Output_5856_Card_1.Output_CH1 = 0;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH1 << 1)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH1 = portData;
        instantDiCtrl1->ReadBit(0, 1, &portData);
        //        qDebug() << "DO CH1:" << Output_5856_Card_1.Output_CH1
        //                 << ", DI CH1:" << static_cast<int>(Input_5856_Card_1.Input_CH1);
        Logger::instance()->logText(QString("Final DO CH1: %1, DI CH1: %2")
                                        .arg(Output_5856_Card_1.Output_CH1)
                                        .arg(static_cast<int>(Input_5856_Card_1.Input_CH1)));
    }
}

void AdvantechCardsInterface::LED_5856_USB_HUB_PS2_12V(bool value)
{
    Logger::instance()->logText(QString("[INFO]LED_5856_USB_HUB_PS2_12V: %1").arg(value));

    /////////// LED ON ////////////////
    Automation::BDaq::uint8 portData = 0;
    if (value == true) {
        Output_5856_Card_1.Output_CH1 = 0;

        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH1 << 0));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl1->ReadBit(0, 0, &portData);
        Input_5856_Card_1.Input_CH1 = portData;

        Output_5856_Card_4.Output_CH15 = 1;
        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH15 << 7));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(1, 4, &portData);
        Input_5856_Card_4.Input_CH12 = portData;

        //        qDebug() << "DO CH1:" << Output_5856_Card_1.Output_CH1
        //                 << ", DI CH1:" << static_cast<int>(Input_5856_Card_1.Input_CH1)
        //                 << "DO CH15:" << Output_5856_Card_4.Output_CH15
        //                 << ", DI CH12:" << static_cast<int>(Input_5856_Card_4.Input_CH12);
        Logger::instance()->logText(QString("[INFO] DO CH15: %1, DI CH12: %2")
                                        .arg(Output_5856_Card_4.Output_CH15)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH12)));

        Output_5856_Card_4.Output_CH15 = 1;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH15 << 7));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(1, 4, &portData);
        Input_5856_Card_4.Input_CH12 = portData;
        //        qDebug() << "DO CH15:" << Output_5856_Card_4.Output_CH15
        //                 << ", DI CH12:" << static_cast<int>(Input_5856_Card_4.Input_CH12);
        Logger::instance()->logText(QString("[INFO] DO CH15: %1, DI CH12: %2 (after reset)")
                                        .arg(Output_5856_Card_4.Output_CH15)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH12)));

    } else {
        /////////// LED OFF ////////////////

        Output_5856_Card_4.Output_CH16 = 1;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH16 << 0));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(1, 4, &portData);
        Input_5856_Card_4.Input_CH12 = portData;

        //        qDebug() << "DO CH16:" << Output_5856_Card_4.Output_CH16
        //                 << ", DI CH12:" << static_cast<int>(Input_5856_Card_4.Input_CH12);
        Logger::instance()->logText(QString("[INFO] DO CH16: %1, DI CH12: %2")
                                        .arg(Output_5856_Card_4.Output_CH16)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH12)));

        Output_5856_Card_4.Output_CH16 = 0;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH16 << 0));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(1, 4, &portData);
        Input_5856_Card_4.Input_CH12 = portData;
        //        qDebug() << "DO CH16:" << Output_5856_Card_4.Output_CH16
        //                 << ", DI CH12:" << static_cast<int>(Input_5856_Card_4.Input_CH12);

        Logger::instance()->logText(QString("[INFO] DO CH16: %1, DI CH12: %2 (after reset)")
                                        .arg(Output_5856_Card_4.Output_CH16)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH12)));
    }
    Logger::instance()->logText("[INFO] LED_5856_USB_HUB_PS2_12V operation completed.\n");
}

void AdvantechCardsInterface::LOAD_MEASURMENT_5856_PS3_5V(bool value)
{
    Logger::instance()->logText(QString("[INFO]LOAD_MEASURMENT_5856_PS3_5V: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;
    if (value == true) {
        Output_5856_Card_1.Output_CH2 = 1;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH2 << 2));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl1->ReadBit(0, 2, &portData);
        Input_5856_Card_4.Input_CH2 = portData;
        //        qDebug() << "DO CH2:" << Output_5856_Card_1.Output_CH2
        //                 << ", DI CH2:" << static_cast<int>(Input_5856_Card_4.Input_CH2);
        Logger::instance()->logText(QString("[INFO] Final DO CH2: %1, DI CH2: %2")
                                        .arg(Output_5856_Card_1.Output_CH2)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));

    } else {
        Output_5856_Card_1.Output_CH2 = 0;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH2 << 2));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl1->ReadBit(0, 2, &portData);
        Input_5856_Card_4.Input_CH2 = portData;
        //        qDebug() << "DO CH2:" << Output_5856_Card_1.Output_CH2
        //                 << ", DI CH2:" << static_cast<int>(Input_5856_Card_4.Input_CH2);
        Logger::instance()->logText(QString("[INFO] Final DO CH2: %1, DI CH2: %2")
                                        .arg(Output_5856_Card_1.Output_CH2)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));
    }
    Logger::instance()->logText("[INFO] LOAD_MEASURMENT_5856_PS3_5V operation completed.\n");
}

void AdvantechCardsInterface::LOAD_MEASURMENT_5856_PS4(bool value)
{
    Logger::instance()->logText(QString("[INFO] LOAD_MEASURMENT_5856_PS4 value: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_4.Output_CH0 = 1;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH0 << 0));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 0, &portData);
        Input_5856_Card_4.Input_CH0 = portData;
        //        qDebug() << "DO CH0:" << Output_5856_Card_4.Output_CH0
        //                 << ", DI CH0:" << static_cast<int>(Input_5856_Card_4.Input_CH0);
        Logger::instance()->logText(QString("[INFO] Final DO CH0: %1, DI CH0: %2")
                                        .arg(Output_5856_Card_4.Output_CH0)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH0)));

    } else {
        Output_5856_Card_4.Output_CH0 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH0 << 0));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 0, &portData);
        Input_5856_Card_4.Input_CH0 = portData;
        //        qDebug() << "DO CH0:" << Output_5856_Card_4.Output_CH0
        //                 << ", DI CH0:" << static_cast<int>(Input_5856_Card_4.Input_CH0);
        Logger::instance()->logText(QString("[INFO] Final DO CH0: %1, DI CH0: %2")
                                        .arg(Output_5856_Card_4.Output_CH0)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH0)));
    }

    Logger::instance()->logText("[INFO] LOAD_MEASURMENT_5856_PS4 operation completed.\n");
}

void AdvantechCardsInterface::LED_5856_CNTRL_CARDS_PS4(bool value)
{
    Logger::instance()->logText(QString("[INFO]LED_5856_CNTRL_CARDS_PS4 value: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_4.Output_CH0 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH0 << 0));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 0, &portData);
        Input_5856_Card_4.Input_CH0 = portData;
        //        qDebug() << "DO CH0:" << Output_5856_Card_4.Output_CH0
        //                 << ", DI CH0:" << static_cast<int>(Input_5856_Card_4.Input_CH0);
        Logger::instance()->logText(QString("[INFO] DO CH0: %1, DI CH0: %2")
                                        .arg(Output_5856_Card_4.Output_CH0)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH0)));

        Output_5856_Card_4.Output_CH3 = 1;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH3 << 3));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 3, &portData);
        Input_5856_Card_4.Input_CH3 = portData;
        //        qDebug() << "DO CH3:" << Output_5856_Card_4.Output_CH3
        //                 << ", DI CH3:" << static_cast<int>(Input_5856_Card_4.Input_CH3);
        Logger::instance()->logText(QString("[INFO] DO CH3: %1, DI CH3: %2")
                                        .arg(Output_5856_Card_4.Output_CH3)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));

        SruLogger::instance()->logText(QString("[INFO] DO CH3: %1, DI CH3: %2")
                                           .arg(Output_5856_Card_4.Output_CH3)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));

        Output_5856_Card_4.Output_CH3 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH3 << 3));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 3, &portData);
        Input_5856_Card_4.Input_CH3 = portData;

        Logger::instance()->logText(QString("[INFO] DO CH3: %1, DI CH3: %2")
                                        .arg(Output_5856_Card_4.Output_CH3)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));

        SruLogger::instance()->logText(QString("[INFO] DO CH3: %1, DI CH3: %2")
                                           .arg(Output_5856_Card_4.Output_CH3)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));

    } else {
        ///////////LED OFF///////////

        Output_5856_Card_4.Output_CH4 = 1;

        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH4 << 4));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 3, &portData);
        Input_5856_Card_4.Input_CH3 = portData;
        //        qDebug() << "DO CH4:" << Output_5856_Card_4.Output_CH3
        //                 << ", DI CH3:" << static_cast<int>(Input_5856_Card_4.Input_CH3);
        Logger::instance()->logText(QString("[INFO] DO CH4: %1, DI CH3: %2")
                                        .arg(Output_5856_Card_4.Output_CH4)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));
        SruLogger::instance()->logText(QString("[INFO] DO CH4: %1, DI CH3: %2")
                                           .arg(Output_5856_Card_4.Output_CH4)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));

        Output_5856_Card_4.Output_CH4 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH4 << 4));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 3, &portData);
        Input_5856_Card_4.Input_CH3 = portData;

        //        qDebug() << "DO CH4:" << Output_5856_Card_4.Output_CH3
        //                 << ", DI CH3:" << static_cast<int>(Input_5856_Card_4.Input_CH3);
        Logger::instance()->logText(QString("[INFO] DO CH4: %1, DI CH3: %2")
                                        .arg(Output_5856_Card_4.Output_CH4)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));
        SruLogger::instance()->logText(QString("[INFO] DO CH4: %1, DI CH3: %2")
                                           .arg(Output_5856_Card_4.Output_CH4)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH3)));
    }
    Logger::instance()->logText("[INFO]LED_5856_CNTRL_CARDS_PS4  completed.\n");
}

void AdvantechCardsInterface::PS4_3_3_Voltage_Monitor()
{
    instantAiCtrl1->Read(10, g_Direct_Monitor.Input_Ch10);
}

void AdvantechCardsInterface::LOAD_MEASURMENT_5856_PS5_5V(bool value)
{
    Automation::BDaq::uint8 portData = 0;
    Logger::instance()->logText(QString("[INFO]LOAD_MEASURMENT_5856_PS5_5V value: %1").arg(value));

    if (value == true) {
        Output_5856_Card_4.Output_CH1 = 1;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH1 << 1));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 1, &portData);
        Input_5856_Card_4.Input_CH1 = portData;

        //        qDebug() << "DO CH1:" << Output_5856_Card_4.Output_CH1
        //                 << ", DI CH1:" << static_cast<int>(Input_5856_Card_4.Input_CH1);
        Logger::instance()->logText(QString(" DO CH1:%1, DI CH1: %2")
                                        .arg(Output_5856_Card_4.Output_CH1)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH1)));
    } else {
        Output_5856_Card_4.Output_CH1 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH1 << 1));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 1, &portData);
        Input_5856_Card_4.Input_CH1 = portData;

        //        qDebug() << "DO CH1:" << Output_5856_Card_4.Output_CH1
        //                 << ", DI CH1:" << static_cast<int>(Input_5856_Card_4.Input_CH1);
        Logger::instance()->logText(QString(" DO CH1:%1, DI CH1: %2")
                                        .arg(Output_5856_Card_4.Output_CH1)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH1)));
    }
}

void AdvantechCardsInterface::LED_ON_OFF_CCARDS_PS5_plus_5V(bool value)
{
    Logger::instance()->logText(QString("[INFO]LED_ON_OFF_CCARDS_PS5_plus_5V value: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_4.Output_CH1 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH1 << 1));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 1, &portData);
        Input_5856_Card_4.Input_CH1 = portData;
        //        qDebug() << "DO CH1:" << Output_5856_Card_4.Output_CH1
        //                 << ", DI CH1:" << static_cast<int>(Input_5856_Card_4.Input_CH1);
        Logger::instance()->logText(QString(" DO CH1:%1, DI CH1: %2")
                                        .arg(Output_5856_Card_4.Output_CH1)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH1)));
        SruLogger::instance()->logText(QString(" DO CH1:%1, DI CH1: %2")
                                           .arg(Output_5856_Card_4.Output_CH1)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH1)));

        Output_5856_Card_4.Output_CH2 = 1;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH2 << 2));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 2, &portData);
        Input_5856_Card_4.Input_CH2 = portData;

        //        qDebug() << "DO CH2:" << Output_5856_Card_4.Output_CH2
        //                 << ", DI CH2:" << static_cast<int>(Input_5856_Card_4.Input_CH2);
        Logger::instance()->logText(QString(" DO CH2:%1, DI CH2: %2")
                                        .arg(Output_5856_Card_4.Output_CH2)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));
        SruLogger::instance()->logText(QString(" DO CH2:%1, DI CH2: %2")
                                           .arg(Output_5856_Card_4.Output_CH2)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));

        Output_5856_Card_4.Output_CH2 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH2 << 2));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 2, &portData);
        Input_5856_Card_4.Input_CH2 = portData;
        //        qDebug() << "DO CH2:" << Output_5856_Card_4.Output_CH2
        //                 << ", DI CH2:" << static_cast<int>(Input_5856_Card_4.Input_CH2);
        Logger::instance()->logText(QString(" DO CH2:%1, DI CH2: %2")
                                        .arg(Output_5856_Card_4.Output_CH2)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));
        SruLogger::instance()->logText(QString(" DO CH2:%1, DI CH2: %2")
                                           .arg(Output_5856_Card_4.Output_CH2)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));
    } else {
        //////LED OFF///////
        Output_5856_Card_4.Output_CH6 = 1;

        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH6 << 6));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 2, &portData);
        Input_5856_Card_4.Input_CH2 = portData;
        //        qDebug() << "DO CH6:" << Output_5856_Card_4.Output_CH6
        //                 << ", DI CH2:" << static_cast<int>(Input_5856_Card_4.Input_CH2);
        Logger::instance()->logText(QString(" DO CH6:%1, DI CH2: %2")
                                        .arg(Output_5856_Card_4.Output_CH6)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));
        SruLogger::instance()->logText(QString(" DO CH6:%1, DI CH2: %2")
                                           .arg(Output_5856_Card_4.Output_CH6)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));

        Output_5856_Card_4.Output_CH6 = 0;
        instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH6 << 6));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 2, &portData);
        Input_5856_Card_4.Input_CH2 = portData;
        //        qDebug() << "DO CH6:" << Output_5856_Card_4.Output_CH6
        //                 << ", DI CH2:" << static_cast<int>(Input_5856_Card_4.Input_CH2);
        Logger::instance()->logText(QString(" DO CH6:%1, DI CH2: %2")
                                        .arg(Output_5856_Card_4.Output_CH6)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));
        SruLogger::instance()->logText(QString(" DO CH6:%1, DI CH2: %2")
                                           .arg(Output_5856_Card_4.Output_CH6)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH2)));
    }
}

void AdvantechCardsInterface::PS5_plus_5_Voltage_monitor()
{
    instantAiCtrl1->Read(11, g_Direct_Monitor.Input_Ch11);
}
void AdvantechCardsInterface::PS5_Negative_5_Voltage_monitor()
{
    instantAiCtrl1->Read(12, g_Direct_Monitor.Input_Ch12);
}

double ReadChannel_N_5MovingAverage(double value)
{
    // Sanity guard: warn if caller isn't passing ~5–6 V
    if (value < -2.0 || value > -6.0) {
        //        qDebug("[MA] WARN: value out of expected range: %.6f\n", value);
    }

    static double buf[500] = {0};
    static uint16_t idx = 0, cnt = 0;
    static double sum = 0.0;

    sum -= buf[idx];
    buf[idx] = value;
    sum += value;
    idx = (idx + 1) % 500;
    if (cnt < 500)
        cnt++;

    double avg = sum / cnt;

    // DEBUG: print first ~20 calls and then every 100th
    static unsigned long calls = 0;
    if (calls < 20 || (calls % 100 == 0)) {
        //        qDebug("[MA] in=%.6f  avg=%.6f  cnt=%u\n", value, avg, cnt);
    }
    calls++;

    return avg;
}

double ReadChannel_P_3p3MovingAverage(double value)
{
    // Sanity guard: warn if caller isn't passing ~5–6 V
    if (value < 2.0 || value > 6.0) {
        //        qDebug("[MA] WARN: value out of expected range: %.6f\n", value);
    }

    static double buf[500] = {0};
    static uint16_t idx = 0, cnt = 0;
    static double sum = 0.0;

    sum -= buf[idx];
    buf[idx] = value;
    sum += value;
    idx = (idx + 1) % 500;
    if (cnt < 500)
        cnt++;

    double avg = sum / cnt;

    // DEBUG: print first ~20 calls and then every 100th
    static unsigned long calls = 0;
    if (calls < 20 || (calls % 100 == 0)) {
        //        qDebug("[MA] in=%.6f  avg=%.6f  cnt=%u\n", value, avg, cnt);
    }
    calls++;

    return avg;
}

double ReadChannel_P_5MovingAverage(double value)
{
    // Sanity guard: warn if caller isn't passing ~5–6 V
    if (value < 2.0 || value > 6.0) {
        //        qDebug("[MA] WARN: value out of expected range: %.6f\n", value);
    }

    static double buf[500] = {0};
    static uint16_t idx = 0, cnt = 0;
    static double sum = 0.0;

    sum -= buf[idx];
    buf[idx] = value;
    sum += value;
    idx = (idx + 1) % 500;
    if (cnt < 500)
        cnt++;

    double avg = sum / cnt;

    // DEBUG: print first ~20 calls and then every 100th
    static unsigned long calls = 0;
    if (calls < 20 || (calls % 100 == 0)) {
        //        qDebug("[MA] in=%.6f  avg=%.6f  cnt=%u\n", value, avg, cnt);
    }
    calls++;

    return avg;
}
//double ReadChannel11MovingAverage(double value)
//{
//    double temp = value;

//    // Make buffer static so it persists across function calls
//    static double movingAverageBuffer[500] = {0};
//    static uint16_t maIndex = 0;
//    static uint16_t maCount = 0;
//    static double maSum = 0;

//    // Subtract the oldest value from the sum
//    maSum -= movingAverageBuffer[maIndex];

//    // Store the new value in the buffer
//    movingAverageBuffer[maIndex] = temp;

//    // Add the new value to the sum
//    maSum += temp;

//    // Move to the next index
//    maIndex = (maIndex + 1) % 500;

//    // Track how many values have been added (up to 500)
//    if (maCount < 500)
//        maCount++;

//    // Return the moving average
//    return maSum / maCount;
//}
void AdvantechCardsInterface::DC_DC_3p3_Voltage_monitor()
{
    double temp = 0;
    instantAiCtrl1->Read(13, temp);
    g_Direct_Monitor.Input_Ch13 = ReadChannel_P_3p3MovingAverage(temp);
    //    instantAiCtrl1->Read(13, g_Direct_Monitor.Input_Ch13);
}
void AdvantechCardsInterface::DC_DC_5_Voltage_monitor()
{
    double temp = 0;
    instantAiCtrl1->Read(14, temp);
    g_Direct_Monitor.Input_Ch14 = ReadChannel_P_5MovingAverage(temp);
    //    instantAiCtrl1->Read(14, g_Direct_Monitor.Input_Ch14);
}
void AdvantechCardsInterface::DC_DC_Negative_5_Voltage_monitor()
{
    double temp = 0;
    instantAiCtrl1->Read(15, temp);
    g_Direct_Monitor.Input_Ch15 = ReadChannel_N_5MovingAverage(temp);
    //    instantAiCtrl1->Read(15, g_Direct_Monitor.Input_Ch15);
}

void AdvantechCardsInterface::LOAD_MEASURMENT_PS6_minus_5V(bool value)
{
    Logger::instance()->logText(QString("[INFO]LOAD_MEASURMENT_PS6 -5V value: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;
    if (value == true) {
        Output_5856_Card_4.Output_CH8 = 1;
        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH8 << 0));
        QThread::msleep(100); // Wait
        instantDiCtrl1->ReadBit(0, 6, &portData);
        Input_5856_Card_4.Input_CH6 = portData;
        //        qDebug() << "DO CH8:" << Output_5856_Card_4.Output_CH8
        //                 << ", DI CH6:" << static_cast<int>(Input_5856_Card_4.Input_CH6);
        Logger::instance()->logText(QString(" DO CH8:%1, DI CH6: %2")
                                        .arg(Output_5856_Card_4.Output_CH8)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH6)));
    } else {
        Output_5856_Card_4.Output_CH8 = 0;
        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH8 << 0));
        QThread::msleep(100); // Wait
        instantDiCtrl4->ReadBit(0, 6, &portData);
        Input_5856_Card_4.Input_CH6 = portData;
        //        qDebug() << "DO CH8:" << Output_5856_Card_4.Output_CH8
        //                 << ", DI CH6:" << static_cast<int>(Input_5856_Card_4.Input_CH6);
        Logger::instance()->logText(QString(" DO CH8:%1, DI CH6: %2")
                                        .arg(Output_5856_Card_4.Output_CH8)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH6)));
    }
}
void AdvantechCardsInterface::LED_ON_CCARDS_PS6_minus5V(bool value)
{
    Logger::instance()->logText(QString("[INFO]LED_ON_CCARDS_PS6 -5V value: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_4.Output_CH8 = 0;
        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH8 << 0));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 6, &portData);
        Input_5856_Card_4.Input_CH6 = portData;
        //        qDebug() << "DO CH8:" << Output_5856_Card_4.Output_CH8
        //                 << ", DI CH6:" << static_cast<int>(Input_5856_Card_4.Input_CH6);
        Logger::instance()->logText(QString(" DO CH8:%1, DI CH6: %2")
                                        .arg(Output_5856_Card_4.Output_CH8)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH6)));
        SruLogger::instance()->logText(QString(" DO CH8:%1, DI CH6: %2")
                                           .arg(Output_5856_Card_4.Output_CH8)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH6)));
        Output_5856_Card_4.Output_CH9 = 1;
        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH9 << 1));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 7, &portData);
        Input_5856_Card_4.Input_CH7 = portData;
        //        qDebug() << "DO CH9:" << Output_5856_Card_4.Output_CH9
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_4.Input_CH7);
        Logger::instance()->logText(QString(" DO CH9:%1, DI CH7: %2")
                                        .arg(Output_5856_Card_4.Output_CH9)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));
        SruLogger::instance()->logText(QString(" DO CH9:%1, DI CH7: %2")
                                           .arg(Output_5856_Card_4.Output_CH9)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));

        Output_5856_Card_4.Output_CH9 = 0;
        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH9 << 1));
        QThread::msleep(DELAY); // Wait
        instantDiCtrl4->ReadBit(0, 7, &portData);
        Input_5856_Card_4.Input_CH7 = portData;
        //        qDebug() << "DO CH9:" << Output_5856_Card_4.Output_CH9
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_4.Input_CH7);
        Logger::instance()->logText(QString(" DO CH9:%1, DI CH7: %2")
                                        .arg(Output_5856_Card_4.Output_CH9)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));
        SruLogger::instance()->logText(QString(" DO CH9:%1, DI CH7: %2")
                                           .arg(Output_5856_Card_4.Output_CH9)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));
        // for sru  ctrl auto to connect USB
        //        qDebug() << "@@@@@@@SRU_CTRL_AUTO_emit";
        emit SRU_CTRL_AUTO_emit();
    } else {
        Output_5856_Card_4.Output_CH10 = 1;

        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH10 << 2));
        QThread::msleep(100); // Wait
        instantDiCtrl4->ReadBit(0, 7, &portData);
        Input_5856_Card_4.Input_CH7 = portData;
        //        qDebug() << "DO CH10:" << Output_5856_Card_4.Output_CH10
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_4.Input_CH7);
        Logger::instance()->logText(QString(" DO CH10:%1, DI CH7: %2")
                                        .arg(Output_5856_Card_4.Output_CH10)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));
        SruLogger::instance()->logText(QString(" DO CH10:%1, DI CH7: %2")
                                           .arg(Output_5856_Card_4.Output_CH10)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));

        Output_5856_Card_4.Output_CH10 = 0;
        instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH10 << 2));
        QThread::msleep(100); // Wait
        instantDiCtrl4->ReadBit(0, 7, &portData);
        Input_5856_Card_4.Input_CH7 = portData;
        //        qDebug() << "DO CH10:" << Output_5856_Card_4.Output_CH10
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_4.Input_CH7);
        Logger::instance()->logText(QString(" DO CH10:%1, DI CH7: %2")
                                        .arg(Output_5856_Card_4.Output_CH10)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));
        SruLogger::instance()->logText(QString(" DO CH10:%1, DI CH7: %2")
                                           .arg(Output_5856_Card_4.Output_CH10)
                                           .arg(static_cast<int>(Input_5856_Card_4.Input_CH7)));
    }
}

void AdvantechCardsInterface::Font_panel_load_on_PS7(bool value)
{
    Logger::instance()->logText(QString("[INFO]Font_panel_load_on_PS7 value: %1").arg(value));

    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_4.Output_CH22 = 1;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH17 = portData;
        //        qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);
        Logger::instance()->logText(QString(" DO CH22:%1, DI CH17: %2")
                                        .arg(Output_5856_Card_4.Output_CH22)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH17)));
    } else {
        ///////////////////////OFF//////////////

        Output_5856_Card_4.Output_CH22 = 0;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH17 = portData;
        //        qDebug() << "DO CH22:" << Output_5856_Card_1.Output_CH22
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);
        Logger::instance()->logText(QString(" DO CH22:%1, DI CH17: %2")
                                        .arg(Output_5856_Card_4.Output_CH22)
                                        .arg(static_cast<int>(Input_5856_Card_4.Input_CH17)));
    }
}

void AdvantechCardsInterface::PS7_Power_on_LRU(int index)
{
    //    BitTestLogger::instance()->logText(QString("[INFO]PS7_Power_on_LRU value: %1").arg(index));

    ////------------16V SUPPLY ON---------------/////
    Automation::BDaq::uint8 portData = 0;
    switch (index) {
    case 1: {
        voltages_16_28_32_OFF();
        Output_5856_Card_4.Output_CH22 = 0;

        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH17 = portData;
        //        qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);
        BitTestLogger::instance()->logText(QString(" DO CH22:%1, DI CH17: %2")
                                               .arg(Output_5856_Card_4.Output_CH22)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH17)));
        Output_5856_Card_4.Output_CH24 = 1;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH24 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(3, 0, &portData);
        Input_5856_Card_4.Input_CH24 = portData;
        //        qDebug() << "DO CH24:" << Output_5856_Card_4.Output_CH24
        //                 << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);
        BitTestLogger::instance()->logText(QString(" DO CH24:%1, DI CH24: %2")
                                               .arg(Output_5856_Card_4.Output_CH24)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH24)));

        Output_5856_Card_4.Output_CH24 = 0;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH24 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(3, 0, &portData);
        Input_5856_Card_4.Input_CH24 = portData;
        //        qDebug() << "DO CH24:" << Output_5856_Card_4.Output_CH24
        //                 << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);
        BitTestLogger::instance()->logText(QString(" DO CH24:%1, DI CH24: %2")
                                               .arg(Output_5856_Card_4.Output_CH24)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH24)));
        PS7_16V_28V_32V_Source_from_Power_Card(index);
        BitTestLogger::instance()->logText("16V SUPPLY ON");

    } break;

    case 2: {
        //        qDebug() << "1";
        voltages_16_28_32_OFF();
        //        qDebug() << "2";
        ////------------28V SUPPLY ON---------------/////
        Output_5856_Card_4.Output_CH22 = 0;

        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));

        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH17 = portData;
        //        qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);
        //                BitTestLogger::instance()->logText(QString(" DO CH22:%1, DI CH17: %2")
        //                                                       .arg(Output_5856_Card_4.Output_CH22)
        //                                                       .arg(static_cast<int>(Input_5856_Card_4.Input_CH17)));
        Output_5856_Card_4.Output_CH26 = 1;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH26 << 2));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(3, 1, &portData);
        Input_5856_Card_4.Input_CH26 = portData;
        //        qDebug() << "DO CH26:" << Output_5856_Card_4.Output_CH24
        //                 << ", DI CH25:" << static_cast<int>(Input_5856_Card_4.Input_CH25);

        //                BitTestLogger::instance()->logText(QString(" DO CH26:%1, DI CH25: %2")
        //                                                       .arg(Output_5856_Card_4.Output_CH26)
        //                                                       .arg(static_cast<int>(Input_5856_Card_4.Input_CH25)));
        Output_5856_Card_4.Output_CH26 = 0;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH26 << 2));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(3, 1, &portData);
        Input_5856_Card_4.Input_CH26 = portData;
        //        qDebug() << "DO CH26:" << Output_5856_Card_4.Output_CH24
        //                 << ", DI CH25:" << static_cast<int>(Input_5856_Card_4.Input_CH25);
        //                BitTestLogger::instance()->logText(QString(" DO CH26:%1, DI CH25: %2")
        //                                                       .arg(Output_5856_Card_4.Output_CH26)
        //                                                       .arg(static_cast<int>(Input_5856_Card_4.Input_CH25)));

        PS7_16V_28V_32V_Source_from_Power_Card(index);
        BitTestLogger::instance()->logText("28V SUPPLY ON");

    } break;
    case 3: {
        voltages_16_28_32_OFF();
        ////------------32V SUPPLY ON---------------/////

        Output_5856_Card_4.Output_CH22 = 0;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH17 = portData;
        //        qDebug() << "DO CH24:" << Output_5856_Card_4.Output_CH24
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);
        BitTestLogger::instance()->logText(QString(" DO CH24:%1, DI CH17: %2")
                                               .arg(Output_5856_Card_4.Output_CH24)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH17)));

        Output_5856_Card_4.Output_CH28 = 1;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH28 << 4));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(3, 2, &portData);
        Input_5856_Card_4.Input_CH26 = portData;

        Output_5856_Card_4.Output_CH28 = 0;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH28 << 4));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(3, 2, &portData);
        //        qDebug() << "DO CH28:" << Output_5856_Card_4.Output_CH28 << ",DI CH26: "
        //                 << ","
        //                 << "DO CH28:" << Output_5856_Card_4.Output_CH28
        //                 << ", DI CH26:" << static_cast<int>(Input_5856_Card_4.Input_CH26);
        BitTestLogger::instance()->logText(QString(" DO CH28:%1, DI CH26: %2")
                                               .arg(Output_5856_Card_4.Output_CH28)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH26)));
        PS7_16V_28V_32V_Source_from_Power_Card(index);
        BitTestLogger::instance()->logText("32V SUPPLY ON");

    } break;
    case 4: // EXT_V
    {
        voltages_16_28_32_OFF();
        ////------------EXT_V SUPPLY ON---------------/////

        Output_5856_Card_4.Output_CH22 = 0;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH17 = portData;
        //        qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);
        BitTestLogger::instance()->logText(QString(" DO CH22:%1, DI CH17: %2")
                                               .arg(Output_5856_Card_4.Output_CH22)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH17)));

        Output_5856_Card_4.Output_CH30 = 1;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH30 << 6));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(3, 3, &portData);
        Input_5856_Card_4.Input_CH27 = portData;
        //        qDebug() << "DO CH30:" << Output_5856_Card_4.Output_CH30
        //                 << ", DI CH27:" << static_cast<int>(Input_5856_Card_4.Input_CH27);

        BitTestLogger::instance()->logText(QString(" DO CH30:%1, DI CH27: %2")
                                               .arg(Output_5856_Card_4.Output_CH30)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH27)));
        Output_5856_Card_4.Output_CH30 = 0;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH30 << 6));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(3, 3, &portData);
        Input_5856_Card_4.Input_CH27 = portData;
        //        qDebug() << "DO CH30:" << Output_5856_Card_4.Output_CH30
        //                 << ", DI CH27:" << static_cast<int>(Input_5856_Card_4.Input_CH27);
        BitTestLogger::instance()->logText(QString(" DO CH30:%1, DI CH27: %2")
                                               .arg(Output_5856_Card_4.Output_CH30)
                                               .arg(static_cast<int>(Input_5856_Card_4.Input_CH27)));
        PS7_16V_28V_32V_Source_from_Power_Card(index);
        BitTestLogger::instance()->logText("External V SUPPLY ON");

    } break;
    case 5: // OFF
    {
        //                qDebug() << "CASE5-OFF";
        voltages_16_28_32_OFF();

    } break;
    default:
        //        qDebug() << "Unknown voltage :";
        break;
    }
}

void AdvantechCardsInterface::voltages_16_28_32_OFF()
{
    Automation::BDaq::uint8 portData = 0;

    ////------------16V SUPPLY OFF---------------/////

    Output_5856_Card_4.Output_CH22 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(2, 1, &portData);
    Input_5856_Card_4.Input_CH22 = portData;
    //    qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
    //             << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);

    Output_5856_Card_4.Output_CH25 = 1;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH25 << 1));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 0, &portData);
    Input_5856_Card_4.Input_CH24 = portData;
    //    qDebug() << "DO CH25:" << Output_5856_Card_4.Output_CH25
    //             << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);

    Output_5856_Card_4.Output_CH25 = 0;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH25 << 1));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 0, &portData);
    Input_5856_Card_4.Input_CH24 = portData;
    //    qDebug() << "DO CH25:" << Output_5856_Card_4.Output_CH25
    //             << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);
    BitTestLogger::instance()->logText("16V SUPPLY OFF");

    ////------------28V SUPPLY OFF---------------/////
    Output_5856_Card_4.Output_CH22 = 0;

    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(2, 1, &portData);
    Input_5856_Card_4.Input_CH17 = portData;
    //    qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
    //    << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);

    Output_5856_Card_4.Output_CH27 = 1;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH27 << 3));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 1, &portData);
    Input_5856_Card_4.Input_CH25 = portData;
    //    qDebug() << "DO CH27:" << Output_5856_Card_4.Output_CH27
    //             << ", DI CH25:" << static_cast<int>(Input_5856_Card_4.Input_CH25);

    Output_5856_Card_4.Output_CH27 = 0;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH27 << 3));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 1, &portData);
    Input_5856_Card_4.Input_CH25 = portData;
    //    qDebug() << "DO CH27:" << Output_5856_Card_4.Output_CH27
    //             << ", DI CH25:" << static_cast<int>(Input_5856_Card_4.Input_CH25);
    BitTestLogger::instance()->logText("28V SUPPLY OFF");

    ////------------32V SUPPLY OFF---------------/////

    Output_5856_Card_4.Output_CH22 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(2, 1, &portData);
    Input_5856_Card_4.Input_CH17 = portData;
    //    qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
    //             << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);

    Output_5856_Card_4.Output_CH29 = 1;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH29 << 5));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 2, &portData);
    Input_5856_Card_4.Input_CH26 = portData;
    //    qDebug() << "DO CH29:" << Output_5856_Card_4.Output_CH29
    //             << ", DI CH26:" << static_cast<int>(Input_5856_Card_4.Input_CH26);

    Output_5856_Card_4.Output_CH29 = 0;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH29 << 5));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 2, &portData);
    Input_5856_Card_4.Input_CH26 = portData;
    //    qDebug() << "DO CH29:" << Output_5856_Card_4.Output_CH29
    //             << ", DI CH26:" << static_cast<int>(Input_5856_Card_4.Input_CH26);
    BitTestLogger::instance()->logText("32V SUPPLY OFF");

    ////------------EXT_V SUPPLY OFF---------------/////

    Output_5856_Card_4.Output_CH22 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(2, 1, &portData);
    Input_5856_Card_4.Input_CH17 = portData;
    //    qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
    //             << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);

    Output_5856_Card_4.Output_CH31 = 1;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH31 << 7));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 3, &portData);
    Input_5856_Card_4.Input_CH27 = portData;
    //    qDebug() << "DO CH31:" << Output_5856_Card_4.Output_CH31
    //             << ", DI CH27:" << static_cast<int>(Input_5856_Card_4.Input_CH27);
    Output_5856_Card_4.Output_CH31 = 0;
    instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH31 << 7));
    QThread::msleep(100);
    instantDiCtrl4->ReadBit(3, 3, &portData);
    Input_5856_Card_4.Input_CH27 = portData;
    //    qDebug() << "DO CH31:" << Output_5856_Card_4.Output_CH31
    //             << ", DI CH27:" << static_cast<int>(Input_5856_Card_4.Input_CH27);
    BitTestLogger::instance()->logText("External V SUPPLY OFF");

    g_Direct_Monitor.Input_Ch6_16 = 0;
    g_Direct_Monitor.Input_Ch6_28 = 0;
    g_Direct_Monitor.Input_Ch6_32 = 0;
    g_Direct_Monitor.Input_ch6_Ext = 0;
}

void AdvantechCardsInterface::onTriggerCard2AIButtonClicked()
{
    instantAiCtrl2->Read(0, ip_ch1);
    instantAiCtrl2->Read(1, ip_ch2);
    instantAiCtrl2->Read(2, ip_ch3);
    instantAiCtrl2->Read(3, ip_ch4);
    instantAiCtrl2->Read(4, ip_ch5);
    instantAiCtrl2->Read(5, ip_ch6);
    instantAiCtrl2->Read(6, ip_ch7);
    instantAiCtrl2->Read(7, ip_ch8);

    //    qDebug() << "Card2ip_ch1:" << ip_ch1;
}

void AdvantechCardsInterface::onTriggerCard1DOButtonClicked()
{
    //    if (!instantDoCtrl || !instantDoCtrl->getInitialized()) {
    //        QMessageBox::warning(this, "Error", "DO device is not ready.");
    //        return;
    //    }

    // Example: Read ON/OFF from checkboxes or buttons
    bool ch0 = true; // Checkbox for CH0
    bool ch1 = true; // Checkbox for CH1

    Automation::BDaq::uint8 portData = 0;
    portData |= (ch0 << 0); // CH0
    portData |= (ch1 << 1); // CH1

    ErrorCode err = instantDoCtrl1->Write(0, portData);

    if (err != Automation::BDaq::Success) {
        //        QMessageBox::warning(nullptr,
        //                             "DO Write Error",
        //                             QString("Failed to write DO values. Error Code: %1").arg(err));
        return;
    }

    //    qDebug() << "DO written -> CH0:" << ch0 << ", CH1:" << ch1;

    //    ui->lineedit_do_status->setText(QString("DO -> CH0: %1, CH1: %2")
    //                                    .arg(ch0 ? "ON" : "OFF")
    //                                    .arg(ch1 ? "ON" : "OFF"));
}

void AdvantechCardsInterface::onTriggerCard2DOButtonClicked()
{
    //    if (!instantDoCtrl || !instantDoCtrl->getInitialized()) {
    //        QMessageBox::warning(this, "Error", "DO device is not ready.");
    //        return;
    //    }

    // Example: Read ON/OFF from checkboxes or buttons
    bool ch0 = true; // Checkbox for CH0
    bool ch1 = true; // Checkbox for CH1

    Automation::BDaq::uint8 portData = 0;
    portData |= (ch0 << 0); // CH0
    portData |= (ch1 << 1); // CH1

    ErrorCode err = instantDoCtrl2->Write(0, portData);

    if (err != Automation::BDaq::Success) {
        //        QMessageBox::warning(nullptr,
        //                             "DO Write Error",
        //                             QString("Failed to write DO values. Error Code: %1").arg(err));
        return;
    }

    //    qDebug() << "Card2DO written -> CH0:" << ch0 << ", CH1:" << ch1;

    //    ui->lineedit_do_status->setText(QString("DO -> CH0: %1, CH1: %2")
    //                                    .arg(ch0 ? "ON" : "OFF")
    //                                    .arg(ch1 ? "ON" : "OFF"));
}

void AdvantechCardsInterface::onTriggerCard1DIButtonClicked()
{
    //    if (!instantDiCtrl || !instantDiCtrl->getInitialized()) {
    //        QMessageBox::warning(this, "Error", "Device is not ready.");
    //        return;
    //    }

    //    Automation::BDaq::uint8 portData = 0;

    // Read entire port 0 (assumes 8-channel DI on one port)
    //    Automation::BDaq::ErrorCode err = instantDiCtrl1->Read(0, portData);

    //    qDebug() << "Port 0 ErrorCode:" << err << ", Value:" << static_cast<int>(portData);

    //    if (err != Automation::BDaq::Success) {
    //        QMessageBox::warning(this, "Read Error",
    //                             QString("Failed to read DI values.\nPort 0 Error Code: %1").arg(err));
    //        return;
    //    }

    // Extract individual bits
    //    bool ch0 = (portData >> 0) & 1;
    //    bool ch1 = (portData >> 1) & 1;

    //    if (portData == 0xFF) { //for testing purpose
    //        ch0 = false;
    //        ch1 = false;
    //    }
    //    qDebug() << "DI READ -> CH0:" << ch0 << ", CH1:" << ch1;

    //    QString combinedText = QString("CH0: %1, CH1: %2")
    //            .arg(ch0 ? "ON" : "OFF")
    //            .arg(ch1 ? "ON" : "OFF");
    //    ui->ch_le1->setText(combinedText);
}

void AdvantechCardsInterface::onTriggerCard2DIButtonClicked()
{
    //    if (!instantDiCtrl || !instantDiCtrl->getInitialized()) {
    //        QMessageBox::warning(this, "Error", "Device is not ready.");
    //        return;
    //    }

    //    Automation::BDaq::uint8 portData = 0;

    // Read entire port 0 (assumes 8-channel DI on one port)
    //    Automation::BDaq::ErrorCode err = instantDiCtrl2->Read(0, portData);

    //    qDebug() << "Port 0 ErrorCode:" << err << ", Value:" << static_cast<int>(portData);

    //    if (err != Automation::BDaq::Success) {
    //        QMessageBox::warning(this, "Read Error",
    //                             QString("Failed to read DI values.\nPort 0 Error Code: %1").arg(err));
    //        return;
    //    }

    // Extract individual bits
    //    bool ch0 = (portData >> 0) & 1;
    //    bool ch1 = (portData >> 1) & 1;

    //    if (portData == 0xFF) { //for testing purpose
    //        ch0 = false;
    //        ch1 = false;
    //    }
    //    qDebug() << "Card2DI READ -> CH0:" << ch0 << ", CH1:" << ch1;

    //    QString combinedText = QString("CH0: %1, CH1: %2")
    //            .arg(ch0 ? "ON" : "OFF")
    //            .arg(ch1 ? "ON" : "OFF");
    //    ui->ch_le1->setText(combinedText);
}

void AdvantechCardsInterface::onTriggerDIButtonClicked_5856()
{
    //    if (!instantDiCtrl || !instantDiCtrl->getInitialized()) {
    //        QMessageBox::warning(this, "Error", "Device is not ready.");
    //        return;
    //    }

    Automation::BDaq::uint8 portData = 0;

    // Read entire port 0 (assumes 8-channel DI on one port)
    // Automation::BDaq::ErrorCode err = instantDiCtrl->Read(0, portData);

    //uint32 testVar = 0xFFFFFFFF;

    instantDiCtrl1->Read(0, portData);
    instantDiCtrl1->Read(1, portData);
    instantDiCtrl1->Read(2, portData);
    instantDiCtrl1->Read(3, portData);
}

void AdvantechCardsInterface::onTriggerCard1DO_ONButtonClicked_5856()
{
    //    qDebug() << "in timer onTriggerCard1DO_ONButtonClicked_5856";
    currentDOState = DO0; // start from DO0
    checkTimer1_5856 = new QTimer(this);

    checkTimer1_5856->setInterval(90); // 90ms DELAY
    connect(checkTimer1_5856,
            &QTimer::timeout,
            this,
            &AdvantechCardsInterface::checkNextChannelCard1_5856);
    checkTimer1_5856->start();
    //    qDebug() << "11in timer onTriggerCard1DO_ONButtonClicked_5856";
}

void AdvantechCardsInterface::onTriggerCard2DO_ONButtonClicked_5856()
{
    currentDOState = DO0; // start from DO0
    checkTimer2_5856 = new QTimer(this);
    checkTimer2_5856->setInterval(90); // 90ms DELAY
    connect(checkTimer2_5856,
            &QTimer::timeout,
            this,
            &AdvantechCardsInterface::checkNextChannelCard2_5856);
    // }

    //currentChannelIndex2 = 0;
    //waitingForResponse2 = false;
    checkTimer2_5856->start();
}

void AdvantechCardsInterface::onTriggerCard3DO_ONButtonClicked_5856()
{
    currentDOState = DO0; // start from DO0
    checkTimer3_5856 = new QTimer(this);
    checkTimer3_5856->setInterval(90); // 90ms DELAY
    connect(checkTimer3_5856,
            &QTimer::timeout,
            this,
            &AdvantechCardsInterface::checkNextChannelCard3_5856);

    // currentChannelIndex3 = 0;
    checkTimer3_5856->start();
}

void AdvantechCardsInterface::onTriggerCard4DO_ONButtonClicked_5856()
{
    currentDOState = DO0; // start from DO0
    if (!checkTimer4_5856) {
        checkTimer4_5856 = new QTimer(this);
        checkTimer4_5856->setInterval(90); // 90ms DELAY
        connect(checkTimer4_5856,
                &QTimer::timeout,
                this,
                &AdvantechCardsInterface::checkNextChannelCard4_5856);
    }
    // currentChannelIndex4 = 0;
    checkTimer4_5856->start();
}
void AdvantechCardsInterface::onTriggerCard2ADCCheck_4716()
{
    DAC_VOLTAGE_DAC_CH1();
    uint8_t voltage[9] = {0};

    for (int i = 0; i < 8; i++) {
        voltage[0] |= (g_ADC_SelfTest.test1Status[i] & 0x01) << i;
        voltage[1] |= (g_ADC_SelfTest.test2Status[i] & 0x01) << i;
        voltage[2] |= (g_ADC_SelfTest.test3Status[i] & 0x01) << i;
        voltage[3] |= (g_ADC_SelfTest.test4Status[i] & 0x01) << i;
        voltage[4] |= (g_ADC_SelfTest.test5Status[i] & 0x01) << i;
        voltage[5] |= (g_ADC_SelfTest.test6Status[i] & 0x01) << i;
        voltage[6] |= (g_ADC_SelfTest.test7Status[i] & 0x01) << i;
        voltage[7] |= (g_ADC_SelfTest.test8Status[i] & 0x01) << i;
        voltage[8] |= (g_ADC_SelfTest.test9Status[i] & 0x01) << i;
    }

    bool allPass = true;
    for (int i = 0; i < 9; ++i) {
        if (voltage[i] != 0xFF) {
            allPass = false;
            // break;
        }
    }

    //emit (allPass);
    emit adcCard2Result(allPass);
}

bool AdvantechCardsInterface::CheckAndSetDO(InstantDoCtrl *instantDoCtrl1,
                                            InstantDiCtrl *instantDiCtrl1,
                                            int Writeport,
                                            int Readport,
                                            uint8_t Outputs,
                                            uint8_t readbyte_position,
                                            uint32_t &Input_CH1,
                                            USB_5856_enum value,
                                            USB_5856_enum &currentDOState,
                                            uint8_t latchRelay)
{
    static int count = 0;
    uint8_t readBack = 0;
    if (instantDoCtrl1->Write(Writeport, Outputs) != Success) {
        return false;
    }
    QThread::msleep(90);

    if (instantDiCtrl1->ReadBit(Readport, readbyte_position, &readBack) != Success) {
        count = 0;
        return false;
    }

    Input_CH1 = readBack;

    if (latchRelay == 0) {
        if (Input_CH1) {
            if (instantDoCtrl1->Write(Writeport, 0) != Success) {
                count = 0;
                return false;
            }

            count = 0;
            currentDOState = value;
            return true;
        }
    }
    if (latchRelay == 1) {
        if (Input_CH1 == 0) {
            if (instantDoCtrl1->Write(Writeport, 0) != Success) {
                count = 0;
                return false;
            }

            count = 0;
            currentDOState = value;
            return true;
        }
    }
    if (count == 9) {
        count = 0;
        currentDOState = value;
        if (instantDoCtrl1->Write(Writeport, 0) != Success) {
            return false;
        }
    }
    //    qDebug() << "count in 1 " << count;
    count++;
    return true;
}

void AdvantechCardsInterface::checkNextChannelCard1_5856()
{
    // qDebug() << "1111111111checkNextChannelCard1_5856";
    if (currentDOState > DO31) {
        g_SelfTestStatus.USB_5856_Card1_STS = 1;
        checkTimer1_5856->stop();
        return;
    }

    static uint32_t Readport = 0;

    uint8_t writePort = 0;
    uint8_t ReadPort = 0;

    uint8_t WriteBitPosition = 0;
    uint8_t ReadBitPosition = 0;

    // qDebug() << "currentDOState" << currentDOState;

    switch (currentDOState) {
    case DO0: {
        //qDebug() << "case11111111111111111111111111";

        Output_5856_Card_1.Output_CH0 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH0 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO2,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH0 = Readport;

            Logger::instance()->logText("Output_5856_Card_1.Output_CH0 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH0 = %1").arg(Readport));
        }
        //        qDebug() << Readport << currentDOState;
        break;
    }
        //    case DO1: {
        //        Output_5856_Card_1.Output_CH1 = 1;
        //        writePort = 0;
        //        ReadPort = 0;
        //        WriteBitPosition = 1;
        //        ReadBitPosition = 1;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH1 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO2,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH1 = Readport;

        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH1 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH1 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO2: {
        Output_5856_Card_1.Output_CH2 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH2 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO3,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH2 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH2= 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH2 = %1").arg(Readport));
        }
        break;
    }

    case DO3: {
        Output_5856_Card_1.Output_CH3 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH3 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO4,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH3 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH3 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH3 = %1").arg(Readport));
        }
        break;
    }
    case DO4: //latchRelay
    {
        Output_5856_Card_1.Output_CH4 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 4;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH4 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO6,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH3 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH4 = 4");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH3 = %1").arg(Readport));
        }
        break;
    }

        //    case DO5: {
        //        Output_5856_Card_1.Output_CH5 = 1;
        //        writePort = 0;
        //        ReadPort = 0;
        //        WriteBitPosition = 5;
        //        ReadBitPosition = 4;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH5 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO6,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH4 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH5 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH4 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO6: {
        Output_5856_Card_1.Output_CH6 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 6;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH6 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO7,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH5 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH6 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH5 = %1").arg(Readport));
        }
        break;
    }

    case DO7: {
        Output_5856_Card_1.Output_CH7 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 7;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH7 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO9,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH5 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH7 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH5 = %1").arg(Readport));
        }
        break;
    }

        //    case DO8: {
        //        Output_5856_Card_1.Output_CH8 = 1;
        //        writePort = 1;
        //        ReadPort = 0;
        //        WriteBitPosition = 0;
        //        ReadBitPosition = 6;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH8 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO9,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH6 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH8 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH6 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO9: {
        Output_5856_Card_1.Output_CH9 = 1;
        writePort = 1;
        ReadPort = 0;
        WriteBitPosition = 1;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH9 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO10,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH7 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH9 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH7 = %1").arg(Readport));
        }
        break;
    }
    case DO10: {
        Output_5856_Card_1.Output_CH10 = 1;
        writePort = 1;
        ReadPort = 0;
        WriteBitPosition = 2;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH10 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO11,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH7 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH10 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH7 = %1").arg(Readport));
        }
        break;
    }
    case DO11: {
        Output_5856_Card_1.Output_CH11 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 3;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH11 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO12,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH8 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH11 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH8 = %1").arg(Readport));
        }
        break;
    }
    case DO12: {
        Output_5856_Card_1.Output_CH12 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 4;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH12 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO14,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH8 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH12 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH8 = %1").arg(Readport));
        }
        break;
    }
        //    case DO13: {
        //        Output_5856_Card_1.Output_CH13 = 1;
        //        writePort = 1;
        //        ReadPort = 1;
        //        WriteBitPosition = 5;
        //        ReadBitPosition = 1;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH13 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO14,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH9 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH13 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH9 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO14: {
        Output_5856_Card_1.Output_CH14 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 6;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH14 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO15,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH10 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH14 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH10 = %1").arg(Readport));
        }
        break;
    }
    case DO15: {
        Output_5856_Card_1.Output_CH15 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 7;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH15 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO16,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH10 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH15 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH10 = %1").arg(Readport));
        }
        break;
    }

    case DO16: {
        Output_5856_Card_1.Output_CH16 = 1;
        writePort = 2;
        ReadPort = 1;
        WriteBitPosition = 0;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH16 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO17,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH11 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH16 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH11 = %1").arg(Readport));
        }
        break;
    }
    case DO17: {
        Output_5856_Card_1.Output_CH17 = 1;
        writePort = 2;
        ReadPort = 1;
        WriteBitPosition = 1;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH17 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO19,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH11 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH17 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH11 = %1").arg(Readport));
        }
        break;
    }
        //    case DO18: {
        //        Output_5856_Card_1.Output_CH18 = 1;
        //        writePort = 2;
        //        ReadPort = 1;
        //        WriteBitPosition = 2;
        //        ReadBitPosition = 4;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH18 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO19,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH12 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH18 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH12 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO19: {
        Output_5856_Card_1.Output_CH19 = 1;
        writePort = 2;
        ReadPort = 1;
        WriteBitPosition = 3;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH19 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO20,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH13 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH19 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH13 = %1").arg(Readport));
        }
        break;
    }
    case DO20: {
        Output_5856_Card_1.Output_CH20 = 1;
        writePort = 2;
        ReadPort = 1;
        WriteBitPosition = 4;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH20 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO21,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH13 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH20 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH13 = %1").arg(Readport));
        }
        break;
    }
    case DO21: {
        Output_5856_Card_1.Output_CH21 = 1;
        writePort = 2;
        ReadPort = 1;
        WriteBitPosition = 5;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH21 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO24,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_1.Input_CH14 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH21 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH14 = %1").arg(Readport));
        }
        break;
    }
        //    case DO22: {
        //        Output_5856_Card_1.Output_CH22 = 1;
        //        writePort = 2;
        //        ReadPort = 1;
        //        WriteBitPosition = 6;
        //        ReadBitPosition = 7;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH22 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO25,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH15 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH22 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH15 = %1").arg(Readport));
        //        }
        //        break;
        //    }

        //    case DO23: {
        //        Output_5856_Card_1.Output_CH23 = 1;
        //        writePort = 2;
        //        ReadPort = 2;
        //        WriteBitPosition = 7;
        //        ReadBitPosition = 0;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH23 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO22,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH16 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH23 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH16 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO24: {
        Output_5856_Card_1.Output_CH24 = 1;
        writePort = 3;
        ReadPort = 1;
        WriteBitPosition = 0;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl1,
                                    instantDiCtrl1,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_1.Output_CH24 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    (USB_5856_enum) 32,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_1.Input_CH14 = Readport;
            Logger::instance()->logText("Output_5856_Card_1.Output_CH24 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH14 = %1").arg(Readport));
            //            qDebug() << "before" << QString::number(outputs, 16);
            //            qDebug() << "before24" << QString::number(Inputs, 16);
        }
        break;
    }

        //    case DO25: {
        //        Output_5856_Card_1.Output_CH25 = 1;
        //        writePort = 3;
        //        ReadPort = 2;
        //        WriteBitPosition = 1;
        //        ReadBitPosition = 2;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH25 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO26,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH18 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH25 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH18 = %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO26: {
        //        Output_5856_Card_1.Output_CH26 = 1;
        //        writePort = 3;
        //        ReadPort = 2;
        //        WriteBitPosition = 2;
        //        ReadBitPosition = 3;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH26 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO27,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH19 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH26 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH19 = %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO27: {
        //        Output_5856_Card_1.Output_CH27 = 1;
        //        writePort = 3;
        //        ReadPort = 2;
        //        WriteBitPosition = 3;
        //        ReadBitPosition = 4;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH27 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO28,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH20 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH27 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH20 = %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO28: {
        //        Output_5856_Card_1.Output_CH28 = 1;
        //        writePort = 3;
        //        ReadPort = 2;
        //        WriteBitPosition = 4;
        //        ReadBitPosition = 5;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH28 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO29,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH21 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH28 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH21 = %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO29: {
        //        Output_5856_Card_1.Output_CH29 = 1;
        //        writePort = 3;
        //        ReadPort = 2;
        //        WriteBitPosition = 5;
        //        ReadBitPosition = 6;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH29 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO30,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH22 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH29 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH22 = %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO30: {
        //        Output_5856_Card_1.Output_CH30 = 1;
        //        writePort = 3;
        //        ReadPort = 2;
        //        WriteBitPosition = 6;
        //        ReadBitPosition = 7;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH30 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO31,
        //                                    currentDOState,
        //                                    0);

        //        if (result) {
        //            Input_5856_Card_1.Input_CH23 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH30 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH23 = %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO31: {
        //        Output_5856_Card_1.Output_CH31 = 1;
        //        writePort = 3;
        //        ReadPort = 3;
        //        WriteBitPosition = 7;
        //        ReadBitPosition = 0;
        //        bool result = CheckAndSetDO(instantDoCtrl1,
        //                                    instantDiCtrl1,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_1.Output_CH31 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    (USB_5856_enum) 32,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_1.Input_CH24 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_1.Output_CH31 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_1.Input_CH24 = %1").arg(Readport));
        //            qDebug() << "before" << QString::number(outputs, 16);
        //            qDebug() << "before31" << QString::number(Inputs, 16);
        //        }
        //        break;
        //    }

    default:
        //        qDebug() << "default1";
        checkTimer1_5856->stop();
        // g_SelfTestStatus.USB_5856_Card1_STS = 1;
        //        qDebug() << "default2";
        break;
    }

    //    memcpy(&outputs,&Output_5856_Card_1,sizeof(Output_5856_Card_1));
    //    memcpy(&Inputs,&Input_5856_Card_1,sizeof(Input_5856_Card_1));
    //    qDebug() << "outputs-after"  << QString::number(outputs,16);
    //    qDebug() << "Inputs-after"  << QString::number(Inputs,16);
}

void AdvantechCardsInterface::checkNextChannelCard2_5856()
{
    if (currentDOState > DO29) {
        g_SelfTestStatus.USB_5856_Card2_STS = 1;
        checkTimer2_5856->stop();
        return;
    }

    static uint32_t Readport = 0;

    uint8_t writePort = 0;
    uint8_t ReadPort = 0;

    uint8_t WriteBitPosition = 0;
    uint8_t ReadBitPosition = 0;
    switch (currentDOState) {
    case DO0: {
        Output_5856_Card_2.Output_CH0 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH0 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO1,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH0 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH0 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH0 = %1").arg(Readport));
            //} else {
            //  Logger::instance()->logText(
            //            g_SelfTestStatus.USB_5856_Card2_STS = -1; // or 0 for fail
            // emit card2FailureDetected();              // Optional: connect to UI feedback
            // checkTimer2_5856->stop();
        }
        //        qDebug() << Readport << currentDOState;
        break;
    }
    case DO1: {
        Output_5856_Card_2.Output_CH1 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH1 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO2,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH1 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH1 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH1 = %1").arg(Readport));
        }
        break;
    }
    case DO2: {
        Output_5856_Card_2.Output_CH2 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH2 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO3,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH2 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH2 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH2 = %1").arg(Readport));
        }
        break;
    }
    case DO3: {
        Output_5856_Card_2.Output_CH3 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH3 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO4,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH3 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH3 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH3 = %1").arg(Readport));
        }
        break;
    }
    case DO4: //latchRelay
    {
        Output_5856_Card_2.Output_CH4 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH4 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO5,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH4 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH4 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH4 = %1").arg(Readport));
        }
        break;
    }
    case DO5:

    {
        Output_5856_Card_2.Output_CH5 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH5 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO6,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH5 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH5 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH5 = %1").arg(Readport));
        }
        break;
    }
    case DO6: {
        Output_5856_Card_2.Output_CH6 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 6;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH6 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO7,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH6 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH6 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH6 = %1").arg(Readport));
        }
        break;
    }

    case DO7: {
        Output_5856_Card_2.Output_CH7 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 7;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH7 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO8,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH7 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH7 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH7 = %1").arg(Readport));
        }
        break;
    }

    case DO8: {
        Output_5856_Card_2.Output_CH8 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH8 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO9,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH8 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH8 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH8 = %1").arg(Readport));
        }
        break;
    }
    case DO9: {
        Output_5856_Card_2.Output_CH9 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH9 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO12,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH9 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH9 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH9 = %1").arg(Readport));
        }
        break;
    }
    case DO12: {
        Output_5856_Card_2.Output_CH12 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH12 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO13,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH12 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH12 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH12 = %1").arg(Readport));
        }
        break;
    }
    case DO13: {
        Output_5856_Card_2.Output_CH13 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH13 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO14,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH13 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH13 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH13 = %1").arg(Readport));
        }
        break;
    }
    case DO14: {
        Output_5856_Card_2.Output_CH14 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 6;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH14 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO15,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH14 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH14 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH14 = %1").arg(Readport));
        }
        break;
    }
    case DO15: {
        Output_5856_Card_2.Output_CH15 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 7;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH15 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO16,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH15 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH15 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH15 = %1").arg(Readport));
        }
        break;
    }

#if 1
    case DO16: {
        Output_5856_Card_2.Output_CH16 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH16 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO17,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH16 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH16 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH16 = %1").arg(Readport));
        }
        break;
    }
    case DO17: {
        Output_5856_Card_2.Output_CH17 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH17 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO18,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH17 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH17 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH17 = %1").arg(Readport));
        }
        break;
    }
    case DO18: {
        Output_5856_Card_2.Output_CH18 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH18 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO19,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH18 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH18= 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH18= %1").arg(Readport));
        }
        break;
    }
    case DO19: {
        Output_5856_Card_2.Output_CH19 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH19 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO20,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH19 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH19 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH19= %1").arg(Readport));
        }
        break;
    }
    case DO20: {
        Output_5856_Card_2.Output_CH20 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH20 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO21,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH20 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH20 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH20 = %1").arg(Readport));
        }
        break;
    }
    case DO21: {
        Output_5856_Card_2.Output_CH21 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH21 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO22,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH21 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH21 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH21 = %1").arg(Readport));
        }
        break;
    }
    case DO22: {
        Output_5856_Card_2.Output_CH22 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 6;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH22 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO23,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH22 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH22 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH22 = %1").arg(Readport));
        }
        break;
    }

    case DO23: {
        Output_5856_Card_2.Output_CH23 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 7;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH23 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO24,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH23 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH23 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH23= %1").arg(Readport));
        }
        break;
    }
    case DO24: {
        Output_5856_Card_2.Output_CH24 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH24 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO25,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH24 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH24 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH24 = %1").arg(Readport));
        }
        break;
    }
#endif
#if 1
    case DO25: {
        Output_5856_Card_2.Output_CH25 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH25 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO26,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH25 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH25 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH25 = %1").arg(Readport));
        }
        break;
    }
    case DO26: {
        Output_5856_Card_2.Output_CH26 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH26 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO27,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH26 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH26 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH26= %1").arg(Readport));
        }
        break;
    }
    case DO27: {
        Output_5856_Card_2.Output_CH27 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH27 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO28,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH27 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH27 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH27 = %1").arg(Readport));
        }
        break;
    }
    case DO28: {
        Output_5856_Card_2.Output_CH28 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH28 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO29,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH28 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH28 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH28 = %1").arg(Readport));
        }
        break;
    }
    case DO29: {
        Output_5856_Card_2.Output_CH29 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl2,
                                    instantDiCtrl2,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_2.Output_CH29 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    (USB_5856_enum) 32,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_2.Input_CH29 = Readport;
            Logger::instance()->logText("Output_5856_Card_2.Output_CH29 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH29 = %1").arg(Readport));
        }
        break;
    }

    //    case DO30:
    //    {
    //        Output_5856_Card_2.Output_CH30 = 1;
    //        writePort = 3;
    //        ReadPort = 3;
    //        WriteBitPosition = 6;
    //        ReadBitPosition=6;
    //        bool result = CheckAndSetDO(instantDoCtrl2, instantDiCtrl2,writePort, ReadPort, Output_5856_Card_2.Output_CH30<<WriteBitPosition,
    //                                    ReadBitPosition,Readport, DO31 , currentDOState,0);
    //        if(result)
    //        {
    //            Input_5856_Card_2.Input_CH30 = Readport;
    //  Logger::instance()->logText("Output_5856_Card_2.Output_CH30 = 1");
    // Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH30 = %1").arg(Readport));
    //        }
    //        break;
    //    }
    //    case DO31:
    //    {
    //        Output_5856_Card_2.Output_CH31 = 1;
    //        writePort = 3;
    //        ReadPort = 3;
    //        WriteBitPosition = 7;
    //        ReadBitPosition=7;
    //        bool result = CheckAndSetDO(instantDoCtrl2, instantDiCtrl2,writePort, ReadPort, Output_5856_Card_2.Output_CH31<<WriteBitPosition,
    //                                    ReadBitPosition,Readport, (USB_5856_enum)32 , currentDOState,0);
    //        if(result)
    //        {
    //            Input_5856_Card_2.Input_CH31 = Readport;
    // Logger::instance()->logText("Output_5856_Card_2.Output_CH31 = 1");
    // Logger::instance()->logText(QString("Input_5856_Card_2.Input_CH31 = %1").arg(Readport));
    //        }
    //        break;
    //    }

#endif
    default:

        checkTimer2_5856->stop();
        //  g_SelfTestStatus.USB_5856_Card2_STS = 1;
        break;
    }
    //    memcpy(&outputs,&Output_5856_Card_2,sizeof(Output_5856_Card_2));
    //    memcpy(&Inputs,&Input_5856_Card_2,sizeof(Input_5856_Card_2));
    //    qDebug() << "card2outputs"  << QString::number(outputs,16);
    //    qDebug() << "card2Inputs"  << QString::number(Inputs,16);
}

void AdvantechCardsInterface::checkNextChannelCard3_5856()
{
    // uint8_t currentDOState = DO0;
    static uint32_t Readport = 0;

    uint8_t writePort = 0;
    uint8_t ReadPort = 0;

    uint8_t WriteBitPosition = 0;
    uint8_t ReadBitPosition = 0;
    switch (currentDOState) {
#if 1
    case DO0: {
        Output_5856_Card_3.Output_CH0 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH0 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO1,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH0 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH0 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH0 = %1").arg(Readport));
        }
        //        qDebug() << Readport << currentDOState;
        break;
    }
    case DO1: {
        Output_5856_Card_3.Output_CH1 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH1 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO2,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH1 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH1 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH1 = %1").arg(Readport));
        }
        break;
    }
    case DO2: {
        Output_5856_Card_3.Output_CH2 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH2 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO3,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH2 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH2= 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH2 = %1").arg(Readport));
        }
        break;
    }

    case DO3: {
        Output_5856_Card_3.Output_CH3 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH3 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO4,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH3 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH3 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH3 = %1").arg(Readport));
        }
        break;
    }
    case DO4: //latchRelay
    {
        Output_5856_Card_3.Output_CH4 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH4 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO5,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH4 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH4 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH4 = %1").arg(Readport));
        }
        break;
    }

    case DO5: {
        Output_5856_Card_3.Output_CH5 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH5 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO6,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH5 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH5 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH5 = %1").arg(Readport));
        }
        break;
    }
    case DO6: {
        Output_5856_Card_3.Output_CH6 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 6;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH6 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO7,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH6 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH6 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH6 = %1").arg(Readport));
        }
        break;
    }

    case DO7: {
        Output_5856_Card_3.Output_CH7 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 7;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH7 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO8,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH7 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH7 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH7 = %1").arg(Readport));
        }
        break;
    }

    case DO8: {
        Output_5856_Card_3.Output_CH8 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH8 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO9,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH8 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH8 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH8 = %1").arg(Readport));
        }
        break;
    }
    case DO9: {
        Output_5856_Card_3.Output_CH9 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH9 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO10,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH9 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH9 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH9 = %1").arg(Readport));
        }
        break;
    }
    case DO10: {
        Output_5856_Card_3.Output_CH10 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH10 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO11,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH10 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH10 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH10 = %1").arg(Readport));
        }
        break;
    }
    case DO11: {
        Output_5856_Card_3.Output_CH11 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH11 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO12,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH11 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH11 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH11 = %1").arg(Readport));
        }
        break;
    }
    case DO12: {
        Output_5856_Card_3.Output_CH12 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH12 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO13,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH12 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH12 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH12 = %1").arg(Readport));
        }
        break;
    }
    case DO13: {
        Output_5856_Card_3.Output_CH13 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH13 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO14,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH13 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH13 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH13 = %1").arg(Readport));
        }
        break;
    }
    case DO14: {
        Output_5856_Card_3.Output_CH14 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 6;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH14 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO15,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH14 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH14 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH14 = %1").arg(Readport));
        }
        break;
    }
    case DO15: {
        Output_5856_Card_3.Output_CH15 = 1;
        writePort = 1;
        ReadPort = 1;
        WriteBitPosition = 7;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH15 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO16,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH15 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH15 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH15 = %1").arg(Readport));
        }
        break;
    }
#endif
#if 1
    case DO16: {
        Output_5856_Card_3.Output_CH16 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH16 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO17,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH16 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH16 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH16 = %1").arg(Readport));
        }
        break;
    }
    case DO17: {
        Output_5856_Card_3.Output_CH17 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH17 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO18,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH17 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH17 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH17= %1").arg(Readport));
        }
        break;
    }
    case DO18: {
        Output_5856_Card_3.Output_CH18 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH18 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO19,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH18 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH18 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH18 = %1").arg(Readport));
        }
        break;
    }
    case DO19: {
        Output_5856_Card_3.Output_CH19 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH19 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO20,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH19 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH19= 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH19 = %1").arg(Readport));
        }
        break;
    }
    case DO20: {
        Output_5856_Card_3.Output_CH20 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH20 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO21,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH20 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH20 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH20 = %1").arg(Readport));
        }
        break;
    }
    case DO21: {
        Output_5856_Card_3.Output_CH21 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH21 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO22,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH21 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH21 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH21 = %1").arg(Readport));
        }
        break;
    }
    case DO22: {
        Output_5856_Card_3.Output_CH22 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 6;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH22 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO23,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH22 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH22 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH22= %1").arg(Readport));
        }
        break;
    }

    case DO23: {
        Output_5856_Card_3.Output_CH23 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 7;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH23 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO24,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH23 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH23 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH23= %1").arg(Readport));
        }
        break;
    }
    case DO24: {
        Output_5856_Card_3.Output_CH24 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH24 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO25,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH24 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH24 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH24 = %1").arg(Readport));
        }
        break;
    }
#endif
#if 1
    case DO25: {
        Output_5856_Card_3.Output_CH25 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH25 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO26,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH25 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH25= 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH25 = %1").arg(Readport));
        }
        break;
    }
    case DO26: {
        Output_5856_Card_3.Output_CH26 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH26 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO27,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH26 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH26= 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH26= %1").arg(Readport));
        }
        break;
    }
    case DO27: {
        Output_5856_Card_3.Output_CH27 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH27 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO28,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH27 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH27= 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH27= %1").arg(Readport));
        }
        break;
    }
    case DO28: {
        Output_5856_Card_3.Output_CH28 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 4;
        ReadBitPosition = 4;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH28 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO29,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH28 = Readport;
            Logger::instance()->logText("Output_5856_Card_3.Output_CH28= 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH28= %1").arg(Readport));
        }
        break;
    }
    case DO29: {
        Output_5856_Card_3.Output_CH29 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 5;
        ReadBitPosition = 5;
        bool result = CheckAndSetDO(instantDoCtrl3,
                                    instantDiCtrl3,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_3.Output_CH29 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    (USB_5856_enum) 32,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_3.Input_CH29 = Readport;
            //            qDebug() << "before" << QString::number(outputs, 16);
            //            qDebug() << "before" << QString::number(Inputs, 16);
            Logger::instance()->logText("Output_5856_Card_3.Output_CH29 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_3.Input_CH29 = %1").arg(Readport));
        }
        Rs422_CH1_CH2_ON_card3_5856();
        break;
    }

#endif
    default:

        checkTimer3_5856->stop();
        g_SelfTestStatus.USB_5856_Card3_STS = 1;
        break;
    }
    //    uint32_t outputs = 0;
    //    uint32_t Inputs = 0;
    //    memcpy(&outputs,&Output_5856_Card_3,sizeof(Output_5856_Card_3));
    //    memcpy(&Inputs,&Input_5856_Card_3,sizeof(Input_5856_Card_3));
    //    qDebug() << "card3outputs"  << QString::number(outputs,16);
    //    qDebug() << "card3Inputs"  << QString::number(Inputs,16);
}

void AdvantechCardsInterface::checkNextChannelCard4_5856()
{
    // static uint8_t currentDOState = DO0;
    static uint32_t Readport = 0;

    uint8_t writePort = 0;
    uint8_t ReadPort = 0;

    uint8_t WriteBitPosition = 0;
    uint8_t ReadBitPosition = 0;
    switch (currentDOState) {
#if 1
    case DO0: {
        Output_5856_Card_4.Output_CH0 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH0 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO1,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH0 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH0 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH0 = %1").arg(Readport));
        }
        //        qDebug() << Readport << currentDOState;
        break;
    }
    case DO1: {
        Output_5856_Card_4.Output_CH1 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 1;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH1 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO2,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH1 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH1 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH1 = %1").arg(Readport));
        }
        break;
    }
    case DO2: {
        Output_5856_Card_4.Output_CH2 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 2;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH2 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO6,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH2 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH2 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH2 = %1").arg(Readport));
        }
        break;
    }

    case DO3: {
        Output_5856_Card_4.Output_CH3 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 3;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH3 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO4,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH3 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH3 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH3 = %1").arg(Readport));
        }
        break;
    }
    case DO4: //latchRelay
    {
        Output_5856_Card_4.Output_CH4 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 4;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH4 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO8,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH3 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH4 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH3 = %1").arg(Readport));
        }
        break;
    }

        //    case DO5: {
        //        Output_5856_Card_4.Output_CH5 = 1;
        //        writePort = 0;
        //        ReadPort = 0;
        //        WriteBitPosition = 5;
        //        ReadBitPosition = 4;
        //        bool result = CheckAndSetDO(instantDoCtrl4,
        //                                    instantDiCtrl4,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_4.Output_CH5 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO7,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_4.Input_CH4 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_4.Output_CH5 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH4 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO6: {
        Output_5856_Card_4.Output_CH6 = 1;
        writePort = 0;
        ReadPort = 0;
        WriteBitPosition = 6;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH6 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO3,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH2 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH6 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH2 = %1").arg(Readport));
        }
        break;
    }

        //    case DO7: {
        //        Output_5856_Card_1.Output_CH7 = 1;
        //        writePort = 0;
        //        ReadPort = 0;
        //        WriteBitPosition = 7;
        //        ReadBitPosition = 5;
        //        bool result = CheckAndSetDO(instantDoCtrl4,
        //                                    instantDiCtrl4,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_4.Output_CH7 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO8,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_4.Input_CH5 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_4.Output_CH7 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH5 = %1").arg(Readport));
        //        }
        //        break;
        //    }

    case DO8: {
        Output_5856_Card_4.Output_CH8 = 1;
        writePort = 1;
        ReadPort = 0;
        WriteBitPosition = 0;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH8 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO9,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH6 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH8 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH6 = %1").arg(Readport));
        }
        break;
    }
    case DO9: {
        Output_5856_Card_4.Output_CH9 = 1;
        writePort = 1;
        ReadPort = 0;
        WriteBitPosition = 1;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH9 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO10,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH7 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH9 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH7 = %1").arg(Readport));
        }
        break;
    }
    case DO10: {
        Output_5856_Card_4.Output_CH10 = 1;
        writePort = 1;
        ReadPort = 0;
        WriteBitPosition = 2;
        ReadBitPosition = 7;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH10 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO18,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH7 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH10 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH7 = %1").arg(Readport));
        }
        break;
    }
    //    case DO11: {
    //        Output_5856_Card_4.Output_CH11 = 1;
    //        writePort = 1;
    //        ReadPort = 1;
    //        WriteBitPosition = 3;
    //        ReadBitPosition = 0;
    //        bool result = CheckAndSetDO(instantDoCtrl4,
    //                                    instantDiCtrl4,
    //                                    writePort,
    //                                    ReadPort,
    //                                    Output_5856_Card_4.Output_CH11 << WriteBitPosition,
    //                                    ReadBitPosition,
    //                                    Readport,
    //                                    DO13,
    //                                    currentDOState,
    //                                    0);
    //        if (result) {
    //            Input_5856_Card_4.Input_CH8 = Readport;
    //            Logger::instance()->logText("Output_5856_Card_4.Output_CH11 = 1");
    //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH8 = %1").arg(Readport));
    //        }
    //        break;
    //    }
    //    case DO12:
    //    {
    //        Output_5856_Card_4.Output_CH12 = 1;
    //        writePort = 1;
    //        ReadPort = 1;
    //        WriteBitPosition = 4;
    //        ReadBitPosition=1;
    //        bool result = CheckAndSetDO(instantDoCtrl4, instantDiCtrl4,writePort, ReadPort, Output_5856_Card_4.Output_CH12<<WriteBitPosition,
    //                                    ReadBitPosition,Readport, DO13, currentDOState,0);
    //        if(result)
    //        {
    //            Input_5856_Card_4.Input_CH9 = Readport;
    //            Logger::instance()->logText("Output_5856_Card_4.Output_CH12 = 1");
    //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH9 = %1").arg(Readport));
    //        }
    //        break;
    //    }
//    case DO13: {
//        Output_5856_Card_4.Output_CH13 = 1;
//        writePort = 1;
//        ReadPort = 1;
//        WriteBitPosition = 5;
//        ReadBitPosition = 2;
//        bool result = CheckAndSetDO(instantDoCtrl4,
//                                    instantDiCtrl4,
//                                    writePort,
//                                    ReadPort,
//                                    Output_5856_Card_4.Output_CH13 << WriteBitPosition,
//                                    ReadBitPosition,
//                                    Readport,
//                                    DO14,
//                                    currentDOState,
//                                    0);
//        if (result) {
//            Input_5856_Card_4.Input_CH10 = Readport;
//            Logger::instance()->logText("Output_5856_Card_4.Output_CH13 = 1");
//            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH10 = %1").arg(Readport));
//        }
//        break;
//    }
//    case DO14: {
//        Output_5856_Card_4.Output_CH14 = 1;
//        writePort = 1;
//        ReadPort = 1;
//        WriteBitPosition = 6;
//        ReadBitPosition = 3;
//        bool result = CheckAndSetDO(instantDoCtrl4,
//                                    instantDiCtrl4,
//                                    writePort,
//                                    ReadPort,
//                                    Output_5856_Card_4.Output_CH14 << WriteBitPosition,
//                                    ReadBitPosition,
//                                    Readport,
//                                    DO18,
//                                    currentDOState,
//                                    0);
//        if (result) {
//            Input_5856_Card_4.Input_CH11 = Readport;
//            Logger::instance()->logText("Output_5856_Card_4.Output_CH014= 1");
//            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH11= %1").arg(Readport));
//        }
//        break;
//    }
//    case DO15:
//    {
//        Output_5856_Card_4.Output_CH15 = 1;
//        writePort = 1;
//        ReadPort = 1;
//        WriteBitPosition = 7;
//        ReadBitPosition=4;
//        bool result = CheckAndSetDO(instantDoCtrl4, instantDiCtrl4,writePort, ReadPort, Output_5856_Card_4.Output_CH15<<WriteBitPosition,
//                                    ReadBitPosition,Readport, DO16, currentDOState,0);
//        if(result)
//        {
//            Input_5856_Card_4.Input_CH12 = Readport;
//            Logger::instance()->logText("Output_5856_Card_4.Output_CH15 = 1");
//            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH12 = %1").arg(Readport));
//        }
//        break;
//    }
#endif
#if 1
        //    case DO16:
        //    {
        //        Output_5856_Card_4.Output_CH16 = 1;
        //        writePort = 2;
        //        ReadPort = 1;
        //        WriteBitPosition = 0;
        //        ReadBitPosition=4;
        //        bool result = CheckAndSetDO(instantDoCtrl4, instantDiCtrl4,writePort, ReadPort, Output_5856_Card_4.Output_CH16<<WriteBitPosition,
        //                                    ReadBitPosition,Readport, DO17, currentDOState,1);
        //        if(result)
        //        {
        //            Input_5856_Card_4.Input_CH12 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_4.Output_CH016= 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH12= %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO17:
        //    {
        //        Output_5856_Card_4.Output_CH17 = 1;
        //        writePort = 2;
        //        ReadPort = 1;
        //        WriteBitPosition = 1;
        //        ReadBitPosition=5;
        //        bool result = CheckAndSetDO(instantDoCtrl4, instantDiCtrl4,writePort, ReadPort, Output_5856_Card_4.Output_CH17<<WriteBitPosition,
        //                                    ReadBitPosition,Readport, DO18, currentDOState,0);
        //        if(result)
        //        {
        //            Input_5856_Card_4.Input_CH13 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_4.Output_CH17= 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH13 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO18: {
        Output_5856_Card_4.Output_CH18 = 1;
        writePort = 2;
        ReadPort = 1;
        WriteBitPosition = 2;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH18 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO19,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH14 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH18= 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH14 = %1").arg(Readport));
        }
        break;
    }
    case DO19: {
        Output_5856_Card_4.Output_CH19 = 1;
        writePort = 2;
        ReadPort = 1;
        WriteBitPosition = 3;
        ReadBitPosition = 6;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH19 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO22,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH14 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH19 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH14 = %1").arg(Readport));
        }
        break;
    }
        //    case DO20: {
        //        Output_5856_Card_4.Output_CH20 = 1;
        //        writePort = 2;
        //        ReadPort = 1;
        //        WriteBitPosition = 4;
        //        ReadBitPosition = 7;
        //        bool result = CheckAndSetDO(instantDoCtrl4,
        //                                    instantDiCtrl4,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_4.Output_CH20 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO22,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_4.Input_CH15 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_4.Output_CH20 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH15 = %1").arg(Readport));
        //        }
        //        break;
        //    }
        //    case DO21:
        //    {
        //        Output_5856_Card_4.Output_CH21 = 1;
        //        writePort = 2;
        //        ReadPort = 2;
        //        WriteBitPosition = 5;
        //        ReadBitPosition=0;
        //        bool result = CheckAndSetDO(instantDoCtrl4, instantDiCtrl4,writePort, ReadPort, Output_5856_Card_4.Output_CH21<<WriteBitPosition,
        //                                    ReadBitPosition,Readport, DO22, currentDOState,0);
        //        if(result)
        //        {
        //            Input_5856_Card_4.Input_CH16 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_4.Output_CH21 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH16 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO22: {
        Output_5856_Card_4.Output_CH22 = 1;
        writePort = 2;
        ReadPort = 2;
        WriteBitPosition = 6;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH22 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO24,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH17 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH22= 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH17 = %1").arg(Readport));
        }
        break;
    }

        //    case DO23: {
        //        Output_5856_Card_4.Output_CH23 = 1;
        //        writePort = 2;
        //        ReadPort = 2;
        //        WriteBitPosition = 7;
        //        ReadBitPosition = 2;
        //        bool result = CheckAndSetDO(instantDoCtrl4,
        //                                    instantDiCtrl4,
        //                                    writePort,
        //                                    ReadPort,
        //                                    Output_5856_Card_4.Output_CH23 << WriteBitPosition,
        //                                    ReadBitPosition,
        //                                    Readport,
        //                                    DO24,
        //                                    currentDOState,
        //                                    0);
        //        if (result) {
        //            Input_5856_Card_4.Input_CH18 = Readport;
        //            Logger::instance()->logText("Output_5856_Card_4.Output_CH23 = 1");
        //            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH18 = %1").arg(Readport));
        //        }
        //        break;
        //    }
    case DO24: {
        Output_5856_Card_4.Output_CH24 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 0;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH24 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO25,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH24 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH24 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH24 = %1").arg(Readport));
        }
        break;
    }
#endif
#if 1
    case DO25: {
        Output_5856_Card_4.Output_CH25 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 1;
        ReadBitPosition = 0;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH25 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO26,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH24 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH25= 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH24= %1").arg(Readport));
        }
        break;
    }
    case DO26: {
        Output_5856_Card_4.Output_CH26 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 2;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH26 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO27,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH25 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH26= 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH26 = %1").arg(Readport));
        }
        break;
    }
    case DO27: {
        Output_5856_Card_4.Output_CH27 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 3;
        ReadBitPosition = 1;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH27 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO28,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH25 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH27= 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH25 = %1").arg(Readport));
        }
        break;
    }
    case DO28: {
        Output_5856_Card_4.Output_CH28 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 4;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH28 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO29,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH26 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH28 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH26 = %1").arg(Readport));
        }
        break;
    }
    case DO29: {
        Output_5856_Card_4.Output_CH29 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 5;
        ReadBitPosition = 2;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH29 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO30,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH26 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH29 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH26= %1").arg(Readport));
        }
        break;
    }
    case DO30: {
        Output_5856_Card_4.Output_CH30 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 6;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH29 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    DO31,
                                    currentDOState,
                                    0);
        if (result) {
            Input_5856_Card_4.Input_CH27 = Readport;
            Logger::instance()->logText("Output_5856_Card_4.Output_CH30 = 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH27 = %1").arg(Readport));
        }
        break;
    }
    case DO31: {
        Output_5856_Card_4.Output_CH31 = 1;
        writePort = 3;
        ReadPort = 3;
        WriteBitPosition = 7;
        ReadBitPosition = 3;
        bool result = CheckAndSetDO(instantDoCtrl4,
                                    instantDiCtrl4,
                                    writePort,
                                    ReadPort,
                                    Output_5856_Card_4.Output_CH29 << WriteBitPosition,
                                    ReadBitPosition,
                                    Readport,
                                    (USB_5856_enum) 32,
                                    currentDOState,
                                    1);
        if (result) {
            Input_5856_Card_4.Input_CH27 = Readport;
            //            qDebug() << "Card4-before" << QString::number(outputs, 16);
            //            qDebug() << "Card4-before" << QString::number(Inputs, 16);
            Logger::instance()->logText("Output_5856_Card_4.Output_CH31= 1");
            Logger::instance()->logText(QString("Input_5856_Card_4.Input_CH27= %1").arg(Readport));
        }
        break;
    }

#endif
    default:

        checkTimer4_5856->stop();
        g_SelfTestStatus.USB_5856_Card4_STS = 1;
        break;
    }
    //    uint32_t outputs = 0;
    //    uint32_t Inputs = 0;
    //    memcpy(&outputs,&Output_5856_Card_4,sizeof(Output_5856_Card_4));
    //    memcpy(&Inputs,&Input_5856_Card_4,sizeof(Input_5856_Card_4));
    //    qDebug() << "card4outputs"  << QString::number(outputs,16);
    //    qDebug() << "card4Inputs"  << QString::number(Inputs,16);
}
///////////-------------------SRU SECTION DISPLAY FUNCTION -----------//////////

void AdvantechCardsInterface::USB_4716_DisplayC1(bool value)
{
    if (value == true) {
        instantDoCtrl1_ADC->WriteBit(0, 0, 1);
        QThread::msleep(DELAY);
    } else {
        instantDoCtrl1_ADC->WriteBit(0, 0, 0);
        QThread::msleep(DELAY);
    }
}

void AdvantechCardsInterface::USB_4716_DisplayC2(bool value)
{
    if (value == true) {
        instantDoCtrl1_ADC->WriteBit(0, 5, 1);
        QThread::msleep(DELAY);
    } else {
        instantDoCtrl1_ADC->WriteBit(0, 5, 0);
        QThread::msleep(DELAY);
    }
}

void AdvantechCardsInterface::USB_4716_DisplayC3(bool value)
{
    if (value == true) {
        instantDoCtrl1_ADC->WriteBit(0, 6, 1);
        QThread::msleep(DELAY);
    } else {
        instantDoCtrl1_ADC->WriteBit(0, 6, 0);
        QThread::msleep(DELAY);
    }
}

void AdvantechCardsInterface::USB_4716_DisplayCTRL_8421(uint16_t value)
{
    //    qDebug() << "in USB_4716_DisplayCTRL_8421" << QString::number(value);
    //    instantDoCtrl1_ADC->WriteBit(0, 1, 1);
    //    instantDoCtrl1_ADC->WriteBit(0, 2, 0);
    //    instantDoCtrl1_ADC->WriteBit(0, 3, 0);
    //    instantDoCtrl1_ADC->WriteBit(0, 4, 0);
    switch (value) {
    case 8: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 9: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 10: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 11: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 12: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 13: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 14: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 15: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 0);
        //        QThread::msleep(DELAY);
        break;
    }
    case 0: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    case 1: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    case 2: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    case 3: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 0);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    case 4: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    case 5: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 0);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    case 6: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 0);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    case 7: {
        instantDoCtrl1_ADC->WriteBit(0, 1, 1);
        instantDoCtrl1_ADC->WriteBit(0, 2, 1);
        instantDoCtrl1_ADC->WriteBit(0, 3, 1);
        instantDoCtrl1_ADC->WriteBit(0, 4, 1);
        //        QThread::msleep(DELAY);
        break;
    }
    default: {
        break;
    }
    }
}

////////////-----------------------------SRU SECTION  DCDC   ------------------///////////////

void AdvantechCardsInterface::SRU_MUX_28V()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_1.Output_CH0 = 0;
    instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH1 << 0)); // write to DO bit 0
    QThread::msleep(DELAY);
    // Wait
    Input_5856_Card_1.Input_CH0 = portData;
    instantDiCtrl1->ReadBit(0, 0, &portData);
    //    qDebug() << "!!!!!DO CH0:" << Output_5856_Card_1.Output_CH0
    //             << ", DI CH0:" << static_cast<int>(Input_5856_Card_1.Input_CH0);

    Output_5856_Card_1.Output_CH5 = 1;
    instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH5 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH4 = portData;
    instantDiCtrl1->ReadBit(0, 4, &portData);
    //    qDebug() << "DO CH5:" << Output_5856_Card_1.Output_CH5
    //             << ", DI CH4:" << static_cast<int>(Input_5856_Card_1.Input_CH4);

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(2, 0, &portData);

    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    ////////------step 5  Disable voltage to DMM --------------///////
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH26 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    ////////------step 6  Disable voltage to mux DMM --------------///////
    Output_5856_Card_1.Output_CH5 = 0;
    instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH5 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH4 = portData;
    instantDiCtrl1->ReadBit(0, 4, &portData);
    //    qDebug() << "DO CH5:" << Output_5856_Card_1.Output_CH5
    //             << ", DI CH4:" << static_cast<int>(Input_5856_Card_1.Input_CH4);
}

void AdvantechCardsInterface::Check_Highest_Resistance()
{
    //    int maxSet = 0;
    double r1 = Differential_mode_resistance_SET1();
    double r2 = Differential_mode_resistance_SET2();
    double r3 = Differential_mode_resistance_SET3();
    double r4 = Differential_mode_resistance_SET4();

    double maxRes = r1;
    //    maxSet = 1;

    if (r2 > maxRes) {
        maxRes = r2;
        //        maxSet = 2;
    }
    if (r3 > maxRes) {
        maxRes = r3;
        //        maxSet = 3;
    }
    if (r4 > maxRes) {
        maxRes = r4;
        //        maxSet = 4;
    }

    //    qDebug() << "Highest resistance is from SET" << maxSet << ":" << maxRes << "Ohms";

    // Optional: send to next function
    // Process_High_Resistance(maxSet, maxRes);
}

double AdvantechCardsInterface::Differential_mode_resistance_SET1()
{
    Automation::BDaq::uint8 portData = 0;

    ////////// Differential mode read resistance//////////
    ////-------- set 1 On Scan collect Data and Off-----------////

    Output_5856_Card_1.Output_CH25 = 1;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH25 << 1)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH18 = portData;
    instantDiCtrl1->ReadBit(2, 2, &portData);
    //    qDebug() << "DO CH25:" << Output_5856_Card_1.Output_CH25
    //             << ", DI CH18:" << static_cast<int>(Input_5856_Card_1.Input_CH18);

    Output_5856_Card_1.Output_CH31 = 1;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH31 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH24 = portData;
    instantDiCtrl1->ReadBit(3, 0, &portData);
    //    qDebug() << "DO CH31:" << Output_5856_Card_1.Output_CH31
    //             << ", DI CH24:" << static_cast<int>(Input_5856_Card_1.Input_CH24);
    //need to call ADC differential function and read the two channels data

    double values[2] = {0};
    double resistance = 100000.0;
    read4716_Differential_CH0_CH1(values);

    //    qDebug() << "Differntial...........................";

    Output_5856_Card_1.Output_CH25 = 0;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH25 << 1)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH18 = portData;
    instantDiCtrl1->ReadBit(2, 2, &portData);
    //    qDebug() << "DO CH25:" << Output_5856_Card_1.Output_CH25
    //             << ", DI CH18:" << static_cast<int>(Input_5856_Card_1.Input_CH18);

    Output_5856_Card_1.Output_CH31 = 0;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH31 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH24 = portData;
    instantDiCtrl1->ReadBit(3, 0, &portData);
    //    qDebug() << "DO CH31:" << Output_5856_Card_1.Output_CH31
    //             << ", DI CH24:" << static_cast<int>(Input_5856_Card_1.Input_CH24);
    return resistance;
}
double AdvantechCardsInterface::Differential_mode_resistance_SET2()
{
    ////-------- set 2 On Scan collect Data and Off-----------////
    Automation::BDaq::uint8 portData = 0;
    Output_5856_Card_1.Output_CH23 = 1;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH23 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH16 = portData;
    instantDiCtrl1->ReadBit(2, 0, &portData);
    //    qDebug() << "DO CH23:" << Output_5856_Card_1.Output_CH23
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_1.Input_CH16);

    Output_5856_Card_1.Output_CH22 = 1;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH22 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH15 = portData;
    instantDiCtrl1->ReadBit(1, 7, &portData);
    //    qDebug() << "DO CH22:" << Output_5856_Card_1.Output_CH22
    //             << ", DI CH15:" << static_cast<int>(Input_5856_Card_1.Input_CH15);

    double values[2] = {0};
    double resistance = 200000.0;
    //    qDebug() << "Before ADC read in SET2";
    read4716_Differential_CH0_CH1(values);
    //    qDebug() << "After ADC read in SET2";

    //    qDebug() << "Differntial...........................";
    Output_5856_Card_1.Output_CH23 = 0;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH23 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH16 = portData;
    instantDiCtrl1->ReadBit(2, 0, &portData);
    //    qDebug() << "DO CH23:" << Output_5856_Card_1.Output_CH23
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_1.Input_CH16);

    Output_5856_Card_1.Output_CH22 = 0;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH22 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH15 = portData;
    instantDiCtrl1->ReadBit(1, 7, &portData);
    //    qDebug() << "DO CH22:" << Output_5856_Card_1.Output_CH22
    //             << ", DI CH15:" << static_cast<int>(Input_5856_Card_1.Input_CH15);

    return resistance;
}
double AdvantechCardsInterface::Differential_mode_resistance_SET3()
{
    ////-------- set 3 On Scan collect Data and Off-----------////
    Automation::BDaq::uint8 portData = 0;
    Output_5856_Card_1.Output_CH27 = 1;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH27 << 3)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH20 = portData;
    instantDiCtrl1->ReadBit(2, 4, &portData);
    //    qDebug() << "DO CH27:" << Output_5856_Card_1.Output_CH27
    //             << ", DI CH20:" << static_cast<int>(Input_5856_Card_1.Input_CH20);
    //    qDebug() << "Differntial...........................";
    Output_5856_Card_1.Output_CH28 = 1;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH28 << 4)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH21 = portData;
    instantDiCtrl1->ReadBit(2, 5, &portData);
    //    qDebug() << "DO CH28:" << Output_5856_Card_1.Output_CH28
    //             << ", DI CH21:" << static_cast<int>(Input_5856_Card_1.Input_CH21);

    double values[2] = {0};
    double resistance = 1000.0;
    //    qDebug() << "Before ADC read in SET3";
    read4716_Differential_CH0_CH1(values);
    //    qDebug() << "After ADC read in SET3";

    Output_5856_Card_1.Output_CH27 = 0;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH27 << 3)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH20 = portData;
    instantDiCtrl1->ReadBit(2, 4, &portData);
    //    qDebug() << "DO CH27:" << Output_5856_Card_1.Output_CH27
    //             << ", DI CH20:" << static_cast<int>(Input_5856_Card_1.Input_CH20);

    Output_5856_Card_1.Output_CH28 = 0;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH28 << 4)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH21 = portData;
    instantDiCtrl1->ReadBit(2, 5, &portData);
    //    qDebug() << "DO CH28:" << Output_5856_Card_1.Output_CH28
    //             << ", DI CH21:" << static_cast<int>(Input_5856_Card_1.Input_CH21);
    return resistance;
}

double AdvantechCardsInterface::Differential_mode_resistance_SET4()
{
    Automation::BDaq::uint8 portData = 0;
    Output_5856_Card_1.Output_CH29 = 1;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH29 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH22 = portData;
    instantDiCtrl1->ReadBit(3, 6, &portData);
    //    qDebug() << "DO CH29:" << Output_5856_Card_1.Output_CH29
    //             << ", DI CH22:" << static_cast<int>(Input_5856_Card_1.Input_CH22);

    Output_5856_Card_1.Output_CH26 = 1;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH26 << 2)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH19 = portData;
    instantDiCtrl1->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH26:" << Output_5856_Card_1.Output_CH26
    //             << ", DI CH19:" << static_cast<int>(Input_5856_Card_1.Input_CH19);

    double values[2] = {0};
    double resistance = 50000.0;
    //    qDebug() << "Before ADC read in SET4";

    read4716_Differential_CH0_CH1(values);
    //    qDebug() << "After ADC read in SET4";

    Output_5856_Card_1.Output_CH29 = 0;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH29 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH22 = portData;
    instantDiCtrl1->ReadBit(3, 6, &portData);
    //    qDebug() << "DO CH29:" << Output_5856_Card_1.Output_CH29
    //             << ", DI CH22:" << static_cast<int>(Input_5856_Card_1.Input_CH22);

    Output_5856_Card_1.Output_CH26 = 0;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH26 << 2)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH19 = portData;
    instantDiCtrl1->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH26:" << Output_5856_Card_1.Output_CH26
    //             << ", DI CH19:" << static_cast<int>(Input_5856_Card_1.Input_CH19);

    return resistance;
}

void AdvantechCardsInterface::SRU_MUX_3_3V()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_4.Output_CH5 = 1;
    instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH5 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_4.Input_CH4 = portData;
    instantDiCtrl4->ReadBit(0, 4, &portData);
    //    qDebug() << "!!!!!DO CH5:" << Output_5856_Card_4.Output_CH5
    //             << ", DI CH4:" << static_cast<int>(Input_5856_Card_4.Input_CH4);

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(2, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);
    Check_Highest_Resistance();
    ////////------step 5  Disable voltage to DMM --------------///////
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH26 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    ////////------step 6  Disable voltage to mux DMM --------------///////
    Output_5856_Card_4.Output_CH5 = 0;
    instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH5 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_4.Input_CH4 = portData;
    instantDiCtrl4->ReadBit(0, 4, &portData);
    //    qDebug() << "DO CH5:" << Output_5856_Card_4.Output_CH5
    //             << ", DI CH4:" << static_cast<int>(Input_5856_Card_4.Input_CH4);
}

void AdvantechCardsInterface::SRU_MUX_plus_5V()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_4.Output_CH7 = 1;
    instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH7 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_4.Input_CH5 = portData;
    instantDiCtrl4->ReadBit(0, 5, &portData);
    //    qDebug() << "DO CH7:" << Output_5856_Card_4.Output_CH7
    //             << ", DI CH5:" << static_cast<int>(Input_5856_Card_4.Input_CH5);

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(2, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    ////////------step 5  Disable voltage to DMM --------------///////
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH26 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Output_5856_Card_4.Output_CH7 = 0;
    instantDoCtrl4->Write(0, (Output_5856_Card_4.Output_CH7 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_4.Input_CH5 = portData;
    instantDiCtrl4->ReadBit(0, 5, &portData);
    //    qDebug() << "DO CH7:" << Output_5856_Card_4.Output_CH7
    //             << ", DI CH5:" << static_cast<int>(Input_5856_Card_4.Input_CH5);
}
void AdvantechCardsInterface::SRU_MUX_minus_5V()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_4.Output_CH11 = 1;
    instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH11 << 3)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH8 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH11:" << Output_5856_Card_4.Output_CH11
    //             << ", DI CH8:" << static_cast<int>(Input_5856_Card_4.Input_CH8);

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(2, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    ////////------step 5  Disable voltage to DMM --------------///////
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Output_5856_Card_4.Output_CH11 = 0;
    instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH11 << 3)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH8 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "!DO CH11:" << Output_5856_Card_4.Output_CH11
    //             << ", DI CH8:" << static_cast<int>(Input_5856_Card_4.Input_CH8);
}
/////////////////////////////----------- DMM OUTPUTS SRU -------------------------------//////////////////////////
void AdvantechCardsInterface::SRU_MUX_plus_5V_Output()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_1.Output_CH11 = 1;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH11 << 3)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH8 = portData;
    instantDiCtrl1->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH11:" << Output_5856_Card_1.Output_CH11
    //             << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);

    Output_5856_Card_1.Output_CH11 = 0;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH11 << 3)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH8 = portData;
    instantDiCtrl1->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH11:" << Output_5856_Card_1.Output_CH11
    //             << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);

    Output_5856_Card_1.Output_CH13 = 1;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH11 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH9 = portData;
    instantDiCtrl1->ReadBit(1, 1, &portData);
    //    qDebug() << "DO CH13:" << Output_5856_Card_1.Output_CH13
    //             << ", DI CH9:" << static_cast<int>(Input_5856_Card_1.Input_CH9);

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(2, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    ////////------step 5  Disable voltage to DMM --------------///////
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH26 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    ////// step 6 DC DC ///////
    Output_5856_Card_1.Output_CH12 = 1;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH12 << 4)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH8 = portData;
    instantDiCtrl1->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH12:" << Output_5856_Card_1.Output_CH12
    //             << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);

    Output_5856_Card_1.Output_CH12 = 0;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH12 << 4)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH8 = portData;
    instantDiCtrl1->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH12:" << Output_5856_Card_1.Output_CH12
    //             << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);

    Output_5856_Card_1.Output_CH13 = 0;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH12 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH9 = portData;
    instantDiCtrl1->ReadBit(1, 1, &portData);
    //    qDebug() << "DO CH13:" << Output_5856_Card_1.Output_CH13
    //             << ", DI CH9:" << static_cast<int>(Input_5856_Card_1.Input_CH9);
}

void AdvantechCardsInterface::SRU_MUX_minus_5V_Output()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_1.Output_CH16 = 1;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH16 << 0)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH11 = portData;
    instantDiCtrl1->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH16:" << Output_5856_Card_1.Output_CH16
    //             << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH11);

    Output_5856_Card_1.Output_CH16 = 0;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH16 << 0)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH11 = portData;
    instantDiCtrl1->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH16:" << Output_5856_Card_1.Output_CH16
    //             << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH11);

    Output_5856_Card_1.Output_CH18 = 1;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH18 << 2)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH12 = portData;
    instantDiCtrl1->ReadBit(1, 4, &portData);
    //    qDebug() << "DO CH18:" << Output_5856_Card_1.Output_CH18
    //             << ", DI CH12:" << static_cast<int>(Input_5856_Card_1.Input_CH12);

    ////// step 2/////

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    /////////step 5 //////

    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    /////// step 6//////
    Output_5856_Card_1.Output_CH17 = 1;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH17 << 1)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH11 = portData;
    instantDiCtrl1->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH17:" << Output_5856_Card_1.Output_CH17
    //             << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH11);

    Output_5856_Card_1.Output_CH17 = 0;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH17 << 1)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH11 = portData;
    instantDiCtrl1->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH17:" << Output_5856_Card_1.Output_CH17
    //             << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH11);
    Output_5856_Card_1.Output_CH18 = 0;
    instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH18 << 2)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH12 = portData;
    instantDiCtrl1->ReadBit(1, 4, &portData);
    //    qDebug() << "DO CH18:" << Output_5856_Card_1.Output_CH18
    //             << ", DI CH12:" << static_cast<int>(Input_5856_Card_1.Input_CH12);
}
void AdvantechCardsInterface::SRU_MUX_3_3V_Output()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_1.Output_CH6 = 1;
    instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH6 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH5 = portData;
    instantDiCtrl1->ReadBit(1, 5, &portData);
    //    qDebug() << "DO CH6:" << Output_5856_Card_1.Output_CH6
    //             << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);

    Output_5856_Card_1.Output_CH6 = 0;
    instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH6 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH5 = portData;
    instantDiCtrl1->ReadBit(1, 5, &portData);
    //    qDebug() << "DO CH6:" << Output_5856_Card_1.Output_CH6
    //             << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);
    Output_5856_Card_1.Output_CH8 = 1;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH8 << 0)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH6 = portData;
    instantDiCtrl1->ReadBit(0, 6, &portData);
    //    qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH8
    //             << ", DI CH6:" << static_cast<int>(Input_5856_Card_1.Input_CH6);

    ////// step 2/////////

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    ///// step 5 /////
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    /////// step 6//////
    Output_5856_Card_1.Output_CH7 = 1;
    instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH7 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH5 = portData;
    instantDiCtrl1->ReadBit(1, 5, &portData);
    //    qDebug() << "DO CH7:" << Output_5856_Card_1.Output_CH7
    //             << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);

    Output_5856_Card_1.Output_CH7 = 0;
    instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH7 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH5 = portData;
    instantDiCtrl1->ReadBit(1, 5, &portData);
    //    qDebug() << "DO CH7:" << Output_5856_Card_1.Output_CH7
    //             << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);

    Output_5856_Card_1.Output_CH8 = 0;
    instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH8 << 0)); // write to DO bit 0
    QThread::msleep(DELAY);                                         // Wait
    Input_5856_Card_1.Input_CH6 = portData;
    instantDiCtrl1->ReadBit(0, 6, &portData);
    //    qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH8
    //             << ", DI CH6:" << static_cast<int>(Input_5856_Card_1.Input_CH6);
}

void AdvantechCardsInterface::SRU_CNTRLC_3_3_Output()
{
    Automation::BDaq::uint8 portData = 0;

    Output_5856_Card_1.Output_CH30 = 1;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH30 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH23 = portData;
    instantDiCtrl1->ReadBit(2, 7, &portData);
    //    qDebug() << "DO CH30:" << Output_5856_Card_1.Output_CH30
    //             << ", DI CH23:" << static_cast<int>(Input_5856_Card_1.Input_CH23);

    ////// step 2/////////

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    ///// step 5 /////
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Output_5856_Card_1.Output_CH30 = 0;
    instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH30 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_1.Input_CH23 = portData;
    instantDiCtrl1->ReadBit(2, 7, &portData);
    //    qDebug() << "DO CH30:" << Output_5856_Card_1.Output_CH30
    //             << ", DI CH23:" << static_cast<int>(Input_5856_Card_1.Input_CH23);
}

void AdvantechCardsInterface::SRU_CNTRLC_MINUS_4_6_Output()
{
    Automation::BDaq::uint8 portData = 0;
    Output_5856_Card_4.Output_CH13 = 1;
    instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH13 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH10 = portData;
    instantDiCtrl4->ReadBit(1, 2, &portData);
    //    qDebug() << "DO CH13:" << Output_5856_Card_4.Output_CH13
    //             << ", DI CH10:" << static_cast<int>(Input_5856_Card_4.Input_CH10);
    ////// step 2/////////

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Output_5856_Card_4.Output_CH13 = 0;
    instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH13 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH10 = portData;
    instantDiCtrl4->ReadBit(1, 2, &portData);
    //    qDebug() << "DO CH13:" << Output_5856_Card_4.Output_CH13
    //             << ", DI CH10:" << static_cast<int>(Input_5856_Card_4.Input_CH10);
}
void AdvantechCardsInterface::SRU_CNTRLC_PLUS_4_6_Output()
{
    Automation::BDaq::uint8 portData = 0;
    Output_5856_Card_4.Output_CH14 = 1;
    instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH13 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH11 = portData;
    instantDiCtrl4->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH14:" << Output_5856_Card_4.Output_CH14
    //             << ", DI CH11:" << static_cast<int>(Input_5856_Card_4.Input_CH11);
    ////// step 2/////////

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Output_5856_Card_4.Output_CH14 = 0;
    instantDoCtrl4->Write(1, (Output_5856_Card_4.Output_CH13 << 6)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH11 = portData;
    instantDiCtrl4->ReadBit(1, 3, &portData);
    //    qDebug() << "DO CH14:" << Output_5856_Card_4.Output_CH14
    //             << ", DI CH11:" << static_cast<int>(Input_5856_Card_4.Input_CH11);
    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);
}

void AdvantechCardsInterface::LRU_INPUT()
{
    Automation::BDaq::uint8 portData = 0;
    Output_5856_Card_4.Output_CH23 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH13 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH18 = portData;
    instantDiCtrl4->ReadBit(2, 2, &portData);
    //    qDebug() << "DO CH23:" << Output_5856_Card_4.Output_CH23
    //             << ", DI CH18:" << static_cast<int>(Input_5856_Card_4.Input_CH18);
    ////// step 2/////////

    Output_5856_Card_4.Output_CH21 = 1;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Check_Highest_Resistance();

    Output_5856_Card_4.Output_CH21 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH21 << 5)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH16 = portData;
    instantDiCtrl4->ReadBit(1, 0, &portData);
    //    qDebug() << "DO CH21:" << Output_5856_Card_4.Output_CH21
    //             << ", DI CH16:" << static_cast<int>(Input_5856_Card_4.Input_CH16);

    Output_5856_Card_4.Output_CH23 = 0;
    instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH13 << 7)); // write to DO bit 0
    QThread::msleep(DELAY);                                          // Wait
    Input_5856_Card_4.Input_CH18 = portData;
    instantDiCtrl4->ReadBit(2, 2, &portData);
    //    qDebug() << "DO CH23:" << Output_5856_Card_4.Output_CH23
    //             << ", DI CH18:" << static_cast<int>(Input_5856_Card_4.Input_CH18);
}
//-------------------------------DC-DC-CARD------------------------------------------------------//

void AdvantechCardsInterface::DC_CARD_5V_InitialValues_LED_Ripple(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_1.Output_CH11 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH11 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH8 = portData;
        instantDiCtrl1->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH11:" << Output_5856_Card_1.Output_CH11
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);

        Output_5856_Card_1.Output_CH11 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH11 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH8 = portData;
        instantDiCtrl1->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH11:" << Output_5856_Card_1.Output_CH11
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);
        //----------------------Oscilloscope----------------------------//
        Output_5856_Card_1.Output_CH13 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH13 << 5)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH9 = portData;
        instantDiCtrl1->ReadBit(1, 5, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH13
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH9);

        Output_5856_Card_2.Output_CH8 = 1;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_2.Input_CH8 = portData;
        instantDiCtrl2->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_2.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_2.Input_CH8);
    } else {
        Output_5856_Card_1.Output_CH12 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH12 << 4)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH8 = portData;
        instantDiCtrl1->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH12:" << Output_5856_Card_1.Output_CH12
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);

        Output_5856_Card_1.Output_CH12 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH12 << 4)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH8 = portData;
        instantDiCtrl1->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH12:" << Output_5856_Card_1.Output_CH12
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH8);

        //----------------------Oscilloscope--------------------------------//

        Output_5856_Card_1.Output_CH13 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH13 << 5)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH9 = portData;
        instantDiCtrl1->ReadBit(1, 5, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH13
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH9);

        Output_5856_Card_2.Output_CH8 = 0;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_2.Input_CH8 = portData;
        instantDiCtrl2->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_2.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_2.Input_CH8);
    }
}
void AdvantechCardsInterface::DC_CARD_5V_LOAD_MEASUREMENT_10_percent(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_1.Output_CH14 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH14 << 6)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH10 = portData;
        instantDiCtrl1->ReadBit(1, 2, &portData);
        //        qDebug() << "DO CH14:" << Output_5856_Card_1.Output_CH14
        //                 << ", DI CH10:" << static_cast<int>(Input_5856_Card_1.Input_CH10);
        Output_5856_Card_1.Output_CH14 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH14 << 6)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH10 = portData;
        instantDiCtrl1->ReadBit(1, 2, &portData);
        //        qDebug() << "DO CH14:" << Output_5856_Card_1.Output_CH14
        //                 << ", DI CH10:" << static_cast<int>(Input_5856_Card_1.Input_CH10);
    } else {
        //        qDebug() << " wait for load test complete...........";
        Output_5856_Card_1.Output_CH15 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH15 << 7)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH10 = portData;
        instantDiCtrl1->ReadBit(1, 2, &portData);
        //        qDebug() << "DO CH15:" << Output_5856_Card_1.Output_CH15
        //                 << ", DI CH10:" << static_cast<int>(Input_5856_Card_1.Input_CH10);

        Output_5856_Card_1.Output_CH15 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH15 << 7)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH10 = portData;
        instantDiCtrl1->ReadBit(1, 2, &portData);
        //        qDebug() << "DO CH15:" << Output_5856_Card_1.Output_CH15
        //                 << ", DI CH10:" << static_cast<int>(Input_5856_Card_1.Input_CH10);
    }
}
void AdvantechCardsInterface::DC_CARD_5V_LOAD_MEASUREMENT_100_percent(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_4.Output_CH18 = 1;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH18 << 2)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_4.Input_CH14 = portData;
        instantDiCtrl4->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH18:" << Output_5856_Card_4.Output_CH18
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_4.Input_CH14);

        Output_5856_Card_4.Output_CH18 = 0;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH18 << 2)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_4.Input_CH14 = portData;
        instantDiCtrl4->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH18:" << Output_5856_Card_4.Output_CH18
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_4.Input_CH14);
    } else {
        //        qDebug() << " wait for load test complete...........";
        Output_5856_Card_4.Output_CH19 = 1;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH19 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_4.Input_CH14 = portData;
        instantDiCtrl4->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH19:" << Output_5856_Card_4.Output_CH19
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_4.Input_CH14);

        Output_5856_Card_4.Output_CH19 = 0;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH19 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_4.Input_CH14 = portData;
        instantDiCtrl4->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH19:" << Output_5856_Card_4.Output_CH19
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_4.Input_CH14);
    }
}

void AdvantechCardsInterface::DC_CARD_MINUS_5V_InitialValues_LED_Ripple(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_1.Output_CH16 = 1;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH16 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH11 = portData;
        instantDiCtrl1->ReadBit(1, 3, &portData);
        //        qDebug() << "DO CH16:" << Output_5856_Card_1.Output_CH16
        //                 << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH11);

        Output_5856_Card_1.Output_CH16 = 0;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH16 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH11 = portData;
        instantDiCtrl1->ReadBit(1, 3, &portData);
        //        qDebug() << "DO CH16:" << Output_5856_Card_1.Output_CH16
        //                 << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH11);
        //----------------------Oscilloscope----------------------------//

        Output_5856_Card_1.Output_CH18 = 1;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH18 << 2)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH12 = portData;
        instantDiCtrl1->ReadBit(1, 4, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH18
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH12);

        Output_5856_Card_2.Output_CH8 = 1;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_2.Input_CH8 = portData;
        instantDiCtrl2->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_2.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_2.Input_CH8);

    } else {
        Output_5856_Card_1.Output_CH17 = 1;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH17 << 1)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH11 = portData;
        instantDiCtrl1->ReadBit(1, 3, &portData);
        //        qDebug() << "DO CH17:" << Output_5856_Card_1.Output_CH17
        //                 << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH13);

        Output_5856_Card_1.Output_CH17 = 0;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH17 << 1)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH11 = portData;
        instantDiCtrl1->ReadBit(1, 3, &portData);
        //        qDebug() << "DO CH17:" << Output_5856_Card_1.Output_CH17
        //                 << ", DI CH11:" << static_cast<int>(Input_5856_Card_1.Input_CH13);

        //----------------------Oscilloscope--------------------------------//

        Output_5856_Card_1.Output_CH18 = 0;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH18 << 2)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH12 = portData;
        instantDiCtrl1->ReadBit(1, 4, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH18
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH12);

        Output_5856_Card_2.Output_CH8 = 0;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_2.Input_CH8 = portData;
        instantDiCtrl2->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_2.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_2.Input_CH8);
    }
}
void AdvantechCardsInterface::DC_CARD_MINUS_5V_LOAD_MEASUREMENT_10_percent(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_1.Output_CH19 = 1;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH19 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH13 = portData;
        instantDiCtrl1->ReadBit(1, 5, &portData);
        //        qDebug() << "DO CH19:" << Output_5856_Card_1.Output_CH19
        //                 << ", DI CH13:" << static_cast<int>(Input_5856_Card_1.Input_CH13);

        Output_5856_Card_1.Output_CH19 = 0;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH19 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH13 = portData;
        instantDiCtrl1->ReadBit(1, 5, &portData);
        //        qDebug() << "DO CH19:" << Output_5856_Card_1.Output_CH19
        //                 << ", DI CH13:" << static_cast<int>(Input_5856_Card_1.Input_CH13);

        //        qDebug() << " wait for load test complete...........";
    } else {
        Output_5856_Card_1.Output_CH20 = 1;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH20 << 4)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH13 = portData;
        instantDiCtrl1->ReadBit(1, 5, &portData);
        //        qDebug() << "DO CH20:" << Output_5856_Card_1.Output_CH20
        //                 << ", DI CH13:" << static_cast<int>(Input_5856_Card_1.Input_CH13);

        Output_5856_Card_1.Output_CH20 = 0;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH20 << 4)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH13 = portData;
        instantDiCtrl1->ReadBit(1, 5, &portData);
        //        qDebug() << "DO CH20:" << Output_5856_Card_1.Output_CH20
        //                 << ", DI CH13:" << static_cast<int>(Input_5856_Card_1.Input_CH13);
    }
}

void AdvantechCardsInterface::DC_CARD_MINUS_5V_LOAD_MEASUREMENT_100_percent(bool checked)
{
    Automation::BDaq::uint8 portData = 0;

    if (checked) {
        Output_5856_Card_1.Output_CH21 = 1;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH21 << 5)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH14 = portData;
        instantDiCtrl1->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH21:" << Output_5856_Card_1.Output_CH21
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_1.Input_CH14);

        Output_5856_Card_1.Output_CH21 = 0;
        instantDoCtrl1->Write(2, (Output_5856_Card_1.Output_CH21 << 5)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH14 = portData;
        instantDiCtrl1->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH21:" << Output_5856_Card_1.Output_CH21
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_1.Input_CH14);

        //        qDebug() << " wait for load test complete...........";
    } else {
        Output_5856_Card_1.Output_CH24 = 1;
        instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH24 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH14 = portData;
        instantDiCtrl1->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH24:" << Output_5856_Card_1.Output_CH24
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_1.Input_CH14);

        Output_5856_Card_1.Output_CH24 = 0;
        instantDoCtrl1->Write(3, (Output_5856_Card_1.Output_CH24 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH14 = portData;
        instantDiCtrl1->ReadBit(1, 6, &portData);
        //        qDebug() << "DO CH24:" << Output_5856_Card_1.Output_CH24
        //                 << ", DI CH14:" << static_cast<int>(Input_5856_Card_1.Input_CH14);
    }
}

void AdvantechCardsInterface::DC_CARD_3_3V_InitialValues_LED_Ripple(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_1.Output_CH6 = 1;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH6 << 6)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH5 = portData;
        instantDiCtrl1->ReadBit(0, 5, &portData);
        //        qDebug() << "DO CH6:" << Output_5856_Card_1.Output_CH6
        //                 << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);

        Output_5856_Card_1.Output_CH6 = 0;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH6 << 6)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH5 = portData;
        instantDiCtrl1->ReadBit(0, 5, &portData);
        //        qDebug() << "DO CH6:" << Output_5856_Card_1.Output_CH6
        //                 << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);

        //----------------------Oscilloscope----------------------------//

        Output_5856_Card_1.Output_CH8 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH6 = portData;
        instantDiCtrl1->ReadBit(0, 6, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH6);

        Output_5856_Card_2.Output_CH8 = 1;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_2.Input_CH8 = portData;
        instantDiCtrl2->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_2.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_2.Input_CH8);
    } else {
        Output_5856_Card_1.Output_CH7 = 1;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH7 << 7)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH5 = portData;
        instantDiCtrl1->ReadBit(0, 5, &portData);
        //        qDebug() << "DO CH7:" << Output_5856_Card_1.Output_CH7
        //                 << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);

        Output_5856_Card_1.Output_CH7 = 0;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH7 << 7)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH5 = portData;
        instantDiCtrl1->ReadBit(0, 5, &portData);
        //        qDebug() << "DO CH7:" << Output_5856_Card_1.Output_CH7
        //                 << ", DI CH5:" << static_cast<int>(Input_5856_Card_1.Input_CH5);

        //----------------------Oscilloscope--------------------------------//

        Output_5856_Card_1.Output_CH8 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH6 = portData;
        instantDiCtrl1->ReadBit(0, 6, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_1.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_1.Input_CH6);

        Output_5856_Card_2.Output_CH8 = 0;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH8 << 0)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_2.Input_CH8 = portData;
        instantDiCtrl2->ReadBit(1, 0, &portData);
        //        qDebug() << "DO CH8:" << Output_5856_Card_2.Output_CH8
        //                 << ", DI CH8:" << static_cast<int>(Input_5856_Card_2.Input_CH8);
    }
}
void AdvantechCardsInterface::DC_CARD_3_3V_LOAD_MEASUREMENT_10_percent(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_1.Output_CH9 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH9 << 1)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH7 = portData;
        instantDiCtrl1->ReadBit(0, 7, &portData);
        //        qDebug() << "DO CH9:" << Output_5856_Card_1.Output_CH9
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_1.Input_CH7);

        Output_5856_Card_1.Output_CH9 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH9 << 1)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH7 = portData;
        instantDiCtrl1->ReadBit(0, 7, &portData);
        //        qDebug() << "DO CH9:" << Output_5856_Card_1.Output_CH9
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_1.Input_CH7);

        //        qDebug() << "wait for 3.3v load test complete............at 10%";
    } else {
        Output_5856_Card_1.Output_CH10 = 1;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH10 << 2)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH7 = portData;
        instantDiCtrl1->ReadBit(0, 7, &portData);
        //        qDebug() << "DO CH10:" << Output_5856_Card_1.Output_CH10
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_1.Input_CH7);

        Output_5856_Card_1.Output_CH10 = 0;
        instantDoCtrl1->Write(1, (Output_5856_Card_1.Output_CH10 << 2)); // write to DO bit 0
        QThread::msleep(DELAY);                                          // Wait
        Input_5856_Card_1.Input_CH7 = portData;
        instantDiCtrl1->ReadBit(0, 7, &portData);
        //        qDebug() << "DO CH10:" << Output_5856_Card_1.Output_CH10
        //                 << ", DI CH7:" << static_cast<int>(Input_5856_Card_1.Input_CH7);
    }
}
void AdvantechCardsInterface::DC_CARD_3_3V_LOAD_MEASUREMENT_100_percent(bool checked)
{
    Automation::BDaq::uint8 portData = 0;
    if (checked) {
        Output_5856_Card_1.Output_CH3 = 1;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH3 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH3 = portData;
        instantDiCtrl1->ReadBit(0, 3, &portData);
        //        qDebug() << "DO CH3:" << Output_5856_Card_1.Output_CH3
        //                 << ", DI CH3:" << static_cast<int>(Input_5856_Card_1.Input_CH3);

        Output_5856_Card_1.Output_CH3 = 0;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH3 << 3)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH3 = portData;
        instantDiCtrl1->ReadBit(0, 3, &portData);
        //        qDebug() << "DO CH3:" << Output_5856_Card_1.Output_CH3
        //                 << ", DI CH3:" << static_cast<int>(Input_5856_Card_1.Input_CH3);

        //        qDebug() << "wait for 3.3v load test complete............at 100%";
    } else {
        Output_5856_Card_1.Output_CH4 = 1;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH4 << 4)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH3 = portData;
        instantDiCtrl1->ReadBit(0, 3, &portData);
        //        qDebug() << "DO CH4:" << Output_5856_Card_1.Output_CH4
        //                 << ", DI CH3:" << static_cast<int>(Input_5856_Card_1.Input_CH3);
        Output_5856_Card_1.Output_CH4 = 0;
        instantDoCtrl1->Write(0, (Output_5856_Card_1.Output_CH4 << 4)); // write to DO bit 0
        QThread::msleep(DELAY);                                         // Wait
        Input_5856_Card_1.Input_CH3 = portData;
        instantDiCtrl1->ReadBit(0, 3, &portData);
        //        qDebug() << "DO CH4:" << Output_5856_Card_1.Output_CH4
        //                 << ", DI CH3:" << static_cast<int>(Input_5856_Card_1.Input_CH3);
    }
}

void AdvantechCardsInterface::read4716_Differential_CH0_CH1(double arr[2])
{
    AiChannelCollection *channels = instantAiCtrl1->getChannels();
    for (int ch = 0; ch < 2; ++ch) {
        channels->getItem(ch).setSignalType(Automation::BDaq::AiSignalType::Differential);
        channels->getItem(ch).setValueRange(Automation::BDaq::ValueRange::V_Neg5To5);
    }
    double voltages[2] = {0};
    //    ErrorCode err = aiCtrl->Read(0, 2, voltages);
    ErrorCode err = instantAiCtrl1->Read(0, 2, voltages);
    if (err == Success) {
        arr[0] = voltages[0];
        arr[1] = voltages[1];

        //        qDebug() << "Voltage CH0 (AI0-AI0):" << arr[0] << "V";
        //        qDebug() << "Voltage CH1 (AI1-AI1):" << arr[1] << "V";
        //        double current = arr[0] / resistances;
        //        qDebug() << "Current (I):" << current << "A";

        //        if (current != 0.0) {
        ////            double unknownR = arr[1] / current;
        //            //            qDebug() << "Unknown Resistance R:" << unknownR << "Ohms";
        //        } else {
        //            //            qDebug() << "Current is zero. Cannot calculate resistance.";
        //        }
    } else {
        //        qDebug() << "AI Read failed with code:" << err;
    }

    //    instantAiCtrl1->Dispose();
}

void AdvantechCardsInterface::DIS_OUT_Read_USB_Card_5856()
{
    uint8_t l_value[4] = {0};
    instantDiCtrl2->Read(0, 4, &l_value[0]);

    uint32_t combined = ((uint32_t) l_value[0]) | ((uint32_t) l_value[1] << 8)
                        | ((uint32_t) l_value[2] << 16) | ((uint32_t) l_value[3] << 24);

    memcpy(&Input_5856_Card_2, &combined, sizeof(Input_5856_Card_2));
    //    //    *value = &l_value;
    //    qDebug() << "l_value[0]" << l_value[0];
    //    qDebug() << "l_value[1]" << l_value[1];
    //    qDebug() << "l_value[2]" << l_value[2];
    //    qDebug() << "l_value[3]" << l_value[3];
}

void AdvantechCardsInterface::read4716_Diff_CH0_CH1(double *arr)
{
    AiChannelCollection *channels = instantAiCtrl2->getChannels();
    for (int ch = 14; ch < 16; ++ch) {
        channels->getItem(ch).setSignalType(Automation::BDaq::AiSignalType::Differential);
        channels->getItem(ch).setValueRange(Automation::BDaq::ValueRange::mV_Neg625To625);
    }
    double voltages = 0;
    ErrorCode err = instantAiCtrl2->Read(14, 1, &voltages);
    if (err == Success) {
        *arr = voltages;
    }
}
///////////////////////------------------ADC Card 2 SELF TEST-----------------------////////////////

void AdvantechCardsInterface::DAC_VOLTAGE_DAC_CH1()
{
    Automation::BDaq::uint8 portData = 0;
    ErrorCode err;
    uint8_t doValue_CH16_to_23 = 0xFF; // All 8 bits ON for CH16–CH23 (port 2)

    // ----------------- STEP 1: Turn ON DO CH16–CH23 -------------------
    err = instantDoCtrl2->Write(2, doValue_CH16_to_23);
    if (err != Success) {
        //        qDebug() << "Failed to write DO CH16–23.";
        // return;
    }

    QThread::msleep(DELAY); // Wait for relays
    QThread::msleep(DELAY); // Wait for relays
    QThread::msleep(DELAY); // Wait for relays
    QThread::msleep(DELAY); // Wait for relays
                            //    qDebug() << "DO CH16–23 turned ON.";

    // ----------------- STEP 2: Verify DI CH16–CH23 --------------------

    err = instantDiCtrl2->ReadAny(2, 8, &portData);

    //    if (err == Success)
    //        qDebug() << QString("DI CH%1: %2").arg(16).arg(portData);
    //    else
    //        qDebug() << QString("Failed to read DI CH%1").arg(16);

    // ----------------- STEP 3: Turn ON DO CH24 ------------------------
    Output_5856_Card_2.Output_CH24 = 1;
    err = instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH24 << 0));
    if (err != Success) {
        qDebug() << "Failed to write DO CH24.";
        return;
    }
    QThread::msleep(DELAY); // Wait
                            //    qDebug() << "DO CH24 (Ground) turned ON.";

    // ----------------- STEP 4: Verify DI CH24 -------------------------
    uint8_t portData24 = 0;
    err = instantDiCtrl2->ReadBit(3, 0, &portData24);
    //    if (err == Success)
    ////        qDebug() << QString("DI CH24: %1").arg(portData24);
    //    else
    ////        qDebug() << "Failed to read DI CH24.";

    // ----------------- STEP 5: Read AI CH1–CH8 (±2V range) ------------
    //  double voltages[8] = {0};
    ADC_CARD_read4716_SingleEnded_CH1_to_CH8(); // Reads AI CH0–CH7 → corresponds to CH1–CH8

    //    for (int i = 0; i < 8; ++i)
    //        qDebug() << QString("AI CH%1: %2 V").arg(i + 1).arg(voltages[i]);
    QThread::msleep(DELAY); // Wait for relays
    QThread::msleep(DELAY); // Wait for relays
    QThread::msleep(DELAY); // Wait for relays
    // ----------------- STEP 6: Turn OFF DO CH16–CH24 ------------------
    instantDoCtrl2->Write(2, 0x00); // Clear CH16–CH23
    Output_5856_Card_2.Output_CH24 = 0;
    instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH24 << 0));
    //    qDebug() << "All DO channels (CH16–CH24) turned OFF.";
}

void AdvantechCardsInterface::ADC_CARD_read4716_SingleEnded_CH1_to_CH8()
{
    const int aoChannel = 0;      // AO CH1
    const int aiStartChannel = 1; // AI CH1 (channel 0-based index)
    const int aiChannelCount = 8;
    const int avgSamples = 30; // Number of samples for moving average

    double voltages[] = {2.0, 1.75, 1.5, 1.25, 1.0, 0.75, 0.5, 0.25, 0.0};
    ValueRange desiredRange = V_Neg2pt5To2pt5;

    //     Configure AO channel range
    for (int ch = 0; ch < 16; ++ch) {
        instantAiCtrl2->getChannels()->getItem(ch).setValueRange(desiredRange);
    }

    // Iterate over voltage values
    for (double voltage : voltages) {
        if (instantAoCtrl2->Write(aoChannel, voltage) == Success) {
            QString aoLog = QString("AO Written on CH%1: %2 V")
                                .arg(aoChannel)
                                .arg(QString::number(voltage, 'f', 4));
            //            qDebug() << "\n----------------------------------------";
            //            qDebug() << aoLog;
            Logger::instance()->logText(aoLog);

        } else {
            QString failLog = QString("AO write failed for %1 V")
                                  .arg(QString::number(voltage, 'f', 4));
            //            qDebug() << failLog;
            Logger::instance()->logText(failLog);
            continue;
        }

        QThread::msleep(5); // Let AO settle

        double sumData[aiChannelCount] = {0}; // Initialize per-channel sum

        for (int sample = 0; sample < avgSamples; ++sample) {
            double aiData[aiChannelCount] = {0};

            if (instantAiCtrl2->Read(aiStartChannel, aiChannelCount, aiData) == Success) {
                for (int ch = 0; ch < aiChannelCount; ++ch) {
                    sumData[ch] += aiData[ch]; // Accumulate each channel individually
                }
            } else {
                //                qDebug() << "AI read failed at sample #" << sample + 1;
            }

            QThread::msleep(5); // Delay between samples
        }

        QVector<double> averagedAi;
        //        qDebug() << "Averaged AI Readings:";
        for (int ch = 0; ch < aiChannelCount; ++ch) {
            double avg = sumData[ch] / avgSamples;
            averagedAi.append(avg);
            QString line = QString("AI CH%1: %2 V").arg(ch + 1).arg(QString::number(avg, 'f', 4));
            // qDebug().nospace() << "  AI CH" << (ch + 1) << " : " << QString::number(avg, 'f', 4)<< " V";

            //            qDebug().noquote() << line;
            logParts.append(line);
        }
        QString logLine = logParts.join(", ");
        Logger::instance()->logText(logLine);

        static int ch = 0;
        for (; ch < 9;) {
            switch (ch)

            {
            case 0: {
                g_ADC_SelfTest.averagedAi_test1 = averagedAi;
                //                qDebug() << "in case 1" << g_ADC_SelfTest.averagedAi_test1;
                //2v_1.8-2.2
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[0] - (voltages[0] * TOLERANCE);
                    float upperBound = voltages[0] + (voltages[0] * TOLERANCE);
                    g_ADC_SelfTest.test1Status[i] = (g_ADC_SelfTest.averagedAi_test1[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test1[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }

                ch++;
                break;
            }
            case 1: {
                g_ADC_SelfTest.averagedAi_test2 = averagedAi;
                //                qDebug() << "in case 2" << g_ADC_SelfTest.averagedAi_test2;
                //1.75v_ 1.57-1.95
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[1] - (voltages[1] * TOLERANCE);
                    float upperBound = voltages[1] + (voltages[1] * TOLERANCE);
                    g_ADC_SelfTest.test2Status[i] = (g_ADC_SelfTest.averagedAi_test2[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test2[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }

                ch++;
                break;
            }
            case 2: {
                g_ADC_SelfTest.averagedAi_test3 = averagedAi;
                //                qDebug() << "in case 3" << g_ADC_SelfTest.averagedAi_test3;
                //1.5v_1.35-1.65
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[2] - (voltages[2] * TOLERANCE);
                    float upperBound = voltages[2] + (voltages[2] * TOLERANCE);
                    g_ADC_SelfTest.test3Status[i] = (g_ADC_SelfTest.averagedAi_test3[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test3[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }

                ch++;
                break;
            }
            case 3: {
                g_ADC_SelfTest.averagedAi_test4 = averagedAi;
                //                qDebug() << "in case 4" << g_ADC_SelfTest.averagedAi_test4;
                for (int i = 0; i < 8; i++) {
                    //1.25v_1.12-1.37
                    //                    float lowerBound = voltages[0] - (voltages[0] * TOLERANCE);
                    //                    float upperBound = voltages[0] + (voltages[0] * TOLERANCE);
                    g_ADC_SelfTest.test4Status[i] = (g_ADC_SelfTest.averagedAi_test4[i]
                                                         >= (voltages[3] - (voltages[3] * TOLERANCE))
                                                     && g_ADC_SelfTest.averagedAi_test4[i]
                                                            <= (voltages[3]
                                                                + (voltages[3] * TOLERANCE)))
                                                        ? 1
                                                        : 0;
                }
                ch++;
                break;
            }
            case 4: {
                g_ADC_SelfTest.averagedAi_test5 = averagedAi;
                //                qDebug() << "in case 5" << g_ADC_SelfTest.averagedAi_test5;
                //1.0v_0.9-1.1
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[4] - (voltages[4] * TOLERANCE);
                    float upperBound = voltages[4] + (voltages[4] * TOLERANCE);
                    g_ADC_SelfTest.test5Status[i] = (g_ADC_SelfTest.averagedAi_test5[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test5[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }
                ch++;
                break;
            }
            case 5: {
                g_ADC_SelfTest.averagedAi_test6 = averagedAi;
                //                qDebug() << "in case 6" << g_ADC_SelfTest.averagedAi_test6;
                //0.75v_0.675-0.825
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[5] - (voltages[5] * TOLERANCE);
                    float upperBound = voltages[5] + (voltages[5] * TOLERANCE);
                    g_ADC_SelfTest.test6Status[i] = (g_ADC_SelfTest.averagedAi_test6[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test6[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }
                ch++;
                break;
            }
            case 6: {
                g_ADC_SelfTest.averagedAi_test7 = averagedAi;
                //                qDebug() << "in case 7" << g_ADC_SelfTest.averagedAi_test7;
                //0.5v_0.45-0.55
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[6] - (voltages[6] * TOLERANCE);
                    float upperBound = voltages[6] + (voltages[6] * TOLERANCE);
                    g_ADC_SelfTest.test7Status[i] = (g_ADC_SelfTest.averagedAi_test7[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test7[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }
                ch++;
                break;
            }
            case 7: {
                g_ADC_SelfTest.averagedAi_test8 = averagedAi;
                //                qDebug() << "in case 8" << g_ADC_SelfTest.averagedAi_test8;
                //0.25v_0.225-0.275
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[7] - (voltages[7] * TOLERANCE);
                    float upperBound = voltages[7] + (voltages[7] * TOLERANCE);
                    g_ADC_SelfTest.test8Status[i] = (g_ADC_SelfTest.averagedAi_test8[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test8[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }
                ch++;
                break;
            }
            case 8: {
                g_ADC_SelfTest.averagedAi_test9 = averagedAi;
                //                qDebug() << "in case 9" << g_ADC_SelfTest.averagedAi_test9;
                //0v_0
                for (int i = 0; i < 8; i++) {
                    float lowerBound = voltages[8] - (TOLERANCE);
                    float upperBound = voltages[8] + (TOLERANCE);
                    g_ADC_SelfTest.test9Status[i] = (g_ADC_SelfTest.averagedAi_test9[i] >= lowerBound
                                                     && g_ADC_SelfTest.averagedAi_test9[i]
                                                            <= upperBound)
                                                        ? 1
                                                        : 0;
                }
                ch = 0;
                break;
            }
            }
            break;
        }
        emit aoAiUpdated(voltage, averagedAi);
        QCoreApplication::processEvents(); // Refresh GUI

        QThread::msleep(50); // Before next voltage
    }
}

///////////-------- switchID---------/////////////////////////
//------------------- ABORT SWITCH ON/OFF--------------//
void AdvantechCardsInterface::handleAbortSwitch(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH25 = 1;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH25 << 1));
        Input_5856_Card_2.Input_CH25 = portData;
        instantDiCtrl1->ReadBit(3, 1, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH25 = portData;
        //        qDebug() << "DO CH25: " << Output_5856_Card_2.Output_CH25
        //                 << ", DI CH25: " << static_cast<int>(Input_5856_Card_2.Input_CH25);
    } else {
        // Turn OFF DO CH25
        Output_5856_Card_2.Output_CH25 = 0;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH25 << 1));
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH25 = portData;
        //        qDebug() << "DO CH25: " << Output_5856_Card_2.Output_CH25
        //                 << ", DI CH25: " << static_cast<int>(Input_5856_Card_2.Input_CH25);
    }
}
//------------------- PREPARATION SWITCH ON/OFF--------------//

void AdvantechCardsInterface::handleREADY_INIT_Switch(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH26 = 1;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH26 << 2));
        Input_5856_Card_2.Input_CH26 = portData;
        instantDiCtrl1->ReadBit(3, 2, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH26 = portData;
        //        qDebug() << "DO CH26: " << Output_5856_Card_2.Output_CH26
        //                 << ", DI CH26: " << static_cast<int>(Input_5856_Card_2.Input_CH26);
    } else {
        Output_5856_Card_2.Output_CH26 = 0;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH26 << 2));
        Input_5856_Card_2.Input_CH26 = portData;
        instantDiCtrl1->ReadBit(3, 2, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH26 = portData;
        //        qDebug() << "DO CH26: " << Output_5856_Card_2.Output_CH26
        //                 << ", DI CH26: " << static_cast<int>(Input_5856_Card_2.Input_CH26);
    }
}
//------------------- PREPARATION SWITCH ON/OFF--------------//

void AdvantechCardsInterface::handlePREP_Switch(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH27 = 1;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH27 << 3));
        Input_5856_Card_2.Input_CH27 = portData;
        instantDiCtrl1->ReadBit(3, 3, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH27 = portData;
        //        qDebug() << "DO CH27: " << Output_5856_Card_2.Output_CH27
        //                 << ", DI CH27: " << static_cast<int>(Input_5856_Card_2.Input_CH27);
    } else {
        Output_5856_Card_2.Output_CH27 = 0;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH27 << 3));
        Input_5856_Card_2.Input_CH27 = portData;
        instantDiCtrl1->ReadBit(3, 3, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH27 = portData;
        //        qDebug() << "DO CH27: " << Output_5856_Card_2.Output_CH27
        //                 << ", DI CH27: " << static_cast<int>(Input_5856_Card_2.Input_CH27);
    }
}

//------------------- DISCRETE_IN_CH1 ON/OFF--------------//
void AdvantechCardsInterface::handleDISCRETE_IN_OFF_CH()
{
    Automation::BDaq::uint8 portData = 0;
    Output_5856_Card_2.Output_CH28 = 0;
    instantDoCtrl2->WriteBit(3, 4, 0);
    QThread::msleep(DELAY);
    instantDiCtrl2->ReadBit(3, 4, &portData);
    Input_5856_Card_2.Input_CH28 = portData;
    //------------ch2------------
    Output_5856_Card_2.Output_CH29 = 0;
    instantDoCtrl2->WriteBit(3, 5, 0);
    QThread::msleep(DELAY);
    instantDiCtrl1->ReadBit(3, 5, &portData);
    Input_5856_Card_2.Input_CH29 = portData;
    //--------------ch3------------
    Output_5856_Card_2.Output_CH15 = 0;
    instantDoCtrl2->WriteBit(1, 7, 0);
    QThread::msleep(DELAY);
    instantDiCtrl1->ReadBit(1, 7, &portData);
    Input_5856_Card_2.Input_CH15 = portData;
}

void AdvantechCardsInterface::handleDISCRETE_IN_CH1(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    //    qDebug() << "@@@@value_IN_1" << value;
    if (value == true) {
        Output_5856_Card_2.Output_CH28 = 1;

        instantDoCtrl2->WriteBit(3, 4, 1);
        QThread::msleep(DELAY);
        instantDiCtrl2->ReadBit(3, 4, &portData);
        Input_5856_Card_2.Input_CH28 = portData;
        //        qDebug() << "DO CH28: " << Output_5856_Card_2.Output_CH28
        //                 << ", DI CH28: " << static_cast<int>(Input_5856_Card_2.Input_CH28);

    } else {
        Output_5856_Card_2.Output_CH28 = 0;
        instantDoCtrl2->WriteBit(3, 4, 0);
        QThread::msleep(DELAY);
        instantDiCtrl2->ReadBit(3, 4, &portData);
        Input_5856_Card_2.Input_CH28 = portData;
        //        qDebug() << "DO CH28: " << Output_5856_Card_2.Output_CH28
        //                 << ", DI CH28: " << static_cast<int>(Input_5856_Card_2.Input_CH28);
    }
}

//------------------- DISCRETE_IN_CH2 ON/OFF--------------//

void AdvantechCardsInterface::handleDISCRETE_IN_CH2(bool value)
{
    Automation::BDaq::uint8 portData = 0;
    //    qDebug() << "@@@@value_IN_2" << value;
    if (value == true) {
        Output_5856_Card_2.Output_CH29 = 1;
        instantDoCtrl2->WriteBit(3, 5, 1);
        Input_5856_Card_2.Input_CH29 = portData;
        QThread::msleep(DELAY);
        instantDiCtrl2->ReadBit(3, 5, &portData);
        Input_5856_Card_2.Input_CH29 = portData;
        //        qDebug() << "DO CH29: " << Output_5856_Card_2.Output_CH29
        //                 << ", DI CH29: " << static_cast<int>(Input_5856_Card_2.Input_CH29);
    } else {
        Output_5856_Card_2.Output_CH29 = 0;
        instantDoCtrl2->WriteBit(3, 5, 0);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH29 = portData;
        instantDiCtrl2->ReadBit(3, 5, &portData);
        Input_5856_Card_2.Input_CH29 = portData;
        //        qDebug() << "DO CH29: " << Output_5856_Card_2.Output_CH29
        //                 << ", DI CH29: " << static_cast<int>(Input_5856_Card_2.Input_CH29);
    }
}

//------------------- DISCRETE_IN_CH3 ON/OFF--------------//

void AdvantechCardsInterface::handleDISCRETE_IN_CH3(bool value)
{
    Automation::BDaq::uint8 portData = 0;
    //    qDebug() << "@@@@value_IN_3" << value;
    if (value == true) {
        Output_5856_Card_2.Output_CH15 = 1;
        instantDoCtrl2->WriteBit(1, 7, 1);
        QThread::msleep(DELAY);
        instantDiCtrl2->ReadBit(1, 7, &portData);
        Input_5856_Card_2.Input_CH15 = portData;
        //        qDebug() << "DO CH15: " << Output_5856_Card_2.Output_CH15
        //                 << ", DI CH15: " << static_cast<int>(Input_5856_Card_2.Input_CH15);
    } else {
        Output_5856_Card_2.Output_CH15 = 0;
        instantDoCtrl2->WriteBit(1, 7, 0);
        QThread::msleep(DELAY);
        instantDiCtrl2->ReadBit(1, 7, &portData);
        Input_5856_Card_2.Input_CH15 = portData;
        //        qDebug() << "DO CH15: " << Output_5856_Card_2.Output_CH15
        //                 << ", DI CH15: " << static_cast<int>(Input_5856_Card_2.Input_CH15);
    }
}
//------------------- DISCRETE_OUT_CH1 ON/OFF--------------//

void AdvantechCardsInterface::handleDISCRETE_OUT_CH1(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH30 = 1;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH30 << 6));
        Input_5856_Card_2.Input_CH30 = portData;
        QThread::msleep(DELAY);
        instantDiCtrl2->ReadBit(3, 6, &portData);
        Input_5856_Card_2.Input_CH30 = portData;
        //        qDebug() << "DO CH30: " << Output_5856_Card_2.Output_CH30
        //                 << ", DI CH30: " << static_cast<int>(Input_5856_Card_2.Input_CH30);
    } else {
        Output_5856_Card_2.Output_CH30 = 0;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH30 << 6));
        Input_5856_Card_2.Input_CH30 = portData;
        instantDiCtrl2->ReadBit(3, 6, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH30 = portData;
        //        qDebug() << "DO CH30: " << Output_5856_Card_2.Output_CH30
        //                 << ", DI CH30: " << static_cast<int>(Input_5856_Card_2.Input_CH30);
    }
}

//------------------- DISCRETE_OUT_CH2 ON/OFF--------------//

void AdvantechCardsInterface::handleDISCRETE_OUT_CH2(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH31 = 1;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH31 << 7));
        Input_5856_Card_2.Input_CH31 = portData;
        QThread::msleep(DELAY);
        instantDiCtrl1->ReadBit(3, 7, &portData);
        Input_5856_Card_2.Input_CH31 = portData;
        //        qDebug() << "DO CH31: " << Output_5856_Card_2.Output_CH31
        //                 << ", DI CH31: " << static_cast<int>(Input_5856_Card_2.Input_CH31);
    } else {
        Output_5856_Card_2.Output_CH31 = 0;
        instantDoCtrl2->Write(3, (Output_5856_Card_2.Output_CH31 << 7));
        Input_5856_Card_2.Input_CH31 = portData;
        QThread::msleep(DELAY);
        instantDiCtrl1->ReadBit(3, 7, &portData);
        Input_5856_Card_2.Input_CH31 = portData;
        //        qDebug() << "DO CH31: " << Output_5856_Card_2.Output_CH31
        //                 << ", DI CH31: " << static_cast<int>(Input_5856_Card_2.Input_CH31);
    }
}

//------------------- DISCRETE_OUT_CH3 ON/OFF--------------//

void AdvantechCardsInterface::handleDISCRETE_OUT_CH3(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH14 = 1;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH14 << 6));
        QThread::msleep(DELAY);
        instantDiCtrl1->ReadBit(1, 6, &portData);
        Input_5856_Card_2.Input_CH14 = portData;
        //        qDebug() << "DO CH14: " << Output_5856_Card_2.Output_CH14
        //                 << ", DI CH14: " << static_cast<int>(Input_5856_Card_2.Input_CH14);
    } else {
        Output_5856_Card_2.Output_CH14 = 0;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH14 << 6));
        QThread::msleep(DELAY);
        instantDiCtrl1->ReadBit(1, 6, &portData);
        Input_5856_Card_2.Input_CH14 = portData;
        //        qDebug() << "DO CH14: " << Output_5856_Card_2.Output_CH14
        //                 << ", DI CH14: " << static_cast<int>(Input_5856_Card_2.Input_CH14);
    }
}

//------------------- DISCRETE_OUT_CH4 ON/OFF--------------//

void AdvantechCardsInterface::handleDISCRETE_OUT_CH4(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH13 = 1;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH13 << 5));
        QThread::msleep(DELAY);
        instantDiCtrl1->ReadBit(1, 5, &portData);
        Input_5856_Card_2.Input_CH13 = portData;
        //        qDebug() << "DO CH13: " << Output_5856_Card_2.Output_CH13
        //                 << ", DI CH13: " << static_cast<int>(Input_5856_Card_2.Input_CH13);
    } else {
        Output_5856_Card_2.Output_CH13 = 0;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH13 << 5));
        Input_5856_Card_2.Input_CH13 = portData;
        instantDiCtrl1->ReadBit(1, 5, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH13 = portData;
        //        qDebug() << "DO CH13: " << Output_5856_Card_2.Output_CH13
        //                 << ", DI CH13: " << static_cast<int>(Input_5856_Card_2.Input_CH13);
    }
}

//------------------- DISCRETE_OUT_CH5 ON/OFF--------------//

void AdvantechCardsInterface::handleDISCRETE_OUT_CH5(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_2.Output_CH12 = 1;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH12 << 4));
        Input_5856_Card_2.Input_CH12 = portData;
        instantDiCtrl1->ReadBit(1, 4, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH12 = portData;
        //        qDebug() << "DO CH12: " << Output_5856_Card_2.Output_CH12
        //                 << ", DI CH12: " << static_cast<int>(Input_5856_Card_2.Input_CH12);
    } else {
        Output_5856_Card_2.Output_CH12 = 0;
        instantDoCtrl2->Write(1, (Output_5856_Card_2.Output_CH12 << 4));
        Input_5856_Card_2.Input_CH12 = portData;
        instantDiCtrl1->ReadBit(1, 4, &portData);
        QThread::msleep(DELAY);
        Input_5856_Card_2.Input_CH12 = portData;
        //        qDebug() << "DO CH12: " << Output_5856_Card_2.Output_CH12
        //                 << ", DI CH12: " << static_cast<int>(Input_5856_Card_2.Input_CH12);
    }
}
//------------------- Rotatory_Switch ON/OFF--------------//

void AdvantechCardsInterface::handleTPS_D1_1(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH0 = 1;
        instantDoCtrl3->WriteBit(0, 0, 1);
        // instantDoCtrl3->Write(0, (Output_5856_Card_3.Output_CH0 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 0, &portData);
        Input_5856_Card_3.Input_CH0 = portData;
        //        qDebug() << "DO CH0: " << Output_5856_Card_3.Output_CH0
        //                 << ", DI CH0: " << static_cast<int>(Input_5856_Card_3.Input_CH0);
    } else {
        Output_5856_Card_3.Output_CH0 = 0;
        instantDoCtrl3->WriteBit(0, 0, 0);
        //  instantDoCtrl3->Write(0, (Output_5856_Card_3.Output_CH0 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 0, &portData);
        Input_5856_Card_3.Input_CH0 = portData;
        //        qDebug() << "DO CH0: " << Output_5856_Card_3.Output_CH0
        //                 << ", DI CH0: " << static_cast<int>(Input_5856_Card_3.Input_CH0);
    }
}

void AdvantechCardsInterface::handleTPS_D1_2(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH1 = 1;
        instantDoCtrl3->WriteBit(0, 1, 1);
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 1, &portData);

        Input_5856_Card_3.Input_CH1 = portData;
        //        qDebug() << "DO CH1: " << Output_5856_Card_3.Output_CH1
        //                 << ", DI CH1: " << static_cast<int>(Input_5856_Card_3.Input_CH1);
    } else {
        Output_5856_Card_3.Output_CH1 = 0;
        instantDoCtrl3->WriteBit(0, 1, 0);
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 1, &portData);
        Input_5856_Card_3.Input_CH1 = portData;
        //        qDebug() << "DO CH1: " << Output_5856_Card_3.Output_CH1
        //                 << ", DI CH1: " << static_cast<int>(Input_5856_Card_3.Input_CH1);
    }
}

void AdvantechCardsInterface::handleTPS_D1_3(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH2 = 1;
        instantDoCtrl3->WriteBit(0, 2, 1);
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 2, &portData);
        Input_5856_Card_3.Input_CH2 = portData;
        //        qDebug() << "DO CH2: " << Output_5856_Card_3.Output_CH2
        //                 << ", DI CH2: " << static_cast<int>(Input_5856_Card_3.Input_CH2);
    } else {
        Output_5856_Card_3.Output_CH2 = 0;
        instantDoCtrl3->WriteBit(0, 2, 0);
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 2, &portData);
        Input_5856_Card_3.Input_CH2 = portData;
        //        qDebug() << "DO CH2: " << Output_5856_Card_3.Output_CH2
        //                 << ", DI CH2: " << static_cast<int>(Input_5856_Card_3.Input_CH2);
    }
}
void AdvantechCardsInterface::handleTPS_D1_4(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH3 = 1;
        instantDoCtrl3->WriteBit(0, 3, 1);
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 3, &portData);

        Input_5856_Card_3.Input_CH3 = portData;
        //        qDebug() << "DO CH3: " << Output_5856_Card_3.Output_CH3
        //                 << ", DI CH3: " << static_cast<int>(Input_5856_Card_3.Input_CH3);
    } else {
        Output_5856_Card_3.Output_CH3 = 0;
        instantDoCtrl3->WriteBit(0, 3, 0);
        QThread::msleep(DELAY);
        instantDiCtrl3->ReadBit(0, 3, &portData);

        Input_5856_Card_3.Input_CH3 = portData;
        //        qDebug() << "DO CH3: " << Output_5856_Card_3.Output_CH3
        //                 << ", DI CH3: " << static_cast<int>(Input_5856_Card_3.Input_CH3);
    }
}
void AdvantechCardsInterface::handleTPS_D1_5(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH4 = 1;
        instantDoCtrl3->WriteBit(0, 4, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 4, &portData);
        Input_5856_Card_3.Input_CH4 = portData;
        //        qDebug() << ""
        //                    "DO CH4: "
        //                 << Output_5856_Card_3.Output_CH4
        //                 << ", DI CH4: " << static_cast<int>(Input_5856_Card_3.Input_CH4);

    } else {
        Output_5856_Card_3.Output_CH4 = 0;
        instantDoCtrl3->WriteBit(0, 4, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 4, &portData);

        Input_5856_Card_3.Input_CH4 = portData;
        //        qDebug() << "DO CH4: " << Output_5856_Card_3.Output_CH4
        //                 << ", DI CH4: " << static_cast<int>(Input_5856_Card_3.Input_CH4);
    }
}
void AdvantechCardsInterface::handleTPS_D1_6(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH5 = 1;
        instantDoCtrl3->WriteBit(0, 5, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 5, &portData);

        Input_5856_Card_3.Input_CH5 = portData;
        //        qDebug() << "DO CH5: " << Output_5856_Card_3.Output_CH5
        //                 << ", DI CH5: " << static_cast<int>(Input_5856_Card_3.Input_CH5);

    } else {
        Output_5856_Card_3.Output_CH5 = 0;
        instantDoCtrl3->WriteBit(0, 5, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 5, &portData);
        Input_5856_Card_3.Input_CH5 = portData;
        //        qDebug() << "DO CH5: " << Output_5856_Card_3.Output_CH5
        //                 << ", DI CH5: " << static_cast<int>(Input_5856_Card_3.Input_CH5);
    }
}
void AdvantechCardsInterface::handleTPS_D1_7(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH6 = 1;
        instantDoCtrl3->WriteBit(0, 6, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 6, &portData);
        Input_5856_Card_3.Input_CH6 = portData;
        //        qDebug() << "DO CH6: " << Output_5856_Card_3.Output_CH6
        //                 << ", DI CH6: " << static_cast<int>(Input_5856_Card_3.Input_CH6);

    } else {
        Output_5856_Card_3.Output_CH6 = 0;
        instantDoCtrl3->WriteBit(0, 6, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 6, &portData);
        Input_5856_Card_3.Input_CH6 = portData;
        //        qDebug() << "DO CH6: " << Output_5856_Card_3.Output_CH6
        //                 << ", DI CH6: " << static_cast<int>(Input_5856_Card_3.Input_CH6);
    }
}

void AdvantechCardsInterface::handleTPS_D1_8(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH7 = 1;
        instantDoCtrl3->WriteBit(0, 7, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 7, &portData);
        Input_5856_Card_3.Input_CH7 = portData;
        //        qDebug() << "DO CH7: " << Output_5856_Card_3.Output_CH7
        //                 << ", DI CH7: " << static_cast<int>(Input_5856_Card_3.Input_CH7);

    } else {
        Output_5856_Card_3.Output_CH7 = 0;
        instantDoCtrl3->WriteBit(0, 7, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(0, 7, &portData);
        Input_5856_Card_3.Input_CH7 = portData;
        //        qDebug() << "DO CH7: " << Output_5856_Card_3.Output_CH7
        //                 << ", DI CH7: " << static_cast<int>(Input_5856_Card_3.Input_CH7);
    }
}
void AdvantechCardsInterface::handleTPS_D1_9(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH8 = 1;
        //        instantDoCtrl3->Write(0, 0);
        instantDoCtrl3->WriteBit(1, 0, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 0, &portData);
        Input_5856_Card_3.Input_CH8 = portData;
        //        qDebug() << "DO CH8: " << Output_5856_Card_3.Output_CH8
        //                 << ", DI CH8: " << static_cast<int>(Input_5856_Card_3.Input_CH8);

    } else {
        Output_5856_Card_3.Output_CH8 = 0;
        instantDoCtrl3->WriteBit(1, 0, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 0, &portData);
        Input_5856_Card_3.Input_CH8 = portData;
        //        qDebug() << "DO CH8: " << Output_5856_Card_3.Output_CH8
        //                 << ", DI CH8: " << static_cast<int>(Input_5856_Card_3.Input_CH8);
    }
}
void AdvantechCardsInterface::handleTPS_D1_10(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH9 = 1;
        instantDoCtrl3->WriteBit(1, 1, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 1, &portData);
        Input_5856_Card_3.Input_CH9 = portData;
        //        qDebug() << "DO CH9: " << Output_5856_Card_3.Output_CH9
        //                 << ", DI CH9: " << static_cast<int>(Input_5856_Card_3.Input_CH9);

    } else {
        Output_5856_Card_3.Output_CH9 = 0;
        instantDoCtrl3->WriteBit(1, 1, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 1, &portData);
        Input_5856_Card_3.Input_CH9 = portData;
        //        qDebug() << "DO CH9: " << Output_5856_Card_3.Output_CH9
        //                 << ", DI CH9: " << static_cast<int>(Input_5856_Card_3.Input_CH9);
    }
}
///------------- Rotatory_switch2_check-----------------------///

void AdvantechCardsInterface::handleTPS_D2_1(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH10 = 1;
        instantDoCtrl3->WriteBit(1, 2, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 2, &portData);
        Input_5856_Card_3.Input_CH10 = portData;
        //        qDebug() << "DO CH10: " << Output_5856_Card_3.Output_CH10
        //                 << "DI CH10: " << static_cast<int>(Input_5856_Card_3.Input_CH10);

    } else {
        Output_5856_Card_3.Output_CH10 = 0;
        instantDoCtrl3->WriteBit(1, 2, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 2, &portData);
        Input_5856_Card_3.Input_CH10 = portData;
        //        qDebug() << "DO CH10: " << Output_5856_Card_3.Output_CH10
        //                 << "DI CH10: " << static_cast<int>(Input_5856_Card_3.Input_CH10);
    }
}

void AdvantechCardsInterface::handleTPS_D2_2(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH11 = 1;
        instantDoCtrl3->WriteBit(1, 3, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 3, &portData);
        Input_5856_Card_3.Input_CH11 = portData;
        //        qDebug() << "DO CH11: " << Output_5856_Card_3.Output_CH11
        //                 << ", DI CH11: " << static_cast<int>(Input_5856_Card_3.Input_CH11);

    } else {
        Output_5856_Card_3.Output_CH11 = 0;
        instantDoCtrl3->WriteBit(1, 3, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 3, &portData);
        Input_5856_Card_3.Input_CH11 = portData;
        //        qDebug() << "DO CH11: " << Output_5856_Card_3.Output_CH11
        //                 << ", DI CH11: " << static_cast<int>(Input_5856_Card_3.Input_CH11);
    }
}
void AdvantechCardsInterface::handleTPS_D2_3(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH12 = 1;
        instantDoCtrl3->WriteBit(1, 4, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 4, &portData);
        Input_5856_Card_3.Input_CH12 = portData;
        //        qDebug() << "DO CH12: " << Output_5856_Card_3.Output_CH12
        //                 << ", DI CH12: " << static_cast<int>(Input_5856_Card_3.Input_CH12);
    } else {
        Output_5856_Card_3.Output_CH12 = 0;
        instantDoCtrl3->WriteBit(1, 4, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 4, &portData);
        Input_5856_Card_3.Input_CH12 = portData;
        //        qDebug() << "DO CH12: " << Output_5856_Card_3.Output_CH12
        //                 << ", DI CH12: " << static_cast<int>(Input_5856_Card_3.Input_CH12);
    }
}
void AdvantechCardsInterface::handleTPS_D2_4(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH13 = 1;
        instantDoCtrl3->WriteBit(1, 5, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 5, &portData);
        Input_5856_Card_3.Input_CH13 = portData;
        //        qDebug() << "DO CH13: " << Output_5856_Card_3.Output_CH13
        //                 << ", DI CH13: " << static_cast<int>(Input_5856_Card_3.Input_CH13);
    } else {
        Output_5856_Card_3.Output_CH13 = 0;
        instantDoCtrl3->WriteBit(1, 5, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 5, &portData);
        Input_5856_Card_3.Input_CH13 = portData;
        //        qDebug() << "DO CH13: " << Output_5856_Card_3.Output_CH13
        //                 << ", DI CH13: " << static_cast<int>(Input_5856_Card_3.Input_CH13);
    }
}
void AdvantechCardsInterface::handleTPS_D2_5(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH14 = 1;
        instantDoCtrl3->WriteBit(1, 6, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 6, &portData);
        Input_5856_Card_3.Input_CH14 = portData;
        //        qDebug() << "DO CH14: " << Output_5856_Card_3.Output_CH14
        //                 << ", DI CH14: " << static_cast<int>(Input_5856_Card_3.Input_CH14);
    } else {
        Output_5856_Card_3.Output_CH14 = 0;
        instantDoCtrl3->WriteBit(1, 6, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 6, &portData);
        Input_5856_Card_3.Input_CH14 = portData;
        //        qDebug() << "DO CH14: " << Output_5856_Card_3.Output_CH14
        //                 << ", DI CH14: " << static_cast<int>(Input_5856_Card_3.Input_CH14);
    }
}
void AdvantechCardsInterface::handleTPS_D2_6(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH15 = 1;
        instantDoCtrl3->WriteBit(1, 7, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 7, &portData);
        Input_5856_Card_3.Input_CH15 = portData;
        //        qDebug() << "DO CH15: " << Output_5856_Card_3.Output_CH15
        //                 << ", DI CH15: " << static_cast<int>(Input_5856_Card_3.Input_CH15);
    } else {
        Output_5856_Card_3.Output_CH15 = 0;
        instantDoCtrl3->WriteBit(1, 7, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(1, 7, &portData);
        Input_5856_Card_3.Input_CH15 = portData;
        //        qDebug() << "DO CH15: " << Output_5856_Card_3.Output_CH15
        //                 << ", DI CH15: " << static_cast<int>(Input_5856_Card_3.Input_CH15);
    }
}
void AdvantechCardsInterface::handleTPS_D2_7(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH16 = 1;
        instantDoCtrl3->WriteBit(2, 0, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 0, &portData);
        Input_5856_Card_3.Input_CH16 = portData;
        //        qDebug() << "DO CH16: " << Output_5856_Card_3.Output_CH16
        //                 << ", DI CH16: " << static_cast<int>(Input_5856_Card_3.Input_CH16);
    } else {
        Output_5856_Card_3.Output_CH16 = 0;
        instantDoCtrl3->WriteBit(2, 0, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 0, &portData);
        Input_5856_Card_3.Input_CH16 = portData;
        //        qDebug() << "DO CH16: " << Output_5856_Card_3.Output_CH16
        //                 << ", DI CH16: " << static_cast<int>(Input_5856_Card_3.Input_CH16);
    }
}
void AdvantechCardsInterface::handleTPS_D2_8(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH17 = 1;
        instantDoCtrl3->WriteBit(2, 1, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 1, &portData);

        Input_5856_Card_3.Input_CH17 = portData;
        //        qDebug() << "DO CH17: " << Output_5856_Card_3.Output_CH17
        //                 << ", DI CH17: " << static_cast<int>(Input_5856_Card_3.Input_CH17);
    } else {
        Output_5856_Card_3.Output_CH17 = 0;
        instantDoCtrl3->WriteBit(2, 1, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 1, &portData);
        Input_5856_Card_3.Input_CH17 = portData;
        //        qDebug() << "DO CH17: " << Output_5856_Card_3.Output_CH17
        //                 << ", DI CH17: " << static_cast<int>(Input_5856_Card_3.Input_CH17);
    }
}
void AdvantechCardsInterface::handleTPS_D2_9(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH18 = 1;
        instantDoCtrl3->WriteBit(2, 2, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 2, &portData);

        Input_5856_Card_3.Input_CH18 = portData;
        //        qDebug() << "DO CH18: " << Output_5856_Card_3.Output_CH18
        //                 << ", DI CH18: " << static_cast<int>(Input_5856_Card_3.Input_CH18);
    } else {
        Output_5856_Card_3.Output_CH18 = 0;
        instantDoCtrl3->WriteBit(2, 2, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 2, &portData);
        Input_5856_Card_3.Input_CH18 = portData;
        //        qDebug() << "DO CH18: " << Output_5856_Card_3.Output_CH18
        //                 << ", DI CH18: " << static_cast<int>(Input_5856_Card_3.Input_CH18);
    }
}
void AdvantechCardsInterface::handleTPS_D2_10(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH19 = 1;
        instantDoCtrl3->WriteBit(2, 3, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 3, &portData);

        Input_5856_Card_3.Input_CH19 = portData;
        //        qDebug() << "DO CH19: " << Output_5856_Card_3.Output_CH19
        //                 << ", DI CH19: " << static_cast<int>(Input_5856_Card_3.Input_CH19);
    } else {
        Output_5856_Card_3.Output_CH19 = 0;
        instantDoCtrl3->WriteBit(2, 3, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 3, &portData);
        Input_5856_Card_3.Input_CH19 = portData;
        //        qDebug() << "DO CH19: " << Output_5856_Card_3.Output_CH19
        //                 << ", DI CH19: " << static_cast<int>(Input_5856_Card_3.Input_CH19);
    }
}
///------------------ ROTATORY_SWITCH3_CHECK-----------------------------////
void AdvantechCardsInterface::handleTPS_D3_1(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH20 = 1;
        instantDoCtrl3->WriteBit(2, 4, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 4, &portData);
        Input_5856_Card_3.Input_CH20 = portData;
        //        qDebug() << "DO CH20: " << Output_5856_Card_3.Output_CH20
        //                 << ", DI CH20: " << static_cast<int>(Input_5856_Card_3.Input_CH20);
    } else {
        Output_5856_Card_3.Output_CH20 = 0;
        instantDoCtrl3->WriteBit(2, 4, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 4, &portData);
        Input_5856_Card_3.Input_CH20 = portData;
        //        qDebug() << "DO CH20: " << Output_5856_Card_3.Output_CH20
        //                 << ", DI CH20: " << static_cast<int>(Input_5856_Card_3.Input_CH20);
    }
}
void AdvantechCardsInterface::handleTPS_D3_2(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH21 = 1;
        instantDoCtrl3->WriteBit(2, 5, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 5, &portData);
        Input_5856_Card_3.Input_CH21 = portData;
        //        qDebug() << "DO CH21: " << Output_5856_Card_3.Output_CH21
        //                 << ", DI CH21: " << static_cast<int>(Input_5856_Card_3.Input_CH21);
    } else {
        Output_5856_Card_3.Output_CH21 = 0;
        instantDoCtrl3->WriteBit(2, 5, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 5, &portData);
        Input_5856_Card_3.Input_CH21 = portData;
        //        qDebug() << "DO CH21: " << Output_5856_Card_3.Output_CH21
        //                 << ", DI CH21: " << static_cast<int>(Input_5856_Card_3.Input_CH21);
    }
}
void AdvantechCardsInterface::handleTPS_D3_3(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH22 = 1;
        instantDoCtrl3->WriteBit(2, 6, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 6, &portData);
        Input_5856_Card_3.Input_CH22 = portData;
        //        qDebug() << "DO CH22: " << Output_5856_Card_3.Output_CH22
        //                 << ", DI CH22: " << static_cast<int>(Input_5856_Card_3.Input_CH22);
    } else {
        Output_5856_Card_3.Output_CH22 = 0;
        instantDoCtrl3->WriteBit(2, 6, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 6, &portData);
        Input_5856_Card_3.Input_CH22 = portData;
        //        qDebug() << "DO CH22: " << Output_5856_Card_3.Output_CH22
        //                 << ", DI CH22: " << static_cast<int>(Input_5856_Card_3.Input_CH22);
    }
}
void AdvantechCardsInterface::handleTPS_D3_4(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH23 = 1;
        instantDoCtrl3->WriteBit(2, 7, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 7, &portData);

        Input_5856_Card_3.Input_CH23 = portData;
        //        qDebug() << "DO CH23: " << Output_5856_Card_3.Output_CH23
        //                 << ", DI CH23: " << static_cast<int>(Input_5856_Card_3.Input_CH23);
    } else {
        Output_5856_Card_3.Output_CH23 = 0;
        instantDoCtrl3->WriteBit(2, 7, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(2, 7, &portData);
        Input_5856_Card_3.Input_CH23 = portData;
        //        qDebug() << "DO CH23: " << Output_5856_Card_3.Output_CH23
        //                 << ", DI CH23: " << static_cast<int>(Input_5856_Card_3.Input_CH23);
    }
}
void AdvantechCardsInterface::handleTPS_D3_5(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH24 = 1;
        instantDoCtrl3->WriteBit(3, 0, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 0, &portData);
        Input_5856_Card_3.Input_CH24 = portData;
        //        qDebug() << "DO CH24: " << Output_5856_Card_3.Output_CH24
        //                 << ", DI CH24: " << static_cast<int>(Input_5856_Card_3.Input_CH24);
    } else {
        Output_5856_Card_3.Output_CH24 = 0;
        instantDoCtrl3->WriteBit(3, 0, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 0, &portData);
        Input_5856_Card_3.Input_CH24 = portData;
        //        qDebug() << "DO CH24: " << Output_5856_Card_3.Output_CH24
        //                 << ", DI CH24: " << static_cast<int>(Input_5856_Card_3.Input_CH24);
    }
}

void AdvantechCardsInterface::handleTPS_D3_6(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH25 = 1;
        instantDoCtrl3->WriteBit(3, 1, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 1, &portData);
        Input_5856_Card_3.Input_CH25 = portData;
        //        qDebug() << "DO CH25: " << Output_5856_Card_3.Output_CH25
        //                 << ", DI CH25: " << static_cast<int>(Input_5856_Card_3.Input_CH25);
    } else {
        Output_5856_Card_3.Output_CH25 = 0;
        instantDoCtrl3->WriteBit(3, 1, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 1, &portData);
        Input_5856_Card_3.Input_CH25 = portData;
        //        qDebug() << "DO CH25: " << Output_5856_Card_3.Output_CH25
        //                 << ", DI CH25: " << static_cast<int>(Input_5856_Card_3.Input_CH25);
    }
}
void AdvantechCardsInterface::handleTPS_D3_7(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH26 = 1;
        instantDoCtrl3->WriteBit(3, 2, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 2, &portData);
        Input_5856_Card_3.Input_CH26 = portData;
        //        qDebug() << "DO CH26: " << Output_5856_Card_3.Output_CH26
        //                 << ", DI CH26: " << static_cast<int>(Input_5856_Card_3.Input_CH26);
    } else {
        Output_5856_Card_3.Output_CH26 = 0;
        instantDoCtrl3->WriteBit(3, 2, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 2, &portData);
        Input_5856_Card_3.Input_CH26 = portData;
        //        qDebug() << "DO CH26: " << Output_5856_Card_3.Output_CH26
        //                 << ", DI CH26: " << static_cast<int>(Input_5856_Card_3.Input_CH26);
    }
}
void AdvantechCardsInterface::handleTPS_D3_8(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH27 = 1;
        instantDoCtrl3->WriteBit(3, 3, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 3, &portData);
        Input_5856_Card_3.Input_CH27 = portData;
        //        qDebug() << "DO CH27: " << Output_5856_Card_3.Output_CH27
        //                 << ", DI CH27: " << static_cast<int>(Input_5856_Card_3.Input_CH27);
    } else {
        Output_5856_Card_3.Output_CH27 = 0;
        instantDoCtrl3->WriteBit(3, 3, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 3, &portData);
        Input_5856_Card_3.Input_CH27 = portData;
        //        qDebug() << "DO CH27: " << Output_5856_Card_3.Output_CH27
        //                 << ", DI CH27: " << static_cast<int>(Input_5856_Card_3.Input_CH27);
    }
}
void AdvantechCardsInterface::handleTPS_D3_9(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH28 = 1;
        instantDoCtrl3->WriteBit(3, 4, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 4, &portData);
        Input_5856_Card_3.Input_CH28 = portData;
        //        qDebug() << "DO CH28: " << Output_5856_Card_3.Output_CH28
        //                 << ", DI CH28: " << static_cast<int>(Input_5856_Card_3.Input_CH28);
    } else {
        Output_5856_Card_3.Output_CH28 = 0;
        instantDoCtrl3->WriteBit(3, 4, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 4, &portData);
        Input_5856_Card_3.Input_CH28 = portData;
        //        qDebug() << "DO CH28: " << Output_5856_Card_3.Output_CH28
        //                 << ", DI CH28: " << static_cast<int>(Input_5856_Card_3.Input_CH28);
    }
}
void AdvantechCardsInterface::handleTPS_D3_10(bool value)
{
    Automation::BDaq::uint8 portData = 0;

    if (value == true) {
        Output_5856_Card_3.Output_CH29 = 1;
        instantDoCtrl3->WriteBit(3, 5, 1);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 5, &portData);
        Input_5856_Card_3.Input_CH29 = portData;
        //        qDebug() << "DO CH29: " << Output_5856_Card_3.Output_CH29
        //                 << ", DI CH29: " << static_cast<int>(Input_5856_Card_3.Input_CH29);
    } else {
        Output_5856_Card_3.Output_CH29 = 0;
        instantDoCtrl3->WriteBit(3, 5, 0);
        QThread::msleep(DELAY);
        instantDoCtrl3->ReadBit(3, 5, &portData);
        Input_5856_Card_3.Input_CH29 = portData;
        //        qDebug() << "DO CH29: " << Output_5856_Card_3.Output_CH29
        //                 << ", DI CH29: " << static_cast<int>(Input_5856_Card_3.Input_CH29);
    }
}

//---------------Send struct packet via USB with DAC_Value=2V---------------------//

void AdvantechCardsInterface::onTriggerCard1DO_OFFButtonClicked_5856()
{
    using namespace Automation::BDaq;

    if (instantDoCtrl1 == nullptr) {
        //        qDebug() << "DO controller is null!";
        return;
    }
    currentDOState = (USB_5856_enum) 32;

    uint8 allOff[4] = {0x00, 0x00, 0x00, 0x00};

    ErrorCode ret = instantDoCtrl1->Write(0, 4, allOff); // 4 ports = 32 bits
    if (BioFailed(ret)) {
        //        qDebug() << "DO write failed with error code:" << ret;
    } else {
        //        qDebug() << "All 32 DOs CARD1 turned OFF successfully.";
    }
}

void AdvantechCardsInterface::onTriggerCard2DO_OFFButtonClicked_5856()
{
    using namespace Automation::BDaq;

    if (instantDoCtrl2 == nullptr) {
        //        qDebug() << "DO controller is null!";
        return;
    }
    currentDOState = (USB_5856_enum) 32;

    uint8 allOff[4] = {0x00, 0x00, 0x00, 0x00};
    ErrorCode ret = instantDoCtrl2->Write(0, 4, allOff); // 4 ports = 32 bits
    if (BioFailed(ret)) {
        //        qDebug() << "DO write failed with error code:" << ret;
    } else {
        //        qDebug() << "All 32 DOs CARD2 turned OFF successfully.";
    }
}
void AdvantechCardsInterface::onTriggerCard3DO_OFFButtonClicked_5856()
{
    using namespace Automation::BDaq;
    if (instantDoCtrl3 == nullptr) {
        //        qDebug() << "DO controller is null!";
        return;
    }
    currentDOState = (USB_5856_enum) 32;

    uint8 allOff[4] = {0x00, 0x00, 0x00, 0x00};
    ErrorCode ret = instantDoCtrl3->Write(0, 4, allOff); // 4 ports = 32 bits
    if (BioFailed(ret)) {
        //        qDebug() << "DO write failed with error code:" << ret;
    } else {
        //        qDebug() << "All 32 DOs CARD3 turned OFF successfully.";
    }
}
void AdvantechCardsInterface::onTriggerCard4DO_OFFButtonClicked_5856()
{
    using namespace Automation::BDaq;

    if (instantDoCtrl4 == nullptr) {
        //        qDebug() << "DO controller is null!";
        return;
    }

    currentDOState = (USB_5856_enum) 32;

    uint8 allOff[4] = {0x00, 0x00, 0x00, 0x00};

    ErrorCode ret = instantDoCtrl4->Write(0, 4, allOff); // 4 ports = 32 bits
    if (BioFailed(ret)) {
        //        qDebug() << "DO write failed with error code:" << ret;
    } else {
        //        qDebug() << "All 32 DOs CARD4 turned OFF successfully.";
    }
}
//void AdvantechCardsInterface::onTriggerCard1AO_OFFButtonClicked_4716()
//{
//    using namespace Automation::BDaq;

//    if (instantAoCtrl1 == nullptr) {
//        qDebug() << "AO controller is null!";
//        return;
//    }

//    // uint8 allOff[4] = {0x00, 0x00, 0x00, 0x00};

//    ErrorCode ret = instantAoCtrl1->Write(0, 0.0);  // 4 ports = 32 bits
//    ErrorCode ret1 = instantAoCtrl1->Write(1, 0.0); // 4 ports = 32 bits

//    if (BioFailed(ret)) {
//        qDebug() << "AO write failed with error code:" << ret << ret1;
//    } else {
//        qDebug() << "All 2 AOs CARD1 turned OFF successfully.";
//    }
//}

void AdvantechCardsInterface::onTriggerCard2AO_OFFButtonClicked_4716()
{
    using namespace Automation::BDaq;

    if (instantAoCtrl2 == nullptr) {
        //        qDebug() << "AO controller is null!";
        return;
    }

    // uint8 allOff[4] = {0x00, 0x00, 0x00, 0x00};

    ErrorCode ret = instantAoCtrl2->Write(0, 0.0); // 4 ports = 32 bits
    //    ErrorCode ret1 = instantAoCtrl2->Write(1, 0.0); // 4 ports = 32 bits

    if (BioFailed(ret)) {
        //        qDebug() << "AO write failed with error code:" << ret << ret1;
    } else {
        //        qDebug() << "All 2 AOs CARD2 turned OFF successfully.";
    }
}

void AdvantechCardsInterface::InitializeDevice_uport() {}

void AdvantechCardsInterface::Initailization()
{
    //    qDebug() << "test 1";
    InitializeDevice_4716();
    InitializeDevice_5856();
    //InitializeDevice_uport();

    // QString SelfTestlog = "1\t10\t10.2\t0.5\t0.2\t" + QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
}

void AdvantechCardsInterface::logSelfTestText(const QString &text)
{
    emit newSelfTestlog(text);
}

void AdvantechCardsInterface::Rs422_CH1_CH2_ON_card3_5856()
{
    Automation::BDaq::uint8 portData = 0;

    //    Output_5856_Card_3.Output_CH30 = 1;
    instantDoCtrl3->WriteBit(3, 6, 1); // write to DO bit 0
    instantDoCtrl3->WriteBit(3, 7, 1); // write to DO bit 0
    QThread::msleep(DELAY);            // Wait
    Input_5856_Card_3.Input_CH30 = portData;
    instantDiCtrl3->ReadBit(3, 6, &portData);
    //    qDebug() << "!!!!!DO CH30 CH31:" << Output_5856_Card_3.Output_CH30;

    //    Output_5856_Card_3.Output_CH31 = 1;
    //    instantDoCtrl3->Write(3, (Output_5856_Card_3.Output_CH31 << 7)); // write to DO bit 0
    //    QThread::msleep(DELAY);                                          // Wait
    //    Input_5856_Card_3.Input_CH31 = portData;
    //    instantDiCtrl3->ReadBit(3, 7, &portData);
    //    qDebug() << "!!!!!DO CH31:" << Output_5856_Card_3.Output_CH31
    //             << ", DI CH31:" << static_cast<int>(Input_5856_Card_3.Input_CH31);
}

void AdvantechCardsInterface::Rs422_CH1_CH2_OFF_card3_5856()
{
    instantDoCtrl3->WriteBit(3, 6, 0); // write to DO bit 0
    instantDoCtrl3->WriteBit(3, 7, 0); // write to DO bit 0

    Output_5856_Card_3.Output_CH30 = 0;
    //    instantDoCtrl3->Write(3, (Output_5856_Card_3.Output_CH30 << 6)); // write to DO bit 0
    //    QThread::msleep(DELAY);                                          // Wait
    //    Input_5856_Card_3.Input_CH30 = portData;
    //    instantDiCtrl3->ReadBit(3, 6, &portData);
    //    qDebug() << "!!!!!DO CH31 30:" << Output_5856_Card_3.Output_CH30;
    //     << ", DI CH30:" << static_cast<int>(Input_5856_Card_3.Input_CH30);

    //    Output_5856_Card_3.Output_CH31 = 0;
    //    instantDoCtrl3->Write(3, (Output_5856_Card_3.Output_CH31 << 7)); // write to DO bit 0
    //    QThread::msleep(DELAY);                                          // Wait
    //    Input_5856_Card_3.Input_CH31 = portData;
    //    instantDiCtrl3->ReadBit(3, 7, &portData);
    //    qDebug() << "!!!!!DO CH31:" << Output_5856_Card_3.Output_CH31
    //             << ", DI CH31:" << static_cast<int>(Input_5856_Card_3.Input_CH31);
}

void AdvantechCardsInterface::LED_PS7_16V_ON_OFF(bool checked)
{
    Automation::BDaq::uint8 portData = 0;

    if (checked) {
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH17 = portData;
        //        qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);

        Output_5856_Card_4.Output_CH24 = 1;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH24 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(3, 0, &portData);
        Input_5856_Card_4.Input_CH24 = portData;
        //        qDebug() << "DO CH24:" << Output_5856_Card_4.Output_CH24
        //                 << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);

        Output_5856_Card_4.Output_CH24 = 0;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH24 << 0));
        QThread::msleep(DELAY);
        instantDiCtrl4->ReadBit(3, 0, &portData);
        Input_5856_Card_4.Input_CH24 = portData;
        //        qDebug() << "DO CH24:" << Output_5856_Card_4.Output_CH24
        //                 << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);

    } else {
        Output_5856_Card_4.Output_CH22 = 0;
        instantDoCtrl4->Write(2, (Output_5856_Card_4.Output_CH22 << 6));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(2, 1, &portData);
        Input_5856_Card_4.Input_CH22 = portData;
        //        qDebug() << "DO CH22:" << Output_5856_Card_4.Output_CH22
        //                 << ", DI CH17:" << static_cast<int>(Input_5856_Card_4.Input_CH17);

        Output_5856_Card_4.Output_CH25 = 1;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH25 << 1));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(3, 0, &portData);
        Input_5856_Card_4.Input_CH24 = portData;
        //        qDebug() << "DO CH24:" << Output_5856_Card_4.Output_CH25
        //                 << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);

        Output_5856_Card_4.Output_CH25 = 0;
        instantDoCtrl4->Write(3, (Output_5856_Card_4.Output_CH25 << 1));
        QThread::msleep(100);
        instantDiCtrl4->ReadBit(3, 0, &portData);
        Input_5856_Card_4.Input_CH24 = portData;
        //        qDebug() << "DO CH24:" << Output_5856_Card_4.Output_CH25
        //                 << ", DI CH24:" << static_cast<int>(Input_5856_Card_4.Input_CH24);
    }
}

QString AdvantechCardsInterface::getDeviceName() const
{
    return currentDevice;
}
InstantDoCtrl *AdvantechCardsInterface::getDoCtrl() const
{
    return instantDoCtrl2;
}

InstantDiCtrl *AdvantechCardsInterface::getDiCtrl() const
{
    return instantDiCtrl2;
}
bool AdvantechCardsInterface::isInitialized() const
{
    //    return instantDoCtrl2 && instantDiCtrl2->getInitialized();

    return doCtrl && doCtrl->getInitialized();
}
void AdvantechCardsInterface::dispose()
{
    //    if (instantDiCtrl2) {
    //        instantDiCtrl2->Dispose();
    //        instantDiCtrl2 = nullptr;
    //    }
    //    if (instantDoCtrl2) {
    //        instantDoCtrl2->Dispose();
    //        instantDoCtrl2 = nullptr;
    //    }
    //    currentDevice.clear();

    if (diCtrl) {
        diCtrl->Dispose();
        diCtrl = nullptr;
    }
    if (doCtrl) {
        doCtrl->Dispose();
        doCtrl = nullptr;
    }
    currentDevice.clear();
}

bool AdvantechCardsInterface::initialize(const QString &deviceName)
{
    //    qDebug() << "initialize.................";

    dispose();
    //        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

    // QThread::msleep(500);
    //    qDebug() << "@@@@@@@@@@@@@@@@@@@@@";

    diCtrl = InstantDiCtrl::Create();
    doCtrl = InstantDoCtrl::Create();
    currentDevice = deviceName;
    // qDebug() << "after device name.";

    if (!diCtrl || !doCtrl) {
        //  qDebug() << "[INIT FAIL] Controller creation failed.";
        return false;
    }

    DeviceInformation devInfo(deviceName.toStdWString().c_str());

    if (diCtrl->setSelectedDevice(devInfo) != Success
        || doCtrl->setSelectedDevice(devInfo) != Success) {
        //  qDebug() << "[INIT FAIL] setSelectedDevice failed for:" << deviceName;
        return false;
    }

    //  QThread::msleep(500); // Allow stabilization

    bool ready = diCtrl->getInitialized() && doCtrl->getInitialized();
    //    qDebug() << "[INIT]" << deviceName << "Init status:" << ready;
    return ready;
}

bool AdvantechCardsInterface::writeBit(int port, int bit, bool value)
{
    if (!doCtrl || !doCtrl->getInitialized()) {
        //        qDebug() << "[WRITE FAIL] DO not initialized.";
        return false;
    }

    ErrorCode err = doCtrl->WriteBit(port, bit, value ? 1 : 0);
    if (err != Success) {
        //        qDebug() << QString("[WRITE FAIL] Port %1 Bit %2 = %3, Err = %4 (enum %5)")
        //                        .arg(port)
        //                        .arg(bit)
        //                        .arg(value ? "ON" : "OFF")
        //                        .arg(err)
        //                        .arg(static_cast<int>(err));
        return false;
    }

    //    qDebug() << QString("***[WRITE OK] Port %1, Bit %2 = %3")
    //                    .arg(port)
    //                    .arg(bit)
    //                    .arg(value ? "ON" : "OFF");
    return true;
}

void AdvantechCardsInterface::updateConnectedCards()
{
    connectedDescriptions.clear();

    InstantDiCtrl *tempCtrl = InstantDiCtrl::Create();
    if (tempCtrl) {
        Array<DeviceTreeNode> *devices = tempCtrl->getSupportedDevices();
        for (int i = 0; i < devices->getCount(); ++i) {
            QString desc = QString::fromWCharArray(devices->getItem(i).Description);

            connectedDescriptions.insert(desc);
        }
        tempCtrl->Dispose();
    }
}

void AdvantechCardsInterface::isCardConnected(int bid)
{
    //    if (bid < 0 || bid >= 4) {
    //        emit USB_5856_Conn_STS_emit(bid, false);
    //    }

    QString deviceDesc = QString("USB-5856,BID#%1").arg(bid);
    DeviceInformation devInfo(deviceDesc.toStdWString().c_str());

    //    qDebug() << "deviceDesc" << deviceDesc;

    if (bid < 0 || bid >= 4) {
        emit USB_5856_Conn_STS_emit(deviceDesc, bid, false);
    }

    InstantDoCtrl *testCtrl = AdxInstantDoCtrlCreate();
    bool result = (testCtrl->setSelectedDevice(devInfo) == Success);
    testCtrl->Dispose();
    emit USB_5856_Conn_STS_emit(deviceDesc, bid, result);
}
