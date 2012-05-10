#include "solidlineeah.h"

/*
 *Constructors perform some minor assignments unique
 *to each line type, using the linebody constructor
 *to finish its creation.
 */
solidlineeah::solidlineeah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Line_EAH;
}

solidlineeah::solidlineeah(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
    m_LineType = Solid_Line_EAH;

    m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

solidlineeah::solidlineeah(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Line_EAH;
}

/*
 *The paint function is called when the line is to be drawn
 *and uses various functions from linebody to create each
 *line respectively.
 */
void solidlineeah::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    //and draws a line from the source to the destination obj
    QPointF obj1 = findObjectCenter(m_SourceReferenceObj);
    QPointF obj2 = findObjectCenter(m_DestinationReferenceObj);
    QLineF myLine(obj1, obj2);

    //Finds where the line intersects with the destination object
    //Note: This program will return a NULL point if the destination
    //object is undefined with regards to intersection.
    QPointF interPoint = findIntersection(m_DestinationReferenceObj, myLine);

    //Exits the paint function if the point is NULL
    if(!checkInterPoint(interPoint))
        return;

    this->setLine(QLineF(interPoint, obj1));

    double angle = this->getAngle();

    //Feeds arrowhead points in to m_ArrowHead based
    //on the angle of the line.
    makeArrowHead(angle, line());

    painter->drawLine(line());

    //The arrowhead is drawn.
    painter->drawPolygon(m_ArrowHead);

    //Draws two dash lines, one on either side, of
    //the line when it is selected.
    if (isSelected())
    {
        QLineF myLine = line();
        painter->setPen(QPen(m_Color, 1, Qt::DashLine));
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }

    update();
}
