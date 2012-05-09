/*toolbar.cpp - includes the functions for the prototypes
                presented in toolbar.h
                Made by Coleman Beasley - 12/16/2011
*/
#include "global.h"
#include "toolbar.h"
#include "optionsdialog.h"
#include "drawarea.h"
#include "icon.h"


Toolbar::Toolbar(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowModality(Qt::NonModal);
    options = new OptionsDialog;

    createActions();

    QGridLayout *layout;
    layout = initButtons();
    setLayout(layout);

    createMenus();
}

//create buttons and add to layout
QGridLayout * Toolbar::initButtons()
{
    //create buttons
    shapeButton = new QPushButton(tr("Shape"));
    textButton = new QPushButton(tr("Text"));
    lineButton = new QPushButton(tr("Line"));
    gridButton = new QPushButton(tr("Grid"));
    deleteButton = new QPushButton(tr("Delete Selected"));

    // connect buttons to slots
    connect(shapeButton, SIGNAL(clicked()), this, SLOT(insertShape()));
    connect(textButton, SIGNAL(clicked()), this, SLOT(addNote()));
    connect(lineButton, SIGNAL(clicked()), this, SLOT(insertLine()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteSelected()));

    /* add created buttons to a grid layout
     * buttons are arranged in a single column
     */
    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(1,0);
    layout->addWidget(shapeButton, 0, 0);
    layout->addWidget(lineButton, 1, 0);
    layout->addWidget(textButton, 2, 0);
    layout->addWidget(gridButton, 3, 0);
    layout->addWidget(deleteButton, 4, 0);

    return layout;
}

