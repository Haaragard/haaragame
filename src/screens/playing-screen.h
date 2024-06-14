#include <stdbool.h>

#include <raylib.h>

#include "../utils/debug.c"
#include "../utils/env.c"

#include "screen-states.c"

#include "../globals/game-state.c"

#include "../addons/camera.c"
#include "../entities/player.c"

#include "../components/component.c"
#include "../components/geometrics/circle.c"
#include "../components/spawners/circle-enemy-spawner.c"

#ifndef HAARAGAME_SCREENS_PLAYING_SCREEN_H
    #define HAARAGAME_SCREENS_PLAYING_SCREEN_H

    typedef struct haaragame_point_t {
        HGComponent body;
        size_t isActive;
    } HGPoint;

    // ------------------------------------------------------------
    // ----------------- HGPlayer-Screen definitions ----------------
    // ------------------------------------------------------------

    // Initialize the playing screen state objects
    void initializePlayingScreen(HGEnv *);

    // Destroy the playing screen state objects
    void destroyPlayingScreen(HGEnv *);

    // Update playing screen
    void playingScreenUpdate(HGEnv *);

    // Render playing screen
    void playingScreenRender(HGEnv *);

    // Usable functions

    #define HG_PLAYING_SCREEN_POINTS_PER_ROW 100
    #define HG_PLAYING_SCREEN_POINTS_PER_COLUMN 100

    void initializePoints(HGUtilArray *);
    void destroyPoints(HGUtilArray *);
    void resetPoints(HGEnv *);
    void updatePoints(HGPlayer *, HGUtilArray *);
    void renderPoints(Camera2D *, HGUtilArray *);

#endif