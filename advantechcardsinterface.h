#ifndef ADVANTECHCARDSINTERFACE_H
#define ADVANTECHCARDSINTERFACE_H

#include "QTimer"
#include "bdaqctrl.h"
#include "logger.h"
#include <QObject>
#include <QSet>
#include <QString>
#include <QVector>
using namespace Automation::BDaq;

//static_assert(true, "Dummy static assert"); // dummy declaration, ends the preamble
#pragma pack(push, 1)
typedef struct
{
    uint8_t Input_CH0 : 1;
    uint8_t Input_CH1 : 1;
    uint8_t Input_CH2 : 1;
    uint8_t Input_CH3 : 1;
    uint8_t Input_CH4 : 1;
    uint8_t Input_CH5 : 1;
    uint8_t Input_CH6 : 1;
    uint8_t Input_CH7 : 1;
    uint8_t Input_CH8 : 1;
    uint8_t Input_CH9 : 1;
    uint8_t Input_CH10 : 1;
    uint8_t Input_CH11 : 1;
    uint8_t Input_CH12 : 1;
    uint8_t Input_CH13 : 1;
    uint8_t Input_CH14 : 1;
    uint8_t Input_CH15 : 1;
    uint8_t Input_CH16 : 1;
    uint8_t Input_CH17 : 1;
    uint8_t Input_CH18 : 1;
    uint8_t Input_CH19 : 1;
    uint8_t Input_CH20 : 1;
    uint8_t Input_CH21 : 1;
    uint8_t Input_CH22 : 1;
    uint8_t Input_CH23 : 1;
    uint8_t Input_CH24 : 1;
    uint8_t Input_CH25 : 1;
    uint8_t Input_CH26 : 1;
    uint8_t Input_CH27 : 1;
    uint8_t Input_CH28 : 1;
    uint8_t Input_CH29 : 1;
    uint8_t Input_CH30 : 1;
    uint8_t Input_CH31 : 1;
} Input_5856;
#pragma pack(pop)

extern Input_5856 Input_5856_Card_1;

//(true, "Dummy static assert"); // dummy declaration, ends the preamble
#pragma pack(push, 1)
typedef struct
{
    uint8_t Output_CH0 : 1;
    uint8_t Output_CH1 : 1;
    uint8_t Output_CH2 : 1;
    uint8_t Output_CH3 : 1;
    uint8_t Output_CH4 : 1;
    uint8_t Output_CH5 : 1;
    uint8_t Output_CH6 : 1;
    uint8_t Output_CH7 : 1;
    uint8_t Output_CH8 : 1;
    uint8_t Output_CH9 : 1;
    uint8_t Output_CH10 : 1;
    uint8_t Output_CH11 : 1;
    uint8_t Output_CH12 : 1;
    uint8_t Output_CH13 : 1;
    uint8_t Output_CH14 : 1;
    uint8_t Output_CH15 : 1;
    uint8_t Output_CH16 : 1;
    uint8_t Output_CH17 : 1;
    uint8_t Output_CH18 : 1;
    uint8_t Output_CH19 : 1;
    uint8_t Output_CH20 : 1;
    uint8_t Output_CH21 : 1;
    uint8_t Output_CH22 : 1;
    uint8_t Output_CH23 : 1;
    uint8_t Output_CH24 : 1;
    uint8_t Output_CH25 : 1;
    uint8_t Output_CH26 : 1;
    uint8_t Output_CH27 : 1;
    uint8_t Output_CH28 : 1;
    uint8_t Output_CH29 : 1;
    uint8_t Output_CH30 : 1;
    uint8_t Output_CH31 : 1;

} Output_5856;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    QVector<double> averagedAi_test1;
    QVector<double> averagedAi_test2;
    QVector<double> averagedAi_test3;
    QVector<double> averagedAi_test4;
    QVector<double> averagedAi_test5;
    QVector<double> averagedAi_test6;
    QVector<double> averagedAi_test7;
    QVector<double> averagedAi_test8;
    QVector<double> averagedAi_test9;

    uint8_t test1Status[8];
    uint8_t test2Status[8];
    uint8_t test3Status[8];
    uint8_t test4Status[8];
    uint8_t test5Status[8];
    uint8_t test6Status[8];
    uint8_t test7Status[8];
    uint8_t test8Status[8];
    uint8_t test9Status[8];
} ADC_SelfTest;
#pragma pack(pop)

