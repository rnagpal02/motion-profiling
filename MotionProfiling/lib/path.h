#ifndef PATH_H
#define PATH_H

#include <vector>

#include "spline.h"

class Path {
    friend class VelocityProfile;
private:
    class VelocityProfile {
    private:
        std::vector<double> leftVelocities;
        std::vector<double> rightVelocities;

        double maxVelocity;
        double maxAcceleration;

    public:
        VelocityProfile(double maxVelocity, double maxAcceleration) 
                        : maxVelocity(maxVelocity), maxAcceleration(maxAcceleration) {}
        bool generateVelocityProfile(const Path &path);
    };

    std::vector<Spline> path; // Path is simply a vector of splines

    std::vector<std::vector<double>> xPoints; // Vector of x coordinates for each spline
    std::vector<std::vector<double>> yPoints; // Vector of y coordinates for each spline

    std::vector<double> leftXPoints;
    std::vector<double> leftYPoints;

    std::vector<double> rightXPoints;
    std::vector<double> rightYPoints;

    double pathLength;
    double leftPathLength;
    double rightPathLength;
    
    VelocityProfile vProfile;

    double wheelbase;

public:
    Path(const std::vector<Waypoint> &points, double maxVelocity, double maxAcceleration, double wheelbase);

    void generatePath(); // Fill x and y vectors
    bool generateVelocityProfile();

    const std::vector<std::vector<double>>& getXPoints() { return xPoints; }
    const std::vector<std::vector<double>>& getYPoints() { return yPoints; }
    const std::vector<double>& getLeftXPoints() { return leftXPoints; }
    const std::vector<double>& getLeftYPoints() { return leftYPoints; }
    const std::vector<double>& getRightXPoints() { return rightXPoints; }
    const std::vector<double>& getRightYPoints() { return rightYPoints; }
    double getPathLength() { return pathLength; }
    double getLeftPathLength() { return leftPathLength; }
    double getRightPathLength() { return rightPathLength; }
};

#endif