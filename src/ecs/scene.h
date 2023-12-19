#pragma once

#include <vector>
#include <queue>
#include "components.h"
#include "../input/input.h"

class Scene {
    public:
        void init(SDL_Renderer* renderer, InputState* input);
        void update_render(float timeStep);

        u64 add_entity();
        void activate_components(u64 eID, u32 components);
        void remove_entity(u64 eID);

        void set_position_data(u64 eID, PositionComponent& component);
        void set_velocity_data(u64 eID, VelocityComponent& component);
        void set_render_data(u64 eID, RenderComponent& component);
        void set_control_data(u64 eID, ControlComponent& component);

    private:
        SDL_Renderer* m_renderer;
        InputState*   m_input;
        std::vector<Entity> m_entities;
        std::queue<u64>     m_reusableEntityIDs;

        // systems
        void render_entity(Entity& entity);
        void control_entity(Entity& entity);
        void move_entity(Entity& entity, float timeStep);
        void update_entity_rect_pos(Entity& entity);
};

