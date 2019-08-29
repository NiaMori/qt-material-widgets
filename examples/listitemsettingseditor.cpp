#include "listitemsettingseditor.h"
#include <QColorDialog>
#include <qtmateriallistitem.h>
#include <lib/qtmaterialtheme.h>

ListItemSettingsEditor::ListItemSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ListItemSettingsForm),
      m_listitem(new QtMaterialListItem())
{
    m_listitem->setLetter( QString("This is the first, image+icon+text, lineitem. I want the string to be longer and longer to test clipping." ));
    m_listitem->setIcon(QtMaterialTheme::icon("communication", "message"));
    m_listitem->setImage(QImage(":/images/assets/sikh.jpg"));
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    QtMaterialListItem *m_listitem2 = new QtMaterialListItem;
    m_listitem2->setLetter( QString("This is the second, icon+text, lineitem. I want the string to be longer and longer to test clipping." ));
    m_listitem2->setIcon(QtMaterialTheme::icon("communication", "message"));

    QtMaterialListItem *m_listitem3 = new QtMaterialListItem;
    m_listitem3->setLetter( QString("This is the third, text only, lineitem. I want the string to be longer and longer to test clipping." ));

//     m_listitem2->setImage(QImage(":/images/assets/sikh.jpg"));


    layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    canvas->setLayout(layout);
    layout->addWidget(m_listitem);
    layout->addWidget(m_listitem2);
    layout->addWidget(m_listitem3);
//    layout->setAlignment(m_listitem, Qt::AlignCenter);
    layout->addStretch();

    setupForm();

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
    connect(ui->typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidget()));
    connect(ui->backgroundColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(ui->textColorToolButton, SIGNAL(pressed()), this, SLOT(selectColor()));

    ui->sizeSpinBox->setRange(5, 300);
}

ListItemSettingsEditor::~ListItemSettingsEditor()
{
    delete ui;
}

void ListItemSettingsEditor::setupForm()
{
    switch (m_listitem->type())
    {
    case Material::LetterListItem:
        ui->typeComboBox->setCurrentIndex(0);
        break;
    case Material::ImageListItem:
        ui->typeComboBox->setCurrentIndex(1);
        break;
    case Material::IconListItem:
        ui->typeComboBox->setCurrentIndex(2);
        break;
    default:
        break;
    }

    ui->disabledCheckBox->setChecked(!m_listitem->isEnabled());
    ui->useThemeColorsCheckBox->setChecked(m_listitem->useThemeColors());
    ui->sizeSpinBox->setValue(m_listitem->size());
}

void ListItemSettingsEditor::updateWidget()
{
    switch (ui->typeComboBox->currentIndex())
    {
    case 0:
        m_listitem->setLetter(QChar('X'));
        break;
    case 1:
        m_listitem->setImage(QImage(":/images/assets/sikh.jpg"));
        break;
    case 2:
        m_listitem->setIcon(QtMaterialTheme::icon("communication", "message"));
        break;
    default:
        break;
    }

    m_listitem->setDisabled(ui->disabledCheckBox->isChecked());
    m_listitem->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    m_listitem->setSize(ui->sizeSpinBox->value());
}

void ListItemSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("textColorToolButton" == senderName) {
            m_listitem->setTextColor(color);
            ui->textColorLineEdit->setText(color.name(QColor::HexRgb));
        } else if ("backgroundColorToolButton" == senderName) {
            m_listitem->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
