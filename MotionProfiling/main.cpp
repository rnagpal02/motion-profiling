#include <iostream>

#include "parse-args.h"
#include "path.h"
#include "graphing.h"

int main(int argc, char *argv[]) {
    ParseArgs pa(argc, argv);
    pa.parseFile();

    Path path(pa.getWaypoints(), pa.getVelocity(), pa.getAcceleration(), pa.getWheelbase());
    path.generateGraph();

    Graphing graphing;
    if(!graphing.generatePathGraph(path.getXPoints(), path.getYPoints(), 
                            path.getLeftXPoints(), path.getLeftYPoints(), 
                            path.getRightXPoints(), path.getRightYPoints())) {
        std::cerr << "Error graphing path\n";
        exit(1);
    }

    if(!path.generateVelocityProfile()) {
        std::cerr << "Error generating velocity profile\n";
        exit(1);
    }

    graphing.showGraphs();
    return 0;
}