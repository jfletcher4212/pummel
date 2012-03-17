#include "textdialog.h"

TextDialog::TextDialog(QWidget *parent, ClassBox *caller) :
    QWidget(parent)
{
    initValues(caller);
}

/* copies values from caller into member variables
 * initializes other members of dialog
 */
void TextDialog::initValues(ClassBox *caller)
{
    //copy values from caller
    m_name = caller->getLabel();
    m_members = caller->getMembers();
    m_methods = caller->getMethods();

    //initialize QTextEdits
    m_nameField = new QTextEdit();
    m_nameField->setText(m_name);
    m_membersField = new QTextEdit();
    m_membersField->setText(m_members);
    m_methodsField = new QTextEdit();
    m_methodsField->setText(m_methods);
}
