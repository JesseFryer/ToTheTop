#include <iostream>

#include "game.h"
#include "../misc/settings.h"

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }

    m_window = SDL_CreateWindow(
            "SDL2 Window",
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            WIN_W, WIN_H,
            0);

    if (!m_window) {
        std::cout << "Failed to create window\n";
        return false;
    }

    SDL_Surface* m_windowSurface = SDL_GetWindowSurface(m_window);
    if (!m_windowSurface) {
        std::cout << "Failed to get the surface from the window\n";
        return false;
    }

    SDL_UpdateWindowSurface(m_window);

    m_input.init();
    m_stats = {};
    m_lastTime = SDL_GetTicks();
    m_running = true;

    return true;
}

void Game::run() {
    while (m_running) {
        m_input.update();
        if (m_input.key_pressed(K_QUIT)) {
            m_running = false;
        }

        u32 deltaTime = limit_frame_time();
        float timeStep = deltaTime * 0.001; 
        update_render(timeStep);

#if DEV_STATS
        dev_record_frame();
#endif
    }
}

void Game::update_render(float timeStep) {
    SDL_Delay(6); // for now simulate it takes a bit
}

u32 Game::limit_frame_time() {
    // wait if we were faster than the required frame time 
    // and add the difference to our deltaTime
    u32 currentTime = SDL_GetTicks(); // time in milliseconds
    u32 deltaTime = currentTime - m_lastTime;
    if (deltaTime < FRAME_TIME) {
        u32 diff = FRAME_TIME - deltaTime;
        SDL_Delay(diff);
        deltaTime += diff;
    } else if (deltaTime > MAX_FRAME_TIME) {
        // cap deltaTime to avoid physics glitches
        // simulation will slow down as a result
        deltaTime = MAX_FRAME_TIME;
    }
    m_lastTime = SDL_GetTicks();
    return deltaTime;
}

void Game::dev_record_frame() {
    u32 currentTime = SDL_GetTicks();
    u32 frameTime = currentTime - m_stats.lastTime;
    m_stats.lastTime = currentTime;
    m_stats.frames++;
    m_stats.timeAccumulator += frameTime;
    if (m_stats.timeAccumulator >= 1000) {
        std::cout << "FPS: " << m_stats.frames << '\n';
        m_stats.frames = 0;
        m_stats.timeAccumulator = 0;
    }
}
