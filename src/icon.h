/* icon.h - contains structs and protoypes applicable to the shapes class.
              Made by Theora Rice - 12/16/2011
  */
#ifndef __ICON_H__
#define __ICON_H__

#include <QWidget>
#include <QGraphicsItem>
#include <QPointF>
#include "markerbox.h"

// delimiter for multiple icon strings in file i/o
// should be either super unique or a hash of some kind
// however it's a low priority
#define XML_DELIM "::+::"

class Icon : public QGraphicsItem
{
protected:

    QRectF boundingRect() const{return QRectF(0,0,m_width, m_height);}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    int m_width;
    int m_height;
    int m_xPos;
    int m_yPos;
    static int m_next_id;
    int m_id;

    QString m_shapetype, m_label;
//    QString m_label;
    QGraphicsTextItem *m_labelBox;
    QPolygonF m_bound;
    QImage m_image;          //holds the imported image to be drawn
    int m_state; // used for zValue stacking and item selection
    MarkerBox *m_markers[4]; // resizing boxes


public:

    Icon(QPointF = QPointF(0,0), QGraphicsItem *parent = 0);
    ~Icon();

    friend class test_xml_io;
    
    // Accessors
    int getWidth();
    int getHeight();
    int get_xPos() { return m_xPos; }
    int get_yPos() { return m_yPos; }
    int getState();
    MarkerBox* getMarkerBox(int x);
    QString reportShapetype();
    void setShapetype(QString shapename);     // simple accessor and mutator methods for the shapetype
    int getID();    // simple accessor for getting the ID
    QPolygonF getType();
    void setPolygon();
    QString getLabel();

    // Mutators
    void setMarkers(MarkerBox* a, MarkerBox* b, MarkerBox* c, MarkerBox* d);
    void setState(int x);
    void setSize(int newXSize, int newYSize);  // simple accessor and mutator methods for the size
    void set_Pos(int x, int y) { m_xPos = x; m_yPos = y; }

    // Utility
    void paintMarkerBoxes();
    
    // file i/o accessors
    virtual QString get_all();
    virtual QStringList split_all(QString value);
};

#endif // __ICON_H__
