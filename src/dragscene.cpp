#include "dragscene.h"
#include "icon.h"
#include "classbox.h"
#include <QList>
#include <QGraphicsSceneDragDropEvent>
#include <QXmlStreamWriter>
#include <QIODevice>

DragScene::DragScene(QObject* parent, int initHeight, int initWidth)
{
    parent = 0;
    this->setSceneRect(QRectF(0,0,initHeight, initWidth));
    sceneCreate = false;
    gridSize = 10;
    grid = true;

    lineTypeEnum = Solid_Line;
    tempLine = 0;
    myTempLineColor = Qt::black;
}

/****************************************************************
 * sceneItemAt is a reimplementation of QGraphicsScene::itemAt()
 * it returns the index number (int) of the top item (highest
 * zValue) at the scene coordinate QPointF.
 * Example usage: sceneItemAt(event->scenePos()); returns index
 * of the Icon in the scene_items list of the item at QPointF
 * Returns -1 if no item is found
 ***************************************************************/
int DragScene::sceneItemAt(QPointF pos)
{
    int topItem = -1; // -1 indicates an error, no item should have a zValue under 0
    int index = -1; // index doesn't exist, if an item is found, this is changed
    if(!this->itemAt(pos))
    {
        // no item found under the cursor
        return -1;
    }
    /*******************************************************
  * The below for loop checks if the x and y of pos fall
  * within the bounds each of the objects in scene_items.
  * If more than one item is matched, the highest zValue
  * item is returned.
  ******************************************************/

    for(int i = 0; i < scene_items.size(); i++)
    {
        if((int)pos.x() >= (int)scene_items.at(i)->x() &&
                (int)pos.x() <= ((int)(scene_items.at(i)->x()+(int)scene_items.at(i)->getWidth())) &&
                (int)pos.y() >= (int)scene_items.at(i)->y() &&
                (int)pos.y() <= ((int)(scene_items.at(i)->y()+(int)scene_items.at(i)->getHeight())))
        {
            // if an item contains the pos.x() and pos.y(), check its zValue to see if it is the highest item
            if(scene_items.at(i)->zValue() > topItem)
            {
                topItem = scene_items.at(i)->zValue(); // new highest zValue item is found
                index = i;
            }
        }
    }
    return index;
}

/****************************************************************
 * mousePressEvent handles the following:
 *     - item selection/deselection
 *     - item creation
 ***************************************************************/
void DragScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int index;

    // this checks if an object is under the cursor, if so, select it
    if(this->itemAt(event->scenePos()) && !lineCreate)
    {
        index = this->sceneItemAt(event->scenePos());
        if(index < 0)
        {
            // do nothing, index < 0 indicates a markerbox was clicked
        }
        else
        {
            Icon *item = scene_items.at(index);
            // if there are items selected, this will deselect them, forcing only one item selected at a time
            for(int i = 0; i < scene_items.size(); i++)
            {
                // set every item to not selected
                scene_items.at(i)->setSelected(false);
            }
            // set the clicked item to selected
            item->setSelected(true);

            // stop creating items once something is selected
            this->sceneCreate = false;

            //Learn if in line creation mode
        }
        QGraphicsScene::mousePressEvent(event);
    }
    else if (lineCreate)
    {
        tempLine = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos())); //Problem line?
        tempLine->setPen(QPen(myTempLineColor, 2));
        this->addItem(tempLine);
    }
    // if there is no object under the cursor, the number of selected items is zero, and sceneCreate is true, create a new item
    else if(this->selectedItems().size() == 0 && sceneCreate)
    {
        Icon *newItem;   // create an Icon pointer
        newItem = new ClassBox(); // only abstract object currently, this will eventually be a switch statement
        // add the new item to the scene
        this->addItem(newItem);
        newItem->setPos(event->scenePos());
        // add new item to the custom list
        scene_items.append(newItem);
        QGraphicsScene::mousePressEvent(event);
    }
    else
    {
        // nothing is clicked and no create mode, deselect everything
        for(int i = 0; i < scene_items.size(); i++)
        {
            scene_items.at(i)->setSelected(false);
        }
        QGraphicsScene::mousePressEvent(event);
    }
}

void DragScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(lineCreate && tempLine != 0)
    {
        QLineF newLine(tempLine->line().p1(), event->scenePos());
        tempLine->setLine(newLine);
    }
    else
    {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

/****************************************************************
 * mouseReleaseEvent handles the following:
 *     - markerbox redrawing
 *     - item zValue settings
 ***************************************************************/
void DragScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Icon* lastItem;
    // item currently being dragged has a state of 2, the last item clicked has a state of 1, everything else has state 0
    for(int i = 0; i < scene_items.size(); i++)
    {
        // find the item that was just dropped (state 2)
        if(scene_items.at(i)->getState() == 2)
        {
            // find item in state 2, set it to state 1
            scene_items.at(i)->setState(1);
            lastItem = scene_items.at(i);
        }
        else
        {
            // set everything else to state 0, leaving one item in state 1, zero in state 2
            scene_items.at(i)->setState(0);
        }
    }
    // check if an item was clicked
    if(this->itemAt(event->scenePos()) && !lineCreate)
    {
        int index;
        // get the index of the top item under the mouse (where we just dropped a new item)
        index = this->sceneItemAt(event->scenePos());
        if(index < 0)
        {
            // clicked a markerbox, ignore everything else
        }
        else
        {
            // set the zValue of the newly dropped item to 1 more than the top item where it was dropped
            // do not alter the zValue of already present items (preserves any stacking)
            lastItem->setZValue(scene_items.at(index)->zValue()+1);
        }
    }
    else if(lineCreate && tempLine != 0)
    {
        /*
        QList<QGraphicsItem *> startRefObjs = items(tempLine->line().p1());
        if(startRefObjs.count() && startRefObjs.first() == tempLine)
            startRefObjs.removeFirst();
        QList<QGraphicsItem *> endRefObjs = items(tempLine->line().p2());
        if(endRefObjs.count() && endRefObjs.first() == tempLine)
            endRefObjs.removeFirst();
            */
        int indexStart, indexEnd;
        indexStart = sceneItemAt(tempLine->line().p1());
        indexEnd = sceneItemAt(tempLine->line().p2());

        removeItem(tempLine);
        delete tempLine;
        if(indexStart == indexEnd || indexStart < 0 || indexEnd < 0)
        {
            // do nothing
        }
        else
        {
            Icon *initRefObj = scene_items.at(indexStart);
            Icon *finRefObj = scene_items.at(indexEnd);
            solidline *solidLine = new solidline(initRefObj, finRefObj, 0, 0);
            //solidLine->setColor();
            //initRefObj->addArrow(arrow);
            //finRefObj->addArrow(arrow);
            solidLine->setZValue(-1);
            this->addItem(solidLine);
           // solidline->updatePosition();
        }

        setLineCreate(false);
        tempLine = 0;
    }
    // update/redraw the marker boxes of all item in the dragscene
    for(int i = 0; i < scene_items.size(); i++)
    {
        scene_items.at(i)->paintMarkerBoxes();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void DragScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
}

/****************************************************************
 * draws the grid, opacity set to 20%
 ***************************************************************/
void DragScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    // if the grid is on, draw the background
    if(grid)
    {
        int gridInterval = gridSize; //interval to draw grid lines at
        painter->setWorldMatrixEnabled(true);
        qreal left = int(rect.left()) - (int(rect.left()) % gridInterval );
        qreal top = int(rect.top()) - (int(rect.top()) % gridInterval );
        QVarLengthArray<QLineF, 100> linesX;
        for (qreal x = left; x < rect.right(); x += gridInterval )
        {
            linesX.append(QLineF(x, rect.top(), x, rect.bottom()));
        }
        QVarLengthArray<QLineF, 100> linesY;
        for (qreal y = top; y < rect.bottom(); y += gridInterval )
        {
            linesY.append(QLineF(rect.left(), y, rect.right(), y));
        }
        painter->setOpacity(0.2);
        painter->drawLines(linesX.data(), linesX.size());
        painter->drawLines(linesY.data(), linesY.size());
    }
}


void DragScene::testAction()
{
    // use as needed

}


