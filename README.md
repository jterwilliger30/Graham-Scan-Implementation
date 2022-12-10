Summary:

- This repo is an implementation of the Graham Scan convex hull algorithm written in C++ written for a project that has since concluded.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Possible Errors And How to deal with them:

- Unique Point Generator Error: numPts cannot be greater than (maxVal + 1)^2. If it is, the program will exit with code EXIT_FAILURE
- Integer Overflow error: maxVal cannot be greater than 46340

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Improvements

- Random points are generated and then added to a set, throwing out duplicates if the point is already in the set. If the number of points being generated is high, as the set fills up and the possible unique points remaining decreases, the program keeps generating points indiscriminately. The program may do thousands of calculations just to add a single point to the almost-full set. In the future, the random point generator could take this into account, and only generate points from the possible remaining unique points.
