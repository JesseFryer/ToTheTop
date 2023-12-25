#pragma once

#include "../scene/scene.h"

void create_player1(SDL_Texture* tex, Scene* scene, u16 animation);
void create_player2(SDL_Texture* tex, Scene* scene);
void create_moving_square(SDL_Texture* tex, Scene* scene);
void create_tile(SDL_Texture* tex, Scene* scene, float x, float y);
