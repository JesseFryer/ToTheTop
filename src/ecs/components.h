#pragma once

#include <SDL2/SDL.h>
#include "../misc/types.h"

// bit-masks for m_activeComponent queries
#define CMP_RENDER    0x00000001
#define CMP_CONTROL   0x00000002
#define CMP_TRANSFORM 0x00000004 

struct Component {
    u64 eID;
    bool operator<(const Component& other);
};

struct RenderComponent : Component {
};

struct ControlComponent : Component {
};

struct TransformComponent : Component {
    float x;
    float y;
    float xV;
    float yV;
    SDL_Rect rect;
};
