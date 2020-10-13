#include "midellipse.h"
#include <cmath>

void MidEllipse::drawEllipse(QPainter *g, int xc,int yc, int rx, int ry, QColor bound=Qt::blue, QColor fill=Qt::yellow){

    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry)
            - (rx * rx * ry)
            + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1 void midptellipse(int rx, int ry, int xc, int yc)
    //{
    while (dx < dy) {

        // Print points based on 4-way symmetry
        //        printf("(%f, %f)\n", x + xc, y + yc);
        //        printf("(%f, %f)\n", -x + xc, y + yc);
        //        printf("(%f, %f)\n", x + xc, -y + yc);
        //        printf("(%f, %f)\n", -x + xc, -y + yc);
        for(int yy=-y+1;yy<y;yy++){
            plot(g,x+xc,yy+yc,fill);
            plot(g,-x+xc,yy+yc,fill);
        }

        plot(g,x+xc,y+yc,bound);
        plot(g,-x+xc,y+yc,bound);
        plot(g,x+xc,-y+yc,bound);
        plot(g,-x+xc,-y+yc,bound);

        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
            + ((rx * rx) * ((y - 1) * (y - 1)))
            - (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0) {

        // printing points based on 4-way symmetry
        //        printf("(%f, %f)\n", x + xc, y + yc);
        //        printf("(%f, %f)\n", -x + xc, y + yc);
        //        printf("(%f, %f)\n", x + xc, -y + yc);
        //        printf("(%f, %f)\n", -x + xc, -y + yc);
        for(int xx=-x+1;xx<x;xx++){
            plot(g,xx+xc,y+yc,fill);
            plot(g,xx+xc,-y+yc,fill);
        }

        plot(g,x+xc,y+yc,bound);
        plot(g,-x+xc,y+yc,bound);
        plot(g,x+xc,-y+yc,bound);
        plot(g,-x+xc,-y+yc,bound);


        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}


void MidEllipse::paint(QPainter *g){
    int x1=0,y1=0,rx=25,ry=15,z;
    QColor bound=Qt::blue;
    QColor fill=Qt::yellow;
    drawEllipse(g,x1,y1,rx,ry,bound,fill);

}

void MidEllipse::PlotEllipse(QPainter *g,int cx, int cy, int xx, int yy){
    plot(g,cx+xx,cy+yy,Qt::blue);
    plot(g,cx-xx,cy+yy,Qt::blue);
    plot(g,cx+xx,cy-yy,Qt::blue);
    plot(g,cx-xx,cy-yy,Qt::blue);
}


