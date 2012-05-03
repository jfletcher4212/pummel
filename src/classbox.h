/* classbox.h
 * ClassBox
 * 3 QGraphicsTextItems for the class name, class members and class methods
 * TO-DO:   Modify double-click behavior so that the object doesn't move immediately when clicked
 */
//
#ifndef CLASSBOX_H
#define CLASSBOX_H

#include <QWidget>
#include <QGraphicsItem>
#include <QtGui>
#include <iostream>
#include "icon.h"

class ClassBox : public Icon
{
private:
    QGraphicsTextItem *m_memberBox, *m_methodBox;
    int m_titleBorder, m_memberBorder, m_methodBorder;
    QString m_members, m_methods;
    void setRect();
    void arrangeBoxes();
    QFont m_lfont;

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

public:
    ClassBox();
    ClassBox(QGraphicsItem *parent, int id, int xsize, int ysize, int xpos, int ypos, QString members);
    ~ClassBox();
    QString getLabel(), getMembers(), getMethods();
    QRectF boundingRect() const;
    void setLabel(QString), setMembers(QString), setMethods(QString);
    int setWidthsManually(int labelWidth, int memberWidth, int methodWidth);
    
    // file i/o accessors
    QString get_all();
    QStringList split_all(QString value);
};

#endif // CLASSBOX_H
