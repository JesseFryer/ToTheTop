#pragma once

#include <vector>
#include "components.h"
#include "../input/input.h"

class Scene {
    public:
        void set_renderer(SDL_Renderer* renderer);
        void set_input(InputState* input);
        void update(float timeStep);

        // add components
        void add_render_component(RenderComponent component);

    private:
        // house-keeping
        SDL_Renderer* m_renderer;
        InputState* m_input;
        std::vector<u64> m_reusableEntityIDs;

        // component buckets and query functions
        std::vector<RenderComponent> m_renderComponents;
        bool has_render_component(u64 eID);

        // systems
        void system_render();
};

