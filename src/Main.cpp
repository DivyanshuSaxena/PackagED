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
	  MatrixXd m(2,2);
	  m(0,0) = 3;
	  m(1,0) = 2.5;
	  m(0,1) = -1;
	  m(1,1) = m(1,0) + m(0,1);
	  std::cout << m << std::endl;
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
