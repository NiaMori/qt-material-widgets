#ifndef QTMATERIALOUTLINEDBUTTON_H
#define QTMATERIALOUTLINEDBUTTON_H

#include "qtmaterialtextbutton.h"

class QtMaterialOutlinedButtonPrivate;

class QtMaterialOutlinedButton : public QtMaterialButton
{
  Q_OBJECT

public:
  explicit QtMaterialOutlinedButton(QWidget *parent = nullptr);
  explicit QtMaterialOutlinedButton(const QString &text, QWidget *parent = nullptr);
  ~QtMaterialOutlinedButton();

protected:
  QtMaterialOutlinedButton(QtMaterialOutlinedButtonPrivate &d, QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

  virtual void paintOutline();

private:
    Q_DISABLE_COPY(QtMaterialOutlinedButton)
    Q_DECLARE_PRIVATE(QtMaterialOutlinedButton)
};

#endif // QTMATERIALOUTLINEDBUTTON_H
