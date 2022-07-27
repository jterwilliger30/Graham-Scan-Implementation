#include "scan.hpp"

// Used psuedocode from wikipedia!

// Constructor for scan which uses the set made form the random class
Scan::Scan(std::set<std::pair<int, int>> st)
{
    // Makes a copy of the set that random made and put it into pairs
    std::copy(st.begin(), st.end(), std::back_inserter(pairs));

    // Finds the starting point for our code
    P0 = find_P0(pairs);

    // Loops through the new vector of pairs and calculates their angle from the start 
    for (std::pair<int, int> i : pairs)
    {
        // Just a simmple check to have the starting point's angle be -1 (or first in the vector)
        if (i != P0)
        {
            // We push a new pair into a new vector named points, were they have their angle form origin and their coordinates
            points.push_back(std::make_pair(calculate_angle(P0, i), std::make_pair(i.first, i.second)));
        }
        else
        {
            // Earmarks P0 so that P0 cannot be compared to itself. -1 is outside the domain of arctan for our purposes, so there will never be a collision.
            points.push_back(std::make_pair(-1, std::make_pair(i.first, i.second)));
        }
    }
}

// Simple function to find the lowest and then leftmost point
std::pair<int, int> Scan::find_P0(std::vector<std::pair<int, int>> vect)
{
    // Creates a new pair that mimics the first pair in the vector
    std::pair<int, int> temp = vect[0];

    // Finds pair with lowest Y coordinate
    for (int i=0; i < vect.size(); i++)
    {
        // Quick check to find if the temp pair's Y coordinate is higher than the pair we are looking at
        if (temp.second > vect[i].second)
        {
            temp = vect[i];
        }
    }

    // Finds pair with lowest X coordinate amongst the pairs with the lowest Y coordinate

    for (int i=0; i < vect.size(); i++)
    {
        // Quick check to find if the temp pair's X coordinate is higher than the pair we are looking at while being on the same Y
        if ((temp.first > vect[i].first) && (temp.second == vect[i].second))
        {
            temp = vect[i];
        }
    }
    
    // Return the newfound origin
    return temp;
}

// A simple function that calculates the angle from the origin
double Scan::calculate_angle(std::pair<int, int> P1, std::pair<int, int> P2)
{
    // Find the X and Y distance from origin
    double xLength = (P2.first - P1.first);
    double yLength = (P2.second - P1.second);

    // Returns the arctan of those 2 distances (Hacky fix for atan returning -0)
    return atan2(yLength, xLength) * (180/M_PI);
}

// Small function that sort whats is given
void Scan::sort_angles()
{
    // Sort seems to work off of the fisrt number in node you give it, so the first number is the angle for each pair
    std::sort(points.begin(), points.end());
}

// Very similar to calculate_angle execpt it find the distance
double Scan::distance_P0(std::pair<int, int> P1)
{
    // Find the X and Y distance from origin
    double xLength = abs(P1.first - P0.first);
    double yLength = abs(P1.second - P0.second);

    // Returns the a^2 + b^2 = c^2 solution for c
    return sqrt(pow(xLength, 2) + pow(yLength, 2));
}

// A function that gets rid of points with the same angle, leaving only the furthest one
void Scan::remove_duplicates()
{
    // First make a copy of the original just so we can debug/visualize what is going on
    pointsWithDuplicates = points;

    // Make some temp vectors, one for storing points that have the same angle, and one that will store all of the points with unique angles
    std::vector<std::pair<double, std::pair<int, int>>> pointsTemp;
    std::vector<std::pair<double, std::pair<int, int>>> temp;

    // Go through all the points from top to bottom
    for (int i=pairs.size() - 1; i > 0; i--)
    {
        // Clear temp as we no longer need any of the points in here.
        temp.clear();

        // Adds first element to temp, starting with its' distance from the origin
        temp.push_back(std::make_pair(distance_P0(points[i].second), points[i].second));

        // Save the angle we are looking for
        double angle = points[i].first;

        // Loop through until we no longer have points with the same angle as the on above
        while (points[i].first == points[i-1].first)
        {
            // Add the point with the same angle into the temp vector with the distance being first
            temp.push_back(std::make_pair(distance_P0(points[i-1].second), points[i-1].second));
            // This both accelerates the for loop above, and continues the while loop
            i--;
        }

        // Sort by the distance and flip to make sure the highest distance is the one in the [0] slot
        std::sort(temp.begin(), temp.end());
        std::reverse(temp.begin(), temp.end());

        // Add [0] to the pointsTemp vector to make sure only the longest one stayed
        pointsTemp.push_back(std::make_pair(angle, temp[0].second));

    }

    // Add the origin into the pointsTemp, reverse so that the sorting is once again in the correct order, and finallymake points equal to the new pointsTemp
    pointsTemp.push_back(std::make_pair(-1, P0));
    std::reverse(pointsTemp.begin(), pointsTemp.end());
    points = pointsTemp;
}

// Small function to find what way the point is rotating
int Scan::rotation(std::pair<int, int> P1, std::pair<int, int> P2, std::pair<int, int> P3)
{
    return ((P2.first - P1.first) * (P3.second - P1.second) - (P2.second - P1.second) * (P3.first - P1.first));
}

// Small function that finds the 2nd point from the top
std::pair<int, int> Scan::penultimate()
{
    // Makes copy of top pair, then removes it from the original
    std::pair<int, int> top = hullPoints.top();
    hullPoints.pop();

    // Makes a copy of the secondFromTop pair
    std::pair<int, int> secondFromTop = hullPoints.top();

    // Adds back the top pair that was deleted
    hullPoints.push(top);

    // Returns the secondFromTop pair
    return secondFromTop;
}

// Basic Print function
void Scan::write_info(std::string filename)
{
    std::ofstream file;
    file.open(filename);

    file << "All Points: " << std::endl;
    for (auto i : pointsWithDuplicates)
    {
        file << "(" << i.second.first << ", " << i.second.second << ")" << std::endl;
        //file << "Angle: " << i.first << std::endl;
    }
    file << std::endl;

    file << "Hull Points: " << std::endl;

    std::stack<std::pair<int, int>> cpy = hullPoints;
    while (!cpy.empty())
    {
        file << "(" << cpy.top().first << ", " << cpy.top().second << ")" << std::endl;
        std::string str = "(" + std::to_string(cpy.top().first) + "," + std::to_string(cpy.top().second) + ")";
        successfulSteps.push_back(str);
        cpy.pop();
    }
    file.close();
}
