#include <iostream>
#include <vector>
#include <string.h>
#include <gtkmm.h>
#include <map>
using namespace std;

///
/// This class is an abstraction of a real-world 3D point.
///
class Point {
public:
    double x,y,z;
    string label;
    void setCoordinates(double,double,double);
    void setCoordinatesAndLabel(double,double,double,string);
    Point projectPoint(double[]);
    double relativePosition(double[]);
    int adjacencyIndex;
    friend std::ostream& operator<< (std::ostream &out, const Point &point) {
        out << "Point(" << point.x << ", " << point.y << ", " << point.z << ", " << point.label << ") ";    
        return out;
    }
    bool checkcollinear(Point *, Point *);
};

///
/// This class represents a cluster of points in their increasing distance 
/// from the viewer, in case of the projection
///
class ClusteredPoint{
public:
    vector<Point> points;
    friend std::ostream& operator<< (std::ostream &out, const ClusteredPoint &cpoint) {
        out << "Cluster(";
        for(int i = 0; i < cpoint.points.size(); i++)
            out << cpoint.points[i].label << ", ";
        out << ") ";
        return out;
    }
};

///
/// This class is an abstraction of the edge of a 3D object. It consists of two endpoints (of the type Point).
///
class Edge {
public:
    Point p1,p2;
    friend std::ostream& operator<< (std::ostream &out, const Edge &edge) {
        out << "Edge(" << edge.p1 << ", " << edge.p2 << ")";    
        return out;
    }
};

///
/// This class is an abstraction of the edge of a 2D Projection. It consists of two endpoints (of the type ClusteredPoint).
///
class Edge2D {
public:
    ClusteredPoint cp1, cp2;
    friend std::ostream& operator<< (std::ostream &out, const Edge2D &edge) {
        out << "Edge( " << edge.cp1 << ", " << edge.cp2 << " )";    
        return out;
    }
};


///
/// This class is the abstraction to represent the faces of a 3D object.
///
class Face {
public:
    vector<int> vertices;
    friend std::ostream& operator<< (std::ostream &out, const Face &face) {
        out << "Face(";
        for(int i = 0; i < face.vertices.size(); i++)
            out << face.vertices[i] << ", ";
        out << ")";
        return out;
    }
};

///
/// This class provides an abstraction for the 2D projection of a 3D object on a plane, that is calculated by the algorithm
///
class PlaneProjection {
public:
    vector<Point> vertices;
    vector<Edge> visibleEdges, hiddenEdges;
    double normal[4];
    int rotatePlane();
    friend std::ostream& operator<< (std::ostream &out, const PlaneProjection &plane) {
        out << "Vertices: ";
        for(int i = 0; i < plane.vertices.size(); i++) {
            out << plane.vertices[i] << ", ";
        }
        out << endl << "Visible Edges: ";
        for(int i = 0; i < plane.visibleEdges.size(); i++) {
            out << plane.visibleEdges[i] << ", ";
        }
        out << endl << "Hidden Edges: ";
        for(int i = 0; i < plane.hiddenEdges.size(); i++) {
            out << plane.hiddenEdges[i] << ", ";
        }
        return out;
    }
};

///
/// This class provides an abstraction for the 2D projection of a 3D object on a plane, that is supposed to be entered by user.
///
class OrthoProjection {
public:
    vector<ClusteredPoint> vertices;
    vector<Edge2D> edges;
    vector<Point> possibleNeighbours(Point);
    vector<Point> sameclusterpoints(Point);
    vector<Point> sameclusterpointsincluded(Point);
    bool isConnected(string, string);
    friend std::ostream& operator<< (std::ostream &out, const OrthoProjection &op) {
        out << "OrthoProjection: " << std::endl << "Vertices: ";
        for(int i = 0; i < op.vertices.size(); i++) {
            out << op.vertices[i] << ", ";
        }
        out << std::endl << "Edges: ";
        for(int i = 0; i < op.edges.size(); i++) {
            out << op.edges[i] << ", ";
        }
        out << endl;
        return out;
    }  
};

///
/// This class provides an abstraction for a real world 3D object and incorporates the functions for the same. The class incorporates functions for operating upon the object
///
class Object3D {
public:
    vector<Point> vertices;
    vector<Edge> edges;
    vector<Face> faces;
    PlaneProjection* project3D(double[]);
    Object3D rotateObject(double, double, double);
    Object3D translate(double, double, double);
    friend std::ostream& operator<< (std::ostream &out, const Object3D &obj) {
        out << "Vertices: ";
        for(int i = 0; i < obj.vertices.size(); i++) {
            out << obj.vertices[i] << ", ";
        }
        out << endl << "Edges: ";
        for(int i = 0; i < obj.edges.size(); i++) {
            out << obj.edges[i] << ", ";
        }
        out << endl << "Faces: ";
        for(int i = 0; i < obj.faces.size(); i++) {
            out << obj.faces[i] << ", ";
        }
        out << endl;
        return out;
    }

private:
    vector<Point> projectedVertices;
    bool checkHiddenVertice(Point,Face,double[],int);
    bool checkHiddenEdge(Edge,Face,double[],int);
    bool rayCasting(Point,vector<Point>);
};

class Wireframe {
public:
    vector<Point> vertices;
    vector<Edge> edges;
    vector<vector<int> > adjacencyMatrix;
    Wireframe* projectFrame();
    int rotateFrame(int);
    friend std::ostream& operator<< (std::ostream &out, const Wireframe &op) {
        out << "Wireframe: " << std::endl << "Vertices: ";
        for(int i = 0; i < op.vertices.size(); i++) {
            out << op.vertices[i] << ", ";
        }
        out << std::endl << "Edges: ";
        for(int i = 0; i < op.edges.size(); i++) {
            out << op.edges[i] << ", ";
        }
        out << endl;
        return out;
    }  
};

///
/// This class holds the 2D orthographic projections of a 3D object.
/// The orthographic views given by the user must be on the standard planes of reference. We
/// describe our model, assuming that: 1. Top view is taken on x-y plane 
/// 2. Front view must be taken on x-z plane
///
class Projection2D {
public:
    OrthoProjection frontview;
    OrthoProjection topview;
    OrthoProjection sideview;
    vector<Point> allpoints;
    vector<vector<int> > adjacencyMatrix;
    map<int, Point *> indextopointmap;
    map<string, Point *> labeltopointmap;

    Wireframe create3D();
    void chkif3edgesanddefthem();
private:
    void determineIntersectedEdges();
    void executeCorollary1onebyone(OrthoProjection *,OrthoProjection *, OrthoProjection *);
    void executeCorollary1();
    Point determinePoint(Point, Point);
    vector<Point> determineAllPoints();
    pair <vector<Edge>, vector<vector<int> > > determinePossibleEdges(Point, vector<Point> *,vector<Point> *);
    int numofpossibleedge();
    bool chkcollinearpossanddef();
    bool chkcollinearpossandposs();
    bool chkposshasdefinother();
    void printmatrix(vector<vector<int> >);
};

PlaneProjection* createObject(Object3D*,double[4]);
Wireframe* createProjection(Projection2D*);
int renderObject(Wireframe);
int renderProjection(OrthoProjection);
