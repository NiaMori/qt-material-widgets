#ifndef QTMATERIALTEXTBUTTON_INTERNAL_H
#define QTMATERIALTEXTBUTTON_INTERNAL_H

#include <QStateMachine>
#include <QColor>

class QtMaterialButton;
class QSequentialAnimationGroup;

class QtMaterialButtonStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal overlayOpacity WRITE setOverlayOpacity READ overlayOpacity)
    Q_PROPERTY(qreal checkedOverlayProgress WRITE setCheckedOverlayProgress READ checkedOverlayProgress)
    Q_PROPERTY(qreal haloOpacity WRITE setHaloOpacity READ haloOpacity)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(qreal haloScaleFactor WRITE setHaloScaleFactor READ haloScaleFactor)

public:
    explicit QtMaterialButtonStateMachine(QtMaterialButton *parent);
    ~QtMaterialButtonStateMachine() Q_DECL_OVERRIDE;

    void setOverlayOpacity(qreal opacity);
    inline qreal overlayOpacity() const;

    void setCheckedOverlayProgress(qreal progress);
    inline qreal checkedOverlayProgress() const;

    void setHaloOpacity(qreal opacity);
    inline qreal haloOpacity() const;

    void setHaloSize(qreal size);
    inline qreal haloSize() const;

    void setHaloScaleFactor(qreal factor);
    inline qreal haloScaleFactor() const;

    void startAnimations();
    void setupProperties();
    void updateCheckedStatus();

signals:
    void buttonPressed();
    void buttonChecked();
    void buttonUnchecked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialButtonStateMachine)

    void addTransition(QObject *object, QEvent::Type eventType, QState *fromState, QState *toState);
    void addTransition(QAbstractTransition *transition, QState *fromState, QState *toState);

    QtMaterialButton     *const m_button;
    QState               *const m_topLevelState;
    QState               *const m_configState;
    QState               *const m_checkableState;
    QState               *const m_checkedState;
    QState               *const m_uncheckedState;
    QState               *const m_neutralState;
    QState               *const m_neutralFocusedState;
    QState               *const m_hoveredState;
    QState               *const m_hoveredFocusedState;
    QState               *const m_pressedState;
    qreal                       m_overlayOpacity;
    qreal                       m_checkedOverlayProgress;
    qreal                       m_haloOpacity;
    qreal                       m_haloSize;
    qreal                       m_haloScaleFactor;
    bool                        m_wasChecked;
};

inline qreal QtMaterialButtonStateMachine::overlayOpacity() const
{
    return m_overlayOpacity;
}

inline qreal QtMaterialButtonStateMachine::checkedOverlayProgress() const
{
    return m_checkedOverlayProgress;
}

inline qreal QtMaterialButtonStateMachine::haloOpacity() const
{
    return m_haloOpacity;
}

inline qreal QtMaterialButtonStateMachine::haloSize() const
{
    return m_haloSize;
}

inline qreal QtMaterialButtonStateMachine::haloScaleFactor() const
{
    return m_haloScaleFactor;
}

#endif // QTMATERIALTEXTBUTTON_INTERNAL_H
