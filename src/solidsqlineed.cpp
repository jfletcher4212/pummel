#include "solidsqlineed.h"

/*
 *Constructors perform some minor assignments unique
 *to each line type, using the linebody constructor
 *to finish its creation.
 */
solidsqlineed::solidsqlineed(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    :lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Sq_Line_ED;
}

solidsqlineed::solidsqlineed(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
    m_LineType = Solid_Sq_Line_ED;

    m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

solidsqlineed::solidsqlineed(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Sq_Line_ED;
}

/*
 *The paint function is called when the line is to be drawn
 *and uses various functions from linebody to create each
 *line respectively.
 */
void solidsqlineed::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->setBrush(Qt::white);
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

    //Finds where the line intersects with the source object
    //Note: This program will return a NULL point if the source
    //object is undefined with regards to intersection.
    QPointF interPoint = findIntersection(m_SourceReferenceObj, lineOne);

    //Exits the paint function if the point is NULL
    if(!checkInterPoint(interPoint))
        return;

    this->setLine(QLineF(interPoint, point2));

    double angle = this->getAngle();

    //Feeds diamond points in to m_ArrowHead based
    //on the angle of the line.
    makeDiamond(angle, line());

    //Each line of the square line is drawn in succession.
    painter->drawLine(line());
    painter->drawLine(lineTwo);
    painter->drawLine(lineThree);

    //The diamond is drawn.
    painter->drawPolygon(m_ArrowHead);

    update();
}
