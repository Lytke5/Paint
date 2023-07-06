#ifndef FREEHAND_H
#define FREEHAND_H
#include "graphobj.h"

class FreeHand : public GraphObj
{
private:
    const int LIMIT = 3000;
    QPoint points[3000];
    int index = 0;
public:
    FreeHand(QPoint startPoint_, QColor color_);
    FreeHand(const FreeHand &obj);
    FreeHand& operator=(const FreeHand &obj);
    ~FreeHand();
    bool update(QPoint point) override;
    void paint(QPainter *painter, bool showBBox) override;
    bool tooSmall() override;
    bool isInside(QPoint point) override;
    void changeColor(QColor newColor) override;
    void reposition(QPoint point) override;
    void calcBBox(QPoint &min, QPoint &max) const override;
};

#endif // FREEHAND_H
