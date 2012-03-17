/* textdialog.h
 * TextDialog
 * dialog box that allows user to change the values in a ClassBox object
 */
#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include "classbox.h"

#include <QWidget>
#include <QDialog>
#include <QtGui>

class TextDialog : public QWidget
{
    Q_OBJECT
public:
    explicit TextDialog(ClassBox *caller = 0);
    //Accessors
    QString getName();
    QString getMembers();
    QString getMethods();

signals:

public slots:

private:
    QString m_name, m_members, m_methods;
    QTextEdit *m_nameField, *m_membersField, *m_methodsField;
    QPushButton *m_okButton,*m_cancelButton;
    ClassBox *m_caller;
    void initFields(ClassBox *caller);
    void buttonSetup();
private slots:
    void acknowledge();
    void quit();
};

#endif // TEXTDIALOG_H