extern ADC_SelfTest g_ADC_SelfTest;
extern ADC_SelfTest g_ADC_Card2_BitTest;
//(true, "Dummy static assert"); // dummy declaration, ends the preamble
#pragma pack(push, 1)
typedef struct
{
    uint8_t USB_5856_Card1_STS : 1;
    uint8_t USB_5856_Card2_STS : 1;
    uint8_t USB_5856_Card3_STS : 1;
    uint8_t USB_5856_Card4_STS : 1;

} SelfTestStatus;

extern SelfTestStatus g_SelfTestStatus;
extern Output_5856 Output_5856_Card_1;
extern Output_5856 Output_5856_Card_2;
extern Output_5856 Output_5856_Card_3;
extern Output_5856 Output_5856_Card_4;

extern Input_5856 Input_5856_Card_1;
extern Input_5856 Input_5856_Card_2;
extern Input_5856 Input_5856_Card_3;
extern Input_5856 Input_5856_Card_4;
#pragma pack(pop)

#pragma pack(push, 1)
struct CardInitResult
{
    QString devicename;
    bool success;
    QString errorMessage;
};
#pragma pack(pop)

enum USB_5856_enum {

    DO0 = 0,
    DO1,
    DO2,
    DO3,
    DO4,
    DO5,
    DO6,
    DO7,
    DO8,
    DO9,
    DO10,
    DO11,
    DO12,
    DO13,
    DO14,
    DO15,
    DO16,
    DO17,
    DO18,
    DO19,
    DO20,
    DO21,
    DO22,
    DO23,
    DO24,
    DO25,
    DO26,
    DO27,
    DO28,
    DO29,
    DO30,
    DO31
};

//(true, "Dummy static assert"); // dummy declaration, ends the preamble
#pragma pack(push, 1)
typedef struct
{
    uint8_t Input_CH1 : 1;
    uint8_t Input_CH2 : 1;
    uint8_t Input_CH3 : 1;
    uint8_t Input_CH4 : 1;
    uint8_t Input_CH5 : 1;
    uint8_t Input_CH6 : 1;
    uint8_t Input_CH7 : 1;
    uint8_t Input_CH8 : 1;
    uint8_t Input_CH9 : 1;
    uint8_t Input_CH10 : 1;
    uint8_t Input_CH11 : 1;
    uint8_t Input_CH12 : 1;
    uint8_t Input_CH13 : 1;
    uint8_t Input_CH14 : 1;
    uint8_t Input_CH15 : 1;
    uint8_t Input_CH16 : 1;
    uint8_t Input_CH17 : 1;
    uint8_t Input_CH18 : 1;
    uint8_t Input_CH19 : 1;
    uint8_t Input_CH20 : 1;
    uint8_t Input_CH21 : 1;
    uint8_t Input_CH22 : 1;
    uint8_t Input_CH23 : 1;
    uint8_t Input_CH24 : 1;
    uint8_t Input_CH25 : 1;
    uint8_t Input_CH26 : 1;
    uint8_t Input_CH27 : 1;
    uint8_t Input_CH28 : 1;
    uint8_t Input_CH29 : 1;
    uint8_t Input_CH30 : 1;
    uint8_t Input_CH31 : 1;
    uint8_t Input_CH32 : 1;

} Input_4716;
#pragma pack(pop)

extern Input_4716 Input_4716_Card_1;
extern Input_4716 Input_4716_Card_2;
extern Input_4716 Input_4716_Card_3;
extern Input_4716 Input_4716_Card_4;

