#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <math.h>
#include "canvas.h"
#include "graphobj.h"
#include "line.h"
#include "rectangle.h"
#include "circle.h"
#include "freehand.h"
#include "polygon.h"
#include "bboxdecorator.h"


Canvas::Canvas(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Box);
    setMouseTracking(true);

    primitiveMode = NONE;
    dragging = false;
}

Canvas::Canvas(const Canvas &canvas)
{
    dragging = canvas.dragging;
    isOutlined = canvas.isOutlined;
    primitiveMode = canvas.primitiveMode;
    currColor = canvas.currColor;
    myScene = canvas.myScene;
}

Canvas& Canvas::operator=(const Canvas &canvas)
{
    dragging = canvas.dragging;
    isOutlined = canvas.isOutlined;
    primitiveMode = canvas.primitiveMode;
    currColor = canvas.currColor;
    myScene = canvas.myScene;

    return *this;
}

Canvas::~Canvas()
{
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize Canvas::sizeHint() const
{
    return QSize(640, 480);
}

void Canvas::clearCanvas(void)
{
    myScene.clear();
}

void Canvas::setPrimitiveMode(int mode)
{
    primitiveMode = (Canvas::PrimitiveMode)mode;
}

void Canvas::setInteractionMode(int mode)
{
    interactionMode = (Canvas::InteractionMode)mode;
}

void Canvas::setCurrColor(QColor color)
{
    currColor = color;
}

void Canvas::setFillMode(bool outline)
{
    isOutlined = outline;
}

void Canvas::setShowBBox(bool show)
{
    showBBox = show;
    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);  // parent class draws border

    QPainter painter(this);

    // white background (inside parent's border)
    painter.fillRect(QRect(1, 1, width() - 2, height() - 2), Qt::white);

    myScene.display(&painter, showBBox);
}

void Canvas::resizeEvent(QResizeEvent *event) 
{
    QFrame::resizeEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(primitiveMode == NONE)
    {
        return;
    }

    switch(interactionMode)
    {
    case CREAT:
        createObj(event);
        break;

    case DEL:
        deleteObj(event);
        break;

    case COL:
        changeColorObj(event);
        break;

    case TRAFO:
    {
        QPoint currPos = event->pos();
        currObj = myScene.getClickedObj(currPos);
        lastPos = currPos;
        dragging = true;
        break;
    }

    default:
        break;
    }

    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currPos = event->pos();

    if(interactionMode == TRAFO && (event->buttons() & Qt::LeftButton) && dragging)
    {
        moveObj(event);
        update();
    }

    else if(usingPolygon)
    {
        return;
    }

    else if ((event->buttons() & Qt::LeftButton) && dragging)
    {
        GraphObj *obj = myScene.getLastObj();
        obj->update(currPos);

        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging) {
        dragging = false;

        if(!usingPolygon)
            myScene.deleteIfTooSmall();

        update();
    }
}

void Canvas::createObj(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;

        // Mouse position given as follows
        QPoint currPos = event->pos();

        switch (primitiveMode) {
        case LINE:
        {
            BBoxDecorator *newObj = new BBoxDecorator(new Line(currPos, currColor));
            myScene.addObj(newObj);
            break;
        }
        case RECTANGLE:
        {
            BBoxDecorator *newObj = new BBoxDecorator(new Rectangle(currPos, currColor, isOutlined));

            myScene.addObj(newObj);
            break;
        }
        case CIRCLE:
        {
            BBoxDecorator *newObj = new BBoxDecorator(new Circle(currPos, currColor, isOutlined));
            myScene.addObj(newObj);
            break;
        }
        case FREE_HAND:
        {
            BBoxDecorator *newObj = new BBoxDecorator(new FreeHand(currPos, currColor));
            myScene.addObj(newObj);
            break;
        }
        case POLYGON:
        {
            if(usingPolygon && !myScene.empty())
            {
                GraphObj *obj = myScene.getLastObj();
                if(obj->update(currPos) == true)
                    usingPolygon = false;
            }
            else
            {
                BBoxDecorator *newObj = new BBoxDecorator(new Polygon(currPos, currColor, isOutlined));
                myScene.addObj(newObj);
                usingPolygon = true;
            }
            break;
        }
        default:
            break;
        }
    }
}

void Canvas::deleteObj(QMouseEvent *event)
{
    QPoint currPos = event->pos();
    myScene.deleteObj(currPos);
}

void Canvas::changeColorObj(QMouseEvent *event)
{
    QPoint currPos = event->pos();
    myScene.ChangeColorObj(currPos, currColor);
}

void Canvas::moveObj(QMouseEvent *event)
{
    QPoint currPos = event->pos();
    currObj->reposition(currPos-lastPos);
    lastPos = currPos;
}
