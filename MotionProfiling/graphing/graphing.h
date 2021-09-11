#include <vector>

class Graphing {
public:
    Graphing();

    bool generatePathGraph(const std::vector<double>& xWaypoints, const std::vector<double>& yWaypoints,
                    const std::vector<double> &xPoints, const std::vector<double> &yPoints,
                    const std::vector<double> &leftXPoints, const std::vector<double> &leftYPoints,
                    const std::vector<double> &rightXPoints, const std::vector<double> &rightYPoints);
    bool generateVelocityGraph(const std::vector<double> &times, 
                                const std::vector<double> &leftVelocities, const std::vector<double> &rightVelocities);
    void showGraphs();
};