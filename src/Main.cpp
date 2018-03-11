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
    Point trythis;
    trythis.x = 1.3;
    trythis.y = 2.3;
    trythis.z = 3.2;
    double thisarr [4] ={5,2,3,4};
    Point newpoint = trythis.projectPoint(thisarr);
    cout << newpoint.x << " " << newpoint.y << " " << newpoint.z << endl;
    Object3D obj;
    obj.vertices.push_back(trythis);
    obj.project3D(thisarr);
    //lets define square
    Point v1,v2,v3,v4;
    v1.setCoordinates(1,1,0);
    v2.setCoordinates(-1,1,0);
    v3.setCoordinates(-1,-1,0);
    v4.setCoordinates(1,-1,0); 
    vector<Point> square;
    square.push_back(v1);
    square.push_back(v2);
    square.push_back(v3);
    square.push_back(v4);
    Point pointofconsideration;
    pointofconsideration.setCoordinates(0.5,0.5,0);
    cout<< "kuch chal"<<endl;
    cout<< obj.rayCasting(pointofconsideration,square)<<endl;
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
