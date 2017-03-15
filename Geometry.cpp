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

bool areParallel(line a, line b){
    return (abs(a.a-b.a)<eps and abs(a.b-b.b)<eps);
}

bool areSame(line a, line b){
    return (areParallel(a,b) and abs(a.c-b.c)<eps);
}

/*
    a1x+b1y+c1=0
    a2x+b2y+c2=0

    so, y=(-a1x-c1)/b1
    and y=(-a2x-c2)/b2

    hence, (-a1x-c1)/b1=(-a2x-c2)/b2
    or, x(a2b1-a1b2)=b2c1-b1c2
    so, x=(b2c1-b1c2)/(a2b1-a1b2)
*/

bool areIntersect(line a, line b, point& p){
    if(areParallel(a,b)) return false;

    p.x=(b.b*a.c-a.b*b.c)/(b.a*a.b-a.a*b.b);

    //checking vertical line
    //if one line is vertical then b=0 and
    //other line is not vertical as they are not parallel
    if(abs(a.b)>eps) p.y=-(a.a*p.x+a.c);
    else p.y=-(b.a*p.x+b.c);
    return true;
}

//vector
struct Vector{
    double x,y;
    Vector(double _x, double _y) : x(_x), y(_y) {}
};

//caution, 1st parameter will be the 1st end of a vector
//2nd parameter is the growing/last end in the direction
Vector points2vector(point a, point b){
    return Vector(b.x-a.x, b.y-a.y);
}

Vector scale(Vector v, double s){
    return Vector(v.x*s, v.y*s);
}

point translate(point p, Vector v){
    return point(p.x+v.x, p.y+v.y);
}

double norm(Vector v){
    return sqrt(v.x*v.x + v.y*v.y);
}

double dot(Vector a, Vector b){
    return (a.x*b.x + a.y*b.y);
}

double cross(Vector a, Vector b){
    return (a.x*b.y - a.y*b.x);
}

// return true if point p is on the same line as AB
bool collinear(point a, point b, point p){
    return (abs(cross(points2vector(a,b), points2vector(a,p)))<eps);
}

//return true if point p is on the left side of line AB
bool ccw(point a, point b, point p){
    return (cross(points2vector(a,b), points2vector(a,p))>0.0);
}

//return angle between 2 vectors
double angleRad(Vector ba, Vector bc){
    return acos(dot(ba,bc)/(norm(ba)*norm(bc)));
}

/*
    p is the point, ab is the line.
    pc is the perpendicular to the line.
    ab.ap = |ab||ap|cos(theta)
    |ap|cos(theta) = ab.ap/|ab|
    |ap|cos(theta) also called |ac|, the projection on line ab.
    so ac=u.|ac| where u is the unit vector.
    or, ac=(ab/|ab|)*|ac|
    or, ac=(ab/|ab|)*(ab.ap)/|ab|
    or, ac=ab.((ab.ap)/|ab|^2)
    or, ac=ab.x where x=(ab.ap)/|ab|^2
    hence point c = translation(point a, vector ac)
*/
//distance between a point and a line
//return distance and save distance point
double dist2line(point a, point b, point p, point& c){
    Vector ap=points2vector(a,p);
    Vector ab=points2vector(a,b);

    double x=dot(ab,ap)/(norm(ab)*norm(ab));
    Vector ac=scale(ab,x);
    c=translate(a,ac);

    return dist(p,c);
}

/*
    If the point is on left of starting point of line,
    Then it creates 90+ angle, and dot product becomes negative.

    If the point is on right of ending point of line,
    Then projection of position vector of the point on line
    becomes greater than the magnitude of line.
*/
double dist2lineSegment(point a, point b, point p, point& c){
    Vector ap=points2vector(a,p);
    Vector ab=points2vector(a,b);

    if(dot(ab,ap)<0.0){
        c=point(a.x,a.y);
        return dist(a,p);
    }

    double projection=dot(ab,ap)/norm(ab);
    if(projection>norm(ab)){
        c=point(b.x,b.y);
        return dist(b,p);
    }

    return dist2line(a,b,p,c);
}

int main()
{
    point a(0,0), b(0,4), p(-2,6), c(2,0);
    cout<<dist2lineSegment(a,b,p,c)<<endl;
    cout<<c.x<<" "<<c.y<<endl;

    return 0;
}
