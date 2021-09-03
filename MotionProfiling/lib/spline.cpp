#include "spline.h"

#include <math.h>

Spline::Spline(const Waypoint &p0, const Waypoint &p1) {
    double s = 1.; // TODO optimize this for least squared curvature

    // These equations come from SplineMath/SplineMath.pdf
    ax = 6 * p1.getX() - 6 * p0.getX() - 3 * s * cos(p1.getTheta()) - 3 * s * cos(p0.getTheta());
    bx = -15 * p1.getX() + 15 * p0.getX() + 7 * s * cos(p1.getTheta()) + 8 * s * cos(p0.getTheta());
    cx = 10 * p1.getX() - 10 * p0.getX() - 4 * s * cos(p1.getTheta()) - 6 * s * cos(p0.getTheta());
    dx = 0;
    ex = s * cos(p0.getTheta());
    fx = p0.getX();

    ay = 6 * p1.getY() - 6 * p0.getY() - 3 * s * sin(p1.getTheta()) - 3 * s * sin(p0.getTheta());
    by = -15 * p1.getY() + 15 * p0.getY() + 7 * s * sin(p1.getTheta()) + 8 * s * sin(p0.getTheta());
    cy = 10 * p1.getY() - 10 * p0.getY() - 4 * s * sin(p1.getTheta()) - 6 * s * sin(p0.getTheta());
    dy = 0;
    ey = s * sin(p0.getTheta());
    fy = p0.getY();
}