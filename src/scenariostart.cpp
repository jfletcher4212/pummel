#include "scenariostart.h"
#include "markerbox.h"
#include <iostream>
#include <QString>


ScenarioStart::ScenarioStart(QPointF location, QGraphicsItem *parent) : Icon(location, parent)
{
    // allows setting of the base rectangle of dragitem
    m_shapetype = "ScenarioStart";

    // In general, leave this block below running for loading images
    m_width= 25;
    m_height= 25;

    if (!m_image.load("icons/scenarioStart.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later


    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/ScenarioStart.png"))
      //  std::cout << "didn't load image properly\n";  //loads the image for drawing later
}

ScenarioStart::ScenarioStart(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos) : Icon(QPointF(xpos, ypos), parent)
{
    // allows setting of the base rectangle of dragitem
    m_id = id;
    m_width = 25;
    m_height = 25;
    m_shapetype = "ScenarioStart";


    this->setPos(xpos,ypos);

    // In general, leave this block below running for loading images

    if (!m_image.load("icons/ScenarioStart.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later

    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/ScenarioStart.png"))
    //    std::cout << "didn't load image properly\n";  //loads the image for drawing later

}

QRectF ScenarioStart::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void ScenarioStart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    option = 0;
    widget = 0;

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

