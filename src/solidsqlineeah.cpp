#include "solidsqlineeah.h"

const qreal Pi = 3.14;

solidsqlineeah::solidsqlineeah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    :lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    myLineType = Solid_Square_Line;
}

solidsqlineeah::~solidsqlineeah()
{

}

void solidsqlineeah::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if (mySourceReferenceObj->collidesWithItem(myDestinationReferenceObj))
        return;

    qreal arrowSize = 20;

    painter->setBrush(Qt::white);
    painter->setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QPointF point1 = mySourceReferenceObj->pos();
    QPointF point4 = myDestinationReferenceObj->pos();

    point1.rx() += 0.5 * mySourceReferenceObj->getWidth();
    point1.ry() += 0.5 * mySourceReferenceObj->getHeight();

    point4.rx() += 0.5 * myDestinationReferenceObj->getWidth();
    point4.ry() += 0.5 * myDestinationReferenceObj->getHeight();

   QPointF point2 = point1;
   QPointF point3;

    QLineF tempAngleLine(point1, point4);
    this->setLine(tempAngleLine);

    qreal angle = line().angle();

   if((angle > 45 && angle < 135) || (angle > 225 && angle < 315))
   {
       point2.ry() += (point4.ry() - point1.ry())/2;
       point3 = point2;
       point3.rx() += point4.rx() - point1.rx();
   }

   else
   {
       point2.rx() += (point4.rx() - point1.rx())/2;
       point3 = point2;
       point3.ry() += point4.ry() - point1.ry();
   }


    QLineF tempLineOne(point1, point2);
    QLineF tempLineTwo(point2, point3);
    QLineF tempLineThree(point3, point4);

    QPointF interPoint = findIntersection(myDestinationReferenceObj, tempLineThree);

    this->setLine(QLineF(interPoint, point3));

    double ahAngle = this->getAngle(interPoint, mySourceReferenceObj);

    QPointF arrowP1 = line().p1() + QPointF(sin(ahAngle + Pi / 3)*arrowSize, cos(ahAngle + Pi / 3) *arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(ahAngle + Pi - Pi / 3) * arrowSize, cos(ahAngle + Pi - Pi / 3) * arrowSize);
    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(tempLineOne);
    painter->drawLine(tempLineTwo);
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);

    update();
}
