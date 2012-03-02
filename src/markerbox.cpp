#include "markerbox.h"

MarkerBox::MarkerBox(QGraphicsItem *parent) : QGraphicsItem(parent){
    width = 5;
    height = 5;
    setOpacity(1.0);
}

QRectF MarkerBox::boundingRect() const{
    return QRectF(0,0,width,height);
}

void MarkerBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(painter == 0){
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setBrush(Qt::black);
    painter->drawRect(QRectF(0, 0,width,height));
}

void MarkerBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->accept();
    this->grabMouse();
}

void MarkerBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

}

void MarkerBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    this->ungrabMouse();
}



