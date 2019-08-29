#ifndef QTMATERIALLISTITEM_P_H
#define QTMATERIALLISTITEM_P_H

#include <QtGlobal>
#include <QChar>
#include <QImage>
#include <QIcon>
#include <QPixmap>
#include <QColor>
#include "lib/qtmaterialtheme.h"

class QtMaterialListItem;

class QtMaterialListItemPrivate
{
    Q_DISABLE_COPY(QtMaterialListItemPrivate)
    Q_DECLARE_PUBLIC(QtMaterialListItem)

public:
    QtMaterialListItemPrivate(QtMaterialListItem *q);
    ~QtMaterialListItemPrivate();

    void init();

    QtMaterialListItem *const q_ptr;
    int                     size;
    Material::ListItemType  type;
    QString                 firstLine;
    QString                 secondLine;
    QString                 thirdLine;
    QImage                  image;
    QIcon                   icon;
    QPixmap                 pixmap;
    bool                    useThemeColors;
    QColor                  textColor;
    QColor                  backgroundColor;
};

#endif // QTMATERIALLISTITEM_P_H
