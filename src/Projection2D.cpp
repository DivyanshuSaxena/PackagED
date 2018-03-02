#include "Classes.h"

class Projection2D {
public:
    OrthoProjection frontview;
    OrthoProjection topview;
    int create3D();
private:
    Point determinePoint(Point, Point);
    Edge * determineEdges(Point, Point[], Point[]);
};
