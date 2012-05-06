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
		Icon *TestCB1 = new ClassBox (QPointF(0,0));
		Icon *TestCB2 = new ClassBox (QPointF(10,10));
		lineBody *testLB = new solidline(TestCB1, TestCB2, 0, 0);
		TestCB1->setSize(100,100);		

		QPointF result;
		result = testLB->findObjectCenter(TestCB1);

		TS_ASSERT((result.x() == 50) && (result.y() == 50));	

	}

	void test_findSRLCenter(void)
	{
                Icon *TestCB1 = new ClassBox (QPointF(0,0));
                lineBody *testLB = new solidline(TestCB1, TestCB1, 0, 0);
                TestCB1->setSize(100,100);
		QPointF result;
                result = testLB->findSRLCenter(TestCB1);

		TS_ASSERT((result.x() == 100) && (result.y() == 50));

	}

        void test_calcSRLRadius(void)
        {

                Icon *TestCB1 = new ClassBox (QPointF(0,0));
                lineBody *testLB = new solidline(TestCB1, TestCB1, 0, 0);
                TestCB1->setSize(100,100);
                qreal result;
                result = testLB->calcSRLRadius(TestCB1);

		TS_ASSERT_EQUALS (result, 45);
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


        void test_squareLine(void)
        {
                Icon *TestCB1 = new ClassBox (QPointF(0,0));
                Icon *TestCB2 = new ClassBox (QPointF(100,100));
                lineBody *testLB = new solidline(TestCB1, TestCB2, 0, 0);
                TestCB1->setSize(100,100);
                TestCB2->setSize(100,100);
		QPointF qpfStart = QPointF(0, 0);
		QPointF qpfEnd = QPointF(100, 100);
		QPointF *qpfSecond = new QPointF(0, 0);
                QPointF *qpfThird = new QPointF(100, 100);

		testLB->squareLine(qreal(10), qpfStart, qpfEnd, qpfSecond, qpfThird);

		TS_ASSERT((qpfSecond->x() == 50) && (qpfSecond->y() == 0));
		TS_ASSERT((qpfThird->x() == 50) && (qpfThird->y() == 100));

		qpfSecond = new QPointF(0, 0);
                qpfThird = new QPointF(100, 100);

		testLB->squareLine(qreal(55), qpfStart, qpfEnd, qpfSecond, qpfThird);

		TS_ASSERT((qpfSecond->x() == 0) && (qpfSecond->y() == 50));
		TS_ASSERT((qpfThird->x() == 100) && (qpfThird->y() == 50));
        }
};

