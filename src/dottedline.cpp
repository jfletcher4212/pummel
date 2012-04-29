#include "dottedline.h"

dottedline::dottedline(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0) : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Dotted_Line;
}

dottedline::dottedline(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Dotted_Line;
}

void dottedline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;
    if (m_SourceReferenceObj->collidesWithItem(m_DestinationReferenceObj))
        return;
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setPen(QPen(m_Color, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    QPointF obj1 = findObjectCenter(m_SourceReferenceObj);
    QPointF obj2 = findObjectCenter(m_DestinationReferenceObj);

    QLineF myLine(obj1, obj2);

    this->setLine(myLine);

    painter->drawLine(line());

    if (isSelected())
    {
        QLineF myLine = line();
        painter->setPen(QPen(m_Color, 1, Qt::DashLine));
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
    update();
}
