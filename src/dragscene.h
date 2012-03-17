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
#include "solidline.h"

class DragScene : public QGraphicsScene
{
public:
    /*
      DragScene constructor, default size of the scene is 500x500, can be set to whatever we want, most likely
      we will want to scale it with window size.
      */
    DragScene(QObject* parent = 0, int initHeight = 500, int initWidth = 500);

    // Accessors
    ShapeType getCreateMode(){return createMode;}
    bool getSceneCreate(){return sceneCreate;}
    bool getGrid(){return grid;}
    int getGridSize(){return gridSize;}
    QList<DragItem*> getObjectList(){return scene_items;}
    QList<BasicLineObject*> getLineList(){return scene_lines;}
    bool getLineCreate(){return lineCreate;}
    LineType getLineCreateType(){return lineTypeEnum;}

    // Mutators
    void setCreateMode(ShapeType newType){createMode = newType;}
    void setSceneCreate(bool a){sceneCreate = a;}
    void setLineCreateType(LineType newType){lineTypeEnum = newType;}
    void setLineCreate(bool a){lineCreate = a;}
    void setGrid(bool a){grid = a;}
    void setGridSize(int newSize){gridSize = newSize;}

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
    LineType lineTypeEnum;
    bool sceneCreate; // toggle for click creation
    bool lineCreate; // toggle for line creation
    QList<DragItem*> scene_items; // custom list of all the DragItem*'s (not QGraphicsItem*) in DragScene
    QList<BasicLineObject*> scene_lines;  //custom list of all lines in DragScene
};

#endif // DRAGSCENE_H
