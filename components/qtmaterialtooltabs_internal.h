#ifndef QTMATERIALTOOLTABS_INTERNAL_H
#define QTMATERIALTOOLTABS_INTERNAL_H

#include "lib/qtmaterialoverlaywidget.h"
#include "qtmaterialbutton.h"
#include <QtWidgets/QHBoxLayout>
#include "lib/qtmaterialstyle.h"

class QPropertyAnimation;
class QtMaterialToolTabs;

class QtMaterialToolTab : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialToolTab(const QString &text);
    ~QtMaterialToolTab();

    inline void setActive(bool state);
    inline bool isActive() const;

    QtMaterialButton* button();
	QWidget* content();

    QSize sizeHint() const Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	void setTitleHeight(int height);
signals:
        void onActivate(QtMaterialToolTab* tooltab);
protected slots:
    void activateTab();

protected:
    void paintForeground(QPainter *painter);// Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialToolTab)

	QVBoxLayout          *m_tabLayout;
    //QtMaterialToolTabs *const m_tabs;
    QtMaterialButton *m_tabButton;
	QWidget *m_tabContent;
    bool                  m_active;
	int titleHeight = 30;
};

inline void QtMaterialToolTab::setActive(bool state)
{
    m_active = state;
	if (state)
	{
		m_tabContent->setMaximumHeight(16777215);
	}
	else
	{
		m_tabContent->setFixedHeight(0);
	}
    update();
}

inline bool QtMaterialToolTab::isActive() const
{
    return m_active;
}

#endif // QTMATERIALTOOLTABS_INTERNAL_H
