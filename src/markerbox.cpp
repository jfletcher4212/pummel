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

/****************************************************************
  * mousePressEvent sets the object the boxes reference if it is
  * not set.  Sets the startX and startY values and grabs mouse
  * events
  ***************************************************************/
void MarkerBox::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->accept();
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
    event = 0;

}

/****************************************************************
  * mouseReleaseEvent calculates the offset for the object and
  * the width and height.  Resets the startX and startY and
  * ungrabs the mouse
  ***************************************************************/
void MarkerBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    int moveDistanceX;
    int moveDistanceY;
    int newWidth;
    int newHeight;

    switch(id){
    case 0:{
        moveDistanceX = startX - (int)event->scenePos().x();
        moveDistanceY = startY - (int)event->scenePos().y();
        canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->setPos(event->scenePos().x()+8, event->scenePos().y()+8);
        break;
    }
    case 1:{
        moveDistanceX = (int)event->scenePos().x() - startX;
        moveDistanceY = startY - (int)event->scenePos().y();
        canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->setPos(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->x(), event->scenePos().y()+8);
        break;
    }
    case 2:{
        moveDistanceX = startX - (int)event->scenePos().x();
        moveDistanceY = (int)event->scenePos().y() - startY;
        canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->setPos(canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->x() - moveDistanceX, canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->y());
        break;
    }
    case 3:{
        moveDistanceX = (int)event->scenePos().x() - startX;
        moveDistanceY = (int)event->scenePos().y() - startY;
        break;
    }
    default:{
        printf("markerbox doesn't have and id\n");
        exit(1);
        break;
    }
    }
    newWidth = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->getWidth() + moveDistanceX;
    newHeight = canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->getHeight() + moveDistanceY;
    canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->setSize(newWidth, newHeight);
    canvas.at(tabWidget->currentIndex())->scene->getObjectList().at(itemIndex)->paintMarkerBoxes();
    startX = -1;
    startY = -1;
    this->ungrabMouse();
}
