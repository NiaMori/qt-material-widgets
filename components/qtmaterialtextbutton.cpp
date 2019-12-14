#include "qtmaterialtextbutton.h"
#include "qtmaterialtextbutton_p.h"

#include "lib/qtmaterialrippleoverlay.h"
#include "lib/qtmaterialripple.h"
#include "lib/qtmaterialstyle.h"
#include "qtmaterialbutton_internal.h"

/*!
 *  \class QtMaterialTextButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialTextButtonPrivate::QtMaterialTextButtonPrivate(QtMaterialTextButton *q)
    : QtMaterialButtonPrivate(q),
      q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialTextButtonPrivate::~QtMaterialTextButtonPrivate() = default;

/*!
 *  \internal
 */
void QtMaterialTextButtonPrivate::init()
{
    Q_Q(QtMaterialTextButton);

    q->setBackgroundMode(Qt::TransparentMode);
    q->setMinimumHeight(42);
    q->setBaseOpacity(0.04);
    q->setOverlayStyle(Material::TintedOverlay);
    q->setRole(Material::Primary);
}


/*!
 *  \class QtMaterialTextButton
 */

QtMaterialTextButton::QtMaterialTextButton(QWidget *parent)
    : QtMaterialButton(*new QtMaterialTextButtonPrivate(this), parent)
{
    d_func()->init();
}

QtMaterialTextButton::QtMaterialTextButton(const QString &text, QWidget *parent)
    : QtMaterialButton(*new QtMaterialTextButtonPrivate(this), parent)
{
    d_func()->init();

    setText(text);
}

QtMaterialTextButton::~QtMaterialTextButton() = default;

QtMaterialTextButton::QtMaterialTextButton(QtMaterialTextButtonPrivate &d,QWidget *parent)
    : QtMaterialButton(d, parent)
{
    d_func()->init();
}
