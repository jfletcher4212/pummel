#ifndef SOLIDLINESAH_H
#define SOLIDLINESAH_H
#include "solidline.h"
#include "filledah.h"

class solidlineSAH
{
public:
    solidlineSAH(QGraphicsItem *, QGraphicsScene *);
private:
protected:
    void painter(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif // SOLIDLINESAH_H
