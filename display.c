// @author Anbu Krishnan - anbu@iastate.edu
#include <stdio.h>
#include <stdlib.h> // For exit()
#include "util.h"
#include "pointcloud.h"

/**
 * Main function for reading point cloud data, and generating the gif
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    char *inputFile = argv[1];
    char *outputFile = argv[2];

    // Opens the input file to start file reading
    FILE *input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Error: Unable to open input file '%s'.\n", inputFile);
        return 1;
    }

    List pointCloud; // Initializes the list to store point cloud data
    int rasterWidth;  // Number of columns in the point cloud

    // Initialize the expanding list
    if (!listInit(&pointCloud, sizeof(pcd_t))) {
        printf("Error: Unable to initialize point cloud list.\n");
        fclose(input);
        return 1;
    }

    // Reads point cloud data from input file and store in pointCloud
    readPointCloudData(input, &rasterWidth, &pointCloud);
    fclose(input);  

    // Generates the point cloud image as a GIF
    imagePointCloud(&pointCloud, rasterWidth, outputFile);
    
    free(pointCloud.data);

    printf("Image successfully saved to '%s'.\n", outputFile);
    return 0;
}
