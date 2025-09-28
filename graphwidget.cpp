#include "graphwidget.h"
#include "advantechcardsinterface.h"
#include "mainwindow.h"

#define WAVEFORM_TIMER_VALUE 5
#define WAVEFORM_UPDATE_TIMER 1000

WaveForm_Plot g_waveform_plot;

float time_value = 0;
uint8_t update_time = 0;

GraphWidget::GraphWidget(MainWindow *mainWindow, QWidget *parent) : QWidget(parent), mainWin(mainWindow)
{
    //Graph1 config
    Graph1 = mainWin->getGraph1();
    Graph1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph1->xAxis->setLabel("Time(sec)");
    Graph1->yAxis->setLabel("Voltage(V)");
    mGraph1 = Graph1->addGraph();
    QPen feedback_color1(QColor(250, 120, 0));
    feedback_color1.setWidth(2);
    mGraph1->setPen(feedback_color1);
    Graph1->legend->setVisible(true);
    mGraph1->setName("CH1");

    //Graph2 config
    Graph2 = mainWin->getGraph2();
    Graph2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph2->xAxis->setLabel("Time(sec)");
    Graph2->yAxis->setLabel("Voltage(V)");
    mGraph2 = Graph2->addGraph();
    QPen feedback_color2(QColor(250, 120, 0));
    feedback_color2.setWidth(2);
    mGraph2->setPen(feedback_color2);
    Graph2->legend->setVisible(true);
    mGraph2->setName("CH2");

    //Graph3 config
    Graph3 = mainWin->getGraph3();
    Graph3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph3->xAxis->setLabel("Time(sec)");
    Graph3->yAxis->setLabel("Voltage(V)");
    mGraph3 = Graph3->addGraph();
    QPen feedback_color3(QColor(250, 120, 0));
    feedback_color3.setWidth(2);
    mGraph3->setPen(feedback_color3);
    Graph3->legend->setVisible(true);
    mGraph3->setName("CH3");

    //Graph4 config
    Graph4 = mainWin->getGraph4();
    Graph4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph4->xAxis->setLabel("Time(sec)");
    Graph4->yAxis->setLabel("Voltage(V)");
    mGraph4 = Graph4->addGraph();
    QPen feedback_color4(QColor(250, 120, 0));
    feedback_color4.setWidth(2);
    mGraph4->setPen(feedback_color4);
    Graph4->legend->setVisible(true);
    mGraph4->setName("CH4");

    //Graph5 config
    Graph5 = mainWin->getGraph5();
    Graph5->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph5->xAxis->setLabel("Time(sec)");
    Graph5->yAxis->setLabel("Voltage(V)");
    mGraph5 = Graph5->addGraph();
    QPen feedback_color5(QColor(250, 120, 0));
    feedback_color5.setWidth(2);
    mGraph5->setPen(feedback_color5);
    Graph5->legend->setVisible(true);
    mGraph5->setName("CH5");

    //Graph6 config
    Graph6 = mainWin->getGraph6();
    Graph6->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph6->xAxis->setLabel("Time(sec)");
    Graph6->yAxis->setLabel("Voltage(V)");
    mGraph6 = Graph6->addGraph();
    QPen feedback_color6(QColor(250, 120, 0));
    feedback_color6.setWidth(2);
    mGraph6->setPen(feedback_color6);
    Graph6->legend->setVisible(true);
    mGraph6->setName("CH6");

    //Graph7 config
    Graph7 = mainWin->getGraph7();
    Graph7->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph7->xAxis->setLabel("Time(sec)");
    Graph7->yAxis->setLabel("Voltage(V)");
    mGraph7 = Graph7->addGraph();
    QPen feedback_color7(QColor(250, 120, 0));
    feedback_color7.setWidth(2);
    mGraph7->setPen(feedback_color7);
    Graph7->legend->setVisible(true);
    mGraph7->setName("CH7");

    //Graph8 config
    Graph8 = mainWin->getGraph8();
    Graph8->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    Graph8->xAxis->setLabel("Time(sec)");
    Graph8->yAxis->setLabel("Voltage(V)");
    mGraph8 = Graph8->addGraph();
    QPen feedback_color8(QColor(250, 120, 0));
    feedback_color8.setWidth(2);
    mGraph8->setPen(feedback_color8);
    Graph8->legend->setVisible(true);
    mGraph8->setName("CH8");

    /*----------------------------QTimer 2--------------------------*/
    GraphUpdateTimer = new QTimer(this);
    connect(GraphUpdateTimer, &QTimer::timeout, this, &GraphWidget::GraphUpdateTimerSlot);
    GraphUpdateTimer->start(WAVEFORM_UPDATE_TIMER);

//    Graph2->setFixedHeight(0);
//    Graph3->setFixedHeight(0);
//    Graph4->setFixedHeight(0);
//    Graph5->setFixedHeight(0);
//    Graph6->setFixedHeight(0);
//    Graph7->setFixedHeight(0);
//    Graph8->setFixedHeight(0);
}


