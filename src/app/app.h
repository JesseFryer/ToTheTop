#pragma once

#include <SDL2/SDL.h>
#include "../input/input.h"
#include "../misc/types.h"
#include "../misc/stats.h"
#include "../scene/scene.h"
#include "../sprite/sprite.h"

class App {
    public:
        bool init();
        void run();
        void quit();

    private:
        bool          m_running;

        SDL_Window*   m_window;
        SDL_Renderer* m_renderer;
        InputState    m_input;
        Scene         m_scene;
        Sprites       m_sprites;

        u32           m_lastTime;
        DevStats      m_stats;

        void update_render(float timeStep); 
        u32  limit_frame_time();
        void dev_record_frame();
        void load_sprites();
};
