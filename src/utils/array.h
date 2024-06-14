#include <stdio.h>
#include <stdbool.h>

#ifndef HAARAGAME_UTILS_ARRAY_H
    #define HAARAGAME_UTILS_ARRAY_H

    typedef struct haaragame_utils_array_t {
        size_t size;
        size_t memorySize;
        void **items;
    } HGUtilArray;

    // Check if the array *memorySize* is not zero
    bool HGUtilArrayIsInitiated(HGUtilArray *);

    // Returns 0 or 1 depending if the Key exists
    bool HGUtilArrayKeyExists(HGUtilArray *, size_t);

    /** Clears the memory space of pre-alocated key item (if it exists), 
     *  if its and index too big for the array size or key doesn't 
     *  exists it just appends to the end of the array.
     */
    void HGUtilArraySetItem(HGUtilArray *, size_t, void *);

    // Push an item to the end of the array
    void HGUtilArrayPushItem(HGUtilArray *, void *);

    // Clear array and all pointers (array and items)
    void HGUtilArrayClear(HGUtilArray *);
#endif