#ifndef GLOBALTOOLBAR_H
#define GLOBALTOOLBAR_H

#include "toolbar.h"

extern Toolbar *toolbar;

typedef struct Snapshot{
    DiagramType d_type;
    ShapeCreationType s_type;
    bool createMode;
} Snapshot;

#endif // GLOBAL_H
