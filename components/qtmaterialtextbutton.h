#ifndef QTMATERIALTEXTBUTTON_H
#define QTMATERIALTEXTBUTTON_H

#include "qtmaterialbutton.h"
#include "lib/qtmaterialtheme.h"

class QtMaterialTextButtonPrivate;

class QtMaterialTextButton : public QtMaterialButton
{
    Q_OBJECT

public:
    explicit QtMaterialTextButton(QWidget *parent = nullptr);
    explicit QtMaterialTextButton(const QString &text, QWidget *parent = nullptr);
    ~QtMaterialTextButton() Q_DECL_OVERRIDE;

protected:
    QtMaterialTextButton(QtMaterialTextButtonPrivate &d, QWidget *parent = nullptr);

private:
    Q_DISABLE_COPY(QtMaterialTextButton)
    Q_DECLARE_PRIVATE(QtMaterialTextButton)
};

#endif // QTMATERIALTEXTBUTTON_H
