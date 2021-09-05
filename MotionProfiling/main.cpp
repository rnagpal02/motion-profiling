#include <iostream>

#include "parse-args.h"
#include "path.h"
#include "graphing.h"

int main(int argc, char *argv[]) {
    ParseArgs pa(argc, argv);
    pa.parseFile();

    Path path(pa.getWaypoints());
    path.generateGraph();

    Graphing graphing;
    graphing.graphPath(path.getXPoints(), path.getYPoints());

    return 0;
}