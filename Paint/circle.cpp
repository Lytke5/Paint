#include <cmath>
#include "circle.h"

#include <QDebug>

Circle::Circle(QPoint startPoint_, QColor color_, bool outlined_)
{
    startPoint = startPoint_;
    endPoint = startPoint_;
    color = color_;
    outlined = outlined_;
}

Circle::Circle(const Circle &obj)
{
    startPoint = obj.startPoint;
    endPoint = obj.endPoint;
    color = obj.color;
    outlined = obj.outlined;
}

Circle& Circle::operator=(const Circle &obj)
{
    if(this == &obj)
        return *this;

    startPoint = obj.startPoint;
    endPoint = obj.endPoint;
    color = obj.color;
    outlined = obj.outlined;

    return *this;
}

Circle::~Circle()
{

}

bool Circle::update(QPoint point)
{
    endPoint = point;
    return true;
}

void Circle::paint(QPainter *painter, bool showBBox)
{
    if (!outlined)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
    }
    else
    {
        painter->setPen(QPen(color, 2));
        painter->setBrush(Qt::NoBrush);
    }

    int radius = endPoint.x()-startPoint.x();
    painter->drawEllipse(startPoint, radius, radius);

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

bool Circle::tooSmall()
{
    float area = 4/3 * 3.1415 * endPoint.x()-startPoint.x() * endPoint.y()-startPoint.y();
    if(area < 0)
        area *= -1;

    if(area < 2)
        return true;

    return false;
}

bool Circle::isInside(QPoint point)
{
    int radius = endPoint.x()-startPoint.x();

    if(radius < 0)
        radius *= -1;

    int c2 = pow(startPoint.x()-point.x(),2) +
                   pow(startPoint.y()-point.y(),2);

    int distance = sqrt(c2);

    if(distance <= radius)
        return true;

    return false;
}

void Circle::changeColor(QColor newColor)
{
    color = newColor;
}

void Circle::reposition(QPoint point)
{
    startPoint += point;
    endPoint += point;
}

void Circle::calcBBox(QPoint &min, QPoint &max) const
{
    int radius = endPoint.x()-startPoint.x();

    QPoint *newMin = new QPoint(startPoint.x()-radius, startPoint.y()+radius);
    min = *newMin;

    QPoint *newMax = new QPoint(startPoint.x()+radius, startPoint.y()-radius);
    max = *newMax;

    delete newMin;
    delete newMax;
}
