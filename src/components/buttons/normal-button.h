#include <stdbool.h>

#include <raylib.h>

#include "../../utils/env.c"

#ifndef HAARAGAME_COMPONENTS_BUTTONS_NORMAL_BUTTON_H
    #define HAARAGAME_COMPONENTS_BUTTONS_NORMAL_BUTTON_H

    typedef struct haaragame_components_buttons_normal_button_t {
        HGEnv *env;
        Vector2 position;
        Rectangle bounds;
        float height;
        float width;
        Color color;
        bool isActive;
        bool isHovered;
        bool isClicked;
        Color inactiveColor;
        bool hasBorder;
        Color borderColor;
        int borderSize;
        void (*onHover)(); // callback usage
        void (*onClick)(); // callback usage
    } HGNormalButton;

    void HGNormalButtonUpdate(HGNormalButton *);
    void HGNormalButtonRender(HGNormalButton *);
#endif