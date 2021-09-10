#include <vector>

class Graphing {
public:
    bool generatePathGraph(const std::vector<double>& xWaypoints, const std::vector<double>& yWaypoints,
                    const std::vector<double> &xPoints, const std::vector<double> &yPoints,
                    const std::vector<double> &leftXPoints, const std::vector<double> &leftYPoints,
                    const std::vector<double> &rightXPoints, const std::vector<double> &rightYPoints);
    void showGraphs();
};