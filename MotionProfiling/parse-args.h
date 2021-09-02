#include <iostream>
#include <string>
#include <getopt.h>

class ParseArgs {
private:
    std::string filename; // filename containing waypoints in CSV format

public:
    ParseArgs(int argc, char *argv[]) {
        int option_index = 0, option = 0;

        // Don't display getopt error messages about options
        opterr = false;

        // Create command line options
        struct option longOpts[] = { {"filename", required_argument, nullptr, 'f'},
                                     {"help", no_argument, nullptr, 'h'} };


        // Vars to track options chosen
        bool stack_set = false, queue_set = false, output_set = false;

        // Get all options
        while ((option = getopt_long(argc, argv, "f:h", longOpts, &option_index)) != -1) {
            switch(option) {
                case 'f':
                    filename = std::string(optarg);
                    break;
                case 'h':
                    std::cerr << "This program reads in a CSV file containing waypoints for a \n" <<
                                 "robot to follow. A graph is then displayed with the computed\n" <<
                                 "path to follow using quintic splines between the waypoints. The\n" <<
                                 "inputted CSV file should have an x, y, and theta for each waypoint.\n" <<
                                 "Usage: \'./MotionProfiling\n\t[--filename | -f]\n" <<
                                                "\t[--help | -h]\'\n" <<
                                                "\tNote: [-f] should have a valid filename relative to the executable\n";
                    exit(1);
                    break;
                default:
                    std::cerr << "Unknown command line option\n";
                    exit(1);
                    break;
            }
        }

    }
};

