#include <stdio.h>
#include <stdbool.h>

#include <raylib.h>

#include "../entities/player.c"
#include "../components/geometrics/circle.h"

#ifndef HAARAGAME_ADDONS_CAMERA_C
    #define HAARAGAME_ADDONS_CAMERA_C

    void HGCamera2DUpdate(Camera2D *camera, HGPlayer *player) {
        camera->target = player->position;
    }

    bool HGCamera2DHasCircleInside(Camera2D *camera, HGCircle *circle) {
        Vector2 screenSize = (Vector2) {
            .x = (float)GetScreenWidth(),
            .y = (float)GetScreenHeight(),
        };

        Rectangle screenBounds = (Rectangle) {
            .x = camera->target.x - screenSize.x/2,
            .y = camera->target.y - screenSize.y/2,
            .width = screenSize.x,
            .height = screenSize.y,
        };

        return CheckCollisionCircleRec(
            circle->position,
            circle->radius,
            screenBounds
        );
    }

#endif