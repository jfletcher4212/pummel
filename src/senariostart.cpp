#include "senariostart.h"
#include "markerbox.h"
#include <iostream>
#include <QString>


SenarioStart::SenarioStart(QGraphicsItem *parent) : Icon(parent)
{
    // allows setting of the base rectangle of dragitem
    m_shapetype = "SenarioStart";

    // In general, leave this block below running for loading images
    m_width= 25;
    m_height= 25;

    if (!m_image.load("icons/senarioStart.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later


    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/senarioStart.png"))
      //  std::cout << "didn't load image properly\n";  //loads the image for drawing later
}

SenarioStart::SenarioStart(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos) : Icon(parent)
{
    // allows setting of the base rectangle of dragitem
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "SenarioStart";

    this->setPos(xpos,ypos);

    // In general, leave this block below running for loading images

    if (!m_image.load("icons/senarioStart.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later

    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/senarioStart.png"))
    //    std::cout << "didn't load image properly\n";  //loads the image for drawing later

}

QRectF SenarioStart::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void SenarioStart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(m_width>m_height)
    {
        m_height=m_width;
    }
    else
    {
        m_width=m_height;
    }
    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::NoPen);

    painter->drawImage(this->boundingRect(),m_image);

    update();

}

