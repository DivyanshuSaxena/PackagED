#include "Classes.h"
#include <Eigen/Dense>
using namespace Eigen;

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

PlaneProjection Object3D::project3D(double projectionPlane[4]) {
    ///
    /// General Function to project the current 3D object onto the projection plane passed as parameter "projectionPlane"
    ///
    int len = this->vertices.size();
    // vector<Point> projectedVertices(len); --------Remove
    vector<bool> isHidden(len);
    vector<bool> isHiddenEdge(len);
    // Iteration to find all the projected vertices
    for (auto i = 0; i < len; i++) {
        this->projectedVertices.push_back(this->vertices[i].projectPoint(projectionPlane));
    }
    cout << projectedVertices[0].x; // --------Remove
    // Now, we check if any of the vertices is hidden or not
    for (int i = 0; i < len; i++) {
        int flag = 0;
        for (auto j = 0; j < this->faces.size(); i++) {
            if(checkHiddenVertice(vertices[i],faces[j],projectionPlane,0))
            {
                flag = 1;
                break;
            }
        }
        if(flag==1)
            isHidden.push_back(true);
        else
            isHidden.push_back(false);
    }
    // Next, we check for each edge, if it is hidden or not
    /* Note: If a part of an edge is hidden then the edge is replaced by the first part 
       and the remaining part is added in the edges vector of the Object3D object */
    for (auto i = 0; i < this->edges.size(); i++) {
        Point p1 = edges[i].p1;
        Point p2 = edges[i].p2;
        auto it1 = find_if(this->vertices.begin(), this->vertices.end(), 
            [p1](Point p) -> bool {return (p.x==p1.x && p.y==p1.y && p.z==p1.z);});
        auto it2 = find_if(this->vertices.begin(), this->vertices.end(), 
            [p2](Point p) -> bool {return (p.x==p2.x && p.y==p2.y && p.z==p2.z);});
        int index1,index2;
        if(it1 != vertices.end())
            index1 = distance(vertices.begin(),it1);
        if(it2 != vertices.end())
            index2 = distance(vertices.begin(),it2);
        if(isHidden[index1] && isHidden[index2])
            isHiddenEdge.push_back(true);
        else {
            int flag = 0;   
            for (int j = 0; j < this->faces.size(); j++) {
                if(checkHiddenEdge(this->edges[i],faces[j],projectionPlane,i))
                {
                    flag = 1;
                    break;
                }
            }
            if(flag==1)
                isHiddenEdge.push_back(true);
            else
                isHiddenEdge.push_back(false);
        }
    }
    // The vectors isHidden and isHiddenEdge store whether or not a point/edge is hidden.
    // This can be used to generate an OrthoProjection object that can be returned from this function.
    PlaneProjection projection;
    for (auto i = 0; i < projectedVertices.size(); i++) {
        projection.vertices.push_back(projectedVertices[i]);
    }
    for (auto i = 0; i < this->edges.size(); i++) {
        if(isHiddenEdge[i])
            projection.hiddenEdges.push_back(this->edges[i]);
        else
            projection.visibleEdges.push_back(this->edges[i]);
    }
    return projection;
}

int countIntersections(Vector3d avertice,Vector3d bvertice,Vector3d dvertice,Vector3d evertice,Vector3d linevector){
    int retValue = 0;
    Vector3d zerovector(0,0,0);
    Vector3d abvector = bvertice - avertice;
    Vector3d acvector = linevector;
    Vector3d advector = dvertice - avertice;
    Vector3d aevector = evertice - avertice;
    Vector3d t1 = abvector.cross(acvector);
    Vector3d t2 = advector.cross(acvector);
    Vector3d t3 = abvector.cross(advector);
    Vector3d t6 = aevector.cross(acvector);
    double t4 = t1.dot(t2);
    double t5 = t1.dot(t3);
    double t7 = t6.dot(t2);
    double abdotac = abvector.dot(acvector);
    if(t1==zerovector || t2==zerovector){
        // Do Nothing
    }else if((t4<=0) && (t5>=0)){
        retValue = 1;
    }
    if(t1==zerovector && abdotac>0){
        if(t7<=0)
            retValue = 2;
        else
            retValue = 3;
    }
    return retValue;
}

