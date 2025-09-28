#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "advantechcardsinterface.h"
#include "bdaqctrl.h"
#include "crcutility.h"
#include "qserialwork_uport.h"
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>

#include "qcombobox.h"
#include "qtablewidget.h"
#include <QAxObject>

using namespace Automation::BDaq;

//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/qserialportinfo.h>
#include "hellothread.h"
#include "niScope.h"
#include "qserialwork.h"
#include "signalgenerator.h"
#include "testpointdataframming.h"
#include <stdio.h>
#include <QDateTime>
#include <QFileDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QTimer>
//#include <QByteArray>
//#include <cstring> // For memcpy

#include "graphwidget.h"
#include "qcustomplot.h"
#include "qserialwork_bittest.h"
#include "qserialwork_currentsensor.h"
#include "qvector.h"
#include <QButtonGroup>

#define NUM_OF_DWORDS 7

#define GUI_VERSION 0.1
#define MANUAL_MODE 3
#define AUTOMATIC_MODE 4
#define STAY_IN_BOOTLOADER_MODE 5
#define CONTROLLER_IN_BOOTMODE 6
#define ERR_MSG_NO_RESPONSE 7
#define APPLICATION_CODE 8
#define BOOTLOADER_CODE 9
#define UC_FLASH_ERASE 10
#define UC_ERASE 11
#define UC_FLASH_ERASE_SUCCESS 12
#define UC_FLASH_ERASE_FAIL 13
#define APPLICATION_DATA 14
#define APP_WR_DATA_PKT_ACK_PASS 15
#define APP_WR_DATA_PKT_ACK_FAIL 16
#define APP_WRT_TIMEOUT 17
#define APP_SIG_DWORD 18
#define APP_SIG_DWORD_WR_PASS 19
#define APP_SIG_DWORD_WR_FAIL 20
#define APP_SIG_WRT_TIMEOUT 21
#define APP_CRC_VERIFY 22
#define APP_CRC_WRT_TIMEOUT 23
#define ACK_TP_PKT_ID 25
#define TP_CONFIG_ID 26
#define WAVEFORM_DISPLAY_ID 27
#define WAVEFORM_CONFIG_ID 28
#define ACK_WAVEFORM_CONFIG_ID 29
#define SEND_TP_PKT_ID 30
#define EXT_FLASH_ERASE 31
#define EXT_FLASH_ERASE_SUCESS 32
#define EXT_FLASH_ERASE_FAIL 33
#define EXT_FLASH_NOT_EMPTY 34
#define CRC_CHECK_FAIL 35
#define READ_EXT_FLASH 36
#define READ_EXT_FLASH_DATA 37
#define EXT_FLASH_CRC 38
#define EXT_FLASH_CRC_TX 39
#define ABORT_SWITCH 40
#define PREP_SWITCH 41
#define READY_INIT_SWITCH 42
#define DISCRETE_IN_CH1 43
#define DISCRETE_IN_CH2 44
#define DISCRETE_IN_CH3 45
#define DISCRETE_OUT_CH1 46
#define DISCRETE_OUT_CH2 47
#define DISCRETE_OUT_CH3 48
#define DISCRETE_OUT_CH4 49
#define DISCRETE_OUT_CH5 50
#define TPS_D1_1 51
#define TPS_D1_2 52
#define TPS_D1_3 53
#define TPS_D1_4 54
#define TPS_D1_5 55
#define TPS_D1_6 56
#define TPS_D1_7 57
#define TPS_D1_8 58
#define TPS_D1_9 59
#define TPS_D1_10 60
#define TPS_D2_1 61
#define TPS_D2_2 62
#define TPS_D2_3 63
#define TPS_D2_4 64
#define TPS_D2_5 65
#define TPS_D2_6 66
#define TPS_D2_7 67
#define TPS_D2_8 68
#define TPS_D2_9 69
#define TPS_D2_10 70
#define TPS_D3_1 71
#define TPS_D3_2 72
#define TPS_D3_3 73
#define TPS_D3_4 74
#define TPS_D3_5 75
#define TPS_D3_6 76
#define TPS_D3_7 77
#define TPS_D3_8 78
#define TPS_D3_9 79
#define TPS_D3_10 80
#define CURRENT_SENSOR 81
#define BITTEST 82
#define MOXA_Tx_1_RX_2 83
#define MOXA_Tx_2_RX_1 84
#define LRU_ADC_BIT_TEST 85
#define LRU_RS422_BIT_TEST 86
#define LRU_MOM_ROT_BIT_TEST 87
#define LRU_DIS_OUTS_BIT_TEST 88
#define LRU_DIS_INS_BIT_TEST 89
#define LRU_CRC_BIT_TEST 90
#define LRU_POST_STATUS_BIT_TEST 91
#define SRUCTRL_Rx1 92
#define SRUCTRL_Rx2 93
#define SRU_DIS_OUT1_STS 94
#define SRU_DIS_OUT2_STS 95
#define SRU_DIS_OUT3_STS 96
#define SRU_DIS_OUT4_STS 97
#define SRU_DIS_OUT5_STS 98
#define SRU_DIS_IN1_STS 99
#define SRU_DIS_IN2_STS 100
#define SRU_DIS_IN3_STS 101
#define SRU_ROT1_STS 102
#define SRU_ROT2_STS 103
#define SRU_ROT3_STS 104
#define SRUCTRL_Rx1_PAT2 105
#define SRUCTRL_Rx2_PAT2 106
#define BIT_TEST_USB_PORT_P1 107
#define BIT_TEST_USB_PORT_P2 108
#define BIT_TEST_RS422_CH2_P1 109
#define BIT_TEST_RS422_CH2_P2 110
#define NUMBER_OF_PAGES 191
#define SELF_TEST_16V 192
#define SELF_TEST_28V 193
#define SELF_TEST_32V 194
#define SELF_TEST_EXT_V 195
#define SELF_TEST_OFF 196
#define RIPPLE_P5V_DELAY 197
#define RIPPLE_N5V_DELAY 198
#define RIPPLE_P3P3V_DELAY 199
#define SRU_DIP1 200
#define SRU_DIP2 201
#define SRU_DIP3 202
#define SRU_DIP4 203
#define SRU_DIP5 204

