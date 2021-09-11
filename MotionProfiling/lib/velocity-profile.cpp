#include "path.h"

void Path::VelocityProfile::generateVelocityProfile(const Path &path) {
    pathTime = 0;

    double pLeftVelocity = 0;
    double pRightVelocity = 0;

    bool deaccelerating = false;

    times.push_back(pathTime);
    leftVelocities.push_back(pLeftVelocity);
    rightVelocities.push_back(pRightVelocity);

    size_t totalIndex = 0;
    for(size_t i = 0; i < path.path.size(); ++i) {
        for(double t = 0; t < 1.; t += path.path[i].getdt(), ++totalIndex) {
            double leftVelocity;
            double rightVelocity;

            double dLeftDistance = path.leftDistances[totalIndex+1] - path.leftDistances[totalIndex];
            double dRightDistance = path.rightDistances[totalIndex+1] - path.rightDistances[totalIndex];

            double curvature = path.path[i].curvature(t);
            bool leftOuter = path.path[i].isLeftOuter(t);

            if(leftOuter) {
                if(deaccelerating) {
                    leftVelocity = calcMinVelocity(pLeftVelocity, dLeftDistance);
                    rightVelocity = calcInnerVelocity(leftVelocity, curvature, path.wheelbase);
                } else {
                    leftVelocity = std::min(calcMaxVelocity(pLeftVelocity, dLeftDistance), maxVelocity);
                    rightVelocity = calcInnerVelocity(leftVelocity, curvature, path.wheelbase);

                    if(abs(rightVelocity) > calcMaxVelocity(abs(pRightVelocity), dRightDistance)) {
                        rightVelocity = std::min(calcMaxVelocity(pRightVelocity, dRightDistance), maxVelocity);
                        leftVelocity = calcOuterVelocity(rightVelocity, curvature, path.wheelbase);
                    }
                    
                    deaccelerating = calcStoppingDistance(leftVelocity) >= path.leftPathLength - path.leftDistances[totalIndex];
                }
            } else {
                if(deaccelerating) {
                    rightVelocity = calcMinVelocity(pRightVelocity, dRightDistance);
                    leftVelocity = calcInnerVelocity(rightVelocity, curvature, path.wheelbase);
                } else {
                    rightVelocity = std::min(calcMaxVelocity(pRightVelocity, dRightDistance), maxVelocity);
                    leftVelocity = calcInnerVelocity(rightVelocity, curvature, path.wheelbase);

                    if(abs(leftVelocity) > calcMaxVelocity(abs(pLeftVelocity), dLeftDistance)) {
                        leftVelocity = std::min(calcMaxVelocity(pLeftVelocity, dLeftDistance), maxVelocity);
                        rightVelocity = calcOuterVelocity(leftVelocity, curvature, path.wheelbase);
                    }

                    deaccelerating = calcStoppingDistance(rightVelocity) >= path.rightPathLength - path.rightDistances[totalIndex];
                }
            }

            double dTime = ((dLeftDistance + dRightDistance) / 2) / ((leftVelocity + rightVelocity) / 2);
            pathTime += dTime;

            pLeftVelocity = leftVelocity;
            pRightVelocity = rightVelocity;

            times.push_back(pathTime);
            leftVelocities.push_back(leftVelocity);
            rightVelocities.push_back(rightVelocity);
        }
    }
}

double Path::VelocityProfile::calcMaxVelocity(double pVelocity, double dDistance) {
    return sqrt(pow(pVelocity, 2) + 2 * maxAcceleration * dDistance);
}
double Path::VelocityProfile::calcMinVelocity(double pVelocity, double dDistance) {
    return sqrt(pow(pVelocity, 2) + 2 * -maxAcceleration * dDistance);
}
double Path::VelocityProfile::calcInnerVelocity(double outerVelocity, double curvature, double wheelbase) {
    if(iszero(curvature)) {
        return outerVelocity;
    }

    double turnRadius = abs(1 / curvature);
    return (2 * turnRadius * outerVelocity - wheelbase * outerVelocity) / (2 * turnRadius + wheelbase);
}
double Path::VelocityProfile::calcOuterVelocity(double innerVelocity, double curvature, double wheelbase) {
    if(iszero(curvature)) {
        return innerVelocity;
    }

    double turnRadius = abs(1 / curvature);
    return (2 * turnRadius * innerVelocity + wheelbase * innerVelocity) / (2 * turnRadius - wheelbase);
}
double Path::VelocityProfile::calcStoppingDistance(double velocity) {
    return pow(velocity, 2) / (2 * maxAcceleration);
}