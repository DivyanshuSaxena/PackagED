#include "Classes.h"
#include <Eigen/Dense>

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

bool isEqual(Point p, Point p0) {
    return (p.x==p0.x && p.y==p0.y && p.z==p0.z);
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
    for (auto i = 0; i < len; i++)
    {
        int flag = 0;
        for (auto j = 0; j < this->faces.size(); i++)
        {
            int faceVerlen = this->faces[j].vertices.size()
            vector<Point> v(faceVerlen);
            // Calculation of the vector, consisting of the projected points of the face 
            for(auto k = 0; k < faceVerlen; k++)
            {
                v.push_back(projectedVertices[this->faces[j].vertices[k]]);
            }
            if(checkHiddenVertice(projectedVertices[i],v))
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
        auto it = find_if(this->vertices.begin(), this->vertices.end(), 
                            [](const Point & p) -> bool {return (p.x==edges[i].p1.x && p.y==edges[i].p1.y && p.z==edges[i].p1.z)})
        else
        {
            for (auto j = 0; j < this->faces.size(); j++)
            {
                int faceVerlen = this->faces[j].vertices.size()
                vector<Point> v(faceVerlen);
                // Calculation of the vector, consisting of the projected points of the face 
                for (auto k = 0; k < faceVerlen; k++)
                {
                    v.push_back(projectedVertices[this->faces[j].vertices[k]]);
                }
                int flag = 0;
                if(checkHiddenEdge(this->edges[i],v))
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
    int numverticesinpolygon = sizeof(polygon.vertices)/sizeof(* (polygon.vertices));
    cout<< "num is "<< numverticesinpolygon;
    return true;
}

bool Object3D::checkHiddenVertice(Point vertex, vector<Point> face) {
    ///
    /// Function to check if the Point passed as parameter "vertex" is hidden by the passed "plane"
    ///
}

bool Object3D::checkHiddenEdge(Edge edge, vector<Point> face) {
    ///
    /// Function to evaluate if the Edge "edge", passed as parameter is hidden by the plane or not
    ///
}
