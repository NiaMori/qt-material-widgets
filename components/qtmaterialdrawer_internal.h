#ifndef DRAWER_INTERNAL_H
#define DRAWER_INTERNAL_H

#include <QStateMachine>
#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialDrawer;
class QtMaterialDrawerWidget;

class QtMaterialDrawerStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit QtMaterialDrawerStateMachine(QtMaterialDrawerWidget *drawer,
                                          QtMaterialDrawer *parent);
    ~QtMaterialDrawerStateMachine();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    bool isInClosedState() const;

    void updatePropertyAssignments();

signals:
    void signalOpen();
    void signalClose();

private:
    Q_DISABLE_COPY(QtMaterialDrawerStateMachine)

    QtMaterialDrawerWidget *const m_drawer;
    QtMaterialDrawer       *const m_main;
    QState                 *const m_openingState;
    QState                 *const m_openedState;
    QState                 *const m_closingState;
    QState                 *const m_closedState;
    qreal                         m_opacity;
};

inline qreal QtMaterialDrawerStateMachine::opacity() const
{
    return m_opacity;
}

class QtMaterialDrawerWidget : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)
    Q_PROPERTY(Qt::AnchorPoint anchor WRITE setAnchor READ anchor)

public:
    explicit QtMaterialDrawerWidget(QWidget *parent = 0);
    ~QtMaterialDrawerWidget();

    void setOffset(int offset);
    inline int offset() const;

    void setAnchor(Qt::AnchorPoint anchor);
    inline Qt::AnchorPoint anchor() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
    int  m_offset;
    Qt::AnchorPoint  m_anchor;
};

inline int QtMaterialDrawerWidget::offset() const
{
    return m_offset;
}

inline Qt::AnchorPoint QtMaterialDrawerWidget::anchor() const
{
    return m_anchor;
}

#endif // DRAWER_INTERNAL_H
