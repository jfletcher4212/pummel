#include "dragitem.h"
#include "markerbox.h"

int DragItem::next_id = 1;

DragItem::DragItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    width = 0;
    height = 0;
    state = 0;
    shape = Square;
    id = next_id;
    next_id++;

    // selection boxes configuration
    for(int i = 0; i < 4; i++){
        markers[i] = new MarkerBox();
        markers[i]->setParentItem(this);
        markers[i]->setVisible(false);
        markers[i]->setId(i);
    }
}

void DragItem::setMarkers(MarkerBox* a, MarkerBox* b, MarkerBox* c, MarkerBox* d)
{
    markers[0] = a;
    markers[1] = b;
    markers[2] = c;
    markers[3] = d;
}

void DragItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;
    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::black);

    if(this->isSelected())
    {
        // properly sets the marker boxes around selected objects
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

    }
    else
    {
        // if not selected, make the boxes invisible

        markers[0]->setVisible(false);
        markers[1]->setVisible(false);
        markers[2]->setVisible(false);
        markers[3]->setVisible(false);
    }

    switch(shape)
    {
        case Rectangle:
        {
            painter->drawRect(QRectF(0,0,width,height));
            break;
        }
        case Ellipse:
        {
            painter->drawEllipse(QRectF(0,0,width,height));
            break;
        }
        case Circle:
        {
            painter->drawEllipse(QRectF(0,0,width,height));
            break;
        }
        case Square:
        {
            painter->drawRect(QRectF(0,0,width,height));
            break;
        }
        default:
        {
            printf("Error in DragItem::paint, Why doesn't this DragItem have a shape type?\n");
            exit(1);
        }
    }
}
/****************************************************************
  * mousePressEvent sets the clicked state to 2, centers the
  * cursor on the object and grabs the mouse
  ***************************************************************/
void DragItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
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

/****************************************************************
  * mouseMoveEvent keeps the cursor centered and moves it with
  * the cursor
  ***************************************************************/
void DragItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * width;
    pos.ry() -= 0.5 * height;
    this->setPos(pos);
}

/****************************************************************
  * mouseReleaseEvent resets the object's coordinates to the cursor's
  * coordinates when the mouse is released, as opposed to creating a
  * new object and then deleting the old one.
  * Also puts opacity back to normal.
  ***************************************************************/
void DragItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * width;
    pos.ry() -= 0.5 * height;
    this->setPos(pos);
    this->setOpacity(1.0);
    this->ungrabMouse();  // release mouse back to DragScene
    update();
}
