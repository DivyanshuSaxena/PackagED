#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

///
/// This class is an abstraction of a real-world 3D point.
///
class Point {
public:
    double x,y,z;
    string label;
    void setCoordinates(double,double,double);
    void setCoordinatesAndLabel(double,double,double,string);
    Point projectPoint(double[]);
    double relativePosition(double[]);

};
class ClusteredPoint{
public:
    vector<Point> points;
};


///
/// This class is an abstraction of the edge of a 3D object. It consists of two endpoints (of the type Point).
///
class Edge {
public:
    Point p1,p2;
};

class Edge2D {
public:
    ClusteredPoint cp1, cp2;
};


///
/// This class is the abstraction to represent the faces of a 3D object.
///
class Face {
public:
    vector<int> vertices;
};

///
/// This class provides an abstraction for the 2D projection of a 3D object on a plane, that is calculated by the algorithm
///
class PlaneProjection {
public:
    vector<Point> vertices;
    vector<Edge> visibleEdges, hiddenEdges;
};

///
/// This class provides an abstraction for the 2D projection of a 3D object on a plane, that is supposed to be entered by user.
///
class PlaneProjection {
public:
    vector<Point> vertices;
    vector<Edge> hiddenEdges,visibleEdges;
};

class OrthoProjection {
public:
    vector<ClusteredPoint> vertices;
    vector<Edge2D> edges;
    vector<Point> possibleNeighbours(Point);
};

///
/// This class provides an abstraction for a real world 3D object and incorporates the functions for the same. The class incorporates functions for operating upon the object
///
class Object3D {
public:
    vector<Point> vertices;
    vector<Edge> edges;
    vector<Face> faces;
    PlaneProjection project3D(double[]);
    Object3D rotateObject(double, double, double);
    Object3D translate(double, double, double);
<<<<<<< HEAD
private:
    vector<Point> projectedVertices;
    bool checkHiddenVertice(Point,Face,double[],int);
    bool checkHiddenEdge(Edge,Face,double[],int);
=======
//private:
    bool checkHiddenVertice(Point,vector<Point>,double[]);
    bool checkHiddenEdge(Edge,vector<Point>,double[]);
>>>>>>> c5a7f7b1c2f25579968fdbc031a5624d5f854bab
    bool rayCasting(Point,vector<Point>);
};

class Wireframe {
public:
    vector<Point> vertices;
    vector<Edge> edges;
};

///
/// This class holds the 2D orthographic projections of a 3D object.
/// The orthographic views given by the user must be on the standard planes of reference. We
//describe our model, assuming that: 1. Top view is taken on x-y plane 
// 2. Front view must be taken on x-z plane
///
class Projection2D {
public:
    OrthoProjection frontview;
    OrthoProjection topview;
    Wireframe create3D();
//private:
    Point determinePoint(Point, Point);
    vector<Point> determineAllPoints();
    vector<Edge> determineEdges(Point, Point[], Point[]);
};
