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
		ClassBox box;

		cout << endl << "***CLASSBOX INSTANTIATION***" << endl;
		//check on initial size
		cout << "\nBOUNDING RECT INITIAL MEASUREMENTS\nHeight: " << box.boundingRect().height() << ". Width: " << box.boundingRect().width() << endl;
		cout << "m_height: " << box.getHeight() << ". m_width: " << box.getWidth() << endl;

		//check initial contents
		cout << "\nINITIAL VALUES\nLabel:\t\t'" << box.getLabel().toStdString() 
			<< "'\nMembers:\t'" << box.getMembers().toStdString() 
			<< "'\nMethods:\t'" << box.getMethods().toStdString() << "'" << endl;

	}

	void test_arrangeBoxes(void)
	{
		
	}

};
