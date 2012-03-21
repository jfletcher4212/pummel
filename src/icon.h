/* icon.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef icon_H
#define icon_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPointF>
#include "markerbox.h"

class Icon : public QGraphicsItem
{
protected:

    QRectF boundingRect() const{return QRectF(0,0,m_width, m_height);}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void paintMarkerBoxes();

    static int m_next_id;
    int m_id;
    QPointF m_pos;
    int m_width;
    int m_height;
    QString m_shapetype;
//    QString m_label;
    QGraphicsTextItem *m_labelbox;
    QPolygon *m_type;
    QImage m_image;          //holds the imported image to be drawn
    int m_state; // used for zValue stacking and item selection
    MarkerBox *m_markers[4]; // resizing boxes


public:

    Icon(QGraphicsItem *parent = 0);

    // Accessors
    int getWidth();
    int getHeight();
    int getState();
    MarkerBox* getMarkerBox(int x);
    QString reportShapetype();
    void setShapetype(QString shapename);     // simple accessor and mutator methods for the shapetype
    int getID();    // simple accessor for getting the ID
    QPolygon *getType();

    // Mutators
    void setMarkers(MarkerBox* a, MarkerBox* b, MarkerBox* c, MarkerBox* d);
    void setState(int x);
    void setSize(int newXSize, int newYSize);  // simple accessor and mutator methods for the size
    void setText(QString input);		//change the value of m_labelbox
};

#endif // shapes_H
