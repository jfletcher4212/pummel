#include "dragitem.h"

DragItem::DragItem(QGraphicsItem *parent) : QGraphicsItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    // allows setting of the base rectangle of dragitem
    base = QRectF(0,0,0,0);
    shape = Rectangle;
}

void DragItem::setBase(QRectF newBase){
    base = newBase;
}

void DragItem::setShape(ShapeType newShape){
    shape = newShape;
}

QRectF DragItem::boundingRect() const{
    // create the outline of the QGraphicsItem
    return base;
}

void DragItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(painter == 0){
        // make a painter if none exists
        painter = new QPainter();
    }
    //painter->drawRect(boundingRect());
    switch(shape){
    case Rectangle:{
        painter->drawRect(base);
        break;
    }
    case Ellipse:{
        painter->drawEllipse(base);
        break;
    }
    case Circle:{
        painter->drawEllipse(base);
        break;
    }
    case Square:{
        painter->drawRect(base);
        break;
    }
    default:{
        printf("Error in DragItem::paint, Why doesn't this DragItem have a type?\n");
        exit(1);
    }
    }

}
/*
void DragItem::paintSquare(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(painter == 0){
        // make a painter if none exists
        painter = new QPainter();
    }
    // draw circle from the base of the object
    painter->drawRect(base);



}
*/
void DragItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->accept();
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * (int)base.width();
    pos.ry() -= 0.5 * (int)base.height();
    this->setPos(pos);
    this->grabMouse();  // DragItem will take all mouse actions
    this->setOpacity(0.5); // Dims the object when dragging to indicate dragging
}

void DragItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * (int)base.width();
    pos.ry() -= 0.5 * (int)base.height();
    this->setPos(pos);
}

void DragItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    /*
      This resets the object's coordinates to the cursor's coordinates when the
      mouse is released, as opposed to creating a new object and then deleting the old one.
      Also puts opacity back to normal.
      */

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * base.width();
    pos.ry() -= 0.5 * base.height();
    this->setPos(pos);
    this->setOpacity(1.0);
    this->ungrabMouse();  // release mouse back to DragScene
}


