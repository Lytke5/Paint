#include "polygon.h"

Polygon::Polygon(QPoint startPoint_, QColor color_, bool outlined_) : points(*(new QList<QPoint>()))
{
    startPoint = startPoint_;
    points.push_back(startPoint);
    color = color_;
    outlined = outlined_;
}

Polygon::Polygon(const Polygon &obj) : points(obj.points)
{
    startPoint = obj.startPoint;
    color = obj.color;
    outlined = obj.outlined;

    for(int i = 0; i < points.size(); i++)
    {
        points[i] = obj.points[i];
    }
}

Polygon& Polygon::operator=(const Polygon &obj)
{
    if(this == &obj)
        return *this;

    startPoint = obj.startPoint;
    color = obj.color;
    outlined = obj.outlined;
    for(int i = 0; i < points.size(); i++)
    {
        points[i] = obj.points[i];
    }

    return *this;
}

Polygon::~Polygon()
{
    delete &points;
}

bool Polygon::update(QPoint point)
{
    int distanceX = point.x() - startPoint.x();
    int distanceY = point.y() - startPoint.y();

    if(((distanceX < 50 && distanceX > 0) || (distanceX > -50 && distanceX < 0)) &&
        ((distanceY < 50 && distanceY > 0) || (distanceY > -50 && distanceY < 0)))
    {
        points.push_back(points.front());
        return true;
    }

    points.push_back(point);
    return false;
}

void Polygon::paint(QPainter *painter, bool showBBox)
{
    if(points.size() == 2)
    {
        painter->setPen(QPen(color, 2));
        painter->setBrush(Qt::NoBrush);
        painter->drawLine(startPoint, points[1]);
        return;
    }

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

        painter->drawPolygon(points);

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

bool Polygon::tooSmall()
{
    int distance = 0;
    for(int i  = 1; i <= points.size(); i++)
    {
        float c2 = pow(points[i].toPointF().x()-points[i-1].toPointF().x(),2) +
                   pow(points[i].toPointF().y()-points[i-1].toPointF().y(),2);

        distance += sqrt(c2);

        if(distance > 2)
            return false;
    }

    return true;
}

bool Polygon::isInside(QPoint point)
{
    int numIntersections = 0;
    int numVertices = points.size();

    for (int i = 0, j = numVertices - 1; i < numVertices; j = i++)
    {
        if (((points[i].y() > point.y()) != (points[j].y() > point.y())) &&
            (point.x() < (points[j].x() - points[i].x()) * (point.y() - points[i].y()) / (points[j].y() - points[i].y()) + points[i].x()))
        {
            numIntersections++;
        }
    }

    return (numIntersections % 2 == 1);
}

void Polygon::changeColor(QColor newColor)
{
    color = newColor;
}

void Polygon::reposition(QPoint point)
{
    for(int i  = 0; i < points.size(); i++)
    {
        points[i] += point;
    }
}

void Polygon::calcBBox(QPoint &min, QPoint &max) const
{
    min = max = points[0];

    for(int i = 1; i < points.size(); i++)
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
