// @author Anbu Krishnan - anbu@iastate.edu
#ifndef POINTCLOUD_H  
#define POINTCLOUD_H

#include "util.h"

// pointcloud_t structure
typedef struct {
    List points;  // List of pcd_t points
    int rows;     // Number of rows in the point cloud
    int cols;     // Number of columns in the point cloud
} pointcloud_t;

// Function prototypes for point cloud handling
pointcloud_t *readPointCloudData(FILE *stream);  // Returns a pointcloud_t*
void imagePointCloud(pointcloud_t* pc, char* filename);  // Uses pointcloud_t for image generation
int initializeWatershed(pointcloud_t *pc);  // Initializes watershed and assigns directional pointers
void watershedAddUniformWater(pointcloud_t* pc, double amount);  // Adds uniform water
void watershedStep(pointcloud_t* pc, double wcoef, double ecoef);  // Simulates one step in the watershed
void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename);  // Generates an image of water content

#endif
