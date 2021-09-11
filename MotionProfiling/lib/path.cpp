#include "path.h"

Path::Path(const std::vector<Waypoint> &points, double maxVelocity, double maxAcceleration, double wheelbase) 
            : vProfile(maxVelocity, maxAcceleration), wheelbase(wheelbase), pathLength(0), leftPathLength(0), rightPathLength(0) {
    // size-1 because there are points-1 splines since each spline is made from a pair
    for(int i = 0; i < points.size() - 1; ++i) {
        path.push_back(Spline(points[i], points[i+1]));
    }
}

void Path::generatePath() {
    pathLength = 0;
    leftPathLength = 0;
    rightPathLength = 0;

    leftDistances.push_back(leftPathLength);
    rightDistances.push_back(rightPathLength);

    std::pair<double, double> currLeftPoint;
    std::pair<double, double> currRightPoint;

    std::pair<double, double> nextLeftPoint;
    std::pair<double, double> nextRightPoint;

    path[0].computeLeftRightPoint(0, wheelbase / 2., currLeftPoint, currRightPoint);

    for(size_t i = 0; i < path.size(); ++i) {
        xWaypoints.push_back(path[i].x(0));
        yWaypoints.push_back(path[i].y(0));

        for(double t = 0.; t < 1.; t += path[i].getdt()) {
            xPoints.push_back(path[i].x(t));
            yPoints.push_back(path[i].y(t));

            leftXPoints.push_back(currLeftPoint.first);
            leftYPoints.push_back(currLeftPoint.second);

            rightXPoints.push_back(currRightPoint.first);
            rightYPoints.push_back(currRightPoint.second);

            path[i].computeLeftRightPoint(t + path[i].getdt(), wheelbase / 2., nextLeftPoint, nextRightPoint);

            pathLength += path[i].dDistance(t);
            leftPathLength += path[i].dDistance(currLeftPoint, nextLeftPoint);
            rightPathLength += path[i].dDistance(currRightPoint, nextRightPoint);

            leftDistances.push_back(leftPathLength);
            rightDistances.push_back(rightPathLength);

            currLeftPoint = nextLeftPoint;
            currRightPoint = nextRightPoint;
        }
    }
    
    xWaypoints.push_back(path.back().x(1));
    yWaypoints.push_back(path.back().y(1));
}

void Path::generateVelocityProfile() {
    vProfile.generateVelocityProfile(*this);
}