#include "scenariostate.h"
#include "markerbox.h"
#include <iostream>
#include <QString>


ScenarioState::ScenarioState(QGraphicsItem *parent) : Icon(parent)
{
    // allows setting of the base rectangle of dragitem
    m_shapetype = "ScenarioState";

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_label= "ScenarioState";
    m_labelBox->setPlainText(m_label);

    m_labelBox->setPos(this->pos());
    arrangeBoxes();

    m_labelBox->setVisible(true);
    // In general, leave this block below running for loading images

    if (!m_image.load("icons/scenarioState.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later


    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/scenarioState.png"))
      //  std::cout << "didn't load image properly\n";  //loads the image for drawing later
}

ScenarioState::ScenarioState(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString label) : Icon(parent)
{
    // allows setting of the base rectangle of dragitem
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "ScenarioState";

    this->setPos(xpos,ypos);

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    m_label = label;
    m_labelBox->setPlainText(m_label);

    m_labelBox->setPos(this->pos());
    arrangeBoxes();

    m_labelBox->setVisible(true);

    // In general, leave this block below running for loading images

    if (!m_image.load("icons/scenarioState.png"))
        std::cout << "didn't load image properly\n";  //loads the image for drawing later

    // If the relative path fails, uncomment and update the below with full path to images (example below from a mac)
    //if (!m_image.load("/Users/mac/Desktop/Rev78-build-desktop-Desktop_Qt_4_7_4_for_GCC__Qt_SDK__Debug/icons/scenarioState.png"))
    //    std::cout << "didn't load image properly\n";  //loads the image for drawing later

}

QRectF ScenarioState::boundingRect() const
{
    return QRectF(0,0,m_width, m_height);
}

void ScenarioState::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

}

void ScenarioState::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setValues();
}

void ScenarioState::setValues()
{
    //open dialog box for user editing
    TextBoxDialog *values = new TextBoxDialog(this);
    values->show();

    arrangeBoxes();
}

void ScenarioState::arrangeBoxes()
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
    if(m_height>m_width)
    {
        m_width=m_height;
    }
    else
    {
        m_height=m_width;
    }
    paintMarkerBoxes();
    update();
}

