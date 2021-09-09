#include "path.h"

Path::Path(const std::vector<Waypoint> &points, double maxVelocity, double maxAcceleration, double wheelbase) 
            : vProfile(maxVelocity, maxAcceleration), wheelbase(wheelbase), pathLength(0), leftPathLength(0), rightPathLength(0) {
    // size-1 because there are points-1 splines since each spline is made from a pair
    for(int i = 0; i < points.size() - 1; ++i) {
        path.push_back(Spline(points[i], points[i+1]));
    }
}

void Path::generatePath() {
    xPoints.resize(path.size());
    yPoints.resize(path.size());

    pathLength = 0;
    leftPathLength = 0;
    rightPathLength = 0;

    std::pair<double, double> currLeftPoint;
    std::pair<double, double> currRightPoint;

    std::pair<double, double> nextLeftPoint;
    std::pair<double, double> nextRightPoint;

    path[0].getLeftRightPoint(0, wheelbase / 2., currLeftPoint, currRightPoint);

    for(size_t i = 0; i < path.size(); ++i) {
        double dt = path[i].getdt();
        size_t numReserve = size_t(1. / dt + 1.);

        xPoints[i].reserve(numReserve);
        yPoints[i].reserve(numReserve);

        leftXPoints.reserve(numReserve);
        leftYPoints.reserve(numReserve);

        rightXPoints.reserve(numReserve);
        rightYPoints.reserve(numReserve);

        for(double t = 0.; t < 1.; t += dt) {
            xPoints[i].push_back(path[i].x(t));
            yPoints[i].push_back(path[i].y(t));

            leftXPoints.push_back(currLeftPoint.first);
            leftYPoints.push_back(currLeftPoint.second);

            rightXPoints.push_back(currRightPoint.first);
            rightYPoints.push_back(currRightPoint.second);

            path[i].getLeftRightPoint(t + dt, wheelbase / 2., nextLeftPoint, nextRightPoint);

            pathLength += sqrt(pow(path[i].dxdt(t), 2) + pow(path[i].dydt(t), 2)) * dt;
            leftPathLength += sqrt(pow((nextLeftPoint.first - currLeftPoint.first) / dt, 2) + pow((nextLeftPoint.second - currLeftPoint.second) / dt, 2)) * dt;
            rightPathLength += sqrt(pow((nextRightPoint.first - currRightPoint.first) / dt, 2) + pow((nextRightPoint.second - currRightPoint.second) / dt, 2)) * dt;

            currLeftPoint = nextLeftPoint;
            currRightPoint = nextRightPoint;
        }
    }
}

bool Path::generateVelocityProfile() {
    return vProfile.generateVelocityProfile(*this);
}