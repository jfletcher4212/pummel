//test_roundedsquare.h

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <QString>
#include "../../src/roundedsquare.h"

using namespace std;

class ut_classbox : public CxxTest::TestSuite
{
public:
    void test_get_split_all(void)
    {
	int id = 1;
	int width = 140;
	int height = 60;
	int xpos = 76;
	int ypos = 23;
	QString label = "Name";
	label.append(XML_DELIM);
	label.append("Members");
	
	Icon *box = new RoundedSquare(0, id, width, height, xpos, ypos, label);
	
	QString result_str = box->get_all();
	QStringList result_lis = box->split_all(label);
	
	TS_ASSERT_EQUALS(result_str, label);
	TS_ASSERT_EQUALS(result_lis[0], "Name");
	TS_ASSERT_EQUALS(result_lis[1], "Members");
	
	delete box;
    }
};
