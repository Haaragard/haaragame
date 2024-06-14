#include <stdio.h>

#include <raylib.h>

#include "sprite.c"

#ifndef HAARAGAME_ADDONS_ANIMATION_C
    #define HAARAGAME_ADDONS_ANIMATION_C

    typedef struct haaragame_addons_animation_t {
        size_t frames; // Animation frames
        size_t actualFrame; // Actual animation frame
        size_t frameSpeed; // How many computed frames will need to change frames
        size_t frameCounter; // How many global frames passed compared to the frameSpeed
        HGSprite *sprites; // Animation Sprites (count of .frames)
    } HGAnimation;

#endif