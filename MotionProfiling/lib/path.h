#ifndef PATH_H
#define PATH_H

#include <vector>

#include "spline.h"

class Path {
    friend class VelocityProfile;
private:
    class VelocityProfile {
    private:
        std::vector<double> times;
        std::vector<double> leftVelocities;
        std::vector<double> rightVelocities;

        double maxVelocity;
        double maxAcceleration;

        double pathTime;

        double calcMaxVelocity(double pVelocity, double dDistance);
        double calcMinVelocity(double pVelocity, double dDistance);
        double calcInnerVelocity(double outerVelocity, double curvature, double wheelbase);
        double calcOuterVelocity(double innerVelocity, double curvature, double wheelbase);
        double calcStoppingDistance(double velocity);
        
    public:
        VelocityProfile(double maxVelocity, double maxAcceleration) 
                        : maxVelocity(maxVelocity), maxAcceleration(maxAcceleration), pathTime(0) {}

        void generateVelocityProfile(const Path &path);

        const std::vector<double>& getTimes() { return times; }
        const std::vector<double>& getLeftVelocities() { return leftVelocities; }
        const std::vector<double>& getRightVelocities() { return rightVelocities; }
    };

    std::vector<Spline> path; // Path is simply a vector of splines

    std::vector<double> xWaypoints;
    std::vector<double> yWaypoints;

    std::vector<double> xPoints; // Vector of x coordinates for each spline
    std::vector<double> yPoints; // Vector of y coordinates for each spline

    std::vector<double> leftXPoints;
    std::vector<double> leftYPoints;

    std::vector<double> rightXPoints;
    std::vector<double> rightYPoints;

    std::vector<double> leftDistances;
    std::vector<double> rightDistances;

    double pathLength;
    double leftPathLength;
    double rightPathLength;
    
    VelocityProfile vProfile;

    double wheelbase;

public:
    Path(const std::vector<Waypoint> &points, double maxVelocity, double maxAcceleration, double wheelbase);

    void generatePath(); // Fill x and y vectors
    void generateVelocityProfile();

    const std::vector<double>& getXWayponts() { return xWaypoints; }
    const std::vector<double>& getYWaypoints() { return yWaypoints; }
    const std::vector<double>& getXPoints() { return xPoints; }
    const std::vector<double>& getYPoints() { return yPoints; }
    const std::vector<double>& getLeftXPoints() { return leftXPoints; }
    const std::vector<double>& getLeftYPoints() { return leftYPoints; }
    const std::vector<double>& getRightXPoints() { return rightXPoints; }
    const std::vector<double>& getRightYPoints() { return rightYPoints; }

    const std::vector<double>& getTimes() { return vProfile.getTimes(); }
    const std::vector<double>& getLeftVelocities() { return vProfile.getLeftVelocities(); }
    const std::vector<double>& getRightVelocities() { return vProfile.getRightVelocities(); }

    double getPathLength() { return pathLength; }
    double getLeftPathLength() { return leftPathLength; }
    double getRightPathLength() { return rightPathLength; }
};

#endif