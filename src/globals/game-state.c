#include <raylib.h>

#include "../addons/animation.c"

#ifndef HAARAGAME_GLOBALS_GAME_STATE_C
    #define HAARAGAME_GLOBALS_GAME_STATE_C

    // ------------------------------------------------------------
    // -------------------- Camera definitions --------------------
    // ------------------------------------------------------------

    // Global camera instance
    Camera2D *global_camera = { 0 };

    // Sets global_camera
    void setCamera(Camera2D *camera) {
        global_camera = camera;
    }

    // Retrieves global_camera
    Camera2D *getCamera() {
        return global_camera;
    }
#endif