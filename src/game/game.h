#pragma once

#include <SDL2/SDL.h>
#include "../input/input.h"
#include "../misc/types.h"
#include "../misc/stats.h"

class Game {
    private:
        bool          m_running;
        InputState    m_input;
        SDL_Window*   m_window;
        SDL_Renderer* m_renderer;
        u32           m_lastTime;
        DevStats      m_stats;

    private:
        void update_render(float timeStep); 
        u32  limit_frame_time();
        void dev_record_frame();

    public:
        bool init();
        void run();
        void quit();
};
