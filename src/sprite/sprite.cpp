#include "sprite.h"
#include <SDL2/SDL_image.h>

Sprites::Sprites() {
    memset(m_sprites, 0, sizeof(SDL_Texture*) * MAX_TEXTURES);
    m_spriteCount = 0;
}

void Sprites::add_sprite(const char* path, SDL_Renderer* renderer) {
    SDL_Texture* tex;
    SDL_Surface* tmp = IMG_Load(path);
    tex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    m_sprites[m_spriteCount++] = tex;
}

SDL_Texture* Sprites::get_sprite(u8 spriteIndex) {
    if (spriteIndex >= m_spriteCount || !m_spriteCount) {
        return nullptr;
    }
    return m_sprites[spriteIndex];
}
