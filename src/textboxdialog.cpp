#include "textboxdialog.h"

TextBoxDialog::TextBoxDialog(Icon *origCaller) :
    QWidget()
{
    this->setWindowTitle("Edit Text Box");
    //copy the original caller to the member m_caller
    m_caller = origCaller;

    //set dialog box to be modal
    this->setWindowModality(Qt::ApplicationModal);

    //main layout
    QFormLayout *layout = new QFormLayout();
    //separate layout for buttons
    QBoxLayout *buttonLayout = new QHBoxLayout();

    initFields();
    buttonSetup();

    //add buttons to their layout
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);

    //add controls to the main QFormLayout
    layout->addRow("Class Label", m_nameField);
    layout->addRow(buttonLayout);

    this->setLayout(layout);
}

/* copies values from caller into member variables
 * initializes other members of dialog
 */
void TextBoxDialog::initFields()
{
    //copy values from caller
    m_name = m_caller->getLabel();

    //initialize QTextEdits
    m_nameField = new QTextEdit();
    m_nameField->setText(m_name);
}

//create buttons for closing dialog
void TextBoxDialog::buttonSetup()
{
    m_okButton = new QPushButton(tr("OK"));
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(acknowledge()));
    m_cancelButton = new QPushButton(tr("Cancel"));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(quit()));
}

//update the member variables when 'OK' is clicked
void TextBoxDialog::acknowledge()
{

    //copy data here
    m_name = m_nameField->toPlainText();

    m_caller->setText(m_name);

    quit();
}

//close the dialog
void TextBoxDialog::quit()
{
    this->close();
}

QString TextBoxDialog::getName()
{
    return m_name;
}

