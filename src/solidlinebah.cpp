#include "solidlinebah.h"

solidlineBAH::solidlineBAH(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Line_BAH;
}

void solidlineBAH::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if (m_SourceReferenceObj->collidesWithItem(m_DestinationReferenceObj))
        return;

    painter->setBrush(m_Color);
    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));


    QPointF obj1 = findObjectCenter(m_SourceReferenceObj);
    QPointF obj2 = findObjectCenter(m_DestinationReferenceObj);

    QLineF myLine(obj1, obj2);

    QPointF interPoint = findIntersection(m_DestinationReferenceObj, myLine);

    this->setLine(QLineF(interPoint, obj1));

    double angle = this->getAngle();

    QPointF arrowP1;
    QPointF arrowP2;

    bareArrowHead(angle, line(), &arrowP1, &arrowP2);

    painter->drawLine(line());

    painter->drawLine(QLineF(line().p1(), arrowP1));
    painter->drawLine(QLineF(line().p1(), arrowP2));

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
