#pragma once

#include <vector>
#include <queue>
#include "../components/components.h"
#include "../input/input.h"

#define MAX_ENTITIES 50000
#define EXCEEDED_ENTITY_LIMIT 12345678

// To compose an entity:
//   - call add_entity which will return the ID of the entity.

// To add functionality to an entity:
//   - call set_*_data for each component you add.
//   - call activate_components (macros can be found in components.h).

struct Scene {
    Entity m_entities[MAX_ENTITIES];
    u64    m_entityCount;

    std::queue<u64> m_reusableEntityIDs;

    Scene();

    u64 add_entity();
    void remove_entity(u64 eID);

    void activate_components(u64 eID, u32 components);
    void set_position_data(u64 eID, PositionComponent& component);
    void set_velocity_data(u64 eID, VelocityComponent& component);
    void set_render_data(u64 eID, RenderComponent& component);
    void set_gravity_data(u64 eID, GravityComponent& component);
    void set_control_func(u64 eID, ControlFunc controlFunc);
    void set_animation_data(u64 eID, AnimationComponent& animation);
};

