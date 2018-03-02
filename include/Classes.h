class Point {
public:
    double x,y,z;
    Point projectPoint(double[]);
    double relativePosition(double[]);
};

class Edge {
public:
    Point p1,p2;
};

class Face {
public:
    Point vertices[];
};

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
