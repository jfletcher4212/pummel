#include "note.h"
#include "markerbox.h"
#include <iostream>
#include <QString>


Note::Note(QPointF location, QGraphicsItem *parent) : Icon(location, parent)
{
    // allows setting of the base rectangle of dragitem
    m_shapetype = "Note";


    m_height /= 1.5;

    m_labelheight = m_labelwidth = 20;
    m_label = "Text";
    arrangeBoxes();

    // In general, leave this block below running for loading images

    if (!m_image.load("icons/note.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later


    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/note.png"))
    //std::cout << "didn't load image properly\n";  //loads the image for drawing later
}

Note::Note(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString label) : Icon(QPointF(xpos, ypos), parent)
{
    // allows setting of the base rectangle of dragitem
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "Note";

    m_xPos = xpos;
    m_yPos = ypos;
    this->setPos(m_xPos,m_yPos);

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_label = label;
    m_labelBox->setPlainText(label);
    m_labelheight = m_labelwidth = 20;

    m_labelBox->setPos(this->pos());
    arrangeBoxes();

    m_labelBox->setVisible(true);

    // In general, leave this block below running for loading images

    if (!m_image.load("icons/note.png"))
           std::cout << "didn't load image properly\n";  //loads the image for drawing later

    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/note.png"))
    //    std::cout << "didn't load image properly\n";  //loads the image for drawing later

}

QRectF Note::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option =0;
    widget =0;

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_labelBox->setPlainText(m_label);

    m_labelBox->setPos(this->pos());

    m_labelBox->boundingRect().setHeight(m_height-20);
    m_labelBox->boundingRect().setWidth(m_width-20);

    m_labelheight = m_labelBox->boundingRect().height();
    m_labelwidth = m_labelBox->boundingRect().width();

    m_labelBox->setPos(((m_width*0.5)-(m_labelBox->boundingRect().width()*0.5)), ((m_height*0.5)-(m_labelBox->boundingRect().height()*0.5)));

    arrangeBoxes();

    m_labelBox->setVisible(true);

    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    painter->drawImage(this->boundingRect(),m_image);
    update();

}

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

    m_labelheight = m_labelBox->boundingRect().height();
    m_labelwidth = m_labelBox->boundingRect().width();

    arrangeBoxes();
}

void Note::arrangeBoxes()
{

    this->prepareGeometryChange();

    //change m_height and m_width
    if(m_labelwidth+20 > m_width)
    {
           m_width = m_labelwidth+20;
    }
    if(m_labelheight+20 > m_height)
    {
          m_height = m_labelheight +20;
    }
    paintMarkerBoxes();
    update();
}

