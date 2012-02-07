#include "dragscene.h"
#include "dragitem.h"

#include <QGraphicsSceneDragDropEvent>

DragScene::DragScene(QObject* parent, int initHeight, int initWidth){
    this->setSceneRect(QRectF(0,0,initHeight, initWidth));
    createMode = Rectangle;
}

void DragScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mousePressEvent(event);
}

void DragScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseMoveEvent(event);
}

void DragScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseReleaseEvent(event);
}

void DragScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    DragItem *newItem = new DragItem();
    newItem->setShape(createMode);

    switch(createMode){
    case Square:{
        newItem->setBase(QRectF(0, 0, 25, 25));
        break;
    }
    case Rectangle:{
        newItem->setBase(QRectF(0, 0, 60, 25));
        break;
    }
    case Circle:{
        newItem->setBase(QRectF(0, 0, 25, 25));
        break;
    }
    case Ellipse:{
        newItem->setBase(QRectF(0, 0, 60, 25));
        break;
    }
    default:{
        printf("Error in DragScene::mouseDoubleClickEvent, Why doesn't the scene have a static createMode set?\n");
        exit(1);
    }
    }
    this->addItem(newItem);
    newItem->setPos(event->scenePos());
    /*
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * (int)newItem->base.width();
    pos.ry() -= 0.5 * (int)newItem->base.height();
    newItem->setPos(pos);
    */

}

void DragScene::setCreateMode(ShapeType newType){
    createMode = newType;
}

ShapeType DragScene::getCreateMode(){
    return createMode;
}

