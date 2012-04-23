
#include "xml_io.h"
#include <iostream>
#include <QString>
#include <QDebug>
#include "actor.h"
#include "classbox.h"
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
    m_diagram_type = "";
}

Xml_io::Xml_io(QList<Icon*> icon_list, /*QList<BasicLineObject*> line_list,*/ QString filename, DiagramType diagram_type)
{
    m_items = icon_list;
    ///m_lines = line_list;

    m_filename = filename;
    m_diagram_type = choose_type(diagram_type);
}

Xml_io::~Xml_io()
{
}

QString Xml_io::choose_type(DiagramType d_type)
{
    if ( d_type == (DiagramType)Class) 
    {
	return (QString)"Class";
    }
    if ( d_type == (DiagramType)StateChart) 
    {
	return (QString)"StateChart";
    }
    if ( d_type == (DiagramType)Sequence) 
    {
	return (QString)"Sequence";
    }
    if ( d_type == (DiagramType)UseCase) 
    {
	return (QString)"UseCase";
    }
    
    return (QString)"";
}

void Xml_io::write_xml()
{
    int i;
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
    
    // diagram type
    saver.writeTextElement("diagram_type", m_diagram_type);
    
    for ( i = 0; i < m_items.length(); i++ )
    {
	//QString valueAsString = QString::number(valueAsDouble);
	// wrapper tags coule be the object's individual ID #
	saver.writeStartElement("icon");
	saver.writeTextElement("width", QString::number(m_items[i]->getWidth()));
	saver.writeTextElement("height", QString::number(m_items[i]->getHeight()));
	saver.writeTextElement("x_pos", QString::number(m_items[i]->get_xPos()));
	saver.writeTextElement("y_pos", QString::number(m_items[i]->get_yPos()));
	saver.writeTextElement("label", m_items[i]->get_all());
	saver.writeTextElement("shapetype", m_items[i]->reportShapetype());
	saver.writeEndElement();
    }
    
    /*
    for ( i = 0; i < m_lines.length(); i++ )
    {
	saver.writeStartElement("line");
	// write line type
	// write begin object index
	// write end object index
	// write arrowhead info
	saver.writeEndElement();
    }
    */
    
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
	    
	    if ( reader.name() == "diagram_type" )
	    {
		reader.readNext();
		m_diagram_type = reader.text().toString();
	    }
	    
	    if ( reader.name() == "icon" )
	    {
		//qDebug() << reader.name();
		icons.append(parse_icon(reader));
		//parse_icon(reader);
	    }
	    /*
	    if ( reader.name() == "line" )
	    {
		//qDebug() << reader.name();
		lines.append(parse_line(reader));
		//parse_icon(reader);
	    }	    
	    */
	}
    }
    
    qDebug() << "returning icons";
    m_items = icons;
    ///m_lines = lines;
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
    else if ( type == "RoundedSquare" )
    {
    	ret = new RoundedSquare(0, width, height, x_pos, y_pos, label);
    }
    else if ( type == "ClassBox" )
    {
	ret = new ClassBox(0, width, height, x_pos, y_pos, label);
    }
    else if ( type == "Note" )
    {
        ret = new Note(0, width, height, x_pos, y_pos, label);
    }
    else if ( type == "ScenarioEnd" )
    {
	ret = new ScenarioEnd(0, width, height, x_pos, y_pos);
    }
    else if ( type == "ScenarioState" )
    {
	ret = new ScenarioState(0, width, height, x_pos, y_pos, label);
    }
    else if ( type == "ScenarioStart" )
    {
	ret = new ScenarioStart(0, width, height, x_pos, y_pos);
    }
    
    return ret;
}

