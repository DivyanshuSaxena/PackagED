#include <iostream>
#include <vector>
using namespace std;

///
/// This class is an abstraction of a real-world 3D point.
///
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
    vector<int> vertices;
};

///
/// This class provides an abstraction for the 2D projection of a 3D object on a plane.
///
class OrthoProjection {
public:
    vector<Point> vertices;
    vector<Edge> visibleEdges, hiddenEdges;
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
    OrthoProjection project3D(double[]);
    Object3D rotateObject(double, double, double);
    Object3D translate(double, double, double);
private:
    bool checkHiddenVertice(Point,vector<Point>);
    bool checkHiddenEdge(Edge,vector<Point>);
    bool rayCasting(Point,vector<Point>);
};

class Wireframe {
public:
    vector<Point> vertices;
    vector<Edge> edges;
};
