#include <stdbool.h>

#include <raylib.h>

#include "screen-states.c"
#include "../utils/env.c"

#include "../components/component.c"
#include "../components/buttons/normal-button.c"
#include "../components/texts/text.c"

#ifndef HAARAGAME_SCREENS_TITLE_SCREEN_H
    #define HAARAGAME_SCREENS_TITLE_SCREEN_H

    void initializeTitleScreen(HGEnv *);
    void destroyTitleScreen(HGEnv *);
    void titleScreenUpdate(HGEnv *);
    void titleScreenRender(HGEnv *);

#endif