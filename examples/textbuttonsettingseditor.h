#ifndef TEXTBUTTONSETTINGSMANAGER_H
#define TEXTBUTTONSETTINGSMANAGER_H

#include <QWidget>
#include "ui_textbuttonsettingsform.h"

class QtMaterialButton;

class TextButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextButtonSettingsEditor(QWidget *parent = nullptr);
    ~TextButtonSettingsEditor();

protected:
    explicit TextButtonSettingsEditor(QtMaterialButton *button, QWidget *parent = nullptr);

    Ui::TextButtonSettingsForm *const ui;

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();
    void applyDefaultPreset();
    void applyCheckablePreset();

private:
    void init();

    QtMaterialButton *const m_button;
};

#endif // TEXTBUTTONSETTINGSMANAGER_H
