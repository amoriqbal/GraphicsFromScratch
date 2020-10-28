#include "dda.h"
#include "midellipse.h"
#include <QApplication>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "AngleEllipse.cpp"
#include <QMouseEvent>

//class MovingEllipse : public MidEllipse{
//public:
//    AngleTree a;
//    volatile int state;
//    int cx,cy;
//    MovingEllipse():cx(-8),cy(0),state(0),a(0,0,1.57,this){}
//    void setCenter(int cx1,int cy1){
//        cx=cx1;
//        cy=cy1;
//        this->update();
//    }
//    void virtual paint(QPainter *g){
//        if(state==1){
//            drawBird(g,cx,cy);
//            usleep(100000);
//            //setCenter(cx-1,cy);

//        }
//        else{
//            drawBird(g,cx,cy);
//            a.draw(g);
//        }
//        a.draw(g);
//    }
//    void drawBird(QPainter *g, int cx, int cy){
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
//    void drawPeck(QPainter *g, int cx, int cy, QColor bound, QColor fill,int scale=1){
//        pix.clear();
//        int xarr[]={cx,cx+10,cx+10};
//        int yarr[]={cy,cy+3,cy-3};
//        drawPoly(g,3,xarr,yarr,bound);
//        boundaryFill(g,cx+2,cy,fill);
//    }

//    void drawTail(QPainter *g, int cx, int cy, QColor bound, QColor fill,int scale=1){
//        pix.clear();
//        int xarr[]={cx,cx+10,cx+15};
//        int yarr[]={cy,cy+8,cy};
//        drawPoly(g,3,xarr,yarr,bound);
//        boundaryFill(g,cx+2,cy+1,fill);
//    }

//    void drawWing(QPainter *g, int px, int py, QColor bound, QColor fill){
//        pix.clear();
//        int xarr[][4]={{px+0,px-10,px+20,px+10},{px+0,px-5,px+10,px+5},{px+0,px-5,px+10,px+5},{px+0,px-5,px+10,px+5}};
//        int yarr[][4]={{py+0,py+13,py+30,py+0},{py+0,py+10,py+18,py+0},{py+0,py-15,py-18,py+0},{py+0,py+10,py+18,py+0}};
//        drawPoly(g,4,xarr[cx%4],yarr[cx%4],bound);
//        boundaryFill(g,px+2,py+(yarr[cx%4][1]-py)/2,fill);
//        //plot(g,px+2,yarr[1][1]/2,Qt::blue);
//        //plot(g,px+2,p0,Qt::cyan);
//    }

//private slots:
//    void virtual on_pushButton_clicked(){
//        if(state==0){
//            state++;
//            this->update();
//        }else{
//            state=0;
//        }
//    }


//};

class Renderer:public MidEllipse{
public:
    vector<Drawable*> drawObjects;

    int toSpawn;
    Renderer():toSpawn(0){}

    void paint(QPainter *g){
        if(drawObjects.size()>0){
            for(auto drawable : drawObjects){
                drawable->draw(g);
                pix.clear();
                drawable->updateParams();
            }
        }
        usleep(100000);
        this->update();
    }

    void mousePressEvent(QMouseEvent *pressEvent){
        QPointF p=pressEvent->localPos();
        Drawable *d=new AngleTree(0,0,0,this);
        drawObjects.push_back(d);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Renderer w;
    w.show();
    return a.exec();
}


