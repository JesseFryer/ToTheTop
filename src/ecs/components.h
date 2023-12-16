#pragma once

#include <SDL2/SDL.h>
#include "../misc/types.h"

struct RenderComponent {
    u64 eID;
    SDL_Rect rect;
};

struct ControlComponent {
    u64 eID;
};

struct VelocityComponent {
    u64 eID;
    float x;
    float y;
};
