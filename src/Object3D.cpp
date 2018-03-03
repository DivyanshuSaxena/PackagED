#include "Classes.h"
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
private:
    bool checkHiddenVertice(Point,double[4]);
    bool checkHiddenEdge(Edge,double[4]);
    bool rayCasting(Point,Face);
};

Object3D Object3D::rotateObject(double aboutx, double abouty, double aboutz) {
    ///
    /// Returns a new 3D Object with the rotated coordinates, obtained by rotating the current object by the angles "aboutz" about the Z-axis, by "aboutx" about the X-axis and by "abouty" about the Y-axis
    ///
}

Object3D Object3D::translate(double x, double y, double z) {
    ///
    /// This function returns a new Object3D instance, which is obtained by translating the current object by the distances, specified in the parameters
    ///
}

int Object3D::project3D(double projectionPlane[4]) {
    ///
    /// General Function to project the current 3D object onto the projection plane passed as parameter "projectionPlane"
    ///
}

bool Object3D::rayCasting(Point point, Face polygon) {
    ///
    /// Function that returns if the Point "point" lies within the polygon formed by the Face "polygon", passed as parameter.
    ///
}

bool Object3D::checkHiddenVertice(Point vertex, double plane[4]) {
    ///
    /// Function to check if the Point passed as parameter "vertex" is hidden by the passed "plane"
    ///
}

bool Object3D::checkHiddenEdge(Edge edge, double plane[4]) {
    ///
    /// Function to evaluate if the Edge "edge", passed as parameter is hidden by the plane or not
    ///
}
