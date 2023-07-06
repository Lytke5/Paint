#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "graphobj.h"


class Rectangle :public GraphObj
{
private:
    bool outlined;
    QPoint endPoint;
public:
    Rectangle(QPoint startPoint_, QColor color_, bool outlined_);
    Rectangle(const Rectangle &obj);
    Rectangle& operator=(const Rectangle &obj);
    ~Rectangle();
    bool update(QPoint point) override;
    void paint(QPainter *painter, bool showBBox) override;
    bool tooSmall() override;
    bool isInside(QPoint point) override;
    void changeColor(QColor newColor) override;
    void reposition(QPoint point) override;
    void calcBBox(QPoint &min, QPoint &max) const override;
};

#endif // RECTANGLE_H
