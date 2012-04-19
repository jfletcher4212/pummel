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
    QString filename = "Testfile.ut";
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

  void test_parse_xml(void)
  {
      QString filename = "Testfile.ut";

      Xml_io *test = new Xml_io();
      test->set_filename(filename);
      
      test->parse_xml();
      
      
      delete test;
  }
};

/*
Things to do:

mainwindow.cpp:
   save method
   draw_icons method

xml_io.cpp
   add icon positions
   add icon text
   handle classbox (multiple text boxes)
   handle lines (line list)
   handle diagram type
   prompt to save on exit (low priority)
   

other:
   icons need to have constructors that take 
   all possible params

 */

/*
void MainWindow::saveAsFile()
{
    // dialog box for user to enter filename
    QString filename = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath(), "*.xml");
    //Xml_io writer(icon_list, filename, diagram_type);
    //Xml_io writer(icon_list, filename);
    
    // write the file
    //writer.write_xml();
    
    // make a new tab
    tabWidget->setTabText(tabWidget->currentIndex(), filename );
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.xml" );
    //Xml_io writer();
    
    // parse the xml
    //writer.set_filename(filename);
    //new_icons = writer.parse_xml();
    
    // strip full path off filename for display
    //int idx = filename.lastIndexOf("/");
    //filename.remove(0, idx+1);
    
    tabWidget->setTabText(tabWidget->currentIndex(), filename);
    //draw_icons(new_icons);
}

void MainWindow::draw_icons()
{
    // draw the icons and set globals
}
 */
