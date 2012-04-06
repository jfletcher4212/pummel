#include "ellipse.h"
#include "markerbox.h"
#include "textdialog.h"



Ellipse::Ellipse(QGraphicsItem *parent) : Icon(parent)
{
    // allows setting of the base rectangle of dragitem
    m_shapetype = "Ellipse";

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_labelBox->setPlainText("Ellipse");

    m_labelBox->setPos(this->pos());
    arrangeBoxes();

    m_labelBox->setVisible(true);

    //loads the image for drawing later
    if(!m_image.load("icons/ellipse.png"))
    {
        printf("ellipse image failed to load\n");
    }

}

Ellipse::Ellipse(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos) : Icon(parent)
{
    // allows setting of the base rectangle of dragitem
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "Ellipse";

    this->setPos(xpos,ypos);

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_labelBox->setPlainText("Ellipse");

    m_labelBox->setPos(this->pos());
    arrangeBoxes();

    m_labelBox->setVisible(true);

    //loads the image for drawing later
    if(!m_image.load("icons/ellipse.png"))
    {
        printf("ellipse image failed to load\n");
    }

}

QRectF Ellipse::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_labelBox->boundingRect().setHeight(m_height-10);
    m_labelBox->boundingRect().setWidth(m_width-10);

    arrangeBoxes();

    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    painter->drawImage(QRectF(0,0,m_width+40,m_height+40), m_image);   //paints from image file

    painter->drawRect(m_labelBox->pos().x()+5, m_labelBox->pos().y()+5, m_width-10, m_height-10);
    //painter->drawEllipse(QRectF(0,0,m_xsize,m_ysize));

    update();

}


void Ellipse::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setValues();
}

void Ellipse::setValues()
{
    //open dialog box for user editing
    TextBoxDialog *values = new TextBoxDialog(this);
    values->show();

    arrangeBoxes();
}

void Ellipse::arrangeBoxes()
{
    this->prepareGeometryChange();

   // printf("boundingRect height: %i\n", (int)this->boundingRect().height());

    //change m_height and m_width
    //match the width of the overall boundary rectangles to the widest one
    if(m_labelBox->boundingRect().width()+10 > m_width)
    {
           m_width = m_labelBox->boundingRect().width()+10;
    }
    if(m_labelBox->boundingRect().height()+10 > m_height)
    {
          m_height = m_labelBox->boundingRect().height() +10;
    }
    paintMarkerBoxes();
    update();
}




/*void ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->grabMouse();  // DragItem will take all mouse actions
    this->setOpacity(0.5); // Dims the object when dragging to indicate dragging
}


void ellipse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_width;
    pos.ry() -= 0.5 * m_height;
    this->setPos(pos.rx(), pos.ry());
}

void ellipse::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
    this->ungrabMouse();  // release mouse back to DragScene
}

*/
