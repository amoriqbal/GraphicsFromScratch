#include "midcircle.h"

void MidCircle::drawCircle(QPainter *g, int x1,int y1, int r, QColor bound=Qt::blue, QColor fill=Qt::yellow){
    int xx,yy;
    xx=r;
    yy=0;
    int P=1-r;
    plot(g,x1+xx,y1+yy,bound);
    plot(g,x1+xx,y1-yy,bound);
    plot(g,x1-xx,y1+yy,bound);
    plot(g,x1-xx,y1-yy,bound);
    plot(g,x1+yy,y1+xx,bound);
    plot(g,x1+yy,y1-xx,bound);
    plot(g,x1-yy,y1+xx,bound);
    plot(g,x1-yy,y1-xx,bound);
    for(int i=1;i<xx;i++){
        plot(g,x1+i,y1+yy,fill);
        plot(g,x1-i,y1+yy,fill);
        plot(g,x1+yy,y1+i,fill);
        plot(g,x1+yy,y1-i,fill);
        plot(g,x1+i,y1-yy,fill);
        plot(g,x1-i,y1-yy,fill);
        plot(g,x1-yy,y1+i,fill);
        plot(g,x1-yy,y1-i,fill);
    }

    while(xx>=yy){
        if(P<=0.5){
            P=P+2*yy+1;
        } else {
            xx--;
            P=P+2*yy-2*xx+1;
        }
        yy++;
        plot(g,x1+xx,y1+yy,bound);
        plot(g,x1+xx,y1-yy,bound);
        plot(g,x1-xx,y1+yy,bound);
        plot(g,x1-xx,y1-yy,bound);
        plot(g,x1+yy,y1+xx,bound);
        plot(g,x1+yy,y1-xx,bound);
        plot(g,x1-yy,y1+xx,bound);
        plot(g,x1-yy,y1-xx,bound);

        for(int i=1;i<xx;i++){
            plot(g,x1+i,y1+yy,fill);
            plot(g,x1-i,y1+yy,fill);
            plot(g,x1+yy,y1+i,fill);
            plot(g,x1+yy,y1-i,fill);
            plot(g,x1+i,y1-yy,fill);
            plot(g,x1-i,y1-yy,fill);
            plot(g,x1-yy,y1+i,fill);
            plot(g,x1-yy,y1-i,fill);
        }
    }
}

void MidCircle::paint(QPainter *g){
    int x1=0,y1=0,r=25,z;
    QColor bound=Qt::blue;
    QColor fill=Qt::yellow;
    drawCircle(g,x1,y1,r,bound,fill);
//    int xx,yy;
//    xx=r;
//    yy=0;
//    int P=1-r;

//    plot(g,x1+xx,y1+yy,bound);
//    plot(g,x1+xx,y1-yy,bound);
//    plot(g,x1-xx,y1+yy,bound);
//    plot(g,x1-xx,y1-yy,bound);
//    plot(g,x1+yy,y1+xx,bound);
//    plot(g,x1+yy,y1-xx,bound);
//    plot(g,x1-yy,y1+xx,bound);
//    plot(g,x1-yy,y1-xx,bound);
//    for(int i=1;i<xx;i++){
//        plot(g,x1+i,y1+yy,fill);
//        plot(g,x1-i,y1+yy,fill);
//        plot(g,x1+yy,y1+i,fill);
//        plot(g,x1+yy,y1-i,fill);
//        plot(g,x1+i,y1-yy,fill);
//        plot(g,x1-i,y1-yy,fill);
//        plot(g,x1-yy,y1+i,fill);
//        plot(g,x1-yy,y1-i,fill);
//    }

//    while(xx>=yy){
//        if(P<=0.5){
//            P=P+2*yy+1;
//        } else {
//            xx--;
//            P=P+2*yy-2*xx+1;
//        }
//        yy++;
//        plot(g,x1+xx,y1+yy,bound);
//        plot(g,x1+xx,y1-yy,bound);
//        plot(g,x1-xx,y1+yy,bound);
//        plot(g,x1-xx,y1-yy,bound);
//        plot(g,x1+yy,y1+xx,bound);
//        plot(g,x1+yy,y1-xx,bound);
//        plot(g,x1-yy,y1+xx,bound);
//        plot(g,x1-yy,y1-xx,bound);
//        for(int i=1;i<xx;i++){
//            plot(g,x1+i,y1+yy,fill);
//            plot(g,x1-i,y1+yy,fill);
//            plot(g,x1+yy,y1+i,fill);
//            plot(g,x1+yy,y1-i,fill);
//            plot(g,x1+i,y1-yy,fill);
//            plot(g,x1-i,y1-yy,fill);
//            plot(g,x1-yy,y1+i,fill);
//            plot(g,x1-yy,y1-i,fill);
//        }
//    }
}


