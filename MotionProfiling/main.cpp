#include <iostream>

#include "parse-args.h"
#include "path.h"
#include "graphing.h"

int main(int argc, char *argv[]) {
    ParseArgs pa(argc, argv);
    pa.parseFile();

    Path path(pa.getWaypoints(), pa.getVelocity(), pa.getAcceleration(), pa.getWheelbase());
    path.generatePath();
    path.generateVelocityProfile();

    Graphing graphing;
    if(!graphing.generatePathGraph(path.getXWayponts(), path.getYWaypoints(),
                            path.getXPoints(), path.getYPoints(), 
                            path.getLeftXPoints(), path.getLeftYPoints(), 
                            path.getRightXPoints(), path.getRightYPoints()) ||
        !graphing.generateVelocityGraph(path.getTimes(), path.getLeftVelocities(), path.getRightVelocities())) {
        std::cerr << "Error graphing path\n";
        exit(1);
    }
    graphing.showGraphs();
    return 0;
}