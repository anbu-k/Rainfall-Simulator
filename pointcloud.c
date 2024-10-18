// @author Anbu Krishnan - anbu@iastate.edu
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "util.h"
#include "bmp.h"
#include "pointcloud.h"

/**
 * Reads point cloud data from a file stream and stores it in a list.
 * It also returns the raster width which is the number of columns by the pointer.
 *
 * @param stream The file stream to read from 
 * @param rasterWidth A pointer to store the number of columns in the point cloud
 * @param pc A pointer to the List where the point cloud data will be stored
 */
void readPointCloudData(FILE* stream, int *rasterWidth, List* pc) {
    fscanf(stream, "%d", rasterWidth); // reads the # of columns

    // Reads the point cloud data until the end of the file
    while (!feof(stream)) {
        pcd_t point;
        if (fscanf(stream, "%lf %lf %lf", &point.x, &point.y, &point.z) == 3) {
            point.water = 0.0; 
            point.north = point.south = point.east = point.west = NULL; // Initializes the neighbor pointers
            listAddEnd(pc, &point); // Adds the point to the dynamic list
        }
    }
}

/**
 * Generates an image of the point cloud data in grayscale, saving it as a GIF file.
 * 
 * @param l Pointer to the List containing the point cloud data.
 * @param width The number of columns in the data.
 * @param filename The name of the file to save the image as (e.g., "out.gif").
 */
void imagePointCloud(List *l, int width, char *filename) {
    int total_points = l->size;
    int height = total_points / width;
    double min_z = DBL_MAX, max_z = -DBL_MAX;

    // z-values (height)
    for (int i = 0; i < total_points; i++) {
        pcd_t *point = (pcd_t*)listGet(l, i);
        if (point->z < min_z) min_z = point->z;
        if (point->z > max_z) max_z = point->z;
    }

    // Creates new BMP image
    Bitmap *image = bm_create(width, height);
    if (image == NULL) {
        printf("Error: Failed to create BMP image.\n");
        return;
    }

    // Maps the z-values to grayscale pixel values and then assigns them to the image
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            pcd_t *point = (pcd_t*)listGet(l, row * width + col);

            int grayscale_value = (int)((point->z - min_z) / (max_z - min_z) * 255);
            
            bm_set(image, col, row, bm_rgb(grayscale_value, grayscale_value, grayscale_value)); // Set the grayscale color
        }
    }

    // Print statement before saving the image
    printf("Saving BMP image to file: %s\n", filename);

    // Save the image to a file
    if (!bm_save(image, filename)) {
        printf("Error: Failed to save BMP image to file: %s\n", filename);
    } else {
        printf("BMP image successfully saved to: %s\n", filename);
    }

    // Free the image memory
    bm_free(image);
}
