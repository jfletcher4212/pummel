// test_xml_io.h
         
#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../src/xml_io.h"
#include "../../src/actor.h"
#include "../../src/ellipse.h"
#include "../../src/classbox.h"
#include "../../src/note.h"
#include "../../src/roundedsquare.h"
#include "../../src/scenarioend.h"
#include "../../src/scenariostate.h"
#include "../../src/scenariostart.h"
#include "../../src/scenariostart.h"

using namespace std;

class ut_xml_io : public CxxTest::TestSuite {
public:
  void test_write_xml(void)
  {
    int size = 1;
    Xml_io *test;

    QList<Icon*> list;
    QString filename = "Testfile.ut";
    QString diagram_type = "testtype";
    
    for( int i = 0; i < size; i++ )
    {
        Icon *temp;
	
	//if ( i % 2 == 0 )
	//{
	    //temp = new Actor();
	//}
	//else
	//{
	temp = new Ellipse();
	    //}
	
	list.append(temp);
	//delete temp;
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

  void test_parse_xml(void)
  {
      QString filename = "Testfile.ut";
      Xml_io *test = new Xml_io();

      test->set_filename(filename);
      test->parse_xml();
      
      delete test;
  }
  
  void test_parse_icon(void)
  {
      Xml_io *test = new Xml_io();
      Icon *current;
      
      // ellipse
      current = new Ellipse();      
      TS_ASSERT( help_test_parse_icon(test, current) );
      //help_test_parse_icon(test, current);
      delete current;
      
      delete test;
  }
  
  int help_test_parse_icon(Xml_io *test, Icon *input)
  {
      int result;
      Icon *output;

      /// set icon properties
      
      QList<Icon*> list;
      list.append(input);
      QString filename = "tmpfile.ut";
      
      // setup
      test->set_items(list);
      test->set_filename(filename);
      test->write_xml();
      
      QFile infile ( filename );
      infile.open(QIODevice::ReadOnly);
      QXmlStreamReader reader(&infile);      
      
      // run the test
      output = test->parse_icon(reader);

      /*
      result = ( 
	  (TS_ASSERT_EQUALS( input->getWidth(), output->getWidth() ))
	  && (TS_ASSERT_EQUALS( input->getHeight(), output->getHeight() ))
	  && (TS_ASSERT_EQUALS( input->get_xPos(), output->get_xPos() ))
	  && (TS_ASSERT_EQUALS( input->get_yPos(), output->get_yPos() ))
	  && (TS_ASSERT_EQUALS( input->reportShapetype(), output->reportShapetype() ))
	  && (TS_ASSERT_EQUALS( input->get_all(), output->get_all() ))
	  );
      */
      /*
      TS_ASSERT_EQUALS( input->getWidth(), output->getWidth() );
      TS_ASSERT_EQUALS( input->getHeight(), output->getHeight() );
      TS_ASSERT_EQUALS( input->get_xPos(), output->get_xPos() );
      TS_ASSERT_EQUALS( input->get_yPos(), output->get_yPos() );
      TS_ASSERT_EQUALS( input->reportShapetype(), output->reportShapetype() );
      TS_ASSERT_EQUALS( input->get_all(), output->get_all() );
      */
      result = (
	  (input->getWidth() == output->getWidth())
	  && (input->getHeight() == output->getHeight())
	  && (input->get_xPos() == output->get_xPos())
	  && (input->get_yPos() == output->get_yPos())
	  && (input->reportShapetype() == output->reportShapetype())
	  && (input->get_all() == output->get_all())
	  );
      
      delete output;
      return result;
  }
  
  void test_choose_type(void)
  {
      Xml_io *test = new Xml_io();
      
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)Class), (QString)"Class");
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)StateChart), (QString)"StateChart");
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)UseCase), (QString)"UseCase");
      
      // bad value: integer value not in enum
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)5), (QString)"");
      
      
      delete test;
  }
};
