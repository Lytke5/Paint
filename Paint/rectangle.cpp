#include "rectangle.h"


Rectangle::Rectangle(QPoint startPoint_, QColor color_, bool outlined_)
{
    startPoint = startPoint_;
    endPoint = startPoint_;
    color = color_;
    outlined = outlined_;
}

Rectangle::Rectangle(const Rectangle &obj)
{
    startPoint = obj.startPoint;
    endPoint = obj.endPoint;
    color = obj.color;
    outlined = obj.outlined;
}

Rectangle& Rectangle::operator=(const Rectangle &obj)
{
    if(this == &obj)
        return *this;

    startPoint = obj.startPoint;
    endPoint = obj.endPoint;
    color = obj.color;
    outlined = obj.outlined;

    return *this;
}

Rectangle::~Rectangle()
{

}

bool Rectangle::update(QPoint point)
{
    endPoint = point;
    return true;
}

void Rectangle::paint(QPainter *painter, bool showBBox)
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

    int width = endPoint.x() - startPoint.x();
    int height = endPoint.y() - startPoint.y();

    painter->drawRect(startPoint.x(), startPoint.y(), width, height);

    if(showBBox)
    {
        QPen dashedPen(Qt::red);
        dashedPen.setStyle(Qt::DashLine);
        painter->setPen(dashedPen);
        painter->setBrush(Qt::NoBrush);

        painter->drawRect(startPoint.x(), startPoint.y(), width, height);
    }
}

bool Rectangle::tooSmall()
{
    float c2 = endPoint.toPointF().x()-startPoint.toPointF().x() *
                                             endPoint.toPointF().y()-startPoint.toPointF().y();

    if(c2 < 0)
        c2 *= -1;

    if(c2 < 2)
        return true;

    return false;
}

bool Rectangle::isInside(QPoint point)
{
    int xMin, xMax, yMin, yMax;
    if(startPoint.x() < endPoint.x())
    {
        xMin = startPoint.x();
        xMax = endPoint.x();
    }
    else
    {
        xMin = endPoint.x();
        xMax = startPoint.x();
    }

    if(startPoint.y() < endPoint.y())
    {
        yMin = startPoint.y();
        yMax = endPoint.y();
    }
    else
    {
        yMin = endPoint.y();
        yMax = startPoint.y();
    }


    return xMin <= point.x() && yMin <= point.y() &&
           point.x() <= xMax && point.y() <= yMax;
}

void Rectangle::changeColor(QColor newColor)
{
    color = newColor;
}

void Rectangle::reposition(QPoint point)
{
    startPoint += point;
    endPoint += point;
}

void Rectangle::calcBBox(QPoint &min, QPoint &max) const
{
    //nichts
}
