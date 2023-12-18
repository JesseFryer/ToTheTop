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

    TransformComponent transform;
    transform.eID = eID;
    transform.x = 0;
    transform.y = 0;
    transform.xV = 0;
    transform.yV = 0;
    scene->add_transform_component(transform);
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

    TransformComponent transform;
    transform.eID = eID;
    transform.x = WIN_W * 0.5; 
    transform.y = WIN_H * 0.5;
    transform.xV = SQUARE_SPEED * cos(theta);
    transform.yV = SQUARE_SPEED * sin(theta);
    scene->add_transform_component(transform);

    theta += 0.01;
}
