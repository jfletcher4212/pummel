#include "roundedsquare.h"
#include "collaborationboxdialog.h"

using namespace std;

RoundedSquare::RoundedSquare(QGraphicsItem *parent) :Icon(parent)
{

    m_shapetype = "RoundedSquare";

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_memberBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //default text
    m_labelBox->setPlainText("State Name");
    m_memberBox->setPlainText("Details");

    arrangeBoxes();
    //show text boxes
    m_labelBox->setVisible(true);
    m_memberBox->setVisible(true);

    if (!m_image.load("icons/roundedSquare.png"))
            std::cout << "didn't load image properly\n";  //loads the image for drawing later


}

RoundedSquare::RoundedSquare(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString members) : Icon(parent)
{
    QStringList tmp = split_all(members);
    
    m_width = xsize;
    m_height = ysize;
    m_shapetype = "RoundedSquare";

    this->setPos(xpos,ypos);

    m_labelBox->setParentItem(this);
    m_labelBox->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_memberBox = new QGraphicsTextItem();
    m_memberBox->setParentItem(this);
    m_memberBox->setFlag(QGraphicsItem::ItemIsSelectable, false);

    //default text
    m_label = tmp[0];
    m_members = tmp[1];
    m_labelBox->setPlainText(m_label);
    m_memberBox->setPlainText(m_members);

    arrangeBoxes();
    //show text boxes
    m_labelBox->setVisible(true);
    m_memberBox->setVisible(true);

    if (!m_image.load("icons/roundedSquare.png"))
            std::cout << "didn't load image properly\n";  //loads the image for drawing later


}

RoundedSquare::~RoundedSquare()
{
    delete m_memberBox;

}

//move boxes to their appropriate positions and set overall size members
void RoundedSquare::arrangeBoxes()
{
    m_labelBox->setPos(((m_width*0.5)-(m_labelBox->boundingRect().width()*0.5)), ((m_height*0.5)-(m_labelBox->boundingRect().height()*0.5)-(m_memberBox->boundingRect().height()*0.5)));
    m_memberBox->setPos(((m_width*0.5)-(m_memberBox->boundingRect().width()*0.5)), m_labelBox->pos().y() + m_labelBox->boundingRect().height());
    this->prepareGeometryChange();

    //change m_height and m_width
    //match the width of the overall boundary rectangles to the widest one
    if(m_width < m_memberBox->boundingRect().width()+20 || m_width < m_labelBox->boundingRect().width()+20)
    {
        if(m_memberBox->boundingRect().width() > m_labelBox->boundingRect().width())
        {
            m_width = m_memberBox->boundingRect().width()+10;
        }
        else
        {
            m_width = m_labelBox->boundingRect().width()+10;
        }
    }
    if(m_labelBox->boundingRect().height()+ m_memberBox->boundingRect().height()+10> m_height)
    {
        m_height = m_labelBox->boundingRect().height()+ m_memberBox->boundingRect().height();
    }
    paintMarkerBoxes();
    update();
}

//text is already handled, so paint only makes the boundary boxes
void RoundedSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int lheight = m_labelBox->boundingRect().height();
    int mheight = m_memberBox->boundingRect().height();
    m_labelBox->boundingRect().setHeight(lheight+(m_height-(lheight+mheight))/2);
    m_memberBox->boundingRect().setHeight(mheight+(m_height-(lheight+mheight))/2);

   this->prepareGeometryChange();

    //pen object for drawing different widths of line
    QPen pen(Qt::black, 2, Qt::SolidLine);
    //boundary rectangles for the text boxes

    //adjust postion of boxes before drawing
    arrangeBoxes();

    // make a painter if none exists
    if(painter == 0)
    {
        painter = new QPainter();
    }

    //draw bounding rectangles
    painter->setPen(pen);
    painter->drawImage(this->boundingRect(),m_image);
    painter->drawLine(3,(m_labelBox->pos().y()+m_labelBox->boundingRect().height()),
                      m_width-3, (m_labelBox->pos().y()+m_labelBox->boundingRect().height()));
    update();
}

//call setValues when RoundedSquare is doubleclicked
void RoundedSquare::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setValues();
}

QRectF RoundedSquare::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

//Called when the RoundedSquare is double-clicked
void RoundedSquare::setValues()
{
    //open dialog box for user editing
    CollaborationBoxDialog *values = new CollaborationBoxDialog(this);
    values->show();

    arrangeBoxes();
}

//The following 2 methods are accessors
QString RoundedSquare::getLabel()
{
    return m_labelBox->toPlainText();
}

QString RoundedSquare::getMembers()
{
    return m_memberBox->toPlainText();
}

//The following 2 methods are mutators
void RoundedSquare::setLabel(QString value)
{
    m_labelBox->setPlainText(value);
}

void RoundedSquare::setMembers(QString value)
{
    m_memberBox->setPlainText(value);
}

QString RoundedSquare::get_all()
{
    QString delim = XML_DELIM;
    
    //                label      +     delimiter    +        members
    return m_labelBox->toPlainText().append(delim).append(m_memberBox->toPlainText());
}

QStringList RoundedSquare::split_all(QString value)
{
    QString delim = XML_DELIM;
    
    return value.split(delim);
}
