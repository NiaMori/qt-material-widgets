#ifndef QTMATERIALOUTLINEDBUTTON_P_H
#define QTMATERIALOUTLINEDBUTTON_P_H

#include "qtmaterialtextbutton_p.h"

class QtMaterialOutlinedButton;

class QtMaterialOutlinedButtonPrivate : public QtMaterialButtonPrivate
{
  Q_DISABLE_COPY(QtMaterialOutlinedButtonPrivate)
  Q_DECLARE_PUBLIC(QtMaterialOutlinedButton)

public:
  QtMaterialOutlinedButtonPrivate(QtMaterialOutlinedButton *q);
  ~QtMaterialOutlinedButtonPrivate() Q_DECL_OVERRIDE;

  void init();

  QtMaterialOutlinedButton *const q_ptr;
};

#endif // QTMATERIALOUTLINEDBUTTON_P_H
