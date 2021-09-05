#ifndef SPLINE_H
#define SPLINE_H

#include "waypoint.h"

static const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342;

class Spline {
private:
    double ax, bx, cx, dx, ex, fx;
    double ay, by, cy, dy, ey, fy;

    double toRadians(double degrees) { return degrees * (PI / 180.); }

public:
    Spline(const Waypoint &p0, const Waypoint &p1);

    double getX(double t);
    double getY(double t);
};

#endif