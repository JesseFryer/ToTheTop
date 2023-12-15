#include "input.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>

void InputState::init() {
    m_keyState = 0;
    m_mouseState = {};
}

void InputState::update() {
    // reset these every frame
    m_mouseState.xmove = 0;
    m_mouseState.ymove = 0;
    m_mouseState.scroll = 0;

    // pull events and pass them off
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                update_keys(&event);
                break;
            case SDL_KEYUP:
                update_keys(&event);
                break;
            case SDL_MOUSEMOTION:
                update_mouse_motion(&event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                update_mouse_button(&event);
                break;
            case SDL_MOUSEBUTTONUP:
                update_mouse_button(&event);
                break;
            case SDL_QUIT:
                m_keyState |= K_QUIT;
                break;
        }
    }
}

void InputState::update_keys(SDL_Event* keyEvent) {
    SDL_Event event = *keyEvent;
    SDL_Keycode key = event.key.keysym.sym; 
    Uint32 type = event.type;
    switch (key) {
        case SDLK_ESCAPE: 
            if (type == SDL_KEYDOWN) {
                m_keyState |= K_ESC;
            } else {
                m_keyState &= K_ESC_OFF;
            }
            break;
        case SDLK_w: 
            if (type == SDL_KEYDOWN) {
                m_keyState |= K_W;
            } else {
                m_keyState &= K_W_OFF;
            }
            break;
        case SDLK_a: 
            if (type == SDL_KEYDOWN) {
                m_keyState |= K_A;
            } else {
                m_keyState &= K_A_OFF;
            }
            break;
        case SDLK_s: 
            if (type == SDL_KEYDOWN) {
                m_keyState |= K_S;
            } else {
                m_keyState &= K_S_OFF;
            }
            break;
        case SDLK_d: 
            if (type == SDL_KEYDOWN) {
                m_keyState |= K_D;
            } else {
                m_keyState &= K_D_OFF;
            }
            break;
    }
}

void InputState::update_mouse_motion(SDL_Event* mouseMotionEvent) {
    SDL_MouseMotionEvent event = 
        *((SDL_MouseMotionEvent*) mouseMotionEvent);
    m_mouseState.xpos = event.x;
    m_mouseState.xpos = event.y;
    m_mouseState.xmove = event.xrel;
    m_mouseState.ymove = event.yrel;
}

void InputState::update_mouse_button(SDL_Event* mouseButtonEvent) {
    SDL_Event event = *mouseButtonEvent;
    Uint8 button = event.button.button;
    Uint32 type = event.type;
    switch (button) {
        case SDL_BUTTON_LEFT:
            if (type == SDL_MOUSEBUTTONDOWN) {
                m_mouseState.leftClick = true;
            } else {
                m_mouseState.leftClick = false;
            }
            break;
        case SDL_BUTTON_RIGHT:
            if (type == SDL_MOUSEBUTTONDOWN) {
                m_mouseState.rightClick = true;
            } else {
                m_mouseState.rightClick = false;
            }
            break;
    }
}

bool InputState::key_pressed(t_key key) {
    return (bool) (m_keyState & key);
}

bool InputState::left_click() {
    return m_mouseState.leftClick;
}

bool InputState::right_click() {
    return m_mouseState.rightClick;
}

int InputState::get_mouse_x() {
    return m_mouseState.xpos;
}

int InputState::get_mouse_y() {
    return m_mouseState.ypos;
}
