#include "path.h"

Path::Path(const std::vector<Waypoint> &points, double dt) : dt(dt) {
    // size-1 because there are points-1 splines since each spline is made from a pair
    for(int i = 0; i < points.size() - 1; ++i) {
        path.push_back(Spline(points[i], points[i+1]));
    }
}

void Path::generateGraph() {
    for(auto spline : path) {
        for(double t = 0; t <= 1; t += dt) {
            x.push_back(spline.getX(t));
            y.push_back(spline.getY(t));
        }
    }
}