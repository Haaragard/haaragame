#include <stdio.h>
#include <string.h>

#ifndef HAARAGAME_UTILS_MAP_C
    #define HAARAGAME_UTILS_MAP_C

    typedef struct haaragame_utils_map_t {
        size_t size;
        size_t memorySize;
        char **keys;
        void **items;
    } HGUtilMap;

    int HGUtilMapIsInitiated(HGUtilMap *map) {
        return (int) map->memorySize;
    }

    // Find and returns the named Key (returns 0 for non-existent)
    size_t HGUtilMapFindKey(HGUtilMap *map, char *key) {
        for (size_t i = 0; i < map->size; i++) {
            if (!strcmp(map->keys[i], key)) {
                return i;
            }
        }

        return 0;
    }

    // Returns 0 or 1 depending if the Key exists
    bool HGUtilMapKeyExists(HGUtilMap *map, char *key) {
        return (bool) HGUtilMapFindKey(map, key);
    }

    void HGUtilMapAddItem(HGUtilMap *map, char *key, void *item) {
        if (! HGUtilMapIsInitiated(map)) {
            return;
        }

        if (HGUtilMapKeyExists(map, key)) {
            return;
        }

        size_t oldSize = map->size;
        char **oldKeys = map->keys;
        void **oldItems = map->items;

        map->size++;
        map->keys = (char **) malloc(sizeof(char *) * map->size);
        map->items = (void **) malloc(sizeof(void *) * map->size);

        memcpy(map->keys, oldKeys, sizeof(char *) * oldSize);
        memcpy(map->items, oldItems, sizeof(void *) * oldSize);

        map->keys[map->size - 1] = key;
        map->items[map->size - 1] = item;

        free(oldKeys);
        free(oldItems);
    }
#endif