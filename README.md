Rainfall Flood Simulation (Point Cloud Data)

I compile by doing: 
1. make (this generates the watershed executable)
2. ./watershed <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <maxwdepth> <seq>  (an example command I used for testing): ./watershed testdata.txt 10 10.0 0.1 0.95 output 1.0 2
3. This above command should generate a certain # of output#.gif depending on the values of iter and seq

To clean:
1. make clean (this will also remove the output#.gif files)

parameter explanations:
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
output a new file every step.

My program reads point cloud data in a x,y, height format. It then calculates and displays the minimum height and its coordinates, the maximum height and its coordinates and the average height of all the point cloud data.

It processes the point cloud data and calculates: the minimum height and its corresponding coordinates, its maximum height and its corresponding coordinates, and the average height of all points in the point cloud.

It then simulates a flood model over a terrain using point cloud data. Each step "iter" simulates water flowing from higher elevations to lower ones based on the water flow
coefficient. The water evaporates based on the evaporation coefficient after each step.

My simulation generates .gif images showing water accumulation at different steps of the simulation, the total number of images depends on the values of iter and seq.
Images are generated every seq steps and always at the final iteration. 

The blue shading represents water depth, the maximum shading intensity corresponds to the deepest water.

I compile and test using MSYS2 MINGW64
