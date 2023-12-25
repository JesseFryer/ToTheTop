#include <iostream>
#include <cstring>
#include <SDL2/SDL.h>

#include "app.h"
#include "../misc/settings.h"
#include "../entities/entities.h"
#include "../game/systems.h"

bool App::init() {
    query_stack();

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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

    SDL_SetWindowResizable(m_window, SDL_TRUE);

    m_renderer = SDL_CreateRenderer(
            m_window,
            0,
            SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cout << "Failed to create renderer\n";
        return false;
    }

    memset(&m_stats, 0, sizeof(DevStats));
    load_sprites();
    create_animations();
    create_entities();

    m_lastTime = SDL_GetTicks();
    m_running = true;
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

    for (u64 eID = 0; eID < MAX_ENTITIES; eID++) {
        Entity& entity = m_scene.m_entities[eID];
        u32 activeComps = entity.activeComponents;

        if (!activeComps) {
            continue;
        }

        if (is_active(activeComps, SYS_CONTROL)) {
            entity.control.control_func(entity, &m_input, timeStep);
        }

        if (is_active(activeComps, SYS_GRAVITY)) {
            apply_gravity(entity, timeStep);
        }

        if (is_active(activeComps, SYS_MOVE)) {
            entity.velocity.move_func(entity, timeStep);

            if (is_active(activeComps, CMP_RENDER)) {
                update_entity_rect_pos(entity);
            }

        }

        if (is_active(activeComps, SYS_ANIMATE)) {
            entity.animation.update_animation_func(entity);
            animate_entity(&m_animations, entity, timeStep);
        }

        if (is_active(activeComps, CMP_RENDER)) {
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

void App::load_sprites() {
    m_sprites.add_sprite("../../res/player.png", m_renderer);
    m_sprites.add_sprite("../../res/slime.png", m_renderer);
    m_sprites.add_sprite("../../res/dirt.png", m_renderer);
    m_sprites.add_sprite("../../res/grass.png", m_renderer);

}

void App::create_entities() {
    for (int i = 0; i < 1000; i++) {
        create_moving_square(m_sprites.get_sprite(SPR_SLIME), &m_scene);
    }
    create_player1(m_sprites.get_sprite(SPR_PLAYER), 
            &m_scene,
            ANI_PLAYER_WALK_L);
}

void App::query_stack() {
    struct rlimit limit;
    getrlimit (RLIMIT_STACK, &limit);
    std::cout << "current stack limit: " << limit.rlim_cur
        << " bytes\nmax stack limit: " << limit.rlim_max 
        << " bytes\n";

    size_t stackUsage = MAX_ENTITIES * sizeof(Entity);
    std::cout << "size of " << MAX_ENTITIES << " entities: "
        << stackUsage << " bytes\n";

    std::cout << "percentage of stack used for entities: "
        << 100.0f * ( ((float) stackUsage) / ((float) limit.rlim_cur) )
        << "%\n";
}

void App::create_animations() {
    // change these for each animation
    int frameW;
    int frameH;
    int numFrames;

    // player walk right 
    // 24x32 pixels each frame 
    // 8 frames
    frameW = 24;
    frameH = 32;
    numFrames = 8;
    std::vector<SDL_Rect> frames;
    SDL_Rect tmp;
    tmp.w = frameW;
    tmp.h = frameH;
    tmp.y = 3 * frameH;
    for (int x = 0; x < frameW * numFrames; x+= frameW) {
        tmp.x = x;
        frames.push_back(tmp);
    }
    m_animations.add_animation(frames);

    // player walk left
    // 24x32 pixels each frame 
    // 8 frames
    frames.clear();
    tmp.y = 2 * frameH;
    for (int x = 0; x < frameW * numFrames; x+= frameW) {
        tmp.x = x;
        frames.push_back(tmp);
    }
    m_animations.add_animation(frames);
}
