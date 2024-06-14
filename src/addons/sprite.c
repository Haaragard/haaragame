#include <stdbool.h>

#include <raylib.h>

#ifndef HAARAGAME_ADDONS_SPRITE_C
    #define HAARAGAME_ADDONS_SPRITE_C

    typedef struct haaragame_addons_sprite_size_t {
        unsigned int width;
        unsigned int height;
    } HGSpriteSize;

    typedef struct haaragame_addons_sprite_t {
        HGSpriteSize size;
        Texture2D texture;
        Rectangle frame;
        Color color;
    } HGSprite;

    void HGDrawSprite(HGSprite sprite, Vector2 location) {
        DrawTextureRec(
            sprite.texture,
            sprite.frame,
            (Vector2) {
                .x = location.x - (float)sprite.size.width,
                .y = location.y - (float)sprite.size.height,
            },
            sprite.color
        );
    }

    void HGDrawSpritePro(HGSprite sprite, Rectangle bounds, Vector2 location) {
        DrawTexturePro(
            sprite.texture,
            sprite.frame,
            bounds,
            (Vector2) {
                .x = -location.x,
                .y = -location.y,
            },
            0.f,
            sprite.color
        );
    }
#endif