#include "note.h"
#include "markerbox.h"



note::note(QGraphicsItem *parent) : Icon(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    // allows setting of the base rectangle of dragitem
    //base = QRectF(0,0,0,0);
    m_shapetype = "Note";
    m_id = m_next_id;
    m_next_id++;

    m_image.load("images/note.png");  //loads the image for drawing later

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
}



note::note(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos) : Icon(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    // allows setting of the base rectangle of dragitem
    //base = QRectF(0,0,0,0);
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "Note";
    m_id = m_next_id;
    m_next_id++;

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
}

QRectF note::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void note::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    if(this->isSelected())
    {
        QPointF pos;
        // properly sets the marker boxes around selected objects
        painter->setBrush(Qt::red);
        markers[0]->setVisible(true);
        markers[1]->setVisible(true);
        markers[2]->setVisible(true);
        markers[3]->setVisible(true);

        pos = this->scenePos(); // sets position to the upper left pixel
        pos.rx() = -8;
        pos.ry() = -8;
        markers[0]->setPos(pos);

        pos = this->scenePos();
        pos.rx() = m_width+3;
        pos.ry() = -8;
        markers[1]->setPos(pos);

        pos = this->scenePos();
        pos.rx() = -8;
        pos.ry() = m_height+3;
        markers[2]->setPos(pos);

        pos = this->scenePos();
        pos.rx() = m_width+3;
        pos.ry() = m_height+3;
        markers[3]->setPos(pos);

    }
    else
    {
        // if not selected, make the boxes invisible
        painter->setBrush(Qt::black);
        markers[0]->setVisible(false);
        markers[1]->setVisible(false);
        markers[2]->setVisible(false);
        markers[3]->setVisible(false);
    }

    painter->drawImage(QRectF(0,0,m_width,m_height), m_image);   //paints from image file

}


void note::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->grabMouse();  // DragItem will take all mouse actions
    this->setOpacity(0.5); // Dims the object when dragging to indicate dragging
}

void note::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->setPos(pos.rx(), pos.ry());
}

void note::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /*
     * This resets the object's coordinates to the cursor's coordinates when the
     * mouse is released, as opposed to creating a new object and then deleting the old one.
     * Also puts opacity back to normal.
     */

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->setPos(pos.rx(),pos.ry());
    this->setOpacity(1.0);
    this->ungrabMouse();  // release mouse back to DragScene
}



