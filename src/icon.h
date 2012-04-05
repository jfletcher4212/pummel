/* icon.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef icon_H
#define icon_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPointF>

//int next_ID = 1;

class icon : public QGraphicsItem
{
protected:

    int m_iD;                       //ID for the item
    QPointF m_pos;                  //Position identifier for canvas
    int m_xsize;                    //width
    int m_ysize;                    //height
    QString m_shapetype;            //name of shape (A.K.A. "ellipse", "classbox", etc.)
//    QString m_label;                //the text in the box
    QGraphicsTextItem *m_labelbox;  //textbox
    QPolygon m_bound;               //bounding rectangle of the item.
    QImage m_image;          //holds the imported image to be drawn

    static int m_next_id;

public:

    icon(QGraphicsItem *parent = 0);
    int getXSize();
    int getYSize();
    void setSize(int newXSize, int newYSize);  // simple accessor and mutator methods for the size
    QString reportShapetype();
    void setShapetype(QString shapename);     // simple accessor and mutator methods for the shapetype
    int getID();                              // simple accessor for getting the ID
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QPolygon getData();
    void setPolyType();
    void setText(QString input);		//change the value of m_labelbox
};

#endif // shapes_H
