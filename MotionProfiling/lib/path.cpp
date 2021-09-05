#include "path.h"

Path::Path(const std::vector<Waypoint> &points, double dt) : dt(dt) {
    // size-1 because there are points-1 splines since each spline is made from a pair
    for(int i = 0; i < points.size() - 1; ++i) {
        path.push_back(Spline(points[i], points[i+1]));
    }
}

void Path::generateGraph() {
    xPoints.resize(path.size());
    yPoints.resize(path.size());
    
    for(size_t i = 0; i < path.size(); ++i) {
        xPoints[i].reserve(size_t(1. / dt + 1.));
        yPoints[i].reserve(size_t(1. / dt + 1.));
        for(double t = 0.; t <= 1.; t += dt) {
            xPoints[i].push_back(path[i].getX(t));
            yPoints[i].push_back(path[i].getY(t));
        }
    }
}