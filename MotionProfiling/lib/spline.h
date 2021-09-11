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

    double toRadians(double degrees) const { return degrees * (PI / 180.); }
    bool isZero(double val) const { return abs(val) < EPSILON; }


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

    double x(double t) const;
    double y(double t) const;
    double dxdt(double t) const;
    double dydt(double t) const;
    double dydx(double t) const;
    double d2xdt(double t) const;
    double d2ydt(double t) const;
    double d2ydx(double t) const;
    double curvature(double t) const;
    double totalCurvatureSquared() const;

    void computeLeftRightPoint(double t, double offset, std::pair<double, double> &left, std::pair<double, double> &right) const;
    
    double dDistance(double t) const;
    double dDistance(const std::pair<double, double> &currPoint, const std::pair<double, double> &nextPoint) const;

    bool isLeftOuter(double t) const;

    double getdt() const { return dt; }
    double getLeftPathDistance() const { return leftPathDistance; }
    double getRightPathDistance() const { return rightPathDistance; }
};

#endif