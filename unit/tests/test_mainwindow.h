// test.h
         
#include <cxxtest/TestSuite.h>
#include "../src/mainwindow.h"
#include "../src/icon.h"
#include "../src/ellipse.h"

using namespace std;

class ut_dragitem : public CxxTest::TestSuite {
public:
    
    /*********** xml tests begin ***********/
    void test_saveAsFile(void)
    {
	int size = 3;
	//icon *icon_list = new icon[size];
	icon *test = new ellipse();
	//cout<<endl<<"here"<<endl;
	//TS_ASSERT(test->getXSize() == 0);
	
	// start with ellipse. instantiate one of each object later
	/*
	for ( int i = 0; i < size; i++ )
	{
	    icon_list[i] = new ellipse();
	}
	
	TS_ASSERT_EQUALS(icon_list[0]->getXSize(), 0);*/
    }

    void test_openFile(void)
    {
	
    }
    /*********** xml tests end ***********/
};
