#ifndef PATH_H
#define PATH_H

#include <vector>

#include "spline.h"

class Path {
private:
    double dt; // increment value when doing computations
    std::vector<Spline> path; // Path is simply a vector of splines
    std::vector<std::vector<double>> xPoints; // Vector of x coordinates for each spline
    std::vector<std::vector<double>> yPoints; // Vector of y coordinates for each spline

public:
    Path(double dt = 0.001) : dt(dt) {}
    Path(const std::vector<Waypoint> &points, double dt = 0.001);

    void generateGraph(); // Fill x and y vectors
    const std::vector<std::vector<double>>& getXPoints() { return xPoints; }
    const std::vector<std::vector<double>>& getYPoints() { return yPoints; }
};

#endif