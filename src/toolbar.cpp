/*toolbar.cpp - includes the functions for the prototypes
                presented in toolbar.h
                Made by Coleman Beasley - 12/16/2011
*/
#include "toolbar.h"
#include "optionsdialog.h"

Toolbar::Toolbar(QWidget *parent) :
    //QDialog(parent)
    QWidget(parent)
{
    this->setWindowModality(Qt::NonModal);
    this->
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

    gridState = 0;  //grid is initialized to off

    QGridLayout *layout;
    layout = initButtons();
    setLayout(layout);
}

//create buttons and add to layout
QGridLayout * Toolbar::initButtons()
{
    //create buttons
    QPushButton * shapeButton = new QPushButton(tr("Shape"));
    QPushButton * textButton = new QPushButton(tr("Text"));
    QPushButton * lineButton = new QPushButton(tr("Line"));
    QPushButton * optionsButton = new QPushButton(tr("Options"));
    QPushButton * gridButton = new QPushButton(tr("Grid On/Off"));

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
void Toolbar::insertShape()
{

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
