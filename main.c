#include "main.h"

#define SCREEN_MAX (Vector2) {GetScreenWidth(), GetScreenHeight()}
#define SCREEN_CENTER_V (Vector2) {GetScreenWidth()/2.f, GetScreenHeight()/2.f}

int main(void) {
    HGEnv *env = &(HGEnv) {
        .screenUpdated = false,
        .actualScreen = HG_LOADING_SCREEN,
        .screens.memorySize = sizeof(HGScreen),
    };

    HGUtilArraySetItem(&env->screens, (size_t) HG_TITLE_SCREEN, (void *) &(HGScreen) {
        .screen = HG_LOADING_SCREEN,
        .screenName = "LOADING",
        .isInitialized = false,
    });
    HGUtilArraySetItem(&env->screens, (size_t) HG_TITLE_SCREEN, (void *) &(HGScreen) {
        .screen = HG_TITLE_SCREEN,
        .screenName = "Title",
        .isInitialized = false,
        .initialize = initializeTitleScreen,
        .destroy = destroyTitleScreen,
        .update = titleScreenUpdate,
        .render = titleScreenRender,
    });
    HGUtilArraySetItem(&env->screens, (size_t) HG_MENU_SCREEN, &(HGScreen) {
        .screen = HG_MENU_SCREEN,
        .screenName = "Menu",
        .isInitialized = false,
    });
    HGUtilArraySetItem(&env->screens, (size_t) HG_PLAYING_SCREEN, &(HGScreen) {
        .screen = HG_PLAYING_SCREEN,
        .screenName = "Play",
        .isInitialized = false,
        .initialize = initializePlayingScreen,
        .destroy = destroyPlayingScreen,
        .update = playingScreenUpdate,
        .render = playingScreenRender,
    });

    SetTargetFPS(DEFAULT_FPS);
    InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "HaaraGame");

    setScreenState(env, HG_TITLE_SCREEN);

    while (!WindowShouldClose()) {
        env->screenUpdated = false;

        update(env);
        render(env);
    }

    CloseWindow();
}

void update(HGEnv *env) {
    HGScreenState screenState = env->actualScreen;
    HGScreen *actualScreen = (HGScreen *)env->screens.items[screenState];

    if (actualScreen->update) {
        actualScreen->update(env);
    } else {
        if (IsKeyPressed(KEY_SPACE)) {
            setScreenState(env, HG_TITLE_SCREEN);
        }
    }
}

void render(HGEnv *env) {
    HGScreenState screenState = env->actualScreen;
    HGScreen *actualScreen = (HGScreen *)env->screens.items[screenState];

    if (actualScreen->render) {
        if (!env->screenUpdated) actualScreen->render(env);
    } else {
        BeginDrawing();
            ClearBackground(DARKBLUE);
        EndDrawing();
    }
}
