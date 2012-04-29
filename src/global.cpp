#include "drawarea.h"
#include "tabmanager.h"
#include "toolbar.h"

QList<DrawArea*> canvas;
TabManager *tabWidget;
Toolbar *toolbar;
QPointF contextEventPos;
int g_savepromptval;
