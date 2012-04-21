
#ifndef __XML_IO__
#define __XML_IO__

#include <QXmlStreamWriter>
#include "icon.h"

class Xml_io
{
  
 public:
    Xml_io();
    Xml_io( QList<Icon*> icon_list, QString filename/*, QString diagram_type*/ );
    ~Xml_io();
    
    void write_xml();
    void parse_xml();
    
    /* Access methods */
    QList<Icon*> get_items() { return m_items; }
    QString get_filename() { return m_filename; }
    //QString get_diagram_type() { return m_diagram_type; }
    
    /* mutator methods */
    void set_items(QList<Icon*> icon_list) { m_items = icon_list; }
    void set_filename(QString filename) { m_filename = filename; }
    //void set_diagram_type(QString diagram_type) { m_diagram_type = diagram_type; }  
    
 private:
    int m_size; 
    QString m_filename;
    //QString m_diagram_type;
    QList<Icon*> m_items;

    Icon * parse_icon(QXmlStreamReader &reader);
    Icon * make_icon(QString type, int width, int height, int x_pos, int y_pos, QString label);
};


#endif // __XML_IO__
