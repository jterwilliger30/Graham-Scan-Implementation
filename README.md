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
- Add all c++ files to a solution (If on Visual Studio)
- Hit the run button for your IDE
- Open the DOT.txt file.
- Copy All with ctrl+a -> ctrl+c
- Paste into: https://dreampuf.github.io/GraphvizOnline/#
- Enjoy c++ selection tree. Red nodes are members of a failing path. While black nodes are nodes on the successful path. 

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Possible Errors And How to deal with them:

Integer Overflow error: May have given the program a large maxVal which must be squared. The maximum value that can be squared is: 46340.9500011
