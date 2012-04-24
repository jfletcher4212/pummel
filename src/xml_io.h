
#ifndef __XML_IO__
#define __XML_IO__

#include <QXmlStreamWriter>
#include "icon.h"
#include "global.h"

class Xml_io
{
  
 public:
    Xml_io(QString filename);
    Xml_io(QList<Icon*> icon_list, QList<lineBody*> line_list, QString filename, DiagramType diagram_type=(DiagramType)-1 );
    ~Xml_io();
    
    void write_xml();
    void parse_xml();
    
    QString choose_type(DiagramType d_type);
    
    /* Access methods */
    QList<Icon*> get_items() { return m_items; }
    QList<lineBody*> get_lines() { return m_lines; }
    QString get_filename() { return m_filename; }
    QString get_diagram_type() { return m_diagram_type; }
    
    /* mutator methods */
    void set_items(QList<Icon*> icon_list) { m_items = icon_list; }
    void set_lines(QList<lineBody*> line_list) { m_lines = line_list; }
    void set_filename(QString filename) { m_filename = filename; }
    void set_diagram_type(QString diagram_type) { m_diagram_type = diagram_type; }  
    
 private:
    int m_size; 
    QString m_filename;
    QString m_diagram_type;
    QList<Icon*> m_items;
    QList<lineBody*> m_lines;

    Icon * parse_icon(QXmlStreamReader &reader);
    Icon * make_icon(QString type, int width, int height, int x_pos, int y_pos, QString label);
};


#endif // __XML_IO__