void GraphWidget::setupWavefomrSiumlation()
{
    //    qDebug() << "in setupGraph";
    /*----------------------------QTimer 1--------------------------*/
    WaveGenerateTimer = new QTimer(this);
    connect(WaveGenerateTimer, &QTimer::timeout, this, &GraphWidget::WaveGenerateTimerSlot);
    WaveGenerateTimer->start(WAVEFORM_TIMER_VALUE);


}
void GraphWidget::GraphUpdateTimerSlot()
{
    //    qDebug() << "in GraphUpdateTimerSlot";
    Graph1->replot();
    Graph2->replot();
    Graph3->replot();
    Graph4->replot();
    Graph5->replot();
    Graph6->replot();
    Graph7->replot();
    Graph8->replot();
    float static time = 0;
    Graph1->xAxis->rescale();
    Graph1->update();
    //set graph scrolling length
    Graph1->xAxis->setRange(Graph1->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph1->rescaleValueAxis(false, true);

    Graph2->rescaleAxes();
    Graph2->update();
    //set2graph scrolling length
    Graph2->xAxis->setRange(Graph2->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph2->rescaleValueAxis(false, true);

    Graph3->rescaleAxes();
    Graph3->update();
    //set3graph scrolling length
    Graph3->xAxis->setRange(Graph3->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph3->rescaleValueAxis(false, true);

    Graph4->rescaleAxes();
    Graph4->update();
    //set4graph scrolling length
    Graph4->xAxis->setRange(Graph4->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph4->rescaleValueAxis(false, true);

    Graph5->rescaleAxes();
    Graph5->update();
    //set5graph scrolling length
    Graph5->xAxis->setRange(Graph5->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph5->rescaleValueAxis(false, true);

    Graph6->rescaleAxes();
    Graph6->update();
    //set6graph scrolling length
    Graph6->xAxis->setRange(Graph6->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph6->rescaleValueAxis(false, true);

    Graph7->rescaleAxes();
    Graph7->update();
    //set7graph scrolling length
    Graph7->xAxis->setRange(Graph7->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph7->rescaleValueAxis(false, true);

    Graph8->rescaleAxes();
    Graph8->update();
    //set8graph scrolling length
    Graph8->xAxis->setRange(Graph8->xAxis->range().upper, (time), Qt::AlignRight);
    mGraph8->rescaleValueAxis(false, true);
    time = 10;
}

void GraphWidget::WaveGenerateTimerSlot()
{
    static float  b = 0;
    float c = 0;
    static float timeValue_X = 0;
    static float Graph_scroll_length = 0;
    if(b<360)
    {
        timeValue_X += WAVEFORM_TIMER_VALUE/1000.0;
        //Graph 1
        Graph1->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 1));
        Graph1->rescaleAxes();
        Graph1->update();
        //set graph scrolling length
        Graph1->xAxis->setRange(Graph1->xAxis->range().upper, 10, Qt::AlignRight);
        //Graph 2
        Graph2->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 2));
        Graph2->rescaleAxes();
        Graph2->update();
        //set graph scrolling length
        Graph2->xAxis->setRange(Graph2->xAxis->range().upper, 10, Qt::AlignRight);
        //Graph 3
        Graph3->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 3));
        Graph3->rescaleAxes();
        Graph3->update();
        //set graph scrolling length
        Graph3->xAxis->setRange(Graph3->xAxis->range().upper, 10, Qt::AlignRight);
        //Graph 4
        Graph4->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 4));
        Graph4->rescaleAxes();
        Graph4->update();
        //set graph scrolling length
        Graph4->xAxis->setRange(Graph4->xAxis->range().upper, 10, Qt::AlignRight);
        //Graph 5
        Graph5->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 5));
        Graph5->rescaleAxes();
        Graph5->update();
        //set graph scrolling length
        Graph5->xAxis->setRange(Graph5->xAxis->range().upper, 10, Qt::AlignRight);
        //Graph 6
        Graph6->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 6));
        Graph6->rescaleAxes();
        Graph6->update();
        //set graph scrolling length
        Graph6->xAxis->setRange(Graph6->xAxis->range().upper, 10, Qt::AlignRight);
        //Graph 7
        Graph7->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 7));
        Graph7->rescaleAxes();
        Graph7->update();
        //set graph scrolling length
        Graph7->xAxis->setRange(Graph7->xAxis->range().upper, 10, Qt::AlignRight);
        //Graph 8
        Graph8->graph(0)->addData(timeValue_X, ((sin(b*(3.14/180))) * 8));
        Graph8->rescaleAxes();
        Graph8->update();
        //set graph scrolling length
        Graph8->xAxis->setRange(Graph8->xAxis->range().upper, 10, Qt::AlignRight);
        c = (360.0/200);
        b += c;
        Graph_scroll_length += 1;
        //        qDebug() << "in waveFenerateTimerSlot"<< QString::number(b,'f',3) << QString::number(c,'f',3) << QString::number(timeValue_X,'f',3);

    }
    else
    {
        b = 0;
        if (Graph_scroll_length == 10)
        {
            Graph_scroll_length = 0;
        }
    }
}


