#include <iostream>
#include <cstring>

#include "game.h"
#include "../misc/settings.h"

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }

    m_window = SDL_CreateWindow(
            "To The Top",
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            WIN_W, WIN_H,
            0);
    if (!m_window) {
        std::cout << "Failed to create window\n";
        return false;
    }

    m_renderer = SDL_CreateRenderer(
            m_window,
            0,
            SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cout << "Failed to create renderer\n";
        return false;
    }

    m_input.init();
    m_scene.set_renderer(m_renderer);
    m_scene.set_input(&m_input);
    memset(&m_stats, 0, sizeof(DevStats));
    m_lastTime = SDL_GetTicks();
    m_running = true;

    // test out ecs
    m_scene.add_render_component({0, 0, 0, 32, 32});
    m_scene.add_velocity_component({0, 50, 50});
    m_scene.add_position_component({0, 0, 0});
    m_scene.add_control_component({0});

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
    m_scene.update(timeStep);
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

void Game::quit() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
