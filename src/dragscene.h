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
#include <QLine>
#include "icon.h"
#include "solidline.h"
#include "dottedline.h"
#include "filledah.h"
#include "solidlinesah.h"
#include "solidsqline.h"
#include "dottedsqline.h"
#include "selfrefline.h"

enum ShapeCreationType {s_None, s_Classbox, s_Ellipse, s_Actor, s_Note, s_RoundedSquare, s_ScenarioStart, s_ScenarioEnd};

class DragScene : public QGraphicsScene
{
public:
    /*
      DragScene constructor, default size of the scene is 500x500, can be set to whatever we want, most likely
      we will want to scale it with window size.
      */
    DragScene(QObject* parent = 0, int initHeight = 500, int initWidth = 500);

    // Accessors
    bool getSceneCreate(){return sceneCreate;}
    bool getGrid(){return grid;}
    int getGridSize(){return gridSize;}
    QList<Icon*> getObjectList(){return scene_items;}
    QList<BasicLineObject*> getLineList(){return scene_lines;}
    bool getLineCreate(){return lineCreate;}
    LineType getLineCreateType(){return lineTypeEnum;}
    bool isResizing(){return m_resizing;}
    ShapeCreationType getShapeCreationType(){return m_shapeCreationType;}

    // Mutators
    void setSceneCreate(bool a){sceneCreate = a;}
    void setLineCreateType(LineType newType){lineTypeEnum = newType;}
    void setLineCreate(bool a){lineCreate = a;}
    void setGrid(bool a){grid = a; update();}
    void setGridSize(int newSize){gridSize = newSize; update();}
    void setResizing(bool x){m_resizing = x;}
    void setShapeCreationType(ShapeCreationType newType){m_shapeCreationType = newType;}

    // Utility functions
    void deleteItem(Icon* item);
    int sceneItemAt(QPointF pos);

    // file i
    void render_icons(QList<Icon*> icons);
    
    // Testing Fucntions
    void testAction();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    ShapeCreationType m_shapeCreationType;
    bool m_resizing; // true if an item on the scene is being resized, false otherwise
    int gridSize; // pixel width of grid lines
    bool grid; // toggle for grid
    LineType lineTypeEnum;
    bool sceneCreate; // toggle for click creation
    bool lineCreate; // toggle for line creation
    QList<Icon*> scene_items; // custom list of all the DragItem*'s (not QGraphicsItem*) in DragScene
    QList<BasicLineObject*> scene_lines;  //custom list of all lines in DragScene

    QGraphicsLineItem* tempLine;
    QColor myTempLineColor;

};

#endif // DRAGSCENE_H
