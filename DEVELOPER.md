This project was developed by me, Anbu Krishnan.

This project simulates water flow over a terrain using point cloud data:
 - reads in grid locations and height values
 - calculates the minimum, maximum, and average heights based on the point cloud data

pointcloud.c is the main key data structure in this project:
 -This file implements the stat1() function, the stat1() function processes the point cloud data.
 - x : represents the x-coordinate
 - y : represents the y-coordinate
 - height : double value that represents the height of the terrain at the x,y position
 - minHeight : stores the minimum height
 - maxHeight : stores the maximum height
 - totalHeight: calculates the average height between all of the height values
 - count : tracks how many points have been processed

pointcloud.h contains the declaration for the stat1() function

Makefile compiles my program using gcc, pointcloud.c is compiled to pointcloud.o which is an object file, it is then linked to create stat 

There are no compile issues, my program does not handle invalid input formats. 
The test data should be formatted with 3 space separated values per line that represent x,y and height