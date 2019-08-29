#include "qtmateriallistitem.h"
#include "qtmateriallistitem_p.h"
#include <QPainter>
#include <QFontDatabase>
#include <QDebug>
#include "lib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialListItemPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialListItemPrivate::QtMaterialListItemPrivate(QtMaterialListItem *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialListItemPrivate::~QtMaterialListItemPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialListItemPrivate::init()
{
    Q_Q(QtMaterialListItem);

    size           = 48;
    // type           = Material::LetterListItem;
    useThemeColors = true;

    q->setContentsMargins(0,0,0,0);

    QSizePolicy policy(QSizePolicy::Ignored,
                       QSizePolicy::Fixed);
    q->setSizePolicy(policy);
}

/*!
 *  \class QtMaterialListItem
 */

QtMaterialListItem::QtMaterialListItem(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialListItemPrivate(this))
{
    d_func()->init();
}

QtMaterialListItem::~QtMaterialListItem()
{
}

void QtMaterialListItem::setUseThemeColors(bool value)
{
    Q_D(QtMaterialListItem);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialListItem::useThemeColors() const
{
    Q_D(const QtMaterialListItem);

    return d->useThemeColors;
}

void QtMaterialListItem::setTextColor(const QColor &color)
{
    Q_D(QtMaterialListItem);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialListItem::textColor() const
{
    Q_D(const QtMaterialListItem);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialListItem::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialListItem);

    d->backgroundColor = color;
    
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialListItem::backgroundColor() const
{
    Q_D(const QtMaterialListItem);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
QSize QtMaterialListItem::sizeHint() const
{
    Q_D(const QtMaterialListItem);

    return QSize(width(), d->size);
}

void QtMaterialListItem::setSize(int size)
{
    Q_D(QtMaterialListItem);

    d->size = size;

    update();
}

int QtMaterialListItem::size() const
{
    Q_D(const QtMaterialListItem);

    return d->size;
}
//void QtMaterialListItem::setLetter(QString *firstLine)
//{
//	setLetter( firstLine, NULL, NULL);
//}
//void QtMaterialListItem::setLetter(QString *firstLine, QString *secondLine )
//{
//	setLetter( firstLine, secondLine, NULL );
//}

// void QtMaterialListItem::setLetter(const QString &firstLine, const QString &secondLine = 0, const QString &thirdLine = 0)
void QtMaterialListItem::setLetter(const QString &firstLine ) // , QString *secondLine = QString() , QString *thirdLine = QString())
{
    Q_D(QtMaterialListItem);

    d->firstLine = firstLine;
    //d->secondLine = secondLine;
    //d->thirdLine = thirdLine;
    d->type = Material::LetterListItem;
    update();
}

void QtMaterialListItem::setImage(const QImage &image)
{
    Q_D(QtMaterialListItem);

    d->image = image;
    d->type = Material::ImageListItem;

    d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size,
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));
    d->size = 56;
    update();
}

void QtMaterialListItem::setIcon(const QIcon &icon)
{
    Q_D(QtMaterialListItem);

    d->icon = icon;
    d->type = Material::IconListItem;
    update();
}

Material::ListItemType QtMaterialListItem::type() const
{
    Q_D(const QtMaterialListItem);

    return d->type;
}

/*!
 *  \reimp
 */
void QtMaterialListItem::paintEvent(QPaintEvent *event)
{
	int iFontWeight = QFont::Normal;

    Q_UNUSED(event)

    Q_D(QtMaterialListItem);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    QRect textRect;

    painter.fillRect( rect(), QColor(255,255,255));

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(textColor());
    painter.setBrush(Qt::NoBrush);

    if( !d->icon.isNull() && d->image.isNull() )
    {
        textRect = r.adjusted( 72,0,-16,0 );
        QRect iconGeometry(16, 16, 24, 24);
        QPixmap pixmap = d->icon.pixmap(24, 24);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), QtMaterialStyle::instance().themeColor("text"));
        painter.drawPixmap(iconGeometry, pixmap);
    }
    else if( !d->icon.isNull() && ! d->image.isNull() )
    {
        QRect iconGeometry;
	iconGeometry = QRect( width()-16-24, 16,24,24 );
        textRect = r.adjusted( 72,0,-46,0 );

        QPixmap pixmap = d->icon.pixmap(24, 24);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), QtMaterialStyle::instance().themeColor("text"));
        painter.drawPixmap(iconGeometry, pixmap);

        QPainterPath path;
        path.addEllipse(16, 8, 40, 40);
        painter.setClipPath(path);

        painter.drawPixmap(QRect(16, 8, 40, 40),
                           d->pixmap);

        painter.setClipping( false );
    }
    else
        textRect = r.adjusted( 16,0,-16,0 );

    painter.setRenderHint(QPainter::Antialiasing);

    QFont font("Roboto", 16, iFontWeight );

    painter.setFont( font );
    painter.setPen(QtMaterialStyle::instance().themeColor("text"));

    painter.drawText(textRect, Qt::AlignLeft + Qt::AlignVCenter, QString(d->firstLine));

}
