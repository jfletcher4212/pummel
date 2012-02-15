/*toolbar.cpp - includes the functions for the prototypes
                presented in toolbar.h
                Made by Coleman Beasley - 12/16/2011
*/
#include "toolbar.h"
#include "optionsdialog.h"
#include "drawarea.h"

#include "global.h"

Toolbar::Toolbar(QWidget *parent) :
    //QDialog(parent)
    QWidget(parent)
{
    this->setWindowModality(Qt::NonModal);
    options = new OptionsDialog;

    /* set defaults for Param variables
      */
    shape.fillColor = "black";
    shape.name = "pill";
    shape.weight = 1;
    text.color = "black";
    text.font = "Times New Roman";
    text.size = 1;
    line.color = "black";
    line.weight = 1;

    createActions();
    createMenus();

    QGridLayout *layout;
    layout = initButtons();
    setLayout(layout);

    shapeButton->setMenu(shapeMenu);
    gridButton->setMenu(gridMenu);
}

//create buttons and add to layout
QGridLayout * Toolbar::initButtons()
{
    //create buttons
    //shapeButton = new QPushButton(tr("Shape"), this);
    shapeButton = new QPushButton(tr("Shape"));
    textButton = new QPushButton(tr("Text"));
    lineButton = new QPushButton(tr("Line"));
    optionsButton = new QPushButton(tr("Options"));
    gridButton = new QPushButton(tr("Grid"));

    // connect buttons to slots
    connect(shapeButton, SIGNAL(clicked()), this, SLOT(insertShape()));
    connect(textButton, SIGNAL(clicked()), this, SLOT(insertText()));
    connect(lineButton, SIGNAL(clicked()), this, SLOT(insertLine()));
    connect(optionsButton, SIGNAL(clicked()), this, SLOT(showOptions()));
    connect(gridButton, SIGNAL(clicked()), this, SLOT(toggleGrid()));

    /* add created buttons to a grid layout
     * buttons are arranged in a single column
     */
    QGridLayout *layout = new QGridLayout;
    layout->setColumnStretch(1,0);
    layout->addWidget(shapeButton, 0, 0);
    layout->addWidget(lineButton, 1, 0);
    layout->addWidget(textButton, 2, 0);
    layout->addWidget(optionsButton, 3, 0);
    layout->addWidget(gridButton, 4, 0);

    return layout;
}

void Toolbar::createActions(){
    addRectAct = new QAction(tr("Rectangle"), this);
    addRectAct->setCheckable(true);
    connect(addRectAct, SIGNAL(triggered()), this, SLOT(addRect()));

    addEllipseAct = new QAction(tr("Ellipse"), this);
    addEllipseAct->setCheckable(true);
    connect(addEllipseAct, SIGNAL(triggered()), this, SLOT(addEllipse()));

    addSquareAct = new QAction(tr("Square"), this);
    addSquareAct->setCheckable(true);
    connect(addSquareAct, SIGNAL(triggered()), this, SLOT(addSquare()));

    addCircleAct = new QAction(tr("Circle"), this);
    addCircleAct->setCheckable(true);
    connect(addCircleAct, SIGNAL(triggered()), this, SLOT(addCircle()));

    addNoneAct = new QAction(tr("None"), this);
    addNoneAct->setCheckable(true);
    addNoneAct->setChecked(true);
    connect(addNoneAct, SIGNAL(triggered()), this, SLOT(addNone()));

    shapesGroup = new QActionGroup(this);
    shapesGroup->addAction(addNoneAct);
    shapesGroup->addAction(addRectAct);
    shapesGroup->addAction(addSquareAct);
    shapesGroup->addAction(addCircleAct);
    shapesGroup->addAction(addEllipseAct);

    gridOnAct = new QAction(tr("On"), this);
    gridOnAct->setCheckable(true);
    gridOnAct->setChecked(true);
    connect(gridOnAct, SIGNAL(triggered()), this, SLOT(gridOn()));

    gridOffAct = new QAction(tr("Off"), this);
    gridOffAct->setCheckable(true);
    connect(gridOffAct, SIGNAL(triggered()), this, SLOT(gridOff()));

    gridOnOffToggleGroup = new QActionGroup(this);
    gridOnOffToggleGroup->addAction(gridOnAct);
    gridOnOffToggleGroup->addAction(gridOffAct);
}

void Toolbar::createMenus(){
    shapeMenu = new QMenu(this);
    shapeMenu->addAction(addNoneAct);
    shapeMenu->addAction(addSquareAct);
    shapeMenu->addAction(addCircleAct);
    shapeMenu->addAction(addRectAct);
    shapeMenu->addAction(addEllipseAct);

    gridMenu = new QMenu(this);
    gridMenu->addAction(gridOnAct);
    gridMenu->addAction(gridOffAct);
}

void Toolbar::showOptions()
{
//    options->exec();
    options->show();
    shape.fillColor = options->shapeFillColor;
    shape.weight = options->shapeWeight;
    text.color = options->textColor;
    text.font = options->textFont;
    text.size = options->textSize;
    line.color = options->lineColor;
    line.weight = options->lineWeight;
}

/*  add a shape into the drawing area. Use the parent's
 * DrawArea object.  Use drawArea.insertShape, and pass in
 * the shape struct
 */
void Toolbar::insertShape(){
    shapeButton->showMenu();
}

/*  add text into the drawing area. Use the parent's
 * DrawArea object.  Use drawArea.insertText, and pass in
 * the text struct
 */
void Toolbar::insertText()
{

}

/*  add a line into the drawing area. Use the parent's
 * DrawArea object.  Use drawArea.insertLine, and pass in
 * the line struct.  Then call drawArea.lineConnect()?
 */
void Toolbar::insertLine()
{

}

void Toolbar::toggleGrid()
{
/*
    gridState = (gridState+1)%2;    //increment grid tracking variable
    if(gridState == 0)
        parent.drawArea.hideGrid();
    else
        parent.drawArea.showGrid();
*/
}

void Toolbar::addRect(){
    canvas->setSceneCreate(true);
    canvas->setSceneCreateMode(Rectangle);
}

void Toolbar::addSquare(){
    canvas->setSceneCreate(true);
    canvas->setSceneCreateMode(Square);
}

void Toolbar::addCircle(){
    canvas->setSceneCreate(true);
    canvas->setSceneCreateMode(Circle);
}

void Toolbar::addEllipse(){
    canvas->setSceneCreate(true);
    canvas->setSceneCreateMode(Ellipse);
}

void Toolbar::addNone(){
    canvas->setSceneCreate(false);
}

void Toolbar::gridOn(){
    canvas->setSceneGrid(true);
}

void Toolbar::gridOff(){
    canvas->setSceneGrid(false);
}
