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
		//check on initial size
		cout << "\nBOUNDING RECT INITIAL MEASUREMENTS\nHeight: " << box.boundingRect().height() << ". Width: " << box.boundingRect().width() << endl;
		cout << "m_height: " << box.getHeight() << ". m_width: " << box.getWidth() << endl;

		//check initial contents
		TS_ASSERT(box.getLabel().compare("Name") == 0);
		TS_ASSERT(box.getMembers().compare("Members") == 0);
		TS_ASSERT(box.getMethods().compare("Methods") == 0);
		cout << "\nINITIAL VALUES\nLabel:\t\t'" << box.getLabel().toStdString() 
			<< "'\nMembers:\t'" << box.getMembers().toStdString() 
			<< "'\nMethods:\t'" << box.getMethods().toStdString() << "'" << endl;

	}

	void test_load_instance(void)
	{
		cout << endl << "***CLASSBOX LOADING***" << endl;
		
		int id = 1;
		int width = 140;
		int height = 60;
		int xpos = 76;
		int ypos = 23;
		QString label = "Name$:^:&+&:^:$Members\nMember2$:^:&+&:^:$Methods";

		ClassBox box(0, id, width, height, xpos, ypos, label);

		cout << "ClassBox loaded.  Checking parameters." << endl;

		TS_ASSERT_EQUALS(box.m_id, id);
		TS_ASSERT_EQUALS(box.m_width, width);
//		box.boundingRect().setHeight(height);
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
//		box.paint(0,0,0);
//		box.m_labelBox->setPlainText("giggity");
//		cout << box.m_labelBox->toPlainText() << endl;
		//check dimensions
		int new_height;
		new_height = box.m_labelBox->boundingRect().height()
			+ box.m_memberBox->boundingRect().height()
			+ box.m_methodBox->boundingRect().height() + 60;
		TS_ASSERT_EQUALS(box.m_height, new_height);
	}
	//this test does not work. No feasible way to resize individual boxes.
	void test_arrangeBoxes(void)
	{
/*
		cout << endl << "***CLASSBOX AUTO-RESIZING***" << endl;

		ClassBox box(QPointF(0,0));
		int boxWidth[3];

		boxWidth[0] = box.setWidthsManually(300, 150, 299);
		boxWidth[1] = box.setWidthsManually(299, 350, 299);
		boxWidth[2] = box.setWidthsManually(299, 299, 300);

		//print boxWidths
			cout << "Label width = 300. m_width = " << box.setWidthsManually(300, 150, 299) << endl;
			
			cout << "Memberbox width = 350. m_width = " << boxWidth[1] << endl;
			cout << "Methodbox width = 300. m_width = " << boxWidth[2] << endl;
*/
	}
};
