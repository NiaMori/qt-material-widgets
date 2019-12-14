#ifndef QTMATERIALTOOLTABS_H
#define QTMATERIALTOOLTABS_H

#include <QtWidgets/QWidget>
#include <QIcon>
#include "lib/qtmaterialtheme.h"

class QtMaterialToolTabsPrivate;
class QtMaterialToolTab;

class QtMaterialToolTabs : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialToolTabs(QWidget *parent = 0);
    ~QtMaterialToolTabs();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(Material::RippleStyle style);
    Material::RippleStyle rippleStyle() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    QtMaterialToolTab* addTab(const QString &text, const QIcon &icon = QIcon());
	QtMaterialToolTab* addTab(QtMaterialToolTab *tab);

    //void setCurrentTab(QtMaterialToolTab *tab);
    void setCurrentTab(int index);
	QtMaterialToolTab* getTab(int index);

    int currentIndex() const;

signals:
    void currentChanged(int);
public slots:
	void setCurrentTab(QtMaterialToolTab*);

protected:
    void setTabActive(int index, bool active = true);
    void updateTabs();

    const QScopedPointer<QtMaterialToolTabsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialToolTabs)
    Q_DECLARE_PRIVATE(QtMaterialToolTabs)
};

#endif // QTMATERIALTOOLTABS_H