void Toolbar::createActions(){

    //create shape actions
    addNoneAct = new QAction(tr("None"), this);
    addNoneAct->setCheckable(true);
    addNoneAct->setChecked(true);
    connect(addNoneAct, SIGNAL(triggered()), this, SLOT(addNone()));

    addEllipseAct = new QAction(tr("Use Case"), this);
    addEllipseAct->setCheckable(true);
    connect(addEllipseAct, SIGNAL(triggered()), this, SLOT(addEllipse()));

    addClassBoxAct = new QAction(tr("Class Box"), this);
    addClassBoxAct->setCheckable(true);
    connect(addClassBoxAct, SIGNAL(triggered()), this, SLOT(addClassBox()));

    addRoundedSquareAct = new QAction(tr("State"), this);
    addRoundedSquareAct->setCheckable(true);
    connect(addRoundedSquareAct, SIGNAL(triggered()), this, SLOT(addRoundedSquare()));

    addScenarioStartAct = new QAction(tr("Start"), this);
    addScenarioStartAct->setCheckable(true);
    connect(addScenarioStartAct, SIGNAL(triggered()), this, SLOT(addScenarioStart()));

    addScenarioEndAct = new QAction(tr("End"), this);
    addScenarioEndAct->setCheckable(true);
    connect(addScenarioEndAct, SIGNAL(triggered()), this, SLOT(addScenarioEnd()));

    addActorAct = new QAction(tr("Actor"), this);
    addActorAct->setCheckable(true);
    connect(addActorAct, SIGNAL(triggered()), this, SLOT(addActor()));

    addNoteAct = new QAction(tr("Note"), this);
    addNoteAct->setCheckable(true);
    connect(addNoteAct, SIGNAL(triggered()), this, SLOT(addNote()));

    addSolidLineAct = new QAction(tr("Interaction"), this);
    addSolidLineAct->setCheckable(true);
    connect(addSolidLineAct, SIGNAL(triggered()), this, SLOT(addSolidLine()));

    addSolidLineEAHAct = new QAction(tr("Generalization"), this);
    addSolidLineEAHAct->setCheckable(true);
    connect(addSolidLineEAHAct, SIGNAL(triggered()), this, SLOT(addSolidLineEAH()));

    addSolidLineBAHAct = new QAction(tr("Event/Action"), this);
    addSolidLineBAHAct->setCheckable(true);
    connect(addSolidLineBAHAct, SIGNAL(triggered()), this, SLOT(addSolidLineBAH()));

    addDottedLineBAHAct = new QAction(tr("Depends On"), this);
    addDottedLineBAHAct->setCheckable(true);
    connect(addDottedLineBAHAct, SIGNAL(triggered()), this, SLOT(addDottedLineBAH()));

    addExtendDLBAHAct = new QAction(tr("Extend"), this);
    addExtendDLBAHAct->setCheckable(true);
    connect(addExtendDLBAHAct, SIGNAL(triggered()), this, SLOT(addDottedLineBAH()));

    addIncludeDLBAHAct = new QAction(tr("Include"), this);
    addIncludeDLBAHAct->setCheckable(true);
    connect(addDottedLineBAHAct, SIGNAL(triggered()), this, SLOT(addDottedLineBAH()));

    addSolidSQLineEAHAct = new QAction(tr("Inherits From"), this);
    addSolidSQLineEAHAct->setCheckable(true);
    connect(addSolidSQLineEAHAct, SIGNAL(triggered()), this, SLOT(addSolidSQLineEAH()));

    addDottedSQLineEAHAct = new QAction(tr("Implements Interface"), this);
    addDottedSQLineEAHAct->setCheckable(true);
    connect(addDottedSQLineEAHAct, SIGNAL(triggered()), this, SLOT(addDottedSQLineEAH()));

    addSelfRefLineAct = new QAction(tr("Self Referencing Line"), this);
    addSelfRefLineAct->setCheckable(true);
    connect(addSelfRefLineAct, SIGNAL(triggered()), this, SLOT(addSelfRefLine()));

    addSolidSQLineBAHAct = new QAction(tr("Is Associated with"), this);
    addSolidSQLineBAHAct->setCheckable(true);
    connect(addSolidSQLineBAHAct, SIGNAL(triggered()), this, SLOT(addSolidSQLineBAH()));

    addSolidSQLineSDAct = new QAction(tr("Is an Aggregate of"), this);
    addSolidSQLineSDAct->setCheckable(true);
    connect(addSolidSQLineSDAct, SIGNAL(triggered()), this, SLOT(addSolidSQLineSD()));

    addSolidSQLineEDAct = new QAction(tr("Is Composed of"), this);
    addSolidSQLineEDAct->setCheckable(true);
    connect(addSolidSQLineEDAct, SIGNAL(triggered()), this, SLOT(addSolidSQLineED()));

    addNoLineAct = new QAction(tr("None"), this);
    addNoLineAct->setCheckable(true);
    addNoLineAct->setChecked(true);
    connect(addNoLineAct, SIGNAL(triggered()), this, SLOT(addNoLine()));

    gridOnAct = new QAction(tr("On"), this);
    gridOnAct->setCheckable(true);
    gridOnAct->setChecked(true);
    connect(gridOnAct, SIGNAL(triggered()), this, SLOT(gridOn()));

    gridOffAct = new QAction(tr("Off"), this);
    gridOffAct->setCheckable(true);
    connect(gridOffAct, SIGNAL(triggered()), this, SLOT(gridOff()));
}

void Toolbar::createMenus(){
    shapeMenu = new QMenu(this);
    shapesGroup = new QActionGroup(this);
    shapesGroup->setExclusive(true);

    lineMenu = new QMenu(this);
    linesGroup = new QActionGroup(this);
    linesGroup->setExclusive(true);

    gridMenu = new QMenu(this);
    gridOnOffToggleGroup = new QActionGroup(this);
    gridOnOffToggleGroup->setExclusive(true);

    shapeButton->setMenu(shapeMenu);
    lineButton->setMenu(lineMenu);
    gridButton->setMenu(gridMenu);

}

