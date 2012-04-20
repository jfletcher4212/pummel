#include "classbox.h"
#include "classboxdialog.h"

using namespace std;

ClassBox::ClassBox()
{

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_memberBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_methodBox = new QGraphicsTextItem();
    m_methodBox->setParentItem(this);
    m_methodBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //default text
    m_labelBox->setPlainText("Name");
    m_memberBox->setPlainText("Members");
    m_methodBox->setPlainText("Methods");

    //set m_memberList's position below m_labelBox, and m_methodList below m_memberList
    m_labelBox->setPos(this->pos());
    arrangeBoxes();
    //show text boxes
    m_labelBox->setVisible(true);
    m_memberBox->setVisible(true);
    m_methodBox->setVisible(true);

}

ClassBox::ClassBox(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString label, QString members, QString methods)
{

    this->setPos(xpos,ypos);
    m_width = xsize;
    m_height = ysize;

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_memberBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_methodBox = new QGraphicsTextItem();
    m_methodBox->setParentItem(this);
    m_methodBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //default text
    m_label = label;
    m_members = members;
    m_methods = methods;

    m_labelBox->setPlainText(label);
    m_memberBox->setPlainText(members);
    m_methodBox->setPlainText(methods);

    //set m_memberList's position below m_labelBox, and m_methodList below m_memberList
    m_labelBox->setPos(this->pos());
    arrangeBoxes();
    //show text boxes
    m_labelBox->setVisible(true);
    m_memberBox->setVisible(true);
    m_methodBox->setVisible(true);


}

ClassBox::~ClassBox()
{
    delete m_memberBox;
    delete m_methodBox;

}

//move boxes to their appropriate positions and set overall size members
void ClassBox::arrangeBoxes()
{
    m_memberBox->setPos(m_labelBox->pos().x(), m_labelBox->pos().y() + (m_height/3));
    m_methodBox->setPos(m_labelBox->pos().x(), m_labelBox->pos().y() + (2*(m_height/3)));
    this->prepareGeometryChange();

   // printf("boundingRect height: %i\n", (int)this->boundingRect().height());

    //change m_height and m_width
    //match the width of the overall boundary rectangles to the widest one
    if(m_width < m_memberBox->boundingRect().width() || m_width < m_methodBox->boundingRect().width()
            || m_width < m_labelBox->boundingRect().width())
    {
        if( (m_memberBox->boundingRect().width() > m_methodBox->boundingRect().width())
                && (m_memberBox->boundingRect().width() > m_labelBox->boundingRect().width()))
        {
            m_width = m_memberBox->boundingRect().width();
        }
        else if( (m_methodBox->boundingRect().width() > m_memberBox->boundingRect().width())
                 && (m_methodBox->boundingRect().width() > m_labelBox->boundingRect().width()))
        {
            m_width = m_methodBox->boundingRect().width();
        }
        else
        {
            m_width = m_labelBox->boundingRect().width();
        }
    }
    if((m_labelBox->boundingRect().height()
            + m_memberBox->boundingRect().height()
            + m_methodBox->boundingRect().height()) > m_height)
    {
        m_height = m_labelBox->boundingRect().height()
                 + m_memberBox->boundingRect().height()
                 + m_methodBox->boundingRect().height();
    }
    paintMarkerBoxes();
    update();
}

//text is already handled, so paint only makes the boundary boxes
void ClassBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_labelBox->boundingRect().setHeight(m_height/3);
    m_memberBox->boundingRect().setHeight(m_height/3);
    m_methodBox->boundingRect().setHeight(m_height/3);

    // draws the white background behind classbox
    painter->setBrush(Qt::white);

    this->prepareGeometryChange();

    //pen object for drawing different widths of line
    QPen pen(Qt::black, 2, Qt::SolidLine);
    //boundary rectangles for the text boxes
    QRectF labelBoundary, memberBoundary, methodBoundary;

    //adjust postion of boxes before drawing
    arrangeBoxes();

    labelBoundary = m_labelBox->boundingRect();
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
    painter->drawRect(m_labelBox->pos().x(), m_labelBox->pos().y(), m_width, (m_height/3));
    painter->drawRect(m_memberBox->pos().x(), (int)m_labelBox->pos().y() + (m_height/3), m_width, (m_height/3));
    painter->drawRect(m_methodBox->pos().x(), (int)m_labelBox->pos().y() + (2*(m_height/3)), m_width, (m_height/3));
    /*
    painter->drawRect(m_memberBox->pos().x(), m_memberBox->pos().y(), m_width, memberBoundary.height());
    painter->drawRect(m_methodBox->pos().x(), m_methodBox->pos().y(), m_width, methodBoundary.height());
    painter->drawRect(m_labelBox->pos().x(), m_labelBox->pos().y(), m_width, labelBoundary.height());

/*
    QRectF mine = this->boundingRect();
    pen.setColor(Qt::red);
    painter->setPen(pen);
//    painter->drawRect(this->pos().x(), this->pos().y(), mine.width(), mine.height());
    painter->drawRect(mine);
*/
    update();
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

}

//Called when the ClassBox is double-clicked
void ClassBox::setValues()
{
    //open dialog box for user editing
    ClassBoxDialog *values = new ClassBoxDialog(this);
    values->show();

    arrangeBoxes();
}

//The following 3 methods are accessors
QString ClassBox::getLabel()
{
    return m_labelBox->toPlainText();
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
    m_labelBox->setPlainText(value);
}

void ClassBox::setMembers(QString value)
{
    m_memberBox->setPlainText(value);
}

void ClassBox::setMethods(QString value)
{
    m_methodBox->setPlainText(value);
}
