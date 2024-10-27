// @author Anbu Krishnan - anbu@iastate.edu
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "util.h"
#include "bmp.h"
#include "pointcloud.h"

// Scale for larger image size
#define SCALE 50  

// Reads point cloud data and returns pointer to pointcloud_t
pointcloud_t *readPointCloudData(FILE *stream) {
    int cols;
    fscanf(stream, "%d", &cols); // reads the number of columns

    pointcloud_t *pc = (pointcloud_t *)malloc(sizeof(pointcloud_t));
    if (!pc) {
        printf("Error: Could not allocate memory for pointcloud_t.\n");
        return NULL;
    }
    listInit(&(pc->points), sizeof(pcd_t));
    pc->cols = cols;
    pc->rows = 0;

    // Reads the point cloud data until the end of the file
    while (!feof(stream)) {
        pcd_t point;
        if (fscanf(stream, "%lf %lf %lf", &point.x, &point.y, &point.z) == 3) {
            point.wd = 0.0; // water depth = 0
            point.north = point.south = point.east = point.west = NULL; // Initializes neighbors
            listAddEnd(&(pc->points), &point); 
            pc->rows = (pc->points.size / pc->cols); // Calculates the number of rows based on points
        }
    }
    return pc;
}

// Generates an image of the point cloud data and saves as a GIF file
void imagePointCloud(pointcloud_t *pc, char *filename) {
    int total_points = pc->points.size;
    int height = pc->rows;
    int width = pc->cols;
    double min_z = DBL_MAX, max_z = -DBL_MAX;

    // min and max z-values 
    for (int i = 0; i < total_points; i++) {
        pcd_t *point = (pcd_t *)listGet(&(pc->points), i);
        if (point->z < min_z) min_z = point->z;
        if (point->z > max_z) max_z = point->z;
    }

    // new scaled BMP image
    Bitmap *image = bm_create(width * SCALE, height * SCALE);
    if (image == NULL) {
        printf("Error: Failed to create BMP image.\n");
        return;
    }

    // adds z-values to pixel values to the scaled image
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            pcd_t *point = (pcd_t *)listGet(&(pc->points), row * width + col);
            int grayscale_value = (int)((point->z - min_z) / (max_z - min_z) * 255);

            // Scales the image 
            for (int y = 0; y < SCALE; y++) {
                for (int x = 0; x < SCALE; x++) {
                    bm_set(image, col * SCALE + x, row * SCALE + y, bm_rgb(grayscale_value, grayscale_value, grayscale_value));
                }
            }
        }
    }

    // Saves the image 
    if (!bm_save(image, filename)) {
        printf("Error: Failed to save BMP image to file: %s\n", filename);
    } else {
        printf("BMP image successfully saved to: %s\n", filename);
    }

    bm_free(image);
}

// Initializes the watershed 
int initializeWatershed(pointcloud_t *pc) {
    int total_points = pc->points.size;
    int width = pc->cols;

    for (int i = 0; i < total_points; i++) {
        pcd_t *point = (pcd_t *)listGet(&(pc->points), i);

        // water depth = 0
        point->wd = 0.0;

        // north, south, east, west pointers
        if (i >= width) { 
            point->north = (pcd_t *)listGet(&(pc->points), i - width);
        }
        if (i < total_points - width) { 
            point->south = (pcd_t *)listGet(&(pc->points), i + width);
        }
        if (i % width != 0) { 
            point->west = (pcd_t *)listGet(&(pc->points), i - 1);
        }
        if (i % width != width - 1) { 
            point->east = (pcd_t *)listGet(&(pc->points), i + 1);
        }
    }

    return 0;
}

// Adds uniform water to all points in the point cloud
void watershedAddUniformWater(pointcloud_t *pc, double amount) {
    int total_points = pc->points.size;
    for (int i = 0; i < total_points; i++) {
        pcd_t *point = (pcd_t *)listGet(&(pc->points), i);
        point->wd += amount;
    }
}

// Computes one step of the analysis
void watershedStep(pointcloud_t *pc, double wcoef, double ecoef) {
    int total_points = pc->points.size;
    double *new_water_depths = (double *)malloc(total_points * sizeof(double));

    // Iterates over each point and calculates the new water depth
    for (int i = 0; i < total_points; i++) {
        pcd_t *point = (pcd_t *)listGet(&(pc->points), i);
        double total_flow = 0.0;

        if (point->west) {
            total_flow += (((point->west->z + point->west->wd) - (point->z + point->wd)) * wcoef);
        }
        if (point->east) {
            total_flow += (((point->east->z + point->east->wd) - (point->z + point->wd)) * wcoef);
        }
        if (point->north) {
            total_flow += (((point->north->z + point->north->wd) - (point->z + point->wd)) * wcoef);
        }
        if (point->south) {
            total_flow += (((point->south->z + point->south->wd) - (point->z + point->wd)) * wcoef);
        }

        new_water_depths[i] = (point->wd + total_flow) * ecoef;
    }

    for (int i = 0; i < total_points; i++) {
        pcd_t *point = (pcd_t *)listGet(&(pc->points), i);
        point->wd = new_water_depths[i];
    }

    free(new_water_depths);
}

// Generates the image showing water content
void imagePointCloudWater(pointcloud_t *pc, double maxwd, char *filename) {
    int total_points = pc->points.size;
    int height = pc->rows;
    int width = pc->cols;

    // new scaled image
    Bitmap *image = bm_create(width * SCALE, height * SCALE);
    if (image == NULL) {
        printf("Error: Failed to create BMP image.\n");
        return;
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            pcd_t *point = (pcd_t *)listGet(&(pc->points), row * width + col);

            // Calculate water depth value and assigns the blue color 
            int blue_value = (int)((point->wd / maxwd) * 255);
            blue_value = blue_value > 255 ? 255 : blue_value; 

            for (int y = 0; y < SCALE; y++) {
                for (int x = 0; x < SCALE; x++) {
                    bm_set(image, col * SCALE + x, row * SCALE + y, bm_rgb(0, 0, blue_value)); 
                }
            }
        }
    }

    if (!bm_save(image, filename)) {
        printf("Error: Failed to save BMP image to file: %s\n", filename);
    } else {
        printf("BMP image successfully saved to: %s\n", filename);
    }

    bm_free(image);
}
