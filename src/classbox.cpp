
#include "classbox.h"
#include "classboxdialog.h"

using namespace std;

ClassBox::ClassBox(QPointF location)
{
    m_xPos = location.x();
    m_yPos = location.y();
    this->setPos(m_xPos, m_yPos);

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_memberBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_methodBox = new QGraphicsTextItem();
    m_methodBox->setParentItem(this);
    m_methodBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //default text
    m_label = "Name";
    m_members = "Members";
    m_methods = "Methods";

    m_lfont.setBold(true);

    m_height = m_labelBox->boundingRect().height()
             + m_memberBox->boundingRect().height()
             + m_methodBox->boundingRect().height();

    //set m_memberList's position below m_labelBox, and m_methodList below m_memberList
    m_labelBox->setPos(0,0);
    arrangeBoxes();
    //show text boxes
    m_labelBox->setVisible(true);
    m_memberBox->setVisible(true);
    m_methodBox->setVisible(true);

}

ClassBox::ClassBox(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos, QString members)
{
    QStringList tmp = split_all(members);
 
    this->setPos(xpos,ypos);
    m_id = id;
    m_xPos = xpos;
    m_yPos = ypos;
    
    // shapetype MUST be set
    m_shapetype = "Class Box";
    
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

    m_height = m_labelBox->boundingRect().height()
             + m_memberBox->boundingRect().height()
             + m_methodBox->boundingRect().height();
    
    //default text
    m_lfont.setBold(true);
    m_label = tmp[0];
    m_members = tmp[1];
    m_methods = tmp[2];

    //set m_memberList's position below m_labelBox, and m_methodList below m_memberList
    m_labelBox->setPos(0,0);
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
    m_memberBox->setPos(m_labelBox->pos().x(), m_labelBox->pos().y() + m_labelBox->boundingRect().height());
    m_methodBox->setPos(m_labelBox->pos().x(), m_memberBox->pos().y() + m_memberBox->boundingRect().height());
    this->prepareGeometryChange();

   // printf("boundingRect height: %i\n", (int)this->boundingRect().height());

    //change m_height and m_width
    //match the width of the overall boundary rectangle to the widest one
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

//set the labelBox text, and paint the boundary boxes
void ClassBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option =0;
    widget =0;

    m_labelBox->setFont(m_lfont);
    m_labelBox->setPlainText(m_label);
    m_memberBox->setPlainText(m_members);
    m_methodBox->setPlainText(m_methods);

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
    painter->drawRect(m_labelBox->pos().x(), (int)m_labelBox->pos().y(), m_width, m_labelBox->boundingRect().height());
    painter->drawRect(m_memberBox->pos().x(), (int)m_memberBox->pos().y(), m_width, m_memberBox->boundingRect().height());
    painter->drawRect(m_methodBox->pos().x(), (int)m_methodBox->pos().y(), m_width, m_methodBox->boundingRect().height());
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
    return m_label;
}

QString ClassBox::getMembers()
{
    return m_members;
}

QString ClassBox::getMethods()
{
    return m_methods;
}

//The following 3 methods are mutators
void ClassBox::setLabel(QString value)
{
    m_label = value;
}

void ClassBox::setMembers(QString value)
{
    m_members = value;
}

void ClassBox::setMethods(QString value)
{
    m_methods = value;
}

QString ClassBox::get_all()
{
    QString delim = XML_DELIM;
    
    //                label      +     delimiter    +     members              +         delimiter   +          methods
    return m_label.append(delim).append(m_members).append(delim).append(m_methods);
}

QStringList ClassBox::split_all(QString value)
{
    QString delim = XML_DELIM;
    
    return value.split(delim);
}

int ClassBox::setWidthsManually(int labelWidth, int memberWidth, int methodWidth)
{
	m_labelBox->boundingRect().setWidth(labelWidth);
	m_memberBox->boundingRect().setWidth(memberWidth);
	m_methodBox->boundingRect().setWidth(methodWidth);
	arrangeBoxes();

	return m_width;
}
