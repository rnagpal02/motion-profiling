#include "spline.h"

Spline::Spline(const Waypoint &p0, const Waypoint &p1) : p0(p0), p1(p1), leftPathDistance(0), rightPathDistance(0) {
    computeLinearDistance();
    computeCoefficients(optimizeScale());
}

Spline::Spline(const Waypoint &p0, const Waypoint &p1, double s) : p0(p0), p1(p1), leftPathDistance(0), rightPathDistance(0) {
    computeLinearDistance();
    computeCoefficients(s);
}

void Spline::computeCoefficients(double s) {
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

void Spline::computeLinearDistance() {
    linearDistance = sqrt(pow(p0.getX() - p1.getX(), 2) + pow(p0.getY() - p1.getY(), 2));
}

// TODO may want to look into optimizing this by path time once velocity profiles are added in
double Spline::optimizeScale() {
    // Use linear distance as initial guess
    double s = linearDistance;

    // k is curvature, dkds is rate of change of curvature with respect to s
    double ds = 0.1 * s;
    double dkds = (Spline(p0, p1, s + ds / 2).totalCurvatureSquared() - Spline(p0, p1, s - ds / 2).totalCurvatureSquared()) / ds;
    
    int numTries = 0;
    while (abs(dkds) > MARGIN_ERROR && numTries < MAX_TRIES) {
        double delta = dkds * DAMPENING_FACTOR;
        s -= delta;
        dkds = (Spline(p0, p1, s + ds / 2).totalCurvatureSquared() - Spline(p0, p1, s - ds / 2).totalCurvatureSquared()) / ds;
        ++numTries;
    }

    return s;
}

double Spline::x(double t) const {
    return ax * pow(t, 5) + bx * pow(t, 4) + cx * pow(t, 3) + dx * pow(t, 2) + ex * t + fx;
}
double Spline::y(double t) const {
    return ay * pow(t, 5) + by * pow(t, 4) + cy * pow(t, 3) + dy * pow(t, 2) + ey * t + fy;
}
double Spline::dxdt(double t) const {
    return 5 * ax * pow(t, 4) + 4 * bx * pow(t, 3) + 3 * cx * pow(t, 2) + 2 * dx * t + ex;
}
double Spline::dydt(double t) const {
    return 5 * ay * pow(t, 4) + 4 * by * pow(t, 3) + 3 * cy * pow(t, 2) + 2 * dy * t + ey;
}
double Spline::dydx(double t) const {
    return dydt(t) / dxdt(t); // TODO check for divide by 0
}
double Spline::d2xdt(double t) const {
    return 20 * ax * pow(t, 3) + 12 * bx * pow(t, 2) + 6 * cx * t + 2 * dx;
}
double Spline::d2ydt(double t) const {
    return 20 * ay * pow(t, 3) + 12 * by * pow(t, 2) + 6 * cy * t + 2 * dy;
}
double Spline::d2ydx(double t) const {
    return (dxdt(t) * d2ydt(t) - d2xdt(t) * dydt(t)) / pow(dxdt(t), 3);
}
double Spline::curvature(double t) const {
    return abs(dxdt(t) * d2ydt(t) - dydt(t) * d2xdt(t)) / pow(pow(dxdt(t), 2) + pow(dydt(t), 2), 1.5);
}
double Spline::totalCurvatureSquared() const {
    double totalCurvature = 0;
    for(double t = 0; t < 1; t += dt) {
        totalCurvature += (pow(curvature(t), 2) * dt); // Could multiply by dt once at end but that might cause overflow
    }
    return totalCurvature;
}

void Spline::computeLeftRightPoint(double t, double offset, std::pair<double, double> &left, std::pair<double, double> &right) const {
    if(isZero(dydt(t))) {
        if(dxdt(t) > 0) {
            left = std::make_pair<double, double>(x(t), y(t) + offset);
            right = std::make_pair<double, double>(x(t), y(t) - offset);
        } else {
            left = std::make_pair<double, double>(x(t), y(t) - offset);
            right = std::make_pair<double, double>(x(t), y(t) + offset);
        }
    } else if(isZero(dxdt(t))) {
        if(dydt(t) > 0) {
            left = std::make_pair<double, double>(x(t) - offset, y(t));
            right = std::make_pair<double, double>(x(t) + offset, y(t));
        } else {
            left = std::make_pair<double, double>(x(t) + offset, y(t));
            right = std::make_pair<double, double>(x(t) - offset, y(t));
        }
    } else {
        double normalSlope = -1 / dydx(t);
        double angle = atan(normalSlope);

        std::pair<double, double> directionVect = std::make_pair<double, double>(abs(normalSlope * cos(angle)), abs(normalSlope * sin(angle)));
        double scaleFactor = offset / sqrt(pow(directionVect.first, 2) + pow(directionVect.second, 2));
        directionVect.first *= scaleFactor;
        directionVect.second *= scaleFactor;

        if(dydx(t) > 0) {
            if(dxdt(t) > 0) {
                left = std::make_pair<double, double>(x(t) - directionVect.first, y(t) + directionVect.second);
                right = std::make_pair<double, double>(x(t) + directionVect.first, y(t) - directionVect.second);
            } else {
                left = std::make_pair<double, double>(x(t) + directionVect.first, y(t) - directionVect.second);
                right = std::make_pair<double, double>(x(t) - directionVect.first, y(t) + directionVect.second);
            }
        } else {
            if(dxdt(t) > 0) {
                left = std::make_pair<double, double>(x(t) + directionVect.first, y(t) + directionVect.second);
                right = std::make_pair<double, double>(x(t) - directionVect.first, y(t) - directionVect.second);
            } else {
                left = std::make_pair<double, double>(x(t) - directionVect.first, y(t) - directionVect.second);
                right = std::make_pair<double, double>(x(t) + directionVect.first, y(t) + directionVect.second);
            }
        }
    }   
}

double Spline::dDistance(double t) const {
    return sqrt(pow(dxdt(t), 2) + pow(dydt(t), 2)) * dt;
}
double Spline::dDistance(const std::pair<double, double> &currPoint, const std::pair<double, double> &nextPoint) const {
    return sqrt(pow((nextPoint.first - currPoint.first) / dt, 2) + pow((nextPoint.second - currPoint.second) / dt, 2)) * dt;
}

bool Spline::isLeftOuter(double t) const {
    if(d2ydx(t) > 0) {
        if(dxdt(t) > 0) {
            return false;
        } else {
            return true;
        }
    } else {
        if(dxdt(t) > 0) {
            return true;
        } else {
            return false;
        }
    }
}