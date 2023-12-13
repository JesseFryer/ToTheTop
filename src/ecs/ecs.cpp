#include "ecs.h"
#include "../misc/settings.h"
#include <iostream>

void ECS::init(SDL_Renderer* renderer, InputState* input) {
    m_renderer = renderer;
    m_input = input;
    m_entities = new Entity[MAX_ENTITIES];
    m_entityCount = 0;
}

u32 ECS::add_entity() {
    // reuse dead entity slots
    u32 eID;
    if (!m_deadEntites.empty()) {
        eID = m_deadEntites.back();
        m_deadEntites.pop_back();
    } else {
        eID = m_entityCount++;
    }
    m_entities[eID] = {};
    return eID;
}

u32 ECS::add_entity(u32 components) {
    // reuse dead entity slots
    u32 eID;
    if (!m_deadEntites.empty()) {
        eID = m_deadEntites.back();
        m_deadEntites.pop_back();
    } else {
        eID = m_entityCount++;
    }
    // m_entities[eID] = {};
    m_entities[eID].activeComponents = components;
    return eID;
}

void ECS::remove_entity(u32 eID) {
    m_entities[eID].activeComponents = 0;
    m_deadEntites.push_back(eID);
    m_entityCount--;
}

void ECS::entity_add_components(u32 eID, u32 components) {
    m_entities[eID].activeComponents |= components;
}

void ECS::entity_set_position(u32 entity, float x, float y) {
    m_entities[entity].cmp_position.x = x;
    m_entities[entity].cmp_position.y = y;
}

void ECS::entity_set_velocity(u32 entity, float xV, float yV) {
    m_entities[entity].cmp_velocity.x = xV;
    m_entities[entity].cmp_velocity.y = yV;
}

void ECS::update(float timeStep) {
    // testing rendering coloured quads
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);

    for (u32 i = 0; i < m_entityCount; i++) {
        if ((m_entities[i].activeComponents & CONTROLLABLE)
                == CONTROLLABLE) {
            control_entity(&m_entities[i]);
        }

        if ((m_entities[i].activeComponents & MOVEABLE)
                == MOVEABLE) {
            move_entity(&m_entities[i], timeStep);
        }

        if ((m_entities[i].activeComponents & RENDERABLE)
                == RENDERABLE) {
            render_entity(&m_entities[i]);
        }
    }
}

void ECS::render_entity(Entity* entity) {
    entity->cmp_rect.rect.x = entity->cmp_position.x;
    entity->cmp_rect.rect.y = entity->cmp_position.y;
    SDL_RenderFillRect(m_renderer, &(entity->cmp_rect.rect));
}

void ECS::move_entity(Entity* entity, float timeStep) {
    float x = entity->cmp_position.x;
    float y = entity->cmp_position.y;
    float xV = entity->cmp_velocity.x;
    float yV = entity->cmp_velocity.y;

    x += xV * timeStep;
    if (x < 0) {
        x = 0;
        xV *= -1;
    } else if (x > WIN_W) {
        x = WIN_W;
        xV *= -1;
    }

    y += yV * timeStep;
    if (y < 0) {
        y = 0;
        yV *= -1;
    } else if (y > WIN_H) {
        y = WIN_H;
        yV *= -1;
    }

    entity->cmp_position.x = x;
    entity->cmp_position.y = y;
    entity->cmp_velocity.x = xV;
    entity->cmp_velocity.y = yV;
}

void ECS::control_entity(Entity* entity) {
    entity->cmp_velocity.x = 0;
    entity->cmp_velocity.y = 0;
    if (m_input->key_pressed(K_W)) {
        entity->cmp_velocity.y = -PLAYER_SPEED;
    }
    if (m_input->key_pressed(K_A)) {
        entity->cmp_velocity.x = -PLAYER_SPEED;
    }
    if (m_input->key_pressed(K_S)) {
        entity->cmp_velocity.y = PLAYER_SPEED;
    }
    if (m_input->key_pressed(K_D)) {
        entity->cmp_velocity.x = PLAYER_SPEED;
    }
}
