#pragma once

#include <SDL2/SDL.h>
#include "../misc/types.h"
#include "../input/input.h"

// bit-masks for m_activeComponent queries
#define CMP_ALL      0xffffffff
#define CMP_POSITION 0x00000001
#define CMP_VELOCITY 0x00000002
#define CMP_RENDER   0x00000004
#define CMP_CONTROL  0x00000008

// for systems that require multiple components
#define SYS_CONTROL (CMP_CONTROL | CMP_VELOCITY)
#define SYS_MOVE    (CMP_POSITION | CMP_VELOCITY)

struct Entity;

typedef void (*control_func)(Entity&, InputState*);

struct PositionComponent {
    float x = 0;
    float y = 0;
};

struct VelocityComponent {
    float xV = 0;
    float yV = 0;
};

struct RenderComponent {
    SDL_Rect rect = {};
    SDL_Texture* texture = nullptr;
};

struct ControlComponent {
    control_func control = nullptr;
};

struct Entity {
    // serves as index into array of entities
    u64 eID;
    // bits are flags for components 
    u32 activeComponents;
    // entities contain all components
    PositionComponent position;
    VelocityComponent velocity;
    RenderComponent   render;
    ControlComponent  control;

    bool operator<(const Entity& other);
};
