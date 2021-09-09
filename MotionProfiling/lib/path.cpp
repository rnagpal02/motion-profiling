#include "path.h"

Path::Path(const std::vector<Waypoint> &points, double maxVelocity, double maxAcceleration, double wheelbase) 
            : wheelbase(wheelbase), vProfile(nullptr) {
    // size-1 because there are points-1 splines since each spline is made from a pair
    for(int i = 0; i < points.size() - 1; ++i) {
        path.push_back(Spline(points[i], points[i+1]));
    }

    vProfile = new VelocityProfile(path, maxVelocity, maxAcceleration, wheelbase);
}

void Path::generateGraph() {
    xPoints.resize(path.size());
    yPoints.resize(path.size());

    for(size_t i = 0; i < path.size(); ++i) {
        double dt = path[i].getdt();
        size_t numReserve = size_t(1. / dt + 1.);

        std::pair<double, double> left;
        std::pair<double, double> right;

        xPoints[i].reserve(numReserve);
        yPoints[i].reserve(numReserve);

        leftXPoints.reserve(numReserve);
        leftYPoints.reserve(numReserve);

        rightXPoints.reserve(numReserve);
        rightYPoints.reserve(numReserve);

        for(double t = 0.; t <= 1.; t += dt) {
            xPoints[i].push_back(path[i].x(t));
            yPoints[i].push_back(path[i].y(t));

            path[i].getLeftRightPoint(t, wheelbase / 2., left, right);
            leftXPoints.push_back(left.first);
            leftYPoints.push_back(left.second);

            rightXPoints.push_back(right.first);
            rightYPoints.push_back(right.second);
        }
    }
}

bool Path::generateVelocityProfile() {
    for(Spline s : path) {
        s.computePathDistance(wheelbase / 2.);
    }

    if (!vProfile || !vProfile->generateVelocityProfile()) {
        return false;
    }

    return true;
}