#define MAX_BLOCK_SIZE (4096)
#define MAX_FW_SIZE (MAX_BLOCK_SIZE * NUMBER_OF_PAGES)

/* -------- Public types -------- */
#pragma pack(push, 1)
typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
} Time_counter;
#pragma pack(pop)
extern Time_counter g_Time_counter;

#pragma pack(push, 1)
typedef struct
{
    float *buf;        /* user-allocated circular buffer              */
    uint16_t capacity; /* maximum number of samples (window length)   */
    uint16_t head;     /* write position                               */
    uint16_t count;    /* current number of valid samples              */
    float sum;         /* running sum for O(1) average                 */
} RunningAverage;
#pragma pack(pop)
extern RunningAverage g_RunningAverage;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint8_t packetCount;
    float voltage;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} ADC_BIT_TEST;
#pragma pack(pop)
extern ADC_BIT_TEST g_ADC_BIT_TEST;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint16_t packetSize; //2
    uint8_t payload[1024];
    uint16_t CRC_WORD; //2
    uint16_t EndMsg;   //2
} RS422_TestPacket;
#pragma pack(pop)
extern RS422_TestPacket g_RS422_TestPacket;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint16_t InternalFlash_CRC;
    uint16_t ExternalFlash_CRC;
    uint16_t ExternalFlash_CRC2;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} CRC_BIT_TEST;
#pragma pack(pop)
extern CRC_BIT_TEST g_CRC_BIT_TEST;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint8_t Dis_out_CH1_Sts : 1;
    uint8_t Dis_out_CH2_Sts : 1;
    uint8_t Dis_out_CH3_Sts : 1;
    uint8_t Dis_out_CH4_Sts : 1;
    uint8_t Dis_out_CH5_Sts : 1;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} DIS_OutputsBIT_TEST;
#pragma pack(pop)
extern DIS_OutputsBIT_TEST g_DIS_OutputsBIT_TEST;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint8_t Dis_IN_CH1_Sts : 1;
    uint8_t Dis_IN_CH2_Sts : 1;
    uint8_t Dis_IN_CH3_Sts : 1;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} DIS_InputsBIT_TEST;
#pragma pack(pop)
extern DIS_InputsBIT_TEST g_DIS_InputsBIT_TEST;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint8_t Abort_Status : 1;
    uint8_t Ready_Init_Status : 1;
    uint8_t Prep_Status : 1;
    uint16_t Rotary_Update;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} Momentary_Switch_Status;
#pragma pack(pop)
extern Momentary_Switch_Status g_Momentary_Switch_Status;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class AdvantechCardsInterface; // Forward declaration for AdvantechManager

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //    MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // void on_Generate_Report_clicked();

    //    void on_SCOPE_pushButton_clicked();
    QStringList logBit;

