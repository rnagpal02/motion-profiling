#include "graphing.h"

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

bool Graphing::generatePathGraph(const std::vector<std::vector<double>> &xPoints, const std::vector<std::vector<double>> &yPoints,
                        const std::vector<double> &leftXPoints, const std::vector<double> &leftYPoints,
                        const std::vector<double> &rightXPoints, const std::vector<double> &rightYPoints) {
    if (xPoints.empty() || xPoints.size() != yPoints.size()) {
        std::cerr << "Invalid data points provided for graphing\n";
        return false;
    }

    if(!plt::named_plot("left", leftXPoints, leftYPoints, "--") ||
        !plt::named_plot("right", rightXPoints, rightYPoints, "--")) {
        return false;
    }

    std::string labelBase = "Spline ";
    for(size_t i = 0; i < xPoints.size(); ++i) {
        if(!plt::named_plot(labelBase + std::to_string(i+1), xPoints[i], yPoints[i])) {
            return false;
        }
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