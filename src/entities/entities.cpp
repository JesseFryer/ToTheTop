#include "entities.h"
#include "../misc/settings.h"

#define PLAYER_W 32
#define PLAYER_H 32

#define MOVING_SQUARE_W 16
#define MOVING_SQUARE_H 16
#define SQUARE_SPEED 200


void create_player(Scene* scene) {
    u64 eID = scene->get_new_eid();

    RenderComponent render;
    render.eID = eID;
    render.rect.x = 0;
    render.rect.y = 0;
    render.rect.w = PLAYER_W;
    render.rect.h = PLAYER_H;
    scene->add_render_component(render);

    ControlComponent control;
    control.eID = eID;
    scene->add_control_component(control);

    VelocityComponent velocity;
    velocity.eID = eID;
    velocity.x = 0;
    velocity.y = 0;
    scene->add_velocity_component(velocity);

    PositionComponent position;
    position.eID = eID;
    position.x = 0;
    position.y = 0;
    scene->add_position_component(position);
}

void create_moving_square(Scene* scene) {
    static float theta = 0;
    u64 eID = scene->get_new_eid();

    RenderComponent render;
    render.eID = eID;
    render.rect.x = 0;
    render.rect.y = 0;
    render.rect.w = MOVING_SQUARE_W;
    render.rect.h = MOVING_SQUARE_H;
    scene->add_render_component(render);

    VelocityComponent velocity;
    velocity.eID = eID;
    velocity.x = SQUARE_SPEED * cos(theta);
    velocity.y = SQUARE_SPEED * sin(theta);
    scene->add_velocity_component(velocity);

    PositionComponent position;
    position.eID = eID;
    position.x = WIN_W * 0.5;
    position.y = WIN_H * 0.5;
    scene->add_position_component(position);

    theta += 0.01;
}