signals:

    void deviceConnected(const QString &portName);
    void deviceDisconnected(const QString &portName);
    qint64 serialWrite(const char *buf, qint64 len);
    qint64 Moxa_Port1_serialWrite(const char *buf, qint64 len);
    qint64 Moxa_Port2_serialWrite(const char *buf, qint64 len);
    void sig_serialPort_Close();
    void Moxa_port1_sig_serialPort_Close();
    void Moxa_port2_sig_serialPort_Close();
    void LoadWaveform_into_GUI();
    void directorySelected(QString directory);
    void sigTransferInit();
    void Stop_TP();
    void sigWaveformProcess();
    void ADV_InitailizationSignal();
    void SRU_CTRL_USB_Write(const char *buf, qint64 len);
    void card1Signal_ON();
    void card1Signal_OFF();
    void card2Signal_ON();
    void card2Signal_OFF();
    void card3Signal_ON();
    void card3Signal_OFF();
    void card4Signal_ON();
    void card4Signal_OFF();

    // void adcCard2Result();
    void adcCard2TriggerSignal();
    void USB_5856_Conn_STS_Signal(int value);

    void ADC_4716card2Signal();
    void ADC_4716card2Signal_OFF();

    void RS422_card1Signal_ON();
    void RS422_card1Signal_OFF();
    void ps1_VM();
    void ps3_VM();
    void ps4_VM();
    void ps5_plus5_VM();
    void ps6_minus5_VM();
    void PS7_VM(int index);
    void LED_PS4_Sig(bool checked);
    void LED_PS5_Sig(bool checked);
    void LED_PS6_Sig(bool checked);
    void LED_PS7_Sig(bool checked);
    void PS7_Sig(int index);
    void ADC_BitTest_Sig();

    void LED_PS1_Sig_MT(bool checked);
    void LED_PS2_Sig_MT(bool checked);
    void LED_PS3_Sig_MT(bool checked);
    void LED_PS4_Sig_MT(bool checked);
    void LED_PS5_Sig_MT(bool checked);
    void LED_PS6_Sig_MT(bool checked);
    void LED_PS7_Sig_MT(bool checked);

    void DC_DC_3p3_SRU();
    void DC_DC_5_SRU();
    void DC_DC_N_5_SRU();
    void DC_DC_5_LED_Ripple(bool checked);
    void DC_DC_5_L_10PER(bool checked);
    void DC_DC_5_L_100PER(bool checked);
    void DC_DC_N_5_L_10PER(bool checked);
    void DC_DC_N_5_L_100PER(bool checked);
    void DC_DC_3p3_L_10PER(bool checked);
    void DC_DC_3p3_L_100PER(bool checked);
    void DC_DC_N_5_LED_Ripple(bool checked);
    void DC_DC_3p3_LED_Ripple(bool checked);
    void DC_DC_N_5_Differential(double *arr);
    void DIS_OUT_Read_USB_Card();
    void Discrete_Input_Ch1(bool checked);
    void Discrete_Input_Ch2(bool checked);
    void Discrete_Input_Ch3(bool checked);
    void Discrete_IN_OFF();
    void card();
    void Display_Digit1(bool checked);
    void Display_Digit2(bool checked);
    void Display_Digit3(bool checked);
    void Display_Dial1(uint16_t value);
    void SRU_AbortSwitch(bool checked);
    void SRU_PrepSwitch(bool checked);
    void SRU_ReadyInitSwitch(bool checked);

    void SRU_TPS_D1_Sig_1(bool checked);
    void SRU_TPS_D1_Sig_2(bool checked);
    void SRU_TPS_D1_Sig_3(bool checked);
    void SRU_TPS_D1_Sig_4(bool checked);
    void SRU_TPS_D1_Sig_5(bool checked);
    void SRU_TPS_D1_Sig_6(bool checked);
    void SRU_TPS_D1_Sig_7(bool checked);
    void SRU_TPS_D1_Sig_8(bool checked);
    void SRU_TPS_D1_Sig_9(bool checked);
    void SRU_TPS_D1_Sig_10(bool checked);

    void SRU_TPS_D2_Sig_1(bool checked);
    void SRU_TPS_D2_Sig_2(bool checked);
    void SRU_TPS_D2_Sig_3(bool checked);
    void SRU_TPS_D2_Sig_4(bool checked);
    void SRU_TPS_D2_Sig_5(bool checked);
    void SRU_TPS_D2_Sig_6(bool checked);
    void SRU_TPS_D2_Sig_7(bool checked);
    void SRU_TPS_D2_Sig_8(bool checked);
    void SRU_TPS_D2_Sig_9(bool checked);
    void SRU_TPS_D2_Sig_10(bool checked);

    void SRU_TPS_D3_Sig_1(bool checked);
    void SRU_TPS_D3_Sig_2(bool checked);
    void SRU_TPS_D3_Sig_3(bool checked);
    void SRU_TPS_D3_Sig_4(bool checked);
    void SRU_TPS_D3_Sig_5(bool checked);
    void SRU_TPS_D3_Sig_6(bool checked);
    void SRU_TPS_D3_Sig_7(bool checked);
    void SRU_TPS_D3_Sig_8(bool checked);
    void SRU_TPS_D3_Sig_9(bool checked);
    void SRU_TPS_D3_Sig_10(bool checked);

    void UsbI2C_Thread_InitailizationSignal();

