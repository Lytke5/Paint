#ifndef CIRCLE_H
#define CIRCLE_H
#include "graphobj.h"
#include <QDebug>

class Circle : public GraphObj
{
private:
    bool outlined;
    QPoint endPoint;
public:
    Circle(QPoint startPoint_, QColor color_, bool outlined_);
    Circle(const Circle &obj);
    Circle& operator=(const Circle &obj);
    ~Circle();
    bool update(QPoint point) override;
    void paint(QPainter *painter, bool showBBox) override;
    bool tooSmall() override;
    bool isInside(QPoint point) override;
    void changeColor(QColor newColor) override;
    void reposition(QPoint point) override;
    void calcBBox(QPoint &min, QPoint &max) const override;
};

#endif // CIRCLE_H
