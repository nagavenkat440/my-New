#include "swipetabwidget.h"

SwipeTabWidget::SwipeTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    // Enable touch for the tab widget itself
    setAttribute(Qt::WA_AcceptTouchEvents);
    grabGesture(Qt::PanGesture);

    // Enable touch + pan on every page that already exists
    for (int i = 0; i < count(); ++i) {
        QWidget *p = widget(i);
        p->setAttribute(Qt::WA_AcceptTouchEvents);
        p->grabGesture(Qt::PanGesture);
    }

    //    // Do the same automatically for pages you add later
    //    connect(this, &QTabWidget::tabInserted, this, [this](int idx) {
    //        QWidget *p = widget(idx);
    //        p->setAttribute(Qt::WA_AcceptTouchEvents);
    //        p->grabGesture(Qt::PanGesture);
    //    });
}

bool SwipeTabWidget::event(QEvent *e)
{
    if (e->type() == QEvent::Gesture) {
        auto *ge = static_cast<QGestureEvent *>(e);
        if (auto *pan = static_cast<QPanGesture *>(ge->gesture(Qt::PanGesture))) {
            switch (pan->state()) {
            case Qt::GestureStarted:
                startPan(pan);
                break;
            case Qt::GestureUpdated:
                updatePan(pan);
                break;
            case Qt::GestureFinished:
            case Qt::GestureCanceled:
                endPan(pan);
                break;
            default:
                break;
            }
            return true; // we handled it
        }
    }
    return QTabWidget::event(e);
}

void SwipeTabWidget::startPan(QPanGesture *g)
{
    m_originIdx = currentIndex();
    const qreal dx = g->delta().x();
    // Decide early which way the user is going
    int nextIdx = dx < 0 ? (m_originIdx + 1) % count() : (m_originIdx - 1 + count()) % count();

    m_currPage = widget(m_originIdx);
    m_nextPage = widget(nextIdx);

    // Position next page just outside the viewport
    m_nextPage->show();
    m_nextPage->move((dx < 0 ? width() : -width()), 0);
}

void SwipeTabWidget::updatePan(QPanGesture *g)
{
    if (!m_currPage)
        return;

    const QPointF total = g->offset(); // total finger travel
    // Move both pages with the finger
    m_currPage->move(total.x(), 0);
    m_nextPage->move(total.x() + (total.x() < 0 ? width() : -width()), 0);
}

void SwipeTabWidget::endPan(QPanGesture *g)
{
    if (!m_currPage)
        return;

    const qreal travel = g->offset().x();
    const bool commit = std::abs(travel) > width() / 3; // snap threshold

    auto animate = [this](QWidget *w, int endX) {
        QPropertyAnimation *anim = new QPropertyAnimation(w, "pos", w);
        anim->setDuration(200);
        anim->setEndValue(QPoint(endX, 0));
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    };

    if (commit) {
        // slide old page off-screen, new page into place
        animate(m_currPage, travel < 0 ? -width() : width());
        animate(m_nextPage, 0);
        setCurrentWidget(m_nextPage); // update tab index
    } else {
        // snap back: user didn’t drag far enough
        animate(m_currPage, 0);
        animate(m_nextPage, (travel < 0 ? width() : -width()));
    }

    m_currPage = m_nextPage = nullptr;
}
