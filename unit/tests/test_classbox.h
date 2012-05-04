//test_classbox.h

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../../src/classbox.h"

using namespace std;

class ut_classbox : public CxxTest::TestSuite
{
public:
	void test_instance(void)
	{
		ClassBox box(QPointF(0,0));

		cout << endl << "***CLASSBOX INSTANTIATION***" << endl;
		//check on initial size
		cout << "\nBOUNDING RECT INITIAL MEASUREMENTS\nHeight: " << box.boundingRect().height() << ". Width: " << box.boundingRect().width() << endl;
		cout << "m_height: " << box.getHeight() << ". m_width: " << box.getWidth() << endl;

		//check initial contents
		cout << "\nINITIAL VALUES\nLabel:\t\t'" << box.getLabel().toStdString() 
			<< "'\nMembers:\t'" << box.getMembers().toStdString() 
			<< "'\nMethods:\t'" << box.getMethods().toStdString() << "'" << endl;

	}

	//this test does not work. No feasible way to resize individual boxes.
	void test_arrangeBoxes(void)
	{

		cout << endl << "***CLASSBOX AUTO-RESIZING***" << endl;

		ClassBox box(QPointF(0,0));
		int boxWidth[3];

		boxWidth[0] = box.setWidthsManually(300, 150, 299);
		boxWidth[1] = box.setWidthsManually(299, 350, 299);
		boxWidth[2] = box.setWidthsManually(299, 299, 300);

		//print boxWidths
		for (int i=0; i<=2; i++)
		{
			cout << "Label width = 300. m_width = " << box.setWidthsManually(300, 150, 299) << endl;
			
			cout << "Memberbox width = 350. m_width = " << boxWidth[1] << endl;
			cout << "Methodbox width = 300. m_width = " << boxWidth[2] << endl;
		}
	}

};
