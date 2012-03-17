#include "markerbox.h"
#include "global.h"
#include "math.h"

MarkerBox::MarkerBox(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    width = 5;
    height = 5;
    setOpacity(1.0);
    itemIndex = -1;
    startX = -1;
    startY = -1;
}

QRectF MarkerBox::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void MarkerBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;
    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setBrush(Qt::black);
    painter->drawRect(QRectF(0, 0,width,height));

}

void MarkerBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(itemIndex < 0){
        for(int i = 0; i < canvas.at(tabWidget->currentIndex())->scene->getObjectList().size(); i++){
            if(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(i)->isSelected()){
                itemIndex = i;
            }
        }
    }
    startX = (int)event->scenePos().x();
    startY = (int)event->scenePos().y();
    this->grabMouse();
}

void MarkerBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

}

void MarkerBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    int moveDistanceX = (int)event->scenePos().x() - startX;
    int moveDistanceY = (int)event->scenePos().y() - startY;
    canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->setPos(event->scenePos().x()+8, event->scenePos().y()+8);
    MarkerBox* m0 = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->getMarkerBox(0);
    MarkerBox* m1 = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->getMarkerBox(1);
    MarkerBox* m2 = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->getMarkerBox(3);

    int newWidth = 11 - (int)sqrt(pow((m0->x() + m1->x()), 2) + pow((m0->y() + m1->y()), 2));
    int newHeight = 11 - (int)sqrt(pow((m0->x() + m2->x()), 2) + pow((m0->y() + m2->y()), 2));
    canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->setSize(newWidth, newHeight);
    /*
    int newX = event->scenePos().x() - startX;
    int newY = event->scenePos().y() - startY;
    int currWidth = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->getWidth();
    int currHeight = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->getHeight();
    */
    switch(id){
    case 0:{

    }
    case 1:{

    }
    case 2:{

    }
    case 3:{

    }
    default:{

    }
    }

   // canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->setSize((newX), (newY));
    startX = -1;
    startY = -1;
    this->ungrabMouse();
}
