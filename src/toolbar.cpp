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
    lineButton->setMenu(lineMenu);
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

    addEllipseAct = new QAction(tr("Ellipse"), this);
    addEllipseAct->setCheckable(true);
    connect(addEllipseAct, SIGNAL(triggered()), this, SLOT(addEllipse()));

    addClassBoxAct = new QAction(tr("Class Box"), this);
    addClassBoxAct->setCheckable(true);
    connect(addClassBoxAct, SIGNAL(triggered()), this, SLOT(addClassBox()));

    addNoneAct = new QAction(tr("None"), this);
    addNoneAct->setCheckable(true);
    addNoneAct->setChecked(true);
    connect(addNoneAct, SIGNAL(triggered()), this, SLOT(addNone()));

    shapesGroup = new QActionGroup(this);
    shapesGroup->addAction(addNoneAct);
    shapesGroup->addAction(addClassBoxAct);
    shapesGroup->addAction(addEllipseAct);

    addSolidLineAct = new QAction(tr("Solid Line"), this);
    addSolidLineAct->setCheckable(true);
    connect(addSolidLineAct, SIGNAL(triggered()), this, SLOT(addSolidLine()));

    addDottedLineAct = new QAction(tr("Dotted Line"), this);
    addDottedLineAct->setCheckable(true);
    connect(addDottedLineAct, SIGNAL(triggered()), this, SLOT(addDottedLine()));

    addSolidLineAHAct = new QAction(tr("Solid line w/solid arrow head"), this);
    addSolidLineAHAct->setCheckable(true);
    connect(addSolidLineAHAct, SIGNAL(triggered()), this, SLOT(addSolidLineAH()));

    addNoLineAct = new QAction(tr("None"), this);
    addNoLineAct->setCheckable(true);
    addNoLineAct->setChecked(true);
    connect(addNoLineAct, SIGNAL(triggered()), this, SLOT(addNoLine()));

    linesGroup = new QActionGroup(this);
    linesGroup->addAction(addNoLineAct);
    linesGroup->addAction(addSolidLineAct);
    linesGroup->addAction(addDottedLineAct);
    linesGroup->addAction(addSolidLineAHAct);

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
    shapeMenu->addAction(addClassBoxAct);
    shapeMenu->addAction(addEllipseAct);

    lineMenu = new QMenu(this);
    lineMenu->addAction(addNoLineAct);
    lineMenu->addAction(addSolidLineAct);
    lineMenu->addAction(addDottedLineAct);
    lineMenu->addAction(addSolidLineAHAct);

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
    //Retrieve a pointer to the source icon
    //DragItem *sourceObj = mou
    //Retrieve a pointer to the target icon
    //Create an instance of solidline using these
    lineButton->showMenu();
    //canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    //canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    //canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Line);
}

void Toolbar::addEllipse(){
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_Ellipse);
}

void Toolbar::addClassBox(){
    canvas.at(tabWidget->currentIndex())->setSceneCreate(true);
    canvas.at(tabWidget->currentIndex())->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_Classbox);
}

void Toolbar::addNone(){
    canvas.at(tabWidget->currentIndex())->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->setSceneShapeCreationType(s_None);
}

void Toolbar::addSolidLine()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Line);
}

void Toolbar::addDottedLine()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Dotted_Line);
}

void Toolbar::addSolidLineAH()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(true);
    canvas.at(tabWidget->currentIndex())->scene->setSceneCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Line_SAH);
}

void Toolbar::addNoLine()
{
    canvas.at(tabWidget->currentIndex())->scene->setLineCreate(false);
    canvas.at(tabWidget->currentIndex())->scene->setLineCreateType(Solid_Line);
}

void Toolbar::gridOn(){
    canvas.at(tabWidget->currentIndex())->setSceneGrid(true);
}

void Toolbar::gridOff(){
    canvas.at(tabWidget->currentIndex())->setSceneGrid(false);
}

void Toolbar::canvasSync()
{
    DiagramType d_type = canvas.at(tabWidget->currentIndex())->getDiagramType();
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
        default:
        {
            printf("no ShapeCreationType defined...\n");
            exit(1);
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
        case Dotted_Line:
        {
            this->addDottedLine();
            addDottedLineAct->setChecked(true);
            break;
        }
        case Solid_Line_SAH:
        {
            this->addSolidLineAH();
            addSolidLineAHAct->setChecked(true);
            break;
        }
        default:
        {
            printf("no LineType defined...\n");
            exit(1);
        }
        }
    }
    else
    {
        this->addNoLine();
        addNoLineAct->setChecked(true);
    }
}

