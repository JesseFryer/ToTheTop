#pragma once

/*
   So basically all entities are stored in one massive array.
   Each entity has all components in them, with as many active 
   as per entity type. to deactivate an entity we just zero out
   it's active components we can then reuse that spot in the 
   array when we make a new entity. Very large space complexity
   but it should be vroom vroom cuz of cache shizzle everything
   is static offsets.
*/

#include <SDL2/SDL.h>
#include <vector>
#include "../misc/types.h"
#include "../input/input.h"

#define MAX_ENTITIES 10000

// componet flags
#define CMP_POSITION 0x00000001
#define CMP_RECT     0x00000002
#define CMP_VELOCITY 0x00000004
#define CMP_CONTROL  0x00000008 

// system flags (combinations of components)
#define MOVEABLE   (CMP_VELOCITY | CMP_POSITION)
#define RENDERABLE (CMP_POSITION | CMP_RECT)
#define CONTROLLABLE (CMP_CONTROL | CMP_VELOCITY)

//============= Components ===============//

typedef struct PositionComponent {
    float x = 128;
    float y = 128;
} PositionComponent;

typedef struct RectComponent {
    SDL_Rect rect = { 0, 0, 16, 16 }; // TODO remove test 
} RectComponent;

typedef struct VelocityComponent {
    float x = 0;
    float y = 0;
} VelocityComponent;

typedef struct ControlComponent {
} ControlComponent;

//========================================//

typedef struct Entity {
    u32 activeComponents;
    PositionComponent cmp_position;
    RectComponent     cmp_rect;
    VelocityComponent cmp_velocity;
} EntityComponents;

class ECS {
    private:
        Entity* m_entities;
        u32 m_entityCount;
        std::vector<u32>  m_deadEntites;
        SDL_Renderer* m_renderer;
        InputState* m_input;

    private:
        // systems (sort of)
        void render_entity(Entity* entity);
        void move_entity(Entity* entity, float timeStep);
        void control_entity(Entity* entity);

    public:
        void update(float timeStep);
        
        void init(SDL_Renderer* renderer, InputState* input); 
        u32 get_entity_count() { return m_entityCount; }

        u32  add_entity();
        u32  add_entity(u32 components);

        void remove_entity(u32 eID);
        void entity_add_components(u32 eID, u32 components);

        void entity_set_position(u32 eID, float x, float y);
        void entity_set_velocity(u32 eID, float xV, float yV);
};
