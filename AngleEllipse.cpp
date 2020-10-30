#ifndef _ANGLE_ELLIPSE
#define _ANGLE_ELLIPSE

#include <QColor>
#include <array>
#include <vector>
#include <cmath>
#include "midellipse.h"
#define xrotate(x1,y1,angle) (x1 * cos(angle) - y1 * sin(angle))
#define yrotate(x1,y1,angle) (x1 * sin(angle) + y1 * cos(angle))

using namespace std;
//class AngleEllipse:public Drawable{
//    int a,b,cx,cy;
//    float angle;
//    bool q1,q2,q3,q4,bound,fill;
//    QColor bound_col, fill_col;
//    void draw(QPainter *g) {}

//};
class Drawable{
public:
    int cx,cy;
    MidEllipse *dda;

    Drawable(int _cx, int _cy, MidEllipse *d):cx(_cx),cy(_cy),dda(d){}
    virtual void draw(QPainter *g)=0;
    virtual void updateParams()=0;
};

class AngleBird:public Drawable{
public:
    float angle=0;
    int scalex=1,scaley=2,wingState=3;
    int speed=1;
    AngleBird(int _cx, int _cy, float _angle,MidEllipse *d):angle(_angle),Drawable(_cx,_cy,d){}

    void draw(QPainter *g){
        dda->pix.clear();
        drawTail(g,cx+xrotate(65,-8,angle)*scalex,cy+yrotate(65,-8,angle)*scaley,angle,Qt::black,Qt::red);
        dda->drawTiltedEllipse(g,cx+xrotate(18,0,angle)*scalex,cy+yrotate(18,0,angle)*scaley,8,8,angle,Qt::black,Qt::yellow,scalex,scaley);
        dda->drawTiltedEllipse(g,cx+xrotate(45,-11,angle)*scalex,cy+yrotate(45,-11,angle)*scaley,24,12,angle,Qt::black,Qt::yellow,scalex,scaley);
        drawWing(g,cx+xrotate(40,-11,angle)*scalex,cy+yrotate(40,-11,angle)*scaley,angle,Qt::black,Qt::magenta);
        drawPeck(g,cx,cy,angle,Qt::black,Qt::red);
        dda->drawTiltedEllipse(g,cx+xrotate(18,3,angle)*scalex,cy+yrotate(18,3,angle)*scaley,2,2,angle,Qt::black,Qt::cyan,scalex,scaley);

    }

    //void drawBird(QPainter *g, int cx, int cy){
    //        pix.clear();
    //        drawTail(g,65+cx,-8+cy,Qt::black,Qt::red);
    //        drawEllipse(g,18+cx,0+cy,8,8,Qt::black,Qt::yellow,true,true,true,true);
    //        drawEllipse(g,45+cx,-11+cy,24,12,Qt::black,Qt::yellow,true,true,true,true);

    //        drawWing(g,40+cx,-11+cy,Qt::black,Qt::magenta);
    //        //drawEllipse(g,45+cx,-2+cy,14,14,Qt::black,Qt::magenta,true,true,true,true);
    //        //drawEllipse(g,45+cx,-11+cy,24,12,Qt::black,Qt::yellow,false,false,true,true);
    //        //midpoint(g,35+cx,-10+cy,55+cx,-10+cy,Qt::black);
    //        drawEllipse(g,18+cx,3+cy,2,2,Qt::blue,Qt::cyan,true,true,true,true);
    //        drawPeck(g,0+cx,0+cy,Qt::black,Qt::red);
    //    }
        void drawPeck(QPainter *g, int cx, int cy, float angle,QColor bound, QColor fill){
            dda->pix.clear();
            int xarr[]={ cx, cx + xrotate(10,3,angle)*scalex, cx + xrotate(10,-3,angle)*scalex};
            int yarr[]={cy, cy + yrotate(10,3,angle)*scaley, cy + yrotate(10,-3,angle)*scaley};
            dda->drawPoly(g,3,xarr,yarr,bound);
            dda->boundaryFill(g,cx+xrotate(5,0,angle)*scalex,cy+yrotate(5,0,angle)*scaley,fill);
        }

        void drawTail(QPainter *g, int cx, int cy, float angle, QColor bound, QColor fill){
            dda->pix.clear();
            int xarr[]={cx,cx+xrotate(10,8,angle)*scalex,cx+xrotate(15,0,angle)*scalex};
            int yarr[]={cy,cy+yrotate(10,8,angle)*scaley,cy+yrotate(15,0,angle)*scaley};
            dda->drawPoly(g,3,xarr,yarr,bound);
            dda->boundaryFill(g,cx+xrotate(5,1,angle)*scalex,cy+yrotate(5,1,angle)*scaley,fill);
        }

