#ifndef PATH_H
#define PATH_H

#include <vector>

#include "spline.h"

class Path {
private:
    std::vector<Spline> path; // Path is simply a vector of splines
public:
    Path() {}
    Path(const std::vector<Waypoint> &points);
};

#endif