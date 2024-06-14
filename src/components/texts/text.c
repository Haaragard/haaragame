#include "text.h"

#ifndef HAARAGAME_COMPONENTS_TEXTS_TEXT_C
    #define HAARAGAME_COMPONENTS_TEXTS_TEXT_C

    void HGTextRender(HGText *text) {
        DrawText(text->text, text->position.x, text->position.y, text->fontSize, text->color);
    }
#endif