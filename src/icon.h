/* icon.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef icon_H
#define icon_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPointF>

//int next_ID = 1;

enum ShapeType {Square, Pill, Ellipse, Rectangle, Circle};

class icon : public QGraphicsItem
{
protected:

    int m_iD;
    QPointF m_pos;
    int m_xsize;
    int m_ysize;
    QString m_shapetype;
    QString m_label;
    QGraphicsTextItem *m_labelbox;
    QPolygon *m_type;
    int m_state;

    static int m_next_id;

public:

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    icon(QGraphicsItem *parent = 0);
    int getWidth();
    int getHeight();
    void setSize(int newXSize, int newYSize);  // simple accessor and mutator methods for the size
    QString reportShapetype();
    void setShape(ShapeType shapename);     // simple accessor and mutator methods for the shapetype
    int getID();                              // simple accessor for getting the ID
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QPolygon *getType();
    void setText(QString input);
    int getState();
    void setState(int x);

};

#endif // shapes_H
