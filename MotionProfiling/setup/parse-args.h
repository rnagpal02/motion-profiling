#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>

#include "waypoint.h"

class ParseArgs {
private:
    std::string filename; // filename containing waypoints in CSV format
    double maxVelocity;
    double maxAcceleration;
    double wheelbase;
    std::vector<Waypoint> waypoints; // vector of waypoints from input file

    double strToDouble(const std::string &str);

public:
    ParseArgs(int argc, char *argv[]); // Parses command line args to get filename

    void parseFile(); // Parse CSV file to get waypoints

    // Getters
    double getVelocity() { return maxVelocity; }
    double getAcceleration() { return maxAcceleration; }
    double getWheelbase() { return wheelbase; }
    const std::vector<Waypoint>& getWaypoints() { return waypoints; }
};