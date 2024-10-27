// @author Anbu Krishnan - anbu@iastate.edu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pointcloud.h"

// prototype
void runWatershedSimulation(pointcloud_t *pc, int iterations, double wcoef, double ecoef, char *ofilebase, double maxwdepth, int seq);

int main(int argc, char *argv[]) {
    if (argc < 8 || argc > 9) {
        fprintf(stderr, "Usage: ./watershed <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <maxwdepth> [seq]\n");
        return 1;
    }

    // command line args
    char *ifile = argv[1];
    int iterations = atoi(argv[2]);
    double initial_water = atof(argv[3]);
    double wcoef = atof(argv[4]);
    double ecoef = atof(argv[5]);
    char *ofilebase = argv[6];
    double maxwdepth = atof(argv[7]);
    int seq = (argc == 9) ? atoi(argv[8]) : 0;

    // water and evaporation coefficients are within the correct bounds
    if (wcoef < 0.0 || wcoef > 0.2 || ecoef < 0.9 || ecoef > 1.0) {
        fprintf(stderr, "Error: wcoef must be between 0.0 and 0.2, and ecoef must be between 0.9 and 1.0\n");
        return 1;
    }

    // Opens input file for reading the point cloud data
    FILE *input_file = fopen(ifile, "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    // Reads the point cloud data into pointcloud_t
    pointcloud_t *pc = readPointCloudData(input_file);
    fclose(input_file);

    if (initializeWatershed(pc) != 0) {
        fprintf(stderr, "Error initializing watershed\n");
        return 1;
    }

    watershedAddUniformWater(pc, initial_water);

    runWatershedSimulation(pc, iterations, wcoef, ecoef, ofilebase, maxwdepth, seq);

    free(pc->points.data);
    free(pc);

    return 0;
}

/**
 * Runs a watershed simulation over the called number of iterations
 * The simulation updates the water levels of the point cloud 
 *
 * @param pc - Pointer to pointcloud_t containing terrain data
 * @param iterations - The number of simulation steps to perform
 * @param wcoef - Water flow coefficient 
 * @param ecoef - Evaporation coefficient 
 * @param ofilebase - filename for output images 
 * @param maxwdepth - Maximum water depth for visualization
 * @param seq - Interval for generating output images
 */
void runWatershedSimulation(pointcloud_t *pc, int iterations, double wcoef, double ecoef, char *ofilebase, double maxwdepth, int seq) {
    char filename[256]; 

    for (int step = 1; step <= iterations; step++) {
        watershedStep(pc, wcoef, ecoef);

        // Generates image every seq steps or at the final iteration
        if (seq > 0 && step % seq == 0) {
            sprintf(filename, "%s%d.gif", ofilebase, step); 
            imagePointCloudWater(pc, maxwdepth, filename); 
        }
    }

    // final image
    sprintf(filename, "%s.gif", ofilebase); 
    imagePointCloudWater(pc, maxwdepth, filename); 
}

