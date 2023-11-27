#pragma once

#include <SDL2/SDL.h>
#include "../input/input.h"

class Game {
    private:
        bool         m_running;
        InputState   m_input;
        SDL_Window*  m_window;
        SDL_Surface* m_windowSurface;

    private:
        void update();

    public:
        bool init();
        void run();
};
