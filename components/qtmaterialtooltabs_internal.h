#ifndef QTMATERIALTOOLTABS_INTERNAL_H
#define QTMATERIALTOOLTABS_INTERNAL_H

#include "lib/qtmaterialoverlaywidget.h"
#include "qtmaterialflatbutton.h"
#include <QtWidgets/QHBoxLayout>

class QPropertyAnimation;
class QtMaterialToolTabs;

class QtMaterialToolTabsInkBar : public QtMaterialOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
    QtMaterialToolTabsInkBar(QtMaterialToolTabs *parent);
    ~QtMaterialToolTabsInkBar();

    inline void setTweenValue(qreal value);
    inline qreal tweenValue() const;

    void refreshGeometry();
    void animate();

protected:
    bool eventFilter(QObject *obj, QEvent *event)  Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialToolTabsInkBar)

    QtMaterialToolTabs     *const m_tabs;
    QPropertyAnimation *const m_animation;
    QRect                     m_geometry;
    QRect                     m_previousGeometry;
    qreal                     m_tween;
};

inline void QtMaterialToolTabsInkBar::setTweenValue(qreal value)
{
    m_tween = value;
    refreshGeometry();
}

inline qreal QtMaterialToolTabsInkBar::tweenValue() const
{
    return m_tween;
}

class QtMaterialToolTab : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialToolTab(QtMaterialToolTabs *parent);
    ~QtMaterialToolTab();

    inline void setActive(bool state);
    inline bool isActive() const;

	QtMaterialFlatButton* button();
	QWidget* content();

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected slots:
    void activateTab();

protected:
    void paintForeground(QPainter *painter); //Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialToolTab)

	QVBoxLayout          *m_tabLayout;
    QtMaterialToolTabs *const m_tabs;
	QtMaterialFlatButton *m_tabButton;
	//QtMaterialFlatButton *m_tabContent;
	QWidget *m_tabContent;
    bool                  m_active;
};

inline void QtMaterialToolTab::setActive(bool state)
{
    m_active = state;
	if (state)
	{
		//m_tabContent->setMinimumHeight(300);
		m_tabContent->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	}
	else
	{
		//m_tabContent->setFixedHeight(0);
		//m_tabContent->setHeight(0);
		m_tabContent->resize(200, 0);
		m_tabContent->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Fixed );
	}
    update();
}

inline bool QtMaterialToolTab::isActive() const
{
    return m_active;
}

#endif // QTMATERIALTOOLTABS_INTERNAL_H
