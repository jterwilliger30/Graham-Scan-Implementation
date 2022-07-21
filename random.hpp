#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <set>

class Random
{
private:
    int maxVal;
    int numPts;

    void generatePair(std::set<std::pair<int, int>>* V, int max);

public:
    Random(int, int);

    std::set<std::pair<int, int>> set;

    void printSet();
};