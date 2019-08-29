#ifndef QTMATERIALLISTITEM_H
#define QTMATERIALLISTITEM_H

#include <QtWidgets/QWidget>
#include "lib/qtmaterialtheme.h"

class QtMaterialListItemPrivate;

class QtMaterialListItem : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialListItem(QWidget *parent = 0);
//    explicit QtMaterialListItem(const QIcon &icon, QWidget *parent = 0);
//    explicit QtMaterialListItem(const QChar &letter, QWidget *parent = 0);
//    explicit QtMaterialListItem(const QImage &image, QWidget *parent = 0);
    ~QtMaterialListItem();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setSize(int size);
    int size() const;

    // void setLetter(const QString &firstLine, const QString &secondLine = 0, const QString &thirdLine = 0);
    void setLetter(const QString &firstLine);
    //void setLetter(QString *firstLine, QString *secondLine);
    //void setLetter(QString *firstLine, QString *secondLine, QString *thirdLine);
    void setImage(const QImage &image);
    void setIcon(const QIcon &icon);

    Material::ListItemType type() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialListItemPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialListItem)
    Q_DECLARE_PRIVATE(QtMaterialListItem)
};

#endif // QTMATERIALLISTITEM_H
