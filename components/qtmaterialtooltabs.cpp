#include "qtmaterialtooltabs.h"
#include "qtmaterialtooltabs_p.h"
#include <QtWidgets/QHBoxLayout>
#include "qtmaterialtooltabs_internal.h"
#include "lib/qtmaterialstyle.h"

/*!
 *  \QtMaterialToolTabsPrivate
 *  \internal
 */

QtMaterialToolTabsPrivate::QtMaterialToolTabsPrivate(QtMaterialToolTabs *q)
    : q_ptr(q)
{
}

QtMaterialToolTabsPrivate::~QtMaterialToolTabsPrivate()
{
}

void QtMaterialToolTabsPrivate::init()
{
    Q_Q(QtMaterialToolTabs);

    tabLayout      = new QVBoxLayout;
    rippleStyle    = Material::CenteredRipple;
    tab            = -1;
    showHalo       = true;
    useThemeColors = true;

    q->setLayout(tabLayout);
    q->setStyle(&QtMaterialStyle::instance());

    tabLayout->setSpacing(0);
    tabLayout->setMargin(0);
    tabLayout->setContentsMargins(0, 0, 0, 0);
}

/*!
 *  \QtMaterialToolTabs
 */

QtMaterialToolTabs::QtMaterialToolTabs(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialToolTabsPrivate(this))
{
    d_func()->init();
}

QtMaterialToolTabs::~QtMaterialToolTabs()
{
}

void QtMaterialToolTabs::setUseThemeColors(bool value)
{
    Q_D(QtMaterialToolTabs);

    d->useThemeColors = value;
}

bool QtMaterialToolTabs::useThemeColors() const
{
    Q_D(const QtMaterialToolTabs);

    return d->useThemeColors;
}

void QtMaterialToolTabs::setHaloVisible(bool value)
{
    Q_D(QtMaterialToolTabs);

    d->showHalo = value;
    updateTabs();
}

bool QtMaterialToolTabs::isHaloVisible() const
{
    Q_D(const QtMaterialToolTabs);

    return d->showHalo;
}

void QtMaterialToolTabs::setRippleStyle(Material::RippleStyle style)
{
    Q_D(QtMaterialToolTabs);

    d->rippleStyle = style;
    updateTabs();
}

Material::RippleStyle QtMaterialToolTabs::rippleStyle() const
{
    Q_D(const QtMaterialToolTabs);

    return d->rippleStyle;
}

void QtMaterialToolTabs::setInkColor(const QColor &color)
{
    Q_D(QtMaterialToolTabs);

    d->inkColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialToolTabs::inkColor() const
{
    Q_D(const QtMaterialToolTabs);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("accent1");
    } else {
        return d->inkColor;
    }
}

void QtMaterialToolTabs::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialToolTabs);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    updateTabs();
    update();
}

QColor QtMaterialToolTabs::backgroundColor() const
{
    Q_D(const QtMaterialToolTabs);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialToolTabs::setTextColor(const QColor &color)
{
    Q_D(QtMaterialToolTabs);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    updateTabs();
    update();
}

QColor QtMaterialToolTabs::textColor() const
{
    Q_D(const QtMaterialToolTabs);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialToolTabs::setCurrentTab(QtMaterialToolTab *tab)
{
    Q_D(QtMaterialToolTabs);

    setCurrentTab(d->tabLayout->indexOf(tab));
}

void QtMaterialToolTabs::setCurrentTab(int index)
{
    Q_D(QtMaterialToolTabs);

    setTabActive(d->tab, false);
    d->tab = index;
    setTabActive(index, true);

    emit currentChanged(index);
}

QtMaterialToolTab* QtMaterialToolTabs::getTab(int index)
{
	Q_D(QtMaterialToolTabs);
	return static_cast<QtMaterialToolTab *>(d->tabLayout->itemAt(index)->widget());
}

QtMaterialToolTab* QtMaterialToolTabs::addTab(QtMaterialToolTab *tab)
{
    Q_D(QtMaterialToolTabs);

	connect(tab, SIGNAL(onActivate(QtMaterialToolTab*)), this, SLOT(setCurrentTab(QtMaterialToolTab*)));

    tab->button()->setHaloVisible(isHaloVisible());
    tab->button()->setRippleStyle(rippleStyle());

	d->tabLayout->addWidget(tab);

	d->tabLayout->setStretchFactor(tab, 0);

    if (-1 == d->tab) {
        d->tab = 0;
        setTabActive(0,true);
    }
	return tab;
}

int QtMaterialToolTabs::currentIndex() const
{
    Q_D(const QtMaterialToolTabs);

    return d->tab;
}

void QtMaterialToolTabs::setTabActive(int index, bool active)
{
    Q_D(QtMaterialToolTabs);

    QtMaterialToolTab *tab;
	QWidget *tabContent;

    if (index > -1) {
		tab = getTab(index);
        if (tab) {
            tab->setActive(active);
			if(active)
				d->tabLayout->setStretch(index, 1);
			else
				d->tabLayout->setStretch(index, 0);
        }
    }
    update();
}

void QtMaterialToolTabs::updateTabs()
{
    Q_D(QtMaterialToolTabs);

    QtMaterialToolTab *tab;
    for (int i = 0; i < d->tabLayout->count(); i++) {
		tab = getTab(i);
        if (tab ) {
            tab->button()->setRippleStyle(d->rippleStyle);
            tab->button()->setHaloVisible(d->showHalo);
            tab->button()->setBackgroundColor(backgroundColor());
            tab->button()->setForegroundColor(textColor());
        }
    }
}

