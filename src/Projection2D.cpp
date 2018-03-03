#include "Classes.h"

class Projection2D {
    ///
    /// This class holds the 2D orthographic projections of a 3D object.
    ///
public:
    OrthoProjection frontview;
    OrthoProjection topview;
    int create3D();
private:
    Point determinePoint(Point, Point);
    Edge * determineEdges(Point, Point[], Point[]);
};

Point Projection2D::determinePoint(Point pfront, Point ptop) {
    ///
    /// This function extends the points from the top view and front view to give the 3D projection of the Point
    ///
}

Edge * Projection2D::determineEdges(Point vertex, Point topNeighbours[], Point frontNeighbours[]) {
    ///
    /// This function determines the edges containing the Point vertex as one of the endpoints
    /// By interpreting its neighbours from the top view and front view
    ///
}
