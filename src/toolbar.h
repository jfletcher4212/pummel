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
#include "drawarea.h"
#include "global.h"
#include "optionsdialog.h"
#include "params.h"
#include "icon.h"
#include "linebody.h"

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
    void canvasSync();
    void setAvailableActions();

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

    void addClassBox();
    void addEllipse();
    void addRoundedSquare();
    void addNote();
    void addNone();

    void addNoLine();
    void addSolidLine();
    void addDottedLine();
    void addSolidLineAH();
    void addSolidSQLine();
    void addDottedSQLine();

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
    QAction *addClassBoxAct;
    QAction *addEllipseAct;
    QAction *addRoundedSquareAct;
    QAction *addNoteAct;

    QMenu *lineMenu;
    QActionGroup *linesGroup;
    QAction *addNoLineAct;
    QAction *addSolidLineAct;
    QAction *addDottedLineAct;
    QAction *addSolidLineAHAct;
    QAction *addSolidSQLineAct;
    QAction *addDottedSQLineAct;

    QMenu *gridMenu;
    QActionGroup *gridOnOffToggleGroup;
    QAction *gridOnAct;
    QAction *gridOffAct;
};

#endif // TOOLBAR_H
