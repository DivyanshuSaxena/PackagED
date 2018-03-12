#include<iostream>
using namespace std;
#include <Eigen/Dense>
#include "Classes.h"

void Point::setCoordinates(double t1, double t2, double t3){
	x=t1;
	y=t2;
	z=t3;
}

void Point::setCoordinatesAndLabel(double t1,double t2,double t3,string s){
	x=t1;
	y=t2;
	z=t3;
	label = s;
	//cout<< "label is this "	<< label <<endl;
} 

Point Point::projectPoint(double projectionPlane[]) {
    ///
    /// Function to give the projection of the current calling object on the projection plane passed in parameters as "projectionPlane"
    ///
    double a = projectionPlane[0];
	double b = projectionPlane[1];
	double c = projectionPlane[2];
	double d = projectionPlane[3];
	double t =((d-(a*x+b*y+c*z))/(a*a+b*b+c*c));
	Point projectedpoint;
	projectedpoint.x = (x+a*t);
	projectedpoint.y = (y+b*t);
	projectedpoint.z = (z+c*t);
	return projectedpoint;
}

double Point::relativePosition(double plane[]) {
    ///
    /// Function to calculate the relative position of the current calling object w.r.t the passed parameter "plane"
    ///
    double a = plane[0];
	double b = plane[1];
	double c = plane[2];
	double d = plane[3];
	double t = ((a*x+b*y+c*z-d)/(a*a+b*b+c*c));
	return t;
}
