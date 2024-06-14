#include "playing-screen.h"

#ifndef HAARAGAME_SCREENS_PLAYING_SCREEN_C
    #define HAARAGAME_SCREENS_PLAYING_SCREEN_C

    void initializePlayingScreen(HGEnv *env) {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];

        if (!screen->player) {
            screen->player = (HGPlayer *) malloc(sizeof(HGPlayer));
            HGPlayerLoadAnimation(screen->player);

            (*screen->player) = (HGPlayer) {
                .name = "Haaragard",
                .speed = 10.f,
                .width = PLAYER_BASE_WIDTH,
                .height = PLAYER_BASE_HEIGHT,
                .score = 0,
                .state = PLAYER_STATE_IDLE,
                .lastState = PLAYER_STATE_IDLE,
                .activeSide = PLAYER_TURNED_DOWN,
                .position.x = (float)GetScreenWidth()/2,
                .position.y = (float)GetScreenHeight()/2,
                .bounds = (Rectangle) {
                    .x = -PLAYER_BASE_WIDTH,
                    .y = -PLAYER_BASE_HEIGHT*2,
                    .width = PLAYER_BASE_WIDTH*2,
                    .height = PLAYER_BASE_HEIGHT*2,
                }
            };
        }
        if (!screen->camera) {
            screen->camera = (Camera2D *) malloc(sizeof(Camera2D));
            (*screen->camera) = (Camera2D) {
                .rotation = 0.f,
                .zoom = 1.f,
                .offset = screen->player->position,
                .target = screen->player->position
            };
        }

        initializePoints(&screen->points);

        if (!screen->entities.size) {
            screen->entities.memorySize = sizeof(HGCircleEnemy);
        }

        if (!screen->spawners.size) {
            screen->spawners.memorySize = sizeof(HGCircleEnemySpawner);
            HGCircleEnemySpawner *spawner = { 0 };

            {
                spawner = (HGCircleEnemySpawner *) malloc(sizeof(HGCircleEnemySpawner));
                (*spawner) = (HGCircleEnemySpawner) {
                    .body = (HGCircle) {
                        .position = {
                            .x = 0,
                            .y = (float)GetScreenHeight()/2,
                        },
                        .radius = 20.f,
                        .color = RED,
                    },
                };

                HGUtilArrayPushItem(&screen->spawners, (void *) spawner);
            }

            {
                spawner = (HGCircleEnemySpawner *) malloc(sizeof(HGCircleEnemySpawner));
                (*spawner) = (HGCircleEnemySpawner) {
                    .body = (HGCircle) {
                        .position = {
                            .x = (float)GetScreenWidth()/2,
                            .y = 0,
                        },
                        .radius = 20.f,
                        .color = RED,
                    },
                };

                HGUtilArrayPushItem(&screen->spawners, (void *) spawner);
            }

            {
                spawner = (HGCircleEnemySpawner *) malloc(sizeof(HGCircleEnemySpawner));
                (*spawner) = (HGCircleEnemySpawner) {
                    .body = (HGCircle) {
                        .position = {
                            .x = (float)GetScreenWidth(),
                            .y = (float)GetScreenHeight()/2,
                        },
                        .radius = 20.f,
                        .color = RED,
                    },
                };

                HGUtilArrayPushItem(&screen->spawners, (void *) spawner);
            }

            {
                spawner = (HGCircleEnemySpawner *) malloc(sizeof(HGCircleEnemySpawner));
                (*spawner) = (HGCircleEnemySpawner) {
                    .body = (HGCircle) {
                        .position = {
                            .x = (float)GetScreenWidth()/2,
                            .y = (float)GetScreenHeight(),
                        },
                        .radius = 20.f,
                        .color = RED,
                    },
                };

                HGUtilArrayPushItem(&screen->spawners, (void *) spawner);
            }
        }
    }

    void destroyPlayingScreen(HGEnv *env) {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];

        if (screen->player) {
            HGPlayerUnloadAnimation(screen->player);

            free(screen->player);
            screen->player = 0;
        }
        if (screen->camera) {
            free(screen->camera);
            screen->camera = 0;
        }

        destroyPoints(&screen->points);

        { // Destroy entities
            HGUtilArrayClear(&screen->entities);
            screen->entities.memorySize = 0;
        }

        { // Destroy spawners
            HGUtilArrayClear(&screen->spawners);
            screen->spawners.memorySize = 0;
        }
    }

    void playingScreenUpdate(HGEnv *env) {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];

        if (IsKeyPressed(KEY_ONE)) {
            env->paused = false;
            setScreenState(env, HG_TITLE_SCREEN);

            return;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            env->paused = !env->paused;
        }

        if (env->paused) return;

        if (IsKeyDown(KEY_R)) {
            screen->player->score = 0;
            resetPoints(env);
        }

        HGPlayerUpdate(screen->player);
        HGCamera2DUpdate(screen->camera, screen->player);
        updatePoints(screen->player, &screen->points);

        {
            for (size_t i = 0; i < screen->entities.size; i++) {
                HGCircleEnemyUpdate(
                    (HGCircleEnemy *) screen->entities.items[i],
                    screen->player,
                    &screen->entities
                );
            }
        }

        {
            for (size_t i = 0; i < screen->spawners.size; i++) {
                HGCircleEnemySpawnerUpdate(
                    (HGCircleEnemySpawner *) screen->spawners.items[i],
                    &screen->entities
                );
            }
        }
    }

    void drawUi(int points) {
        char text[100] = { 0 };

        sprintf(text, "Points: %d", points);
        DrawText(text, 20, 20, 20, WHITE);
        DrawLineV(
            (Vector2) {20.f, 40.f},
            (Vector2) {130.f, 40.f},
            WHITE
        );
        DrawText("Controls", 20, 70, 20, WHITE);
        DrawText("- W: up", 25, 100, 20, WHITE);
        DrawText("- S: down", 25, 130, 20, WHITE);
        DrawText("- A: left", 25, 160, 20, WHITE);
        DrawText("- D: right", 25, 190, 20, WHITE);
    }

    void playingScreenRender(HGEnv *env) {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];

        BeginDrawing();
            ClearBackground((Color) {0x18, 0x18, 0x18, 0xFF});

            BeginMode2D((*screen->camera));
                renderPoints(screen->camera, &screen->points);
                {
                    for (size_t i = 0; i < screen->spawners.size; i++) {
                        HGCircleEnemySpawnerRender((HGCircleEnemySpawner *) screen->spawners.items[i]);
                    }
                }

                {
                    for (size_t i = 0; i < screen->entities.size; i++) {
                        HGCircleEnemyRender(screen->camera, (HGCircleEnemy *) screen->entities.items[i]);
                    }
                }

                HGPlayerRender(screen->player);
            EndMode2D();

            DrawFPS(GetScreenWidth() - 100, 20);

            drawUi(screen->player->score);
        EndDrawing();
    }

    void initializePoints(HGUtilArray *points) {
        if (HGUtilArrayIsInitiated(points)) {
            return;
        }

        points->memorySize = sizeof(HGPoint);

        int pointsDistance = 100;
        Vector2 screenCenter = (Vector2) {
            (float)GetScreenWidth()/2,
            (float)GetScreenHeight()/2
        };

        for (int i = 0; i < HG_PLAYING_SCREEN_POINTS_PER_ROW; i++) {
            for (int j = 0; j < HG_PLAYING_SCREEN_POINTS_PER_COLUMN; j++) {
                float xAxis = { 0.f };
                xAxis += screenCenter.x;
                xAxis -= pointsDistance * HG_PLAYING_SCREEN_POINTS_PER_ROW/2;
                xAxis += pointsDistance * i;

                float yAxis = { 0.f };
                yAxis += screenCenter.y;
                yAxis += pointsDistance * HG_PLAYING_SCREEN_POINTS_PER_ROW/2;
                yAxis -= pointsDistance * j;

                Vector2 actualCircle = (Vector2) {
                    .x = xAxis,
                    .y = yAxis,
                };

                HGPoint *point = (HGPoint *) malloc(sizeof(HGPoint));
                (*point) = (HGPoint) {
                    .body = {
                        .type = COMPONENT_TYPE_HG_CIRCLE,
                        .component = {
                            .circle = {
                                .position = actualCircle,
                                .radius = 10.f,
                                .color = BLUE,
                            },
                        },
                    },
                    .isActive = true,
                };

                HGUtilArrayPushItem(points, (void *) point);
            }
        }
    }

    void destroyPoints(HGUtilArray *points) {
        HGUtilArrayClear(points);
        points->memorySize = 0;
    }

    void resetPoints(HGEnv *env) {
        HGScreen *screen = (HGScreen *) env->screens.items[env->actualScreen];

        HGPoint *point = { 0 };
        for (size_t i = 0; i < screen->points.size; i++) {
            point = (HGPoint *) screen->points.items[i];
            point->isActive = true;
        }

        screen->player->score = 0;
    }

    void updatePoints(HGPlayer *player, HGUtilArray *points) {
        HGPoint *point = { 0 };
        for (size_t i = 0; i < points->size; i++) {
            point = (HGPoint *) points->items[i];
            if (!point->isActive) {
                continue;
            }

            Rectangle playerBounds = (Rectangle) {
                .x = player->position.x + player->bounds.x,
                .y = player->position.y + player->bounds.y,
                .width = player->bounds.width,
                .height = player->bounds.height,
            };

            if (CheckCollisionCircleRec(
                point->body.component.circle.position,
                point->body.component.circle.radius,
                playerBounds
            )) {
                point->isActive = false;
                player->score++;
            }
        }
    }

    void renderPoints(Camera2D *camera, HGUtilArray *points) {
        HGPoint *point = { 0 };
        for (size_t i = 0; i < points->size; i++) {
            point = (HGPoint *) points->items[i];

            if (!point->isActive) {
                continue;
            }

            HGComponentRender(&point->body, camera);

            // if (!HGCamera2DHasCircleInside(camera, &point->circle)) continue;

            // HGCircleRender(&point->circle);
        }
    }

#endif