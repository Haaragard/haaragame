#include "player.h"

#include <string.h>

#include "../utils/debug.c"

#ifndef HAARAGAME_ENTITIES_PLAYER_C
    #define HAARAGAME_ENTITIES_PLAYER_C

    void HGPlayerLoadAnimation(HGPlayer *player) {
        player->sprite = LoadTexture(PLAYER_SPRITE_PATH);
    
        // IDLE ANIMATION INIT ------------------------------------------------------
        {
            Rectangle animationsMap[] = {
                [PLAYER_TURNED_DOWN] = (Rectangle)PLAYER_SPRITE_LOCATION_IDLE_DOWN,
                [PLAYER_TURNED_RIGHT] = (Rectangle)PLAYER_SPRITE_LOCATION_IDLE_RIGHT,
                [PLAYER_TURNED_LEFT] = (Rectangle)PLAYER_SPRITE_LOCATION_IDLE_LEFT,
                [PLAYER_TURNED_TOP] = (Rectangle)PLAYER_SPRITE_LOCATION_IDLE_TOP,
            };

            size_t itemsQuantity = sizeof(animationsMap)/sizeof(animationsMap[0]);
            for (size_t spriteLocation = 0; spriteLocation < itemsQuantity; spriteLocation++) {
                playerAnimationIdle[spriteLocation] = (HGAnimation *) malloc(sizeof(HGAnimation));
                playerAnimationIdle[spriteLocation]->frames = PLAYER_SPRITE_IDLE_COUNT;
                playerAnimationIdle[spriteLocation]->frameSpeed = PLAYER_BASE_ANIMATION_SPEED;
                playerAnimationIdle[spriteLocation]->actualFrame = 0;
                playerAnimationIdle[spriteLocation]->frameCounter = 0;
                playerAnimationIdle[spriteLocation]->sprites = (HGSprite *) malloc(sizeof(HGSprite) * PLAYER_SPRITE_IDLE_COUNT);

                Rectangle frame = animationsMap[spriteLocation];
                for (size_t spritePosition = 0; spritePosition < PLAYER_SPRITE_IDLE_COUNT; spritePosition++) {
                    frame.x = PLAYER_SPRITE_SIZE * spritePosition;

                    playerAnimationIdle[spriteLocation]->sprites[spritePosition] = (HGSprite) {
                        .size = (HGSpriteSize) {
                            .width = PLAYER_SPRITE_RENDER_WIDTH,
                            .height = PLAYER_SPRITE_RENDER_HEIGHT,
                        },
                        .texture = player->sprite,
                        .frame = frame,
                        .color = WHITE,
                    };
                }
            }
        }
        // IDLE ANIMATION END -------------------------------------------------------

        // WALK ANIMATION INIT ------------------------------------------------------
        {
            Rectangle animationsMap[] = {
                [PLAYER_TURNED_DOWN] = PLAYER_SPRITE_LOCATION_WALK_DOWN,
                [PLAYER_TURNED_RIGHT] = PLAYER_SPRITE_LOCATION_WALK_RIGHT,
                [PLAYER_TURNED_LEFT] = PLAYER_SPRITE_LOCATION_WALK_LEFT,
                [PLAYER_TURNED_TOP] = PLAYER_SPRITE_LOCATION_WALK_TOP,
            };

            size_t itemsQuantity = sizeof(animationsMap)/sizeof(animationsMap[0]);
            for (size_t spriteLocation = 0; spriteLocation < itemsQuantity; spriteLocation++) {
                playerAnimationWalk[spriteLocation] = (HGAnimation *) malloc(sizeof(HGAnimation));
                playerAnimationWalk[spriteLocation]->frames = PLAYER_SPRITE_WALK_COUNT;
                playerAnimationWalk[spriteLocation]->frameSpeed = PLAYER_BASE_ANIMATION_SPEED;
                playerAnimationWalk[spriteLocation]->actualFrame = 0;
                playerAnimationWalk[spriteLocation]->frameCounter = 0;
                playerAnimationWalk[spriteLocation]->sprites = (HGSprite *) malloc(sizeof(HGSprite) * PLAYER_SPRITE_WALK_COUNT);

                Rectangle frame = animationsMap[spriteLocation];
                for (size_t spritePosition = 0; spritePosition < PLAYER_SPRITE_WALK_COUNT; spritePosition++) {
                    frame.x = PLAYER_SPRITE_SIZE * spritePosition;

                    playerAnimationWalk[spriteLocation]->sprites[spritePosition] = (HGSprite) {
                        .size = (HGSpriteSize) {
                            .width = PLAYER_SPRITE_RENDER_WIDTH,
                            .height = PLAYER_SPRITE_RENDER_HEIGHT,
                        },
                        .texture = player->sprite,
                        .frame = frame,
                        .color = WHITE,
                    };
                }
            }
        }
        // WALK ANIMATION END -------------------------------------------------------
    }

    void HGPlayerUnloadAnimation(HGPlayer *player) {
        HGAnimation *loadedAnimations[] = {
            playerAnimationIdle[PLAYER_TURNED_DOWN],
            playerAnimationIdle[PLAYER_TURNED_RIGHT],
            playerAnimationIdle[PLAYER_TURNED_LEFT],
            playerAnimationIdle[PLAYER_TURNED_TOP],

            playerAnimationWalk[PLAYER_TURNED_DOWN],
            playerAnimationWalk[PLAYER_TURNED_RIGHT],
            playerAnimationWalk[PLAYER_TURNED_LEFT],
            playerAnimationWalk[PLAYER_TURNED_TOP],
        };

        size_t arraySize = sizeof(loadedAnimations)/sizeof(loadedAnimations[0]);
        for (size_t i = 0; i < arraySize; i++) {
            free(loadedAnimations[i]->sprites);
            free(loadedAnimations[i]);
        }

        UnloadTexture(player->sprite);
    }

    void playerAnimationUpdate(HGPlayer *player) {
        HGAnimation *animation = { 0 };
        switch (player->state) {
            case PLAYER_STATE_IDLE:
                    animation = playerAnimationIdle[player->activeSide];
                break;
            case PLAYER_STATE_WALKING:
            case PLAYER_STATE_RUNNING:
                    animation = playerAnimationWalk[player->activeSide];
                break;
            default:
                break;
        }

        if (animation) {
            if (player->lastState != player->state) {
                animation->frameCounter = 0;
                animation->actualFrame = 0;
            }
    
            animation->frameCounter++;
            size_t frameSpeed = animation->frameSpeed;
            if (player->state == PLAYER_STATE_RUNNING) {
                frameSpeed += animation->frameSpeed * PLAYER_BOOST_MULTIPLIER;
            }
            
            if (animation->frameCounter >= (GetFPS()/frameSpeed)) {
                animation->frameCounter = 0;
                animation->actualFrame++;
                if (animation->actualFrame >= animation->frames) {
                    animation->actualFrame = 0;
                }
            }
        }
    }

    void HGPlayerUpdate(HGPlayer* player) {
        player->state = PLAYER_STATE_IDLE;

        float playerWalkSpeed = { player->speed * PLAYER_BASE_SPEED * GetFrameTime() };
        int isPlayerBoosted = { 0 };
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            isPlayerBoosted = 1;
            playerWalkSpeed += playerWalkSpeed * PLAYER_BOOST_MULTIPLIER;
        }

        if (IsKeyDown(KEY_W)) {
            player->position.y -= playerWalkSpeed;
            player->state = isPlayerBoosted ? PLAYER_STATE_RUNNING : PLAYER_STATE_WALKING;
            player->activeSide = PLAYER_TURNED_TOP;
        }
        
        if (IsKeyDown(KEY_S)) {
            player->position.y += playerWalkSpeed;
            player->state = isPlayerBoosted ? PLAYER_STATE_RUNNING : PLAYER_STATE_WALKING;
            player->activeSide = PLAYER_TURNED_DOWN;
        }

        if (IsKeyDown(KEY_A)) {
            player->position.x -= playerWalkSpeed;
            player->state = isPlayerBoosted ? PLAYER_STATE_RUNNING : PLAYER_STATE_WALKING;
            player->activeSide = PLAYER_TURNED_LEFT;
        }

        if (IsKeyDown(KEY_D)) {
            player->position.x += playerWalkSpeed;
            player->state = isPlayerBoosted ? PLAYER_STATE_RUNNING : PLAYER_STATE_WALKING;
            player->activeSide = PLAYER_TURNED_RIGHT;
        }

        playerAnimationUpdate(player);

        player->lastState = player->state;

        // {
        //     char *playerState = { 0 };
        //     switch (player->state) {
        //         case PLAYER_STATE_IDLE:
        //             playerState = "PLAYER IDLE";
        //             break;
        //         case PLAYER_STATE_WALKING:
        //             playerState = "PLAYER WALKING";
        //             break;
        //         case PLAYER_STATE_RUNNING:
        //             playerState = "PLAYER RUNNING";
        //             break;
        //         default:
        //             break;
        //     }

        //     HG_DEBUG(HG_LOG_INFO, "Player state = %s", playerState);

        //     char *playerActiveSide = { 0 };
        //     switch (player->activeSide) {
        //         case PLAYER_TURNED_DOWN:
        //             playerActiveSide = "PLAYER IS TURNED DOWN";
        //             break;
        //         case PLAYER_TURNED_RIGHT:
        //             playerActiveSide = "PLAYER IS TURNED RIGHT";
        //             break;
        //         case PLAYER_TURNED_LEFT:
        //             playerActiveSide = "PLAYER IS TURNED LEFT";
        //             break;
        //         case PLAYER_TURNED_TOP:
        //             playerActiveSide = "PLAYER IS TURNED TOP";
        //             break;
        //         default:
        //             break;
        //     }

        //     HG_DEBUG(HG_LOG_INFO, "Player activeSide = %s", playerActiveSide);
        // }
    }

    void HGPlayerRender(HGPlayer *player) {
        HGAnimation *animation = { 0 };
        switch (player->state) {
            case PLAYER_STATE_IDLE:
                    animation = playerAnimationIdle[player->activeSide];
                break;
            case PLAYER_STATE_WALKING:
            case PLAYER_STATE_RUNNING:
                    animation = playerAnimationWalk[player->activeSide];
                break;
            default:
                break;
        }

        if (animation) {
            HGDrawSpritePro(
                animation->sprites[animation->actualFrame],
                (Rectangle) {
                    .x = -player->width*2.5,
                    .y = -player->height*4.3,
                    .width = player->width*5,
                    .height = player->height*5,
                },
                player->position
            );
        }

        DrawRectangleLinesEx((Rectangle) {
            .x = player->position.x + player->bounds.x,
            .y = player->position.y + player->bounds.y,
            .width = player->bounds.width,
            .height = player->bounds.height,
        }, 1.f, WHITE);
    }
#endif