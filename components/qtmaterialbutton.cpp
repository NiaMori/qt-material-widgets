#include "qtmaterialbutton.h"
#include "qtmaterialbutton_p.h"

#include "lib/qtmaterialrippleoverlay.h"
#include "lib/qtmaterialripple.h"
#include "lib/qtmaterialstyle.h"
#include "qtmaterialbutton_internal.h"

#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QBitmap>
#include <QPainterPath>
#include <QIcon>
#include <QtWidgets/QApplication>

/*!
 *  \class QtMaterialButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialButtonPrivate::QtMaterialButtonPrivate(QtMaterialButton *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialButtonPrivate::~QtMaterialButtonPrivate() = default;

/*!
 *  \internal
 */
void QtMaterialButtonPrivate::init()
{
    Q_Q(QtMaterialButton);

    rippleOverlay        = new QtMaterialRippleOverlay(q);
    stateMachine         = new QtMaterialButtonStateMachine(q);
    role                 = Material::Default;
    rippleStyle          = Material::PositionedRipple;
    iconPlacement        = Material::LeftIcon;
    overlayStyle         = Material::GrayOverlay;
    bgMode               = Qt::TransparentMode;
    textAlignment        = Qt::AlignHCenter;
    fixedRippleRadius    = 64;
    cornerRadius         = 3;
    baseOpacity          = 0.13;
    fontSize             = 10;        // 10.5;
    useThemeColors       = true;
    useFixedRippleRadius = false;
    haloVisible          = true;

    q->setStyle(&QtMaterialStyle::instance());
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);

    QFont font("Roboto", fontSize, QFont::Medium);
    font.setCapitalization(QFont::AllUppercase);
    q->setFont(font);

    QPainterPath path;
    path.addRoundedRect(q->rect(), cornerRadius, cornerRadius);
    rippleOverlay->setClipPath(path);
    rippleOverlay->setClipping(true);

    stateMachine->setupProperties();
    stateMachine->startAnimations();
}

QtMaterialButton::QtMaterialButton(QWidget* parent, Material::ButtonPreset preset)
    : QPushButton(parent),
      d_ptr(new QtMaterialButtonPrivate(this))
{
  d_func()->init();

  applyPreset(preset);
}

QtMaterialButton::QtMaterialButton(const QString& text, QWidget* parent, Material::ButtonPreset preset)
    : QPushButton(text, parent),
      d_ptr(new QtMaterialButtonPrivate(this))
{
  d_func()->init();

  applyPreset(preset);
}

QtMaterialButton::QtMaterialButton(const QString& text, Material::Role role, QWidget* parent, Material::ButtonPreset preset)
    : QPushButton(text, parent),
      d_ptr(new QtMaterialButtonPrivate(this))
{
  d_func()->init();

  applyPreset(preset);
  setRole(role);
}

QtMaterialButton::~QtMaterialButton() = default;

void QtMaterialButton::applyPreset(Material::ButtonPreset preset)
{
    switch (preset)
    {
    case Material::NotCheckablePreset:
        setOverlayStyle(Material::NoOverlay);
        break;
    case Material::CheckablePreset:
        setOverlayStyle(Material::NoOverlay);
        setCheckable(true);
        setHaloVisible(false);
        break;
    default:
        break;
    }
}