//(true, "Dummy static assert"); // dummy declaration, ends the preamble
#pragma pack(push, 1)
typedef struct
{
    uint8_t Output_CH1 : 1;
    uint8_t Output_CH2 : 1;
    uint8_t Output_CH3 : 1;
    uint8_t Output_CH4 : 1;
    uint8_t Output_CH5 : 1;
    uint8_t Output_CH6 : 1;
    uint8_t Output_CH7 : 1;
    uint8_t Output_CH8 : 1;
    uint8_t Output_CH9 : 1;
    uint8_t Output_CH10 : 1;
    uint8_t Output_CH11 : 1;
    uint8_t Output_CH12 : 1;
    uint8_t Output_CH13 : 1;
    uint8_t Output_CH14 : 1;
    uint8_t Output_CH15 : 1;
    uint8_t Output_CH16 : 1;
    uint8_t Output_CH17 : 1;
    uint8_t Output_CH18 : 1;
    uint8_t Output_CH19 : 1;
    uint8_t Output_CH20 : 1;
    uint8_t Output_CH21 : 1;
    uint8_t Output_CH22 : 1;
    uint8_t Output_CH23 : 1;
    uint8_t Output_CH24 : 1;
    uint8_t Output_CH25 : 1;
    uint8_t Output_CH26 : 1;
    uint8_t Output_CH27 : 1;
    uint8_t Output_CH28 : 1;
    uint8_t Output_CH29 : 1;
    uint8_t Output_CH30 : 1;
    uint8_t Output_CH31 : 1;
    uint8_t Output_CH32 : 1;

} Output_4716;
#pragma pack(pop)

extern Output_4716 Output_4716_Card_1;
extern Output_4716 Output_4716_Card_2;
extern Output_4716 Output_4716_Card_3;
extern Output_4716 Output_4716_Card_4;

//(true, "Dummy static assert"); // dummy declaration, ends the preamble
#pragma pack(push, 1)
typedef struct
{
    double Input_Ch6_16;
    double Input_Ch6_28;
    double Input_Ch6_32;
    double Input_ch6_Ext;
    double Input_Ch8;
    double Input_Ch9;
    double Input_Ch10;
    double Input_Ch11;
    double Input_Ch12;
    double Input_Ch13;
    double Input_Ch14;
    double Input_Ch15;

} Direct_Monitor;
#pragma pack(pop)
extern Direct_Monitor g_Direct_Monitor;

#pragma pack(push, 1)
typedef struct
{
    double CH_data[8];
    uint64_t time;
} ADC_BitTest;
#pragma pack(pop)
extern ADC_BitTest g_ADC_BitTest;

//#pragma pack(push, 1)
//typedef struct
//{
//    QVector<double> avg_ch1;
//    QVector<double> avg_ch2;
//    QVector<double> avg_ch3;
//    QVector<double> avg_ch4;
//    QVector<double> avg_ch5;
//    QVector<double> avg_ch6;
//    QVector<double> avg_ch7;
//    QVector<double> avg_ch8;
//    QVector<double> avg_ch9;

//    uint8_t ch1Status[8];
//    uint8_t ch2Status[8];
//    uint8_t ch3Status[8];
//    uint8_t ch4Status[8];
//    uint8_t ch5Status[8];
//    uint8_t ch6Status[8];
//    uint8_t ch7Status[8];
//    uint8_t ch8Status[8];
//    uint8_t ch9Status[8];
//} ADC_Card2_BitTest;
//#pragma pack(pop)

//extern ADC_Card2_BitTest g_ADC_Card2_BitTest;

#pragma pack(push, 1)
typedef struct
{
    uint8_t Header;
    uint8_t MessageID;
    uint8_t NoOfBytes;
    float curr_PS1;
    float curr_PS2;
    float curr_PS3;
    float curr_PS4;
    float curr_PS5;
    float curr_PS6;
    float curr_DC3p3;
    float curr_DCp5V;
    float curr_DCn5V;
    float curr_PS7;
    uint16_t CheckSum;
    uint16_t Footer;

} CurrentSensorData;
#pragma pack(pop)
extern CurrentSensorData g_CurrentSensorData;

class AdvantechCardsInterface : public QObject
{
    Q_OBJECT
public:
    AdvantechCardsInterface();
    ~AdvantechCardsInterface();
    // explicit AdvantechCardsInterface(QObject *parent = nullptr);