//filter actions on the toolbar based on the active diagram's type
void Toolbar::setAvailableActions()
{
    //get the type of the active diagram
    DiagramType type;
    type = canvas.at(tabWidget->currentIndex())->getDiagramType();

    //get rid of all actions in menu before adding new ones.
    delete shapeMenu;
    delete shapesGroup;
    delete lineMenu;
    delete linesGroup;
    delete gridMenu;
    delete gridOnOffToggleGroup;
    createMenus();

    shapeButton->setMenu(shapeMenu);
    lineButton->setMenu(lineMenu);
    gridButton->setMenu(gridMenu);

    //None action should always be loaded
    shapesGroup->addAction(addNoneAct);
    linesGroup->addAction(addNoLineAct);

    switch (type)
    {
    case Class:         // I.E. Class
    {
        shapesGroup->addAction(addClassBoxAct);
        linesGroup->addAction(addDottedLineBAHAct);
        linesGroup->addAction(addSolidSQLineEAHAct);
        linesGroup->addAction(addDottedSQLineEAHAct);
        linesGroup->addAction(addSolidSQLineBAHAct);
        linesGroup->addAction(addSolidSQLineEDAct);
        linesGroup->addAction(addSolidSQLineSDAct);

        break;
    }
    case StateChart:
    {
        shapesGroup->addAction(addScenarioStartAct);
        shapesGroup->addAction(addRoundedSquareAct);
        shapesGroup->addAction(addScenarioEndAct);
        linesGroup->addAction(addSolidLineBAHAct);
        linesGroup->addAction(addSelfRefLineAct);

        break;
    }
    case Sequence:         // Sequence
    {
        break;
    }
    case UseCase:         // UseCase
    {
        shapesGroup->addAction(addActorAct);
        shapesGroup->addAction(addEllipseAct);
        linesGroup->addAction(addSolidLineAct);
        linesGroup->addAction(addExtendDLBAHAct);
        linesGroup->addAction(addIncludeDLBAHAct);
        linesGroup->addAction(addSolidLineEAHAct);

        break;
    }
    }


    //add grid actions
    gridOnOffToggleGroup->addAction(gridOnAct);
    gridOnOffToggleGroup->addAction(gridOffAct);


    //set group defaults
    shapesGroup->actions().at(0)->setChecked(true);
    linesGroup->actions().at(0)->setChecked(true);
    gridOnOffToggleGroup->actions().at(0)->setChecked(true);


    //add QActionGroups to QMenus
    shapeMenu->addActions(shapesGroup->actions());
    lineMenu->addActions(linesGroup->actions());
    gridMenu->addActions(gridOnOffToggleGroup->actions());
}

/*  add a shape into the drawing area. Use the parent's
 * DrawArea object.  Use drawArea.insertShape, and pass in
 * the shape struct
 */
void Toolbar::deleteSelected()
{
    int iconSelectedIndex = -1;
    for(int i = 0; i < canvas.at(tabWidget->currentIndex())->scene->getObjectList().size(); i++)
    {
        if(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(i)->isSelected())
        {
            iconSelectedIndex = i;
        }
    }

    if(iconSelectedIndex < 0)
    {
        return;
    }
    else
    {
        // this needs to also do an index shift or file loading will break
        canvas.at(tabWidget->currentIndex())->scene->deleteItem(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(iconSelectedIndex));
    }
}

void Toolbar::insertShape()
{
    shapeButton->showMenu();
}

void Toolbar::insertLine()
{
    lineButton->showMenu();
}

void Toolbar::addEllipse(){
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_Ellipse);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(No_Line);
    linesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addClassBox(){
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_Classbox);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(No_Line);
    linesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addRoundedSquare()
{
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_RoundedSquare);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(No_Line);
    linesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addScenarioStart()
{
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_ScenarioStart);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(No_Line);
    linesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addScenarioEnd()
{
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_ScenarioEnd);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(No_Line);
    linesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addActor()
{
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_Actor);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(No_Line);
    linesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addNone(){
    canvas.at(tabWidget->currentIndex())->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
}

void Toolbar::addNote()
{
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    //set shape and line menus to check 'None'
    shapesGroup->actions().at(0)->setChecked(true);
    linesGroup->actions().at(0)->setChecked(true);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_Note);
}

