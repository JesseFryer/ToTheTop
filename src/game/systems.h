#pragma once

#include <SDL2/SDL.h>
#include "../components/components.h"
#include "../input/input.h"

void render_entity(Entity& entity, SDL_Renderer* renderer);
void control_player1(Entity& entity, InputState* input, float timeStep);
void control_player2(Entity& entity, InputState* input, float timeStep);
void move_square(Entity& self, float timeStep);
void move_player(Entity& self, float timeStep);
void update_entity_rect_pos(Entity& entity);
void apply_gravity(Entity& entity, float timeStep);
void animate_entity(Animations* animations, Entity& entity, float timeStep);
void update_player_animation(Entity& self);
