// @author Anbu Krishnan - anbu@iastate.edu
#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string.h> // For memcpy
#include <stdio.h>  // For FILE handling

// access macro using #define to return the index in a one-dimensional array of an element in a 2-dimensional array
#define ACCESS_ARRAY(array, row, column, num_columns) ((array)[(row) * (num_columns) + (column)])

// allocates a 2D array of doubles
void *allocateArray(int rows, int columns);

// stores point cloud data
typedef struct pcd {
    double x, y, z;    
    double wd;    
    struct pcd *north, *south, *east, *west; 
} pcd_t;

// Expanding array list structure
typedef struct {
    int max_size;        
    int max_element_size; 
    void* data;         
    int size;         
} List;

int listInit(List* l, int max_elmt_size);
void listAddEnd(List* l, void* elmt);
void* listGet(List* l, int index);

#endif
