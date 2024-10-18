Project 1 P1 - Rainfall Flood Simulation (Point Cloud Data)

I compile by doing: 
1. make 
2. ./display yourfile.txt out.gif   //the test files I used are test1.txt and test2.txt, yourfile.txt is just a random example. out.gif is the name of the file that you want to save the image to.
3. the out.gif file should be saved into your directory after running the command in step 2

To clean:
1. make clean (this will also remove the out.gif file)

I compile by doing: 
1. make 
2. ./stat < testdata.txt

My program reads point cloud data in a x,y, height format. It then calculates and displays the minimum height and its coordinates, the maximum height and its coordinates and the average height of all the point cloud data.

It processes the point cloud data and calculates: the minimum height and its corresponding coordinates, its maximum height and its corresponding coordinates, and the average height of all points in the point cloud.

The data is then visualized as a grayscale image saved as out.gif where the lower heights are represented by darker shades, and the higher heights are represented by the lighter shades.

I compile and test using MSYS2 MINGW64