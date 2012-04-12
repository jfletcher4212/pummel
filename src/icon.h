/* icon.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef __ICON_H__
#define __ICON_H__

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

    int m_width;
    int m_height;
    static int m_next_id;
    int m_id;

    QString m_shapetype, m_label;
//    QString m_label;
    QGraphicsTextItem *m_labelBox;
    QPolygon *m_type;
    QImage m_image;          //holds the imported image to be drawn
    int m_state; // used for zValue stacking and item selection
    MarkerBox *m_markers[4]; // resizing boxes


public:

    Icon(QGraphicsItem *parent = 0);
    ~Icon();

    // Accessors
    int getWidth();
    int getHeight();
    int getState();
    MarkerBox* getMarkerBox(int x);
    QString reportShapetype();
    void setShapetype(QString shapename);     // simple accessor and mutator methods for the shapetype
    int getID();    // simple accessor for getting the ID
    QPolygon *getType();
    QString getLabel();

    // Mutators
    void setMarkers(MarkerBox* a, MarkerBox* b, MarkerBox* c, MarkerBox* d);
    void setState(int x);
    void setSize(int newXSize, int newYSize);  // simple accessor and mutator methods for the size
    void setText(QString input);		//change the value of m_labelbox

    // Utility
    void paintMarkerBoxes();
};

#endif // __ICON_H__
