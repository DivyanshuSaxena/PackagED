///
/// This class is an abstraction of a real-world 3D point.
///
#include<iostream>
using namespace std;
class Point {
public:
    double x,y,z;
    Point projectPoint(double[]);
    double relativePosition(double[]);
};

///
/// This class is an abstraction of the edge of a 3D object. It consists of two endpoints (of the type Point).
///
class Edge {
public:
    Point p1,p2;
};

///
/// This class is the abstraction to represent the faces of a 3D object.
///
class Face {

public:
    void setface(Point pointarr[]){
        vertices= pointarr;
    };
    Point * vertices;
};

///
/// This class provides an abstraction for the 2D projection of a 3D object on a plane.
///
class OrthoProjection {
public:
    Point vertices[];
    Edge visibleEdges[], hiddenEdges[];
    Point * possibleNeighbours(Point);
};

///
/// This class provides an abstraction for a real world 3D object and incorporates the functions for the same. The class incorporates functions for operating upon the object
///
class Object3D {
public:
    Point vertices[];
    Edge edges[];
    Face faces[];
    int project3D(double[4]);
    Object3D rotateObject(double, double, double);
    Object3D translate(double, double, double);
    bool checkHiddenVertice(Point,double[4]);
    bool checkHiddenEdge(Edge,double[4]);
    bool rayCasting(Point point,Face polygon){
        cout << "yo"<<polygon.vertices[0].x << endl;
        int numverticesinpolygon = sizeof(polygon.vertices)/sizeof(Point);
    cout<< "num is "<< numverticesinpolygon<<endl;
    cout<<"first is "<<sizeof(polygon.vertices)<<endl;
    cout << "second is "<<sizeof(** polygon.vertices)<<endl;
    return true;
    };
};

class Wireframe {
public:
    Point vertices[];
    Edge edges[];
};
