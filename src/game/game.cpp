#include "game.h"
#include <iostream>

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }

    m_window = SDL_CreateWindow(
            "SDL2 Window",
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED,
            1280, 720,
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
    m_running = true;

    return true;
}

void Game::run() {
    while (m_running) {
        update();
    }
}

void Game::update() {
    m_input.update();
    if (m_input.key_pressed(K_QUIT)) {
        m_running = false;
    }
}
