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
    if (entity.position.y >= WIN_H - 64) {
        entity.position.y = WIN_H - 64;
    }
}

void apply_gravity(Entity& entity, float timeStep) {
    entity.velocity.yV += GRAVITY * entity.gravity.strength * timeStep;
}

void control_player1(Entity& self, InputState* input, float timeStep) { 
    self.velocity.xV = 0.0f;

    static float jumpAccumulator = JUMP_TIMER;
    jumpAccumulator -= timeStep;
    if (jumpAccumulator <= 0.0f) {
        jumpAccumulator = 0.0f;
    }

    if (input->key_pressed(K_W) && !jumpAccumulator) {
        jumpAccumulator = JUMP_TIMER;
        self.velocity.yV = -PLAYER_JUMP_STR;
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

void control_player2(Entity& self, InputState* input, float timeStep) { 
    self.velocity.xV = 0.0f;

    static float jumpAccumulator = JUMP_TIMER;
    jumpAccumulator -= timeStep;
    if (jumpAccumulator <= 0.0f) {
        jumpAccumulator = 0.0f;
    }

    if (input->key_pressed(K_UP) && !jumpAccumulator) {
        jumpAccumulator = JUMP_TIMER;
        self.velocity.yV = -PLAYER_JUMP_STR;
    }
    if (input->key_pressed(K_LEFT)) {
        self.velocity.xV = -PLAYER_SPEED;
    }
    if (input->key_pressed(K_DOWN)) {
        self.velocity.yV = PLAYER_SPEED;
    }
    if (input->key_pressed(K_RIGHT)) {
        self.velocity.xV = PLAYER_SPEED;
    }
}

void update_entity_rect_pos(Entity& entity) {
    entity.render.rect.x = entity.position.x;
    entity.render.rect.y = entity.position.y;
}
