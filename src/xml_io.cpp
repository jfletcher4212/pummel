
#include "xml_io.h"
#include <QString>

//using namespace std;


Xml_io::Xml_io()
{
  //m_items = NULL;
  
  //m_filename = "";
  //  m_diagram_type = "";
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
    
    for ( int i = 0; i < m_items.length()-1; i++ )
    {
	//QString valueAsString = QString::number(valueAsDouble);
	// wrapper tags coule be the object's individual ID #
	saver.writeStartElement("icon");
	saver.writeTextElement("width", QString::number(m_items[i]->getWidth()));
	saver.writeTextElement("height", QString::number(m_items[i]->getHeight()));
	saver.writeTextElement("id", QString::number(m_items[i]->getID()));
	saver.writeTextElement("label", m_items[i]->getLabel());
	saver.writeTextElement("shapetype", m_items[i]->reportShapetype());
	saver.writeEndElement();
    }
    
    saver.writeEndDocument();
    saver.setAutoFormatting(true);
    savefile.close();
}


void Xml_io::openFile()
{
    /*
    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.xml" );
    newTab();
    
    QFile infile ( filename );
    infile.open(QIODevice::ReadOnly);

    // strip full path off filename for display
    int idx = filename.lastIndexOf("/");
    filename.remove(0, idx+1);
    
    tabWidget->setTabText(tabWidget->currentIndex(), filename);
    
    QXmlStreamReader reader(&infile);
    // what is this doing???
    QList< QMap<QString,QString> > icons;
    
    while ( !reader.atEnd() && !reader.hasError() )
    {
	//read next element
	QXmlStreamReader::TokenType token = xml.readNext();
	
	if ( token == QXmlStreamReader::StartDocument )
	{
	    continue;
	}
	
	if ( token == QXmlStreamReader::StartElement )
	{
	    if ( reader.name() == filename )
	    {
		continue;
	    }
	    
	    if ( reader.name() == "coord" )
	    {
		icons.append(parse_icon(reader));
	    }
	    
	    }
    }
    
    // icons should have everything we need at this point
    
    //cout<<reader.readElementText(1)<endl;
    cout<<"HERE"<<endl;
    //cout<<reader.readElementText().toStdString()<<endl;
    reader.readNextStartElement();
    cout<<reader.readElementText(QXmlStreamReader::IncludeChildElements).toStdString()<<endl;*/
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
