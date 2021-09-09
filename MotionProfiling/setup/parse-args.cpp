#include "parse-args.h"

#include <fstream>
#include <sstream>

ParseArgs::ParseArgs(int argc, char *argv[]) {
    int option_index = 0, option = 0;

    // Don't display getopt error messages about options
    opterr = false;

    // Create command line options
    struct option longOpts[] = {{"filename", required_argument, nullptr, 'f'},
                                {"velocity", required_argument, nullptr, 'v'},
                                {"acceleration", required_argument, nullptr, 'a'},
                                {"wheelbase", required_argument, nullptr, 'w'},
                                {"help", no_argument, nullptr, 'h'}};


    // Vars to track options chosen
    bool stack_set = false, queue_set = false, output_set = false;

    bool gotFile = false;
    bool gotVelocity = false;
    bool gotAcceleration = false;
    bool gotWheelbase = false;

    // Get all options
    while ((option = getopt_long(argc, argv, "f:v:a:w:h", longOpts, &option_index)) != -1) {
        switch(option) {
            case 'f':
                filename = std::string(optarg);
                gotFile = true;
                break;
            case 'v':
                maxVelocity = strToDouble(optarg);
                gotVelocity = true;
                break;
            case 'a':
                maxAcceleration = strToDouble(optarg);
                gotAcceleration = true;
                break;
            case 'w':
                wheelbase = strToDouble(optarg);
                gotWheelbase = true;
                break;
            case 'h':
                std::cerr << "This program reads in a CSV file containing waypoints for a \n" <<
                                "robot to follow. A graph is then displayed with the computed\n" <<
                                "path to follow using quintic splines between the waypoints. The\n" <<
                                "inputted CSV file should have an x, y, and theta for each waypoint.\n" <<
                                "Usage: \'./MotionProfiling\n\t[--filename | -f]\n" <<
                                            "\t[--velocity | -v]\n" <<
                                            "\t[--acceleration | -a]\n" <<
                                            "\t[--wheelbase | -w]\n" <<
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

    if(!gotFile) {
        std::cerr << "No filename provided. Please use --help for more info.\n";
        exit(1);
    }
    if(!gotVelocity) {
        std::cerr << "No velocity provided. Please use --help for more info.\n";
        exit(1);
    }
    if(!gotAcceleration) {
        std::cerr << "No acceleration provided. Please use --help for more info.\n";
        exit(1);
    }
    if(!gotWheelbase) {
        std::cerr << "No wheelbase provided. Please use --help for more info.\n";
        exit(1);
    }
}

void ParseArgs::parseFile() {
    std::ifstream is(filename);
    if(!is.is_open()) {
        std::cerr << "Invalid filename provided\n";
        exit(1);
    }

    std::string line;
    std::string strValue;
    getline(is, line); // Throw away first line in CSV, doesn't matter

    // TODO check formatting is correct
    while(getline(is, line)) {
        std::stringstream ss(line);

        // Need to read in x, y, and theta from the line
        std::getline(ss, strValue, ',');
        double x = strToDouble(strValue);

        std::getline(ss, strValue, ',');
        double y = strToDouble(strValue);

        std::getline(ss, strValue, ',');
        double theta = strToDouble(strValue);

        // Add point to vector
        waypoints.emplace_back(Waypoint(x, y, theta));
    }

    if(waypoints.size() < 2) {
        std::cerr << "Insufficient number of waypoints provided\n";
        exit(1);
    }
}

double ParseArgs::strToDouble(const std::string &str) {
    try {
        return std::stod(str);
    } catch (std::invalid_argument e) {
        std::cerr << "Invalid value " << str << "\n";
    } catch (std::out_of_range e) {
        std::cerr << "Value " << str << " is out of range\n";
    } catch(...) {
        std::cerr << "Unknown error. Unable to parse " << str << "\n";
    }

    exit(1);
    return 0.; // irrelevant
}