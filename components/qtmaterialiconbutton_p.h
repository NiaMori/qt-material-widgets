#ifndef QTMATERIALICONBUTTON_P_H
#define QTMATERIALICONBUTTON_P_H

#include <QtGlobal>
#include <QColor>
#include "lib/qtmaterialtheme.h"

class QtMaterialIconButton;
class QtMaterialRippleOverlay;
class QColor;

class QtMaterialIconButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialIconButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialIconButton)

public:
    QtMaterialIconButtonPrivate(QtMaterialIconButton *q);
    virtual ~QtMaterialIconButtonPrivate();

    void init();
    void updateRipple();

    QtMaterialIconButton    *const q_ptr;
    QtMaterialRippleOverlay *rippleOverlay;
    Material::Role           role;
    QColor                   color;
    QColor                   disabledColor;
    QColor                   checkedColor;
    bool                     useThemeColors;
};

#endif // QTMATERIALICONBUTTON_P_H
