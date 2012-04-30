#include "dottedlinesd.h"

dottedlineSD::dottedlineSD(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Dotted_Line_SD;
}

dottedlineSD::dottedlineSD(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
}

dottedlineSD::dottedlineSD(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Dotted_Line_SD;
}

void dottedlineSD::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if (m_SourceReferenceObj->collidesWithItem(m_DestinationReferenceObj))
        return;
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setBrush(m_Color);
    painter->setPen(QPen(m_Color, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    QPointF obj1 = findObjectCenter(m_SourceReferenceObj);
    QPointF obj2 = findObjectCenter(m_DestinationReferenceObj);

    QLineF myLine(obj1, obj2);

    QPointF interPoint = findIntersection(m_SourceReferenceObj, myLine);

    if(!checkInterPoint(interPoint))
        return;

    this->setLine(QLineF(interPoint, obj2));

    double angle = this->getAngle();

    makeDiamond(angle, line());

    painter->drawLine(line());

    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter->drawPolygon(m_ArrowHead);

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
