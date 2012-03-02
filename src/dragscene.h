/*
 * Reimplementation of QGraphicsScene
 * Manages DragItems
 *
 */

#ifndef DRAGSCENE_H
#define DRAGSCENE_H

#include <QtGui>
#include <QGraphicsScene>
#include <QList>
#include "dragitem.h"
#include "connection.h"

class DragScene : public QGraphicsScene
{
public:
    /*
      DragScene constructor, default size of the scene is 500x500, can be set to whatever we want, most likely
      we will want to scale it with window size.
      */
    DragScene(QObject* parent = 0, int initHeight = 500, int initWidth = 500);

    // Accessors
    ShapeType getCreateMode();
    bool getSceneCreate();
    bool getGrid();
    int getGridSize();
    bool getSceneConnect();
    QList<DragItem*> getObjectList();

    // Mutators
    void setCreateMode(ShapeType newType);
    void setSceneCreate(bool a);
    void setSceneConnect(bool a);
    void setGrid(bool a);
    void setGridSize(int newSize);
    void addSceneConnection(DragItem* a, DragItem* b);

    // Testing Fucntions
    void testAction();



    /*
    // file io
    void writeXML(QString *filename);
    void readXML(){};
    */

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);


private:
    int gridSize; // pixel width of grid lines
    bool grid; // toggle for grid
    ShapeType createMode; // type of shape the scene is creating
    bool connectMode;
    bool sceneCreate; // toggle for click creation
    QPen* pen;
    QList<DragItem*> scene_items; // custom list of all the DragItem*'s (not QGraphicsItem*) in DragScene
    QList<Connection*> connection_list; // list of all connection between items
};

#endif // DRAGSCENE_H
