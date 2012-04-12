// test_xml_io.h
         
#include <cxxtest/TestSuite.h>
#include "../src/xml_io.h"
#include "../../src/actor.h"
#include "../../src/ellipse.h"
#include "../../src/classbox.h"

class ut_xml_io : public CxxTest::TestSuite {
public:
  void test_write_xml(void)
  {
    int size = 5;
    Xml_io *test;

    QList<Icon*> list;
    QString filename = "Testfile";
    QString diagram_type = "testtype";
    
    for( int i = 0; i < size; i++ )
    {
        Icon *temp;
	
	if ( i % 2 == 0 )
	{
	    temp = new actor();
	}
	else
	{
	    temp = new Ellipse();
	}
	
	list.append(temp);
    }
    
    test = new Xml_io(list, filename);
    //test = new Xml_io();

    test->write_xml();
    
    for (int i = 0; i < size; i++ )
    {
	delete list[i];
    }
    
    delete test;

  }  
};
