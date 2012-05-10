#include "solidsqlinebah.h"

/*
 *Constructors perform some minor assignments unique
 *to each line type, using the linebody constructor
 *to finish its creation.
 */
solidsqlinebah::solidsqlinebah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    :lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Sq_Line_BAH;
}

solidsqlinebah::solidsqlinebah(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
    m_LineType = Solid_Sq_Line_BAH;

    m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

solidsqlinebah::solidsqlinebah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Sq_Line_BAH;
}

/*
 *The paint function is called when the line is to be drawn
 *and uses various functions from linebody to create each
 *line respectively.
 */
void solidsqlinebah::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    //Exits the paint function (line is not drawn) if the two reference
    //objects overlap.
    if (m_SourceReferenceObj->collidesWithItem(m_DestinationReferenceObj))
        return;
    //Makes sure neither of the reference objects are NULL
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setBrush(m_Color);
    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    //Finds each reference objects center respectively
    QPointF point1 = findObjectCenter(m_SourceReferenceObj);
    QPointF point4 = findObjectCenter(m_DestinationReferenceObj);

    //These two points are to be used for the start and end
    //points of the third line.
    QPointF point2 = point1;
    QPointF point3;

    //A temporary line is drawn from the center of the
    //initial reference object to the center of the
    //final reference object.
    QLineF tempAngleLine(point1, point4);
    this->setLine(tempAngleLine);

    //The angle of the temporary line is then calculated
    qreal sqAngle = line().angle();

    //And that angle is used to calculate each point's relation
    //to eachother.
    squareLine(sqAngle, point1, point4, &point2, &point3);

    QLineF lineOne(point1, point2);
    QLineF lineTwo(point2, point3);
    QLineF lineThree(point3, point4);

    //Finds where the line intersects with the destination object
    //Note: This program will return a NULL point if the destination
    //object is undefined with regards to intersection.
    QPointF interPoint = findIntersection(m_DestinationReferenceObj, lineThree);

    //Exits the paint function if the point is NULL
    if(!checkInterPoint(interPoint))
        return;

    this->setLine(QLineF(interPoint, point3));

    double angle = this->getAngle();

    QPointF arrowP1;
    QPointF arrowP2;

    //Feeds the arrowhead's corner points in to arrowP1 and arrowP2
    bareArrowHead(angle, line(), &arrowP1, &arrowP2);

    painter->drawLine(lineOne);
    painter->drawLine(lineTwo);
    painter->drawLine(line());

    //Draws the bare arrowhead's edges
    painter->drawLine(QLineF(line().p1(), arrowP1));
    painter->drawLine(QLineF(line().p1(), arrowP2));

    update();
}
