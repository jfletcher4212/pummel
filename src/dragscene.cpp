#include "dragscene.h"
#include "icon.h"
#include "classbox.h"
#include "ellipse.h"
#include "actor.h"
#include "note.h"
#include "toolbar.h"
#include "roundedsquare.h"
#include "scenariostart.h"
#include "solidlineed.h"
#include "scenarioend.h"
#include <QList>
#include <QGraphicsSceneDragDropEvent>
#include <QXmlStreamWriter>
#include <QIODevice>
#include <QWidget>

extern Toolbar *toolbar;

DragScene::DragScene(QObject* parent, int initHeight, int initWidth)
{
    parent = 0;
    this->setSceneRect(QRectF(0,0,initHeight, initWidth));
    sceneCreate = false;
    gridSize = 10;
    grid = true;
    lineCreate = false;
    tempLine = 0;
    myTempLineColor = Qt::black;
    m_shapeCreationType = s_None;
    m_resizing = 0;
    sceneCreate = false;
    lineTypeEnum = No_Line;
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

void DragScene::deleteItem(Icon* item)
{
    lineCreate = false;
    sceneCreate = false;

    QList<lineBody*> lineRemovalList; // list of items to remove
    for(int i = 0; i < scene_lines.size(); i++)
    {
        // check if the item is equal to the reference objects of an item
        if(scene_lines.at(i)->getSourceReferenceObj()->getID() == item->getID() || scene_lines.at(i)->getDestinationReferenceObj()->getID() == item->getID())
        {
            scene_lines.at(i)->setParentItem(item); // set parent object to item to be deleted (so that it will be deleted with it)
            lineRemovalList.append(scene_lines.at(i)); // add line to removal list
        }
    }
    for(int i = 0; i < lineRemovalList.size(); i++)
    {
        scene_lines.removeOne(lineRemovalList.at(i)); // remove the lines from the list
        delete lineRemovalList.at(i); // delete it
    }
    scene_items.removeOne(item); // remove the item from list
    this->removeItem(item); // remove from scene
    delete item; // delete it
}

/****************************************************************
 * mousePressEvent handles the following:
 *     - item selection/deselection
 *     - item creation
 *     - line creation
 *     - line selection/deselection
 ***************************************************************/

void DragScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // this checks if an object is under the cursor and lineCreate is false, if so, select it
    if(this->itemAt(event->scenePos()))
    {
        if (!lineCreate)
        {
            if(this->sceneItemAt(event->scenePos()) < 0)
            {
                // do nothing, index < 0 indicates a markerbox was clicked
            }
            else
            {
                Icon *item = scene_items.at(this->sceneItemAt(event->scenePos()));
                /**** using this->clearSelection() takes care of deselecting everything. Built in Qt func
                // if there is another item selected, this will deselect it, forcing only one item selected at a time
                for(int i = 0; i < scene_items.size(); i++)
                {
                    // set every item to not selected
                    scene_items.at(i)->setSelected(false);
                }
                //deselect all lines
                for(int i = 0; i < scene_lines.size(); i++)
                {
                    scene_lines.at(i)->setSelected(true);
                }
                */
                this->clearSelection();
                // set the clicked item to selected
                item->setSelected(true);

                // stop creating items once something is selected
                this->sceneCreate = false;
                this->lineCreate = false;
                this->m_shapeCreationType = s_None;
                this->lineTypeEnum = No_Line;
                toolbar->canvasSync(); // update toolbar to changes

            }
            QGraphicsScene::mousePressEvent(event);
        }
        else if (lineCreate && lineTypeEnum != Self_Ref_Line)
        {
            tempLine = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
            tempLine->setPen(QPen(myTempLineColor, 2));
            this->addItem(tempLine);
            this->clearSelection();
            this->m_shapeCreationType = s_None;     //stop creating shapes when lines are created
        }
        else if(lineCreate && lineTypeEnum == Self_Ref_Line)
        {
            //int indexStart, indexEnd;
            //indexStart = sceneItemAt(tempLine->line().p1());
            //indexEnd = sceneItemAt(tempLine->line().p2());

            //Icon *initRefObj = scene_items.at(indexStart);
            //Icon *finRefObj = scene_items.at(indexEnd);

            //unneccesary with new if-statement condition above
    /*
            if(this->sceneItemAt(event->scenePos()) < 0)
            {
                // exit routine if no source object was clicked
                // DEV debugging indicates this routine may be entered three time.
                //Need to discover why.

                return;
            }
    */
            int self_idx = this->sceneItemAt(event->scenePos());
            Icon *item = scene_items.at(self_idx);
	    int self_id = item->getID();

            selfRefLine *newLine = new selfRefLine(item, item, 0, 0);
            newLine->set_ids(self_id, self_id);
            this->scene_lines.append(newLine);
            this->addItem(newLine);
            newLine->setZValue(-1);
        }
    }
    // if there is no object under the cursor, and sceneCreate is true, create a new item
    else if(sceneCreate)
    {
        Icon *newItem = NULL;   // create an Icon pointer

        // create abstract class based on m_shapeCreationType
        this->clearSelection();
        switch(m_shapeCreationType){
        case s_Classbox:{
            newItem = new ClassBox(event->scenePos());
            newItem->setShapetype("Class Box");
            break;
        }
        case s_Ellipse:{
            newItem = new Ellipse();
            newItem->setShapetype("Ellipse");
            break;
        }
        case s_Actor:{
            newItem = new Actor();
            newItem->setShapetype("Actor");
            break;
        }
        case s_Note:
        {
            newItem = new Note();
            newItem->setShapetype("Note");
            break;
        }
        case s_ScenarioStart:
        {
            newItem = new ScenarioStart();
            newItem->setShapetype("Scenario Start");
            break;
        }
        case s_RoundedSquare:
        {
            newItem = new RoundedSquare();
            newItem->setShapetype("Rounded Square");
            break;
        }
        case s_ScenarioEnd:
        {
            newItem = new ScenarioEnd();
            newItem->setShapetype("Scenario End");
            break;
        }
        default:{
            printf("dragscene doesn't have a shapeCreationType defined\n");
            newItem = NULL;
        }

        }
        // add the new item to the scene
        if (newItem != NULL)
        {
            this->addItem(newItem);
            newItem->setPos(event->scenePos());
            // add new item to the custom list
            scene_items.append(newItem);
        }
        QGraphicsScene::mousePressEvent(event);
    }
    else
    {
        // nothing is clicked and no create mode, deselect everything
        for(int i = 0; i < scene_items.size(); i++)
        {
            scene_items.at(i)->setSelected(false);
        }
        for(int i = 0; i < scene_lines.size(); i++)
        {
            scene_lines.at(i)->setSelected(false);
        }
        //exit selection modes
        this->sceneCreate = false;
        this->lineCreate = false;
        this->m_shapeCreationType = s_None;
        this->lineTypeEnum = No_Line;
        toolbar->canvasSync();

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
    if(m_ignoreReleaseEvent)
    {
        m_ignoreReleaseEvent = false;
        return;
    }
    Icon* lastItem = NULL;
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
    if(this->itemAt(event->scenePos()) && !lineCreate && !m_resizing)
    {
        int index;
        // get the index of the top item under the mouse (where we just dropped a new item)
        index = this->sceneItemAt(event->scenePos());
        if(index < 0)
        {
            // error, should never get here
            exit(5);
        }
        else
        {
            // set the zValue of the newly dropped item to 1 more than the top item where it was dropped
            // do not alter the zValue of already present items (preserves any stacking)
            if(lastItem)
            {
                lastItem->setZValue(scene_items.at(index)->zValue()+1);
            }
        }
    }
    else if(lineCreate && tempLine != 0)
    {
        int indexStart, indexEnd;
        indexStart = sceneItemAt(tempLine->line().p1());
        indexEnd = sceneItemAt(tempLine->line().p2());

	// id saving
	int id_start, id_end = -1;
	id_start = scene_items.at(indexStart)->getID();
	
	if ( indexEnd > 0 )
	{
	    id_end = scene_items.at(indexEnd)->getID();
	}
	

        removeItem(tempLine);
        //delete tempLine;
        if(indexStart == indexEnd || indexStart < 0 || indexEnd < 0)
        {
            // do nothing
        }
        else
        {
            Icon *initRefObj = scene_items.at(indexStart);
            Icon *finRefObj = scene_items.at(indexEnd);
            //newLine->setColor();
            //initRefObj->addArrow(arrow);
            //finRefObj->addArrow(arrow);

            if(lineTypeEnum == Solid_Line)
            {
                solidline *newLine = new solidline(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Line)
            {
                dottedline *newLine = new dottedline(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Line_SAH)
            {
                //make new solid line + ah in here, just like above
                //place code similar to above in paint function
                //solidline *newLine = new solidline(initRefObj, finRefObj, 0, 0);
                //this->addItem(newLine);
                //newLine->setZValue(-1);

                //filledAH *newAH = new filledAH(newLine, 0, 0);
                //this->addItem(newAH);
                //newAH->setZValue(-1);

                solidlineSAH *newLine = new solidlineSAH(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Line_SAH)
            {
                dottedlineSAH *newLine = new dottedlineSAH(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Line_EAH)
            {
                solidlineeah *newLine = new solidlineeah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Line_EAH)
            {
                dottedlineeah *newLine = new dottedlineeah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Line_SD)
            {
                solidlineSD *newLine = new solidlineSD(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Line_SD)
            {
                dottedlineSD *newLine = new dottedlineSD(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Line_ED)
            {
                solidlineed *newLine = new solidlineed(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Line_ED)
            {
                dottedlineed *newLine = new dottedlineed(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Line_BAH)
            {
                solidlineBAH *newLine = new solidlineBAH(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Line_BAH)
            {
                dottedlinebah *newLine = new dottedlinebah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Square_Line)
            {
                //Dev note - memory leak here? Want to test adding this as a parameter,
                //and then explicitly deleting to obj in dragscene's destructor to see effects on valgrind
                //in both situations
                solidsqline *newLine = new solidsqline(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Square_Line)
            {
                dottedsqline *newLine = new dottedsqline(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Sq_Line_SAH)
            {
                solidsqlinesah *newLine = new solidsqlinesah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Sq_Line_SAH)
            {
                dottedsqlinesah *newLine = new dottedsqlinesah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Sq_Line_EAH)
            {
                solidsqlineeah *newLine = new solidsqlineeah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Dotted_Sq_Line_EAH)
            {
                dottedsqlineeah *newLine = new dottedsqlineeah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Sq_Line_BAH)
            {
                solidsqlinebah *newLine = new solidsqlinebah(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Sq_Line_SD)
            {
                solidsqlinesd *newLine = new solidsqlinesd(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            else if(lineTypeEnum == Solid_Sq_Line_ED)
            {
                solidsqlineed *newLine = new solidsqlineed(initRefObj, finRefObj, 0, 0);
                newLine->set_ids(id_start, id_end);
                this->addItem(newLine);
                this->scene_lines.append(newLine);
                newLine->setZValue(-1);
            }
            // newLine->updatePosition();
        }
        delete tempLine;
        tempLine = 0;
    }
    // update/redraw the marker boxes of all item in the dragscene
    for(int i = 0; i < scene_items.size(); i++)
    {
        scene_items.at(i)->paintMarkerBoxes();
    }
    ////toolbar->canvasSync();
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
    update();
}


void DragScene::testAction()
{
    // use as needed

}

void DragScene::render_icons(QList<Icon*> icons, QList<lineBody*> lines)
{
    int i;
    Icon *tmp_start;
    Icon *tmp_end;

    // draw the icons
    for ( i = 0; i < icons.length(); i++ )
    {
        if(icons[i] != NULL)
        {

	    //qDebug() << "before rendering: " << icons[i]->get_xPos();
	    //qDebug() << "before rendering: " << icons[i]->get_yPos();

	    this->addItem(icons[i]);
	    //icons[i]->setPos(event->scenePos());
	    //add new item to the custom list
	    scene_items.append(icons[i]);
        }
    }

    // draw the lines
    for ( i = 0; i < lines.length(); i++ )
    {
	//qDebug() << "in the loop....";
	if ( lines[i] != NULL )
	{
	    //qDebug() << "in the if....";
            // get the right icons
	    tmp_start = find_icon_id(icons, lines[i]->get_id_start());
	    tmp_end = find_icon_id(icons, lines[i]->get_id_end());
	    
	    //qDebug() << "setting icons....";
	    // set the icons
	    lines[i]->setSourceObject(tmp_start);
	    lines[i]->setDestObject(tmp_end);
	    /*
	    //qDebug() << "drawing....";
	    // draw the line
	    this->addItem(lines[i]);
	    this->scene_lines.append(lines[i]);
	    lines[i]->setZValue(-1);*/
	}
    }

    //qDebug() << "updating....";
    update();
}

Icon * DragScene::find_icon_id(QList<Icon*> icons, int target_id)
{
    int i;

    for ( i = 0; i < icons.length(); i++ )
    {
	if ( icons[i]->getID() == target_id )
	{
	    return icons[i];
	}
    }

    return NULL;
}
