#include "midellipse.h"
#include <cmath>
using namespace std;
void MidEllipse::drawEllipse(QPainter *g, int xc,int yc, int rx, int ry, QColor bound=Qt::blue, QColor fill=Qt::yellow, bool q1=true,bool q2=true,bool q3=true,bool q4=true){

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
        for(int yy=(q3|q4?-y+1:1);yy<(q1|q2?y:0);yy++){
            plot(g,(q1|q4?x:0)+xc,yy+yc,fill);
            plot(g,(q2|q3?-x:0)+xc,yy+yc,fill);
        }

        if(q1) plot(g,x+xc,y+yc,bound);
        if(q2) plot(g,-x+xc,y+yc,bound);
        if(q4) plot(g,x+xc,-y+yc,bound);
        if(q3) plot(g,-x+xc,-y+yc,bound);


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
        for(int xx=(q2|q3?-x+1:1);xx<(q1|q4?x:0);xx++){
            plot(g,xx+xc,(q1|q2?y:0)+yc,fill);
            plot(g,xx+xc,(q3|q4?-y:0)+yc,fill);
        }

        if(q1) plot(g,x+xc,y+yc,bound);
        if(q2) plot(g,-x+xc,y+yc,bound);
        if(q4) plot(g,x+xc,-y+yc,bound);
        if(q3) plot(g,-x+xc,-y+yc,bound);


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

void MidEllipse::drawTiltedEllipse(QPainter* qp, int cx, int cy, int rx, int ry, double angle, QColor bound, QColor fill, int scalex, int scaley, bool q1, bool q2,bool q3, bool q4)
{
    pix.clear();
    angle=-angle;
    if(q1==true){
        for(uint i=0; i<90; ++i)
        {
            double pi=3.142;
            double x1, y1, x2, y2;
            x1 = cx + rx*cos((pi*i)/180)*cos(angle)*scalex + ry*sin((pi*i)/180)*sin(angle)*scalex;
            y1 = cy + ry*sin((pi*i)/180)*cos(angle)*scaley - rx*cos((pi*i)/180)*sin(angle)*scaley;
            x2 = cx + rx*cos((pi*(i+1))/180)*cos(angle)*scalex + ry*sin((pi*(i+1))/180)*sin(angle)*scalex;
            y2 = cy + ry*sin((pi*(i+1))/180)*cos(angle)*scaley - rx*cos((pi*(i+1))/180)*sin(angle)*scaley;
            midpoint(qp, round(x1), round(y1), round(x2), round(y2), bound);
        }
    }
    if(q2==true){
        for(uint i=90; i<180; ++i)
        {
            double pi=3.142;
            double x1, y1, x2, y2;
            x1 = cx + rx*cos((pi*i)/180)*cos(angle)*scalex + ry*sin((pi*i)/180)*sin(angle)*scalex;
            y1 = cy + ry*sin((pi*i)/180)*cos(angle)*scaley - rx*cos((pi*i)/180)*sin(angle)*scaley;
            x2 = cx + rx*cos((pi*(i+1))/180)*cos(angle)*scalex + ry*sin((pi*(i+1))/180)*sin(angle)*scalex;
            y2 = cy + ry*sin((pi*(i+1))/180)*cos(angle)*scaley - rx*cos((pi*(i+1))/180)*sin(angle)*scaley;
            midpoint(qp, round(x1), round(y1), round(x2), round(y2), bound);
        }
    }
    if(q3==true){
        for(uint i=180; i<270; ++i)
        {
            double pi=3.142;
            double x1, y1, x2, y2;
            x1 = cx + rx*cos((pi*i)/180)*cos(angle)*scalex + ry*sin((pi*i)/180)*sin(angle)*scalex;
            y1 = cy + ry*sin((pi*i)/180)*cos(angle)*scaley - rx*cos((pi*i)/180)*sin(angle)*scaley;
            x2 = cx + rx*cos((pi*(i+1))/180)*cos(angle)*scalex + ry*sin((pi*(i+1))/180)*sin(angle)*scalex;
            y2 = cy + ry*sin((pi*(i+1))/180)*cos(angle)*scaley - rx*cos((pi*(i+1))/180)*sin(angle)*scaley;
            midpoint(qp, round(x1), round(y1), round(x2), round(y2), bound);
        }
    }
    if(q4==true){
        for(uint i=270; i<360; ++i)
        {
            double pi=3.142;
            double x1, y1, x2, y2;
            x1 = cx + rx*cos((pi*i)/180)*cos(angle)*scalex + ry*sin((pi*i)/180)*sin(angle)*scalex;
            y1 = cy + ry*sin((pi*i)/180)*cos(angle)*scaley - rx*cos((pi*i)/180)*sin(angle)*scaley;
            x2 = cx + rx*cos((pi*(i+1))/180)*cos(angle)*scalex + ry*sin((pi*(i+1))/180)*sin(angle)*scalex;
            y2 = cy + ry*sin((pi*(i+1))/180)*cos(angle)*scaley - rx*cos((pi*(i+1))/180)*sin(angle)*scaley;
            midpoint(qp, round(x1), round(y1), round(x2), round(y2), bound);
        }
    }

    if(q1 and q2 and q3 and q4){
        boundaryFill(qp,cx,cy,fill);
    }
}
