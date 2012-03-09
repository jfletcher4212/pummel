#include "markerbox.h"

MarkerBox::MarkerBox(QGraphicsItem *parent) : QGraphicsItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    width = 5;
    height = 5;
    setOpacity(1.0);
}

QRectF MarkerBox::boundingRect() const{
    return QRectF(0,0,width,height);
}

void MarkerBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    option = 0;
    widget = 0;
    if(painter == 0){
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setBrush(Qt::black);
    painter->drawRect(QRectF(0, 0,width,height));

}

void MarkerBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->parentItem()->setPos(this->parentItem()->x()+50, this->parentItem()->y());
}
