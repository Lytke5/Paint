#include <cmath>
#include "freehand.h"

#include <iostream>

FreeHand::FreeHand(QPoint startPoint_, QColor color_)
{
    points[0] = startPoint_;
    color = color_;
}

FreeHand::FreeHand(const FreeHand &obj)
{
    startPoint = obj.startPoint;
    color = obj.color;
    index = obj.index;

    for(int i = 0; i < LIMIT; i++)
    {
        points[i] = obj.points[i];
    }
}

FreeHand& FreeHand::operator=(const FreeHand &obj)
{
    if(this == &obj)
        return *this;

    startPoint = obj.startPoint;
    color = obj.color;
    index = obj.index;

    for(int i = 0; i < LIMIT; i++)
    {
        points[i] = obj.points[i];
    }

    return *this;
}

FreeHand::~FreeHand()
{

}

bool FreeHand::update(QPoint point)
{
    if(index <= LIMIT)
        points[++index] = point;
    return true;
}

void FreeHand::paint(QPainter *painter, bool showBBox)
{
    painter->setPen(QPen(color, 2));
    painter->drawPolyline(points, index);

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

bool FreeHand::tooSmall()
{
    int distance = 0;
    for(int i  = 1; i <= index; i++)
    {
        float c2 = pow(points[i].toPointF().x()-points[i-1].toPointF().x(),2) +
                   pow(points[i].toPointF().y()-points[i-1].toPointF().y(),2);

        distance += sqrt(c2);

        if(distance > 2)
            return false;
    }

    return true;
}

bool FreeHand::isInside(QPoint point)
{
    int distance = 0;
    for(int i  = 0; i <= index; i++)
    {
        int c2 = pow(points[i].x()-point.x(),2) +
                   pow(points[i].y()-point.y(),2);

        distance = sqrt(c2);

        if(distance <= 30)
            return true;
    }

    return false;
}

void FreeHand::changeColor(QColor newColor)
{
    color = newColor;
}

void FreeHand::reposition(QPoint point)
{
    for(int i  = 0; i < index; i++)
    {
        points[i] += point;
    }
}

void FreeHand::calcBBox(QPoint &min, QPoint &max) const
{
    min = max = points[0];

    for(int i = 1; i < index; i++)
    {
        if(points[i].x() < min.x())
        {
            QPoint *tempMin = new QPoint(points[i].x(),min.y());
            min = *tempMin;
            delete tempMin;
        }

        if(points[i].y() < min.y())
        {
            QPoint *tempMin = new QPoint(min.x(),points[i].y());
            min = *tempMin;
            delete tempMin;
        }

        if(points[i].x() > max.x())
        {
            QPoint *tempMax = new QPoint(points[i].x(),max.y());
            max = *tempMax;
            delete tempMax;
        }

        if(points[i].y() > max.y())
        {
            QPoint *tempMax = new QPoint(max.x(),points[i].y());
            max = *tempMax;
            delete tempMax;
        }
    }
}

