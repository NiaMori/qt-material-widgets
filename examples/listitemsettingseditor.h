#ifndef LISTITEMSETTINGSEDITOR_H
#define LISTITEMSETTINGSEDITOR_H

#include <QWidget>
#include "ui_LISTITEMsettingsform.h"

class QtMaterialListItem;

class ListItemSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemSettingsEditor(QWidget *parent = 0);
    ~ListItemSettingsEditor();

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private:
    Ui::ListItemSettingsForm *const ui;
    QtMaterialListItem       *const m_listitem;
};

#endif // LISTITEMSETTINGSEDITOR_H
