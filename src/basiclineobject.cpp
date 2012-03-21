#include <math.h>
#include "basiclineobject.h"
const qreal Pi = 3.14;
BasicLineObject::BasicLineObject(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene)
{
    //Instantiate the object's elements
    mySourceReferenceObj = sourceReferenceObj;
    myDestinationReferenceObj = destinationReferenceObj;
    myColor = Qt::black;
    //Allow for the item to be selected
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
//Change at which end of the line the arrow head resides.
void BasicLineObject::swapLineDirection()
{
    //Swap the source and destination reference objects
    //Redraw
}
/*
 * Virtual Function - QGraphicsLineItem
 * The point of the boundingRect() is to define
 * the outer bounds of an item as a rectangle;
 * in which all painting must take place.
 */
QRectF BasicLineObject::boundingRect() const
{
    /*
     * Sets the local variable extra equal to the width of the pen
     * (line width) plus a little bit more.
     */
    qreal extra = (pen().width() + 20) / 2.0;
    /*
     * Sets the new bounding rectangle's top left corner
     * equal to the end reference object. It then sets
     * the length equal to the line and the width will
     * end up equaling 1.
     */
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y()))
    /*
     * This line ensures that the rectangle generated above
     * does not have any negative coordinates.
     */
        .normalized()
    /*
     * This line widens the rectangle so that it encompasses
     * the line
     */
        .adjusted(-extra, -extra, extra, extra);
}
/*
 * Virtual Function - QGraphicsItem
 * The shape of an object is used for many things
 * (such as collision detection, hit tests, etc.)
 * and is returned as a QPainterPath in local coordinates.
*/
QPainterPath BasicLineObject::shape() const
{
    /*
     * This first line declares the QPainterPath and
     * assigns the shape of a basic line to it.
     */
    QPainterPath path = QGraphicsLineItem::shape();
    /*
     * This line adds the shape of the arrow head to
     * the QPainterPath.
     */
    path.addPolygon(arrowHead);
    return path;
}
/*
void BasicLineObject::updatePosition();
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}
*/
QPointF BasicLineObject::findIntersection(Icon *refObj, QLineF interLine) //Find the intersection of the line and object, for determining arrow direction
{
    //QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        //Here a line object is constructed that "represents" a line between the position of myStartItem and myEndItem
        /*How pos() works: Returns the position of the item in "parent coordinates" or
         * scene coordinates if the item has no parent. The position describes it origin (local
         * coordinates (0,0)) in parent coordinates [this funct returns the same as mapToParent(0,0).
         * You can use scenePos() to determine the scene coordinates regardless of the parent.
         */
        //This line isn't neccisary for this portion of the code -> should be placed in a function for
        //drawing the lines.

   //For now, we will implement the QPoly here. This will need to be a property of the icon in the future.
   QRectF * myRect = new QRectF(qreal(refObj->x()), qreal(refObj->y()), qreal(refObj->getWidth()), qreal(refObj->getHeight()));
   //Why does this work, and not (& myRect);?
   QPolygonF * tempRefPoly = new QPolygonF ((*myRect));


   QPointF startPoint = tempRefPoly->first() + refObj->pos();
    QPointF endPoint;
    QPointF interPoint;
    QLineF tempPolyLine;
    for(int i = 1; i < tempRefPoly->count(); ++i)
    {
        endPoint = tempRefPoly->at(i) + refObj->pos();
        tempPolyLine = QLineF(startPoint, endPoint);
        QLineF::IntersectType interBool = tempPolyLine.intersect(interLine, &interPoint);
        if(interBool == QLineF::BoundedIntersection)
            break;
        startPoint = endPoint;
    }
    //setLine(QLineF(intersectPoint, myStartItem->pos()));
    /* Here the line is drawn back from the point of intersection (where it meets the end
     * reference object) to the origin of the initial object. This should be included in the
     * drawing portion of the line. Instead we return the point of intersection.
     */
    return interPoint;
}
double BasicLineObject::getAngle (QPointF intersectPoint, Icon *myStartItem)//(BasicLineObject line)//rotateArrowHead(QPointF, DragItem)
{
    setLine(QLineF(intersectPoint, myStartItem->pos()));
    /*
     * The object's line needs to be set for line() to operate
     * properly, which is done with the line above. However,
     * not sure whether or not this line has to be set
     * locally.
     * Calculates the angle the line makes with the x axis.
     * line()
     * acos() is part of the math.h library
     * dx() and dy() are part of the QLineF class
     */
    double angle = ::acos(line().dx() / line().length());
    /*
     * Checks to see if the lines vertical component is
     * negative.
     * The angle is flipped due to the setLine() oulined above which
     * makes the initial point for the line the final reference
     * object.
     */
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;
    return angle;
    //The following lines are used to draw the arrowhead.
     //    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
     //    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
     //    arrowHead.clear();
     //    arrowHead << line().p1() << arrowP1 << arrowP2;
}
