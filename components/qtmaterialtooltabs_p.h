#ifndef QTMATERIALTOOLTABS_P_H
#define QTMATERIALTOOLTABS_P_H

#include <QtGlobal>
#include "lib/qtmaterialtheme.h"

class QVBoxLayout;
class QtMaterialToolTabs;
class QtMaterialToolTabsInkBar;

class QtMaterialToolTabsPrivate
{
    Q_DISABLE_COPY(QtMaterialToolTabsPrivate)
    Q_DECLARE_PUBLIC(QtMaterialToolTabs)

public:
    QtMaterialToolTabsPrivate(QtMaterialToolTabs *q);
    ~QtMaterialToolTabsPrivate();

    void init();

    QtMaterialToolTabs       *const q_ptr;
    QtMaterialToolTabsInkBar *inkBar;
    QVBoxLayout          *tabLayout;
    Material::RippleStyle rippleStyle;
    QColor                inkColor;
    QColor                backgroundColor;
    QColor                textColor;
    int                   tab;
    bool                  showHalo;
    bool                  useThemeColors;
};

#endif // QTMATERIALTOOLTABS_P_H
