#include "randomPoints.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <utility>
#include <cmath>

// Function for writing points into a file
void WriteFile(std::string file_name, std::vector<std::pair<int, int>>* data) 
{
	// Make a file to writeur points into 
	std::ofstream output_file(file_name);

	// Loop through the vector and ourpur them into the file until out of points
	for (int i = 0; i < (*data).size(); i++) {
		output_file << (*data)[i].first << " " << (*data)[i].second << std::endl;
	}

	// Making sure close the file afterwards   
	output_file.close();
}

// Constructor that makes a file of unique random points 
randomPoints::randomPoints(std::string fname, int max, int min)
{
	// Making the amount of points generally equal to half the total possible combinations  
	const int maxPts = pow((max - min), 2) / 2;

	// Initializing the data vector and point pair 
	std::vector<std::pair<int, int>> data;
	std::pair<int, int> xy;

	// Making sure the points random every time  
	srand(time(NULL));

	// Loop that generates points
	for (int i = 0; i < maxPts; ++i){
		// Making x and y random with the limit given 
		int x = rand() % max;
		int y = rand() % max;

		// Making sure that the points aren't under min  
		if (x < min) {
			x += min;
		}
		if (y < min) {
			y += min;
		}

		// Filling in the pair
		xy.first = x;
		xy.second = y;

		// Checking if the point is already in the data to make sure all points are unique     
		bool copy = false;
		for (int j = 0; j < data.size(); j++) {
			if (xy.first == data[j].first && xy.second == data[j].second) {
				copy = true;
			}
		}

		// If it is unique we keep it, if not, we just run the loop again (could technically last forever...)  
		if(copy == false){
			data.push_back(xy);
		}
		else{
			i--;
		}
	}

	// Finally writing the data into a file for future use 
	WriteFile(fname, &data);
}