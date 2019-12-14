#include "qtmaterialoutlinedbutton.h"
#include "qtmaterialoutlinedbutton_p.h"
#include <QPainter>

/*!
 * class QtMaterialOutlinedButtonPrivate
 * \internal
 */

/*!
 *  \internal
 */
QtMaterialOutlinedButtonPrivate::QtMaterialOutlinedButtonPrivate(QtMaterialOutlinedButton *q)
    : QtMaterialButtonPrivate(q),
    q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialOutlinedButtonPrivate::~QtMaterialOutlinedButtonPrivate() = default;

/*!
 *  \internal
 */
void QtMaterialOutlinedButtonPrivate::init()
{
    Q_Q(QtMaterialOutlinedButton);

    q->setBackgroundMode(Qt::TransparentMode);
    q->setMinimumHeight(42);
    q->setBaseOpacity(0.04);
    q->setOverlayStyle(Material::TintedOverlay);
    q->setRole(Material::Primary);
}

/*!
 *  \class QtMaterialOutlinedButton
 */

QtMaterialOutlinedButton::QtMaterialOutlinedButton(QWidget *parent)
  : QtMaterialButton(*new QtMaterialOutlinedButtonPrivate(this), parent)
{
    d_func()->init();
}

QtMaterialOutlinedButton::QtMaterialOutlinedButton(const QString &text, QWidget *parent)
  : QtMaterialButton(*new QtMaterialOutlinedButtonPrivate(this), parent)
{
    d_func()->init();

    setText(text);
}

QtMaterialOutlinedButton::~QtMaterialOutlinedButton() = default;

QtMaterialOutlinedButton::QtMaterialOutlinedButton(QtMaterialOutlinedButtonPrivate &d, QWidget *parent)
    : QtMaterialButton(d, parent)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
void QtMaterialOutlinedButton::paintEvent(QPaintEvent *event)
{
  QtMaterialButton::paintEvent(event);

  paintOutline();
}

/*!
 *  \internal
 */
void QtMaterialOutlinedButton::paintOutline()
{
    Q_D(QtMaterialOutlinedButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal cr = d->cornerRadius;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (isEnabled()) {
        brush.setColor(foregroundColor());
    } else {
        brush.setColor(disabledBackgroundColor());
    }
    painter.setPen(QPen(brush, 1));
    painter.drawRoundedRect(rect(), cr, cr);
}
