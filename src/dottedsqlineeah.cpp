#include "dottedsqlineeah.h"

dottedsqlineeah::dottedsqlineeah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    :lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Sq_Line_EAH;
}

dottedsqlineeah::dottedsqlineeah(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
}

dottedsqlineeah::dottedsqlineeah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Dotted_Sq_Line_EAH;
}

void dottedsqlineeah::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if (m_SourceReferenceObj->collidesWithItem(m_DestinationReferenceObj))
        return;
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setBrush(Qt::white);
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

    QPointF interPoint = findIntersection(m_DestinationReferenceObj, lineThree);

    if(!checkInterPoint(interPoint))
        return;

    this->setLine(QLineF(interPoint, point3));

    double angle = this->getAngle();

    makeArrowHead(angle, line());

    painter->drawLine(lineOne);
    painter->drawLine(lineTwo);
    painter->drawLine(line());

    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter->drawPolygon(m_ArrowHead);

    update();
}
