#include "entities.h"
#include "../misc/settings.h"

#define PLAYER_W 32
#define PLAYER_H 32

#define MOVING_SQUARE_W 16
#define MOVING_SQUARE_H 16
#define SQUARE_SPEED 200


void create_player(Scene* scene) {
    u64 eID = scene->get_new_eid();

    ControlComponent control;
    control.eID = eID;
    scene->add_control_component(control);

    TransformComponent transform;
    transform.eID = eID;
    transform.x = 0;
    transform.y = 0;
    transform.xV = 0;
    transform.yV = 0;
    transform.rect.w = PLAYER_W;
    transform.rect.h = PLAYER_H;
    scene->add_transform_component(transform);
}

void create_moving_square(Scene* scene) {
    static float theta = 0;
    u64 eID = scene->get_new_eid();

    TransformComponent transform;
    transform.eID = eID;
    transform.x = WIN_W * 0.5; 
    transform.y = WIN_H * 0.5;
    transform.xV = SQUARE_SPEED * cos(theta);
    transform.yV = SQUARE_SPEED * sin(theta);
    transform.rect.w = MOVING_SQUARE_W;
    transform.rect.h = MOVING_SQUARE_H;
    scene->add_transform_component(transform);

    theta += 0.01;
}
