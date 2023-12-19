#pragma once

#include <SDL2/SDL.h>
#include "../misc/types.h"

// bit-masks for m_activeComponent queries
#define CMP_POSITION 0x00000001
#define CMP_VELOCITY 0x00000002
#define CMP_RENDER   0x00000004
#define CMP_CONTROL  0x00000008

#define CMP_ALL 0xffffffff

#define SYS_CONTROL (CMP_CONTROL | CMP_VELOCITY)
#define SYS_MOVE (CMP_POSITION | CMP_VELOCITY)

struct PositionComponent {
    float x;
    float y;
};

struct VelocityComponent {
    float xV;
    float yV;
};

struct RenderComponent {
    SDL_Rect rect;
    SDL_Texture* texture;
};

struct ControlComponent {
};

struct Entity {
    // serves as index into array of entities
    u64 eID;

    // bits are flags for components 
    u32 activeComponents;

    // possible components
    PositionComponent position;
    VelocityComponent velocity;
    RenderComponent   render;
    ControlComponent  control;

    bool operator<(const Entity& other);
};
