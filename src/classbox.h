/* classbox.h
 * ClassBox
 * 3 QGraphicsTextItems for the class name, class members and class methods
 * TO-DO:   Modify double-click behavior so that the object doesn't move immediately when clicked
 */
#ifndef CLASSBOX_H
#define CLASSBOX_H

#include <QWidget>
#include <QGraphicsItem>
#include <QtGui>
#include <iostream>
#include "icon.h"

class ClassBox : public icon
{
private:
    QGraphicsTextItem *m_memberBox, *m_methodBox;
    int m_titleBorder, m_memberBorder, m_methodBorder;
    int m_width, m_height;
    QString m_members, m_methods;
    void setRect();
    void arrangeBoxes();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

public:
    ClassBox();
    QString getLabel(), getMembers(), getMethods();
    void setLabel(QString), setMembers(QString), setMethods(QString);
};

#endif // CLASSBOX_H
