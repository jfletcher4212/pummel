#ifndef TESTICON_H
#define TESTICON_H

#include "icon.h"
//#include <QtTest/QtTest>

class TestIcon : public icon
{
public:
    TestIcon();
    void setSize();
    void setPos();
    void setShapetype();

};

#endif // TESTICON_H
