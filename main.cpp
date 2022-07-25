#include "random.hpp"
#include "scan.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <set>

void writeDOT(std::vector<std::string> scs, std::vector<std::string> psbl, std::vector<std::string> unscs, std::vector<std::string> unscsN) {
    std::ofstream out("DOT.txt");
    int success = 0;
    int last = 0;
    out << "digraph {" << std::endl;
    for (int i = 0; i < psbl.size(); i++) {
        bool red = false;
        for (int j = 0; j < unscsN.size(); j++) {
            if (psbl[i] == unscsN[j]) {
                out << "\t" + std::to_string(i) + " [shape = \"circle\", label =\"" + psbl[i] + "\", color = \"red\"]" << std::endl;
                //out << "\t" + std::to_string(success) + " -> " + std::to_string(i) << std::endl;
                red = true;
                if (unscs[i + 1] == unscs[i]) { //Parent is last successful
                    out << "\t" + std::to_string(last) + " -> " + std::to_string(i) + ";" << std::endl;
                }
                else { //Parent is i - 1
                    out << "\t" + std::to_string(i - 1) + " -> " + std::to_string(i) + ";" << std::endl;
                }
            }
        }
        if (red == false) {
            out << "\t" + std::to_string(i) + " [shape = \"circle\", label =\"" + psbl[i] + "\"]";
            out << std::endl;
            if (i != 0) {
                out << "\t" + std::to_string(last) + " -> " + std::to_string(i) + ";" << std::endl;
            }
            ++success;
            last = i;
        }
    }
    out << "}";
}

int main(int argc, char* argv[])
{
    // If number of command line arguments is not 3, exits program with failure code
    if (argc != 3)
    {
        std::cout << "Incorrect number of CLI arguments!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Maximum X and Y coordinate for generated points
    int maxVal = std::stoi(argv[1]);

    // Number of unique points to be generated
    int numPts = std::stoi(argv[2]);

    // Generates a set of "numPts" unique points, with no point having value greater than "maxVal"
    Random randData(maxVal, numPts);

    // Sets up Graham's Scan algorithm on set of points generated above by finding P0 and calculating angles from P0
    Scan scn(randData.set);

    // Sorts points by their angle from P0 (with P0 being first)
    scn.sort_angles();

    // Removes points with the same angle, keeping only the one furthest from P0
    scn.remove_duplicates();

    // Executes the Grahams Scan Algorithm
    scn.grahamScan();

    // Writes all points (including duplicates removed above) and hull points to output.csv
    scn.write_info("./output.csv");

    std::vector<std::string> uncsNodes = scn.unsuccessfulNodes;
    std::vector<std::string> psblSteps = scn.possibleSteps;
    std::vector<std::string> uncsSteps = scn.unsuccessfulSteps;
    std::vector<std::string> scsSteps = scn.successfulSteps;

    writeDOT(scsSteps, psblSteps, uncsSteps, uncsNodes);
}
