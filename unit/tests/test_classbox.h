//test_classbox.h

#include <cxxtest/TestSuite.h>
#include <iostream>
#include <QString>
#include "../../src/classbox.h"

using namespace std;

class ut_classbox : public CxxTest::TestSuite
{
public:
	void test_simple_instance(void)
	{
		ClassBox box(QPointF(0,0));

		cout << endl << "***CLASSBOX INSTANTIATION***" << endl;
		//check initial contents
		TS_ASSERT(box.getLabel().compare("Name") == 0);
		TS_ASSERT(box.getMembers().compare("Members") == 0);
		TS_ASSERT(box.getMethods().compare("Methods") == 0);
	}

	void test_load_instance(void)
	{
		cout << endl << "***CLASSBOX LOADING***" << endl;
		
		int id = 1;
		int width = 140;
		int height = 60;
		int xpos = 76;
		int ypos = 23;
		QString label = "Name";
		label.append(XML_DELIM);
		label.append("Members\nMember2");
		label.append(XML_DELIM);
		label.append("Methods");

		ClassBox box(0, id, width, height, xpos, ypos, label);

		cout << "ClassBox loaded.  Checking parameters." << endl;

		TS_ASSERT_EQUALS(box.m_id, id);
		TS_ASSERT_EQUALS(box.m_width, width);
		TS_ASSERT_EQUALS(box.m_height, height);
		TS_ASSERT_EQUALS(box.m_xPos, xpos);
		TS_ASSERT_EQUALS(box.m_yPos, ypos);
		TS_ASSERT_EQUALS(box.m_width, width);
		

		QString quick;
		quick = box.getLabel();
		TS_ASSERT(quick.compare("Name") == 0);
		quick = box.getMembers();
		TS_ASSERT(quick.compare("Members\nMember2") == 0);
		quick = box.getMethods();
		TS_ASSERT(quick.compare("Methods") == 0);

		box.arrangeBoxes();
		//check dimensions
		int new_height;
		new_height = box.m_labelBox->boundingRect().height()
			+ box.m_memberBox->boundingRect().height()
			+ box.m_methodBox->boundingRect().height() + 60;
		TS_ASSERT_EQUALS(box.m_height, new_height);
	}
};
