#include "spline.h"

#include <math.h>

Spline::Spline(const Waypoint &p0, const Waypoint &p1) {
    double s = 1.; // TODO optimize this for least squared curvature

    // These equations come from SplineMath/SplineMath.pdf
    ax = 6. * p1.getX() - 6. * p0.getX() - 3. * s * cos(toRadians(p1.getTheta())) - 3. * s * cos(toRadians(p0.getTheta()));
    bx = -15. * p1.getX() + 15. * p0.getX() + 7. * s * cos(toRadians(p1.getTheta())) + 8. * s * cos(toRadians(p0.getTheta()));
    cx = 10. * p1.getX() - 10. * p0.getX() - 4. * s * cos(toRadians(p1.getTheta())) - 6. * s * cos(toRadians(p0.getTheta()));
    dx = 0.;
    ex = s * cos(toRadians(p0.getTheta()));
    fx = p0.getX();

    ay = 6. * p1.getY() - 6. * p0.getY() - 3. * s * sin(toRadians(p1.getTheta())) - 3. * s * sin(toRadians(p0.getTheta()));
    by = -15. * p1.getY() + 15. * p0.getY() + 7. * s * sin(toRadians(p1.getTheta())) + 8. * s * sin(toRadians(p0.getTheta()));
    cy = 10. * p1.getY() - 10. * p0.getY() - 4. * s * sin(toRadians(p1.getTheta())) - 6. * s * sin(toRadians(p0.getTheta()));
    dy = 0.;
    ey = s * sin(toRadians(p0.getTheta()));
    fy = p0.getY();
}

double Spline::getX(double t) {
    return ax * pow(t, 5) + bx * pow(t, 4) + cx * pow(t, 3) + dx * pow(t, 2) + ex * pow(t, 1) + fx;
}
double Spline::getY(double t) {
    return ay * pow(t, 5) + by * pow(t, 4) + cy * pow(t, 3) + dy * pow(t, 2) + ey * pow(t, 1) + fy;
}