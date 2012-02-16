#include <QtTest/QtTest>
#include "TestIcon.h"
#include "icon.h"


TestIcon::TestIcon()
{

}



void TestIcon::setPos()
{
    icon test = new icon;
    test.setPos(150, 300);
    QVERIFY(test.getXPos()==150);
    QVERIFY(test.getYPos()==300);

}



void TestIcon::setSize()
{
    icon test = new icon;
    test.setSize(2,3);
    QVERIFY(test.getXSize()== 2);
    QVERIFY(test.getYSize()== 3);


}


void TestIcon::setShapetype()
{
    icon test = new icon;
    test.setShapetype("testIcon");
    QVERIFY(test.reportShapetype()=="testIcon")

}
