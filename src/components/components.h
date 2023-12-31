#pragma once

#include <SDL2/SDL.h>
#include "../misc/types.h"
#include "../input/input.h"
#include "../sprite/animation.h"

// bit-masks for m_activeComponent queries
#define CMP_ALL      0xffffffff
#define CMP_POSITION 0x00000001
#define CMP_VELOCITY 0x00000002
#define CMP_RENDER   0x00000004
#define CMP_CONTROL  0x00000008
#define CMP_GRAVITY  0x00000010
#define CMP_ANIMATE  0x00000020

// for systems that require multiple components
#define SYS_CONTROL (CMP_CONTROL | CMP_VELOCITY)
#define SYS_MOVE    (CMP_POSITION | CMP_VELOCITY)
#define SYS_GRAVITY (CMP_VELOCITY | CMP_GRAVITY)
#define SYS_ANIMATE (CMP_RENDER | CMP_ANIMATE)

// check if an entity has checkComps components active 
// activeComps is the entity's active components
// checkComps is the components to check
bool is_active(u32 activeComps, u32 checkComps);

struct Entity;


struct PositionComponent {
    float x;
    float y;

    PositionComponent();
};

typedef void (*MoveFunc)(Entity& self, float timeStep);
struct VelocityComponent {
    float xV;
    float yV;
    MoveFunc move_func;

    VelocityComponent();
};

struct GravityComponent {
    float strength;

    GravityComponent();
};

struct RenderComponent {
    SDL_Rect rect;
    SDL_Rect textureRect; // portion of the texture
    SDL_Texture* texture; // the texture (spritesheet)

    RenderComponent();
};

typedef void (*UpdateAnimationFunc)(Entity& self);
struct AnimationComponent {
    u8 animation; // macros in animation.h
    float speed; // gets added to accumulator each frame
    float accumulator;
    u8    index;
    UpdateAnimationFunc update_animation_func;

    AnimationComponent();
};

typedef void (*ControlFunc)(Entity& self, InputState* input, float timeStep);
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
    PositionComponent  position;
    VelocityComponent  velocity;
    RenderComponent    render;
    ControlComponent   control;
    GravityComponent   gravity;
    AnimationComponent animation;

    Entity();
    bool operator<(const Entity& other);
};
