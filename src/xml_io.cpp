
#include "xml_io.h"
#include <iostream>
#include <QString>
#include <QDebug>

#include "derived_types.h"

using namespace std;

Xml_io::Xml_io(QString filename)
{
    m_filename = filename;
    m_diagram_type = (DiagramType)-1;
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
    return (QString)"Sequence";
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
	saver.writeTextElement("shapetype", m_items[i]->reportShapetype() );
    saver.writeEndElement();
    }
    
    for ( i = 0; i < m_lines.length(); i++ )
    {
    saver.writeStartElement("line");
	saver.writeTextElement("linetype", QString::number(m_lines[i]->getLinetype()) );
	saver.writeTextElement("id_start", QString::number(m_lines[i]->get_id_start()) );
	saver.writeTextElement("id_end", QString::number(m_lines[i]->get_id_end()) );
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
	    reader.readNext();
	    m_diagram_type = reader.text().toString();
        }

        if ( reader.name() == "icon" )
        {
	    //qDebug() << reader.name();
	    icons.append(parse_icon(reader));
        }
        
        if ( reader.name() == "line" )
        {
	    //qDebug() << reader.name();
	    lines.append(parse_line(reader));
        }
        
    }
    }

    qDebug() << "returning icons";
    m_items = icons;
    m_lines = lines;
}

Icon * Xml_io::parse_icon(QXmlStreamReader &reader)
{
    int width = 0;
    int height = 0;
    int x_pos = 0;
    int y_pos = 0;
    QString label = "";
    QString type = "";

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
		qDebug() << width;
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
    else if ( type == "Rounded Square" )
    {
        ret = new RoundedSquare(0, width, height, x_pos, y_pos, label);
    }
    else if ( type == "Class Box" )
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


lineBody * Xml_io::parse_line(QXmlStreamReader &reader)
{
    int linetype = -1;
    int id_start = -1;
    int id_end = -1;

    // next element
    reader.readNext();

    while ( ! (reader.tokenType() == QXmlStreamReader::EndElement &&  reader.name() == "line") )
    {
	//read next element
	QXmlStreamReader::TokenType token = reader.readNext();

	if ( token == QXmlStreamReader::StartElement )
	{
	    if ( reader.name() == "linetype" )
	    {
		reader.readNext();
		linetype = reader.text().toString().toInt();
	    }

	    if ( reader.name() == "id_start" )
	    {
		reader.readNext();
		id_start = reader.text().toString().toInt();		
	    }

	    if ( reader.name() == "id_end" )
	    {
		reader.readNext();
		id_end = reader.text().toString().toInt();		
	    }
	}
    }

    return make_line(linetype, id_start, id_end);
}


lineBody * Xml_io::make_line(int linetype, int id_start, int id_end)
{
    lineBody *ret = NULL;

    if ( linetype == (LineType)Solid_Line )
    {
	ret = new solidline(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Line )
    {
	ret = new dottedline(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Line_SAH )
    {
	ret = new solidlineSAH(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Line_SAH )
    {
	ret = new dottedlineSAH(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Line_EAH )
    {
	ret = new solidlineeah(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Line_EAH )
    {
	ret = new dottedlineeah(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Line_SD )
    {
	ret = new solidlineSD(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Line_SD )
    {
	ret = new dottedlineSD(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Line_ED )
    {
	ret = new solidlineed(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Line_ED )
    {
	ret = new dottedlineed(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Line_BAH )
    {
	ret = new solidlineBAH(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Line_BAH )
    {
	ret = new dottedlinebah(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Square_Line )
    {
	ret = new solidsqline(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Square_Line )
    {
	ret = new dottedsqline(id_start, id_end);
    }
    if ( linetype == (LineType)Solid_Sq_Line_SAH )
    {
	ret = new solidsqlinesah(id_start, id_end);
    }
    if ( linetype == (LineType)Dotted_Sq_Line_SAH )
    {
	ret = new dottedsqlinesah(id_start, id_end);
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

    return ret;
}


