#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include "qcustomplot.h"
#include "axistag.h"
#include <QTimer>


class MainWindow;  // Forward declaration

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(MainWindow *mainWindow, QWidget *parent = nullptr);

signals:

private:
    MainWindow *mainWin = NULL;
    QCustomPlot *Graph1 = NULL;
    QCustomPlot *Graph2 = NULL;
    QCustomPlot *Graph3 = NULL;
    QCustomPlot *Graph4 = NULL;
    QCustomPlot *Graph5 = NULL;
    QCustomPlot *Graph6 = NULL;
    QCustomPlot *Graph7 = NULL;
    QCustomPlot *Graph8 = NULL;
    QTimer *WaveGenerateTimer = NULL;
    QTimer *GraphUpdateTimer = NULL;
    AxisTag *mTag1 = NULL;
    QPointer<QCPGraph> mGraph1 = NULL;
    QPointer<QCPGraph> mGraph2 = NULL;
    QPointer<QCPGraph> mGraph3 = NULL;
    QPointer<QCPGraph> mGraph4 = NULL;
    QPointer<QCPGraph> mGraph5 = NULL;
    QPointer<QCPGraph> mGraph6 = NULL;
    QPointer<QCPGraph> mGraph7 = NULL;
    QPointer<QCPGraph> mGraph8 = NULL;

private slots:
    void graph_rescale ();
    void graph_replot();
    void graph_setInteractions();
//    void move_Xaxis(float value);
    void clearGraph();
    //    void on_Button_clicked();
    //    void Graph_Plot();
    void WaveGenerateTimerSlot();
    void GraphUpdateTimerSlot();



public slots:
    void setupWavefomrSiumlation();
    void Stop_button_Clicked(bool checked);
    void SaveGraph();
    void slotWaveformProcess();

};

#endif // GRAPHWIDGET_H
