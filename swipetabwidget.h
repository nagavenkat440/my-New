#pragma once
#include <QGestureEvent>
#include <QPanGesture>
#include <QPropertyAnimation>
#include <QTabWidget>

class SwipeTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit SwipeTabWidget(QWidget *parent = nullptr);

protected:
    bool event(QEvent *e) override;

private:
    void startPan(QPanGesture *g);
    void updatePan(QPanGesture *g);
    void endPan(QPanGesture *g);

    int m_originIdx = 0;
    QWidget *m_currPage = nullptr;
    QWidget *m_nextPage = nullptr;
};
