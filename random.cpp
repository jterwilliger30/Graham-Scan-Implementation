#include "random.hpp"

Random::Random(int a, int b)
{
    maxVal = a;
    numPts = b;

    srand(time(NULL));
    while (set.size() != numPts)
    {
        generatePair(&set, maxVal);
    }
}

void Random::generatePair(std::set<std::pair<int, int>>* V, int max)
{
    std::pair<int, int> pr;
    for (int i=0; i < max; i++)
    {
        pr.first = rand() % (max + 1);
        pr.second = rand() % (max + 1);
    }

    V->insert(pr);
}

void Random::printSet()
{
    for (std::pair<int, int> i : set)
    {
        std::cout << "(" << i.first << ", " << i.second << ")" << std::endl;
    }
    std::cout << "Size: " << set.size() << std::endl;
}