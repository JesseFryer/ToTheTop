#include "scene.h"
#include "../misc/settings.h"
#include <iostream>

u64 Scene::add_entity() {
    u64 eID;
    if (m_reusableEntityIDs.size()) {
        eID = m_reusableEntityIDs.front();
        m_reusableEntityIDs.pop();
        memset(&m_entities.at(eID), 0, sizeof(Entity));
        //m_entities.at(eID) = {};
    } else {
        eID = m_entities.size();
        Entity entity;
        m_entities.push_back(entity);
    }
    m_entities.at(eID).eID = eID;
    return eID;
}

void Scene::remove_entity(u64 eID) {
    m_entities.at(eID) = Entity();
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

void Scene::set_control_func(u64 eID, ControlFunc controlFunc) {
    m_entities.at(eID).control.control_func = controlFunc;
}
