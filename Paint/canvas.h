#ifndef CANVAS_H
#define CANVAS_H

#include <QFrame>
#include <vector>
#include "Scene.h"

class Canvas : public QFrame
{
    Q_OBJECT

public:
    enum PrimitiveMode {
        NONE, FREE_HAND, CIRCLE, LINE, TRIANGLE, RECTANGLE, POLYGON
    };

    enum InteractionMode {
        CREAT, DEL, COL, TRAFO
    };

    Canvas(QWidget *parent = 0);
    Canvas(const Canvas &canvas);
    Canvas& operator=(const Canvas &canvas);
    ~Canvas();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void clearCanvas(void);
    void setPrimitiveMode(int mode);
    void setInteractionMode(int mode);
    void setCurrColor(QColor color);
    void setFillMode(bool outline);
    void setShowBBox(bool show);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void createObj(QMouseEvent *event);
    void deleteObj(QMouseEvent *event);
    void changeColorObj(QMouseEvent *event);
    void moveObj(QMouseEvent *event);

private:
    bool dragging;
    bool isOutlined = false;
    bool usingPolygon = false;
    bool showBBox = false;
    PrimitiveMode primitiveMode;
    InteractionMode interactionMode;
    QPoint lastPos;
    GraphObj* currObj;
    QColor currColor;
    Scene myScene;

};

#endif // CANVAS_H
