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

typedef void (*ControlFunc)(Entity&, InputState*);

struct PositionComponent {
    float x;
    float y;

    PositionComponent();
};

struct VelocityComponent {
    float xV;
    float yV;

    VelocityComponent();
};

struct RenderComponent {
    SDL_Rect rect;
    SDL_Texture* texture;

    RenderComponent();
};

struct ControlComponent {
    ControlFunc control_func;

    ControlComponent();
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

    Entity();
    bool operator<(const Entity& other);
};
