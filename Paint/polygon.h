#ifndef POLYGON_H
#define POLYGON_H

#include "graphobj.h"


class Polygon : public GraphObj
{
private:
    QList<QPoint> &points;
    bool outlined;
public:
    Polygon(QPoint startPoint_, QColor color_, bool outlined_);
    Polygon(const Polygon &obj);
    Polygon& operator=(const Polygon &obj);
    ~Polygon();
    bool update(QPoint point) override;
    void paint(QPainter *painter, bool showBBox) override;
    bool tooSmall() override;
    bool isInside(QPoint point) override;
    void changeColor(QColor newColor) override;
    void reposition(QPoint point) override;
    void calcBBox(QPoint &min, QPoint &max) const override;
};

#endif // POLYGON_H
