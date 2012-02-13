/* Toolbar Class
 * has buttons that will insert various elements into Drawing Area
 * use Options button to change parameters of elements.
 * Coleman Beasley
 * Last Edit: Nov. 30, 2011
 */

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QDialog>
#include <QtGui>
#include "./OptionsDialog.h"
#include "params.h"

using namespace std;

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QErrorMessage;
class QTextEdit;
class QGridLayout;
QT_END_NAMESPACE

class Toolbar : public QWidget
{
    Q_OBJECT
private:
    OptionsDialog *options;
    QGridLayout *initButtons();
public:
    explicit Toolbar(QWidget *parent = 0);

    //parameters for shapes
    shapeParams shape;

    //parameters for lines
    lineParams line;

    //parameters for text
    textParams text;

    int gridState;      //int to toggle grid on and off, used in toggleGrid()

signals:

public slots:
    void insertShape();
    void insertLine();
    void insertText();
    void toggleGrid();
    void showOptions();

};

#endif // TOOLBAR_H
