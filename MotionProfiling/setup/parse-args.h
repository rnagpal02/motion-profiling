#include <iostream>
#include <string>
#include <getopt.h>

class ParseArgs {
private:
    std::string filename; // filename containing waypoints in CSV format

public:
    ParseArgs(int argc, char *argv[]); // Parses command line args to get filename

    void parseFile(); // Parse CSV file to get waypoints
};

