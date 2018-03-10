#include <iostream>
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
    Point trythis;
    trythis.x = 1.3;
    trythis.y = 2.3;
    trythis.z = 3.2;
    double thisarr [4] ={5,2,3,4};
    Point newpoint = trythis.projectPoint(thisarr);
    cout << newpoint.x << " " << newpoint.y << " " << newpoint.z << "\n";
    Object3D threedobj;
    Face testface;

    Point v [1] = {trythis};
    * testface.vertices = (new  Point);
    threedobj.rayCasting(trythis,testface);
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
