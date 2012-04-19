
#include "xml_io.h"
#include <iostream>
#include <QString>
#include <QDebug>
#include "actor.h"
#include "ellipse.h"


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
    
    //Icon(int width, int height, int id, int label, int shapetype);
    
    for ( int i = 0; i < m_items.length(); i++ )
    {
	//QString valueAsString = QString::number(valueAsDouble);
	// wrapper tags coule be the object's individual ID #
	saver.writeStartElement("icon");
	saver.writeTextElement("width", QString::number(m_items[i]->getWidth()));
	saver.writeTextElement("height", QString::number(m_items[i]->getHeight()));
	saver.writeTextElement("id", QString::number(m_items[i]->getID()));
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
    //QList< QMap<QString,QString> > icons;
    
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
		//icons.append(parse_icon(reader));
		parse_icon(reader);
	    }
	    
	}
    }
    
//    return icons;
}

void Xml_io::parse_icon(QXmlStreamReader &reader)
{
    int width;
    int height;
    int id;
    QString type;
    
    Icon *ret;
    
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

	    if( reader.name() == "id")
	    {
		reader.readNext();
		id = reader.text().toString().toInt();
	    }

	    if( reader.name() == "shapetype")
	    {
		reader.readNext();
		type = reader.text().toString();
	    }
	}
    }

    if ( type == "Ellipse") 
    {
	ret = new Ellipse();
    }
    if ( type == "Actor" )
    {
	ret = new actor();
    }
    
    //return ret;
}

QMap<QString, QString> Xml_io::parsePerson(QXmlStreamReader& xml)
{
    QMap<QString, QString> icon;
  
    if ( ! (xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "coord") ) 
	return icon;
  
    QXmlStreamAttributes attributes = xml.attributes();
    /*
    // this is for the object id
    if(attributes.hasAttribute("icon_id")) 
    {
    person["icon_id"] = attributes.value("icon_id").toString();
    }
    xml.readNext();
    */
    /*
    while( !(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "coord") )
    {
	if( xml.tokenType() == QXmlStreamReader::StartElement) 
	{
	    if( xml.name() == "x_coord" ) 
	    {
		this->addElementDataToMap(xml, icon);
	    }
	  
	    if( xml.name() == "y_coord" ) 
	    {
		this->addElementDataToMap(xml, icon);
	    }
	}
	xml.readNext();
    }
    */
    return icon;
}