        void drawWing(QPainter *g, int px, int py, float angle,QColor bound, QColor fill){
            dda->pix.clear();
            int xarr[][4]={{+0,-10,+20,+10},{+0,-10,+20,+10},{+0,-10,+20,+10},{+0,-10,+20,+10}};
            int yarr[][4]={{+0,+13,+30,+0},{+0,+10,+18,+0},{+0,-15,-18,+0},{+0,+10,+18,+0}};
            int xf[]={5,5,5,5};
            int yf[]={2,2,-2,2};
            vector<int> xf2,yf2;
            vector<int> xbrr[4],ybrr[4];
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    xbrr[i].push_back(px+xrotate(xarr[i][j],yarr[i][j],angle)*scalex);
                    ybrr[i].push_back(py+yrotate(xarr[i][j],yarr[i][j],angle)*scaley);
                }
                xf2.push_back(px+xrotate(xf[i],yf[i],angle)*scalex);
                yf2.push_back(py+yrotate(xf[i],yf[i],angle)*scaley);
            }

            dda->drawPoly(g,4,xbrr[wingState%4].data(),ybrr[wingState%4].data(),bound);
            dda->boundaryFill(g,xf2[wingState%4],yf2[wingState%4],fill);
            //plot(g,px+2,yarr[1][1]/2,Qt::blue);
            //plot(g,px+2,p0,Qt::cyan);
        }
    void updateParams(){
        wingState++;
    }
};

class AngleTree:public Drawable{
public:

    float angle;
    int scalex=1,scaley=1;
    AngleTree(int _cx, int _cy, float _angle,MidEllipse *d):angle(_angle),Drawable(_cx,_cy,d){}
    void draw(QPainter *g){

        //base
        vector<int> xb3({-10,+10,+10,-10});
        vector<int> yb3({10,10,-10,-10});


        //trunk
        vector<int> xb2({-3,+3,+3,-3});
        vector<int> yb2({20,20,10,10});


        vector<int> xb4({-3,+3,+3,-3});
        vector<int> yb4({10,10,0,0});

        //top
        vector<int> xb1({+0,+10,+5,+10,+5,+10,-10,-5,-10,-5,-10});
        vector<int> yb1({+40,30,30,25,25,20,20,25,25,30,30});

        vector<int> xa1,ya1,xa2,ya2,xa3,ya3,xa4,ya4;

        for(int i = 0; i< xb1.size();i++){
            xa1.push_back(cx + xb1[i]*cos(angle)*scalex - yb1[i]*sin(angle)*scalex);
            ya1.push_back(cy + xb1[i]*sin(angle)*scaley + yb1[i]*cos(angle)*scaley);
        }

        for(int i = 0; i< xb2.size();i++){
            //xa2.push_back(cx + xb2[i]*cos(angle)*scalex - yb2[i]*sin(angle)*scalex);
            xa2.push_back(cx+xrotate(xb2[i],yb2[i],angle)*scalex);
            ya2.push_back(cy+yrotate(xb2[i],yb2[i],angle)*scaley);
        }

        for(int i = 0; i< xb3.size();i++){
            //xa3.push_back(cx + xb3[i]*cos(angle) - yb3[i]*sin(angle));
            //ya3.push_back(cy + xb3[i]*sin(angle) + yb3[i]*cos(angle));
            xa3.push_back(cx + xb3[i]*scalex);
            ya3.push_back(cy + yb3[i]*scaley);
        }

        for(int i = 0; i< xb4.size();i++){
            xa4.push_back(cx + xb4[i]*cos(angle)*scalex - yb4[i]*sin(angle)*scalex);
            ya4.push_back(cy + xb4[i]*sin(angle)*scaley + yb4[i]*cos(angle)*scaley);
        }


        dda->drawPoly(g,4,xa3.data(),ya3.data(),Qt::black);
        dda->boundaryFill(g,cx,cy-5,Qt::darkGray);
        dda->pix.clear();

        dda->drawPoly(g,4,xa2.data(),ya2.data(),QColor(255,203,154));
        dda->drawPoly(g,4,xa4.data(),ya4.data(),QColor(255,203,154));
        //dda->boundaryFill(g,cx+5*sin(angle),cy-5*cos(angle),Qt::darkGray);

        dda->boundaryFill(g, cx-15*sin(angle)*scalex, cy+15*cos(angle)*scaley, QColor(255,203,154));
        dda->boundaryFill(g, cx-5*sin(angle)*scalex, cy+5*cos(angle)*scaley, QColor(255,203,154));
        dda->pix.clear();

        dda->drawPoly(g,11,xa1.data(),ya1.data(),Qt::darkGreen);
        dda->boundaryFill(g, cx-35*sin(angle)*scalex, cy+35*cos(angle)*scaley,Qt::green);

    }
    void updateParams(){
        angle+=0.1;
    }
};

#endif
