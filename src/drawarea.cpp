#include <QBoxLayout>
#include "drawarea.h"
#include "dragscene.h"
#include "dragview.h"
#include "dragitem.h"

DrawArea::DrawArea(QWidget *parent, int newHeight, int newWidth){
    scene = new DragScene(0, newHeight, newWidth);
    view = new DragView();
    layout = new QHBoxLayout();
    view->setAcceptDrops(true);
    view->setScene(scene);
    layout->addWidget(view);
    this->setLayout(layout);
}

void DrawArea::setSceneCreateMode(ShapeType newType){
    scene->setCreateMode(newType);
}

ShapeType DrawArea::getSceneCreateMode(){
    return scene->getCreateMode();
}

void DrawArea::setSceneCreate(bool a){
    scene->setSceneCreate(a);
}

bool DrawArea::getSceneCreate(){
    return scene->getSceneCreate();
}

bool DrawArea::getSceneGrid(){
    return scene->getGrid();
}

int DrawArea::getSceneGridSize(){
    return scene->getGridSize();
}

void DrawArea::setSceneGrid(bool a){
    scene->setGrid(a);
}

void DrawArea::setSceneGridSize(int newSize){
    scene->setGridSize(newSize);
}
