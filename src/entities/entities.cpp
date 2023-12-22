#include "entities.h"
#include "../misc/settings.h"
#include "../game/systems.h"

#define PLAYER_W 32
#define PLAYER_H 32

#define MOVING_SQUARE_W 16
#define MOVING_SQUARE_H 16
#define SQUARE_SPEED 200

void create_player(Scene* scene) {
    u64 eID = scene->add_entity();

    PositionComponent position;
    RenderComponent   render;
    ControlComponent  control;

    position.x = WIN_W * 0.5;
    position.y = WIN_H * 0.5;
    render.rect.w = PLAYER_W;
    render.rect.h = PLAYER_H;
    control.control_func = control_player;

    scene->set_render_data(eID, render);
    scene->set_position_data(eID, position);
    scene->set_control_func(eID, control);
    scene->activate_components(eID, CMP_ALL);
}

void create_moving_square(Scene* scene) {
    static float theta = 0;
    u64 eID = scene->add_entity();

    PositionComponent position;
    VelocityComponent velocity;
    RenderComponent   render;

    position.x = WIN_W * 0.5;
    position.y = WIN_H * 0.5;
    velocity.xV = SQUARE_SPEED * cos(theta);
    velocity.yV = SQUARE_SPEED * sin(theta);
    render.rect.w = MOVING_SQUARE_W;
    render.rect.h = MOVING_SQUARE_H;

    scene->set_position_data(eID, position);
    scene->set_velocity_data(eID, velocity);
    scene->set_render_data(eID, render);

    scene->activate_components(eID, 
            CMP_POSITION | CMP_VELOCITY | CMP_RENDER);

    theta += 0.01;
}
