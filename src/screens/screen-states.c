#include <stdio.h>
#include <stdbool.h>

#include "../utils/array.c"
#include "../entities/player.c"

#ifndef HAARAGAME_SCREENS_SCREEN_STATES_C
    #define HAARAGAME_SCREENS_SCREEN_STATES_C

    typedef enum haaragame_screens_screen_state_enum_t {
        HG_LOADING_SCREEN,
        HG_TITLE_SCREEN,
        HG_MENU_SCREEN,
        HG_PLAYING_SCREEN,
    } HGScreenState;

    typedef struct haaragame_screens_screen_t {
        HGScreenState screen;
        char *screenName;
        bool isInitialized;
        void (*initialize)();
        void (*destroy)();
        void (*update)();
        void (*render)();
        HGPlayer *player;
        Camera2D *camera;
        HGUtilArray elements;
        HGUtilArray spawners;
        HGUtilArray entities;
        HGUtilArray points;
    } HGScreen;

#endif