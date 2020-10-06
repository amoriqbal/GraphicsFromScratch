#ifndef MIDCIRCLE_H
#define MIDCIRCLE_H
#include "dda.h"

class MidCircle:public DDA
{
public:
    MidCircle() {}
    void virtual paint(QPainter *g);
    void drawCircle(QPainter *g, int x1,int y1, int r, QColor bound, QColor fill);
};

#endif // MIDCIRCLE_H
