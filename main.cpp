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

int main()
{
    Random randData(200, 30);

    Scan scn(randData.set);

    scn.sort_angles();

    scn.remove_duplicates();

    scn.grahamScan();

    scn.write_info("./output.csv");

    std::vector<std::string> uncsNodes = scn.unsuccessfulNodes;
    std::vector<std::string> psblSteps = scn.possibleSteps;
    std::vector<std::string> uncsSteps = scn.unsuccessfulSteps;
    std::vector<std::string> scsSteps = scn.successfulSteps;

    std::cout << "Unsuccessful Path" << std::endl;
    for (int i = 0; i < uncsSteps.size(); i++) {
        std::cout << uncsSteps[i] << std::endl;
    }
    std::cout << std::endl;

    writeDOT(scsSteps, psblSteps, uncsSteps, uncsNodes);
}