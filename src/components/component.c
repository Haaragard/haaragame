#include <stdio.h>
#include <stdbool.h>

#include <raylib.h>

#include "../addons/camera.c"

#include "geometrics/circle.c"
#include "buttons/normal-button.c"
#include "texts/text.c"

#ifndef HAARAGAME_COMPONENTS_COMPONENT_C
    #define HAARAGAME_COMPONENTS_COMPONENT_C

    typedef enum haaragame_components_component_type_enum_t {
        COMPONENT_TYPE_HG_CIRCLE,
        COMPONENT_TYPE_RECTANGLE,
        COMPONENT_TYPE_HG_NORMAL_BUTTON,
        COMPONENT_TYPE_HG_TEXT,
        COMPONENT_TYPE_HG_POINT,
    } HGComponentTypes;

    typedef union haaragame_components_component_type_union_t {
        HGCircle circle;
        Rectangle rectangle;
        HGNormalButton button;
        HGText text;
    } HGComponentType;

    typedef struct haaragame_components_component_t {
        HGComponentTypes type;
        HGComponentType component;
    } HGComponent;

    void HGUpdateComponent(HGComponent *component) {
        switch(component->type) {
            case COMPONENT_TYPE_HG_NORMAL_BUTTON:
                HGNormalButtonUpdate(&component->component.button);
                break;
            default:
                break;
        }
    }

    void HGDrawComponent(HGComponent *component) {
        switch(component->type) {
            case COMPONENT_TYPE_HG_CIRCLE:
                HGCircleRender(&component->component.circle);
                break;
            case COMPONENT_TYPE_RECTANGLE:
                DrawRectangleRec((Rectangle) component->component.rectangle, BLUE);
                break;
            case COMPONENT_TYPE_HG_NORMAL_BUTTON:
                HGNormalButtonRender(&component->component.button);
                break;
            case COMPONENT_TYPE_HG_TEXT:
                HGTextRender(&component->component.text);
                break;
            case COMPONENT_TYPE_HG_POINT:
                HGTextRender(&component->component.text);
                break;
            default:
                break;
        }
    }

    bool HGComponentIsOnView(HGComponent *component, Camera2D *camera) {
        switch(component->type) {
            case COMPONENT_TYPE_HG_CIRCLE:
                return HGCamera2DHasCircleInside(camera, &component->component.circle);
            // case COMPONENT_TYPE_RECTANGLE:
            //     DrawRectangleRec((Rectangle) component->component.rectangle, BLUE);
            //     break;
            // case COMPONENT_TYPE_HG_NORMAL_BUTTON:
            //     HGNormalButtonRender(&component->component.button);
            //     break;
            // case COMPONENT_TYPE_HG_TEXT:
            //     HGTextRender(&component->component.text);
            //     break;
            // case COMPONENT_TYPE_HG_POINT:
            //     break;
            default:
                return false;
        }
    }

    void HGComponentRender(HGComponent *component, Camera2D *camera) {
        if (!HGComponentIsOnView(component, camera)) {
            return;
        }

        HGDrawComponent(component);
    }

#endif