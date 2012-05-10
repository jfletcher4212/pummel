
#include "xml_io.h"
#include <iostream>
#include <QString>
#include <QDebug>

#include "derived_types.h"

using namespace std;

Xml_io::Xml_io(QString filename)
{
    m_filename = filename;
    m_diagram_type = (DiagramType)(-1);
}

Xml_io::Xml_io(QList<Icon*> icon_list, QList<lineBody*> line_list, QString filename, DiagramType diagram_type)
{
    m_items = icon_list;
    m_lines = line_list;

    m_filename = filename;
    m_diagram_type = choose_type(diagram_type);
}

Xml_io::~Xml_io()
{
}

//////////////////////////////////////////////////////////////////////
// the method returns the string value corresponding to the
// diagram type enum value
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
    if ( d_type == (DiagramType)UseCase)
    {
	return (QString)"UseCase";
    }

    return (QString)"";
}

//////////////////////////////////////////////////////////////////////
// writes the contents of m_items (icons in the diagram) and 
// m_lines (lines in the diagram) as well as diagram type and filename
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

    // write the icons
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
	saver.writeTextElement("id", QString::number(m_items[i]->getID()));
	saver.writeTextElement("shapetype", m_items[i]->reportShapetype() );
	saver.writeEndElement();
    }
    
    // write the lines
    for ( i = 0; i < m_lines.length(); i++ )
    {
	saver.writeStartElement("line");
	saver.writeTextElement("id_start", QString::number(m_lines[i]->get_id_start()) );
	saver.writeTextElement("id_end", QString::number(m_lines[i]->get_id_end()) );
	saver.writeTextElement("linetype", QString::number(m_lines[i]->getLinetype()) );
	saver.writeEndElement();
    }
    
    saver.writeEndDocument();
    saver.setAutoFormatting(true);
    savefile.close();
}

//////////////////////////////////////////////////////////////////////
// parses out all data needed to recreate the diagram from scratch:
// filename, diagram type, icon properties and line properties
// based on icon and line properties is able to create list of icons
// and lines and saves them
void Xml_io::parse_xml()
{
    // do a check to ensure the file exists first
    QFile infile ( m_filename );
    infile.open(QIODevice::ReadOnly);

    QXmlStreamReader reader(&infile);

    // empty lists
    QList<Icon*> icons;
    QList<lineBody*> lines;

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
		// save the diagram type
		reader.readNext();
		m_diagram_type = reader.text().toString();
	    }
	    
	    if ( reader.name() == "icon" )
	    {
		// append found icon to the list
		icons.append(parse_icon(reader));
	    }
        
	    if ( reader.name() == "line" )
	    {
		// append found line to the list
		lines.append(parse_line(reader));
	    }
	    
	}
    }
    
    m_items = icons;
    m_lines = lines;
}

//////////////////////////////////////////////////////////////////////
// handles a given icon portion of the xml file. takes the reader
// as input and parses the icon properties and returns the result
// of make_icon passing the found properties as input
Icon * Xml_io::parse_icon(QXmlStreamReader &reader)
{
    // default values
    int id = 0;
    int width = 0;
    int height = 0;
    int x_pos = 0;
    int y_pos = 0;
    QString label = "";
    QString type = "";

    while ( ! (reader.tokenType() == QXmlStreamReader::EndElement &&  reader.name() == "icon") )
    {
	//read next element
	QXmlStreamReader::TokenType token = reader.readNext();

	if ( token == QXmlStreamReader::StartElement )
	{
	    if( reader.name() == "width")
	    {
		// read the width
		reader.readNext();
		width = reader.text().toString().toInt();
	    }

	    if( reader.name() == "height")
	    {
		// read the height
		reader.readNext();
		height = reader.text().toString().toInt();
	    }

	    if( reader.name() == "x_pos")
	    {
		// read the x position
		reader.readNext();
		x_pos = reader.text().toString().toInt();
	    }

	    if( reader.name() == "y_pos")
	    {
		// read the y position
		reader.readNext();
		y_pos = reader.text().toString().toInt();
	    }

	    if( reader.name() == "label")
	    {
		// read the icon label
		reader.readNext();
		label = reader.text().toString();
	    }

	    if( reader.name() == "id")
	    {
		// read the icon id
		reader.readNext();
		id = reader.text().toString().toInt();
	    }

	    if( reader.name() == "shapetype")
	    {
		// read the shapetype
		reader.readNext();
		type = reader.text().toString();
	    }
	}
    }
    
    // return a new icon with found properties
    return make_icon(type, id, width, height, x_pos, y_pos, label);
}

