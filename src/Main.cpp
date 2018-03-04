#include <GL/glut.h>
#include "Classes.h"

Object3D createObject();
OrthoProjection createProjection();
int renderObject(Wireframe);
int renderProjection(OrthoProjection);

int main() {
    ///
    /// The main function shall be responsible for calling various other functions and instantiating the classes for using their functions
    ///
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
