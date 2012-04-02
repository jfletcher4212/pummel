#include "dragview.h"

DragView::DragView(QWidget *parent) : QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing);
}


