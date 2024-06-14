#include <stdio.h>
#include <stdbool.h>

#include "map.c"
#include "array.c"
#include "../screens/screen-states.c"
#include "../entities/player.c"

#ifndef HAARAGAME_UTILS_ENV_C
    #define HAARAGAME_UTILS_ENV_C

    typedef struct haaragame_utils_env_t {
        bool paused;
        bool screenUpdated;
        HGScreenState actualScreen;
        HGUtilArray screens;
    } HGEnv;

    // Set Screen State
    void setScreenState(HGEnv *env, HGScreenState screenState) {
        if (!HGUtilArrayKeyExists(&env->screens, screenState)) {
            return;
        }

        HGScreenState actualScreenState = env->actualScreen;
        HGScreen *actualScreen = (HGScreen *)env->screens.items[actualScreenState];
        if (actualScreen->isInitialized && actualScreen->destroy) {
            actualScreen->isInitialized = false;
            actualScreen->destroy(env);
        }

        actualScreenState = env->actualScreen = screenState;
        actualScreen = (HGScreen *)env->screens.items[actualScreenState];
        if (!actualScreen->isInitialized && actualScreen->initialize) {
            actualScreen->isInitialized = true;
            actualScreen->initialize(env);
        }

        env->screenUpdated = true;
    }

#endif