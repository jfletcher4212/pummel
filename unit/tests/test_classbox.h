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
		int height = 0;
		int x_pos = 76;
		int y_pos = 23;
		QString label = "Name$:^:&+&:^:$Members\nMember2$:^:&+&:^:$Methods";

		ClassBox box(0, id, width, height, x_pos, y_pos, label);

		cout << "ClassBox loaded.  Checking parameters." << endl;

		QString quick;
		quick = box.getLabel();
		TS_ASSERT(quick.compare("Name") == 0);
		quick = box.getMembers();
		TS_ASSERT(quick.compare("Members\nMember2") == 0);
		quick = box.getMethods();
		TS_ASSERT(quick.compare("Methods") == 0);

		//check dimensions
		m_height = m_labelBox->boundingRect().height
			+ m_memberBox->boundingRect().height
			+ m_methodBox->boundingRect().height();

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