Vector3d intersectLines(Point a,Point b,Vector3d c) {
    Vector3d retVal;
    Vector3d av(a.x,a.y,a.z);
    Vector3d bv(b.x,b.y,b.z);
    retVal = av + ((c-av).dot(bv-av))*(bv-av);
    return retVal;
}

bool Object3D::rayCasting(Point point, vector<Point> polygon) {
    ///
    /// Function that returns if the Point "point" lies within the polygon formed by the Face "polygon", passed as parameter.
    ///
    int numverticesinpolygon = polygon.size();
    cout<< "num of points in polygon is "<< numverticesinpolygon<<endl;
    Vector3d avertice;
    avertice << point.x, point.y, point.z;
    int numintersections = 0;
    Vector3d zerovector(0,0,0);
    Vector3d icap(1,0,0);
    Vector3d jcap(0,1,0);
    Vector3d startone;
    startone << polygon[0].x, polygon[0].y, polygon[0].z;
    Vector3d secondone;
    secondone << polygon[1].x, polygon[1].y, polygon[1].z;
    Vector3d thirdone;
    thirdone << polygon[2].x, polygon[2].y, polygon[2].z;
    Vector3d firstvector = secondone-startone;
    Vector3d secondvector = thirdone-secondone;
    Vector3d perpendicular = firstvector.cross(secondvector);
    Vector3d linevector = perpendicular.cross(icap);

    double checkzero = linevector.dot(linevector);
    if(checkzero==0){
        linevector = perpendicular.cross(jcap);
    }
    // Vector3d linevector(1,1,0);
    int i=0;
    for(auto it= polygon.begin();it!=polygon.end();it++){
        Point thisone = *it;
        Point nextone,prevone;
        if(i==numverticesinpolygon-1){
            prevone = *(it-1);
            nextone = polygon.front();
        }else if(i==0){
            prevone = polygon.back();
            nextone = *(it+1);
        }else{
            prevone = *(it-1);
            nextone = *(it+1);
        }
        //Point nextone = *(it + 1);
        Vector3d bvertice;
        bvertice << thisone.x, thisone.y, thisone.z;
        Vector3d dvertice;
        dvertice << nextone.x,nextone.y, nextone.z;
        Vector3d evertice;
        evertice << prevone.x, prevone.y, prevone.z;
        int ci = countIntersections(avertice,bvertice,dvertice,evertice,linevector);
        if(ci==0){
            // Do Nothing
        }else if(ci==1 || ci==2){
            numintersections = numintersections +1;
        }else if(ci==3){
            numintersections = numintersections + 2;            
        }
        i++;
    }
    cout<< "numintersections is "<< numintersections<<endl;
    if(numintersections%2==1){
        return true;
    }else{
        return false;
    }
}

bool Object3D::checkHiddenVertice(Point vertex, Face face, double plane[4], int predicate) {
    ///
    /// Function to check if the Point passed as parameter "vertex" is hidden by the face, 
    /// which is passed in the parameter "face", the projection being taken on the plane "plane"
    ///
    bool retValue = false;
    Vector3d point1(vertices[face.vertices[0]].x,vertices[face.vertices[0]].y,vertices[face.vertices[0]].z);
    Vector3d point2(vertices[face.vertices[1]].x,vertices[face.vertices[1]].y,vertices[face.vertices[1]].z);
    Vector3d point3(vertices[face.vertices[2]].x,vertices[face.vertices[2]].y,vertices[face.vertices[2]].z);
    Vector3d dir1 = (point3-point1);
    Vector3d dir2 = (point2-point1);
    Vector3d normal = dir1.cross(dir2);
    double facePlane[4] = {normal.x(),normal.y(),normal.z(),normal.dot(point1)};
    vector<Point> faceProject;
    for (int i = 0; i < face.vertices.size(); i++) {
        faceProject.push_back(projectedVertices[face.vertices[i]]);
    }
    Point projectedVertex = vertex.projectPoint(plane);
    if(rayCasting(projectedVertex,faceProject)) {
        if(predicate==0) {
            if(vertex.relativePosition(facePlane)*projectedVertex.relativePosition(facePlane) >= 0)
                retValue = false;
            else
                retValue = true;
        }else{
            if(vertex.relativePosition(facePlane)*projectedVertex.relativePosition(facePlane) > 0)
                retValue = false;
            else
                retValue = true;
        }
    }
    return retValue;
}

