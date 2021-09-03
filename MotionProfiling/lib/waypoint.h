#ifndef WAYPOINT_H
#define WAYPOINT_H

class Waypoint {
private:
    double x;
    double y;
    double theta;

public:
    Waypoint(double x, double y, double theta) : x(x), y(y), theta(theta) {}

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getTheta() const { return theta; }
};

#endif