    bool initialize(const QString &deviceName);
    bool writeBit(int port, int bit, bool value);
    bool isInitialized() const;
    void dispose();
    void InitializeDevice_4716();
    void InitializeDevice_5856();
    void InitializeDevice_uport();
    void stopThread();

    QStringList logParts;

    QString getDeviceName() const;
    Automation::BDaq::InstantDoCtrl *getDoCtrl() const;
    Automation::BDaq::InstantDiCtrl *getDiCtrl() const;

    CardInitResult initializeCard_5856(const QString &deviceName,
                                       Automation::BDaq::InstantDiCtrl *&diCtrl,
                                       Automation::BDaq::InstantDoCtrl *&doCtrl);

    InstantAiCtrl *instantAiCtrl1;
    InstantAoCtrl *instantAoCtrl1;
    InstantDiCtrl *instantDiCtrl1_ADC;
    InstantDoCtrl *instantDoCtrl1_ADC;
    InstantDiCtrl *instantDiCtrl1;
    InstantDoCtrl *instantDoCtrl1;

    InstantAiCtrl *instantAiCtrl2;
    InstantAoCtrl *instantAoCtrl2;
    Automation::BDaq::InstantDiCtrl *instantDiCtrl2_ADC;
    Automation::BDaq::InstantDoCtrl *instantDoCtrl2_ADC;
    Automation::BDaq::InstantDiCtrl *instantDiCtrl2;
    Automation::BDaq::InstantDoCtrl *instantDoCtrl2;

signals:
    void adcCard2Result(bool pass);

    void finished();
    void card2FailureDetected();
    void signalCard1StatusReady_5856(const QString &status, const QString &status1);
    void signalCard2StatusReady_5856(const QString &status, const QString &status2);
    void signalCard3StatusReady_5856(const QString &status, const QString &status3);
    void signalCard4StatusReady_5856(const QString &status, const QString &status4);
    void newSelfTestlog(const QString &text);
    void USB_5856_cards_status_signal(
        int value1, int value2, int value3, int value4, const QString &devicename);

    void USB_4716_cards_status_signal(const QString &Dev_Info_4716);
    void testSignal_1();

    void aoAiUpdated(double aoVoltage, const QVector<double> &aiValues);

    void USB_5856_Conn_STS_emit(const QString &Devicename, int value, bool status);
    void SRU_CTRL_AUTO_emit();

private slots:
    bool CheckAndSetDO(InstantDoCtrl *instantDoCtrl1,
                       InstantDiCtrl *instantDiCtrl1,
                       int Writeport,
                       int Readport,
                       uint8_t Outputs,
                       uint8_t readbyte_position,
                       uint32_t &Input_CH1,
                       USB_5856_enum value,
                       USB_5856_enum &currentDOState,
                       uint8_t latchRelay);

public slots:
    void start();
    void stop();
    //    void display1();
    //    void call_thread();
    void Initailization();
    void onTriggerCard1DO_ONButtonClicked_5856(); // ✅ Slot to be connected to UI
    void onTriggerCard2DO_ONButtonClicked_5856(); // ✅ Slot to be connected to UI
    void onTriggerCard3DO_ONButtonClicked_5856(); // ✅ Slot to be connected to UI
    void onTriggerCard4DO_ONButtonClicked_5856(); // ✅ Slot to be connected to UI

    void onTriggerCard1DO_OFFButtonClicked_5856();
    void onTriggerCard2DO_OFFButtonClicked_5856();
    void onTriggerCard3DO_OFFButtonClicked_5856();
    void onTriggerCard4DO_OFFButtonClicked_5856();

    // void onTriggerCard1AO_OFFButtonClicked_4716();
    void onTriggerCard2AO_OFFButtonClicked_4716();

    void onTriggerDIButtonClicked_5856();

    void onTriggerCard1AIButtonClicked();
    void onTriggerCard1AOButtonClicked();
    void onTriggerCard1DIButtonClicked();
    void onTriggerCard1DOButtonClicked();

    void onTriggerCard1AO_refresh();
    void onTriggerCard1AI_refresh();
    void onTriggerCard2AOButtonClicked();
    void onTriggerCard2AO_refresh();
    void onTriggerCard2AI_refresh();
    void onTriggerCard2AIButtonClicked();
    void onTriggerCard2DOButtonClicked();
    void onTriggerCard2DIButtonClicked();
    void onTriggerCard2ADCCheck_4716();

