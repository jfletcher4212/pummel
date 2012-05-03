#include "scenarioend.h"
#include "markerbox.h"
#include <iostream>
#include <QString>


ScenarioEnd::ScenarioEnd(QPointF location, QGraphicsItem *parent) : Icon(location, parent)
{
    // allows setting of the base rectangle of dragitem
    m_shapetype = "ScenarioEnd";

    // In general, leave this block below running for loading images
    m_width= 25;
    m_height= 25;

    if (!m_image.load("icons/scenarioEnd.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later


    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/ScenarioEnd.png"))
      //  std::cout << "didn't load image properly\n";  //loads the image for drawing later
}

ScenarioEnd::ScenarioEnd(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos) : Icon(QPointF(xpos, ypos), parent)
{
    // allows setting of the base rectangle of dragitem
    m_id = id;
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "ScenarioEnd";

    this->setPos(xpos,ypos);

    // In general, leave this block below running for loading images

    if (!m_image.load("icons/ScenarioEnd.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later

    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/ScenarioEnd.png"))
    //    std::cout << "didn't load image properly\n";  //loads the image for drawing later

}

QRectF ScenarioEnd::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void ScenarioEnd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

