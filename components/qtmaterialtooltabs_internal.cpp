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

QtMaterialToolTab::QtMaterialToolTab(const QString &text)
      :m_active(false)
{
   // Q_ASSERT(parent);
	m_tabLayout = new QVBoxLayout(this);
    m_tabButton = new QtMaterialButton(this);
	m_tabContent = new QWidget(this);

	m_tabLayout->addWidget(m_tabButton);
	m_tabLayout->addWidget(m_tabContent);
	m_tabLayout->setStretchFactor(m_tabButton, 0);
	m_tabLayout->setStretchFactor(m_tabContent, 1);
	m_tabLayout->setContentsMargins(0, 0, 0, 0);
	m_tabLayout->setSpacing(0);
    m_tabLayout->setMargin(0);

    QFont f(font());
    f.setStyleName("Normal");
    m_tabButton->setFont(f);
	m_tabButton->setText(text);

    m_tabButton->setCornerRadius(0);
    m_tabButton->setRole(Material::Primary);
    m_tabButton->setBackgroundMode(Qt::OpaqueMode);
    m_tabButton->setBaseOpacity(0.25);

	setTitleHeight(titleHeight);

	m_tabContent->setFixedHeight(0);

	QColor col = m_tabButton->backgroundColor().darker(120);
	QString str = " background-color : " +col.name();
	m_tabContent->setStyleSheet(str);
	
	setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );


    connect(m_tabButton, SIGNAL(clicked(bool)), this, SLOT(activateTab()));
}

QtMaterialToolTab::~QtMaterialToolTab()
{
}

void QtMaterialToolTab::setTitleHeight(int height)
{
	m_tabButton->setFixedHeight(height);
	titleHeight = height;
	updateGeometry();
}

QSize QtMaterialToolTab::sizeHint() const
{
	if (m_active)
        return QSize(m_tabButton->sizeHint().width(), titleHeight) + m_tabContent->sizeHint();
	else
        return m_tabButton->minimumSize();// QSize(m_tabButton->sizeHint().width(), titleHeight);
}

QSize QtMaterialToolTab::minimumSizeHint() const
{
    return m_tabButton->minimumSize();
}


void QtMaterialToolTab::activateTab()
{
	emit onActivate(this);
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

QtMaterialButton* QtMaterialToolTab::button()
{
	return m_tabButton;
}

QWidget* QtMaterialToolTab::content()
{
	return m_tabContent;
}