    void logSelfTestText(const QString &text);
    void PS1_28V_Source_from_Power_Card();
    void PS2_12V_Source_from_Power_Card();

    void PS3_5V_Source_from_Power_Card();

    void LED_5856_ON_PS1_28V(bool value);
    void LOAD_MEASURMENT_PS1_28V(bool value);

    void LOAD_MEASURMENT_PS2_12V(bool value);
    void LED_5856_USB_HUB_PS2_12V(bool value);

    void LOAD_MEASURMENT_5856_PS3_5V(bool value);

    void LOAD_MEASURMENT_5856_PS4(bool value);
    void LED_5856_CNTRL_CARDS_PS4(bool value);

    void LOAD_MEASURMENT_5856_PS5_5V(bool value);
    void PS5_plus_5_Voltage_monitor();
    void PS5_Negative_5_Voltage_monitor();
    void DC_DC_Negative_5_Voltage_monitor();
    void DC_DC_5_Voltage_monitor();
    void DC_DC_3p3_Voltage_monitor();

    //void PS6_minus_Voltage_monitor();

    void PS7_16V_28V_32V_Source_from_Power_Card(int index);

    void PS4_3_3_Voltage_Monitor();

    void LED_ON_OFF_CCARDS_PS5_plus_5V(bool value);
    void LOAD_MEASURMENT_PS6_minus_5V(bool value);
    void LED_ON_CCARDS_PS6_minus5V(bool value);
    void Font_panel_load_on_PS7(bool value);
    void PS7_Power_on_LRU(int index);

    void SRU_MUX_28V();

    void read4716_Differential_CH0_CH1(double arr[2]);
    double Differential_mode_resistance_SET1();
    double Differential_mode_resistance_SET2();
    double Differential_mode_resistance_SET3();
    double Differential_mode_resistance_SET4();
    void Check_Highest_Resistance();

    void SRU_MUX_3_3V();
    void SRU_MUX_plus_5V();
    void SRU_MUX_minus_5V();
    void SRU_MUX_plus_5V_Output();
    void SRU_MUX_minus_5V_Output();
    void SRU_MUX_3_3V_Output();
    void SRU_CNTRLC_3_3_Output();
    void SRU_CNTRLC_MINUS_4_6_Output();
    void SRU_CNTRLC_PLUS_4_6_Output();
    void LRU_INPUT();

    void DC_CARD_5V_LOAD_MEASUREMENT_10_percent(bool checked);
    void DC_CARD_5V_LOAD_MEASUREMENT_100_percent(bool checked);
    void DC_CARD_MINUS_5V_LOAD_MEASUREMENT_10_percent(bool checked);
    void DC_CARD_MINUS_5V_LOAD_MEASUREMENT_100_percent(bool checked);
    void DC_CARD_3_3V_LOAD_MEASUREMENT_10_percent(bool checked);
    void DC_CARD_3_3V_LOAD_MEASUREMENT_100_percent(bool checked);
    void DAC_VOLTAGE_DAC_CH1();
    void ADC_CARD_read4716_SingleEnded_CH1_to_CH8();

    void handleAbortSwitch(bool value);
    void handlePREP_Switch(bool value);
    void handleREADY_INIT_Switch(bool value);
    void handleDISCRETE_IN_CH1(bool value);
    void handleDISCRETE_IN_CH2(bool value);
    void handleDISCRETE_IN_CH3(bool value);
    void handleDISCRETE_OUT_CH1(bool value);
    void handleDISCRETE_OUT_CH2(bool value);
    void handleDISCRETE_OUT_CH3(bool value);
    void handleDISCRETE_OUT_CH4(bool value);
    void handleDISCRETE_OUT_CH5(bool value);
    void handleTPS_D1_1(bool value);
    void handleTPS_D1_2(bool value);
    void handleTPS_D1_3(bool value);
    void handleTPS_D1_4(bool value);
    void handleTPS_D1_5(bool value);
    void handleTPS_D1_6(bool value);
    void handleTPS_D1_7(bool value);
    void handleTPS_D1_8(bool value);
    void handleTPS_D1_9(bool value);
    void handleTPS_D1_10(bool value);

