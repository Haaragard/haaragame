#include "normal-button.h"

#ifndef HAARAGAME_COMPONENTS_BUTTONS_NORMAL_BUTTON_C
    #define HAARAGAME_COMPONENTS_BUTTONS_NORMAL_BUTTON_C

    void HGNormalButtonUpdate(HGNormalButton *button) {
        button->isHovered = false;
        button->isClicked = false;

        button->bounds.x = button->position.x;
        button->bounds.y = button->position.y;
        button->bounds.width = button->width;
        button->bounds.height = button->height;

        if (!button->isActive) return;

        button->isHovered = CheckCollisionPointRec(GetMousePosition(), button->bounds);
        if (button->isHovered && button->onHover) {
            button->onHover(button);
        }

        button->isClicked = button->isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        if (button->isClicked && button->onClick) {
            button->onClick(button);
        }
    }

    void HGNormalButtonRender(HGNormalButton *button) {
        Color renderColor = (button->isActive) ? button->color : button->inactiveColor;

        DrawRectangleRec(button->bounds, renderColor);
        if (button->hasBorder && button->borderSize) {
            DrawRectangleLines(
                button->position.x,
                button->position.y,
                button->width,
                button->height,
                button->borderColor
            );
        }
    }

#endif