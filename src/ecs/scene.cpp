#include "scene.h"
#include "../misc/settings.h"
#include <iostream>

void Scene::init(SDL_Renderer* renderer, InputState* input) {
    m_renderer = renderer;
    m_input = input;
}

void Scene::update_render(float timeStep) {
    SDL_SetRenderDrawColor(m_renderer,
            255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer,
            0, 0, 0, 255);
    for (u64 eID = 0; eID < m_entities.size(); eID++) {
        Entity& entity = m_entities.at(eID);
        u32 activeComponents = entity.activeComponents;

        if ((activeComponents & SYS_CONTROL) == SYS_CONTROL) {
            control_entity(entity);
        }

        if ((activeComponents & SYS_MOVE) == SYS_MOVE) {
            move_entity(entity, timeStep);
            if (activeComponents & CMP_RENDER) {
                update_entity_rect_pos(entity);
            }
        }

        if (activeComponents & CMP_RENDER) {
            render_entity(entity);
        }
    }
    SDL_RenderPresent(m_renderer);
}

u64 Scene::add_entity() {
    u64 eID;
    if (m_reusableEntityIDs.size()) {
        eID = m_reusableEntityIDs.front();
        m_reusableEntityIDs.pop();
    } else {
        eID = m_entities.size();
    }
    Entity entity;
    memset(&entity, 0, sizeof(Entity));
    entity.eID = eID;
    m_entities.push_back(entity);
    return eID;
}

void Scene::remove_entity(u64 eID) {
    memset(&(m_entities.data()[eID]), 0, sizeof(Entity));
    m_reusableEntityIDs.push(eID);
}


//////////////////////// set components ///////////////////////////

void Scene::activate_components(u64 eID, u32 componentsMask) {
    m_entities.at(eID).activeComponents |= componentsMask;
}

void Scene::set_position_data(u64 eID, PositionComponent& component) {
    m_entities.at(eID).position = component;
}

void Scene::set_velocity_data(u64 eID, VelocityComponent& component) {
    m_entities.at(eID).velocity = component;
}

void Scene::set_render_data(u64 eID, RenderComponent& component) {
    m_entities.at(eID).render = component;
}

void Scene::set_control_data(u64 eID, ControlComponent& component) {
    m_entities.at(eID).control = component;
}

////////////////////////// systems ////////////////////////////////

void Scene::render_entity(Entity& entity) {
    SDL_RenderFillRect(m_renderer, &entity.render.rect);
}

void Scene::move_entity(Entity& entity, float timeStep) {
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

void Scene::control_entity(Entity& entity) {
    const float speed = 400;
    entity.velocity.xV = 0;
    entity.velocity.yV = 0;
    if (m_input->key_pressed(K_W)) {
        entity.velocity.yV = -speed;
    }
    if (m_input->key_pressed(K_A)) {
        entity.velocity.xV = -speed;
    }
    if (m_input->key_pressed(K_S)) {
        entity.velocity.yV = speed;
    }
    if (m_input->key_pressed(K_D)) {
        entity.velocity.xV = speed;
    }
}

void Scene::update_entity_rect_pos(Entity& entity) {
    entity.render.rect.x = entity.position.x;
    entity.render.rect.y = entity.position.y;
}
