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

OrthoProjection Object3D::project3D(double projectionPlane[4]) {
    ///
    /// General Function to project the current 3D object onto the projection plane passed as parameter "projectionPlane"
    ///
    int len = this->vertices.size();
    vector<Point> projectedVertices(len);
    vector<bool> isHidden(len);
    vector<bool> isHiddenEdge(len);
    // Iteration to find all the projected vertices
    for (auto i = 0; i < len; i++)
    {
        projectedVertices.push_back(this->vertices[i].projectPoint(projectionPlane));
    }
    cout << projectedVertices[0].x;
    // Now, we check if any of the vertices is hidden or not
    for (int i = 0; i < len; i++)
    {
        int flag = 0;
        for (auto j = 0; j < this->faces.size(); i++)
        {
            int faceVerlen = this->faces[j].vertices.size();
            vector<Point> v(faceVerlen);
            // Calculation of the vector, consisting of the projected points of the face 
            for(auto k = 0; k < faceVerlen; k++)
            {
                v.push_back(projectedVertices[this->faces[j].vertices[k]]);
            }
            if(checkHiddenVertice(projectedVertices[i],v,projectionPlane))
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
    for (auto i = 0; i < this->edges.size(); i++)
    {
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
        else
        {
            int flag = 0;   
            for (int j = 0; j < this->faces.size(); j++)
            {
                int faceVerlen = this->faces[j].vertices.size();
                vector<Point> v(faceVerlen);
                // Calculation of the vector, consisting of the projected points of the face 
                for (auto k = 0; k < faceVerlen; k++)
                {
                    v.push_back(projectedVertices[this->faces[j].vertices[k]]);
                }
                if(checkHiddenEdge(this->edges[i],v,projectionPlane))
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
    OrthoProjection projection;
    for (auto i = 0; i < projectedVertices.size(); i++)
    {
        projection.vertices.push_back(projectedVertices[i]);
    }
    for (auto i = 0; i < this->edges.size(); i++)
    {
        if(isHiddenEdge[i])
            projection.hiddenEdges.push_back(this->edges[i]);
        else
            projection.visibleEdges.push_back(this->edges[i]);
    }
    return projection;
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
    // cout << "zero vector is "<<endl;
    // cout << zerovector <<endl;
    Vector3d icap(1,0,0);
    //icap << 1,0,0;
    Vector3d jcap(0,1,0);
    //jcap << 0,1,0;
    Vector3d startone;
    startone << polygon[0].x, polygon[0].y, polygon[0].z;
    Vector3d secondone;
    secondone << polygon[1].x, polygon[1].y, polygon[1].z;
    Vector3d thirdone;
    thirdone << polygon[2].x, polygon[2].y, polygon[2].z;
    Vector3d firstvector = secondone-startone;
    Vector3d secondvector = thirdone-secondone;
    Vector3d perpendicular = firstvector.cross(secondvector);
    //cout << "perpendicular is "<<endl;
    // cout << perpendicular << endl;
    Vector3d linevector = perpendicular.cross(icap);
    double checkzero = linevector.dot(linevector);
    if(checkzero==0){
        linevector = perpendicular.cross(jcap);
    }
    // cout <<"linevector is" <<endl;
    // cout<< linevector<<endl;
    int i=0;
    for(auto it= polygon.begin();it!=polygon.end();it++){
        Point thisone = *it;
        Point nextone;
        if(i==numverticesinpolygon-1){
            nextone = polygon.front();
        }else{
            nextone = *(it+1);
        }
        //Point nextone = *(it + 1);
        Vector3d bvertice;
        bvertice << thisone.x, thisone.y, thisone.z;
        Vector3d dvertice;
        dvertice << nextone.x,nextone.y, nextone.z;
        Vector3d abvector = bvertice - avertice;
        Vector3d acvector = linevector;
        Vector3d advector = dvertice - avertice;
        Vector3d t1 = abvector.cross(acvector);
        Vector3d t2 = advector.cross(acvector);
        Vector3d t3 = abvector.cross(advector);
        double t4 = t1.dot(t2);
        double t5 = t1.dot(t3);
        double t6 = t2.dot(t3);
        if(t1==zerovector && t2==zerovector){
            numintersections = numintersections +2;
        }else if(t1==zerovector || t2==zerovector){
            if(t5>0){
                numintersections = numintersections+1;
            }else if(t5==0 && t6<0){
                numintersections = numintersections+1;
            }
        }else{
            if((t4<=0) && (t5>=0)){
                numintersections = numintersections +1;
            }
        }
        //cout<< "numintersectionsinpolygon is "<<numintersections<< "i is "<<i<< "t4 and t5 are "<< t4<< " "<< t5<<endl;
        i++;
    }
    if(numintersections%2==1){
        cout<<"inside hai"<<endl;
        return true;
    }else{
        cout<< "outside hai"<<endl;
        return false;
    }
}

bool Object3D::checkHiddenVertice(Point vertex, vector<Point> face, double plane[4]) {
    ///
    /// Function to check if the Point passed as parameter "vertex" is hidden by the passed "plane"
    ///
    bool retValue = false;
    if(rayCasting(vertex,face))
    {
        Point projectedVertex = vertex.projectPoint(plane);
        if(vertex.relativePosition(plane)*projectedVertex.relativePosition(plane) >= 0)
            retValue = false;
        else
            retValue = true;
    }
    return retValue;
}

bool Object3D::checkHiddenEdge(Edge edge, vector<Point> face, double plane[4]) {
    ///
    /// Function to evaluate if the Edge "edge", passed as parameter is hidden by the plane or not
    ///
}
