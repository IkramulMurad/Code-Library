#include <bits/stdc++.h>

using namespace std;

const double pi=acos(-1);
const double eps=1e-9;

//point
struct pointInt{
    int x,y;

    pointInt(){
        x=y=0;
    }

    pointInt(int _x, int _y){
        x=_x; y=_y;
    }

    bool operator<(pointInt& b){
        if(x==b.x)
            return y<b.y;
        else return x<b.x;
    }

    bool operator==(pointInt& b){
        return (x==b.x and y==b.y);
    }
};

struct point{
    double x,y;

    point(){
        x=y=0.0;
    }

    point(double _x, double _y){
        x=_x; y=_y;
    }

    bool operator<(point& b){
        if(abs(x-b.x)<eps)
            return y<b.y;
        else return x<b.x;
    }

    bool operator==(point& b){
        return (abs(x-b.x)<eps and abs(y-b.y)<eps);
    }
};

template <class T>
double dist(T a, T b){
    return hypot(a.x-b.x, a.y-b.y);
}

double deg2rad(double deg){
    return deg*pi/180;
}

template <class T>
T rotate(T a, double theta){
    theta=deg2rad(theta);
    return T(a.x*cos(theta)-a.y*sin(theta),
             a.x*sin(theta)+a.y*cos(theta));
}


//line
struct line{
    double a,b,c;
};

/*
    m=(y2-y1)/(x2-x1)

    y-y1 = m(x-x1)
    or, y-mx = y1-mx1
    or, -mx + y + (mx1-y1) =0
    hence, a=-m, b=1, c=mx1-y1

    for vertical line,
    m=(y2-y1)/(x2-x1)=undefined=1/0

    y-y1=m(x-x1)
    or, (y-y1)/m=x-x1
    or, 0=x-x1
    or, x+0-x1=0
    hence, a=1, b=0, c=-x1
*/
//make standard form
line points2line(point a, point b){
    line l;
    if(abs(a.x-b.x)<eps){
        l.a=1.0; l.b=0.0; l.c=-a.x;
    }
    else{
        double m=(b.y-a.y)/(b.x-a.x);
        l.a=-m;
        l.b=1.0;
        l.c=m*a.x-a.y;
    }
    return l;
}

int main()
{
    point a(3,2), b(6,5), c(10,3);
    c=rotate(c,77);
    cout<<c.x<<" "<<c.y<<endl;
    return 0;
}
