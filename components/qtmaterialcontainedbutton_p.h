#ifndef QTMATERIALCONTAINEDBUTTON_P_H
#define QTMATERIALCONTAINEDBUTTON_P_H

#include "qtmaterialbutton_p.h"

class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;
class QtMaterialContainedButton;

class QtMaterialContainedButtonPrivate : public QtMaterialButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialContainedButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialContainedButton)

public:
    QtMaterialContainedButtonPrivate(QtMaterialContainedButton *q);
    ~QtMaterialContainedButtonPrivate();

    void init();

    QtMaterialContainedButton *const q_ptr;
    QStateMachine             *shadowStateMachine;
    QState                    *normalState;
    QState                    *pressedState;
    QState                    *focusedState;
    QState                    *hoverState;
    QState                    *hoverAndFocusedState;
    QGraphicsDropShadowEffect *effect;
};

#endif // QTMATERIALCONTAINEDBUTTON_P_H
