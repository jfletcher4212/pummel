#include "classbox.h"
#include "textdialog.h"

ClassBox::ClassBox()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

//    m_labelbox = new QGraphicsTextItem();
    m_labelbox->setParentItem(this);
    m_labelbox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_memberBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_methodBox = new QGraphicsTextItem();
    m_methodBox->setParentItem(this);
    m_methodBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    /******
     *default text
     ******/
    m_labelbox->setPlainText("Class Name");
    m_memberBox->setPlainText("int newMember \n int otherMember");
    m_methodBox->setPlainText("void method1 \n void method2");

    //set bounding boxes of classboxes to be opaque

    //set m_memberList's position below m_labelBox, and m_methodList below m_memberList
    m_labelbox->setPos(this->pos());
    arrangeBoxes();
    //set overall bounding rect
    this->boundingRect().setWidth(m_memberBox->boundingRect().width());
    this->boundingRect().setHeight(m_labelbox->boundingRect().height() + m_memberBox->boundingRect().height()
                                   + m_methodBox->boundingRect().height());

    //show text boxes
    m_labelbox->setVisible(true);
    m_memberBox->setVisible(true);
    m_methodBox->setVisible(true);

}

//move boxes to their appropriate positions
void ClassBox::arrangeBoxes()
{
    m_memberBox->setPos(m_labelbox->pos().x(), m_labelbox->pos().y() + m_labelbox->boundingRect().height());
    m_methodBox->setPos(m_labelbox->pos().x(), m_memberBox->pos().y() + m_memberBox->boundingRect().height());
}

//text is already handled, so paint only makes the boundary boxes
void ClassBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, 3, Qt::SolidLine);  //pen object for drawing different widths of line
    //boundary rectangles for the text boxes
    QRectF labelBoundary, memberBoundary, methodBoundary;
    labelBoundary = m_labelbox->boundingRect();
    memberBoundary = m_memberBox->boundingRect();
    methodBoundary = m_methodBox->boundingRect();

    //make the widths of the two boundary rectangles match
    if(memberBoundary.width() > methodBoundary.width())
    {
        labelBoundary.setWidth(memberBoundary.width());
        methodBoundary.setWidth(memberBoundary.width());
    }
    else
    {
        labelBoundary.setWidth(methodBoundary.width());
        memberBoundary.setWidth(methodBoundary.width());
    }

    //adjust size of boxes before drawing
    arrangeBoxes();

    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }

    //draw bounding rectangles
    painter->setPen(pen);
    painter->drawRect(m_labelbox->pos().x(), m_labelbox->pos().y(), labelBoundary.width(), labelBoundary.height());
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(m_memberBox->pos().x(), m_memberBox->pos().y(), memberBoundary.width(), memberBoundary.height());
    painter->drawRect(m_methodBox->pos().x(), m_methodBox->pos().y(), methodBoundary.width(), methodBoundary.height());


}

//call setValues when classbox is doubleclicked
void ClassBox::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setValues();
}

QRectF ClassBox::boundingRect() const
{
    return QRectF(0,0,50,25);
}

//Called when the ClassBox is double-clicked
void ClassBox::setValues()
{
    //open dialog box for user editing
    TextDialog *values = new TextDialog(this);
    values->show();

    arrangeBoxes();
    //loop to wait until window is closed
//    while(values->isVisible())
    {

    }
/*
    //update QGraphicsTextItems with dialog values
    m_labelbox->setPlainText(values->getName());
    m_memberBox->setPlainText(values->getMembers());
    m_methodBox->setPlainText(values->getMethods());
*/
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
