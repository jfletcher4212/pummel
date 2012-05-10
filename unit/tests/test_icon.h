// MyTestSuite.h
#include <cxxtest/TestSuite.h>
#include <QWidget>
#include <iostream>
#include <QGraphicsItem>
#include <QPointF>
#include "../../src/markerbox.h"
#include "../../src/icon.h"
#include "../../src/ellipse.h"

using namespace std;

class test_icon : public CxxTest::TestSuite
{
public:
   void test_boundingRect()
   {
/*
     QRectF expected = QRectF(0,0,5,5);
     Icon* actual;
     QRectF actual1 = actual->boundingRect(); 
     TS_ASSERT( actual1 == expected );
     TS_ASSERT_EQUALS( actual1, expected );
 
     delete actual;
*/
   }
   void test_getWidth_setSize()
   {
/*
     int expected = 5;
     Icon* example;
     example->setSize(expected,0);

     TS_ASSERT( example->getWidth() == expected );
     TS_ASSERT_EQUALS( expected, example->getWidth() ); 

     delete example;
*/
   } 
   void test_getHeight_setSize()
   { 
/*
     int actual;
     int expected = 5;
     Icon* example = new Ellipse;
     example->setSize(0, expected);
     actual = example->getHeight();

     TS_ASSERT( actual == expected );
     TS_ASSERT_EQUALS( actual, expected  );

     delete example;
*/
   } 
   void test_set_Pos_get_XPos()
   {
/*
     int actual;
     int expected = 5;
     Icon* example;
     example->set_Pos(expected, 1);
     actual = example->get_xPos();

     TS_ASSERT( actual == expected );
     TS_ASSERT_EQUALS( actual, expected  );

     delete example;
*/
   }
   void test_set_Pos_get_YPos()
   {
/*
     int actual;
     int expected = 5;
     Icon *example;
     example->set_Pos(1, expected);
     actual = example->get_yPos();

     TS_ASSERT( actual == expected );
     TS_ASSERT_EQUALS( actual, expected  );

     delete example;
*/
   }
   void test_setState_getState()
   {
/*
     int actual;
     int expected = 1;
     Icon* example = new Ellipse;
     example->setState(expected);
     actual = example->getState();

     TS_ASSERT( actual == expected );
     TS_ASSERT_EQUALS( actual, expected  );

     delete example;
*/
    }

   void test_setShapetype_reportShapetype()
   {
/*
     QString expected = "testShape!";

     Icon* example = new Ellipse;
     example->setShapetype(expected);
     QString actual = example->reportShapetype();

     TS_ASSERT( actual == expected );
     TS_ASSERT_EQUALS( actual, expected);
     
     delete example;
*/
   }
   void test_setText_getLabel()
   {
/*
     QString expected = "test text string!!";
     
     Icon* example = new Ellipse;
     example->setText(expected);
     QString actual = example->getLabel();

     TS_ASSERT( actual == expected );
     TS_ASSERT_EQUALS( actual, expected);
     
     delete example;
*/
   }
};
