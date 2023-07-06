#include "scene.h"

#include <iostream>

Scene::Scene()
{

}

void Scene::addObj(GraphObj* Obj)
{
    allShapes.push_back(Obj);
}

void Scene::display(QPainter *painter, bool showBBox)
{
    for(GraphObj *obj : allShapes)
    {
        obj->paint(painter, showBBox);
    }
}

void Scene::deleteObj(QPoint point)
{
    for(int i = 0; i < allShapes.size(); i++)
    {
        if(allShapes[i]->isInside(point))
        {
            GraphObj *obj = allShapes[i];
            allShapes.erase(allShapes.begin()+i);
            delete obj;
            return;
        }
    }
}

void Scene::ChangeColorObj(QPoint point, QColor color)
{
    for(int i = 0; i < allShapes.size(); i++)
    {
        if(allShapes[i]->isInside(point))
        {
            allShapes[i]->changeColor(color);
            return;
        }
    }
}

GraphObj* Scene::getClickedObj(QPoint point)
{
    for(int i = 0; i < allShapes.size(); i++)
    {
        if(allShapes[i]->isInside(point))
        {
            return allShapes[i];
        }
    }
}

void Scene::deleteIfTooSmall()
{
    GraphObj* obj = allShapes.back();

    if(obj->tooSmall())
    {
        allShapes.pop_back();
        delete obj;
    }
}

bool Scene::empty()
{
    return allShapes.empty();
}

GraphObj* Scene::getLastObj()
{
    return allShapes.back();
}

void Scene::clear()
{
    for(GraphObj* obj : allShapes)
    {
        delete obj;
    }
    allShapes.clear();
}
