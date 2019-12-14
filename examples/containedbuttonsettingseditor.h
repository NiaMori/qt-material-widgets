#ifndef CONTAINEDBUTTONSETTINGSEDITOR_H
#define CONTAINEDBUTTONSETTINGSEDITOR_H

#include "textbuttonsettingseditor.h"

class ContainedButtonSettingsEditor : public TextButtonSettingsEditor
{
    Q_OBJECT

public:
    explicit ContainedButtonSettingsEditor(QWidget *parent = 0);
    ~ContainedButtonSettingsEditor();
};

#endif // CONTAINEDBUTTONSETTINGSEDITOR_H
