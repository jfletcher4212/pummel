
#include "solidline.h"
// solidline(DragItem *sourceReferenceObj, DragItem *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
solidline::solidline(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
   : BasicLineObject(sourceReferenceObj, destinationReferenceObj)
{
    parent = 0;
    scene = 0;

   //BasicLineObject * objMyBasicLine = new BasicLineObject(sourceReferenceObj, destinationReferenceObj);
}
void solidline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;
    if (mySourceReferenceObj->collidesWithItem(myDestinationReferenceObj))
        return;
    //qreal arrowSize = 20;
    painter->setPen(QPen(myColor, 2));

    QPointF obj1 = mySourceReferenceObj->pos();
    QPointF obj2 = myDestinationReferenceObj->pos();

    obj1.rx() += 0.5 * mySourceReferenceObj->getWidth();
    obj1.ry() += 0.5 * mySourceReferenceObj->getHeight();

    obj2.rx() += 0.5 * myDestinationReferenceObj->getWidth();
    obj2.ry() += 0.5 * myDestinationReferenceObj->getHeight();

    QLineF tempLineOne(obj1, obj2);


    //QLineF tempLineOne(mySourceReferenceObj->pos(), myDestinationReferenceObj->pos());

    this->setLine(tempLineOne);
/*
    QPolygonF endPolygon = myEndItem->polygon();
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
    p2 = endPolygon.at(i) + myEndItem->pos();
    polyLine = QLineF(p1, p2);
    QLineF::IntersectType intersectType =
        polyLine.intersect(centerLine, &intersectPoint);
    if (intersectType == QLineF::BoundedIntersection)
        break;
        p1 = p2;
    }
*/
    //The above block of code was originally used
    //to determine the intersect point of the line
    //and final reference object.
    //QPointF interPoint;
    //interPoint = findIntersection(myDestinationReferenceObj, tempLineOne);
    //setLine(QLineF(interPoint, mySourceReferenceObj->pos()));
/*
    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;
*/
    //The above block of code was originally used
    //to determine the angle to draw the arrowhead at.
    //This isn't needed for drawing the line
/*
    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
*/
    //The Above block of code is used to draw
    //the arrow head. This isn't needed for the line
    //arrowHead.clear();
    //arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(tempLineOne);
    //painter->drawPolygon(arrowHead);
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

