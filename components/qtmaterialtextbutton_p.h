#ifndef QTMATERIALTEXTBUTTON_P_H
#define QTMATERIALTEXTBUTTON_P_H

#include "qtmaterialbutton_p.h"

class QtMaterialTextButton;

class QtMaterialTextButtonPrivate : public QtMaterialButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialTextButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialTextButton)

public:
    QtMaterialTextButtonPrivate(QtMaterialTextButton *q);
    virtual ~QtMaterialTextButtonPrivate();

    void init();

    QtMaterialTextButton *const q_ptr;
};

#endif // QTMATERIALTEXTBUTTON_P_H
