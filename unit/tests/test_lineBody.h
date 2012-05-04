#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../../src/solidline.h"
#include "../../src/classbox.h"

using namespace std;


class ut_lineBody : public CxxTest::TestSuite {
public:
  void test_getState(void)
  {
        cout<<"\nTesting\n";
        }

  void test_findObjectCenter(void)
	{

		QPointF tmpQPoint;//creates the point at 0,0 
		Icon *TestCB = new ClassBox (tmpQPoint);
		lineBody *testLB = new solidline(TestCB, TestCB, 0, 0);
		//findObjectCenter is protected in linebody.h
		//tmpQPoint = testLB->findObjectCenter(TestCB);
	
		//cout<<"\ntestCenter is: " << tmpQPoint.x() << ", " << tmpQPoint.y() << "\n";

	}

};

