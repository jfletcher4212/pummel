/* icon.cpp -contains the functions to store default properties in the shape structs
               and contains the creation function for each shape
               Made by Theora Rice
  */
#include "icon.h"
#include <QtGui>

//#include <QPointF>

int icon::m_next_id = 1;

icon::icon(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    m_xsize = 0;
    m_ysize = 0;
//    m_label = "";
    m_labelbox = new QGraphicsTextItem;
    m_labelbox->setPlainText(m_label);
    m_labelbox->setPos(this->pos());
    m_type = new QPolygon();
}

int icon::getXSize()
{
    return m_xsize;
}

int icon::getYSize()
{
    return m_ysize;
}

void icon::setSize(int newXSize, int newYSize)
{
    m_xsize = newXSize;
    m_ysize = newYSize;

}

QString icon::reportShapetype()
{
    return m_shapetype;
}

void icon::setShapetype(QString shapename)
{
    m_shapetype = shapename;
}

int icon::getID()
{
    return m_iD;
}

void icon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->accept();
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_xsize; // this centers the object on the cursor
    pos.ry() -= 0.5 * m_ysize;
    this->grabMouse();  // icon will take all mouse actions
    this->setOpacity(0.5); // Dims the object when dragging to indicate dragging
}

void icon::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_xsize;
    pos.ry() -= 0.5 * m_ysize;
    this->setPos(pos);
}

void icon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    /*
      This resets the object's coordinates to the cursor's coordinates when the
      mouse is released, as opposed to creating a new object and then deleting the old one.
      Also puts opacity back to normal.
      */

    // Centers the cursor while dragging, as opposed to dragging by the top-left most pixel
    QPointF pos = event->scenePos();
    pos.rx() -= 0.5 * m_xsize;
    pos.ry() -= 0.5 * m_ysize;
    this->setPos(pos);
    this->setOpacity(1.0);
    this->ungrabMouse();  // release mouse back to DragScene
}

QPolygon* icon::getType()
{
    return m_type;
}

void icon::setText(QString input)
{
    m_labelbox->setPlainText(input);
}
