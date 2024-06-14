#include "circle.h"

#ifndef HAARAGAME_COMPONENTS_GEOMETRICS_CIRCLE_C
    #define HAARAGAME_COMPONENTS_GEOMETRICS_CIRCLE_C

    // void HGCircleUpdate(HGCircle *circle);
    void HGCircleRender(HGCircle *circle) {
        DrawCircleV(circle->position, circle->radius, circle->color);
    }
#endif