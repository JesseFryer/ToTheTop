#include "systems.h"
#include "../misc/settings.h"

void render_entity(Entity& entity, SDL_Renderer* renderer) {
    if (entity.render.texture) {
        SDL_RenderCopy(
                renderer, 
                entity.render.texture, 
                NULL, 
                &entity.render.rect);
    } else {
        SDL_RenderFillRect(renderer, &entity.render.rect);
    }
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

void control_player(Entity& self, InputState* input) { 
    self.velocity.xV = 0.0f;
    self.velocity.yV = 0.0f;
    if (input->key_pressed(K_W)) {
        self.velocity.yV = -PLAYER_SPEED;
    }
    if (input->key_pressed(K_A)) {
        self.velocity.xV = -PLAYER_SPEED;
    }
    if (input->key_pressed(K_S)) {
        self.velocity.yV = PLAYER_SPEED;
    }
    if (input->key_pressed(K_D)) {
        self.velocity.xV = PLAYER_SPEED;
    }

}

void update_entity_rect_pos(Entity& entity) {
    entity.render.rect.x = entity.position.x;
    entity.render.rect.y = entity.position.y;
}
