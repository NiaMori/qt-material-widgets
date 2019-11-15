#include "qtmaterialtooltabs_internal.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLayoutItem>
#include <QEvent>
#include "qtmaterialtooltabs.h"
#include <QDebug>
#include "qtmaterialscrollbar.h"
#include <QtWidgets/QAbstractScrollArea>

/*!
 *  \class QtMaterialToolTabsInkBar
 *  \internal
 */

QtMaterialToolTabsInkBar::QtMaterialToolTabsInkBar(QtMaterialToolTabs *parent)
    : QtMaterialOverlayWidget(parent),
      m_tabs(parent),
      m_animation(new QPropertyAnimation(parent)),
      m_tween(0)
{
    Q_ASSERT(parent);

    m_animation->setPropertyName("tweenValue");
    m_animation->setEasingCurve(QEasingCurve::OutCirc);
    m_animation->setTargetObject(this);
    m_animation->setDuration(700);

    m_tabs->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

QtMaterialToolTabsInkBar::~QtMaterialToolTabsInkBar()
{
}

void QtMaterialToolTabsInkBar::refreshGeometry()
{
    QLayoutItem *item = m_tabs->layout()->itemAt(m_tabs->currentIndex());

    if (item)
    {
        const QRect r(item->geometry());
        const qreal s = 1-m_tween;

        if (QAbstractAnimation::Running != m_animation->state()) {
            m_geometry = QRect(r.left(), r.bottom()-1, r.width(), 2);
        } else {
            const qreal left = m_previousGeometry.left()*s + r.left()*m_tween;
            const qreal width = m_previousGeometry.width()*s + r.width()*m_tween;
            m_geometry = QRect(left, r.bottom()-1, width, 2);
        }
        m_tabs->update();
    }
}

void QtMaterialToolTabsInkBar::animate()
{
    raise();

    m_previousGeometry = m_geometry;

    m_animation->stop();
    m_animation->setStartValue(0);
    m_animation->setEndValue(1);
    m_animation->start();
}

bool QtMaterialToolTabsInkBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
    {
        refreshGeometry();
        break;
    }
    default:
        break;
    }
    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void QtMaterialToolTabsInkBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setOpacity(1);
    painter.fillRect(m_geometry, m_tabs->inkColor());
}

/*!
 *  \class QtMaterialToolTab
 *  \internal
 */

QtMaterialToolTab::QtMaterialToolTab(QtMaterialToolTabs *parent)
	 :m_tabs(parent),
      m_active(false)
{
    Q_ASSERT(parent);

	m_tabLayout = new QVBoxLayout(this);
	m_tabButton = new QtMaterialFlatButton(this);
	m_tabContent = new QWidget(this);
	//m_tabContent = new QtMaterialScrollBar(this);

	m_tabButton->setFixedHeight(40);
    QFont f(font());
    f.setStyleName("Normal");
    m_tabButton->setFont(f);

    m_tabButton->setCornerRadius(0);
    m_tabButton->setRole(Material::Primary);
    m_tabButton->setBackgroundMode(Qt::OpaqueMode);
    m_tabButton->setBaseOpacity(0.25);

	m_tabButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Fixed );
	m_tabButton->setStyleSheet("border: 3px solid red");

	//m_tabContent->setFixedHeight(0);

	m_tabContent->setStyleSheet("background: blue;");
	m_tabContent->resize(200, 0);
	m_tabContent->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Fixed );
/*
	QVBoxLayout *layout = new QVBoxLayout(m_tabContent);
    m_tabContent->setLayout(layout);
	QAbstractScrollArea *scrollArea = new QAbstractScrollArea(m_tabContent);
	layout->addWidget(scrollArea);
	//m_tabContent->setStyleSheet("border: 8px solid green");
*/

	//m_tabContent->setStyleSheet("background-color:black;");
	//m_tabContent->setBackgroundMode(Qt::OpaqueMode);
    //m_tabContent->setBaseOpacity(0.25);

	m_tabLayout->addWidget(m_tabButton);
	m_tabLayout->addWidget(m_tabContent);
	m_tabLayout->setContentsMargins(0, 0, 0, 0);
	m_tabLayout->setSpacing(0);
    m_tabLayout->setMargin(0);
	m_tabLayout->setStretch(0, 0);
	m_tabLayout->setStretch(1, 0);
	//m_tabLayout->setAlignment(Qt::AlignTop);

    connect(m_tabButton, SIGNAL(clicked(bool)), this, SLOT(activateTab()));
}

QtMaterialToolTab::~QtMaterialToolTab()
{
}

QSize QtMaterialToolTab::sizeHint() const
{
    if (m_tabButton->icon().isNull()) {
        return m_tabButton->sizeHint()+QSize(40,m_tabContent->height());
    } else {
        return QSize(40, m_tabButton->iconSize().height()+m_tabContent->height());
    }
}

void QtMaterialToolTab::activateTab()
{
    m_tabs->setCurrentTab(this);
}

void QtMaterialToolTab::paintForeground(QPainter *painter)
{
   painter->setPen(m_tabButton->foregroundColor());

    if (!m_tabButton->icon().isNull()) {
        painter->translate(0, 12);
    }

    QSize textSize(m_tabButton->fontMetrics().size(Qt::TextSingleLine, m_tabButton->text()));
    QSize base(m_tabButton->size()-textSize);

    QRect textGeometry(QPoint(base.width(), base.height())/2, textSize);

    painter->drawText(textGeometry, Qt::AlignCenter, m_tabButton->text());

    if (!m_tabButton->icon().isNull())
    {
        const QSize &size = m_tabButton->iconSize();
        QRect iconRect(QPoint((width()-size.width())/2, 0), size);

        QPixmap pixmap = m_tabButton->icon().pixmap(m_tabButton->iconSize());
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), painter->pen().color());
        painter->drawPixmap(iconRect, pixmap);
    }

    if (!m_active)
    {
        if (!m_tabButton->icon().isNull()) {
            painter->translate(0, -12);
        }
        QBrush overlay;
        overlay.setStyle(Qt::SolidPattern);
        overlay.setColor(m_tabButton->backgroundColor());
        painter->setOpacity(0.36);
        painter->fillRect(rect(), overlay);
    }
}

QtMaterialFlatButton* QtMaterialToolTab::button()
{
	return m_tabButton;
}

QWidget* QtMaterialToolTab::content()
{
	return m_tabContent;
}

