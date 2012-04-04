#include "linebody.h"

lineBody::lineBody(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : BasicLineObject()
{
    parent = 0;
    scene = 0;

    mySourceReferenceObj = sourceReferenceObj;
    myDestinationReferenceObj = destinationReferenceObj;
}

QPointF lineBody::findIntersection(Icon *refObj, QLineF interLine) //Find the intersection of the line and object, for determining arrow direction
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
