
/*
  Jason Fletcher

  Goal: create the methods by which all of the
  current file's objects will be saved, primarily
  in an XML format, and eventually image files (ex. png)
  or latex/pdf format

  Current status: a basic framework for saving into and loading from XML
  exists, though it was based on early designs before
  some parts of the project were revised, and as such is
  incompatible with the rest of the project and in need of
  changes. Saving and loading were de-prioritized shortly after
  Thanksgiving break, with the idea that the object structure
  should be finalized and implemented first.

void MainWindow::save()
{
    QString filename;

    Object *temp;
    temp = DrawArea.head;
    //likely to change...not sure exactly how it will call the head of the list
    filename = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath(), "*.xml");
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "<UMLFILE>\n";
    while(temp != NULL)
    {
        saveObject( out, temp );
        temp = temp->next;
    }
    out << "</UMLFILE>\n";
    file.close();
}
void saveObject( QTextStream out, Object *temp )
{
    //text box
    if(temp->type == "TextBox")
    {
        storeObject(out, temp->size, temp->x, temp->y );
        storeText(out, temp->font, temp->usertext, temp->ShapeID);
    }
    //basic shape
    if(temp->type == "Ellipse" || temp->type == "Rect" || temp->type == "Triangle")
    {
        out << "<" << type << ">\n";
        storeObject(out, temp->size, temp->x, temp->y );
        int rvalue = temp->color.rvalue;
        int gvalue = temp->color.gvalue;
        int bvalue = temp->color.bvalue;
        int avalue = temp->color.avalue;
        storeColor(out, rvalue, gvalue, bvalue, avalue );
        store(out, "linewidth", temp->linewidth);
        out << "</" << label << ">\n";
    }
    //more complex shapes separated in case they have special requirements
    if(temp->type == "Pill" || temp->type == "Polygon" || temp->type == "Actor")
    {
        out << "<" << type << ">\n";
        storeObject(out, size, x, y );
        int rvalue = temp->color.rvalue;
        int gvalue = temp->color.gvalue;
        int bvalue = temp->color.bvalue;
        int avalue = temp->color.avalue;
        storeColor(out, rvalue, gvalue, bvalue, avalue );
        store(in, "linewidth", temp->linewidth);
        out << "</" << label << ">\n";
    }
    //"line" family
    if(temp->type == "Line" || temp->type == "Arc" || temp->type == "Arrow" || temp->type == "DiamondLine")
    {
        out << "<" << type << ">\n";
        storeObject(out,  size, x, y );
        int rvalue = temp->color.rvalue;
        int gvalue = temp->color.gvalue;
        int bvalue = temp->color.bvalue;
        int avalue = temp->color.avalue;
        storeColor(out, rvalue, gvalue, bvalue, avalue );
        store(out, "linewidth", temp->linewidth);
        out << "</" << label << ">\n";
    }
}
void MainWindow::open()
{
    QString buffer;
 //   int errorCode = 0;
    QString filename;
    //DrawArea.deleteAllObjects()?
    Object *temp = NULL;
    filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.xml" );
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly ))
    {
        QTextStream in(&file);
        in >> buffer;
        if( buffer.compare("<UMLFILE>") == 0)
        {
            in >> buffer;
            while( buffer.compare("</UMLFILE>") != 0 )
            {
                analyzeFile(in, temp, buffer);
                //addToList( temp );
                in >> buffer;
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Failed: File is not in the correct format.");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Failed File Open.");
        msgBox.exec();
    }
}
// reading an int/QString value in from the XML file and returning it
int getVal(QTextStream in)
{
    QString buffer;
    Qstring discard;
    in >> buffer; //<tag>
    in >> buffer; //value
    in >> discard; //</tag>
    return buffer.toInt();
}
QString getVal(QTextStream in)
{
    QString buffer;
    Qstring discard;
    in >> buffer; //<tag>
    in >> buffer; //value
    in >> discard; //</tag>
    return buffer;
}
void analyzeFile( QTextStream in, Object *temp, QString buffer )
{
    QString discard;
    switch( buffer )
    {
    case "<TextBox>" :
        int test;
        QString Stest;
        test = getVal( in ); //<size>
        if( test > 0 )
        {
            temp->size = test;
        }

        test = getVal( in ); //<x>
        if( test > 0)
        {
            temp->x = test;
        }

        test = getVal( in ); //<y>
        if( test > 0)
        {
            temp->y = test;
        }

        temp->font = getVal( in ); //<font>

        temp->usertext = in.getline(0);
        in >> buffer; //next line to be read will be the next object's tag

        break;

    case "<Ellipse>" :
        test = getVal( in );
        if( test > 0 )
        {
            temp->size = test;
        }

        test = getVal( in ); //<x>
        if( test > 0)
        {
            temp->x = test;
        }

        test = getVal( in ); //<y>
        if( test > 0)
        {
            temp->y = test;
        }
        test = getVal( in ); //<rvalue>
        if( test > 0)
        {
            temp->rvalue = test;
        }
        test = getVal( in ); //<gvalue>
        if( test > 0)
        {
            temp->gvalue = test;
        }
        test = getVal( in ); //<bvalue>
        if( test > 0)
        {
            temp->bvalue = test;
        }
        test = getVal( in ); //<avalue>
        if( test > 0)
        {
            temp->avalue = test;
        }
        test = getVal( in ); //<linewidth>
        if( test > 0)
        {
            temp->linewidth = test;
        }
        break;
    case "<Pill>" :
        //basically the same as 'Ellipse,
        //not copying to save space, as well as
        //because a function could be written to do the same
        //readInVals( in, temp );?

        break;
    case "<Triangle>" :
        //see <Pill> above

        break;
    case "<Rect>" :
        //see <Pill> above

        break;
    case "<Polygon>" :
        //see <Pill> above

        break;
    case "<Actor>" :
        //same as <Polygon> above

        break;
    case "<Line>" :
        //see <Pill> above

        break;
    case "<Arc>" :
        //see <Pill> above

        break;
    case "<Arrow>" :
        //see <Pill> above

        break;
    case "<DiamondLine>" :
        //see <Pill> above

        break;
    default :
        //error handling, checking for proper format
        break;

    }

}

void store(QTextStream out, QString tag, QString value)
{
    out << "<" << tag << ">\n";
    out << value << "\n";
    out << "</" << tag << ">\n";
}
void store(QTextStream out, QString tag, int value)
{
    out << "<" << tag << ">\n";
    out << value << "\n";
    out << "</" << tag << ">\n";
}
void storeObject(QTextStream out, int size, int x, int y)
{
    store(out, "size", size);
    store(out, "x", x);
    store(out, "y", y);
}
void storeColor( QTextStream out, int rvalue, int gvalue, int bvalue, int avalue)
{
    store(out, "rvalue", rvalue);
    store(out, "gvalue", gvalue);
    store(out, "bvalue", bvalue);
    store(out, "avalue", avalue);
}
void storeText( QTextStream out, Qstring font, QString text, int ShapeID, )
{
    store(out, "font", font );
    store(out, "text", text);
    store(out, "ShapeID", ShapeID);
}
*/
