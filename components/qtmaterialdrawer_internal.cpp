#include "qtmaterialdrawer_internal.h"
#include <QState>
#include <QPainter>
#include <QtWidgets/QLayout>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "qtmaterialdrawer.h"

/*!
 *  \class QtMaterialDrawerStateMachine
 *  \internal
 */

QtMaterialDrawerStateMachine::QtMaterialDrawerStateMachine(QtMaterialDrawerWidget *drawer, QtMaterialDrawer *parent)
    : QStateMachine(parent),
      m_drawer(drawer),
      m_main(parent),
      m_openingState(new QState),
      m_openedState(new QState),
      m_closingState(new QState),
      m_closedState(new QState),
      m_opacity(0)
{
    addState(m_openingState);
    addState(m_openedState);
    addState(m_closingState);
    addState(m_closedState);

    setInitialState(m_closedState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    transition = new QSignalTransition(this, SIGNAL(signalOpen()));
    transition->setTargetState(m_openingState);
    m_closedState->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_openedState);
    m_openingState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(signalClose()));
    transition->setTargetState(m_closingState);
    m_openingState->addTransition(transition);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(signalClose()));
    transition->setTargetState(m_closingState);
    m_openedState->addTransition(transition);

    animation = new QPropertyAnimation(drawer, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(220);
    transition->addAnimation(animation);

    transition = new QSignalTransition(animation, SIGNAL(finished()));
    transition->setTargetState(m_closedState);
    m_closingState->addTransition(transition);

    updatePropertyAssignments();
}

QtMaterialDrawerStateMachine::~QtMaterialDrawerStateMachine()
{
}

void QtMaterialDrawerStateMachine::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_main->update();
}

bool QtMaterialDrawerStateMachine::isInClosedState() const
{
    return m_closedState->active();
}

void QtMaterialDrawerStateMachine::updatePropertyAssignments()
{
    const qreal closedOffset = -(m_drawer->width()+32);

    m_closingState->assignProperty(m_drawer, "offset", closedOffset);
    m_closedState->assignProperty(m_drawer, "offset", closedOffset);

    m_closingState->assignProperty(this, "opacity", 0);
    m_closedState->assignProperty(this, "opacity", 0);

    m_openingState->assignProperty(m_drawer, "offset", 0);
    m_openingState->assignProperty(this, "opacity", 0.4);
}

/*!
 *  \class QtMaterialDrawerWidget
 *  \internal
 */

QtMaterialDrawerWidget::QtMaterialDrawerWidget(QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      m_offset(0)
{
}

QtMaterialDrawerWidget::~QtMaterialDrawerWidget()
{
}

void QtMaterialDrawerWidget::setOffset(int offset)
{
    m_offset = offset;

    QWidget *widget = parentWidget();
    if (widget) {
        if (m_anchor == Qt::AnchorLeft)
            setGeometry(widget->rect().translated(offset, 0));
        else
            setGeometry(widget->rect().translated(widget->width()-width()-offset, 0));
    }
    update();
}

void QtMaterialDrawerWidget::setAnchor(Qt::AnchorPoint anchor)
{
    m_anchor = anchor;
    update();
}

void QtMaterialDrawerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QWidget *widget = parentWidget();

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);


    QLinearGradient gradient(QPointF(width()-16, 0), QPointF(width(), 0));
    if (m_anchor == Qt::AnchorLeft)
    {
        painter.drawRect(0, 0, width()-16, widget->height());
    }
    else
    {
        painter.drawRect(widget->rect().adjusted(16, 0, 0, 0));

        gradient.setStart(QPointF(16, 0));
        gradient.setFinalStop(QPointF(0, 0));
    }
    gradient.setColorAt(0, QColor(0, 0, 0, 80));
    gradient.setColorAt(0.5, QColor(0, 0, 0, 20));
    gradient.setColorAt(1, QColor(0, 0, 0, 0));
    painter.setBrush(QBrush(gradient));

    if (m_anchor == Qt::AnchorLeft)
        painter.drawRect(width()-16, 0, width(), widget->height());
    else
        painter.drawRect(widget->rect().adjusted(0, 0, -widget->width()+16, 0));
}

QRect QtMaterialDrawerWidget::overlayGeometry() const
{
    QWidget *widget = parentWidget();
    if (m_anchor == Qt::AnchorLeft)
        return rect().translated(m_offset, 0);
    else
        return rect().translated(widget->width()-width()-m_offset, 0);
}
