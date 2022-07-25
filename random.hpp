#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <set>
#include <cmath>

class Random
{
private:
    void generatePair(std::set<std::pair<int, int>>* V, int max);

public:
    Random(int maxVal, int numPts);

    std::set<std::pair<int, int>> set;

    void printSet();
};
