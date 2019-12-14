#include "qtmaterialcontainedbutton.h"
#include "qtmaterialcontainedbutton_p.h"
#include <QStateMachine>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEventTransition>

/*!
 *  \class QtMaterialContainedButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialContainedButtonPrivate::QtMaterialContainedButtonPrivate(QtMaterialContainedButton *q)
    : QtMaterialButtonPrivate(q),
      q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialContainedButtonPrivate::~QtMaterialContainedButtonPrivate() = default;

/*!
 *  \internal
 */
void QtMaterialContainedButtonPrivate::init()
{
    Q_Q(QtMaterialContainedButton);

    shadowStateMachine   = new QStateMachine(q);
    normalState          = new QState;
    pressedState         = new QState;
    focusedState         = new QState;
    hoverState           = new QState;
    hoverAndFocusedState = new QState;
    effect               = new QGraphicsDropShadowEffect;

    effect->setBlurRadius(7);
    effect->setOffset(QPointF(0, 2));
    effect->setColor(QColor(0, 0, 0, 75));

    shadowStateMachine->addState(normalState);
    shadowStateMachine->addState(pressedState);
    shadowStateMachine->addState(focusedState);
    shadowStateMachine->addState(hoverState);
    shadowStateMachine->addState(hoverAndFocusedState);

    normalState->assignProperty(effect, "offset", QPointF(0, 2));
    normalState->assignProperty(effect, "blurRadius", 7);

    focusedState->assignProperty(effect, "offset", QPoint(0, 3));
    focusedState->assignProperty(effect, "blurRadius", 12);

    hoverState->assignProperty(effect, "offset", QPoint(0, 3));
    hoverState->assignProperty(effect, "blurRadius", 12);

    hoverAndFocusedState->assignProperty(effect, "offset", QPoint(0, 3));
    hoverAndFocusedState->assignProperty(effect, "blurRadius", 12);

    pressedState->assignProperty(effect, "offset", QPointF(0, 5));
    pressedState->assignProperty(effect, "blurRadius", 29);

    QAbstractTransition *transition;

    transition = new QEventTransition(q, QEvent::HoverEnter);
    transition->setTargetState(hoverState);
    normalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::HoverLeave);
    transition->setTargetState(normalState);
    hoverState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::FocusIn);
    transition->setTargetState(focusedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::FocusOut);
    transition->setTargetState(normalState);
    focusedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::FocusIn);
    transition->setTargetState(hoverAndFocusedState);
    hoverState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::FocusOut);
    transition->setTargetState(hoverState);
    hoverAndFocusedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::HoverEnter);
    transition->setTargetState(hoverAndFocusedState);
    focusedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::HoverLeave);
    transition->setTargetState(focusedState);
    hoverAndFocusedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);
    hoverAndFocusedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonRelease);
    transition->setTargetState(hoverAndFocusedState);
    pressedState->addTransition(transition);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(effect, "offset", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "blurRadius", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    shadowStateMachine->setInitialState(normalState);
    shadowStateMachine->start();

    q->setBackgroundMode(Qt::OpaqueMode);
    q->setMinimumHeight(42);
    q->setGraphicsEffect(effect);
    q->setBaseOpacity(0.2);
    q->setOverlayStyle(Material::TintedOverlay);
    q->setOverlayColor(Qt::white);
    q->setRole(Material::Primary);
}

/*!
 *  \class QtMaterialContainedButton
 */

QtMaterialContainedButton::QtMaterialContainedButton(QWidget *parent)
    : QtMaterialButton(*new QtMaterialContainedButtonPrivate(this), parent)
{
    d_func()->init();
}

QtMaterialContainedButton::QtMaterialContainedButton(const QString &text, QWidget *parent)
    : QtMaterialButton(*new QtMaterialContainedButtonPrivate(this), parent)
{
    d_func()->init();

    setText(text);
}

QtMaterialContainedButton::~QtMaterialContainedButton() = default;

QtMaterialContainedButton::QtMaterialContainedButton(QtMaterialContainedButtonPrivate &d, QWidget *parent)
    : QtMaterialButton(d, parent)
{
    d_func()->init();
}

bool QtMaterialContainedButton::event(QEvent *event)
{
    Q_D(QtMaterialContainedButton);

    if (QEvent::EnabledChange == event->type()) {
        if (isEnabled()) {
            d->shadowStateMachine->start();
            d->effect->setEnabled(true);
        } else {
            d->shadowStateMachine->stop();
            d->effect->setEnabled(false);
        }
    }
    return QtMaterialButton::event(event);
}
