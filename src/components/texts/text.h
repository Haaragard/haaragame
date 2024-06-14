#include <stdio.h>
#include <stdbool.h>

#include <raylib.h>

#ifndef HAARAGAME_COMPONENTS_TEXTS_TEXT_H
    #define HAARAGAME_COMPONENTS_TEXTS_TEXT_H

    typedef struct haaragame_components_text_text_button {
        char *text;
        Vector2 position;
        int fontSize;
        Color color;
    } HGText;

    void HGTextRender(HGText *);
#endif