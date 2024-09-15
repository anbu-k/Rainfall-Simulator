// @author Anbu Krishnan - anbu@iastate.edu
#include <stdio.h>
#include <float.h>
/**
 * stat1 reads point cloud data in the form of x,y,height, 
 * it then finds the min and max heights and their coordinates, and then calculates the average height
 */
void stat1() {
    double x; // x point
    double y; // y point
    double height; // the height
    double minHeight = DBL_MAX; // the biggest possible value for the minHeight
    double maxHeight = -DBL_MAX; // the smallest possible value for the maxHeight
    double minX; // minHeight coordinate x
    double minY; // minHeight coordinate y 
    double maxX; // maxHeight coordinate x
    double maxY; // maxHeight coordinate y
    double totalHeight = 0.0; // sum of all heights
    int count = 0; // counter for processed points

    // Keeps reading data in the form (x,y, height) until the of the file, (stream of tuples is terminated by the end of file)
    while (scanf("%lf %lf %lf", &x, &y, &height) != EOF) {  
        // Updates the minHeight and stores the coordinates if the current height is smaller
        if (height < minHeight) {
            minHeight = height;
            minX = x;
            minY = y;
        }
        // Updates the maxHeight and stores the coordinates if the current height is larger
        if (height > maxHeight) {
            maxHeight = height;
            maxX = x;
            maxY = y;
        }
        totalHeight += height; // calcualtes the total height in order to find the average height
        count++; // counter that is used to find the average height
    }

    printf("Min Height: %.2f is at (%.2f, %.2f)\n", minHeight, minX, minY); // min height + coordinates where it occurs
    printf("Max Height: %.2f is at (%.2f, %.2f)\n", maxHeight, maxX, maxY); // max height + coordinates where it occurs
    printf("Average Height: %.6f\n", totalHeight / count); // avg height
}

/**
 * main function, all it does is calls the stat1 function and then exits
 */
int main() {
    stat1();
    return 0;
}
