#include "randomPoints.h"
#include "grahamScan.h"
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

void ReadFile(std::string file_name, std::vector<std::pair<int, int>>* data) 
{
    // Opens the file for reading
    std::ifstream file(file_name);

    // Creates a string to hold each line in temporarily
    std::string str;

    // Iterates over the file, storing one line at a time into `str`
    while (std::getline(file, str)) 
    {
        // Create a temporary pair
        std::pair<int, int> new_point;

        // Create a stringstream object with our line of integers from the file
        std::istringstream ss(str);

        // Create a int that will hold our extracted values from the string
        int token;

        // Takes the first 2 numbers of the line and stores them into a pair 
        ss >> token;
        new_point.first = token;
        ss >> token;
        new_point.second = token;

        // We the finally push these points into our data
        data->push_back(new_point);
    }
}

grahamScan::grahamScan(std::string fname, int max, int min)
{
    // We make a file of random points and put those points into the convex_data
    randomPoints(fname, max, min);
    ReadFile(fname, convex_data);
}