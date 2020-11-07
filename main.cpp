#include "dda.h"
#include "midellipse.h"
#include <QApplication>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "AngleEllipse.cpp"
#include <QMouseEvent>
#include "Settings.cpp"
#include <QWidget>
#include <QIcon>
#include <QAbstractButton>
#include <ui_dda.h>

using namespace std;

class Renderer:public MidEllipse{
public:
    vector<Drawable*> drawObjects;
    vector<QWidget*> birdControls, treeControls;
    volatile int toSpawn;
    Renderer():toSpawn(0){
        QPixmap pixm("bird.png");
        QIcon icon(pixm);
        ui->bird_button->setIcon(icon);

        birdControls.push_back(ui->birdSettingsLabel);
        birdControls.push_back(ui->birdFlock);
        birdControls.push_back(ui->birdHead);
        birdControls.push_back(ui->birdSize);
        birdControls.push_back(ui->birdSpeed);
        birdControls.push_back(ui->birdTail);
        birdControls.push_back(ui->birdTilt);
        birdControls.push_back(ui->birdWing);
        birdControls.push_back(ui->label);
        birdControls.push_back(ui->label_2);
        birdControls.push_back(ui->label_3);
        birdControls.push_back(ui->label_4);
        birdControls.push_back(ui->label_5);
        birdControls.push_back(ui->label_6);
        birdControls.push_back(ui->label_7);

        treeControls.push_back(ui->treeSettingsLabel);
        treeControls.push_back(ui->treeFallover);
        treeControls.push_back(ui->treeFalloverLabel);
        treeControls.push_back(ui->treeForest);
        treeControls.push_back(ui->treeForestLabel);
        treeControls.push_back(ui->treeSize);
        treeControls.push_back(ui->treeSizeLabel);

        if(toSpawn==0){
            setControlsVisible(birdControls,true);
            setControlsVisible(treeControls,false);
        } else {
            setControlsVisible(birdControls,false);
            setControlsVisible(treeControls,true);
        }
    }
    void setControlsVisible(vector<QWidget*> &ws,bool show){
        for(auto *x : ws){
            if(show)
                x->show();
            else
                x->hide();
        }
    }
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

    int getXInv(int x1){
        return (x1-width()/2)/gap;
    }

    int getYInv(int y1){
        return -(y1-height()/2)/gap;
    }
    void mousePressEvent(QMouseEvent *pressEvent){
        QPointF p=pressEvent->localPos();
        //Drawable *d;
        switch (toSpawn) {
        case 0:
            BirdSettings::spawn(drawObjects,getXInv(p.x()),getYInv(p.y()),this);
            break;
        case 1:
            TreeSettings::spawn(drawObjects,getXInv(p.x()),getYInv(p.y()),this);
            break;
        default:
            break;
        }

        //drawObjects.push_back(d);
    }
private slots:

    void on_bird_button_pressed(){
        toSpawn=0;
        setControlsVisible(birdControls,true);
        setControlsVisible(treeControls,false);
    }

    void on_tree_button_pressed(){
        toSpawn=1;
        setControlsVisible(birdControls,false);
        setControlsVisible(treeControls,true);
    }

    void on_birdSize_textChanged(const QString &s){
        BirdSettings::size=s.toInt();
        if(BirdSettings::size==0){
            BirdSettings::size=1;
        }
    }

    void on_birdTilt_textChanged(const QString &s){
        BirdSettings::tilt=s.toFloat()*3.142/180;
    }

    void on_birdHead_textChanged(const QString &s){
        BirdSettings::head=s.toFloat()*3.142/180;
    }
    void on_birdSpeed_textChanged(const QString &s){
        BirdSettings::speed=s.toInt();
    }
    void on_birdFlock_textChanged(const QString &s){
        BirdSettings::flock=s.toInt();
    }
    void on_birdWing_textChanged(const QString &s){
        BirdSettings::wing=s.toInt();
    }
    void on_birdTail_textChanged(const QString &s){
        BirdSettings::tail=s.toInt();
    }
    void on_treeFallover_textChanged(const QString &s){
        TreeSettings::fallover=s.toFloat()*3.142/180;
    }
    void on_treeForest_textChanged(const QString &s){
        TreeSettings::forest=s.toInt();
    }
    void on_treeSize_textChanged(const QString &s){
        TreeSettings::size=s.toInt();
    }

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Renderer w;

    w.show();
    return a.exec();
}


