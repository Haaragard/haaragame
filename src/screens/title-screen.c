#include "title-screen.h"

#ifndef HAARAGAME_SCREENS_TITLE_SCREEN_C
    #define HAARAGAME_SCREENS_TITLE_SCREEN_C

    void actionButtonHovered();
    void actionButtonClicked(HGNormalButton*);

    void initializeTitleScreen(HGEnv *env) {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];

        screen->elements.memorySize = sizeof(HGComponent);
        HGComponent *component = { 0 };
        {
            component = (HGComponent *) malloc(sizeof(HGComponent));
            component->type = COMPONENT_TYPE_RECTANGLE;
            component->component.rectangle = (Rectangle) {
                .width = 200.f,
                .height = (float)GetScreenHeight(),
                .x = (float)GetScreenWidth() - 200.f,
                .y = 0,
            };

            HGUtilArrayPushItem(&screen->elements, (void *) component);
        }

        {
            component = (HGComponent *) malloc(sizeof(HGComponent));
            component->type = COMPONENT_TYPE_HG_NORMAL_BUTTON;
            component->component.button = (HGNormalButton) {
                .env = env,
                .position = (Vector2) {
                    .x = (float)GetScreenWidth() - 200,
                    .y = 0,
                },
                .height = 50.f,
                .width = 200.f,
                .color = WHITE,
                .inactiveColor = PURPLE,
                .isActive = 1,
            };

            HGUtilArrayPushItem(&screen->elements, (void *) component);
        }

        {
            component = (HGComponent *) malloc(sizeof(HGComponent));
            component->type = COMPONENT_TYPE_HG_TEXT;
            component->component.text = (HGText) {
                .text = "Acessar bacon",
                .position = (Vector2) {
                    .x = (float)GetScreenWidth() - 175,
                    .y = 16.f,
                },
                .fontSize = 20,
                .color = BLACK,
            };

            HGUtilArrayPushItem(&screen->elements, component);
        }

        {
            component = (HGComponent *) malloc(sizeof(HGComponent));
            component->type = COMPONENT_TYPE_HG_NORMAL_BUTTON;
            component->component.button = (HGNormalButton) {
                .env = env,
                .position = (Vector2) {
                    .x = (float)GetScreenWidth()/2 - 100,
                    .y = (float)GetScreenHeight()/2 - 50,
                },
                .height = 50.f,
                .width = 100.f,
                .color = RED,
                .inactiveColor = PURPLE,
                .hasBorder = 1,
                .borderColor = BLUE,
                .borderSize = 1,
                .isActive = 1,
                .onHover = actionButtonHovered,
                .onClick = actionButtonClicked,
            };

            HGUtilArrayPushItem(&screen->elements, component);
        }

        {
            component = (HGComponent *) malloc(sizeof(HGComponent));
            component->type = COMPONENT_TYPE_HG_TEXT;
            component->component.text = (HGText) {
                .text = "Iniciar",
                .position = (Vector2) {
                    .x = (float)GetScreenWidth()/2 - 70,
                    .y = (float)GetScreenHeight()/2 - 32,
                },
                .fontSize = 16,
                .color = WHITE,
            };

            HGUtilArrayPushItem(&screen->elements, component);
        }
    }

    void destroyTitleScreen(HGEnv *env) {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];
        HGUtilArrayClear(&screen->elements);
    }

    void titleScreenUpdate(HGEnv *env)
    {
        if (IsKeyPressed(KEY_SPACE)) {
            setScreenState(env, HG_MENU_SCREEN);

            return;
        }

        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];
        for (size_t i = 0; i < screen->elements.size; i++) {
            HGUpdateComponent((HGComponent *)screen->elements.items[i]);
        }
    }

    void titleScreenRender(HGEnv *env)
    {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];

        BeginDrawing();
            ClearBackground((Color) {0x18, 0x18, 0x18, 0xFF});

            for (size_t i = 0; i < screen->elements.size; i++) {
                HGDrawComponent((HGComponent *)screen->elements.items[i]);
            }
        EndDrawing();
    }

    void actionButtonHovered() {
        HG_DEBUG(HG_LOG_INFO, "Button Hover");
    }

    void actionButtonClicked(HGNormalButton *button) {
        setScreenState(button->env, HG_PLAYING_SCREEN);
        HG_DEBUG(HG_LOG_INFO, "Button Click");
    }

#endif