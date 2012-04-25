#include "linebody.h"
#include <math.h>

const qreal Pi = 3.14;

lineBody::lineBody(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene)
{
    parent = 0;

    m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_SourceReferenceObj = sourceReferenceObj;
    m_DestinationReferenceObj = destinationReferenceObj;
}

lineBody::lineBody(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int idx_start, int idx_end, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene)
{
    m_Idx_Start = idx_start;
    m_Idx_End = idx_end;

    m_SourceReferenceObj = sourceReferenceObj;
    m_DestinationReferenceObj = destinationReferenceObj;
}

QPointF lineBody::findObjectCenter(Icon *obj)
{
    QPointF centerPoint = obj->pos();

    centerPoint.rx() += 0.5 * obj->getWidth();
    centerPoint.ry() += 0.5 * obj->getHeight();

    return centerPoint;
}

void lineBody::squareLine(qreal angle, QPointF startPoint, QPointF endPoint, QPointF *secondPointer, QPointF *thirdPointer)
{
    QPointF secondPoint = *secondPointer;
    QPointF thirdPoint =  *thirdPointer;

    if((angle > 45 && angle < 135) || (angle > 225 && angle < 315))
    {
        secondPoint.ry() += (endPoint.ry() - startPoint.ry())/2;
        thirdPoint = secondPoint;
        thirdPoint.rx() += endPoint.rx() - startPoint.rx();
    }
    else
    {
        secondPoint.rx() += (endPoint.rx() - startPoint.rx())/2;
        thirdPoint = secondPoint;
        thirdPoint.ry() += endPoint.ry() - startPoint.ry();
    }

    *secondPointer = secondPoint;
    *thirdPointer = thirdPoint;
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
    path.addPolygon(m_ArrowHead);
    return path;
}

QPointF lineBody::findIntersection(Icon *obj, QLineF interLine) //Find the intersection of the line and object, for determining arrow direction
{
    QPointF interPoint;
    QString iconType = obj->reportShapetype();
    if(iconType.compare("Class Box") == 0)
    {
        QPointF point1 = obj->pos();
        QPointF point2 = point1;
        point2.rx() += obj->getWidth();
        QPointF point3 = point1;
        point3.ry() += obj->getHeight();
        QPointF point4 = point1;
        point4.rx() += obj->getWidth();
        point4.ry() += obj->getHeight();
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
    else if(iconType.compare("Ellipse") == 0)
    {
        interPoint = obj->pos();
    }
    else if(iconType.compare("Rounded Square") == 0)
    {

    }
    else if(iconType.compare("Scenario End") == 0)
    {

    }
    else
    {
        interPoint = QPointF(NULL, NULL);
    }
    return interPoint;
}

double lineBody::getAngle ()
{
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

void lineBody::bareArrowHead(double angle, QLineF interLine, QPointF *firstPointer, QPointF *secondPointer)
{
    qreal arrowSize = 20;

    *firstPointer = interLine.p1() + QPointF(sin(angle + Pi / 3)*arrowSize, cos(angle + Pi / 3) *arrowSize);
    *secondPointer = interLine.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
}

void lineBody::makeArrowHead(double angle, QLineF interLine)
{
    qreal arrowSize = 20;

    QPointF arrowP1 = interLine.p1() + QPointF(sin(angle + Pi / 3)*arrowSize, cos(angle + Pi / 3) *arrowSize);
    QPointF arrowP2 = interLine.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    m_ArrowHead.clear();
    m_ArrowHead << interLine.p1() << arrowP1 << arrowP2;
}

void lineBody::makeDiamond(double angle, QLineF interLine)
{
    qreal arrowSize = 20;

    QPointF arrowP1 = interLine.p1() + QPointF(sin(angle + Pi / 3)*arrowSize, cos(angle + Pi / 3) *arrowSize);
    QPointF arrowP2 = interLine.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    QPointF arrowP3 = interLine.p1() + QPointF(2*(sin(angle + Pi/2)*arrowSize), 2*(cos(angle + Pi/2)*arrowSize));


    m_ArrowHead.clear();
    m_ArrowHead << interLine.p1() << arrowP1 << arrowP3 << arrowP2;
}