private slots:
    //    void onCard2ADCResult(bool pass);

    void on_actionAbout_triggered();

    void on_OpenPort_toggled(bool checked);

    void M_SerialAboutToClose();

    void M_SerialErrorOccurred(QSerialPort::SerialPortError error);

    void on_SAVE_clicked();

    void on_OpenSavedFile_clicked();

    void on_ClearButton_clicked();

    void on_Browse_clicked();

    void on_Connect_to_UC_clicked();

    void ADC_BitTestTimer();

    void SRU_ADC_DAC_Loop_Back();

    void on_EraseFlash_clicked();

    void TimeOutTimer_Indications();

    void on_Download_HexFile_clicked();

    void AppCRC_Verify();

    void on_OpenWaveFormGenerator_clicked();

    void checkDevices();

    void SerialConnected(const QString &portName);

    void SerialDisconnected(const QString &portName);

    void on_LoadWaveform_inti_GUI_clicked();

    void updateFromTestPoint(uint16_t counter, int testPointNum, QString TestPointfileName, bool ok);

    void onRequestDirectorySelection();

    //    void on_TransferTestPointData_clicked();

    void sendTP_data_to_UC();

    void on_GraphSave_clicked();

    void on_GraphStop_toggled(bool checked);

    QString findSTM32Port();

    void on_TransferTestPointData_clicked();

    void on_EraseExtFlash_clicked();

    void on_ReadDataFromFlash_clicked();

    void on_USB_5856_AE_Card1_pb_clicked(bool checked);

    void on_USB_5856_AE_Card2_pb_clicked(bool checked);

    void on_USB_5856_AE_Card3_pb_clicked(bool checked);

    void on_USB_5856_AE_Card4_pb_clicked(bool checked);

    void on_USB_4716_AE_CARD2_pb_clicked(bool checked);

    void on_REPORT_pb_clicked();

    //    void handleSerialMessage(const QByteArray &message);
    void handleSerialError(QSerialPort::SerialPortError error);
    void handleSerialClose();
    void onSerialDataReceived(const QByteArray &data);

    void on_RS422_LOOP_BACK_pb_1_clicked(bool checked);
    void on_RS422_LOOP_BACK_pb_2_clicked(bool checked);

    void SelfTest_StatusUpdate();

    // void on_Volt_12_pb_toggled(bool checked);

    void on_Volt_5_pb_clicked(bool checked);

    void on_Volt_3_3_pb_clicked(bool checked);

    void on_Volts_plus_5_pb_clicked();

    void on_Volts_minus_5_pb_clicked(bool checked);

    //  void on_Volt_28_16_32_pb_toggled(bool checked);

    void on_USB_5132_OSCILLOSCOPE_CARD_pb_toggled(bool checked);

    void on_Volt_28_16_32_Cmb_currentIndexChanged(int index);

    void on_LED_DISPLAY_STATUS_pb_toggled(bool checked);

    void on_refreshButton_clicked();

    //    void on_MVoltage_pb_toggled(bool checked);

    //    void on_Discrete_Input_Ch1_pb_toggled(bool checked);

    void on_LRU_VoltagePB_toggled(bool checked);

    void on_Volt_28_pb_clicked();

    void onCard2ADCResult(bool pass);

    void on_RESTORE_clicked();

    void on_Bittest_Start_Pb_toggled(bool checked);

    void on_Discrete_Inputs_Pb_toggled(bool checked);

    void on_FTU_BitTest_Report_clicked();

    void on_bittest_refresh_pb_clicked();

    void checkUsb5856Status();
    void checkUsb4716Status();
    void checkUsb5132Status(bool initial = false);
    //    void showNextPopup();

    void on_Display_Card_Dial1_valueChanged(int value);
    void on_DISPLAY_C2_pb_clicked(bool checked);

    void on_DISPLAY_C3_pb_clicked(bool checked);

    void on_Display_Card_Dial2_valueChanged(int value);

    void on_Display_Card_Dial3_valueChanged(int value);

    void on_Auto_mode_rb_clicked();

    void on_Manual_mode_rb_clicked();

    void on_Start_PB_clicked();

    void on_Emergency_Stop_PB_clicked();
    void USB_5856_Conn_Status(const QString &Devicename, int value, bool status);
    void USB_5856_cards_status(
        int value1, int value2, int value3, int value4, const QString &devicename);

    void USB_4716_cards_status(const QString &Dev_Info_4716);

    void on_SRU_DC_5V_IV_PB_clicked(bool checked);

    void on_DC_DC_Card__DISP_PB_clicked(bool checked);

    void on_CTRL_Card_PB_clicked(bool checked);

    void on_SRU_DC_5V_L10_PB_clicked(bool checked);
    void Volage_5V_Combine(bool checked);

    void on_SRU_DC_5V_L100_PB_clicked(bool checked);

    void on_SRU_DC_N_5V_IV_PB_clicked(bool checked);

    void on_SRU_DC_N_5V_L10_PB_clicked(bool checked);

    void on_SRU_DC_N_5V_L100_PB_clicked(bool checked);

    void on_SRU_DC_3p3V_IV_PB_clicked(bool checked);

    void on_SRU_DC_3p3V_L10_PB_clicked(bool checked);

    void on_SRU_DC_3p3V_L100_PB_clicked(bool checked);

    //void on_SRU_Volts_CB_currentIndexChanged(int index);

    void on_SRU_CTRL_Volt_pb_clicked(bool checked);

    void on_CC_Ch1_TX_pb_clicked(bool checked);

    void on_CC_Ch2_TX_pb_clicked(bool checked);

    void on_CC_PropSwitch_Pb_clicked(bool checked);

    void on_CC_InitSwitch_pb_clicked(bool checked);

    void on_CC_AbortSwitch_Pb_clicked(bool checked);

    void on_CC_Discrete_ch1_OP_pb_clicked(bool checked);

    void on_CC_Discrete_ch2_OP_pb_clicked(bool checked);

    void on_CC_Discrete_ch3_OP_pb_clicked(bool checked);

    void on_CC_Discrete_ch4_OP_pb_clicked(bool checked);

    void on_CC_Discrete_ch5_OP_pb_clicked(bool checked);

    void on_CC_Discrete_ch1_IP_pb_clicked(bool checked);

    void on_CC_Discrete_ch2_IP_pb_clicked(bool checked);

    void on_CC_Discrete_ch3_IP_pb_clicked(bool checked);

    void on_RotarySwitch1_pb_clicked(bool checked);

    void on_RotarySwitch2_pb_clicked(bool checked);

    void on_RotarySwitch3_pb_clicked(bool checked);

    void on_refresh_SRU_CC_pb_clicked();

    void on_SRU_DCDC_REPORT_clicked();

    void on_SRU_CntrlCard_Report_clicked();

    void on_SRU_ExternalFlash_pb_clicked();

    void on_USB_port_clicked(bool checked);

    void on_SRU_VoltagePB_toggled(bool checked);

    void on_SRU_Start_pb_toggled(bool checked);

    void on_Open_Oscilloscope_PB_clicked();

    void on_PS1_28V_pb_clicked(bool checked);

    void on_PS2_12_pb_clicked(bool checked);

    void on_PS3_5V_pb_clicked(bool checked);

    void on_PS4_3p3V_pb_clicked(bool checked);

    void on_PS5_plus5V_pb_clicked(bool checked);

    void on_PS6_N_5V_pb_clicked(bool checked);

    void on_PS7_External_V_pb_clicked(bool checked);

    void on_RS422_ch1_pb_clicked(bool checked);

    void onTable1CellClicked(int row, int column);
    void onTable2CellClicked(int row, int column);
    void onTable3CellClicked(int row, int column);
    void onTable4CellClicked(int row, int column);
    void onTable5CellClicked(int row, int column);
    void onTable6CellClicked(int row, int column);
    void adjustTableToLayoutSize(QTableWidget *table);
    void importExcelToMultipleTables();
    void exportAllTablesToExcel();

    void on_Generate_Pbtn_clicked();
    void saveWaveformTableDataToBinFile();

    void on_Ripple_N5V_pb_clicked();

    void on_Ripple_3p3V_pb_clicked();

    void on_DCDC_CTRL_Auto_RB_clicked();

    void on_DCDC_Manual_RB_clicked();

    void on_refresh_SRU_DC_pb_clicked();

    void on_checkBox_front_panel_lru_checks_clicked(bool checked);

    void on_Bit_USB_port_clicked(bool checked);

    void on_rd_btn_RotarySwitch_1_2_3_clicked(bool checked);

    void on_rd_btn_Prep_Switch_clicked(bool checked);

    void on_rd_btn_Ready_Init_Switch_clicked(bool checked);

    void on_rd_btn_Abort_Switch_clicked(bool checked);

    void on_pb_yes_RotarySwitch_1_2_3_clicked();

    void on_pb_no_RotarySwitch_1_2_3_clicked();

    void on_pb_yes_Prep_Switch_clicked();

    void on_pb_no_Prep_Switch_clicked();

    void on_pb_yes_Ready_Init_Switch_clicked();

    void on_pb_no_Ready_Init_Switch_clicked();

    void on_pb_yes_Abort_Switch_clicked();

    void on_pb_no_Abort_Switch_clicked();

    void on_FTU_LRUReport_pb_clicked();

