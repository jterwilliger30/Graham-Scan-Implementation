How to use:

RUN GRAHAM'S SCAN ALGORITHM
- Add all C++ files to a solution (If on Visual Studio)
- Compile scan.cpp, random.cpp, and main.cpp, and run the executable with two arguments, maxVal and numPoints, creating output.csv and DOT.txt

VIEW THE DOT SELECTION TREE
- Open the DOT.txt file.
- Copy All with ctrl+a -> ctrl+c
- Paste into: https://dreampuf.github.io/GraphvizOnline/#
- Enjoy c++ selection tree. Red nodes are members of a failing path. While black nodes are nodes on the successful path. 

VIEW THE 2D SCATTERPLOT
- Install Python and the matplotlib library
- Run the visualizer.py file, which pulls data from output.csv
- Open the generated scatterplot.png file, showing the pointcloud and convex hull

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Possible Errors And How to deal with them:

- Unique Point Generator Error: numPts cannot be greater than (maxVal + 1)^2. If it is, the program will exit with code EXIT_FAILURE
- Integer Overflow error: maxVal cannot be greater than 46340

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Improvements

- Random points are generated and then added to a set, throwing out duplicates if the point is already in the set. If the number of points being generated is high, as the set fills up and the possible unique points remaining decreases, the program keeps generating points indiscriminately. The program may do thousands of calculations just to add a single point to the almost-full set. In the future, the random point generator could take this into account, and only generate points from the possible remaining unique points.
