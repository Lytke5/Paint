#ifndef LINE_H
#define LINE_H
#include "graphobj.h"


class Line : public GraphObj
{
private:
    QPoint endPoint;
public:
    Line(QPoint startPoint_, QColor color_);
    Line(const Line &obj);
    Line& operator=(const Line &obj);
    ~Line();
    bool update(QPoint point) override;
    void paint(QPainter *painter, bool showBBox) override;
    bool tooSmall() override;
    bool isInside(QPoint point) override;
    void changeColor(QColor newColor) override;
    void reposition(QPoint point) override;
    void calcBBox(QPoint &min, QPoint &max) const override;
};

#endif // LINE_H
