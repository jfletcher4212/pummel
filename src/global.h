#ifndef GLOBAL_H
#define GLOBAL_H
#include "drawarea.h"
#include "tabmanager.h"
#include "toolbar.h"

extern QList<DrawArea*> canvas;
extern TabManager *tabWidget;
extern QPointF contextEventPos;

#endif // GLOBAL_H
