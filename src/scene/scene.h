#pragma once

#include <vector>
#include <queue>
#include "../components/components.h"
#include "../input/input.h"

// To compose an entity:
//   - call add_entity which will return the ID of the entity.

// To add functionality to an entity:
//   - call set_*_data for each component you add.
//   - call activate_components (macros can be found in components.h).

struct Scene {
    //TODO: possibly make this a static sized array
    std::vector<Entity> m_entities;
    std::queue<u64>     m_reusableEntityIDs;

    u64 add_entity();
    void remove_entity(u64 eID);

    void activate_components(u64 eID, u32 components);
    void set_position_data(u64 eID, PositionComponent& component);
    void set_velocity_data(u64 eID, VelocityComponent& component);
    void set_render_data(u64 eID, RenderComponent& component);
    void set_gravity_data(u64 eID, GravityComponent& component);
    void set_control_func(u64 eID, ControlFunc controlFunc);
};

