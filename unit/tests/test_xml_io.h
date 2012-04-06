// test_xml_io.h
         
#include <cxxtest/TestSuite.h>
#include "../src/xml_io.h"
#include "dummy_icon.h"
#include "../../src/actor.h"

class ut_xml_io : public CxxTest::TestSuite {
public:
  void test_write_xml(void)
  {
    int size = 2;
    Xml_io *test;

    QList<Icon*> list;
    QString filename = "Testfile";
    QString diagram_type = "testtype";
    
    Icon *temp;
    temp = new actor();
    //temp = new Dummy_icon_test();
    delete temp;
    
    /*
    for( int i = 0; i < size; i++ )
      {
        Icon *temp = new ClassBox();
	list.append(temp);
      }
    */
    //test = new Xml_io(list, filename);
    //test = new Xml_io();

    //test->write_xml();
    /*
    for (int i = 0; i < size; i++ )
      {
	delete list[i];
      }
    */
    delete test;

  }  
};
