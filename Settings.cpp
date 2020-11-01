#ifndef _SETTINGS
#define _SETTINGS
#include "AngleEllipse.cpp"
#include "midellipse.h"

class BirdSettings{
public:
    static inline float tilt=0,head=0;
    static inline int size=1,speed=0,wing=0,tail=0,flock=1;
    static void spawn(vector<Drawable*> &dv, int cx, int cy, MidEllipse *dda){
        Drawable *d;
        for(int i=0;i<flock;i++){
            d=new AngleBird(cx+size*(i/2)*80,cy+size*(i+1)/2*30,tilt,head,size,size,wing,tail,speed,dda);
            dv.push_back(d);
        }
    }
};

class TreeSettings{
public:
    static inline int fallover=0, forest=1,size=1;
    static void spawn(vector<Drawable*> &dv, int cx, int cy, MidEllipse *dda){
        Drawable *d;
        for(int i=0;i<forest;i++){
            d=new AngleTree(cx,cy,fallover,size,size,dda);
            dv.push_back(d);
        }
    }
};
#endif
