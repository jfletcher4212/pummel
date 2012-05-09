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
    //void showOptions();

    void addClassBox();
    void addEllipse();
    void addRoundedSquare();
    void addNote();
    void addScenarioStart();
    void addScenarioEnd();
    void addActor();
    void addNone();

    void addNoLine();
    void addSolidLine();
    void addDottedLine();
    void addSolidLineSAH();
    void addDottedLineSAH();
    void addSolidLineEAH();
    void addDottedLineEAH();
    void addSolidLineSD();
    void addDottedLineSD();
    void addSolidLineED();
    void addDottedLineED();
    void addSolidLineBAH();
    void addDottedLineBAH();
    void addSolidSQLine();
    void addDottedSQLine();
    void addSolidSQLineSAH();
    void addDottedSQLineSAH();
    void addSolidSQLineEAH();
    void addDottedSQLineEAH();
    void addSelfRefLine();
    void addSolidSQLineBAH();
    void addSolidSQLineSD();
    void addSolidSQLineED();

    void deleteSelected();

    void gridOn();
    void gridOff();

private:

    void createActions();
    void createMenus();



    QPushButton * shapeButton;
    QPushButton * textButton;
    QPushButton * lineButton;
    QPushButton * optionsButton;
    QPushButton * deleteButton;
    QPushButton * gridButton;

    QMenu *shapeMenu;
    QActionGroup *shapesGroup;
    QAction *addNoneAct;
    QAction *addClassBoxAct;
    QAction *addEllipseAct;
    QAction *addRoundedSquareAct;
    QAction *addScenarioStartAct;
    QAction *addScenarioEndAct;
    QAction *addActorAct;
    QAction *addNoteAct;

    QMenu *lineMenu;
    QActionGroup *linesGroup;
    QAction *addNoLineAct;
    QAction *addSolidLineAct;
    QAction *addDottedLineAct;
    QAction *addSolidLineSAHAct;
    QAction *addDottedLineSAHAct;
    QAction *addSolidLineEAHAct;
    QAction *addDottedLineEAHAct;
    QAction *addSolidLineSDAct;
    QAction *addDottedLineSDAct;
    QAction *addSolidLineEDAct;
    QAction *addDottedLineEDAct;
    QAction *addSolidLineBAHAct;
    QAction *addDottedLineBAHAct;
    QAction *addSolidSQLineAct;
    QAction *addDottedSQLineAct;
    QAction *addSolidSQLineSAHAct;
    QAction *addDottedSQLineSAHAct;
    QAction *addSolidSQLineEAHAct;
    QAction *addDottedSQLineEAHAct;
    QAction *addSelfRefLineAct;
    QAction *addSolidSQLineBAHAct;
    QAction *addSolidSQLineSDAct;
    QAction *addSolidSQLineEDAct;

    QAction *addExtendDLBAHAct;
    QAction *addIncludeDLBAHAct;

    QMenu *gridMenu;
    QActionGroup *gridOnOffToggleGroup;
    QAction *gridOnAct;
    QAction *gridOffAct;
};

#endif // TOOLBAR_H