//////////////////////////////////////////////////////////////////////
// takes a set of icon properties and returns a new icon based
// on the shapetype value, passing all other values to the icon
// on instantiation.
Icon * Xml_io::make_icon(QString type, int id, int width, int height, int x_pos, int y_pos, QString label)
{
    Icon *ret = NULL;

    if ( type == "Ellipse")
    {
	ret = new Ellipse(0, id, width, height, x_pos, y_pos, label);
    }
    else if ( type == "Actor" )
    {
	ret = new Actor(0, id, width, height, x_pos, y_pos, label);
    }
    else if ( type == "Rounded Square" )
    {
        ret = new RoundedSquare(0, id, width, height, x_pos, y_pos, label);
    }
    else if ( type == "Class Box" )
    {
	ret = new ClassBox(0, id, width, height, x_pos, y_pos, label);
    }
    else if ( type == "Note" )
    {
        ret = new Note(0, width, height, x_pos, y_pos, label);
    }
    
    // scenario icons do not hold labels
    else if ( type == "Scenario End" )
    {
	ret = new ScenarioEnd(0, id, width, height, x_pos, y_pos);
    }
    else if ( type == "Scenario Start" )
    {
	ret = new ScenarioStart(0, id, width, height, x_pos, y_pos);
    }
    
    
    return ret;
}

//////////////////////////////////////////////////////////////////////
// handles a given line portion of the xml file. takes the reader
// as input and parses the line properties and returns the result
// of make_line passing the found properties as input
lineBody * Xml_io::parse_line(QXmlStreamReader &reader)
{
    // default values
    int linetype = -1;
    int id_start = -1;
    int id_end = -1;

    while ( ! (reader.tokenType() == QXmlStreamReader::EndElement &&  reader.name() == "line") )
    {
	//read next element
	QXmlStreamReader::TokenType token = reader.readNext();
	
	//qDebug() << reader.name();
	
	if ( token == QXmlStreamReader::StartElement )
	{
	    if ( reader.name() == "id_start" )
	    {
		// read the id of the line's source icon
		reader.readNext();
		id_start = reader.text().toString().toInt();
	    }
	    
	    if ( reader.name() == "id_end" )
	    {
		// read the id of the line's destination icon
		reader.readNext();
		id_end = reader.text().toString().toInt();		
	    }

	    if ( reader.name() == "linetype" )
	    {
		// read the line type (enum value)
		reader.readNext();
		linetype = reader.text().toString().toInt();
	    }
	}
    }
    
    return make_line(linetype, id_start, id_end);
}

//////////////////////////////////////////////////////////////////////
// takes a set of line properties and returns a new line based
// on the linetype value, passing all other values to the line
// on instantiation.
lineBody * Xml_io::make_line(int linetype, int id_start, int id_end)
{
    lineBody *ret = NULL;

    if ( linetype == (LineType)Solid_Line )
    {
	ret = new solidline(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Line_EAH )
    {
	ret = new solidlineeah(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Line_BAH )
    {
	ret = new solidlineBAH(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Line_BAH )
    {
	ret = new dottedlinebah(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Sq_Line_EAH )
    {
	ret = new solidsqlineeah(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Sq_Line_EAH )
    {
	ret = new dottedsqlineeah(id_start, id_end);
    }
    if ( linetype == (LineType)Self_Ref_Line )
    {
	ret = new selfRefLine(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Sq_Line_BAH )
    {
	ret = new solidsqlinebah(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Sq_Line_SD )
    {
	ret = new solidsqlinesd(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Sq_Line_ED )
    {
	ret = new solidsqlineed(id_start, id_end);
    }
    
    return ret;
}


