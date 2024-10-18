// @author Anbu Krishnan - anbu@iastate.edu
#ifndef POINTCLOUD_H  
#define POINTCLOUD_H

#include "util.h"

// Function prototypes for point cloud handling
void readPointCloudData(FILE* stream, int *rasterWidth, List* pc);
void imagePointCloud(List* l, int width, char* filename);

#endif 