//void GraphWidget::move_Xaxis(float value)
//{
//    float l_default_value = 0;

//    l_default_value = (10/value);
//    //this line is used for moving x axis
//    Graph1->xAxis->setRange(Graph1->xAxis->range().upper, l_default_value, Qt::AlignRight);
//}

void GraphWidget::graph_rescale ()
{
    Graph1->xAxis->rescale();
}
void GraphWidget::graph_replot()
{
    Graph1->replot();
}
void GraphWidget::graph_setInteractions()
{
    Graph1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables
                            |QCP::iSelectAxes|QCP::iMultiSelect|QCP::iSelectItems|QCP::iSelectOther|QCP::iSelectLegend );
}

void GraphWidget::clearGraph()
{
//    Graph1->clearGraphs();
//    Graph2->clearGraphs();
//    Graph3->clearGraphs();
//    Graph4->clearGraphs();
//    Graph5->clearGraphs();
//    Graph6->clearGraphs();
//    Graph7->clearGraphs();
//    Graph8->clearGraphs();
    if(mGraph1->dataCount() > 0) {
        mGraph1->data().data()->clear();
    }

    //         ui->widget_plot->xAxis->setRange(10,0);
    //         ui->widget_plot->yAxis->setRange(10,0);
}

//void GraphWidget::on_Button_clicked()
//{
//    for( int g=0; g<mGraph1->dataCount(); g++ )
//    {
//        mGraph1->data().data()->clear();
//    }
//    for( int g=0; g<mGraph2->dataCount(); g++ )
//    {
//        mGraph2->data()->clear();
//    }
//    for( int g=0; g<mGraph3->dataCount(); g++ )
//    {
//        mGraph3->data().data()->clear();
//    }

