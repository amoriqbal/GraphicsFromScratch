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
        if(state!=0){
            drawEllipse(g,cx++,cy,15,10,Qt::blue,Qt::yellow);
            this->update();
            usleep(100000);
        } else {
            drawEllipse(g,cx,cy,15,10,Qt::blue,Qt::yellow);
        }
        //drawEllipse(g,0,0,5,8,Qt::blue,Qt::yellow);
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


