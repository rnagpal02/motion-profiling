#include <iostream>

#include "parse-args.h"
#include "path.h"

int main(int argc, char *argv[]) {
    ParseArgs pa(argc, argv);
    pa.parseFile();

    Path path(pa.getWaypoints());
    path.generateGraph();

    return 0;
}