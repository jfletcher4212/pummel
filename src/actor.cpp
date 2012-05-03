#include "actor.h"
#include "markerbox.h"

Actor::Actor(QPointF location, QGraphicsItem *parent) : Icon(location, parent)
{
    m_shapetype = "Actor";
    m_label = "Actor";

    //m_labelBox->setParentItem(this);
    //m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //m_labelBox->setPlainText(m_label);

    //m_labelBox->setPos(this->pos());
    arrangeBoxes();

    //m_labelBox->setVisible(true);

    m_width = 80;
    m_height = 100;

    m_image.load("icons/actor.png");  //loads the image for drawing later
}



Actor::Actor(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos, QString contents) : Icon(QPointF(xpos, ypos), parent)
{
    m_id = id;
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "Actor";

    this->setPos(xpos,ypos);

    //m_labelBox->setParentItem(this);
    //m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_label = contents;
    //m_labelBox->setPlainText(contents);

    //m_labelBox->setPos(this->pos());
    arrangeBoxes();

    //m_labelBox->setVisible(true);

    m_image.load("icons/actor.png");  //loads the image for drawing later

}

QRectF Actor::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_labelBox->setVisible(true);

    m_labelBox->setPlainText(m_label);

    m_labelwidth = m_labelBox->boundingRect().width();
    m_labelheight = m_labelBox->boundingRect().height();

    m_labelBox->boundingRect().setWidth(m_width-20);

    arrangeBoxes();

    m_labelBox->setPos(m_width/2 - m_labelBox->boundingRect().width()/2, m_height - m_labelBox->boundingRect().height());

    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    painter->drawImage(this->boundingRect(),m_image);

    update();

}

void Actor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setValues();
}

void Actor::setValues()
{
    //open dialog box for editing label
    TextBoxDialog *values = new TextBoxDialog(this);
    values->show();

    arrangeBoxes();
}

void Actor::arrangeBoxes()
{
    //m_labelBox->setPos(m_width/2 - m_labelBox->boundingRect().width()/2, m_height - m_labelBox->boundingRect().height());

    this->prepareGeometryChange();

    if(m_labelwidth > m_width)
    {
           m_width = m_labelwidth +20;
    }
    if(m_labelheight +30 > m_height)
    {
          m_height = m_labelheight +30;
    }

    paintMarkerBoxes();
    update();

}
