#include "bboxdecorator.h"

BBoxDecorator::BBoxDecorator(GraphObj *Obj)
{
    myGraphObj = Obj;
}

bool BBoxDecorator::update(QPoint point)
{
    myGraphObj->update(point);
}

void BBoxDecorator::paint(QPainter *painter, bool showBBox)
{
    myGraphObj->paint(painter, showBBox);
}

bool BBoxDecorator::tooSmall()
{
    myGraphObj->tooSmall();
}

bool BBoxDecorator::isInside(QPoint point)
{
    myGraphObj->isInside(point);
}

void BBoxDecorator::changeColor(QColor newColor)
{
    myGraphObj->changeColor(newColor);
}

void BBoxDecorator::reposition(QPoint point)
{
    myGraphObj->reposition(point);
}

void BBoxDecorator::calcBBox(QPoint &min, QPoint &max)const
{
    myGraphObj->calcBBox(min, max);
}

BBoxDecorator::~BBoxDecorator()
{
    delete myGraphObj;
}
