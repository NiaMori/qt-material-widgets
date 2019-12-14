#ifndef QTMATERIALCONTAINEDBUTTON_H
#define QTMATERIALCONTAINEDBUTTON_H

#include "qtmaterialbutton.h"

class QtMaterialContainedButtonPrivate;

class QtMaterialContainedButton : public QtMaterialButton
{
    Q_OBJECT

public:
    explicit QtMaterialContainedButton(QWidget *parent = nullptr);
    explicit QtMaterialContainedButton(const QString &text, QWidget *parent = nullptr);
    ~QtMaterialContainedButton() Q_DECL_OVERRIDE;

protected:
    QtMaterialContainedButton(QtMaterialContainedButtonPrivate &d, QWidget *parent = nullptr);

    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialContainedButton)
    Q_DECLARE_PRIVATE(QtMaterialContainedButton)
};

#endif // QTMATERIALCONTAINEDBUTTON_H
