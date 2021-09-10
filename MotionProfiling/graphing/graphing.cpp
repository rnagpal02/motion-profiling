#include "graphing.h"

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

bool Graphing::generatePathGraph(const std::vector<double>& xWaypoints, const std::vector<double>& yWaypoints,
                        const std::vector<double> &xPoints, const std::vector<double> &yPoints,
                        const std::vector<double> &leftXPoints, const std::vector<double> &leftYPoints,
                        const std::vector<double> &rightXPoints, const std::vector<double> &rightYPoints) {
    if (xPoints.empty() || xPoints.size() != yPoints.size()) {
        std::cerr << "Invalid data points provided for graphing\n";
        return false;
    }

    if(!plt::scatter(xWaypoints, yWaypoints, 25) ||
        !plt::plot(xPoints, yPoints) ||
        !plt::named_plot("left", leftXPoints, leftYPoints, "--") ||
        !plt::named_plot("right", rightXPoints, rightYPoints, "--")) {
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

void Graphing::showGraphs() {
    plt::show();
}