#ifndef MIDELLIPSE_H
#define MIDELLIPSE_H
#include "dda.h"

class MidEllipse:public DDA
{
public:
    MidEllipse() {}
    void virtual paint(QPainter *g);
    void drawEllipse(QPainter *g, int x1,int y1, int a, int b, QColor bound, QColor fill, bool q1, bool q2, bool q3, bool q4);
    void PlotEllipse(QPainter *g,int cx,int xy,int xx,int yy);
};

#endif // MIDELLIPSE_H
