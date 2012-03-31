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
#include "optionsdialog.h"
#include "params.h"
#include "icon.h"

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

public slots:
    void insertShape();
    void insertLine();
    void insertText();
    void showOptions();

    void addRect();
    void addSquare();
    void addCircle();
    void addEllipse();
    void addNone();

    void gridOn();
    void gridOff();

private:

    void createActions();
    void createMenus();


    QPushButton * shapeButton;
    QPushButton * textButton;
    QPushButton * lineButton;
    QPushButton * optionsButton;
    QPushButton * gridButton;

    QMenu *shapeMenu;
    QActionGroup *shapesGroup;
    QAction *addNoneAct;
    QAction *addSquareAct;
    QAction *addCircleAct;
    QAction *addRectAct;
    QAction *addEllipseAct;

    QMenu *gridMenu;
    QActionGroup *gridOnOffToggleGroup;
    QAction *gridOnAct;
    QAction *gridOffAct;
};

#endif // TOOLBAR_H
