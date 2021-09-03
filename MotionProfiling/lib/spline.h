#ifndef SPLINE_H
#define SPLINE_H

#include "waypoint.h"

class Spline {
private:
    double ax, bx, cx, dx, ex, fx;
    double ay, by, cy, dy, ey, fy;

public:
    Spline(const Waypoint &p0, const Waypoint &p1);
};

#endif