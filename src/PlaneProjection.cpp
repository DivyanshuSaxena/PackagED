#include "Classes.h"
#include <Eigen/Dense>
using namespace Eigen;

int PlaneProjection::rotatePlane() {
    ///
    /// Function to rotate the PlaneProjection instance so as to get the normal parallel to z-axis
    ///
    Vector3d zaxis(0,0,1);
    Vector3d norml(normal[0],normal[1],normal[2]);
    // cout << "Norml: " << endl << norml << endl;
    double costheta = zaxis.dot(norml);
    double sintheta = zaxis.cross(norml).norm();
    if(costheta < 0) {
        costheta = 0-costheta;
    }
    Vector3d axis = zaxis.cross(norml);
    Matrix3d id = Matrix3d::Identity();
    // cout << "Identity Matrix: " << endl << id << endl;
    Matrix3d ux;
    ux << 0, -axis.z(), axis.y(),
                axis.z(), 0, -axis.x(),
                -axis.y(), axis.x(), 0;
    // cout << "UX Matrix: " << endl << ux << endl;
    Matrix3d tensorprod = axis*axis.transpose();
    // cout << "Tensor Product Matrix: " << endl << tensorprod << endl;
    Matrix3d rotmax = costheta*id + sintheta*ux + (1-costheta)*tensorprod;
    for(auto i = 0; i < visibleEdges.size(); i++) {
        Vector3d point1(visibleEdges[i].p1.x,visibleEdges[i].p1.y,visibleEdges[i].p1.z);
        Vector3d point2(visibleEdges[i].p2.x,visibleEdges[i].p2.y,visibleEdges[i].p2.z);
        point1 = rotmax*point1;
        point2 = rotmax*point2;
        visibleEdges[i].p1.x = point1.x();
        visibleEdges[i].p1.y = point1.y();
        visibleEdges[i].p1.z = point1.z();
        visibleEdges[i].p2.x = point2.x();
        visibleEdges[i].p2.y = point2.y();
        visibleEdges[i].p2.z = point2.z();
    }
    for(auto i = 0; i < hiddenEdges.size(); i++) {
        Vector3d point1(hiddenEdges[i].p1.x,hiddenEdges[i].p1.y,hiddenEdges[i].p1.z);
        Vector3d point2(hiddenEdges[i].p2.x,hiddenEdges[i].p2.y,hiddenEdges[i].p2.z);
        point1 = rotmax*point1;
        point2 = rotmax*point2;
        hiddenEdges[i].p1.x = point1.x();
        hiddenEdges[i].p1.y = point1.y();
        hiddenEdges[i].p1.z = point1.z();
        hiddenEdges[i].p2.x = point2.x();
        hiddenEdges[i].p2.y = point2.y();
        hiddenEdges[i].p2.z = point2.z();
    }
}