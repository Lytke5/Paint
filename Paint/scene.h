#ifndef SCENE_H
#define SCENE_H
#include <QPainter>
#include "GraphObj.h"


class Scene
{
private:
    std::vector <GraphObj*> allShapes;
public:
    Scene();
    void addObj(GraphObj* Obj);
    void display(QPainter *painter, bool showBBox);
    void deleteObj(QPoint point);
    void ChangeColorObj(QPoint point, QColor color);
    GraphObj* getClickedObj(QPoint point);
    void deleteIfTooSmall();
    bool empty();
    GraphObj* getLastObj();
    void clear();
};

#endif // SCENE_H
