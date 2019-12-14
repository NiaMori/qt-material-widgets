#include "containedbuttonsettingseditor.h"
#include <qtmaterialcontainedbutton.h>

ContainedButtonSettingsEditor::ContainedButtonSettingsEditor(QWidget *parent)
    : TextButtonSettingsEditor(new QtMaterialContainedButton("Contained Button"), parent)
{
    ui->transparentCheckBox->setDisabled(true);
    ui->defaultPresetPushButton->setDisabled(true);
    ui->checkablePresetPushButton->setDisabled(true);
}

ContainedButtonSettingsEditor::~ContainedButtonSettingsEditor()
{
}
