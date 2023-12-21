#include "systems.h"
#include "../misc/settings.h"

void render_entity(Entity& entity, SDL_Renderer* renderer) {
    SDL_RenderFillRect(renderer, &entity.render.rect);
}

void move_entity(Entity& entity, float timeStep) {
    entity.position.x += timeStep * entity.velocity.xV;
    entity.position.y += timeStep * entity.velocity.yV;
    if (entity.position.x > WIN_W) {
        entity.position.x = WIN_W;
        entity.velocity.xV *= -1;
    } else if (entity.position.x < 0) {
        entity.position.x = 0;
        entity.velocity.xV *= -1;
    }
    if (entity.position.y > WIN_H) {
        entity.position.y = WIN_H;
        entity.velocity.yV *= -1;
    } else if (entity.position.y < 0) {
        entity.position.y = 0;
        entity.velocity.yV *= -1;
    }

}

void control_player(Entity& entity, InputState* input) {
}

void update_entity_rect_pos(Entity& entity) {
    entity.render.rect.x = entity.position.x;
    entity.render.rect.y = entity.position.y;
}
