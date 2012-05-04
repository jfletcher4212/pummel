#include "solidsqline.h"

solidsqline::solidsqline(Icon *sourceReferenceObj, Icon *destinationReferenceObj, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
    :lineBody(sourceReferenceObj, destinationReferenceObj, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Square_Line;
}

solidsqline::solidsqline(int id_start, int id_end) : lineBody(id_start, id_end)
{
    set_ids(id_start, id_end);
    m_LineType = Solid_Square_Line;
    
    m_Color = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

solidsqline::solidsqline(Icon *sourceReferenceObj, Icon *destinationReferenceObj, int id_start, int id_end, QGraphicsItem *parent, QGraphicsScene *scene) : lineBody(sourceReferenceObj, destinationReferenceObj, id_start, id_end, parent, scene)
{
    parent = 0;
    scene = 0;
    m_LineType = Solid_Square_Line;
}

void solidsqline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = 0;
    widget = 0;

    if (m_SourceReferenceObj->collidesWithItem(m_DestinationReferenceObj))
        return;
    else if (!checkReferences(m_SourceReferenceObj, m_DestinationReferenceObj))
        return;

    painter->setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QPointF point1 = findObjectCenter(m_SourceReferenceObj);
    QPointF point4 = findObjectCenter(m_DestinationReferenceObj);

    QPointF point2 = point1;
    QPointF point3;

    QLineF tempAngleLine(point1, point4);
    this->setLine(tempAngleLine);

    qreal sqAngle = line().angle();

    squareLine(sqAngle, point1, point4, &point2, &point3);

    QLineF lineOne(point1, point2);
    QLineF lineTwo(point2, point3);
    QLineF lineThree(point3, point4);

    painter->drawLine(lineOne);
    painter->drawLine(lineTwo);
    painter->drawLine(lineThree);

    update();
}
