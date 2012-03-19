#include "textdialog.h"

TextDialog::TextDialog(ClassBox *origCaller) :
    QWidget()
{
    this->setWindowTitle("Edit Class Box");
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
    layout->addRow("Class Members", m_membersField);
    layout->addRow("Class Methods", m_methodsField);
    layout->addRow(buttonLayout);

    this->setLayout(layout);
}

/* copies values from caller into member variables
 * initializes other members of dialog
 */
void TextDialog::initFields()
{
    //copy values from caller
    m_name = m_caller->getLabel();
    m_members = m_caller->getMembers();
    m_methods = m_caller->getMethods();

    //initialize QTextEdits
    m_nameField = new QTextEdit();
    m_nameField->setText(m_name);
    m_membersField = new QTextEdit();
    m_membersField->setText(m_members);
    m_methodsField = new QTextEdit();
    m_methodsField->setText(m_methods);
}

//create buttons for closing dialog
void TextDialog::buttonSetup()
{
    m_okButton = new QPushButton(tr("OK"));
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(acknowledge()));
    m_cancelButton = new QPushButton(tr("Cancel"));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(quit()));
}

//update the member variables when 'OK' is clicked
void TextDialog::acknowledge()
{

    //copy data here
    m_name = m_nameField->toPlainText();
    m_members = m_membersField->toPlainText();
    m_methods = m_methodsField->toPlainText();

    m_caller->setLabel(m_name);
    m_caller->setMembers(m_members);
    m_caller->setMethods(m_methods);

    quit();
}

//close the dialog
void TextDialog::quit()
{
    this->close();
}

QString TextDialog::getName()
{
    return m_name;
}

QString TextDialog::getMembers()
{
    return m_members;
}

QString TextDialog::getMethods()
{
    return m_members;
}
