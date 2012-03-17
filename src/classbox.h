/* classbox.h
 * ClassBox
 * 3 QGraphicsTextItems for the class name, class members and class methods
 * CURRENTLY:
 *  all text boxes hold default text (set in the constructor)
 *  class boxes can only be moved reliably by dragging the top left corner.
 */
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
