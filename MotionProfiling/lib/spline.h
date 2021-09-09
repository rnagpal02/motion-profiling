#ifndef SPLINE_H
#define SPLINE_H

#include <math.h>
#include <utility>

#include "waypoint.h"

static const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342;

class Spline {
private:
    Spline(const Waypoint &p0, const Waypoint &p1, double s);

    void computeLinearDistance();
    void computeCoefficients(double s);
    double optimizeScale();

    double toRadians(double degrees) { return degrees * (PI / 180.); }
    bool isZero(double val) { return abs(val) < EPSILON; }


    double ax, bx, cx, dx, ex, fx;
    double ay, by, cy, dy, ey, fy;
    double linearDistance;
    double leftPathDistance;
    double rightPathDistance;
    const Waypoint &p0,  &p1;

    const int MAX_TRIES = 1000; // Max times to run loop for optimizing before giving up 
    const double DAMPENING_FACTOR = 0.167; // Multiply this by dkds; found experimentally
    const double MARGIN_ERROR = 1e-3; // Margin of error for dkds (target is 0)
    const double EPSILON = 1e-13;

    // TODO may want to make this modifiable or optimize based on scenario
    const double dt = 0.001; // increment value when doing computations

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

    void computePathDistance(double offset);
    void getLeftRightPoint(double t, double offset, std::pair<double, double> &left, std::pair<double, double> &right);

    double getdt() { return dt; }
    double getLeftPathDistance() { return leftPathDistance; }
    double getRightPathDistance() { return rightPathDistance; }
};

#endif