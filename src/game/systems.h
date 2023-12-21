#pragma once

#include <SDL2/SDL.h>
#include "../components/components.h"
#include "../input/input.h"

void render_entity(Entity& entity, SDL_Renderer* renderer);
void control_player(Entity& entity, InputState* input);
void move_entity(Entity& entity, float timeStep);
void update_entity_rect_pos(Entity& entity);