bool Object3D::checkHiddenEdge(Edge edge, Face face, double plane[4], int index) {
    ///
    /// Function to evaluate if the Edge "edge", passed as parameter is hidden by the face, 
    /// whose projection on the plane "plane" is passed as argument "face"
    ///
    bool retValue = false;
    Point projectp1 = edge.p1.projectPoint(plane);
    Point projectp2 = edge.p2.projectPoint(plane);
    vector<Point> faceProject;
    for (int i = 0; i < face.vertices.size(); i++) {
        faceProject.push_back(projectedVertices[face.vertices[i]]);
    }
    if(rayCasting(projectp1,faceProject)) {
        if(checkHiddenVertice(edge.p1,face,plane,1)) {
            // Evaluate the point of intersection of edge with the polygon faceProject
            Vector3d avertice(edge.p1.x,edge.p1.y,edge.p1.z);
            Vector3d linevector(edge.p2.x-edge.p1.x,edge.p2.y-edge.p1.y,edge.p2.z-edge.p1.z);
            vector<Vector3d> intersections;
            vector<Point> polygon;
            for(int i = 0; i < face.vertices.size(); i++) {
                polygon.push_back(this->projectedVertices[face.vertices[i]]);
            }
            int i=0, numverticesinpolygon=polygon.size();
            for(auto it= polygon.begin();it!=polygon.end();it++){
                Point thisone = *it;
                Point nextone,prevone;
                if(i==numverticesinpolygon-1){
                    prevone = *(it-1);
                    nextone = polygon.front();
                }else if(i==0){
                    prevone = polygon.back();
                    nextone = *(it+1);
                }else{
                    prevone = *(it-1);
                    nextone = *(it+1);
                }
                //Point nextone = *(it + 1);
                Vector3d bvertice;
                bvertice << thisone.x, thisone.y, thisone.z;
                Vector3d dvertice;
                dvertice << nextone.x,nextone.y, nextone.z;
                Vector3d evertice;
                evertice << prevone.x, prevone.y, prevone.z;
                int ci = countIntersections(avertice,bvertice,dvertice,evertice,linevector);
                if(ci==2 || ci==3){
                    intersections.push_back(bvertice);
                }else if(ci==1){
                    // Intersects (bvertice,dvertice) in the middle somewhere  
                    Vector3d intersection = intersectLines(edge.p1,edge.p2,bvertice);
                    intersections.push_back(intersection);
                }
                i++;
            }
            // All intersections of the edge have been taken with the face, and are stored in intersections
            Vector3d closestIntersection;
            if(intersections.size()==1){
                closestIntersection = intersections[0];
            }else if(intersections.size()!=0){
                closestIntersection = *min_element(intersections.begin(),intersections.end(),
                [avertice] (Vector3d v1, Vector3d v2) -> bool {return (avertice-v1).norm()<(avertice-v2).norm();});
            }
            // The vector closestIntersection holds the closest point of intersection, from p1
            Edge segment;
            segment.p1.setCoordinates(closestIntersection.x(),closestIntersection.y(),closestIntersection.z());
            segment.p2.setCoordinates(edge.p2.x,edge.p2.y,edge.p2.z); 
            edge.p2.setCoordinates(closestIntersection.x(),closestIntersection.y(),closestIntersection.z());
            this->edges.insert(this->edges.begin(),index+1,segment);
            retValue = false;
        }else{
            if(checkHiddenVertice(edge.p2,face,plane,0)) {
                retValue = true;
            }else{
                retValue = false;
            }
        }
    }
    return retValue;
}

// int faceVerlen = this->faces[j].vertices.size();
// vector<Point> v(faceVerlen);
// // Calculation of the vector, consisting of the projected points of the face 
// for (auto k = 0; k < faceVerlen; k++)
// {
//     v.push_back(vertices[this->faces[j].vertices[k]]);
// }