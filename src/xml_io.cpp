
#include "xml_io.h"
#include <iostream>
#include <QString>
#include <QDebug>
#include "actor.h"
#include "ellipse.h"
#include "note.h"
#include "roundedsquare.h"
#include "scenarioend.h"
#include "scenariostate.h"
#include "scenariostart.h"
#include "scenariostart.h"


using namespace std;


Xml_io::Xml_io()
{
    //m_items = NULL;
  
    m_filename = "";
    //m_diagram_type = "";
}

Xml_io::Xml_io(QList<Icon*> icon_list, QString filename/*, QString diagram_type*/ )
{
    m_items = icon_list;

    m_filename = filename;
    //m_diagram_type = diagram_type;
}

Xml_io::~Xml_io()
{
}

void Xml_io::write_xml()
{
    int idx;
    QFile savefile ( m_filename );
    savefile.open(QIODevice::WriteOnly);
    
    // strip full path off filename for display later and addition to xml file
    idx = m_filename.lastIndexOf("/");
    m_filename.remove(0, idx+1);
    
    // instantiate the xml writer
    QXmlStreamWriter saver(&savefile);
    
    saver.writeStartDocument();
    saver.writeStartElement(m_filename);
    //saver.writeStartElement(m_diagram_type);
    
    for ( int i = 0; i < m_items.length(); i++ )
    {
	//QString valueAsString = QString::number(valueAsDouble);
	// wrapper tags coule be the object's individual ID #
	saver.writeStartElement("icon");
	saver.writeTextElement("width", QString::number(m_items[i]->getWidth()));
	saver.writeTextElement("height", QString::number(m_items[i]->getHeight()));
	//saver.writeTextElement("x_pos", QString::number(m_items[i]->get_xPos()));
	//saver.writeTextElement("y_pos", QString::number(m_items[i]->get_yPos()));
	//saver.writeTextElement("label", m_items[i]->getLabel());
	saver.writeTextElement("shapetype", m_items[i]->reportShapetype());
	saver.writeEndElement();
    }
    
    saver.writeEndDocument();
    saver.setAutoFormatting(true);
    savefile.close();
}

void Xml_io::parse_xml()
{
    // do a check to ensure the file exists first
    QFile infile ( m_filename );
    infile.open(QIODevice::ReadOnly);
    
    QXmlStreamReader reader(&infile);

    QList<Icon*> icons;
    
    while ( ! reader.atEnd() && ! reader.hasError() )
    {
	//read next element
	QXmlStreamReader::TokenType token = reader.readNext();
	
	if ( token == QXmlStreamReader::StartDocument )
	{
	    continue;
	}
	
	if ( token == QXmlStreamReader::StartElement )
	{
	    if ( reader.name() == m_filename )
	    {
		continue;
	    }
	    
	    if ( reader.name() == "icon" )
	    {
		//qDebug() << reader.name();
		icons.append(parse_icon(reader));
		//parse_icon(reader);
	    }
		
	}
    }
    
    //    return icons;
}

Icon * Xml_io::parse_icon(QXmlStreamReader &reader)
{
    int width;
    int height;
    int x_pos;
    int y_pos;
    QString label;
    QString type;
    
    // next element
    reader.readNext();
    
    while ( ! (reader.tokenType() == QXmlStreamReader::EndElement &&  reader.name() == "icon") )
    {
	//read next element
	QXmlStreamReader::TokenType token = reader.readNext();

	if ( token == QXmlStreamReader::StartElement )
	{
	    if( reader.name() == "width")
	    {
		reader.readNext();
		width = reader.text().toString().toInt();
	    }
	    
	    if( reader.name() == "height")
	    {
		reader.readNext();
		height = reader.text().toString().toInt();
	    }

	    if( reader.name() == "x_pos")
	    {
		reader.readNext();
		x_pos = reader.text().toString().toInt();
	    }
	    
	    if( reader.name() == "y_pos")
	    {
		reader.readNext();
		y_pos = reader.text().toString().toInt();
	    }

	    if( reader.name() == "label")
	    {
	    	reader.readNext();
	    	label = reader.text().toString();
	    }

	    if( reader.name() == "shapetype")
	    {
		reader.readNext();
		type = reader.text().toString();
	    }
	}
    }
    
    return make_icon(type, width, height, x_pos, y_pos, label);
}

Icon * Xml_io::make_icon(QString type, int width, int height, int x_pos, int y_pos, QString label)
{
    Icon *ret = NULL;
    
    if ( type == "Ellipse") 
    {
	ret = new Ellipse(0, width, height, x_pos, y_pos, label);
    }
    else if ( type == "Actor" )
    {
	ret = new Actor(0, width, height, x_pos, y_pos, label);
    }
    //else if ( type == "ClassBox" )
    //{
    //ret = new ClassBox(width, height, x_pos, y_pos, label);
    //}
    //else if ( type == "RoundedSquare" )
    //{
    //	ret = new roundedSquare(width, height, x_pos, y_pos, label);
    //}
    //else if ( type == "Note" )
    //{
//	ret = new note(width, height, x_pos, y_pos, label);
    //}
    //else if ( type == "ScenarioEnd" )
    //{
//	ret = new ScenarioEnd(width, height, x_pos, y_pos, label);
    //}
    //else if ( type == "ScenarioState" )
    //{
//	ret = new ScenarioState(width, height, x_pos, y_pos, label);
    //}
    //else if ( type == "ScenarioStart" )
    //{
//	ret = new ScenarioStart(width, height, x_pos, y_pos, label);
    //}
    
    return ret;
}

