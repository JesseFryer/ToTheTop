#pragma once

#include <SDL2/SDL.h>
#include "../misc/types.h"

#define MAX_TEXTURES 50

// sprite index's for get_sprite
#define SPR_PLAYER 0 
#define SPR_SLIME  1

struct Sprites {
    SDL_Texture* m_sprites[MAX_TEXTURES];
    u8 m_spriteCount;

    Sprites();
    void add_sprite(const char* path, SDL_Renderer* renderer);
    SDL_Texture* get_sprite(u8 spriteIndex);
};
