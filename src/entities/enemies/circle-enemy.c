#include <stdio.h>

#include <raylib.h>

#include "../../components/geometrics/circle.c"
#include "../player.c"
#include "../../addons/camera.c"

#ifndef HAARAGAME_ENTITIES_ENEMIES_CIRCLE_ENEMY_C
    #define HAARAGAME_ENTITIES_ENEMIES_CIRCLE_ENEMY_C

    typedef struct haaragame_entities_enemies_circle_enemy_t {
        size_t id;
        HGCircle body;
    } HGCircleEnemy;

    void HGCircleEnemyUpdate(HGCircleEnemy *enemy, HGPlayer *player, HGUtilArray *enemies) {
        Rectangle playerBounds = (Rectangle) {
            .x = player->position.x + player->bounds.x,
            .y = player->position.y + player->bounds.y,
            .width = player->bounds.width,
            .height = player->bounds.height,
        };

        if (CheckCollisionCircleRec(
            enemy->body.position,
            enemy->body.radius,
            playerBounds
        )) {
            return;
        }

        Vector2 positionComparison = (Vector2) {
            .x = player->position.x - enemy->body.position.x,
            .y = (player->position.y + player->height/2) - enemy->body.position.y,
        };

        Vector2 newXPos = (Vector2) {
            .x = enemy->body.position.x + ((positionComparison.x > 0) ? 50 : -50) * GetFrameTime(),
            .y = enemy->body.position.y,
        };
        Vector2 newYPos = (Vector2) {
            .x = enemy->body.position.x,
            .y = enemy->body.position.y + ((positionComparison.y > 0) ? 50 : -50) * GetFrameTime(),
        };

        bool posXCollided = { false };
        bool posYCollided = { false };

        for (size_t i = 0; i < enemies->size; i++) {
            if (posXCollided && posYCollided) break;

            HGCircleEnemy *enemyIterator = (HGCircleEnemy *) enemies->items[i];
            if (enemy->id == enemyIterator->id) continue;

            if (!posXCollided) {
                // Vector2 comparisonX = (Vector2) {
                //     .x = newXPos.x - enemy->body.position.x,
                //     .y = (player->position.y + player->height/2) - enemy->body.position.y,
                // };

                posXCollided = CheckCollisionCircles(
                    newXPos,
                    enemy->body.radius,
                    enemyIterator->body.position,
                    enemyIterator->body.radius
                );
            }
            
            if (!posYCollided) {
                posYCollided = CheckCollisionCircles(
                    newYPos,
                    enemy->body.radius,
                    enemyIterator->body.position,
                    enemyIterator->body.radius
                );
            }
        }

        enemy->body.position = (Vector2) {
            .x = (posXCollided) ? enemy->body.position.x : newXPos.x,
            .y = (posYCollided) ? enemy->body.position.y : newYPos.y,
        };
    }

    void HGCircleEnemyRender(Camera2D *camera, HGCircleEnemy *enemy) {
        if (!HGCamera2DHasCircleInside(camera, &enemy->body)) {
            return;
        }

        HGCircleRender(&enemy->body);
    }

#endif