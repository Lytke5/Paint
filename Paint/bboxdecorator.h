#ifndef BBOXDECORATOR_H
#define BBOXDECORATOR_H

#include "graphobj.h"


class BBoxDecorator : public GraphObj
{
private:
    GraphObj* myGraphObj;
public:
    BBoxDecorator(GraphObj*);
    bool update(QPoint point);
    void paint(QPainter *painter, bool showBBox);
    bool tooSmall();
    bool isInside(QPoint point);
    void changeColor(QColor newColor);
    void reposition(QPoint point);
    void calcBBox(QPoint &min, QPoint &max) const;
    ~BBoxDecorator();
};

#endif // BBOXDECORATOR_H
