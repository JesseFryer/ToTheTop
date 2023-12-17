#pragma once

#include <vector>
#include <map>
#include "components.h"
#include "../input/input.h"

class Scene {
    public:
        void set_renderer(SDL_Renderer* renderer);
        void set_input(InputState* input);
        void update(float timeStep);

        // add components
        void add_render_component(RenderComponent component);
        void add_control_component(ControlComponent component);
        void add_velocity_component(VelocityComponent component);
        void add_position_component(PositionComponent component);

        u64 get_new_eid();

    private:
        // house-keeping
        SDL_Renderer* m_renderer;
        InputState* m_input;
        u64 m_entityCount;
        std::vector<u64> m_reusableEntityIDs;

        // quick lookups
        std::map<u64, u32> m_activeComponents;
        bool has_components(u64 eID, u32 componentsMask);
        void add_components(u64 eID, u32 componentsMask);

        // component buckets
        std::vector<RenderComponent> m_renderComponents;
        std::vector<ControlComponent> m_controlComponents;
        std::vector<VelocityComponent> m_velocityComponents;
        std::vector<PositionComponent> m_positionComponents;

        // retrieve components (eID must be known to have the component)
        // use has_components to find this out before calling these
        size_t get_render_component(u64 eID);
        size_t get_control_component(u64 eID);
        size_t get_velocity_component(u64 eID);
        size_t get_position_component(u64 eID);

        // systems
        void system_render();
        void system_move(float timeStep);
        void system_control();
};

