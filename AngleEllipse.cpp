#ifndef _ANGLE_ELLIPSE
#define _ANGLE_ELLIPSE

#include <QColor>
#include <array>
#include <vector>
#include <cmath>
#include "dda.h"

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
    virtual void draw(QPainter *g)=0;
};

class AngleTree:public Drawable{
public:
    int cx,cy;
    float angle;
    DDA *dda;
    AngleTree(int _cx, int _cy, float _angle,DDA *d):cx(_cx),cy(_cy),angle(_angle),dda(d){}
    void draw(QPainter *g){

        //base
        vector<int> xb3({-10,+10,+10,-10});
        vector<int> yb3({-30,-30,-50,-50});


        //trunk
        vector<int> xb2({-3,+3,+3,-3});
        vector<int> yb2({-20,-20,-30,-30});


        vector<int> xb4({-3,+3,+3,-3});
        vector<int> yb4({-30,-30,-40,-40});

        //top
        vector<int> xb1({+0,+10,+5,+10,+5,+10,-10,-5,-10,-5,-10});
        vector<int> yb1({+0,-10,-10,-15,-15,-20,-20,-15,-15,-10,-10});

        vector<int> xa1,ya1,xa2,ya2,xa3,ya3,xa4,ya4;

        for(int i = 0; i< xb1.size();i++){
            xa1.push_back(cx + xb1[i]*cos(angle) - yb1[i]*sin(angle));
            ya1.push_back(cy + xb1[i]*sin(angle) + yb1[i]*cos(angle));
        }

        for(int i = 0; i< xb2.size();i++){
            xa2.push_back(cx + xb2[i]*cos(angle) - yb2[i]*sin(angle));
            ya2.push_back(cy + xb2[i]*sin(angle) + yb2[i]*cos(angle));
        }

        for(int i = 0; i< xb3.size();i++){
            xa1.push_back(cx + xb3[i]*cos(angle) - yb3[i]*sin(angle));
            ya1.push_back(cy + xb3[i]*sin(angle) + yb3[i]*cos(angle));
        }

        for(int i = 0; i< xb4.size();i++){
            xa1.push_back(cx + xb4[i]*cos(angle) - yb4[i]*sin(angle));
            ya1.push_back(cy + xb4[i]*sin(angle) + yb4[i]*cos(angle));
        }
        dda->drawPoly(g,4,xa3.data(),ya3.data(),Qt::black);
        dda->drawPoly(g,4,xa2.data(),ya2.data(),QColor(255,203,154));
        dda->drawPoly(g,4,xa4.data(),ya4.data(),QColor(255,203,154));
        dda->drawPoly(g,11,xa1.data(),ya1.data(),Qt::darkGreen);

        dda->boundaryFill(g,cx,cy-5,Qt::green);
        dda->boundaryFill(g,cx,cy-45,Qt::darkGray);
        dda->boundaryFill(g,cx,cy-25,QColor(255,203,154));
        dda->boundaryFill(g,cx,cy-35,QColor(255,203,154));
    }

};

#endif