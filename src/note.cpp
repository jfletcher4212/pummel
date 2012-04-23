#include "note.h"
#include "markerbox.h"
#include "textboxdialog.h"
#include <iostream>



Note::Note(QGraphicsItem *parent) : Icon(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    // allows setting of the base rectangle of dragitem
    //base = QRectF(0,0,0,0);
    m_shapetype = "Note";
    m_id = m_next_id;
    m_next_id++;


    if (!m_image.load("icons/note.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later
//    m_image.load("icons/note.png");  //loads the image for drawing later

    //set icon text and box
    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_label = "Note";
    m_labelBox->setPlainText(m_label);
    m_labelBox->setPos(this->pos());

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



Note::Note(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos) : Icon(parent)
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

    if (!m_image.load("icons/note.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later

    //set icon text and box
    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_label = "Note";
    m_labelBox->setPlainText(m_label);
    m_labelBox->setPos(this->pos());


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

QRectF Note::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_labelBox->boundingRect().setHeight(m_height-20);
    m_labelBox->boundingRect().setWidth(m_width-20);

    arrangeBoxes();

    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    painter->drawImage(this->boundingRect(),m_image);
    update();
/*
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

    painter->drawImage(this->boundingRect(), m_image);   //paints from image file
*/
}

/*
void Note::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->grabMouse();  // DragItem will take all mouse actions
    this->setOpacity(0.5); // Dims the object when dragging to indicate dragging
}

void Note::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->setPos(pos.rx(), pos.ry());
}

void Note::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /*
     * This resets the object's coordinates to the cursor's coordinates when the
     * mouse is released, as opposed to creating a new object and then deleting the old one.
     * Also puts opacity back to normal.
     */
/*
    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->setPos(pos.rx(),pos.ry());
    this->setOpacity(1.0);
//    this->ungrabMouse();  // release mouse back to DragScene
}
*/

void Note::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setValues();
}

void Note::setValues()
{
    //open dialog box for user editing
    TextBoxDialog *values = new TextBoxDialog(this);
    values->show();

    arrangeBoxes();
}

void Note::arrangeBoxes()
{
    m_labelBox->setPos(((m_width*0.5)-(m_labelBox->boundingRect().width()*0.5)), ((m_height*0.5)-(m_labelBox->boundingRect().height()*0.5)));
   // (int)m_labelBox->boundingRect().width();
   // (int)m_labelBox->boundingRect().height();


    this->prepareGeometryChange();

    //change m_height and m_width
    if(m_labelBox->boundingRect().width()+20 > m_width)
    {
           m_width = m_labelBox->boundingRect().width()+20;
    }
    if(m_labelBox->boundingRect().height()+20 > m_height)
    {
          m_height = m_labelBox->boundingRect().height() +20;
    }
    paintMarkerBoxes();
    update();
}
