#include <iostream>
#include <cstring>
#include <SDL2/SDL.h>

#include "app.h"
#include "../misc/settings.h"
#include "../entities/entities.h"
#include "../game/systems.h"

bool App::init() {
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

    memset(&m_stats, 0, sizeof(DevStats));
    m_lastTime = SDL_GetTicks();
    m_running = true;

    // test out ecs
    create_player(&m_scene);
    for (int i = 0; i < 20000; i++) {
        create_moving_square(&m_scene);
    }

    return true;
}

void App::run() {
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

void App::update_render(float timeStep) {

    SDL_SetRenderDrawColor(m_renderer,
            255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    for (u64 eID = 0; eID < m_scene.m_entities.size(); eID++) {

        Entity& entity = m_scene.m_entities.at(eID);
        u32 activeComponents = entity.activeComponents;

        if ((activeComponents & SYS_CONTROL) == SYS_CONTROL) {
            // causes seg fault not sure why
            //entity.control.control(entity, &m_input);
        }

        if ((activeComponents & SYS_MOVE) == SYS_MOVE) {
            move_entity(entity, timeStep);
            if (activeComponents & CMP_RENDER) {
                update_entity_rect_pos(entity);
            }
        }

        if (activeComponents & CMP_RENDER) {
            render_entity(entity, m_renderer);
        }
    }
    SDL_RenderPresent(m_renderer);
}

u32 App::limit_frame_time() {
    u32 currentTime = SDL_GetTicks(); // time in milliseconds
    u32 deltaTime = currentTime - m_lastTime;
    if (deltaTime < FRAME_TIME) {
        u32 diff = FRAME_TIME - deltaTime;
        SDL_Delay(diff);
        deltaTime += diff;
    } else if (deltaTime > MAX_FRAME_TIME) {
        // cap deltaTime to avoid physics glitches (slows simulation)
        deltaTime = MAX_FRAME_TIME;
    }
    m_lastTime = SDL_GetTicks();
    return deltaTime;
}

void App::dev_record_frame() {
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

void App::quit() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
