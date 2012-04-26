#include "dottedsqline.h"

dottedsqline::dottedsqline(Icon *sourceReferenceObject, Icon *destinationReferenceObject, QGraphicsItem *parent=0, QGraphicsScene *scene=0) : lineBody(sourceReferenceObject, destinationReferenceObject, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Dotted_Square_Line;
}

void dottedsqline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if (m_SourceReferenceObj->collidesWithItem(m_DestinationReferenceObj))
        return;
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setPen(QPen(m_Color, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    QPointF point1 = findObjectCenter(m_SourceReferenceObj);
    QPointF point4 = findObjectCenter(m_DestinationReferenceObj);

    QPointF point2 = point1;
    QPointF point3;

    QLineF tempAngleLine(point1, point4);
    this->setLine(tempAngleLine);

    qreal sqAngle = line().angle();

    squareLine(sqAngle, point1, point4, &point2, &point3);

    QLineF lineOne(point1, point2);
    QLineF lineTwo(point2, point3);
    QLineF lineThree(point3, point4);

    painter->drawLine(lineOne);
    painter->drawLine(lineTwo);
    painter->drawLine(lineThree);


    update();
}
