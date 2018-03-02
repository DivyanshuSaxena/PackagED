#include "Classes.h"

class Object3D {
public:
    Point vertices[];
    Edge edges[];
    Face faces[];
    int project3D(double[4]);
private:
    bool checkHiddenVertice(Point,double[4]);
    bool checkHiddenEdge(Edge,double[4]);
    bool rayCasting(Point,Face);
};

int Object3D::project3D(double projectionPlane[4]) {
    // General Function to project the current 3D object onto the projection plane passed as parameter "projectionPlane"
}

bool Object3D::rayCasting(Point point, Face polygon) {
    // Function that returns if the Point "point" lies within the polygon formed by the Face "polygon", passed as parameter.
}

bool Object3D::checkHiddenVertice(Point vertex, double plane[4]) {
    // Function to check if the Point passed as parameter "vertex" is hidden by the passed "plane"
}

bool Object3D::checkHiddenEdge(Edge edge, double plane[4]) {
    // Function to evaluate if the Edge "edge", passed as parameter is hidden by the plane or not
}