void QtMaterialButton::setUseThemeColors(bool value)
{
    Q_D(QtMaterialButton);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool QtMaterialButton::useThemeColors() const
{
    Q_D(const QtMaterialButton);

    return d->useThemeColors;
}

void QtMaterialButton::setRole(Material::Role role)
{
    Q_D(QtMaterialButton);

    d->role = role;
    d->stateMachine->setupProperties();
}

Material::Role QtMaterialButton::role() const
{
    Q_D(const QtMaterialButton);

    return d->role;
}

void QtMaterialButton::setForegroundColor(const QColor &color)
{
    Q_D(QtMaterialButton);

    d->foregroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialButton::foregroundColor() const
{
    Q_D(const QtMaterialButton);

    if (d->useThemeColors || !d->foregroundColor.isValid())
    {
        if (Qt::OpaqueMode == d->bgMode) {
            return QtMaterialStyle::instance().themeColor("canvas");
        }
        switch (d->role)
        {
        case Material::Primary:
            return QtMaterialStyle::instance().themeColor("primary1");
        case Material::Secondary:
            return QtMaterialStyle::instance().themeColor("accent1");
        case Material::Default:
        default:
            return QtMaterialStyle::instance().themeColor("text");
        }
    }
    return d->foregroundColor;
}

void QtMaterialButton::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialButton);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialButton::backgroundColor() const
{
    Q_D(const QtMaterialButton);

    if (d->useThemeColors || !d->backgroundColor.isValid())
    {
        switch (d->role)
        {
        case Material::Primary:
            return QtMaterialStyle::instance().themeColor("primary1");
        case Material::Secondary:
            return QtMaterialStyle::instance().themeColor("accent1");
        case Material::Default:
        default:
            return QtMaterialStyle::instance().themeColor("text");
        }
    }
    return d->backgroundColor;
}

void QtMaterialButton::setOverlayColor(const QColor &color)
{
    Q_D(QtMaterialButton);

    d->overlayColor = color;

    MATERIAL_DISABLE_THEME_COLORS

    setOverlayStyle(Material::TintedOverlay);
    update();
}

QColor QtMaterialButton::overlayColor() const
{
    Q_D(const QtMaterialButton);

    if (d->useThemeColors || !d->overlayColor.isValid()) {
        return foregroundColor();
    }
    return d->overlayColor;
}

void QtMaterialButton::setDisabledForegroundColor(const QColor &color)
{
    Q_D(QtMaterialButton);

    d->disabledColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialButton::disabledForegroundColor() const
{
    Q_D(const QtMaterialButton);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

void QtMaterialButton::setDisabledBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialButton);

    d->disabledBackgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialButton::disabledBackgroundColor() const
{
    Q_D(const QtMaterialButton);

    if (d->useThemeColors || !d->disabledBackgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("disabled3");
    } else {
        return d->disabledBackgroundColor;
    }
}

void QtMaterialButton::setFontSize(qreal size)
{
    Q_D(QtMaterialButton);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal QtMaterialButton::fontSize() const
{
    Q_D(const QtMaterialButton);

    return d->fontSize;
}

void QtMaterialButton::setHaloVisible(bool visible)
{
    Q_D(QtMaterialButton);

    d->haloVisible = visible;
    update();
}

bool QtMaterialButton::isHaloVisible() const
{
    Q_D(const QtMaterialButton);

    return d->haloVisible;
}

void QtMaterialButton::setOverlayStyle(Material::OverlayStyle style)
{
    Q_D(QtMaterialButton);

    d->overlayStyle = style;
    update();
}

Material::OverlayStyle QtMaterialButton::overlayStyle() const
{
    Q_D(const QtMaterialButton);

    return d->overlayStyle;
}

void QtMaterialButton::setRippleStyle(Material::RippleStyle style)
{
    Q_D(QtMaterialButton);

    d->rippleStyle = style;
}

Material::RippleStyle QtMaterialButton::rippleStyle() const
{
    Q_D(const QtMaterialButton);

    return d->rippleStyle;
}

void QtMaterialButton::setIconPlacement(Material::ButtonIconPlacement placement)
{
    Q_D(QtMaterialButton);

    d->iconPlacement = placement;
    update();
}

Material::ButtonIconPlacement QtMaterialButton::iconPlacement() const
{
    Q_D(const QtMaterialButton);

    return d->iconPlacement;
}

void QtMaterialButton::setCornerRadius(qreal radius)
{
    Q_D(QtMaterialButton);

    d->cornerRadius = radius;
    updateClipPath();
    update();
}

qreal QtMaterialButton::cornerRadius() const
{
    Q_D(const QtMaterialButton);

    return d->cornerRadius;
}

void QtMaterialButton::setBackgroundMode(Qt::BGMode mode)
{
    Q_D(QtMaterialButton);

    d->bgMode = mode;
    d->stateMachine->setupProperties();
}

Qt::BGMode QtMaterialButton::backgroundMode() const
{
    Q_D(const QtMaterialButton);

    return d->bgMode;
}

void QtMaterialButton::setBaseOpacity(qreal opacity)
{
    Q_D(QtMaterialButton);

    d->baseOpacity = opacity;
    d->stateMachine->setupProperties();
}

qreal QtMaterialButton::baseOpacity() const
{
    Q_D(const QtMaterialButton);

    return d->baseOpacity;
}

void QtMaterialButton::setCheckable(bool value)
{
    Q_D(QtMaterialButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::setCheckable(value);
}

void QtMaterialButton::setHasFixedRippleRadius(bool value)
{
    Q_D(QtMaterialButton);

    d->useFixedRippleRadius = value;
}

bool QtMaterialButton::hasFixedRippleRadius() const
{
    Q_D(const QtMaterialButton);

    return d->useFixedRippleRadius;
}

void QtMaterialButton::setFixedRippleRadius(qreal radius)
{
    Q_D(QtMaterialButton);

    d->fixedRippleRadius = radius;
    setHasFixedRippleRadius(true);
}

void QtMaterialButton::setTextAlignment(Qt::Alignment alignment)
{
    Q_D(QtMaterialButton);

    d->textAlignment = alignment;
}

Qt::Alignment QtMaterialButton::textAlignment() const
{
    Q_D(const QtMaterialButton);

    return d->textAlignment;
}

/*!
 *  \reimp
 */
QSize QtMaterialButton::sizeHint() const
{
    ensurePolished();

    QSize label(fontMetrics().size(Qt::TextSingleLine, text()));

    int w = 20 + label.width();
    int h = label.height();
    if (!icon().isNull()) {
        w += iconSize().width() + QtMaterialButton::IconPadding;
        h = qMax(h, iconSize().height());
    }
    return QSize(w, 20 + h);
}

QtMaterialButton::QtMaterialButton(QtMaterialButtonPrivate &d, QWidget *parent, Material::ButtonPreset preset)
    : QPushButton(parent),
      d_ptr(&d)
{
    d_func()->init();

    applyPreset(preset);
}

/*!
 *  \reimp
 */
void QtMaterialButton::checkStateSet()
{
    Q_D(QtMaterialButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::checkStateSet();
}

/*!
 *  \reimp
 */
void QtMaterialButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(QtMaterialButton);

    if (Material::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (Material::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->pos();
        }

        if (d->useFixedRippleRadius) {
            radiusEndValue = d->fixedRippleRadius;
        } else {
            radiusEndValue = static_cast<qreal>(2*qMax(pos.rx(), qAbs(pos.rx()-width())));
        }

        QtMaterialRipple *ripple = new QtMaterialRipple(pos);

        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(foregroundColor());
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(600);

        d->rippleOverlay->addRipple(ripple);
    }

    QPushButton::mousePressEvent(event);
}

/*!
 *  \reimp
 */
void QtMaterialButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QtMaterialButton);

    QPushButton::mouseReleaseEvent(event);

    d->stateMachine->updateCheckedStatus();
}

/*!
 *  \reimp
 */
void QtMaterialButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);

    updateClipPath();
}

