/* roundedsquare.h
 * RoundedSquare
 * 3 QGraphicsTextItems for the collaboration name, methods
 */
#ifndef ROUNDEDSQUARE_H
#define ROUNDEDSQUARE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QtGui>
#include <iostream>
#include "icon.h"

class RoundedSquare : public Icon
{
private:
    QGraphicsTextItem *m_memberBox;
    int m_titleBorder, m_memberBorder;
    QString m_members;
    void setRect();
    void arrangeBoxes();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *);
    void setValues();

public:
    RoundedSquare(QGraphicsItem *parent = 0);
    RoundedSquare(QGraphicsItem *parent, int xsize, int ysize, int xpos, int ypos, QString members);
    ~RoundedSquare();
    QString getLabel(), getMembers();
    void setLabel(QString), setMembers(QString);
    
    // file i/o accessors
    QString get_all();
    QStringList split_all(QString value);
};

#endif // ROUNDEDSQUARE_H
