#include "array.h"

#include "debug.c"

#ifndef HAARAGAME_UTILS_ARRAY_C
    #define HAARAGAME_UTILS_ARRAY_C

    bool HGUtilArrayIsInitiated(HGUtilArray *array) {
        return (bool) array->memorySize;
    }

    bool HGUtilArrayKeyExists(HGUtilArray *array, size_t key) {
        if (!array->size) {
            return false;
        }

        return array->size > key;
    }

    void HGUtilArraySetItem(HGUtilArray *array, size_t key, void *item) {
        if (! HGUtilArrayIsInitiated(array)) {
            return;
        }

        if (HGUtilArrayKeyExists(array, key)) {
            free(array->items[key]);
            array->items[key] = item;

            return;
        }

        size_t oldSize = array->size;
        void **oldItems = array->items;

        array->size++;
        array->items = (void **) malloc(sizeof(void *) * array->size);

        memcpy(array->items, oldItems, sizeof(void *) * oldSize);

        array->items[oldSize] = item;

        free(oldItems);
    }

    void HGUtilArrayPushItem(HGUtilArray *array, void *item) {
        if (! HGUtilArrayIsInitiated(array)) {
            return;
        }

        size_t nextKey = array->size;

        if (HGUtilArrayKeyExists(array, nextKey)) {
            return;
        }

        size_t oldSize = array->size;
        void **oldItems = array->items;

        array->size++;
        array->items = (void **) malloc(sizeof(void *) * array->size);

        if (oldSize) {
            memcpy(array->items, oldItems, sizeof(void *) * oldSize);
        }

        array->items[array->size - 1] = item;

        free(oldItems);
    }

    void HGUtilArrayClear(HGUtilArray *array) {
        if (!array->size) {
            return;
        }

        for (size_t i = array->size; i > 0; i--) {
            free((void *) array->items[i - 1]);
        }

        array->size = 0;
    }
#endif