#include "dda.h"
#include "ui_dda.h"
#include<QPainter>
#include<iostream>
#include<math.h>
#include<QKeyEvent>

using namespace  std;
DDA::DDA(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DDA)
{
    ui->setupUi(this);
    gap=10;
    shiftx=0;
    shifty=0;
    this->installEventFilter(this);
}

DDA::~DDA()
{
    delete ui;
}

void DDA::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);
//    int x1[]={-5,5,10,0,-10};
//    int y1[]={5,5,0,-5,0};
    drawGrid(&qp);
    pix.clear();
//    drawTree(&qp,0,5);
//    drawTree(&qp,-30,20);
//    drawTree(&qp,30,10);
    paint(&qp);
}

void DDA::paint(QPainter *g){
}
void DDA::drawGrid(QPainter *qp){
    drawHGrid(qp);
    drawVGrid(qp);
}
void DDA::drawHGrid(QPainter *qp){
    int h,w;
    h=height();
    w=width();
    QPen pen(Qt::red,3,Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(0,h/2+shifty,w,h/2+shifty);

    QPen pen2(Qt::black,1,Qt::SolidLine);
    qp->setPen(pen2);

    for(int y=gap;y<h/2-shifty;y+=gap){
        qp->drawLine(0,h/2+y+shifty,w,h/2+y+shifty);
    }
    for(int y=gap;y<h/2+shifty;y+=gap){
        qp->drawLine(0,h/2-y+shifty,w,h/2-y+shifty);
    }
}

void DDA::drawVGrid(QPainter *qp){
    int h,w;
    h=height();
    w=width();
    QPen pen(Qt::red,3,Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(w/2+shiftx,0,w/2+shiftx,h);

    QPen pen2(Qt::black,1,Qt::SolidLine);
    qp->setPen(pen2);

    for(int x=gap;x<w/2-shiftx;x+=gap){
        qp->drawLine(w/2+x+shiftx,0,w/2+x+shiftx,h);
    }
    for(int x=gap;x<w/2+shiftx;x+=gap){
        qp->drawLine(w/2-x+shiftx,0,w/2-x+shiftx,h);
    }
}

void DDA::plot(QPainter *qp,int x1, int y1){
    plot(qp,x1,y1,Qt::blue);
}

void DDA::plot(QPainter *qp,int x1, int y1,QColor col){
    qp->fillRect(x(x1)-gap/4+shiftx,y(y1)-gap/4+shifty,gap*3/4,gap*3/4,col);
    pix.push_back({col,x1,y1});
}

QColor DDA::getPixel(int x1, int y1){
    for(auto &t : pix){
        if(t.x==x1 && t.y==y1){
            return t.col;
        }
    }
    return QColor(Qt::white);
}

int DDA::x(int x1){
    return x1*gap + width()/2;
}

int DDA::y(int y1){
    return -y1*gap + height()/2;
}

void DDA::ddaLine(QPainter *g, int x1, int y1, int x2, int y2)
{
    int dx,dy;
            dx=x2-x1;
            dy=y2-y1;
            int steps=max(abs(dx),abs(dy));
            for(int i=0;i<=steps;i++){
                int fx,fy;
                fx=(int)(dx*i/(1.0*steps))+x1;
                fy=(int)(dy*i/(1.0*steps))+y1;
                plot(g,fx,fy,Qt::blue);
            }
}

void DDA::bresenham(QPainter *g, int x0, int y0, int x1, int y1){
    int dx, dy, p, x, y;
    dx=x1-x0;
    dy=y1-y0;
    x=x0;
  y=y0;
  p=2*dy-dx;
  while(x<=x1)
  {
     if(p>=0)
     {
           plot(g,x,y, Qt::yellow);
           y=y+1;
           p=p+2*dy-2*dx;
     }
     else
     {
           plot(g,x,y, Qt::yellow);
           p=p+2*dy;
     }
     x=x+1;
  }

}

void DDA::zoomin(){
    gap++;
    this->repaint();
}
void DDA::zoomout(){
    gap--;
    this->repaint();
}
void DDA::midpoint(QPainter *g,int x0, int y0, int x1, int y1, QColor col=QColor(Qt::yellow)){


      if(x1==x0){
         if(y0>y1){
            int t=y0;
            y0=y1;
            y1=t;
         }
         for(int i=y0;i<=y1;i++){
            plot(g,x0,i,col);
         }
         return;
      }
      int slope_sign=1;
      if((x0-x1)*(y0-y1)<0){
         x1=-x1;
         x0=-x0;
         slope_sign=-1;
      }
      int dx=x1-x0;
      int dy=y1-y0;

      if(y0>y1){
         int t=y0;
         y0=y1;
         y1=t;
         t=x0;
         x0=x1;
         x1=t;
      }

      double m=dy*1.0/dx;
      double ma=abs(m);

      if(ma>1){
         if(y0>y1){
            int t=y0;
            y0=y1;
            y1=t;
            t=x0;
            x0=x1;
            x1=t;
         }
         double p=1-ma/2;
         int xn=x0;
         for(int y=y0;y<=y1;y++){
            plot(g,slope_sign*xn,y,col);
            if(p>=0){
               xn=xn+1;
               p=p+1-m;
            }
            else{
               p=p+1;
            }
         }
      } else {
         if(x0>x1){
            int t=y0;
            y0=y1;
            y1=t;
            t=x0;
            x0=x1;
            x1=t;
         }
         double p=0.5-ma;
         int yn=y0;
         for(int x=x0;x<=x1;x++){
            plot(g,slope_sign*x,yn,col);
            if(p>=0){
               p=p-m;
            }
            else{
               yn=yn+1;
               p=p+1-m;
            }
         }
      }

   }

void DDA::drawPoly(QPainter *g, int n, int *xarr, int *yarr, QColor col){
    for(int i=0;i<n;i++)
    {
        midpoint(g,xarr[i],yarr[i],xarr[(i+1)%n],yarr[(i+1)%n],col);
    }
}

void DDA::boundaryFill(QPainter *g, int x1, int y1,QColor col){
    QColor bg(Qt::white);
    if(getPixel(x1,y1)==col){
        return;
    }
    if(getPixel(x1,y1)==bg){
        plot(g,x1,y1,col);
        boundaryFill(g,x1+1,y1,col);
        boundaryFill(g,x1,y1+1,col);
        boundaryFill(g,x1-1,y1,col);
        boundaryFill(g,x1,y1-1,col);
    }
}

void DDA::drawTree(QPainter *g, int x1, int y1){
    //base
    int xa3[]={x1-10,x1+10,x1+10,x1-10};
    int ya3[]={y1-30,y1-30,y1-50,y1-50};


    //trunk
    int xa2[]={x1-3,x1+3,x1+3,x1-3};
    int ya2[]={y1-20,y1-20,y1-30,y1-30};


    int xa4[]={x1-3,x1+3,x1+3,x1-3};
    int ya4[]={y1-30,y1-30,y1-40,y1-40};

    //top
    vector<int> xa1({x1+0,x1+10,x1+5,x1+10,x1+5,x1+10,x1-10,x1-5,x1-10,x1-5,x1-10});
    vector<int> ya1({y1+0,y1-10,y1-10,y1-15,y1-15,y1-20,y1-20,y1-15,y1-15,y1-10,y1-10});

    drawPoly(g,4,xa3,ya3,Qt::black);
    drawPoly(g,4,xa2,ya2,QColor(255,203,154));
    drawPoly(g,4,xa4,ya4,QColor(255,203,154));
    drawPoly(g,11,xa1.data(),ya1.data(),Qt::darkGreen);

    boundaryFill(g,x1,y1-5,Qt::green);
    boundaryFill(g,x1,y1-45,Qt::darkGray);
    boundaryFill(g,x1,y1-25,QColor(255,203,154));
    boundaryFill(g,x1,y1-35,QColor(255,203,154));

}

void DDA::on_zoomOut_clicked()
{
    zoomout();
}


void DDA::on_zoomIn_clicked()
{
    zoomin();
}
bool DDA::eventFilter(QObject *object, QEvent *ev)
{
      if (ev->type() == QEvent::KeyPress)
      {
           QKeyEvent* keyEvent = (QKeyEvent*)ev;

           if (keyEvent->key() == Qt::Key_D)
           {
              shiftx+=3;
              this->repaint();
           } else if (keyEvent->key() == Qt::Key_A)
           {
              shiftx-=3;
              this->repaint();
           } else if (keyEvent->key() == Qt::Key_W)
           {
              shifty-=3;
              this->repaint();
           } else if (keyEvent->key() == Qt::Key_S)
           {
              shifty+=3;
              this->repaint();
           }
    }

    return false;
}
void DDA::on_pushButton_clicked()
{

}

void DDA::on_bird_button_pressed()
{

}

void DDA::on_tree_button_pressed()
{

}

void DDA::on_birdSize_textChanged(const QString &arg1)
{

}

void DDA::on_birdTilt_textChanged(const QString &s)
{

}

void DDA::on_birdHead_textChanged(const QString &s)
{

}


void DDA::on_birdFlock_textChanged(const QString &s)
{

}

void DDA::on_birdWing_textChanged(const QString &s)
{

}

void DDA::on_birdTail_textChanged(const QString &s)
{

}

void DDA::on_birdSpeed_textChanged(const QString &s)
{

}

void DDA::on_treeFallover_textChanged(const QString &s)
{

}

void DDA::on_treeSize_textChanged(const QString &s)
{

}

void DDA::on_treeForest_textChanged(const QString &s)
{

}
