This project was developed by me, Anbu Krishnan.

Part a:

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

Part b:

This project simulates water flow over a terrain using point cloud data:
 - reads in grid locations and height values
 - calculates the minimum, maximum, and average heights based on the point cloud data

 pointcloud.c update:
 - readPointCloudData(FILE* stream, int* rasterWidth, List* pc): Reads point cloud data from a file and stores it in an expanding list
 - imagePointCloud(List* l, int width, char* filename): Generates a grayscale image from the point cloud data, and saves it as a GIF 
 - using pcd_t from a structure to represent each point in the point cloud, which includes the x-coordinate of the point, the y-coordinate, the height(z-value), minHeight, maxHeight, totalHeight, and count

 pointcloud.h update:
 - contains the declarations for the functions and structs that are being used in pointcloud.c
 - declares the pcd_t structure, and the new readPointCloudData and imagePointCloud functions

 util.c & util.h:
 - these contain utility functions that help with memory allocation and array management
 - primarily includes the implementation of an expanding list that dynamically adjusts in size to store the point cloud data
 - Functions: listAddEnd, listGet, listInit - these are used to manage and interact with the list

 bmp.c & bmp.h:
 - Got this code from github from the assignment spec
 - I use functions from these files to create and save gifs
 - Functions: bm_create (creates a bitmap), bm_set (sets a pixel value in the bitmap), bm_save (saves the bitmap as a gif), bm_free (frees memory allocated for the bitmap)

 display.c:
 - has the main function
 - initializes the list to store point cloud data
 - reads data from the input file
 - calls the imagePointCloud function to generate the gif for the point cloud data

 Makefile compiles my program using gcc, it compiles the pointcloud.c, util.c, and bmp.c source files into object files, the object files are then linked together to generate the display executable. Clean removes the object files and the out.gif file.

 There are no compile issues, to test after running make do: ./display "yourfile.txt" out.gif
 I have two test files that i used, test1.txt and test2.txt
