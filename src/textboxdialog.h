/* textdialog.h
 * TextDialog
 * dialog box that allows user to change the values in a ClassBox object
 * TODO:    setup tab order to allow easy input
 *          resize window to a more reasonable size
 */

#ifndef TEXTBOXDIALOG_H
#define TEXTBOXDIALOG_H

#include "icon.h"

#include <QWidget>
#include <QDialog>
#include <QtGui>

class TextBoxDialog : public QWidget
{
    Q_OBJECT
public:
    explicit TextBoxDialog(Icon *caller = 0);
    //Accessors
    QString getName();

signals:

public slots:

private:
    QString m_name;
    QTextEdit *m_nameField;
    QPushButton *m_okButton,*m_cancelButton;
    Icon *m_caller;
    void initFields();
    void buttonSetup();
private slots:
    void acknowledge();
    void quit();
};

#endif // TEXTBOXDIALOG_H
