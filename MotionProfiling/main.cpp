#include <iostream>

#include "setup/parse-args.h"

int main(int argc, char *argv[]) {
    ParseArgs pa(argc, argv);
    pa.parseFile();
    return 0;
}