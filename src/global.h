#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "drawarea.h"
#include "tabmanager.h"
#include "toolbar.h"

extern QList<DrawArea*> canvas;
extern TabManager *tabWidget;
extern QPointF contextEventPos;

#endif // __GLOBAL_H__