/*!
 *  \reimp
 */
void QtMaterialButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal cr = d->cornerRadius;

    if (cr > 0)
    {
        QPainterPath path;
        path.addRoundedRect(rect(), cr, cr);

        painter.setClipPath(path);
        painter.setClipping(true);
    }

    paintBackground(&painter);
    paintHalo(&painter);

    painter.setOpacity(1);
    painter.setClipping(false);

    paintForeground(&painter);
}

/*!
 *  \internal
 */
void QtMaterialButton::paintBackground(QPainter *painter)
{
    Q_D(QtMaterialButton);

    const qreal overlayOpacity = d->stateMachine->overlayOpacity();
    const qreal checkedProgress = d->stateMachine->checkedOverlayProgress();

    if (Qt::OpaqueMode == d->bgMode) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if (isEnabled()) {
            brush.setColor(backgroundColor());
        } else {
            brush.setColor(disabledBackgroundColor());
        }
        painter->setOpacity(1);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect());
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(Qt::NoPen);

    if (!isEnabled()) {
        return;
    }

    if ((Material::NoOverlay != d->overlayStyle) && (overlayOpacity > 0)) {
        if (Material::TintedOverlay == d->overlayStyle) {
            brush.setColor(overlayColor());
        } else {
            brush.setColor(Qt::gray);
        }
        painter->setOpacity(overlayOpacity);
        painter->setBrush(brush);
        painter->drawRect(rect());
    }

    if (isCheckable() && checkedProgress > 0) {
        const qreal q = Qt::TransparentMode == d->bgMode ? 0.45 : 0.7;
        brush.setColor(foregroundColor());
        painter->setOpacity(q*checkedProgress);
        painter->setBrush(brush);
        QRect r(rect());
        r.setHeight(static_cast<qreal>(r.height())*checkedProgress);
        painter->drawRect(r);
    }
}

