#include "selfrefline.h"

/*
 *Constructors perform some minor assignments unique
 *to each line type, using the linebody constructor
 *to finish its creation.
 */
selfRefLine::selfRefLine(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    : lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Self_Ref_Line;
}

selfRefLine::selfRefLine(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
    m_LineType = Self_Ref_Line;

    m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

selfRefLine::selfRefLine(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Self_Ref_Line;
}

/*
 *The paint function is called when the line is to be drawn
 *and uses various functions from linebody to create each
 *line respectively.
 */
void selfRefLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    //Exits the paint function of the two reference objects
    //are somehow not the same.
    if(m_SourceReferenceObj != m_DestinationReferenceObj)
    {
        return;
    }
    //Makes sure neither of the reference objects are NULL
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    //Determines where the center of the right side of the reference
    //object is.
    QPointF circleCenter = findSRLCenter(m_SourceReferenceObj);

    //Calculates the size of the circle to be drawn (the line)
    qreal radiusy = calcSRLRadius(m_SourceReferenceObj);
    qreal radiusx = radiusy;

    //Finds where the arrowhead is to be drawn for a self
    //referencing line.
    QPointF arrowP1 = calcSRArrowPoint(circleCenter, radiusy);

    //Feeds arrowhead points in to m_ArrowHead based
    //on the angle of the line.
    makeArrowHead(0, arrowP1);

    //Draws our circlc (line)
    painter->drawEllipse(circleCenter, radiusx, radiusy);

    painter->setBrush(Qt::black);

    //Draws the arrowhead
    painter->drawPolygon(m_ArrowHead);

    update();
}
