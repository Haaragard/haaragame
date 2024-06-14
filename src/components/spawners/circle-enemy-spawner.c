#include <stdio.h>

#include <raylib.h>

#include "../../utils/array.c"

#include "../geometrics/circle.c"
#include "../../entities/enemies/circle-enemy.c"

#ifndef HAARAGAME_COMPONENTS_SPAWNERS_CIRCLE_ENEMY_SPAWNER_C
    #define HAARAGAME_COMPONENTS_SPAWNERS_CIRCLE_ENEMY_SPAWNER_C

    typedef struct haaragame_components_spawners_circle_enemy_spawner_t {
        HGCircle body;
        size_t spawnedEnemies;
        size_t spawnTimeInterval;
        size_t frameCounter;
    } HGCircleEnemySpawner;

    void HGCircleEnemySpawnerUpdate(HGCircleEnemySpawner *spawner, HGUtilArray *enemies) {
        if (spawner->spawnedEnemies > 4) {
            return;
        }

        size_t enemyNumber = spawner->spawnedEnemies + 1;

        {
            HGCircleEnemy *enemy = (HGCircleEnemy *) malloc(sizeof(HGCircleEnemy));
            (*enemy) = (HGCircleEnemy) {
                .id = enemies->size +1,
                .body = {
                    .position = {
                        .x = spawner->body.position.x + 100 * enemyNumber,
                        .y = spawner->body.position.y + 100 * enemyNumber,
                    },
                    .radius = 20,
                    .color = WHITE,
                },
            };

            HGUtilArrayPushItem(enemies, enemy);
        }

        spawner->spawnedEnemies++;
    }

    void HGCircleEnemySpawnerRender(HGCircleEnemySpawner *spawner) {
        HGCircleRender(&spawner->body);
    }

#endif