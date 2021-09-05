#ifndef PATH_H
#define PATH_H

#include <vector>

#include "spline.h"

class Path {
private:
    double dt; // increment value when doing computations
    std::vector<Spline> path; // Path is simply a vector of splines
    std::vector<double> x; // vector of x coordinates
    std::vector<double> y; // vector of y coordinates 

public:
    Path(double dt = 0.001) : dt(dt) {}
    Path(const std::vector<Waypoint> &points, double dt = 0.001);

    void generateGraph(); // Fill x and y vectors
    const std::vector<double>& getX() { return x; }
    const std::vector<double>& getY() { return y; }
};

#endif