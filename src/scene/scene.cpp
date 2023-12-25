#include "scene.h"
#include "../misc/settings.h"
#include <iostream>

Scene::Scene() {
    memset(&m_entities, 0, MAX_ENTITIES * sizeof(Entity));
    m_entityCount = 0;
}

u64 Scene::add_entity() {
    u64 eID;
    if (m_reusableEntityIDs.size()) {
        eID = m_reusableEntityIDs.front();
        m_reusableEntityIDs.pop();
    } else {
        if (m_entityCount == MAX_ENTITIES) {
            return EXCEEDED_ENTITY_LIMIT;
        }
        eID = m_entityCount;
    }
    m_entities[eID].eID = eID; //TODO: might not need this
    m_entityCount++;
    return eID;
}

void Scene::remove_entity(u64 eID) {
    if (m_entities[eID].activeComponents) {
        memset(&m_entities[eID], 0, sizeof(Entity));
        m_reusableEntityIDs.push(eID);
        m_entityCount--;
    }
}

//////////////////////// set components ///////////////////////////

void Scene::activate_components(u64 eID, u32 componentsMask) {
    m_entities[eID].activeComponents |= componentsMask;
}

void Scene::set_position_data(u64 eID, PositionComponent& component) {
    m_entities[eID].position = component;
}

void Scene::set_velocity_data(u64 eID, VelocityComponent& component) {
    m_entities[eID].velocity = component;
}

void Scene::set_render_data(u64 eID, RenderComponent& component) {
    m_entities[eID].render = component;
}

void Scene::set_gravity_data(u64 eID, GravityComponent& component) {
    m_entities[eID].gravity = component;
}

void Scene::set_control_func(u64 eID, ControlFunc controlFunc) {
    m_entities[eID].control.control_func = controlFunc;
}

void Scene::set_animation_data(u64 eID, AnimationComponent& animation) {
    m_entities[eID].animation = animation;
}
