/********************************************************************************
** Form generated from reading UI file 'signalgenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNALGENERATOR_H
#define UI_SIGNALGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_SignalGenerator
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_15;
    QGroupBox *groupBox_15;
    QVBoxLayout *verticalLayout_20;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_FTU_TestNo;
    QLineEdit *lineEdit_FTU_TestNo;
    QComboBox *cmb_FTU_TestNo;
    QPushButton *pbtn_FTU_TestNo;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label;
    QComboBox *ProjectName;
    QHBoxLayout *horizontalLayout_15;
    QLabel *TransmissionMode_label;
    QLineEdit *TransmissionMode_lineedit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *WaveFormSelect_lable;
    QLineEdit *WaveFormSelect_lineedit;
    QHBoxLayout *horizontalLayout_14;
    QLabel *SignalInjectionPoint_label;
    QLineEdit *SignalInjectionPoint_lineedit;
    QHBoxLayout *horizontalLayout_13;
    QLabel *Amp1_label;
    QLineEdit *Amplitude1_LineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Amplitude_percent_of_stroke_label;
    QLineEdit *Amplitude_percent_of_stroke_LineEdit;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_SafeEngageTime;
    QLineEdit *SafeEngageTime;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_InvertFlag;
    QLineEdit *LIneEdit_InvertFlag;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_C0;
    QLineEdit *lineEdit_C0;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_C1;
    QLineEdit *lineEdit_C1;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelStartFreq;
    QLineEdit *lineEditStartFreq;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelEndFreq;
    QLineEdit *lineEditEndFreq;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelFreqStep;
    QLineEdit *lineEditFreqStep;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelDWell_Duration;
    QLineEdit *lineEdit_DwellDuration;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_TypeOfInput;
    QLineEdit *lineEdit_TypeOfInput;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_SlateInput;
    QLineEdit *lineEdit_SlateInput;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_PulseWidth;
    QLineEdit *lineEdit_PulseWidth;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_PulseWidth_Sec;
    QLineEdit *lineEdit_PulseWidth_Sec;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_Repeats;
    QLineEdit *lineEdit_Repeats;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_Time_BW_Repeats;
    QLineEdit *lineEdit_Time_BW_Repeats;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_Max_Amplitude;
    QLineEdit *lineEdit_Max_Amplitude;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_Impulse_Amplitude;
    QLineEdit *lineEdit_Impulse_Amplitude;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse;
    QLineEdit *lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_Wo;
    QLineEdit *lineEdit_Wo;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_Wf;
    QLineEdit *lineEdit_Wf;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_Sweep_Duration;
    QLineEdit *lineEdit_Sweep_Duration;
    QFrame *line;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer;
    QPushButton *PlotWaveforms_PB;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *waveform_read_pbtn;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *LabelGraph1;
    QCustomPlot *Graph1;
    QLabel *LabelGraph2;
    QCustomPlot *Graph2;
    QLabel *LabelGraph3;
    QCustomPlot *Graph3;
    QLabel *LabelGraph4;
    QCustomPlot *Graph4;

    void setupUi(QWidget *SignalGenerator)
    {
        if (SignalGenerator->objectName().isEmpty())
            SignalGenerator->setObjectName(QString::fromUtf8("SignalGenerator"));
        SignalGenerator->resize(1053, 1008);
        SignalGenerator->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 68, 87);\n"
"color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(SignalGenerator);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(SignalGenerator);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(25, 49, 61);\n"
"color: rgb(0, 0, 0);"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("Bookman Old Style"));
        font.setPointSize(18);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"color: rgb(255, 213, 69);"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_2);


        verticalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(-1, -1, -1, 0);
        groupBox_15 = new QGroupBox(groupBox_2);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        groupBox_15->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"color: rgb(255, 213, 69);"));
        verticalLayout_20 = new QVBoxLayout(groupBox_15);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(-1, -1, -1, 0);
        label_FTU_TestNo = new QLabel(groupBox_15);
        label_FTU_TestNo->setObjectName(QString::fromUtf8("label_FTU_TestNo"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bookman Old Style"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_FTU_TestNo->setFont(font1);

        horizontalLayout_16->addWidget(label_FTU_TestNo);

        lineEdit_FTU_TestNo = new QLineEdit(groupBox_15);
        lineEdit_FTU_TestNo->setObjectName(QString::fromUtf8("lineEdit_FTU_TestNo"));
        lineEdit_FTU_TestNo->setFont(font1);
        lineEdit_FTU_TestNo->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_FTU_TestNo->setInputMethodHints(Qt::ImhNone);
        lineEdit_FTU_TestNo->setMaxLength(999);
        lineEdit_FTU_TestNo->setAlignment(Qt::AlignCenter);
        lineEdit_FTU_TestNo->setReadOnly(true);

        horizontalLayout_16->addWidget(lineEdit_FTU_TestNo);

        cmb_FTU_TestNo = new QComboBox(groupBox_15);
        cmb_FTU_TestNo->setObjectName(QString::fromUtf8("cmb_FTU_TestNo"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Bookman Old Style"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        cmb_FTU_TestNo->setFont(font2);
        cmb_FTU_TestNo->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        horizontalLayout_16->addWidget(cmb_FTU_TestNo);

        pbtn_FTU_TestNo = new QPushButton(groupBox_15);
        pbtn_FTU_TestNo->setObjectName(QString::fromUtf8("pbtn_FTU_TestNo"));
        pbtn_FTU_TestNo->setFont(font2);
        pbtn_FTU_TestNo->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        horizontalLayout_16->addWidget(pbtn_FTU_TestNo);


        verticalLayout_20->addLayout(horizontalLayout_16);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(-1, -1, -1, 0);
        label = new QLabel(groupBox_15);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        horizontalLayout_25->addWidget(label);

        ProjectName = new QComboBox(groupBox_15);
        ProjectName->setObjectName(QString::fromUtf8("ProjectName"));
        ProjectName->setFont(font1);
        ProjectName->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));

        horizontalLayout_25->addWidget(ProjectName);


        verticalLayout_20->addLayout(horizontalLayout_25);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(-1, -1, -1, 0);
        TransmissionMode_label = new QLabel(groupBox_15);
        TransmissionMode_label->setObjectName(QString::fromUtf8("TransmissionMode_label"));
        TransmissionMode_label->setFont(font1);

        horizontalLayout_15->addWidget(TransmissionMode_label);

        TransmissionMode_lineedit = new QLineEdit(groupBox_15);
        TransmissionMode_lineedit->setObjectName(QString::fromUtf8("TransmissionMode_lineedit"));
        TransmissionMode_lineedit->setFont(font1);
        TransmissionMode_lineedit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        TransmissionMode_lineedit->setAlignment(Qt::AlignCenter);
        TransmissionMode_lineedit->setReadOnly(true);

        horizontalLayout_15->addWidget(TransmissionMode_lineedit);


        verticalLayout_20->addLayout(horizontalLayout_15);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, -1, -1, 0);
        WaveFormSelect_lable = new QLabel(groupBox_15);
        WaveFormSelect_lable->setObjectName(QString::fromUtf8("WaveFormSelect_lable"));
        WaveFormSelect_lable->setFont(font1);

        horizontalLayout_7->addWidget(WaveFormSelect_lable);

        WaveFormSelect_lineedit = new QLineEdit(groupBox_15);
        WaveFormSelect_lineedit->setObjectName(QString::fromUtf8("WaveFormSelect_lineedit"));
        WaveFormSelect_lineedit->setFont(font1);
        WaveFormSelect_lineedit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        WaveFormSelect_lineedit->setAlignment(Qt::AlignCenter);
        WaveFormSelect_lineedit->setReadOnly(true);

        horizontalLayout_7->addWidget(WaveFormSelect_lineedit);


        verticalLayout_20->addLayout(horizontalLayout_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(-1, -1, -1, 0);
        SignalInjectionPoint_label = new QLabel(groupBox_15);
        SignalInjectionPoint_label->setObjectName(QString::fromUtf8("SignalInjectionPoint_label"));
        SignalInjectionPoint_label->setFont(font1);

        horizontalLayout_14->addWidget(SignalInjectionPoint_label);

        SignalInjectionPoint_lineedit = new QLineEdit(groupBox_15);
        SignalInjectionPoint_lineedit->setObjectName(QString::fromUtf8("SignalInjectionPoint_lineedit"));
        SignalInjectionPoint_lineedit->setFont(font1);
        SignalInjectionPoint_lineedit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        SignalInjectionPoint_lineedit->setAlignment(Qt::AlignCenter);
        SignalInjectionPoint_lineedit->setReadOnly(true);

        horizontalLayout_14->addWidget(SignalInjectionPoint_lineedit);


        verticalLayout_20->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(-1, -1, -1, 0);
        Amp1_label = new QLabel(groupBox_15);
        Amp1_label->setObjectName(QString::fromUtf8("Amp1_label"));
        Amp1_label->setFont(font1);

        horizontalLayout_13->addWidget(Amp1_label);

        Amplitude1_LineEdit = new QLineEdit(groupBox_15);
        Amplitude1_LineEdit->setObjectName(QString::fromUtf8("Amplitude1_LineEdit"));
        Amplitude1_LineEdit->setFont(font1);
        Amplitude1_LineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        Amplitude1_LineEdit->setAlignment(Qt::AlignCenter);
        Amplitude1_LineEdit->setReadOnly(true);

        horizontalLayout_13->addWidget(Amplitude1_LineEdit);


        verticalLayout_20->addLayout(horizontalLayout_13);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        Amplitude_percent_of_stroke_label = new QLabel(groupBox_15);
        Amplitude_percent_of_stroke_label->setObjectName(QString::fromUtf8("Amplitude_percent_of_stroke_label"));
        Amplitude_percent_of_stroke_label->setFont(font1);

        horizontalLayout_2->addWidget(Amplitude_percent_of_stroke_label);

        Amplitude_percent_of_stroke_LineEdit = new QLineEdit(groupBox_15);
        Amplitude_percent_of_stroke_LineEdit->setObjectName(QString::fromUtf8("Amplitude_percent_of_stroke_LineEdit"));
        Amplitude_percent_of_stroke_LineEdit->setFont(font1);
        Amplitude_percent_of_stroke_LineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        Amplitude_percent_of_stroke_LineEdit->setAlignment(Qt::AlignCenter);
        Amplitude_percent_of_stroke_LineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(Amplitude_percent_of_stroke_LineEdit);


        verticalLayout_20->addLayout(horizontalLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(-1, -1, -1, 0);
        label_SafeEngageTime = new QLabel(groupBox_15);
        label_SafeEngageTime->setObjectName(QString::fromUtf8("label_SafeEngageTime"));
        label_SafeEngageTime->setFont(font1);

        horizontalLayout_12->addWidget(label_SafeEngageTime);

        SafeEngageTime = new QLineEdit(groupBox_15);
        SafeEngageTime->setObjectName(QString::fromUtf8("SafeEngageTime"));
        SafeEngageTime->setFont(font1);
        SafeEngageTime->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        SafeEngageTime->setAlignment(Qt::AlignCenter);
        SafeEngageTime->setReadOnly(true);

        horizontalLayout_12->addWidget(SafeEngageTime);


        verticalLayout_20->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(-1, -1, -1, 0);
        label_InvertFlag = new QLabel(groupBox_15);
        label_InvertFlag->setObjectName(QString::fromUtf8("label_InvertFlag"));
        label_InvertFlag->setFont(font1);

        horizontalLayout_11->addWidget(label_InvertFlag);

        LIneEdit_InvertFlag = new QLineEdit(groupBox_15);
        LIneEdit_InvertFlag->setObjectName(QString::fromUtf8("LIneEdit_InvertFlag"));
        LIneEdit_InvertFlag->setFont(font1);
        LIneEdit_InvertFlag->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        LIneEdit_InvertFlag->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(LIneEdit_InvertFlag);


        verticalLayout_20->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, -1, -1, 0);
        label_C0 = new QLabel(groupBox_15);
        label_C0->setObjectName(QString::fromUtf8("label_C0"));
        label_C0->setFont(font1);

        horizontalLayout_10->addWidget(label_C0);

        lineEdit_C0 = new QLineEdit(groupBox_15);
        lineEdit_C0->setObjectName(QString::fromUtf8("lineEdit_C0"));
        lineEdit_C0->setFont(font1);
        lineEdit_C0->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_C0->setAlignment(Qt::AlignCenter);
        lineEdit_C0->setReadOnly(true);

        horizontalLayout_10->addWidget(lineEdit_C0);


        verticalLayout_20->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(-1, -1, -1, 0);
        label_C1 = new QLabel(groupBox_15);
        label_C1->setObjectName(QString::fromUtf8("label_C1"));
        label_C1->setFont(font1);

        horizontalLayout_9->addWidget(label_C1);

        lineEdit_C1 = new QLineEdit(groupBox_15);
        lineEdit_C1->setObjectName(QString::fromUtf8("lineEdit_C1"));
        lineEdit_C1->setFont(font1);
        lineEdit_C1->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_C1->setAlignment(Qt::AlignCenter);
        lineEdit_C1->setReadOnly(true);

        horizontalLayout_9->addWidget(lineEdit_C1);


        verticalLayout_20->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, -1, 0);
        labelStartFreq = new QLabel(groupBox_15);
        labelStartFreq->setObjectName(QString::fromUtf8("labelStartFreq"));
        labelStartFreq->setFont(font1);

        horizontalLayout_8->addWidget(labelStartFreq);

        lineEditStartFreq = new QLineEdit(groupBox_15);
        lineEditStartFreq->setObjectName(QString::fromUtf8("lineEditStartFreq"));
        lineEditStartFreq->setFont(font1);
        lineEditStartFreq->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEditStartFreq->setAlignment(Qt::AlignCenter);
        lineEditStartFreq->setReadOnly(true);

        horizontalLayout_8->addWidget(lineEditStartFreq);


        verticalLayout_20->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, -1, -1, 0);
        labelEndFreq = new QLabel(groupBox_15);
        labelEndFreq->setObjectName(QString::fromUtf8("labelEndFreq"));
        labelEndFreq->setFont(font1);

        horizontalLayout_6->addWidget(labelEndFreq);

        lineEditEndFreq = new QLineEdit(groupBox_15);
        lineEditEndFreq->setObjectName(QString::fromUtf8("lineEditEndFreq"));
        lineEditEndFreq->setFont(font1);
        lineEditEndFreq->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEditEndFreq->setAlignment(Qt::AlignCenter);
        lineEditEndFreq->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEditEndFreq);


        verticalLayout_20->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        labelFreqStep = new QLabel(groupBox_15);
        labelFreqStep->setObjectName(QString::fromUtf8("labelFreqStep"));
        labelFreqStep->setFont(font1);

        horizontalLayout_5->addWidget(labelFreqStep);

        lineEditFreqStep = new QLineEdit(groupBox_15);
        lineEditFreqStep->setObjectName(QString::fromUtf8("lineEditFreqStep"));
        lineEditFreqStep->setFont(font1);
        lineEditFreqStep->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEditFreqStep->setAlignment(Qt::AlignCenter);
        lineEditFreqStep->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEditFreqStep);


        verticalLayout_20->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, -1, 0);
        labelDWell_Duration = new QLabel(groupBox_15);
        labelDWell_Duration->setObjectName(QString::fromUtf8("labelDWell_Duration"));
        labelDWell_Duration->setFont(font1);

        horizontalLayout_4->addWidget(labelDWell_Duration);

        lineEdit_DwellDuration = new QLineEdit(groupBox_15);
        lineEdit_DwellDuration->setObjectName(QString::fromUtf8("lineEdit_DwellDuration"));
        lineEdit_DwellDuration->setFont(font1);
        lineEdit_DwellDuration->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_DwellDuration->setAlignment(Qt::AlignCenter);
        lineEdit_DwellDuration->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_DwellDuration);


        verticalLayout_20->addLayout(horizontalLayout_4);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(-1, -1, -1, 0);
        label_TypeOfInput = new QLabel(groupBox_15);
        label_TypeOfInput->setObjectName(QString::fromUtf8("label_TypeOfInput"));
        label_TypeOfInput->setFont(font1);

        horizontalLayout_17->addWidget(label_TypeOfInput);

        lineEdit_TypeOfInput = new QLineEdit(groupBox_15);
        lineEdit_TypeOfInput->setObjectName(QString::fromUtf8("lineEdit_TypeOfInput"));
        lineEdit_TypeOfInput->setFont(font1);
        lineEdit_TypeOfInput->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_TypeOfInput->setAlignment(Qt::AlignCenter);
        lineEdit_TypeOfInput->setReadOnly(true);

        horizontalLayout_17->addWidget(lineEdit_TypeOfInput);


        verticalLayout_20->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(-1, -1, -1, 0);
        label_SlateInput = new QLabel(groupBox_15);
        label_SlateInput->setObjectName(QString::fromUtf8("label_SlateInput"));
        label_SlateInput->setFont(font1);

        horizontalLayout_18->addWidget(label_SlateInput);

        lineEdit_SlateInput = new QLineEdit(groupBox_15);
        lineEdit_SlateInput->setObjectName(QString::fromUtf8("lineEdit_SlateInput"));
        lineEdit_SlateInput->setFont(font1);
        lineEdit_SlateInput->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_SlateInput->setAlignment(Qt::AlignCenter);
        lineEdit_SlateInput->setReadOnly(true);

        horizontalLayout_18->addWidget(lineEdit_SlateInput);


        verticalLayout_20->addLayout(horizontalLayout_18);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        label_PulseWidth = new QLabel(groupBox_15);
        label_PulseWidth->setObjectName(QString::fromUtf8("label_PulseWidth"));
        label_PulseWidth->setFont(font1);

        horizontalLayout_29->addWidget(label_PulseWidth);

        lineEdit_PulseWidth = new QLineEdit(groupBox_15);
        lineEdit_PulseWidth->setObjectName(QString::fromUtf8("lineEdit_PulseWidth"));
        lineEdit_PulseWidth->setFont(font1);
        lineEdit_PulseWidth->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_PulseWidth->setAlignment(Qt::AlignCenter);
        lineEdit_PulseWidth->setReadOnly(true);

        horizontalLayout_29->addWidget(lineEdit_PulseWidth);


        verticalLayout_20->addLayout(horizontalLayout_29);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(-1, -1, -1, 0);
        label_PulseWidth_Sec = new QLabel(groupBox_15);
        label_PulseWidth_Sec->setObjectName(QString::fromUtf8("label_PulseWidth_Sec"));
        label_PulseWidth_Sec->setFont(font1);

        horizontalLayout_19->addWidget(label_PulseWidth_Sec);

        lineEdit_PulseWidth_Sec = new QLineEdit(groupBox_15);
        lineEdit_PulseWidth_Sec->setObjectName(QString::fromUtf8("lineEdit_PulseWidth_Sec"));
        lineEdit_PulseWidth_Sec->setFont(font1);
        lineEdit_PulseWidth_Sec->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_PulseWidth_Sec->setAlignment(Qt::AlignCenter);
        lineEdit_PulseWidth_Sec->setReadOnly(true);

        horizontalLayout_19->addWidget(lineEdit_PulseWidth_Sec);


        verticalLayout_20->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(-1, -1, -1, 0);
        label_Repeats = new QLabel(groupBox_15);
        label_Repeats->setObjectName(QString::fromUtf8("label_Repeats"));
        label_Repeats->setFont(font1);

        horizontalLayout_20->addWidget(label_Repeats);

        lineEdit_Repeats = new QLineEdit(groupBox_15);
        lineEdit_Repeats->setObjectName(QString::fromUtf8("lineEdit_Repeats"));
        lineEdit_Repeats->setFont(font1);
        lineEdit_Repeats->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_Repeats->setAlignment(Qt::AlignCenter);
        lineEdit_Repeats->setReadOnly(true);

        horizontalLayout_20->addWidget(lineEdit_Repeats);


        verticalLayout_20->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(-1, -1, -1, 0);
        label_Time_BW_Repeats = new QLabel(groupBox_15);
        label_Time_BW_Repeats->setObjectName(QString::fromUtf8("label_Time_BW_Repeats"));
        label_Time_BW_Repeats->setFont(font1);

        horizontalLayout_21->addWidget(label_Time_BW_Repeats);

        lineEdit_Time_BW_Repeats = new QLineEdit(groupBox_15);
        lineEdit_Time_BW_Repeats->setObjectName(QString::fromUtf8("lineEdit_Time_BW_Repeats"));
        lineEdit_Time_BW_Repeats->setFont(font1);
        lineEdit_Time_BW_Repeats->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        lineEdit_Time_BW_Repeats->setAlignment(Qt::AlignCenter);
        lineEdit_Time_BW_Repeats->setReadOnly(true);

        horizontalLayout_21->addWidget(lineEdit_Time_BW_Repeats);


        verticalLayout_20->addLayout(horizontalLayout_21);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(-1, -1, -1, 0);
        label_Max_Amplitude = new QLabel(groupBox_15);
        label_Max_Amplitude->setObjectName(QString::fromUtf8("label_Max_Amplitude"));
        label_Max_Amplitude->setFont(font1);

        horizontalLayout_23->addWidget(label_Max_Amplitude);

        lineEdit_Max_Amplitude = new QLineEdit(groupBox_15);
        lineEdit_Max_Amplitude->setObjectName(QString::fromUtf8("lineEdit_Max_Amplitude"));
        lineEdit_Max_Amplitude->setFont(font1);
        lineEdit_Max_Amplitude->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_Max_Amplitude->setAlignment(Qt::AlignCenter);
        lineEdit_Max_Amplitude->setReadOnly(true);

        horizontalLayout_23->addWidget(lineEdit_Max_Amplitude);


        verticalLayout_20->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        horizontalLayout_24->setContentsMargins(-1, -1, -1, 0);
        label_Impulse_Amplitude = new QLabel(groupBox_15);
        label_Impulse_Amplitude->setObjectName(QString::fromUtf8("label_Impulse_Amplitude"));
        label_Impulse_Amplitude->setFont(font1);

        horizontalLayout_24->addWidget(label_Impulse_Amplitude);

        lineEdit_Impulse_Amplitude = new QLineEdit(groupBox_15);
        lineEdit_Impulse_Amplitude->setObjectName(QString::fromUtf8("lineEdit_Impulse_Amplitude"));
        lineEdit_Impulse_Amplitude->setFont(font1);
        lineEdit_Impulse_Amplitude->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_Impulse_Amplitude->setAlignment(Qt::AlignCenter);
        lineEdit_Impulse_Amplitude->setReadOnly(true);

        horizontalLayout_24->addWidget(lineEdit_Impulse_Amplitude);


        verticalLayout_20->addLayout(horizontalLayout_24);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse = new QLabel(groupBox_15);
        label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setObjectName(QString::fromUtf8("label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse"));
        label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setFont(font1);

        horizontalLayout_3->addWidget(label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse);

        lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse = new QLineEdit(groupBox_15);
        lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setObjectName(QString::fromUtf8("lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse"));
        lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setFont(font1);
        lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setAlignment(Qt::AlignCenter);
        lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse);


        verticalLayout_20->addLayout(horizontalLayout_3);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        label_Wo = new QLabel(groupBox_15);
        label_Wo->setObjectName(QString::fromUtf8("label_Wo"));
        label_Wo->setFont(font1);

        horizontalLayout_26->addWidget(label_Wo);

        lineEdit_Wo = new QLineEdit(groupBox_15);
        lineEdit_Wo->setObjectName(QString::fromUtf8("lineEdit_Wo"));
        lineEdit_Wo->setFont(font1);
        lineEdit_Wo->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_Wo->setAlignment(Qt::AlignCenter);
        lineEdit_Wo->setReadOnly(true);

        horizontalLayout_26->addWidget(lineEdit_Wo);


        verticalLayout_20->addLayout(horizontalLayout_26);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_Wf = new QLabel(groupBox_15);
        label_Wf->setObjectName(QString::fromUtf8("label_Wf"));
        label_Wf->setFont(font1);

        horizontalLayout_27->addWidget(label_Wf);

        lineEdit_Wf = new QLineEdit(groupBox_15);
        lineEdit_Wf->setObjectName(QString::fromUtf8("lineEdit_Wf"));
        lineEdit_Wf->setFont(font1);
        lineEdit_Wf->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_Wf->setAlignment(Qt::AlignCenter);
        lineEdit_Wf->setReadOnly(true);

        horizontalLayout_27->addWidget(lineEdit_Wf);


        verticalLayout_20->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_Sweep_Duration = new QLabel(groupBox_15);
        label_Sweep_Duration->setObjectName(QString::fromUtf8("label_Sweep_Duration"));
        label_Sweep_Duration->setFont(font1);

        horizontalLayout_28->addWidget(label_Sweep_Duration);

        lineEdit_Sweep_Duration = new QLineEdit(groupBox_15);
        lineEdit_Sweep_Duration->setObjectName(QString::fromUtf8("lineEdit_Sweep_Duration"));
        lineEdit_Sweep_Duration->setFont(font1);
        lineEdit_Sweep_Duration->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);\n"
""));
        lineEdit_Sweep_Duration->setAlignment(Qt::AlignCenter);
        lineEdit_Sweep_Duration->setReadOnly(true);

        horizontalLayout_28->addWidget(lineEdit_Sweep_Duration);


        verticalLayout_20->addLayout(horizontalLayout_28);

        line = new QFrame(groupBox_15);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_20->addWidget(line);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer);

        PlotWaveforms_PB = new QPushButton(groupBox_15);
        PlotWaveforms_PB->setObjectName(QString::fromUtf8("PlotWaveforms_PB"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bookman Old Style"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setWeight(75);
        PlotWaveforms_PB->setFont(font3);
        PlotWaveforms_PB->setStyleSheet(QString::fromUtf8("color: rgb(55, 117, 168);\n"
"background-color: rgb(255, 213, 69);"));

        horizontalLayout_22->addWidget(PlotWaveforms_PB);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_2);

        waveform_read_pbtn = new QPushButton(groupBox_15);
        waveform_read_pbtn->setObjectName(QString::fromUtf8("waveform_read_pbtn"));
        waveform_read_pbtn->setFont(font2);
        waveform_read_pbtn->setStyleSheet(QString::fromUtf8("color: rgb(55, 117, 168);\n"
"background-color: rgb(255, 213, 69);"));

        horizontalLayout_22->addWidget(waveform_read_pbtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_3);


        verticalLayout_20->addLayout(horizontalLayout_22);

        line_2 = new QFrame(groupBox_15);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_20->addWidget(line_2);


        verticalLayout_15->addWidget(groupBox_15);


        horizontalLayout->addLayout(verticalLayout_15);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, -1, -1, 0);
        LabelGraph1 = new QLabel(groupBox_2);
        LabelGraph1->setObjectName(QString::fromUtf8("LabelGraph1"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Bookman Old Style"));
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setWeight(75);
        LabelGraph1->setFont(font4);
        LabelGraph1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        LabelGraph1->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(LabelGraph1);

        Graph1 = new QCustomPlot(groupBox_2);
        Graph1->setObjectName(QString::fromUtf8("Graph1"));
        Graph1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(55, 117, 168);"));

        verticalLayout_7->addWidget(Graph1);

        LabelGraph2 = new QLabel(groupBox_2);
        LabelGraph2->setObjectName(QString::fromUtf8("LabelGraph2"));
        LabelGraph2->setFont(font4);
        LabelGraph2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        LabelGraph2->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(LabelGraph2);

        Graph2 = new QCustomPlot(groupBox_2);
        Graph2->setObjectName(QString::fromUtf8("Graph2"));
        Graph2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));

        verticalLayout_7->addWidget(Graph2);

        LabelGraph3 = new QLabel(groupBox_2);
        LabelGraph3->setObjectName(QString::fromUtf8("LabelGraph3"));
        LabelGraph3->setFont(font4);
        LabelGraph3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        LabelGraph3->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(LabelGraph3);

        Graph3 = new QCustomPlot(groupBox_2);
        Graph3->setObjectName(QString::fromUtf8("Graph3"));
        Graph3->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));

        verticalLayout_7->addWidget(Graph3);

        LabelGraph4 = new QLabel(groupBox_2);
        LabelGraph4->setObjectName(QString::fromUtf8("LabelGraph4"));
        LabelGraph4->setFont(font4);
        LabelGraph4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        LabelGraph4->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(LabelGraph4);

        Graph4 = new QCustomPlot(groupBox_2);
        Graph4->setObjectName(QString::fromUtf8("Graph4"));
        Graph4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 255);"));

        verticalLayout_7->addWidget(Graph4);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 10);
        verticalLayout_7->setStretch(2, 1);
        verticalLayout_7->setStretch(3, 10);
        verticalLayout_7->setStretch(4, 1);
        verticalLayout_7->setStretch(5, 10);
        verticalLayout_7->setStretch(6, 1);
        verticalLayout_7->setStretch(7, 10);

        horizontalLayout->addLayout(verticalLayout_7);

        horizontalLayout->setStretch(1, 10);

        verticalLayout_6->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox_2);


        verticalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 14);

        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addWidget(groupBox);


        retranslateUi(SignalGenerator);

        QMetaObject::connectSlotsByName(SignalGenerator);
    } // setupUi

    void retranslateUi(QWidget *SignalGenerator)
    {
        SignalGenerator->setWindowTitle(QString());
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("SignalGenerator", "WAVEFORMS FILE GENERATOR FOR FTU", nullptr));
        groupBox_2->setTitle(QString());
        groupBox_15->setTitle(QString());
        label_FTU_TestNo->setText(QApplication::translate("SignalGenerator", "FTU TEST No", nullptr));
        pbtn_FTU_TestNo->setText(QApplication::translate("SignalGenerator", "BROWSE", nullptr));
        label->setText(QApplication::translate("SignalGenerator", "PROJECT NAME", nullptr));
        TransmissionMode_label->setText(QApplication::translate("SignalGenerator", "TRANSMISSION MODE", nullptr));
        WaveFormSelect_lable->setText(QApplication::translate("SignalGenerator", "SIGNAL TYPE", nullptr));
        SignalInjectionPoint_label->setText(QApplication::translate("SignalGenerator", "SIGNAL INJECTION POINT", nullptr));
        Amp1_label->setText(QApplication::translate("SignalGenerator", "AMPLITUDE_1 (Vpp)", nullptr));
        Amplitude_percent_of_stroke_label->setText(QApplication::translate("SignalGenerator", "Amplitude_percent_of_stroke", nullptr));
        label_SafeEngageTime->setText(QApplication::translate("SignalGenerator", "SAFE ENGAGE TIME (Sec)", nullptr));
        label_InvertFlag->setText(QApplication::translate("SignalGenerator", "INVERT FLAG", nullptr));
        label_C0->setText(QApplication::translate("SignalGenerator", "C0-(mm) or (mV)", nullptr));
        label_C1->setText(QApplication::translate("SignalGenerator", "C1-(mm) or (mV)", nullptr));
        labelStartFreq->setText(QApplication::translate("SignalGenerator", "START FREQUENCY (Hz)", nullptr));
        labelEndFreq->setText(QApplication::translate("SignalGenerator", "END FREQUENCY (Hz)", nullptr));
        labelFreqStep->setText(QApplication::translate("SignalGenerator", "FREQUENCY STEP (Hz)", nullptr));
        labelDWell_Duration->setText(QApplication::translate("SignalGenerator", "DWELL DURATION (Sec)", nullptr));
        label_TypeOfInput->setText(QApplication::translate("SignalGenerator", "TYPE OF INPUT ", nullptr));
        label_SlateInput->setText(QApplication::translate("SignalGenerator", "SLAT INPUT", nullptr));
        label_PulseWidth->setText(QApplication::translate("SignalGenerator", "PULSE WIDTH", nullptr));
        label_PulseWidth_Sec->setText(QApplication::translate("SignalGenerator", "PULSE WIDTH (Sec)", nullptr));
        label_Repeats->setText(QApplication::translate("SignalGenerator", "No. of REPEATS (Sec)", nullptr));
        label_Time_BW_Repeats->setText(QApplication::translate("SignalGenerator", "TIME BETWEEN REPEATS (Sec)", nullptr));
        label_Max_Amplitude->setText(QApplication::translate("SignalGenerator", "Max_Amplitude", nullptr));
        label_Impulse_Amplitude->setText(QApplication::translate("SignalGenerator", "Impulse_Amplitude", nullptr));
        label_Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse->setText(QApplication::translate("SignalGenerator", "Frequency_Hz_for_sine_doublets_and_Time_sec_for_pulse", nullptr));
        label_Wo->setText(QApplication::translate("SignalGenerator", "Wo", nullptr));
        label_Wf->setText(QApplication::translate("SignalGenerator", "Wf", nullptr));
        label_Sweep_Duration->setText(QApplication::translate("SignalGenerator", "Sweep_Duration", nullptr));
        lineEdit_Sweep_Duration->setText(QString());
        PlotWaveforms_PB->setText(QApplication::translate("SignalGenerator", "PLOT WAVEFORMS", nullptr));
        waveform_read_pbtn->setText(QApplication::translate("SignalGenerator", "READ", nullptr));
        LabelGraph1->setText(QApplication::translate("SignalGenerator", "TextLabel", nullptr));
        LabelGraph2->setText(QApplication::translate("SignalGenerator", "TextLabel", nullptr));
        LabelGraph3->setText(QApplication::translate("SignalGenerator", "TextLabel", nullptr));
        LabelGraph4->setText(QApplication::translate("SignalGenerator", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignalGenerator: public Ui_SignalGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNALGENERATOR_H
