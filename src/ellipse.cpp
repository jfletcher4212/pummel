#include "ellipse.h"
#include "markerbox.h"
#include <iostream>
#include <QString>


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


    if (!m_image.load("icons/ellipse.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later

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


    if (!m_image.load("icons/ellipse.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later

}

QRectF Ellipse::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_labelBox->boundingRect().setHeight(m_height-20);
    m_labelBox->boundingRect().setWidth(m_width-20);
    //m_labelBox->boundingRect().setX(this->pos().x()+10);
    //m_labelBox->boundingRect().setX(this->pos().x()+10);
    //m_labelBox->setPos(this->pos().x(), this->pos().y());


    arrangeBoxes();

    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    //QString myPath;
    //myPath = "icons/ellipse.png";
    //if(!m_image.load(myPath))
    //{std::cout <<"didnt load from in the paint func\n";}
    painter->drawImage(this->boundingRect(),m_image);
    //painter->drawImage(this->pos().x(),this->pos().y(),m_image);
    //painter->drawImage(QRectF(0,0,m_width+40,m_height+40), m_image);   //paints from image file

    //painter->drawImage();
    //painter->drawRect(m_labelBox->pos().x()+5, m_labelBox->pos().y()+5, m_width-10, m_height-10);
    //painter->drawEllipse(QRectF(0,0,m_xsize,m_ysize));

    //painter->drawRect(m_labelBox->pos().x()+10, m_labelBox->pos().y()+10, m_width-10, m_height-10);


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
    m_labelBox->setPos(10, 10);


    this->prepareGeometryChange();

   // printf("boundingRect height: %i\n", (int)this->boundingRect().height());

    //change m_height and m_width
    //match the width of the overall boundary rectangles to the widest one
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

