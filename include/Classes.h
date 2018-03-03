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
    Point vertices[];
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

class Wireframe {
public:
    Point vertices[];
    Edge edges[];
};
