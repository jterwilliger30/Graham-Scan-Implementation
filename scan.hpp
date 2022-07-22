#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <set>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <stack>

class Scan
{
private:
    
public:
    Scan(std::set<std::pair<int, int>>);

    std::vector<std::string> unsuccessfulSteps;
    std::vector<std::string> unsuccessfulNodes;
    std::vector<std::string> possibleSteps;
    std::vector<std::string> successfulSteps;

    std::vector<std::pair<int, int>> pairs;
    std::vector<std::pair<double, std::pair<int, int> >> pointsWithDuplicates;
    std::vector<std::pair<double, std::pair<int, int> >> points;

    std::stack<std::pair<int, int>> hullPoints;

    std::pair<int, int> P0;

    std::pair<int, int> find_P0(std::vector<std::pair<int, int>>);

    double calculate_angle(std::pair<int, int>, std::pair<int, int>);

    void sort_angles();

    double distance_P0(std::pair<int, int>);

    void remove_duplicates();

    void grahamScan();

    // Positive is counter-clockwise, Negative is clockwise, Zero is co-linear
    int rotation(std::pair<int, int>, std::pair<int, int>, std::pair<int, int>);

    std::pair<int, int> penultimate();

    void write_info(std::string);
};