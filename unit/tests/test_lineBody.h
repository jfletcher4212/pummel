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

		//QString tmpString = "Testfile.ut";
		//Icon *MyTestClassbox = new ClassBox (0, 5, 5, 0, 0, tmpString);
		//Icon *testCB = NULL; 
		lineBody *testLB = NULL;

		testLB = new solidline(NULL, NULL, 0, 0);

		//lineBody->findObjectCenter(testCB);
	
		//QPointF testCenter = MyTestLine->findObjectCenter (MyTestClassbox);	

		//cout<<"\ntestCenter is: " << testCenter << "\n";

	}

};

