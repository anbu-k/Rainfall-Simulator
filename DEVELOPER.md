This project was developed by me, Anbu Krishnan.

<Part a>:

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

<Part b>:

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

<PART C>:

Details:
- Expanded the project to include a watershed simulation that demonstrates how water accumulates and flows over terrain using point cloud data. 
- This part shows the dynamics of rainfall simulation and visualizes through .gif images
- water flow is being simulated using the water coefficient to determine how the water spreads from cell to cell
- water evaporation is being simulated over time using the evaporation coefficient

- I used testdata.txt for testing

pointcloud.c update:
- implemented the pointcloud_t structure to manage point cloud data
    - list of pcd_t structures representing individual points
    - grid dimensions - rows and cols

- readPointCloudData(FILE *stream): refactored this function to return a pointer to poinctloud_t. This allows for better management of the point cloud data structure

- initializeWatershed(pointcloud_t *pc): This function sets the initial conditions for the simulation by setting the water depth to 0 and initializing north, south, east, and west pointers for each point, which allows water to flow between adjacent points

- watershedStep(pointcloud_t *pc, double wcoef, double ecoef): This function simulates a single step of water flow. Water flow between neighboring points is based on the formula using wcoef, and evaporation is applied using ecoef

- imagePointCloudWater(pointcloud_t * pc, double maxwd, char *filename): this function generates .gif images showing the water content over the terrain. The blue intensity of each cell relates to the water depth, which is scaled to a maximum by maxwd.

new file watershed.c:
- handles user input from the command line, and sets parameters
- uses the pointcloud_t structure to manage terrain data and simulate water flow over time
- generates .gif images that show how water accumulates and evaporates over terrain

Functions:
- main function is the entry point pertaining to arguments:
1. <ifile> is the input file name of the pointcloud file. 
2. <iter> is the integer number of computation steps to perform. 
3. <iwater> is the initial floating point amount of water covering the pointcloud. 
4. <wcoef> is a floating point number between 0.0 and 0.2, which is the water flow 
coefficient. 
5. <ecoef> is a floating point number between 0.9 and 1.0, which is the evaporation 
coefficient. 
6. <ofilebase> is the base filename of the output file.  If no seq parameter is given the 
output file is simply <ofilebase>.gif, and is the final output of the simulation. 
7. <maxwdepth> gives the max water depth
8. <seq> is a number indicating that every seq number of steps a new output file is 
generated with the name <ofilebase><iter step>.gif.  A seq number of 1 would 
output a new file every step

- the input file is read to initialize the pointcloud_T struct using readPointCloudData, and then the initial simulation parameters are set using initializeWatershed.

- void runWatershedSimulation(pointcloud_t *pc, int iterations, double wcoef, double ecoef, char *ofilebase, double maxwdepth, int seq):
    - handles the core simulation loop, iterating over the specified number of steps
    - generates output images and saves the final image after all the iterations

pointcloud.h update:
- new declarations for all new functions
- defines the pointcloud_t and pcd_t structures

Makefile update:
- updated the Makefile to generate the watershed executable
- if you run make with nothing else the watershed executable is created like asked in the project spec