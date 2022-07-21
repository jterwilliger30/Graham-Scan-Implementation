#include "scan.hpp"

Scan::Scan(std::set<std::pair<int, int>> st)
{
    std::copy(st.begin(), st.end(), std::back_inserter(pairs));

    P0 = find_P0(pairs);

    for (auto i : pairs)
    {
        if (i != P0)
        {
            points.push_back(std::make_pair(calculate_angle(P0, i), std::make_pair(i.first, i.second)));
        }
        else
        {
            // Earmarks P0 so that P0 cannot be compared to itself. -1 is outside the domain of arctan for our purposes, so there will never be a collision.
            points.push_back(std::make_pair(-1, std::make_pair(i.first, i.second)));
        }
    }
}

std::pair<int, int> Scan::find_P0(std::vector<std::pair<int, int>> vect)
{
    std::pair<int, int> temp = vect[0];

    // Finds pair with lowest Y coordinate
    for (int i=0; i < vect.size(); i++)
    {
        if (temp.second > vect[i].second)
        {
            temp = vect[i];
        }
    }

    // hello
    // Finds pair with lowest X coordinate
    for (int i=0; i < vect.size(); i++)
    {
        if ((temp.first > vect[i].first) && (temp.second == vect[i].second))
        {
            temp = vect[i];
        }
    }

    return temp;
}

double Scan::calculate_angle(std::pair<int, int> P1, std::pair<int, int> P2)
{
    double xLength = (P2.first - P1.first);
    double yLength = (P2.second - P1.second);

    // Hacky fix for atan returning -0
    return atan2(yLength, xLength) * (180/M_PI);

}

void Scan::sort_angles()
{
    std::sort(points.begin(), points.end());
}

double Scan::distance_P0(std::pair<int, int> P1)
{
    double xLength = abs(P1.first - P0.first);
    double yLength = abs(P1.second - P0.second);

    return sqrt(pow(xLength, 2) + pow(yLength, 2));
}

void Scan::remove_duplicates()
{
    pointsWithDuplicates = points;

    std::vector<std::pair<double, std::pair<int, int>>> pointsTemp;
    std::vector<std::pair<double, std::pair<int, int>>> temp;

    for (int i=pairs.size() - 1; i > 0; i--)
    {
        temp.clear();

        // Adds first element to temp
        temp.push_back(std::make_pair(distance_P0(points[i].second), points[i].second));

        double angle = points[i].first;

        while (points[i].first == points[i-1].first)
        {
            temp.push_back(std::make_pair(distance_P0(points[i-1].second), points[i-1].second));
            i--;
        }

        std::sort(temp.begin(), temp.end());
        std::reverse(temp.begin(), temp.end());

        pointsTemp.push_back(std::make_pair(angle, temp[0].second));

    }
    pointsTemp.push_back(std::make_pair(-1, P0));
    std::reverse(pointsTemp.begin(), pointsTemp.end());
    points = pointsTemp;
}

void Scan::grahamScan()
{
    // Creates new vector of pairs called "pts", omitting the angle (double) that "points" includes
    std::vector<std::pair<int, int>> pts;
    for (auto i : points)
    {
        pts.push_back(i.second);
    }

    // Graham's Scan Algorithm
    for (std::pair<int, int> point : pts)
    {
        while ((hullPoints.size() > 1) && (rotation(penultimate(), hullPoints.top(), point) <= 0))
        {
            hullPoints.pop();
        }
        hullPoints.push(point);
    }
}

int Scan::rotation(std::pair<int, int> P1, std::pair<int, int> P2, std::pair<int, int> P3)
{
    return ((P2.first - P1.first) * (P3.second - P1.second) - (P2.second - P1.second) * (P3.first - P1.first));
}

std::pair<int, int> Scan::penultimate()
{
    std::stack<std::pair<int, int>> cpy = hullPoints;
    cpy.pop();
    return cpy.top();
}

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
        cpy.pop();
    }
    file.close();
}