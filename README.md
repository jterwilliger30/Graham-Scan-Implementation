Final Project for CSC212 - Focus: Convex Hulls

Must implement:

Graham's Scan algorithm
Read a set of points from a file
Save animated visualization
generate a DOT file.
Paper Report Link Here: https://docs.google.com/document/d/1cGlddapAfUnV9N0lz7ocquaopFk14spjWsR_wm-sVyo/edit?usp=sharing

This project includes a Graham Scan found in scan.cpp, and DOT file writer which can be located in the main.cpp file. We also utilized a matplotlib graph in our visualizer.py file. 

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to use:

RUN GRAHAM'S SCAN ALGORITHM
- Add all C++ files to a solution (If on Visual Studio)
- Toggle the two parameters of the randData object, maxVal and numPoints
- Compile and run scan.cpp, random.cpp, and main.cpp, creating output.csv and dot.txt

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

Unique Point Generator Error: numPts cannot be greater than (maxVal + 1)^2. If it is, the program will loop forever.
Integer Overflow error: May have given the program a large maxVal which must be squared. The maximum value that can be squared is: 46340.9500011
