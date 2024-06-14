#include <stdbool.h>

#include <raylib.h>

#include "../../utils/env.c"

#ifndef HAARAGAME_COMPONENTS_GEOMETRICS_CIRCLE_H
    #define HAARAGAME_COMPONENTS_GEOMETRICS_CIRCLE_H

    typedef struct haaragame_components_geometrics_circle_t {
        Vector2 position;
        float radius;
        Color color;
    } HGCircle;

    // void HGCircleUpdate(HGCircle *);
    void HGCircleRender(HGCircle *);
#endif