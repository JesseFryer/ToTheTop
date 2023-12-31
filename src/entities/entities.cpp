#include "entities.h"
#include "../misc/settings.h"
#include "../game/systems.h"
#include <SDL2/SDL_image.h>

void create_player1(SDL_Texture* tex, Scene* scene, u16 initAnimation) {
    u64 eID = scene->add_entity();

    PositionComponent  position;
    RenderComponent    render;
    ControlComponent   control;
    GravityComponent   gravity;
    VelocityComponent  velocity;
    AnimationComponent animation;

    position.x = WIN_W * 0.5;
    position.y = WIN_H * 0.5;
    velocity.move_func = move_player;
    velocity.move_func = move_player;
    render.rect.w = PLAYER_W;
    render.rect.h = PLAYER_H;
    render.texture = tex;
    render.textureRect.x = 0;
    render.textureRect.y = 0;
    render.textureRect.w = 24;
    render.textureRect.h = 32;
    gravity.strength = PLAYER_GRAV_STR;
    animation.animation = initAnimation;
    animation.speed = 8;
    animation.update_animation_func = update_player_animation;

    scene->set_render_data(eID, render);
    scene->set_position_data(eID, position);
    scene->set_velocity_data(eID, velocity);
    scene->set_gravity_data(eID, gravity);
    scene->set_control_func(eID, control_player1);
    scene->set_animation_data(eID, animation);
    scene->activate_components(eID, CMP_ALL);
}

void create_player2(SDL_Texture* tex, Scene* scene) {
    u64 eID = scene->add_entity();

    PositionComponent position;
    RenderComponent   render;
    ControlComponent  control;
    GravityComponent  gravity;
    VelocityComponent velocity;

    position.x = WIN_W * 0.5;
    position.y = WIN_H * 0.5;
    velocity.move_func = move_player;
    render.rect.w = PLAYER_W;
    render.rect.h = PLAYER_H;
    render.texture = tex;
    gravity.strength = PLAYER_GRAV_STR;

    scene->set_velocity_data(eID, velocity);
    scene->set_render_data(eID, render);
    scene->set_position_data(eID, position);
    scene->set_gravity_data(eID, gravity);
    scene->set_control_func(eID, control_player2);
    scene->activate_components(eID, CMP_ALL);
}

void create_moving_square(SDL_Texture* tex, Scene* scene) {
    static float theta = 0;
    u64 eID = scene->add_entity();

    PositionComponent position;
    VelocityComponent velocity;
    RenderComponent   render;

    position.x = WIN_W * 0.5;
    position.y = WIN_H * 0.5;
    velocity.xV = SQUARE_SPEED * cos(theta);
    velocity.yV = SQUARE_SPEED * sin(theta);
    velocity.move_func = move_square;
    render.rect.w = MOVING_SQUARE_W;
    render.rect.h = MOVING_SQUARE_H;
    render.texture = tex;
    render.textureRect.x = 0;
    render.textureRect.y = 0;
    render.textureRect.w = 454;
    render.textureRect.h = 316;

    scene->set_position_data(eID, position);
    scene->set_velocity_data(eID, velocity);
    scene->set_velocity_data(eID, velocity);
    scene->set_render_data(eID, render);

    scene->activate_components(eID, 
            CMP_POSITION | CMP_VELOCITY | CMP_RENDER);

    theta += 0.01;
}

void create_tile(SDL_Texture* tex, Scene* scene, float x, float y) {
    u64 eID = scene->add_entity();
    PositionComponent position;
    RenderComponent   render;
    position.x = x;
    position.y = y;
    render.texture = tex;
    render.rect.x = x;
    render.rect.y = y;
    render.rect.w = TILE_W;
    render.rect.h = TILE_H;

    scene->set_position_data(eID, position);
    scene->set_render_data(eID, render);
    scene->activate_components(eID, CMP_POSITION | CMP_RENDER);
}
