#include "random.hpp"

// The main function for this class
Random::Random(int maxVal, int numPts)
{
    // Set a random seed
    srand(time(NULL));

    // While we don't have the number of points we need, we add more (set doesn't allow for duplicates)
    while (set.size() != numPts)
    {
        generatePair(&set, maxVal);
    }
}

// This function sole purpose is to make a random pair of coordinates and store it in a set
void Random::generatePair(std::set<std::pair<int, int>>* V, int max)
{
    // Make a point to store data in
    std::pair<int, int> pr;

    // Add randome numbers for the x and y values while keeping the numbers under the confines of our soon to be graph
    pr.first = rand() % (max + 1);
    pr.second = rand() % (max + 1);

    // Lastly we insert the pair into our set
    V->insert(pr);
}

// Debugging helper...
void Random::printSet()
{
    for (std::pair<int, int> i : set)
    {
        std::cout << "(" << i.first << ", " << i.second << ")" << std::endl;
    }
    std::cout << "Size: " << set.size() << std::endl;
}