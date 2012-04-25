#include "linebody.h"
#include <math.h>

const qreal Pi = 3.14;

lineBody::lineBody(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene)
{
    parent = 0;

    myColor = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    mySourceReferenceObj = sourceReferenceObj;
    myDestinationReferenceObj = destinationReferenceObj;
}

lineBody::lineBody(int idx_start, int idx_end)
{
    m_idx_start = idx_start;
    m_idx_end = idx_end;
}

lineBody::~lineBody()
{
    //delete mySourceReferenceObj;
    //delete myDestinationReferenceObj;
}

/*
 * Virtual Function - QGraphicsLineItem
 * The point of the boundingRect() is to define
 * the outer bounds of an item as a rectangle;
 * in which all painting must take place.
 */
QRectF lineBody::boundingRect() const
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
QPainterPath lineBody::shape() const
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

void lineBody::setSourceObject(Icon* newSource)
{
    mySourceReferenceObj = newSource;
}
void lineBody::setDestObject(Icon *newDest)
{
    myDestinationReferenceObj = newDest;
}

//Change at which end of the line the arrow head resides.
void lineBody::swapLineDirection()
{
    //Swap the source and destination reference objects
    //Redraw
}

QPointF lineBody::findIntersection(Icon *refObj, QLineF interLine) //Find the intersection of the line and object, for determining arrow direction
{
    QPointF interPoint;
    QString tempStr = refObj->reportShapetype();
    if(tempStr.compare("Class Box") == 0)
    {
        QPointF point1 = refObj->pos();
        QPointF point2 = point1;
        point2.rx() += refObj->getWidth();
        QPointF point3 = point1;
        point3.ry() += refObj->getHeight();
        QPointF point4 = point1;
        point4.rx() += refObj->getWidth();
        point4.ry() += refObj->getHeight();
        QLineF topLine = QLineF(point1, point2);
        QLineF leftLine = QLineF(point1, point3);
        QLineF rightLine = QLineF(point2, point4);
        QLineF bottomLine = QLineF(point3, point4);
        QPointF tempInter1;
        QPointF tempInter2;
        QPointF tempInter3;
        QPointF tempInter4;
        QLineF::IntersectType intersectType1 = topLine.intersect(interLine, &tempInter1);
        QLineF::IntersectType intersectType2 = leftLine.intersect(interLine, &tempInter2);
        QLineF::IntersectType intersectType3 = rightLine.intersect(interLine, &tempInter3);
        QLineF::IntersectType intersectType4 = bottomLine.intersect(interLine, &tempInter4);
        if(intersectType1 == QLineF::BoundedIntersection)
        {
            interPoint = tempInter1;
        }
        else if(intersectType2 == QLineF::BoundedIntersection)
        {
            interPoint = tempInter2;
        }
        else if(intersectType3 == QLineF::BoundedIntersection)
        {
            interPoint = tempInter3;
        }
        else if(intersectType4 == QLineF::BoundedIntersection)
        {
            interPoint = tempInter4;
        }
    }
    else if(tempStr.compare("Ellipse") == 0)
    {
        interPoint = refObj->pos();
    }
    else if(tempStr.compare("Rounded Square") == 0)
    {

    }
    else if(tempStr.compare("Scenario End") == 0)
    {

    }
    else
    {
        interPoint = QPointF(NULL, NULL);
    }
    return interPoint;
}

double lineBody::getAngle (QPointF intersectPoint, Icon *myStartItem)//(BasicLineObject line)//rotateArrowHead(QPointF, DragItem)
{
    //setLine(QLineF(intersectPoint, myStartItem->pos()));
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

}
/*
void BasicLineObject::updatePosition();
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
}
*/
