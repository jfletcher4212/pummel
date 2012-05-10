#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#ifndef _UNIT_TEST_
#define _UNIT_TEST_
#endif

#include "drawarea.h"
#include "tabmanager.h"
#include "toolbar.h"

extern QList<DrawArea*> canvas;
extern TabManager *tabWidget;
extern QPointF contextEventPos;
extern int g_savepromptval;
#endif // __GLOBAL_H__
