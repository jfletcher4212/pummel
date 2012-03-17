#include "classbox.h"

ClassBox::ClassBox()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

//    m_labelbox = new QGraphicsTextItem();
    m_labelbox->setParentItem(this);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_methodBox = new QGraphicsTextItem();
    m_methodBox->setParentItem(this);

    /******
     *default text
     ******/
    m_labelbox->setPlainText("Class Name");
    m_memberBox->setPlainText("int newMember \n int otherMember");
    m_methodBox->setPlainText("void method1 \n void method2");

    //set bounding boxes of classboxes to be opaque

    //set m_memberList's position below m_labelBox, and m_methodList below m_memberList
    m_labelbox->setPos(this->pos());
    m_memberBox->setPos(this->pos().x(), this->pos().y() + m_labelbox->boundingRect().height());
    m_methodBox->setPos(this->pos().x(), m_memberBox->pos().y() + m_memberBox->boundingRect().height());
    //set overall bounding rect
    this->boundingRect().setWidth(m_memberBox->boundingRect().width());
    this->boundingRect().setHeight(m_labelbox->boundingRect().height() + m_memberBox->boundingRect().height()
                                   + m_methodBox->boundingRect().height());

    //show text boxes
    m_labelbox->setVisible(true);
    m_memberBox->setVisible(true);
    m_methodBox->setVisible(true);

}

//text is already handled, so paint only makes the boundary boxes
void ClassBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //boundary rectangles for the text boxes
    QRectF labelBoundary, memberBoundary, methodBoundary;
    labelBoundary = m_labelbox->boundingRect();
    memberBoundary = m_memberBox->boundingRect();
    methodBoundary = m_methodBox->boundingRect();
/*
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
*/
    if(painter == 0)
    {
        // make a painter if none exists
        painter = new QPainter();
    }
    painter->setPen(Qt::black);
    painter->setPen(Qt::SolidLine);

    //draw bounding rectangles
    painter->drawRect(m_labelbox->pos().x(), m_labelbox->pos().y(), labelBoundary.width(), labelBoundary.height());
    painter->drawRect(m_memberBox->pos().x(), m_memberBox->pos().y(), memberBoundary.width(), memberBoundary.height());
    painter->drawRect(m_methodBox->pos().x(), m_methodBox->pos().y(), methodBoundary.width(), methodBoundary.height());


}

QRectF ClassBox::boundingRect() const
{
    return QRectF(0,0,50,25);
}

//Called when the ClassBox is double-clicked
void ClassBox::setValues()
{
    //open dialog box for user editing

    //copy dialog values into m_memberBox and m_methodBox
}

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