private:
    QString getLatestImageFromFolder(const QString &folderPath);
    QVector<TestPoint_main> testPointMain;
    TestPoint_main g_ReceivedTestPoint;
    uint16_t g_checkCRC_word = 0;
    bool g_USB_Port_Connect = 0;
    uint16_t g_CRC_word = 0;
    uint8_t DCDC_TimerValue = 0;
    int passFailCountBitTest_DIP[3][2];

public slots:

    void message_received(const QByteArray &message);
    void handleTestPointsData(QVector<TestPoint_main> receivedTestPoints);
    QByteArray serializeTestPoint(const TestPoint_main &test_Point);
    void onGenerateReportClicked();
    void updateLoopBackStatus(const QString &status);
    void DC_DC_Report();

    //void performSelfTest(const QString &resourceName);
    void Controller_Report();

    void FTU_LRU_Checks();
    void FTULRU_Report();
    void updateAoAiLineEdits(double ao, const QVector<double> &ai);

    void RA_Init(RunningAverage *ra, float *storage, uint16_t len);
    void RA_Reset(RunningAverage *ra);

    void RA_Push(RunningAverage *ra, float sample); /* drops oldest if full */
    float RA_GetMean(const RunningAverage *ra);
    uint16_t RA_Size(const RunningAverage *ra);
    uint16_t RA_Cap(const RunningAverage *ra);
    static inline uint16_t next_idx(uint16_t idx, uint16_t cap)
    {
        return (idx + 1u) >= cap ? 0u : (uint16_t) (idx + 1u);
    }

    void Sequence_TimerInterrupt(void);
    void AutoStepCompleted();

    // void ProcessCurrentSensorData(const QByteArray &rx_data);

    void on_DISPLAY_C1_pb_clicked(bool checked);

    void SRU_DC_DC_TimerUpdate();
    void setDCDC_TimerValue(uint8_t value);
    uint8_t getDCDC_TimerValue();

    // void updateScopeSettings();

    void on_pushButton_clicked();

    //    void updateScopeSettings();

    // void onImageDownloaded(QNetworkReply *reply);

    void BittestLogUpdate();

    void Volage_5V_L100_Combine(bool checked);

    void updateScopeMinMax();

    void DCDC_AutoModeConfig();
    void CTRL_AutoModeConfig();

    void SRU_CTRL_AutoStepCompleted();