    void handleTPS_D2_1(bool value);
    void handleTPS_D2_2(bool value);
    void handleTPS_D2_3(bool value);
    void handleTPS_D2_4(bool value);
    void handleTPS_D2_5(bool value);
    void handleTPS_D2_6(bool value);
    void handleTPS_D2_7(bool value);
    void handleTPS_D2_8(bool value);
    void handleTPS_D2_9(bool value);
    void handleTPS_D2_10(bool value);

    void handleTPS_D3_1(bool value);
    void handleTPS_D3_2(bool value);
    void handleTPS_D3_3(bool value);
    void handleTPS_D3_4(bool value);
    void handleTPS_D3_5(bool value);
    void handleTPS_D3_6(bool value);
    void handleTPS_D3_7(bool value);
    void handleTPS_D3_8(bool value);
    void handleTPS_D3_9(bool value);
    void handleTPS_D3_10(bool value);

    void voltages_16_28_32_OFF();

    void Rs422_CH1_CH2_ON_card3_5856();
    void Rs422_CH1_CH2_OFF_card3_5856();

    void LED_PS7_16V_ON_OFF(bool checked);

    void ADC_CARD2_CH1_to_CH8();

    //    bool isCardConnected(int index) const;

    void updateConnectedCards();

    void handleDISCRETE_IN_OFF_CH();

    void USB_4716_DisplayC1(bool value);
    void USB_4716_DisplayC2(bool value);
    void USB_4716_DisplayC3(bool value);
    void USB_4716_DisplayCTRL_8421(uint16_t value);

    void isCardConnected(int bid);

    void DC_CARD_5V_InitialValues_LED_Ripple(bool checked);

    void DC_CARD_MINUS_5V_InitialValues_LED_Ripple(bool checked);
    void DC_CARD_3_3V_InitialValues_LED_Ripple(bool checked);
    void read4716_Diff_CH0_CH1(double *arr);

    void DIS_OUT_Read_USB_Card_5856();

private:
    std::atomic<bool> running{true};
    // Declare your helper function
    //bool initialize_4716_card(const QString &deviceName,
    CardInitResult initializeCard_4716(const QString &deviceName,

                                       Automation::BDaq::InstantAiCtrl *&aiCtrl,
                                       Automation::BDaq::InstantDiCtrl *&diCtrl,
                                       Automation::BDaq::InstantAoCtrl *&aoCtrl,
                                       Automation::BDaq::InstantDoCtrl *&doCtrl);

    InstantAiCtrl *instantAiCtrl3;
    InstantAoCtrl *instantAoCtrl3;
    InstantDiCtrl *instantDiCtrl3;
    InstantDoCtrl *instantDoCtrl3;

    InstantAiCtrl *instantAiCtrl4;
    InstantAoCtrl *instantAoCtrl4;
    InstantDiCtrl *instantDiCtrl4;
    InstantDoCtrl *instantDoCtrl4;

    int currentChannelIndex1 = 0;

    QTimer *checkTimer1_5856 = nullptr;

    QTimer *checkTimer2_5856 = nullptr;
    int currentChannelIndex2 = 0;

    QTimer *checkTimer3_5856 = nullptr;
    int currentChannelIndex3 = 0;

    QTimer *checkTimer4_5856 = nullptr;
    int currentChannelIndex4 = 0;

    void checkNextChannelCard1_5856();
    void checkNextChannelCard2_5856();
    void checkNextChannelCard3_5856();
    void checkNextChannelCard4_5856();

    quint32 card1ChannelStatus_5856 = 0;

    quint32 doStatus_5856 = 0;
    quint32 diStatus_5856 = 0;

    USB_5856_enum currentDOState;

    QString currentDevice;

    Automation::BDaq::InstantDoCtrl *doCtrl;
    Automation::BDaq::InstantDiCtrl *diCtrl;
    QSet<QString> connectedDescriptions; // Stores connected device descriptions
};

#endif // ADVANTECHCARDSINTERFACE_H
