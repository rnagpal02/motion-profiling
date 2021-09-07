#ifndef SPLINE_H
#define SPLINE_H

#include "waypoint.h"

static const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342;

class Spline {
private:
    Spline(const Waypoint &p0, const Waypoint &p1, double s);

    void computeLinearDistance();
    double toRadians(double degrees) { return degrees * (PI / 180.); }
    void computeCoefficients(double s);
    double optimizeScale();

    double ax, bx, cx, dx, ex, fx;
    double ay, by, cy, dy, ey, fy;
    double linearDistance;
    const Waypoint &p0,  &p1;

    const int MAX_TRIES = 1000; // Max times to run loop for optimizing before giving up 
    const double DAMPENING_FACTOR = 0.167; // Multiply this by dkds; found experimentally
    const double MARGIN_ERROR = 0.001; // Margin of error for dkds (target is 0)
    const double dt = 0.001; // TODO may want to make this modifiable or optimize based on scenario

public:
    Spline(const Waypoint &p0, const Waypoint &p1);

    double x(double t);
    double y(double t);
    double dxdt(double t);
    double dydt(double t);
    double dydx(double t);
    double d2xdt(double t);
    double d2ydt(double t);
    double d2ydx(double t);
    double curvature(double t);
    double totalCurvatureSquared();
};

#endif