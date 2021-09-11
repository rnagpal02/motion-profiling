#include "graphing.h"

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

Graphing::Graphing() {
    plt::suptitle("Motion Profiling");
}

bool Graphing::generatePathGraph(const std::vector<double>& xWaypoints, const std::vector<double>& yWaypoints,
                        const std::vector<double> &xPoints, const std::vector<double> &yPoints,
                        const std::vector<double> &leftXPoints, const std::vector<double> &leftYPoints,
                        const std::vector<double> &rightXPoints, const std::vector<double> &rightYPoints) {
    plt::subplot(1, 2, 1);

    if(!plt::scatter(xWaypoints, yWaypoints, 25) ||
        !plt::named_plot("Left", leftXPoints, leftYPoints, "--") ||
        !plt::named_plot("Right", rightXPoints, rightYPoints, "--") ||
        !plt::plot(xPoints, yPoints)) {
        return false;
    }

    plt::title("Path");
    plt::xlabel("X");
    plt::ylabel("Y");
    plt::legend();
    plt::grid(true);
    plt::set_aspect_equal();

    return true;
}

bool Graphing::generateVelocityGraph(const std::vector<double> &times, 
                                    const std::vector<double> &leftVelocities, const std::vector<double> &rightVelocities) {
    plt::subplot(1, 2, 2);
    if(!plt::named_plot("Left", times, leftVelocities) ||
        !plt::named_plot("Right", times, rightVelocities)) {
        return false;
    }

    plt::title("Velocity Profile");
    plt::xlabel("Time (s)");
    plt::ylabel("Velocity (units/s)");
    plt::legend();
    return true;
}

void Graphing::showGraphs() {
    plt::show();
}