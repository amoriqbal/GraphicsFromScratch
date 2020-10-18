#include "dda.h"
#include "midellipse.h"
#include <QApplication>
#include <chrono>
#include <thread>
#include <unistd.h>
class MovingEllipse : public MidEllipse{
public:
    volatile int state;
    int cx,cy;
    MovingEllipse():cx(-8),cy(0),state(0){}
    void setCenter(int cx1,int cy1){
        cx=cx1;
        cy=cy1;
        this->update();
    }
    void virtual paint(QPainter *g){
        drawBird(g,-40,0);
    }
    void drawBird(QPainter *g, int cx, int cy){
        drawTail(g,65+cx,-8+cy,Qt::red,Qt::red);
        drawEllipse(g,18+cx,0+cy,8,8,Qt::black,Qt::yellow,true,true,true,true);
        drawEllipse(g,45+cx,-11+cy,24,12,Qt::black,Qt::yellow,true,true,true,true);
        drawEllipse(g,45+cx,-2+cy,14,14,Qt::black,Qt::magenta,true,true,true,true);
        drawEllipse(g,45+cx,-11+cy,24,12,Qt::black,Qt::yellow,false,false,true,true);
        midpoint(g,35+cx,-10+cy,55+cx,-10+cy,Qt::black);
        drawEllipse(g,18+cx,3+cy,2,2,Qt::blue,Qt::cyan,true,true,true,true);
        drawPeck(g,0+cx,0+cy,Qt::red,Qt::red);
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