void Toolbar::addSolidLine()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Line);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}
void Toolbar::addSolidLineEAH()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Line_EAH);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}
void Toolbar::addSolidLineBAH()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Line_BAH);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addDottedLineBAH()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Dotted_Line_BAH);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}
void Toolbar:: addSolidSQLineEAH()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Sq_Line_EAH);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}

void Toolbar:: addDottedSQLineEAH()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Dotted_Sq_Line_EAH);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addSelfRefLine()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Self_Ref_Line);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addSolidSQLineBAH()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Sq_Line_BAH);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addSolidSQLineSD()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Sq_Line_SD);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addSolidSQLineED()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Sq_Line_ED);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
    shapesGroup->actions().at(0)->setChecked(true);
}

void Toolbar::addNoLine()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(No_Line);
}

void Toolbar::gridOn(){
    canvas.at(tabWidget->currentIndex())->setSceneGrid(true);
}

void Toolbar::gridOff(){
    canvas.at(tabWidget->currentIndex())->setSceneGrid(false);
}

void Toolbar::canvasSync()
{
    ShapeCreationType s_type = canvas.at(tabWidget->currentIndex())->getSceneShapeCreationType();
    LineType l_type = canvas.at(tabWidget->currentIndex())->getLineCreationType();

    if(canvas.at(tabWidget->currentIndex())->getLineCreate() && canvas.at(tabWidget->currentIndex())->getSceneCreate())
    {
        printf("line and shape create both set\n");
    }

    // if shape creation mode is off, set the menu to None
    if(canvas.at(tabWidget->currentIndex())->getSceneCreate())
    {
        switch(s_type){
        case s_Classbox:
        {
            this->addClassBox();
            addNoneAct->setChecked(false);
            addClassBoxAct->setChecked(true);
            break;
        }
        case s_Ellipse:
        {
            this->addEllipse();
            addEllipseAct->setChecked(true);
            break;
        }
        case s_None:
        {
            this->addNone();
            addNoneAct->setChecked(true);
            break;
        }
        case s_Note:
        {
            this->addNote();
            break;
        }
        case s_ScenarioStart:
        {
            this->addScenarioStart();
            break;
        }
        case s_ScenarioEnd:
        {
            this->addScenarioEnd();
            break;
        }
		case s_RoundedSquare:
		{
			this->addRoundedSquare();
			break;
		}
        default:
        {
            printf("no ShapeCreationType defined...\n");
        }
        }
    }
    else
    {
        this->addNone();
        addNoneAct->setChecked(true);
    }

    // if the line creation mode is off, set the menu to No Line
    if(canvas.at(tabWidget->currentIndex())->getLineCreate())
    {
        switch(l_type){
        case No_Line:
        {
            this->addNoLine();
            addNoLineAct->setChecked(true);
            break;
        }
        case Solid_Line:
        {
            this->addSolidLine();
            addSolidLineAct->setChecked(true);
            break;
        }
        case Solid_Line_EAH:
        {
            this->addSolidLineEAH();
            addSolidLineEAHAct->setChecked(true);
            break;
        }
        case Solid_Sq_Line_EAH:
        {
            this->addSolidSQLineEAH();
            addSolidSQLineEAHAct->setChecked(true);
            break;
        }
        case Dotted_Sq_Line_EAH:
        {
            this->addDottedSQLineEAH();
            addDottedSQLineEAHAct->setChecked(true);
            break;
        }
        case Self_Ref_Line:
        {
            this->addSelfRefLine();
            addSelfRefLineAct->setChecked(true);
            break;
        }
        case Solid_Sq_Line_BAH:
        {
            this->addSolidSQLineBAH();
            addSolidSQLineBAHAct->setChecked(true);
            break;
        }
        case Solid_Sq_Line_SD:
        {
            this->addSolidSQLineSD();
            addSolidSQLineSDAct->setChecked(true);
            break;
        }
        case Solid_Sq_Line_ED:
        {
            this->addSolidSQLineED();
            addSolidSQLineEDAct->setChecked(true);
            break;
        }
        default:
        {
            printf("no LineType defined...\n");
        }
        }
    }
    else
    {
        this->addNoLine();
        addNoLineAct->setChecked(true);
    }
}
