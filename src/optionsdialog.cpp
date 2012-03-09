/*optionsdialog.cpp - includes the functions for the prototypes
                      defined in optionsdialog.h
                      Made by Coleman Beasley - 12/16/2011
  */
#include "optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowModality(Qt::ApplicationModal);

    //initialize values
    initValues();

    //set up buttons
    buttonSetup();
    //set up tabs
    tabWidget = new QTabWidget;
    shapeTab = new QWidget;
    shapeTabSetup();
    lineTab = new QWidget;
    lineTabSetup();
    textTab = new QWidget;
    textTabSetup();

    tabWidget->addTab(shapeTab, tr("Shape"));
    tabWidget->addTab(lineTab, tr("Line"));
    tabWidget->addTab(textTab, tr("Text"));

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(okButton);
    mainLayout->addWidget(cancelButton);
    setLayout(mainLayout);
}

void OptionsDialog::initValues()
{
    //init shape variables
    shapeFillColor = "white";
    shapeWeight = 1;

    //init line variables
    lineColor = "black";
    lineWeight = 1;

    //init text variables
    textColor = "black";
    textSize = 1;
    textFont = "Arial";
}

//create buttons for closing dialog
void OptionsDialog::buttonSetup()
{
    okButton = new QPushButton(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(acknowledge()));
    cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(quit()));
}

// add fields to the shapeTab Widget
void OptionsDialog::shapeTabSetup()
{
    //initalize fields and labels
    shapeFillField = new QTextEdit;
    shapeFillField->setFixedHeight(25);
    QLabel *fillLabel = new QLabel;
    fillLabel->setText("Shape Fill Color");

//    shapeWeightField = new QTextEdit;
//    shapeWeightField->setFixedHeight(25);
    QLabel *weightLabel = new QLabel;
    weightLabel->setText("Shape Weight");
    shapeWeightBox = new QSpinBox;
    shapeWeightBox->setSingleStep(1);
    shapeWeightBox->setValue(shapeWeight);

    /* create the widget's layout
     * labels on left, fields on right
     */
    QGridLayout * layout = new QGridLayout;
    layout->addWidget(shapeFillField, 0, 1);
    layout->addWidget(fillLabel, 0, 0);
//    layout->addWidget(shapeWeightField, 1, 1);
    layout->addWidget(weightLabel, 1, 0);
    layout->addWidget(shapeWeightBox, 1, 1);
    shapeTab->setLayout(layout);
}

// add fields to the lineTab Widget
void OptionsDialog::lineTabSetup()
{
    //initalize fields and labels
    lineColorField = new QTextEdit;
    lineColorField->setFixedHeight(25);
    QLabel *colorLabel = new QLabel;
    colorLabel->setText("Line Color");

    lineWeightBox = new QSpinBox;
    lineWeightBox->setSingleStep(1);
    lineWeightBox->setValue(lineWeight);
    QLabel *weightLabel = new QLabel;
    weightLabel->setText("Line Weight");

    /* create the widget's layout
     * labels on left, fields on right
     */
    QGridLayout *layout = new QGridLayout;
    layout->setRowStretch(0,1 );
    layout->addWidget(colorLabel, 0, 0);
    layout->addWidget(lineColorField, 0, 1);
    layout->addWidget(weightLabel, 1, 0);
    layout->addWidget(lineWeightBox, 1, 1);
    lineTab->setLayout(layout);
}

//add fields to the textTab Widget
void OptionsDialog::textTabSetup()
{
    //initalize fields and labels
    textFontField = new QTextEdit;
    textFontField->setFixedHeight(25);
    QLabel *fontLabel = new QLabel;
    fontLabel->setText("Font");

    textColorField = new QTextEdit;
    textColorField->setFixedHeight(25);
    QLabel *colorLabel = new QLabel;
    colorLabel->setText("Text Color");

    textSizeBox = new QSpinBox;
    textSizeBox->setSingleStep(1);
    textSizeBox->setValue(textSize);
    QLabel *sizeLabel = new QLabel;
    sizeLabel->setText("Font Size");

    /* create the widget's layout
     * labels on left, fields on right
     */
    QGridLayout *layout = new QGridLayout;
//    layout->setRowStretch(0, 1);
    layout->addWidget(fontLabel, 0, 0);
    layout->addWidget(textFontField, 0, 1);
    layout->addWidget(colorLabel, 1, 0);
    layout->addWidget(textColorField, 1, 1);
    layout->addWidget(sizeLabel, 2, 0);
    layout->addWidget(textSizeBox, 2, 1);
    textTab->setLayout(layout);
}

/* take the values from the fields of the dialog
 * and plug them into the data members
 */
void OptionsDialog::acknowledge()
{
    //copy data here
    //shape
    shapeFillColor = shapeFillField->toPlainText();
    shapeWeight = shapeWeightBox->value();
    //line
    lineColor = lineColorField->toPlainText();
    lineWeight = lineWeightBox->value();
    //text
    textColor = textColorField->toPlainText();
    textFont = textFontField->toPlainText();
    textSize = textSizeBox->value();

    quit();
}

/* close the dialog box
 */
void OptionsDialog::quit()
{
    this->close();
}

