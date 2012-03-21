#include "classbox.h"
#include "textdialog.h"

using namespace std;

ClassBox::ClassBox()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    m_labelbox->setParentItem(this);
    m_labelbox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_memberBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_methodBox = new QGraphicsTextItem();
    m_methodBox->setParentItem(this);
    m_methodBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //default text
    m_labelbox->setPlainText("Name");
    m_memberBox->setPlainText("Members");
    m_methodBox->setPlainText("Methods");

    //set m_memberList's position below m_labelBox, and m_methodList below m_memberList
    m_labelbox->setPos(this->pos());
    arrangeBoxes();
    //show text boxes
    m_labelbox->setVisible(true);
    m_memberBox->setVisible(true);
    m_methodBox->setVisible(true);

}

//move boxes to their appropriate positions and set overall size members
void ClassBox::arrangeBoxes()
{
    m_memberBox->setPos(m_labelbox->pos().x(), m_labelbox->pos().y() + m_labelbox->boundingRect().height());
    m_methodBox->setPos(m_labelbox->pos().x(), m_memberBox->pos().y() + m_memberBox->boundingRect().height());
    this->prepareGeometryChange();

   // printf("boundingRect height: %i\n", (int)this->boundingRect().height());

    //change m_height and m_width
    //match the width of the overall boundary rectangles to the widest one
    if( (m_memberBox->boundingRect().width() > m_methodBox->boundingRect().width())
            && (m_memberBox->boundingRect().width() > m_labelbox->boundingRect().width()))
    {
        m_width = m_memberBox->boundingRect().width();
    }
    else if( (m_methodBox->boundingRect().width() > m_memberBox->boundingRect().width())
             && (m_methodBox->boundingRect().width() > m_labelbox->boundingRect().width()))
    {
        m_width = m_methodBox->boundingRect().width();
    }
    else
    {
        m_width = m_labelbox->boundingRect().width();
    }

    m_height = m_labelbox->boundingRect().height()
             + m_memberBox->boundingRect().height()
             + m_methodBox->boundingRect().height();
}

//text is already handled, so paint only makes the boundary boxes
void ClassBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //pen object for drawing different widths of line
    QPen pen(Qt::black, 2, Qt::SolidLine);
    //boundary rectangles for the text boxes
    QRectF labelBoundary, memberBoundary, methodBoundary;

    //adjust postion of boxes before drawing
    arrangeBoxes();

    labelBoundary = m_labelbox->boundingRect();
    memberBoundary = m_memberBox->boundingRect();
    methodBoundary = m_methodBox->boundingRect();
    labelBoundary.setWidth(m_width);
    memberBoundary.setWidth(m_width);
    methodBoundary.setWidth(m_width);

    // make a painter if none exists
    if(painter == 0)
    {
        painter = new QPainter();
    }

    //draw bounding rectangles
    painter->setPen(pen);
    painter->drawRect(m_labelbox->pos().x(), m_labelbox->pos().y(), m_width, labelBoundary.height());
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRect(m_memberBox->pos().x(), m_memberBox->pos().y(), m_width, memberBoundary.height());
    painter->drawRect(m_methodBox->pos().x(), m_methodBox->pos().y(), m_width, methodBoundary.height());

/*
    QRectF mine = this->boundingRect();
    pen.setColor(Qt::red);
    painter->setPen(pen);
//    painter->drawRect(this->pos().x(), this->pos().y(), mine.width(), mine.height());
    painter->drawRect(mine);
*/
}

//call setValues when classbox is doubleclicked
void ClassBox::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setValues();
}

QRectF ClassBox::boundingRect() const
{
 /*
    return QRectF(0,0, m_methodBox->boundingRect().width(),
                  m_labelbox->boundingRect().height() + m_memberBox->boundingRect().height()
                  + m_methodBox->boundingRect().height());

*/
    return QRectF(0, 0, m_width, m_height);
//    return QRectF(0,0,50,25);
}

//Called when the ClassBox is double-clicked
void ClassBox::setValues()
{
    //open dialog box for user editing
    TextDialog *values = new TextDialog(this);
    values->show();

    arrangeBoxes();
}

//The following 3 methods are accessors
QString ClassBox::getLabel()
{
    return m_labelbox->toPlainText();
}

QString ClassBox::getMembers()
{
    return m_memberBox->toPlainText();
}

QString ClassBox::getMethods()
{
    return m_methodBox->toPlainText();
}

//The following 3 methods are mutators
void ClassBox::setLabel(QString value)
{
    m_labelbox->setPlainText(value);
}

void ClassBox::setMembers(QString value)
{
    m_memberBox->setPlainText(value);
}

void ClassBox::setMethods(QString value)
{
    m_methodBox->setPlainText(value);
}
