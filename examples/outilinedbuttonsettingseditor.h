#ifndef OUTILINEDBUTTONSETTINGSEDITOR_H
#define OUTILINEDBUTTONSETTINGSEDITOR_H

#include "textbuttonsettingseditor.h"

class OutilinedButtonSettingsEditor : public TextButtonSettingsEditor
{
    Q_OBJECT

public:
    explicit OutilinedButtonSettingsEditor(QWidget *parent = nullptr);
    ~OutilinedButtonSettingsEditor();
};

#endif // OUTILINEDBUTTONSETTINGSEDITOR_H
