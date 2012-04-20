#include "collaborationboxdialog.h"

 CollaborationBoxDialog::CollaborationBoxDialog(RoundedSquare *origCaller) :
    QWidget()
{
    this->setWindowTitle("Edit Collaboration Box");
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
    layout->addRow("State Label", m_nameField);
    layout->addRow("Members", m_membersField);
    layout->addRow(buttonLayout);

    this->setLayout(layout);
}

CollaborationBoxDialog::~CollaborationBoxDialog()
{
    //delete fields
    delete m_nameField;
    delete m_membersField;

    //delete buttons
    delete m_okButton;
    delete m_cancelButton;

}

/* copies values from caller into member variables
 * initializes other members of dialog
 */
void CollaborationBoxDialog::initFields()
{
    //copy values from caller
    m_name = m_caller->getLabel();
    m_members = m_caller->getMembers();

    //initialize QTextEdits
    m_nameField = new QTextEdit();
    m_nameField->setText(m_name);
    m_membersField = new QTextEdit();
    m_membersField->setText(m_members);
}

//create buttons for closing dialog
void CollaborationBoxDialog::buttonSetup()
{
    m_okButton = new QPushButton(tr("OK"));
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(acknowledge()));
    m_cancelButton = new QPushButton(tr("Cancel"));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(quit()));
}

//update the member variables when 'OK' is clicked
void CollaborationBoxDialog::acknowledge()
{

    //copy data here
    m_name = m_nameField->toPlainText();
    m_members = m_membersField->toPlainText();

    m_caller->setLabel(m_name);
    m_caller->setMembers(m_members);

    quit();
}

//close the dialog
void CollaborationBoxDialog::quit()
{
    this->close();
}

QString CollaborationBoxDialog::getName()
{
    return m_name;
}

QString CollaborationBoxDialog::getMembers()
{
    return m_members;
}
