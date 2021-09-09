#ifndef PATH_H
#define PATH_H

#include <vector>

#include "spline.h"
#include "velocity-profile.h"

class Path {
private:
    std::vector<Spline> path; // Path is simply a vector of splines

    std::vector<std::vector<double>> xPoints; // Vector of x coordinates for each spline
    std::vector<std::vector<double>> yPoints; // Vector of y coordinates for each spline

    std::vector<double> leftXPoints;
    std::vector<double> leftYPoints;

    std::vector<double> rightXPoints;
    std::vector<double> rightYPoints;
    
    VelocityProfile *vProfile;

    double wheelbase;

public:
    Path(const std::vector<Waypoint> &points, double maxVelocity, double maxAcceleration, double wheelbase);
    ~Path() { if(vProfile) delete vProfile; }

    void generateGraph(); // Fill x and y vectors
    bool generateVelocityProfile();

    const std::vector<std::vector<double>>& getXPoints() { return xPoints; }
    const std::vector<std::vector<double>>& getYPoints() { return yPoints; }
    const std::vector<double>& getLeftXPoints() { return leftXPoints; }
    const std::vector<double>& getLeftYPoints() { return leftYPoints; }
    const std::vector<double>& getRightXPoints() { return rightXPoints; }
    const std::vector<double>& getRightYPoints() { return rightYPoints; }
};

#endif