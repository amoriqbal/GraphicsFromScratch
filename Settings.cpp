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
            d=new AngleBird(cx+size*(i/2)*80,cy+size*(i%2)*50,tilt,head,size,size,wing,tail,speed,dda);
            dv.push_back(d);
        }
    }
};

class TreeSettings{
public:
    static inline int forest=1,size=1;
    static inline float fallover=0;
    static void spawn(vector<Drawable*> &dv, int cx, int cy, MidEllipse *dda){
        Drawable *d;
        for(int i=0;i<forest;i++){
            d=new AngleTree(cx+size*(i/2)*30,cy+size*(i%2)*40,fallover,size,size,dda);
            dv.push_back(d);
        }
    }
};
#endif
