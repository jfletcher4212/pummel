// test_xml_io.h
         
#include <cxxtest/TestSuite.h>
#include <iostream>
#include "../../src/global.h"
#include "../../src/xml_io.h"
#include "../../src/icon.h"
#include "../../src/actor.h"
#include "../../src/ellipse.h"
#include "../../src/classbox.h"
#include "../../src/note.h"
#include "../../src/roundedsquare.h"
#include "../../src/scenarioend.h"
#include "../../src/scenariostart.h"
#include "../../src/scenariostart.h"

using namespace std;

class test_xml_io : public CxxTest::TestSuite
{
public:
  void test_write_xml(void)
  {
    int size = 0;
    Xml_io *test;

    QList<Icon*> list;
    QString filename = "Testfile.ut";
    QString diagram_type = "testtype";
    Icon *tmp;    

    // actor
    tmp = new Actor(0, 0, 23, 23, 23, 23, (QString)"test_actor");
    list.append(tmp);
    size++;
    
    // ellipse
    tmp = new Ellipse(0, 0, 23, 23, 23, 23, (QString)"test_ellipse");
    list.append(tmp);
    size++;
    
    // classbox
    tmp = new ClassBox(0, 0, 23, 23, 23, 23, (QString)"test_classbox$:^:&+&:^:$and$:^:&+&:^:$this");
    list.append(tmp);
    size++;
        
    // note
    //tmp = new Note(0, 0, 23, 23, 23, 23, (QString)"test_note");
    //list.append(tmp);
        
    // roundedsquare
    tmp = new RoundedSquare(0, 0, 23, 23, 23, 23, (QString)"test$:^:&+&:^:$roundedsquare");
    list.append(tmp);
    size++;
        
    // scenariostart
    tmp = new ScenarioStart(0, 0, 23, 23, 23, 23);
    list.append(tmp);
    size++;
        
    // scenarioend
    tmp = new ScenarioEnd(0, 0, 23, 23, 23, 23);      
    list.append(tmp);
    size++;
    
    test = new Xml_io(filename);
    test->set_items(list);
    size++;
    
    // run the test
    test->write_xml();
    
    // write an expected file and diff?
    // or verify things can be read out?
    
    for (int i = 0; i < size; i++ )
    {
	delete list[i];
    }
    
    delete test;


  } 

  void test_parse_xml(void)
  {
      /*
      QString filename = "Testfile.ut";
      Xml_io *test = new Xml_io(filename);

      test->set_filename(filename);
      test->parse_xml();
      
      delete test;*/
  }
  
  // do instantiation better per class
  void test_parse_icon(void)
  {
      /*
      QString filename = "tmpfile.ut";
      Xml_io *test = new Xml_io(filename);
      Icon *current;
      
      // actor
      current = new Actor(0, 0, 23, 23, 23, 23, (QString)"test_actor");
      help_test_parse_icon(test, current);
      delete current;

      // ellipse
      current = new Ellipse(0, 0, 23, 23, 23, 23, (QString)"test_ellipse");
      help_test_parse_icon(test, current);
      delete current;

      // classbox $:^:&+&:^:$
      current = new ClassBox(0, 0, 23, 23, 23, 23, (QString)"test_classbox$:^:&+&:^:$and$:^:&+&:^:$this");
      help_test_parse_icon(test, current);
      delete current;

      // note
      //current = new Note(0, 0, 23, 23, 23, 23, (QString)"test_note");
      //help_test_parse_icon(test, current);
      delete current;

      // roundedsquare
      current = new RoundedSquare(0, 0, 23, 23, 23, 23, (QString)"test_rounded$:^:&+&:^:$square");
      help_test_parse_icon(test, current);
      delete current;

      // scenariostart
      current = new ScenarioStart(0, 0, 23, 23, 23, 23);
      help_test_parse_icon(test, current);
      delete current;

      // scenarioend
      current = new ScenarioEnd(0, 0, 23, 23, 23, 23);      
      help_test_parse_icon(test, current);
      delete current;

      
      delete test;*/
  }
  
  void help_test_parse_icon(Xml_io *test, Icon *input)
  {/*
      int result;
      Icon *output;
      
      // setup
      QList<Icon*> list;
      list.append(input);
      QString filename = "tmpfile.ut";

      test->set_items(list);
      test->set_filename(filename);
      test->write_xml();
      
      QFile infile ( filename );
      infile.open(QIODevice::ReadOnly);
      QXmlStreamReader reader(&infile);      
      
      // run the test
      //output = test->parse_icon(reader);
      
      TS_ASSERT(input->getWidth() == output->getWidth());
      TS_ASSERT(input->getHeight() == output->getHeight());
      TS_ASSERT(input->get_xPos() == output->get_xPos());
      TS_ASSERT(input->get_yPos() == output->get_yPos());
      TS_ASSERT(input->reportShapetype() == output->reportShapetype());
      TS_ASSERT(input->get_all() == output->get_all());

      // cleanup
      delete output;*/
  }
  
  void test_make_icon(void)
  {/*
      QString filename = "tmpfile.ut";
      Xml_io *test = new Xml_io(filename);
      Icon *current;
      
      QString val0 = "Actor";
      QString val1 = "test_actor";
      int val2 = 23;
      int val3 = 23;
      int val4 = 23;
      int val5 = 23;
      
      // actor
      //current = test->make_icon(val0, val2, val3, val4, val5, val1);
      //TS_ASSERT(current);
      
      delete current;
      delete test;*/
  }
  
  void test_choose_type(void)
  {
      QString filename = "tmpfile.ut";
      Xml_io *test = new Xml_io(filename);
      
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)Class), (QString)"Class");
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)StateChart), (QString)"StateChart");
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)UseCase), (QString)"UseCase");
      
      // bad value: integer value not in enum
      TS_ASSERT_EQUALS(test->choose_type((DiagramType)5), (QString)"");
      
      
      delete test;
  }
};
