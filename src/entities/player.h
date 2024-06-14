#include <stdbool.h>

#include <raylib.h>

#include "../../configs/consts.c"

#include "../addons/sprite.c"
#include "../addons/animation.c"

#ifndef HAARAGAME_ENTITIES_PLAYER_H
    #define HAARAGAME_ENTITIES_PLAYER_H

    #define PLAYER_SPRITE_PATH "sprites/characters/player.png"
    #define PLAYER_SPRITE_SIZE 48
    #define PLAYER_SPRITE_RENDER_WIDTH 24
    #define PLAYER_SPRITE_RENDER_HEIGHT 43

    // Player Sprite IDLE
    #define PLAYER_SPRITE_IDLE_COUNT 6
    #define PLAYER_SPRITE_LOCATION_IDLE_DOWN (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = 0, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}
    #define PLAYER_SPRITE_LOCATION_IDLE_RIGHT (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}
    #define PLAYER_SPRITE_LOCATION_IDLE_LEFT (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE, .width = (float)-PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE} // Needs to reverse the WIDTH
    #define PLAYER_SPRITE_LOCATION_IDLE_TOP (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 2, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}

    // Player Sprite WALK
    #define PLAYER_SPRITE_WALK_COUNT 6
    #define PLAYER_SPRITE_LOCATION_WALK_DOWN (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 3, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}
    #define PLAYER_SPRITE_LOCATION_WALK_RIGHT (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 4, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}
    #define PLAYER_SPRITE_LOCATION_WALK_LEFT (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 4, .width = (float)-PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE} // Needs to reverse the WIDTH
    #define PLAYER_SPRITE_LOCATION_WALK_TOP (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 5, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}

    // Player Sprite ATTACK
    #define PLAYER_SPRITE_ATTACK_COUNT 4
    #define PLAYER_SPRITE_LOCATION_ATTACK_DOWN (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 6, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}
    #define PLAYER_SPRITE_LOCATION_ATTACK_RIGHT (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 7, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}
    #define PLAYER_SPRITE_LOCATION_ATTACK_LEFT (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 7, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE} // Needs to reverse the WIDTH
    #define PLAYER_SPRITE_LOCATION_ATTACK_TOP (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 8, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}

    // Player Sprite DEATH
    #define PLAYER_SPRITE_DEATH_RIGHT_COUNT 3
    #define PLAYER_SPRITE_LOCATION_DEATH_RIGHT (Rectangle) { .x = (float)PLAYER_SPRITE_SIZE, .y = (float)PLAYER_SPRITE_SIZE * 9, .width = (float)PLAYER_SPRITE_SIZE, .height = (float)PLAYER_SPRITE_SIZE}

    #define PLAYER_BASE_WIDTH (float)PLAYER_SPRITE_SIZE
    #define PLAYER_BASE_HEIGHT (float)PLAYER_SPRITE_SIZE

    #define PLAYER_BASE_SPEED 70.f

    #define PLAYER_BASE_ANIMATION_SPEED 8
    #define PLAYER_BOOST_MULTIPLIER 0.4

    typedef enum {
        PLAYER_STATE_IDLE,
        PLAYER_STATE_WALKING,
        PLAYER_STATE_RUNNING,
        PLAYER_STATE_DEAD,
    } HGPlayerState;

    #define PLAYER_ANIMATION_SIDES_COUNT 4

    typedef enum {
        PLAYER_TURNED_DOWN,
        PLAYER_TURNED_RIGHT,
        PLAYER_TURNED_LEFT,
        PLAYER_TURNED_TOP,
    } HGPlayerTurnSide;

    typedef struct haaragame_entities_player_t {
        char *name;
        float speed;
        Vector2 position;
        float height;
        float width;
        Rectangle bounds;
        unsigned int score;
        HGPlayerState state;
        HGPlayerState lastState;
        HGPlayerTurnSide activeSide;
        Texture2D sprite;
    } HGPlayer;

    HGAnimation *playerAnimationIdle[PLAYER_ANIMATION_SIDES_COUNT] = { 0 };
    HGAnimation *playerAnimationWalk[PLAYER_ANIMATION_SIDES_COUNT] = { 0 };

    void HGPlayerLoadAnimation(HGPlayer *);
    void HGPlayerUnloadAnimation(HGPlayer *);
    void HGPlayerUpdate(HGPlayer*);
    void HGPlayerRender(HGPlayer*);

#endif