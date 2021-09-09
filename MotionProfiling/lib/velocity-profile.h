#include <vector>

#include "spline.h"

class VelocityProfile {
private:
    std::vector<double> leftVelocities;
    std::vector<double> rightVelocities;

    std::vector<Spline> &path;

    double maxVelocity;
    double maxAcceleration;
    double wheelbase;

public:
    VelocityProfile(std::vector<Spline> &path, double maxVelocity, double maxAcceleration, double wheelbase) 
                    : path(path), maxVelocity(maxVelocity), maxAcceleration(maxAcceleration), wheelbase(wheelbase) {}

    bool generateVelocityProfile();
};