#include <cmath>
#include "line.h"

Line::Line(QPoint startPoint_, QColor color_)
{
    startPoint = startPoint_;
    endPoint = startPoint_;
    color = color_;
}

Line::Line(const Line &obj)
{
    startPoint = obj.startPoint;
    endPoint = obj.endPoint;
    color = obj.color;
}

Line& Line::operator=(const Line &obj)
{
    if(this == &obj)
        return *this;

    startPoint = obj.startPoint;
    endPoint = obj.endPoint;
    color = obj.color;

    return *this;
}

Line::~Line()
{

}

bool Line::update(QPoint point)
{
    endPoint = point;
    return true;
}

void Line::paint(QPainter *painter, bool showBBox)
{
    painter->setPen(QPen(color, 2));
    painter->drawLine(startPoint, endPoint);

    if(showBBox)
    {
        QPoint min, max;

        QPen dashedPen(Qt::red);
        dashedPen.setStyle(Qt::DashLine);
        painter->setPen(dashedPen);
        painter->setBrush(Qt::NoBrush);

        calcBBox(min, max);

        int width = max.x() - min.x();
        int height = max.y() - min.y();

        painter->drawRect(min.x(), min.y(), width, height);
    }
}

bool Line::tooSmall()
{
    float c2 = pow(endPoint.toPointF().x()-startPoint.toPointF().x(),2) +
               pow(endPoint.toPointF().y()-startPoint.toPointF().y(),2);

    if(c2 < 2)
        return true;

    return false;
}

bool Line::isInside(QPoint point)
{
    QPoint vectorU(endPoint.x()-startPoint.x(),endPoint.y()-startPoint.y());
    QPoint vector1(point.x() - startPoint.x(), point.y() - startPoint.y());
    int numerator = vector1.x()*vectorU.y() - vector1.y()*vectorU.x();
    int denominator = sqrt(vectorU.x() * vectorU.x() + vectorU.y() * vectorU.y());


    int distance = numerator / denominator;

    if(distance < 0)
        distance *= -1;

    if(distance < 30)
        return true;

    return false;

}

void Line::changeColor(QColor newColor)
{
    color = newColor;
}

void Line::reposition(QPoint point)
{
    startPoint += point;
    endPoint += point;
}

void Line::calcBBox(QPoint &min, QPoint &max) const
{
    min = startPoint;
    max = endPoint;
}

