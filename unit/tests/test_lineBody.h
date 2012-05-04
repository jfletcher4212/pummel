#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../../src/solidline.h"
#include "../../src/classbox.h"

using namespace std;


class ut_lineBody : public CxxTest::TestSuite
{
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

	void test_checkReferences(void)
	{
		Icon *box1 = new ClassBox(QPointF(0,0));
		Icon *box2 = new ClassBox(QPointF(30,30));
		lineBody *line = new solidline(box1, box2, 0, 0);

		bool result;
		result = line->checkReferences(NULL, NULL);
		TS_ASSERT_EQUALS(result, false);
		result = line->checkReferences(box1, NULL);
		TS_ASSERT_EQUALS(result, false);
		result = line->checkReferences(NULL, box1);
		TS_ASSERT_EQUALS(result, false);
		result = line->checkReferences(box1, box2);
		TS_ASSERT_EQUALS(result, true);
	}

	void test_checkInterPoint(void)
	{
		Icon *box2 = new ClassBox(QPointF(30,30));
		lineBody *line = new solidline(box2, box2, 0, 0);
		QPointF dummy;
		bool result;

		dummy.setX(NULL);
		dummy.setY(NULL);
		result = line->checkInterPoint(dummy);
		TS_ASSERT_EQUALS(result, false);
		dummy.setX(15);
		dummy.setY(NULL);
		result = line->checkInterPoint(dummy);
		TS_ASSERT_EQUALS(result, false);
		dummy.setX(NULL);
		dummy.setY(15);
		result = line->checkInterPoint(dummy);
		TS_ASSERT_EQUALS(result, false);
		dummy.setX(15);
		dummy.setY(15);
		result = line->checkInterPoint(dummy);
		TS_ASSERT_EQUALS(result, true);
	}
};

