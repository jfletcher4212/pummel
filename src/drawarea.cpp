#include <QBoxLayout>
#include "drawarea.h"
#include "dragscene.h"
#include "dragview.h"
#include "icon.h"
#include "diagramtypeselector.h"
#include <iostream>

DrawArea::DrawArea(QWidget *parent, int newHeight, int newWidth)
{
    parent = 0;
    scene = new DragScene(0, newHeight, newWidth);
    view = new DragView();
    layout = new QHBoxLayout();
    view->setAcceptDrops(true);
    view->setScene(scene);
    layout->addWidget(view);
//    type = Class;
    this->setLayout(layout);

    DiagramTypeSelector *selector = new DiagramTypeSelector();
    selector->exec();
    while (selector->isVisible())
    {}

    type = selector->getType();
}

DrawArea::DrawArea(QWidget *parent, int newHeight, int newWidth, QList<Icon*> icons,  QList<lineBody*> lines, QString d_type)
{
    parent = 0;
    scene = new DragScene(0, newHeight, newWidth);
    view = new DragView();
    layout = new QHBoxLayout();
    view->setAcceptDrops(true);
    view->setScene(scene);
    layout->addWidget(view);
    this->setLayout(layout);
    
    type = choose_type(d_type);
    
    //qDebug() << "rendering the icons from drawarea";
    // draw the icons
    scene->render_icons(icons, lines);
}

// Class, StateChart, Sequence, UseCase 
DiagramType DrawArea::choose_type(QString d_type)
{
    DiagramType ret = (DiagramType)-1;
    
    if ( d_type == "Class") 
    {
	ret = Class;
    }
    if ( d_type == "StateChart") 
    {
	ret = StateChart;
    }
    if ( d_type == "Sequence") 
    {
	ret = Sequence;
    }
    if ( d_type == "UseCase") 
    {
	ret = UseCase;
    }
    
    return ret;
}
