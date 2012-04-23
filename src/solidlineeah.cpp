#include "solidlineeah.h"

const qreal Pi = 3.14;

solidlineeah::solidlineeah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    myLineType = Solid_Line_EAH;
}

void solidlineeah::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if (mySourceReferenceObj->collidesWithItem(myDestinationReferenceObj))
        return;

    qreal arrowSize = 20;

    painter->setBrush(Qt::white);
    painter->setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QPointF obj1 = mySourceReferenceObj->pos();
    QPointF obj2 = myDestinationReferenceObj->pos();

    obj1.rx() += 0.5 * mySourceReferenceObj->getWidth();
    obj1.ry() += 0.5 * mySourceReferenceObj->getHeight();

    obj2.rx() += 0.5 * myDestinationReferenceObj->getWidth();
    obj2.ry() += 0.5 * myDestinationReferenceObj->getHeight();

    QLineF tempLineOne(obj1, obj2);

    QPointF interPoint = findIntersection(myDestinationReferenceObj, tempLineOne);

    this->setLine(QLineF(interPoint, obj1));

    double angle = this->getAngle(interPoint, mySourceReferenceObj);

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3)*arrowSize, cos(angle + Pi / 3) *arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());

    painter->drawPolygon(arrowHead);

    if (isSelected())
    {
        QLineF myLine = line();
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }

    update();
}
