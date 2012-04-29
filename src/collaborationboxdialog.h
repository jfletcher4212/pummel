/* collaborationboxdialog.h
 * CollaborationBoxDialog
 * dialog box that allows user to change the values in a roundedSquare object
 */
#ifndef COLLABORATIONBOXDIALOG_H
#define COLLABORATIONBOXDIALOG_H

#include "roundedsquare.h"

#include <QWidget>
#include <QDialog>
#include <QtGui>

class CollaborationBoxDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CollaborationBoxDialog(RoundedSquare *caller = 0);
    ~CollaborationBoxDialog();
    //Accessors
    QString getName();
    QString getMembers();

signals:

public slots:

private:
    QString m_name, m_members;
    QTextEdit *m_nameField, *m_membersField;
    QPushButton *m_okButton,*m_cancelButton;
    RoundedSquare *m_caller;
    void initFields();
    void buttonSetup();
private slots:
    void acknowledge();
    void quit();
};

#endif // COLLABORATIONBOXDIALOG_H
