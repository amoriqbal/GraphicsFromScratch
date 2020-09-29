#include "dda.h"
#include "midcircle.h"
#include <QApplication>
#include <chrono>
#include <thread>
#include <unistd.h>
class MovingCircle : public MidCircle{
public:
    int cx,cy;
    MovingCircle():cx(-8),cy(0){}
    void setCenter(int cx1,int cy1){
        cx=cx1;
        cy=cy1;
        this->update();
    }
    void virtual paint(QPainter *g){
        drawCircle(g,cx,cy,10,Qt::blue,Qt::yellow);

    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MovingCircle w;
    w.show();
    for(int i=0;i<10;i++)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        usleep(1);
        w.setCenter(-8+i,0);
    }

    return a.exec();
}


