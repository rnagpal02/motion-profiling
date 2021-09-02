class Waypoint {
private:
    double x;
    double y;
    double theta;

public:
    Waypoint() {}
    Waypoint(double x, double y, double theta) : x(x), y(y), theta(theta) {}
};