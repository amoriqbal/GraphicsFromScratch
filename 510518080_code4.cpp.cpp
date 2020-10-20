#include "dda.h"
#include "midellipse.h"
#include <QApplication>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <math.h>


class MovingEllipse : public MidEllipse{
public:
    volatile int state;
    float th;
    MovingEllipse():th(0),state(1){}
    void setTheta(float t){
        th=t;
        this->update();
    }
    void virtual paint(QPainter *g){
        if(state==1){
            drawSettings(g,th);
            setTheta(th+0.1);
        }
        else{
        drawSettings(g,th);
        }
        //drawBird(g,-40,0);
    }
    void drawBird(QPainter *g, int cx, int cy){
        drawTail(g,65+cx,-8+cy,Qt::black,Qt::magenta);
        drawEllipse(g,18+cx,0+cy,8,8,Qt::black,Qt::yellow,true,true,true,true);
        drawEllipse(g,45+cx,-11+cy,24,12,Qt::black,Qt::yellow,true,true,true,true);
        drawEllipse(g,45+cx,-2+cy,14,14,Qt::black,Qt::magenta,true,true,true,true);
        drawEllipse(g,45+cx,-11+cy,24,12,Qt::black,Qt::yellow,false,false,true,true);
        midpoint(g,35+cx,-10+cy,55+cx,-10+cy,Qt::black);
        drawEllipse(g,18+cx,3+cy,2,2,Qt::black,Qt::cyan,true,true,true,true);
        drawPeck(g,0+cx,0+cy,Qt::black,Qt::red);
    }
    void drawPeck(QPainter *g, int cx, int cy, QColor bound, QColor fill,int scale=1){
        int xarr[]={cx,cx+10,cx+10};
        int yarr[]={cy,cy+3,cy-3};
        drawPoly(g,3,xarr,yarr,bound);
        boundaryFill(g,cx+2,cy,fill);
    }

    void drawTail(QPainter *g, int cx, int cy, QColor bound, QColor fill,int scale=1){
        int xarr[]={cx,cx+10,cx+15};
        int yarr[]={cy,cy+8,cy};
        drawPoly(g,3,xarr,yarr,bound);
        boundaryFill(g,cx+2,cy+1,fill);
    }

    void drawSettings(QPainter *g, float theta){
        int n=8;
        int r1=10,r2=15,r3=20;
        int s=3.14*r2/n*0.7;
        std::vector<int> ptsx,ptsy;
        for(int i=0;i<n;i++){
            float angle=2*3.142/n*i+theta;
            ptsx.push_back(s*std::cos(angle)-r2*std::sin(angle));
            ptsy.push_back(s*std::sin(angle)+r2*std::cos(angle));
            ptsx.push_back(s*std::cos(angle)-r3*std::sin(angle));
            ptsy.push_back(s*std::sin(angle)+r3*std::cos(angle));
            ptsx.push_back(-s*std::cos(angle)-r3*std::sin(angle));
            ptsy.push_back(-s*std::sin(angle)+r3*std::cos(angle));
            ptsx.push_back(-s*std::cos(angle)-r2*std::sin(angle));
            ptsy.push_back(-s*std::sin(angle)+r2*std::cos(angle));
}

        drawPoly(g,4*n,ptsx.data(),ptsy.data(),Qt::black);
        drawEllipse(g,0,0,r1,r1,Qt::black,Qt::white,true,true,true,true);
        boundaryFill(g,0,r1+1,Qt::darkGray);
    }
private slots:
    void virtual on_pushButton_clicked(){
        if(state==0){
            state++;
            this->update();
        }else{
            state=0;
        }
    }


};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MovingEllipse w;
    w.show();
    return a.exec();
}


