#include <bits/stdc++.h>

using namespace std;

const double pi=acos(-1);
const double eps=1e-9;

//point
template <class T>
class Point{
public:
    T x, y;

    Point(T _x = 0, T _y = 0){
        x = _x;  y = _y;
    }

    bool operator<(Point& b){
        if(abs(x - b.x) < eps)
            return y < b.y;
        else return x < b.x;
    }

    bool operator==(Point& b){
        return (abs(x - b.x) < eps and abs(y - b.y) < eps);
    }

    double dist(Point b){
        return hypot(x - b.x, y - b.y);
    }

    Point rotate(double theta){
        theta = theta * pi / 180.0;
        return Point(x * cos(theta) - y * sin(theta),
                     x * sin(theta) + y * cos(theta));
    }
};

double deg2rad(double deg){
    return deg * pi / 180.0;
}

//***************************************************//


//line
class Line{
public:
    double a,b,c;
    Line(){}

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

    //another function is described outside of class
    //make standard form
    template <class T>
    Line(Point<T> p, Point<T> q){
        if(abs(p.x - q.x) < eps){
            a = 1.0;
            b = 0.0;
            c = -p.x;
        }
        else{
            double m = (q.y - p.y) / (q.x - p.x);
            a = -m;
            b = 1.0;
            c = m * p.x - p.y;
        }
    }

    bool are_parallel(Line B){
        return (abs(a - B.a) < eps and abs(b - B.b) < eps);
    }

    bool are_same(Line B){
        return (are_parallel(B) and abs(c - B.c) < eps);
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

    template <class T>
    bool are_intersect(Line B, Point<T> &p){
        if(are_parallel(B)) return false;

        p.x = (B.b * c - b * B.c) / (B.a * b - a * B.b);
        //checking vertical line
        //if one line is vertical then b=0 and
        //other line is not vertical as they are not parallel
        if(abs(b) > eps) p.y = -(a * p.x + c);
        else p.y = -(B.a * p.x + B.c);

        return true;
    }

};

template <class T>
Line points_to_line(Point<T> a, Point<T> b){
    Line L(a, b);
    return L;
}
//*************************************************//

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
//**************************************************//

//circle

//return 0 if inside, 1 for border, 2 for outside
//good choice is using all integers
template<class T>
int insideCircle(T p, T c, double r){
    double dx=p.x-c.x, dy=p.y-c.y;
    double eq=dx*dx+dy*dy;
    double rSq=r*r;

    if(eq<rSq) return 0;
    if(abs(eq-rSq)<eps) return 1;
    return 2;
}

double circumference(double r){
    return 2*pi*r;
}

double area(double r){
    return pi*r*r;
}

double arcLength(double r, double theta){
    return circumference(r)*theta/360.0;
}

//sector is the area bounded by 2 radius and arc
double sector(double r, double theta){
    return area(r)*theta/360.0;
}

/*
    Chord makes a triangle with sides chord, radius, radius.
    Chord is the opposite to theta.
    Using cosine rule,
    cos(theta)=(a^2+b^2-c^2)/2ab
    or, cos(theta) = (r^2+r^2-chord^2)/2rr
    or, 2r^2cos(theta) = 2r^2-chord^2
    or, chord^2 = 2r^2-2r^2cos(theta)
    or, chord^2 = 2r^2(1-cos(theta))
    or, chord = sqrt(2r^2(1-cos(theta)))
*/
//chord
double chordLength(double r, double theta){
    return sqrt(2*r*r*(1-cos(theta)));
}

//segment is the area bounded by chord and arc
//segment=sector-triangle with sides chord, r, r
double segment(double r, double chord){
    double s=(chord+r+r)/2;
    double triangleArea=sqrt(s*(s-chord)*(s-r)*(s-r));

    double theta=acos(1-(chord*chord/(2*r*r)));
    double sectorArea=sector(r,theta);

    return sectorArea-triangleArea;
}

int main()
{
    Point<double> a(0,0), x(0,4), b(2,0), q(-2,6), c(4,4), d(0,0);

    Line A(a,b), B(c,x);
    Line C = points_to_line(q,d);
    cout << C.a << " " << C.b << " " << C.c << endl;

    cout << A.are_parallel(B) << endl;
    cout << A.are_same(B) << endl;
    cout << A.are_intersect(B,q) << endl;
    cout << q.x << " " << q.y << endl;

    return 0;
}
