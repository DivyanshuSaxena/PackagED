#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <gtkmm.h>
#include <Eigen/Dense>
#include "Classes.h"


using namespace std;
using Eigen::MatrixXd;

Object3D createObject();
OrthoProjection createProjection();
int renderObject(Wireframe);
int renderProjection(OrthoProjection);

int main() {
    /// 
    /// The main function shall be responsible for calling various other functions and instantiating the classes for using their functions cop290
    ///
    double thisarr [4] ={0,1,0,0};
    Object3D obj;
    Point v1,v2,v3,v4,v5;
    v1.setCoordinates(2,2,0);
    v2.setCoordinates(2,1,0);
    v3.setCoordinates(1,1,0);
    v4.setCoordinates(2,1,1); 
    v5.setCoordinates(1,1,1);
    obj.vertices.push_back(v1);
    obj.vertices.push_back(v2);
    obj.vertices.push_back(v3);
    obj.vertices.push_back(v4);
    obj.vertices.push_back(v5);
    Edge e1,e2,e3,e4,e5,e6,e7,e8;
    e1.p1 = v1; e1.p2 = v2; e2.p1 = v1; e2.p2 = v3;
    e3.p1 = v1; e3.p2 = v4; e4.p1 = v1; e4.p2 = v5;
    e5.p1 = v2; e5.p2 = v4; e6.p1 = v2; e6.p2 = v3;
    e7.p1 = v4; e7.p2 = v5; e8.p1 = v3; e8.p2 = v5;
    obj.edges.push_back(e1);
    obj.edges.push_back(e2);
    obj.edges.push_back(e3);
    obj.edges.push_back(e4);
    obj.edges.push_back(e5);
    obj.edges.push_back(e6);
    obj.edges.push_back(e7);
    obj.edges.push_back(e8);
    Face f1,f2,f3,f4,f5;
    f1.vertices.push_back(0);
    f1.vertices.push_back(1);
    f1.vertices.push_back(2);
    f2.vertices.push_back(0);
    f2.vertices.push_back(1);
    f2.vertices.push_back(3);
    f3.vertices.push_back(0);
    f3.vertices.push_back(3);
    f3.vertices.push_back(4);
    f4.vertices.push_back(0);
    f4.vertices.push_back(2);
    f4.vertices.push_back(4);
    f5.vertices.push_back(1);
    f5.vertices.push_back(2);
    f5.vertices.push_back(3);
    f5.vertices.push_back(4);
    obj.faces.push_back(f1);
    obj.faces.push_back(f2);
    obj.faces.push_back(f3);
    obj.faces.push_back(f4);
    obj.faces.push_back(f5);
    PlaneProjection p = obj.project3D(thisarr);
    cout << "Projection: " << p << endl;
}

Object3D createObject() {
    ///
    /// This function shall make use of the gtk library, to interactively take input from the user and returns the 3D object created from the user input
    ///
}

OrthoProjection createProjection() {
    ///
    /// This function shall make use of the gtk library, to interactively take input from the user, to form a 2D projection and returns the Projection created from the user input
    ///
}
int renderObject(Wireframe frame) {
    ///
    /// This function shall make use of opengl library to render the object, from the Wireframe instance passed in parameter.
    ///
}

int renderProjection(OrthoProjection projection) {
    ///
    /// This function shall make use of opengl library to render the object, from the OrthoProjection instance passed in parameter.
    ///
}
