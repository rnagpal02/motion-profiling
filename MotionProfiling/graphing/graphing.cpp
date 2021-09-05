#include "graphing.h"

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

bool Graphing::graphPath(const std::vector<std::vector<double>> &xPoints, const std::vector<std::vector<double>> &yPoints) {
    if (xPoints.empty() || xPoints.size() != yPoints.size()) {
        std::cerr << "Invalid data points provided for graphing\n";
        return false;
    }

    for(size_t i = 0; i < xPoints.size(); ++i) {
        if(!plt::plot(xPoints[i], yPoints[i])) {
            std::cerr << "Error plotting path data\n";
            return false;
        }
    }

    plt::title("Path");
    plt::xlabel("X");
    plt::ylabel("Y");
    plt::grid(true);
    plt::set_aspect_equal();
    plt::show();

    return true;
}