//}

//void MainWindow::on_Current_graph_stateChanged(int arg1)
//{
//    if(arg1 == 2)
//    {
//        //        mGraph3->setVisible(true);
//        for( int g=0; g<mGraph3->dataCount(); g++ )
//        {
//            mGraph3->setVisible(true);
//        }
//        mDataTimer.stop();
//    }
//    else
//    {
//        mGraph3->setVisible(false);
//    }
//}

//void GraphWidget::SaveGraph()
//{
//    //save file
//    QDateTime date_time = QDateTime::currentDateTime();
//    QString default_file_save_location = "FTU_PLOT_"+ date_time.toString("D_dd_MM_yyyy_T_hh_mm_ss");

//    QFileDialog fileDialog;
//    QString default_file_name = fileDialog.getSaveFileName(this,"SaveFile",default_file_save_location,"Image(*.png)");
//    if(default_file_name == "")
//    {
//        return;
//    }
//    QFile file(default_file_name);

//    if (!file.open(QIODevice::WriteOnly))
//    {
//        qDebug() << file.errorString();
//    } else {
//        Graph1->savePng(default_file_name);
//    }

//    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Info",
//                                          "GRAPH saved ",
//                                          QMessageBox::Ok);
//    QTimer *msgBoxCloseTimer = new QTimer(this);
//    msgBoxCloseTimer->setInterval(1000);
//    msgBoxCloseTimer->setSingleShot(true);
//    connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject())); //or accept()

//    msgBoxCloseTimer->start();
//    msgBox->exec();
//}

void GraphWidget::SaveGraph()
{
    // Timestamp base for naming
    QDateTime date_time = QDateTime::currentDateTime();
    QString baseName = "FTU_PLOT_" + date_time.toString("D_dd_MM_yyyy_T_hh_mm_ss");

    // Select folder instead of file
    QString folderPath = QFileDialog::getExistingDirectory(this, "Select Folder to Save Graphs");
    if (folderPath.isEmpty())
        return;

    // Map of plots (or just QVector if you don't need names)
    QVector<QCustomPlot*> plots = {
        Graph1, Graph2, Graph3, Graph4,
        Graph5, Graph6, Graph7, Graph8
    };

    // Save each plot with indexed name
    for (int i = 0; i < plots.size(); ++i) {
        QString fileName = QString("%1/%2_CH%3.png")
                           .arg(folderPath)
                           .arg(baseName)
                           .arg(i + 1); // CH1...CH8
        if (!plots[i]->savePng(fileName)) {
            //            qDebug() << "Failed to save:" << fileName;
        }
    }

    // Show message box (auto-closing after 1 second)
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Info",
                                          "All graphs saved successfully",
                                          QMessageBox::Ok);
    QTimer *msgBoxCloseTimer = new QTimer(this);
    msgBoxCloseTimer->setInterval(1000);
    msgBoxCloseTimer->setSingleShot(true);
    connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject()));
    msgBoxCloseTimer->start();
    msgBox->exec();
}


void GraphWidget::Stop_button_Clicked(bool checked)
{
    if(checked == true)
    {
//        WaveGenerateTimer->stop();
        GraphUpdateTimer->stop();
    }
    else if(checked == false)
    {
//        WaveGenerateTimer->start(WAVEFORM_TIMER_VALUE);
        GraphUpdateTimer->start(WAVEFORM_UPDATE_TIMER);
    }

}
void GraphWidget::slotWaveformProcess()
{
    double static timeValue = 0;
    Graph1->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[0]));
    Graph2->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[1]));
    Graph3->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[2]));
    Graph4->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[3]));
    Graph5->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[4]));
    Graph6->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[5]));
    Graph7->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[6]));
    Graph8->graph(0)->addData(timeValue, (g_ADC_BitTest.CH_data[7]));
    timeValue += 0.001;
}
