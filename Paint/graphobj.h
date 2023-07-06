#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H
#include <QPainter>


class GraphObj
{
protected:
    QPoint startPoint;    
    QColor color;
public:
    GraphObj();
    bool virtual update(QPoint point) = 0;
    void virtual paint(QPainter *painter, bool showBBox) = 0;
    bool virtual tooSmall() = 0;
    bool virtual isInside(QPoint point) = 0;
    void virtual changeColor(QColor newColor) = 0;
    void virtual reposition(QPoint point) = 0;
    void virtual calcBBox(QPoint &min, QPoint &max) const = 0;
    virtual ~GraphObj();
};

#endif // GRAPHOBJ_H
