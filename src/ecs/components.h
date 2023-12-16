#pragma once

#include <SDL2/SDL.h>
#include "../misc/types.h"

// bit-masks for m_activeComponent queries
#define CMP_RENDER   0x00000001
#define CMP_CONTROL  0x00000002
#define CMP_VELOCITY 0x00000004 
#define CMP_POSITION 0x00000008 

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

struct PositionComponent {
    u64 eID;
    float x;
    float y;
};