/*!
 *  \internal
 */
void QtMaterialButton::paintHalo(QPainter *painter)
{
    Q_D(QtMaterialButton);

    if (!d->haloVisible) {
        return;
    }

    const qreal opacity = d->stateMachine->haloOpacity();
    const qreal s = d->stateMachine->haloScaleFactor()*d->stateMachine->haloSize();
    const qreal radius = static_cast<qreal>(width())*s;

    if (isEnabled() && opacity > 0) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(foregroundColor());
        painter->setOpacity(opacity);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        const QPointF center = rect().center();
        painter->drawEllipse(center, radius, radius);
    }
}

#define COLOR_INTERPOLATE(CH) (1-progress)*source.CH() + progress*dest.CH()

/*!
 *  \internal
 */
void QtMaterialButton::paintForeground(QPainter *painter)
{
    Q_D(QtMaterialButton);

    if (isEnabled()) {
        painter->setPen(foregroundColor());
        const qreal progress = d->stateMachine->checkedOverlayProgress();
        if (isCheckable() && progress > 0) {
            QColor source = foregroundColor();
            QColor dest = Qt::TransparentMode == d->bgMode ? Qt::white
                                                           : backgroundColor();
            if (qFuzzyCompare(1, progress)) {
                painter->setPen(dest);
            } else {
                painter->setPen(QColor(COLOR_INTERPOLATE(red),
                                       COLOR_INTERPOLATE(green),
                                       COLOR_INTERPOLATE(blue),
                                       COLOR_INTERPOLATE(alpha)));
            }
        }
    } else {
        painter->setPen(disabledForegroundColor());
    }

    if (icon().isNull())  {
        if (Qt::AlignLeft == d->textAlignment) {
            painter->drawText(rect().adjusted(12, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text());
        } else {
            painter->drawText(rect(), Qt::AlignCenter, text());
        }
        return;
    }

    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size()-textSize);

    const int iw = iconSize().width() + IconPadding;
    QPoint pos(Qt::AlignLeft == d->textAlignment ? 12 : (base.width()-iw)/2, 0);

    QRect textGeometry(pos + QPoint(0, base.height()/2), textSize);
    QRect iconGeometry(pos + QPoint(0, (height()-iconSize().height())/2), iconSize());

    if (Material::LeftIcon == d->iconPlacement) {
        textGeometry.translate(iw, 0);
    } else {
        iconGeometry.translate(textSize.width() + IconPadding, 0);
    }

    painter->drawText(textGeometry, Qt::AlignCenter, text());

    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    icon.fillRect(pixmap.rect(), painter->pen().color());
    painter->drawPixmap(iconGeometry, pixmap);
}

/*!
 *  \internal
 */
void QtMaterialButton::updateClipPath()
{
    Q_D(QtMaterialButton);

    const qreal radius = d->cornerRadius;

    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    d->rippleOverlay->setClipPath(path);
}

void QtMaterialButton::enterEvent(QEvent*)
{
  QApplication::setOverrideCursor(Qt::PointingHandCursor);
}

void QtMaterialButton::leaveEvent(QEvent*)
{
  QApplication::restoreOverrideCursor();
}
