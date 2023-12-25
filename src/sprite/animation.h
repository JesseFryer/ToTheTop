#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "../misc/types.h"

#define MAX_FRAMES     16
#define MAX_ANIMATIONS 8

#define ANI_PLAYER_WALK_R 0
#define ANI_PLAYER_WALK_L 1

struct Animation {
    SDL_Rect m_frames[MAX_FRAMES];
    u8 m_frameCount;

    Animation();
    void set_frames(std::vector<SDL_Rect>& frames);
};

struct Animations {
    Animation m_animations[MAX_ANIMATIONS];
    u16 m_animationCount;

    Animations();
    void add_animation(std::vector<SDL_Rect>& frames);
};