protected:
    uint8_t APP_BIN[MAX_FW_SIZE];
    uint8_t g_mode_flag = 0;
    uint64_t g_binFileSize = 0;
    uint64_t g_Dword_app_bin[MAX_FW_SIZE / 8];

    uint8_t g_msg_pkt[50] = {0};
    uint8_t g_boot_timer_status = 1;

    uint32_t g_Dword_cnt = 0;
    uint32_t g_packet_no_sent = 0;

    uint8_t g_time_out_flag = 0;
    uint8_t g_time_out_state = 0;

    uint16_t g_CRC_check_GUI = 0;
    uint16_t g_CRC_check_UC = 0;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

public:
    QCustomPlot *getGraph1() const; // Getter function for Graph1
    QCustomPlot *getGraph2() const; // Getter function for Graph2
    QCustomPlot *getGraph3() const; // Getter function for Graph3
    QCustomPlot *getGraph4() const; // Getter function for Graph4
    QCustomPlot *getGraph5() const; // Getter function for Graph5
    QCustomPlot *getGraph6() const; // Getter function for Graph6
    QCustomPlot *getGraph7() const; // Getter function for Graph7
    QCustomPlot *getGraph8() const; // Getter function for Graph8

    InstantDiCtrl *instantDiCtrl1 = nullptr;
    InstantDoCtrl *instantDoCtrl1 = nullptr;

