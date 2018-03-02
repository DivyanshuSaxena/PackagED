#include "Classes.h"

class Projection2D {
public:
    OrthoProjection front;
    OrthoProjection top;
    int create3D();
private:
    Point determinePoint(Point, Point);
    Edge * determineEdges(Point, Point[], Point[]);
};

