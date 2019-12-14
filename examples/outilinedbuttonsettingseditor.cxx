#include "outilinedbuttonsettingseditor.h"
#include <qtmaterialoutlinedbutton.h>

OutilinedButtonSettingsEditor::OutilinedButtonSettingsEditor(QWidget *parent)
    : TextButtonSettingsEditor(new QtMaterialOutlinedButton("Outlined Button"), parent)
{
  ui->transparentCheckBox->setChecked(true);
  ui->transparentCheckBox->setDisabled(true);
}

OutilinedButtonSettingsEditor::~OutilinedButtonSettingsEditor()
{
}
