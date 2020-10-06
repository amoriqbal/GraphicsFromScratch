#include "dda.h"
#include "midcircle.h"
#include <QApplication>
#include <chrono>
#include <thread>
#include <unistd.h>
class MovingCircle : public MidCircle{
public:
    volatile int state;
    int cx,cy;
    MovingCircle():cx(-8),cy(0),state(0){}
    void setCenter(int cx1,int cy1){
        cx=cx1;
        cy=cy1;
        this->update();
    }
    void virtual paint(QPainter *g){
        if(state!=0){
            drawCircle(g,cx++,cy,10,Qt::blue,Qt::yellow);
            this->update();
            usleep(100000);
        } else {
            drawCircle(g,cx,cy,10,Qt::blue,Qt::yellow);
        }
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
    MovingCircle w;
    w.show();
    return a.exec();
}


