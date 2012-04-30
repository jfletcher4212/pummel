/* OptionsDialog
 * dialog that allows user to make changes to default properties of shapes, text, and lines
 * Coleman Beasley
 * Last Edit: Dec. 12, 2011
 */

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QErrorMessage;
class QGridLayout;
QT_END_NAMESPACE

class OptionsDialog : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsDialog(QWidget *parent = 0);
    //members
    QTabWidget *tabWidget;
    QWidget *shapeTab, *textTab, *lineTab;
    QString shapeFillColor, lineColor, textColor;
    int shapeWeight, lineWeight, textSize;
    QString textFont;


signals:

private:
    QTextEdit *shapeFillField, *shapeWeightField, *lineColorField, *textFontField, *textColorField ;
    QSpinBox *shapeWeightBox, *lineWeightBox, *textSizeBox;
    QPushButton *okButton, *cancelButton;
    void initValues();
    void buttonSetup();
    void shapeTabSetup();
    void textTabSetup();
    void lineTabSetup();


private slots:
    void acknowledge();
    void quit();

public slots:

};

#endif // OPTIONSDIALOG_H

