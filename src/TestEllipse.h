#ifndef TESTELLIPSE_H
#define TESTELLIPSE_H

#include "ellipse.h"
//#include <QtTest/QtTest>

class TestEllipse : Ellipse
{
    TestEllipse();
    QRectF boundingRect() const;
    void paint();
    void mouseMoveEvent();
    void mousePressEvent();
    void mouseReleaseEvent();
    void getID();

};

#endif // TESTELLIPSE_H
