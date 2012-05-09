#include "linebody.h"
#include <math.h>

//Pi constant for mathematics
const qreal Pi = 3.14;

/*
 *Constructors used to set various member variables.
 */
lineBody::lineBody(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene)
{
    parent = 0;

    m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    m_SourceReferenceObj = sourceReferenceObj;
    m_DestinationReferenceObj = destinationReferenceObj;
}

lineBody::lineBody(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsLineItem(parent, scene)
{
    m_Id_Start = id_start;
    m_Id_End = id_end;

    m_SourceReferenceObj = sourceReferenceObj;
    m_DestinationReferenceObj = destinationReferenceObj;
}

lineBody::lineBody(int id_start, int id_end) : QGraphicsLineItem()
{
    set_ids(id_start, id_end);
}

/*
 *Uses an objects width and height to calculate it's respective center.
 */
QPointF lineBody::findObjectCenter(Icon *obj)
{
    QPointF centerPoint = obj->pos();

    centerPoint.rx() += 0.5 * obj->getWidth();
    centerPoint.ry() += 0.5 * obj->getHeight();

    return centerPoint;
}

/*
 *Calculates the center of the right side of an object.
 */
QPointF lineBody::findSRLCenter(Icon *obj)
{
    QPointF centerPoint = findObjectCenter(obj);

    centerPoint.rx() += (obj->getWidth())/2;

    return centerPoint;

}

/*
 *Calculates the size of a self referencing line
 */
qreal lineBody::calcSRLRadius(Icon *obj)
{
    int offset = 5;

    return ((obj->getHeight()) / 2) - offset;
}

/*
 *Determines where the arrowhead for a self
 *referencing line should start being drawn.
 */
QPointF lineBody::calcSRArrowPoint(QPointF centerPoint, qreal radius)
{
    QPointF arrowP = centerPoint;
    arrowP.ry() += radius;

    return arrowP;
}

/*
 *Checks to make sure that a line's reference objects exist.
 */
bool lineBody::checkReferences(Icon *obj1, Icon *obj2)
{
    if(obj1 == NULL || obj2 == NULL)
        return false;
    else
        return true;
}

/*
 *Makes sure that an arrowhead is capable
 *of being drawn on this object.
 */
bool lineBody::checkInterPoint(QPointF interPoint)
{
    if(interPoint.rx() == 0 || interPoint.ry() == 0)
        return false;
    else
        return true;
}

/*
 *Determines the second and third point for a squared line
 *based upon which quadrant the destination reference objec
 *falls in to.
 */
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
     * This line declares the QPainterPath and
     * assigns the shape of a basic line to it.
     */
    QPainterPath path = QGraphicsLineItem::shape();

    return path;
}

/*
 *Checks to make sure that the object is defined to have
 *an arrowhead drawn on it. If it is then it will determine
 *what point the interLine intersects with the object and
 *return that point.
 */
QPointF lineBody::findIntersection(Icon *obj, QLineF interLine)
{
    QPointF interPoint;
    QString iconType = obj->reportShapetype();
    if(iconType.compare("Class Box") == 0 || iconType.compare("Rounded Square") == 0)
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
        interPoint = findObjectCenter(obj);

        double radiusA = (obj->getWidth())/2;
        double radiusB = (obj->getHeight())/2;

        double angleDeg = interLine.angle();
        double angleRad = -angleDeg * (Pi/180);

        double xCo = radiusA * cos(angleRad);
        double yCo = radiusB * sin(angleRad);

        interPoint.rx() -= xCo;
        interPoint.ry() -= yCo;
    }
    else if(iconType.compare("Scenario End") == 0)
    {
        interPoint = findObjectCenter(obj);

        double radius = (obj->getHeight())/2;

        double angleDeg = interLine.angle();
        double angleRad = -angleDeg * (Pi/180);

        double xCo = radius * cos(angleRad);
        double yCo = radius * sin(angleRad);

        interPoint.rx() -= xCo;
        interPoint.ry() -= yCo;
    }
    else
    {
        interPoint = QPointF(NULL, NULL);
    }
    return interPoint;
}

/*
 *Custom function for determining the angle of a line.
 */
double lineBody::getAngle ()
{
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
 *The next four functions calculate where the arrowhead and diamond
 *points are respectively and either sets pointers equal to them
 *or feeds the points in to m_ArrowHead.
 */
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

void lineBody::makeArrowHead(double angle, QPointF arrowP1)
{
    qreal arrowSize = 20;

    QPointF arrowP2 = arrowP1 + QPointF(sin(angle + Pi / 3)*arrowSize, cos(angle + Pi / 3) *arrowSize);
    QPointF arrowP3 = arrowP1 + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    m_ArrowHead.clear();
    m_ArrowHead << arrowP1 << arrowP2 << arrowP3;
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