private:
    Ui::MainWindow *ui;
    uint8_t OpenPortStatus;
    QTimer *Timer_stay_in_boot_mode;
    QTimer *ADC_BitTestTim;
    QTimer *TimeOutTimer;
    QTimer *SerialTimer;
    QTimer *lcdUpdate;
    QList<QSerialPortInfo> lastKnownPorts;
    HelloThread *helloThread;
    QThread *thread1, *thread2;
    //    QThread *Advantech_thread;
    //    AdvantechCardsInterface *helloThreadAdv;

    //    qSerialWork *SerialWork;
    GraphWidget *graphWidget;
    SignalGenerator g_SignalGenerator;
    AdvantechCardsInterface *g_AdvantechCardsInterface;
    QThread *advThread{nullptr};
    AdvantechCardsInterface *AdvWorker{nullptr};

    //    AdvantechCardsInterface *advInterface;

    //    QSerialWorker *com6Worker = nullptr;
    //    QSerialWorker *com7Worker = nullptr;

    //    bool receiveFromCOM7 = false;
    //    bool receiveFromCOM6 = false;

    //    QByteArray data, data1;
    //    QTimer *timeout1;
    //    QTimer *timeout2;
    //    bool received1 = false;
    //    bool received2 = false;

    bool deviceAvailable = false;
    QString detectedDevice;
    QStringList scopes;

    SerialWork_CurrentSensor *usbWorker = nullptr;

    SerialWork_Bittest *BitWorker = nullptr;
    SerialWork_Bittest *BitWorker1 = nullptr;

    QTimer *usbPollTimer;
    AdvantechCardsInterface *usb5856Manager;
    AdvantechCardsInterface *usb4716Manager;

    bool isOutputOn = false;

    //    bool reinitUsb5856(int index);

    AdvantechCardsInterface advantechInterface; // ✅ Add this line

    //    bool safeWriteDO_5856(int cardIndex, int port, int bit, bool value); // updated prototype
    //    bool safeWriteDO_4716(int cardIndex, int port, int bit, bool value); // updated prototype

    //    bool reinitUsb4716(int index);

    //    static constexpr int MAX_4716CARDS = 2;
    //    bool isUsb4716Connected[MAX_4716CARDS];
    //    AdvantechCardsInterface *usb4716Managers[MAX_4716CARDS];
    //    bool popupShownForConnect_4716[MAX_4716CARDS];
    //    bool popupShownForDisconnect_4716[MAX_4716CARDS];
    //    bool toggleState_4716[MAX_4716CARDS]; // Optional: for DO on/off per card

    //    QQueue<QPair<QString, QString>> popupQueue; // title, message
    //    bool popupActive = false;

    //    static const int MAX_CARDS = 4;

    //    bool isUsb5856Connected[MAX_CARDS] = {false};
    //    bool popupShownForConnect[MAX_CARDS] = {false};
    //    bool popupShownForDisconnect[MAX_CARDS] = {false};
    //    bool toggleState[MAX_CARDS] = {false};

    //    AdvantechCardsInterface *usb5856Managers[MAX_CARDS] = {nullptr};

    //    void enqueuePopup(const QString &title, const QString &message);

    // Per-card status arrays

    // Button map for per-BID access
    //    QMap<int, QPushButton *> cardButtons;

    //    QStringList previousNiScopeDevices;
    //    QTimer *niScopePollTimer;

    //    static const int MAX_USB5132_CARDS = 1;
    bool isUsb5132Connected;
    //    bool popupShownForConnect_5132 = false;
    //    bool popupShownForDisconnect_5132 = false;
    //    //    bool toggleState[MAX_USB5132_CARDS] = {false};
    //    QSet<QString> knownUsb5132Devices;

    //    QSet<QString> connectedUsb5132Descriptions;
    //    QSet<QString> previousUsb5132Descriptions;
    //    bool popupShownFor5132Connect = false;
    //    bool popupShownFor5132Disconnect = false;

    //    bool usb5132WasConnected;
    //    QSet<QString> previousUsb5132Devices;
    QString usbDeviceName;

    bool findAllNIScopeDevices();
    QSerialPort *stmPort;

    bool isMoxa1Connected = false;
    bool isMoxa2Connected = false;
    bool isStmConnected;
    bool connectToPort(QSerialPort *port, const QString &portName, int index);

    QStringList findMoxaPorts();
    QList<QString> moxaPorts; // <--- Add this here
    QList<QSerialPort *> moxaPortObjects;
    QList<QString> moxaPortNames;

    // In class MainWindow
    QThread *moxa1Thread;
    QThread *moxa2Thread;
    qSerialWorkMoxa *moxa1Worker;
    qSerialWorkMoxa *moxa2Worker;

    bool popupShownForConnectMoxa1 = false;
    bool popupShownForDisconnectMoxa1 = false;

    bool popupShownForConnectMoxa2 = false;
    bool popupShownForDisconnectMoxa2 = false;

    bool card1WarningShown = false;

    QTimer *comboHoverTimer;
    bool comboPopupOpen = false;
    QTimer *settingsMonitorTimer = nullptr;

    QTimer *valueTimer;
    bool isInstrumentRunning = false;

    ViSession session_5132;
    bool is5132Initialized = false;
    void showError(const QString &title, const QString &message);

    //QNetworkAccessManager *manager;
    QPushButton *button;

    bool usb5856_card1_success = false;
    bool usb5856_card2_success = false;
    bool usb5856_card3_success = false;
    bool usb5856_card4_success = false;

    bool usb5132_card_success = false;

    bool autoMode = false;

    bool isFirstADCTrigger;

    QTimer *BittestLogTimer = nullptr;

    QFont importedFont;
    QList<QTableWidget *> tableWidgets; // Stores pointers to the 10 widgets

    void addPlusRow(QTableWidget *table, const QFont &font);
    bool isSpecialTable(QTableWidget *table);
    void insertEmployeeRowAbove(QTableWidget *table, int clickedRow, const QFont &font);
    QFont extractFontFromExcel(QAxObject *sheet);
    void addComboBoxItems(QComboBox *combo, const QStringList &items, const QString &initialValue);
    void update();

    //    QThread *serialThread = nullptr;
    //    qSerialWork *worker = nullptr;
};

/*---------------------********************Note--need to change the Message ID structure and interface to it
 * in bootloader code*******----------------*/

#pragma pack(push, 1)
typedef struct
{
    uint16_t passCount_post;
    uint16_t passCount_ADC_DAC_N2[8];
    uint16_t passCount_ADC_DAC_N1p5[8];
    uint16_t passCount_ADC_DAC_N1[8];
    uint16_t passCount_ADC_DAC_N0p5[8];
    uint16_t passCount_ADC_DAC_0V[8];
    uint16_t passCount_ADC_DAC_0p5V[8];
    uint16_t passCount_ADC_DAC_1V[8];
    uint16_t passCount_ADC_DAC_1p5V[8];
    uint16_t passCount_ADC_DAC_2V[8];
    uint16_t passCount_DIP[3];
    uint16_t passCount_DOP[5];
    uint16_t passCount_FrontPanel[4];
    uint16_t passCount_RS422;
    //--------------fail count-----------------------
    uint16_t failCount_post;
    uint16_t failCount_ADC_DAC_N2[8];
    uint16_t failCount_ADC_DAC_N1p5[8];
    uint16_t failCount_ADC_DAC_N1[8];
    uint16_t failCount_ADC_DAC_N0p5[8];
    uint16_t failCount_ADC_DAC_0V[8];
    uint16_t failCount_ADC_DAC_0p5V[8];
    uint16_t failCount_ADC_DAC_1V[8];
    uint16_t failCount_ADC_DAC_1p5V[8];
    uint16_t failCount_ADC_DAC_2V[8];
    uint16_t failCount_DIP[3];
    uint16_t failCount_DOP[5];
    uint16_t failCount_FrontPanel[4];
    uint16_t failCount_RS422;
} BitTestLogger_PassFailCount;
extern BitTestLogger_PassFailCount g_BitTestLogger_PassFailCount;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint8_t Dword_cnt;
    uint64_t Dword[NUM_OF_DWORDS];
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} BinFileTx;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint8_t SingleEnded_SEL : 1;
    uint8_t Differential_SEL : 1;
    uint8_t NumOFChannels;
    uint16_t TP1_2_3_Value;
    uint32_t DDS_CLK;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} TP_Config;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint16_t data[8];
    float time;
    uint8_t update;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} WaveForm_Plot;
