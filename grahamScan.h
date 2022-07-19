#include <string>
#include <utility>
#include <vector>

class grahamScan {
private:
	std::vector<std::pair<int, int>>* convex_data;
public:
	grahamScan(std::string fname, int max, int min);
};