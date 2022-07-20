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

int main()
{
    Random randData(200, 30);

    Scan scn(randData.set);

    scn.sort_angles();

    scn.remove_duplicates();

    scn.grahamScan();

    scn.write_info("./output.csv");
}