#pragma pack(pop)

extern WaveForm_Plot g_waveform_plot;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint16_t packetSize;
    uint16_t data[128];
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} Moxa_port;
#pragma pack(pop)

extern Moxa_port g_Moxa_port1;
extern Moxa_port g_Moxa_port2;

#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    uint16_t CRC_WORD;
    uint16_t endByte;
} Sty_in_Boot;
#pragma pack(pop)

extern Sty_in_Boot g_Sty_in_Boot;
#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    uint16_t FTU_TestNo;
    uint16_t CRC_WORD;
    uint16_t endByte;
} ReadDataExtFlash;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    uint16_t extFlash_CRC;
    uint16_t TstPointFileCnt;
    uint16_t CRC_WORD;
    uint16_t endByte;
} ExtFlashCRC;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    uint16_t CRC_WORD;
    uint16_t endByte;
} FlashErase;
#pragma pack(pop)

extern FlashErase g_FlashErase;

#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    uint16_t SOFT_VER;
    uint16_t CRC_WORD;
    uint16_t endByte;
} AppSigDword;
#pragma pack(pop)

extern AppSigDword g_AppSigDword;

#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    uint32_t appCode_size;
    uint16_t CRC_WORD;
    uint16_t endByte;
} AppCrcVerify;
#pragma pack(pop)

extern AppCrcVerify g_AppCrcVerify;

#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    uint8_t SwitchSTS;
    uint16_t CRC_WORD;
    uint16_t endByte;
} SRU_SwitchSTS;
#pragma pack(pop)

extern SRU_SwitchSTS g_SRU_SwitchSTS;

#pragma pack(push, 1)
typedef struct
{
    uint8_t startByte;
    uint8_t MsgID;
    uint16_t packetSize;
    double DAC_Value;
    uint16_t CRC_WORD;
    uint16_t endByte;
} SetDAC_Value;
#pragma pack(pop)
extern SetDAC_Value g_SetDAC_Value;

#pragma pack(push, 1)
typedef struct
{
    QString I1;
    QString I2;
    QString I3;

} MV_current;
#pragma pack(pop)
extern MV_current g_MV_current;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t MsgID;
    uint8_t packetSize;
    uint16_t Display_status_1; //serviceability of display elements "888"
    uint16_t App_SW_Idetification;
    uint16_t AppFlash_SW_CRC;
    uint16_t EXT_Flash_SW_Idetification;
    uint16_t EXT_Flash_SW_CRC;
    uint16_t Display_status_2; //"AAA" Hardware self Test in Progress
    uint8_t ABORT_READY_INIT_LED_BLINK_STATUS;
    uint8_t TX1[5];
    uint8_t RX2[5];
    uint8_t TX2[5];
    uint8_t RX1[5];
    float P5V;
    float ANA_3p3V;
    float N5V;
    float N4P6;
    float P4P6;
    float DIG_3p3;
    float DAC1_1V;
    float DAC2_1V;
    float DAC3_1V;
    float DAC4_1V;
    float DAC5_1V;
    float DAC6_1V;
    float DAC7_1V;
    float DAC8_1V;
    uint16_t CRC_WORD;
    uint16_t EndMsg;
} Post_Status_data;
#pragma pack(pop)

extern Post_Status_data g_Post_Status_data;

#pragma pack(push, 1)
typedef struct
{
    uint8_t StartMsg;
    uint8_t packetSize;
    uint16_t FTU_Test_No;
    uint8_t Signal_Type;
    uint8_t Signal_Injection_Point;
    float Safe_engage_Time_Secs;
    uint8_t Invert_Flag;
    float Slat_Input;
    uint8_t No_of_Repeats;
    float Time_Between_Repeats;
    float Amplitude;
    float Pulse_Width_sec;
    uint8_t Type_of_Input;
    float C0;
    float C1;
    float Amplitude_percent_of_stroke;
    float Start_FreqHz;
    float End_FreqHz;
    float Freq_StepHz;
    float DwellDuration_Secs;
    float Max_Amplitude;
    float Impulse_Amplitude;
    float Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse;
    float Wo;
    float Wf;
    float Sweep_Duration;
    float Pulse_Width;
    uint16_t CRC_WORD;
    uint16_t EndMsg;

} TestPoint_Table_Data;
#pragma pack(pop)
extern TestPoint_Table_Data g_TestPoint_Table_Data[1000];
extern TestPoint_Table_Data g_TestPoint_Table_Data_Read;

#endif // MAINWINDOW_H
