#include "dragitem.h"
#include "markerbox.h"

int DragItem::next_id = 1;

DragItem::DragItem(QGraphicsItem *parent) : QGraphicsItem(parent){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    // allows setting of the base rectangle of dragitem
    //base = QRectF(0,0,0,0);
    width = 0;
    height = 0;
    state = 0;
    shape = Square;
    id = next_id;
    next_id++;

    // selection boxes
    markers[0] = new MarkerBox();
    markers[1] = new MarkerBox();
    markers[2] = new MarkerBox();
    markers[3] = new MarkerBox();

    markers[0]->setParentItem(this);
    markers[1]->setParentItem(this);
    markers[2]->setParentItem(this);
    markers[3]->setParentItem(this);

    markers[0]->setVisible(false);
    markers[1]->setVisible(false);
    markers[2]->setVisible(false);
    markers[3]->setVisible(false);

    markers[0]->setId(0);
    markers[1]->setId(1);
    markers[2]->setId(2);
    markers[3]->setId(3);
}

int DragItem::getWidth(){
    return width;
}

int DragItem::getHeight(){
    return height;
}

void DragItem::setSize(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
}

int DragItem::getId(){
    return id;
}

int DragItem::getState(){
    return state;
}

MarkerBox* DragItem::getMarkerBox(int i){
    return markers[i];
}

void DragItem::setMarkers(MarkerBox* a, MarkerBox* b, MarkerBox* c, MarkerBox* d){
    markers[0] = a;
    markers[1] = b;
    markers[2] = c;
    markers[3] = d;
}

void DragItem::setState(int x){
    state = x;
}

void DragItem::setShape(ShapeType newShape){
    shape = newShape;
}

QRectF DragItem::boundingRect() const{
    return QRectF(0,0,width, height);
}

void DragItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    option = 0;
    widget = 0;
    if(painter == 0){
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    if(this->isSelected()){
        // properly sets the marker boxes around selected objects
        painter->setBrush(Qt::red);
        markers[0]->setVisible(true);
        markers[1]->setVisible(true);
        markers[2]->setVisible(true);
        markers[3]->setVisible(true);

        // this next section grabs the scenePos of the object and offsets its markerboxes 3 pixels away from the corners of the obejcts
        // boundingRect
        QPointF pos = this->scenePos(); // sets position to the upper left pixel
        pos.rx() = -8;
        pos.ry() = -8;
        markers[0]->setPos(pos); // upper left markerbox

        pos = this->scenePos();
        pos.rx() = width+3;
        pos.ry() = -8;
        markers[1]->setPos(pos); // upper right

        pos = this->scenePos();
        pos.rx() = -8;
        pos.ry() = height+3;
        markers[2]->setPos(pos); // lower left

        pos = this->scenePos();
        pos.rx() = width+3;
        pos.ry() = height+3;
        markers[3]->setPos(pos); // lower right

    } else{
        // if not selected, make the boxes invisible
        painter->setBrush(Qt::black);

        markers[0]->setVisible(false);
        markers[1]->setVisible(false);
        markers[2]->setVisible(false);
        markers[3]->setVisible(false);
    }

    switch(shape){
        case Rectangle:{
            painter->drawRect(QRectF(0,0,width,height));
            break;
        }
        case Ellipse:{
            painter->drawEllipse(QRectF(0,0,width,height));
            break;
        }
        case Circle:{
            painter->drawEllipse(QRectF(0,0,width,height));
            break;
        }
        case Square:{
            painter->drawRect(QRectF(0,0,width,height));
            break;
        }
        default:{
            printf("Error in DragItem::paint, Why doesn't this DragItem have a shape type?\n");
            exit(1);
        }
    }
}

void DragItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->accept();
    QPointF pos = event->scenePos();
    // this centers the object on the cursor
    pos.rx() -= 0.5 * width;
    pos.ry() -= 0.5 * height;
    this->grabMouse();  // DragItem will take all mouse actions
    this->setOpacity(0.5); // Dims the object when dragging to indicate dragging
    state = 2;
    update();
}

void DragItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * width;
    pos.ry() -= 0.5 * height;
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
    pos.rx() -= 0.5 * width;
    pos.ry() -= 0.5 * height;
    this->setPos(pos);
    this->setOpacity(1.0);
    this->ungrabMouse();  // release mouse back to DragScene
    update();
}
