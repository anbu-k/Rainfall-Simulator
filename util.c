// @author Anbu Krishnan - anbu@iastate.edu
#include "util.h"

/**
 * Allocates memory for a 2D array of doubles.
 * Initializes all elements to zero using calloc.
 *
 * @param rows Number of rows in the array.
 * @param columns Number of columns in the array.
 * @return Pointer to the allocated 2D array.
 */
void *allocateArray(int rows, int columns) {
    // Allocates memory for a 2D array stored as a 1D array
    return calloc(rows * columns, sizeof(double));
}

/**
 * Initializes a List structure.
 *
 * @param l Pointer to the List to initialize.
 * @param max_elmt_size Maximum size of any element in the list (in bytes).
 * @return 1 if the list is successfully initialized, 0 otherwise.
 */
int listInit(List *l, int max_elmt_size) {
    l->max_size = 10; // 10 elements
    l->max_element_size = max_elmt_size;
    l->data = malloc(l->max_size * l->max_element_size); 
    l->size = 0; 
    return l->data != NULL;
}

/**
 * Adds an element to the end of the list.
 * If the list is full, it doubles in size.
 *
 * @param l Pointer to the List.
 * @param elmt Pointer to the element to add.
 */
void listAddEnd(List *l, void *elmt) {
    if (l->size == l->max_size) {
        l->max_size *= 2; 
        l->data = realloc(l->data, l->max_size * l->max_element_size); 
    }
    // Copies the element into the list at the end
    memcpy((char*)l->data + (l->size * l->max_element_size), elmt, l->max_element_size);
    l->size++; 
}

/**
 * Gets a pointer to an element in the list.
 *
 * @param l Pointer to the List.
 * @param index Index of the element to retrieve.
 * @return Pointer to the element at the specified index, or NULL if the index is out of bounds.
 */
void *listGet(List *l, int index) {
    if (index < 0 || index >= l->size) return NULL;

    return (char*)l->data + (index * l->max_element_size);
}
