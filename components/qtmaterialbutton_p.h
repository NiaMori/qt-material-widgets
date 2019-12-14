#ifndef QTMATERIALBUTTON_P_H
#define QTMATERIALBUTTON_P_H

#include <QColor>

#include "lib/qtmaterialtheme.h"

class QtMaterialButton;
class QtMaterialRippleOverlay;
class QtMaterialButtonStateMachine;

class QtMaterialButtonPrivate
{
  Q_DISABLE_COPY(QtMaterialButtonPrivate)
  Q_DECLARE_PUBLIC(QtMaterialButton)

public:
    QtMaterialButtonPrivate(QtMaterialButton *q);
    virtual ~QtMaterialButtonPrivate();

    void init();

    QtMaterialButton                 *const q_ptr;
    QtMaterialRippleOverlay          *rippleOverlay;
    QtMaterialButtonStateMachine     *stateMachine;
    Material::Role                    role;
    Material::RippleStyle             rippleStyle;
    Material::ButtonIconPlacement     iconPlacement;
    Material::OverlayStyle            overlayStyle;
    Qt::BGMode                        bgMode;
    Qt::Alignment                     textAlignment;
    QColor                            backgroundColor;
    QColor                            foregroundColor;
    QColor                            overlayColor;
    QColor                            disabledColor;
    QColor                            disabledBackgroundColor;
    qreal                             fixedRippleRadius;
    qreal                             cornerRadius;
    qreal                             baseOpacity;
    qreal                             fontSize;
    bool                              useThemeColors;
    bool                              useFixedRippleRadius;
    bool                              haloVisible;
};

#endif // QTMATERIALBUTTON_P_H
