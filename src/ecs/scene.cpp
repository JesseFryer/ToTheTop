#include "scene.h"
#include <iostream>

void Scene::set_renderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

void Scene::set_input(InputState* input) {
    m_input = input;
}

void Scene::update(float timeStep) {
    system_control();
    system_move(timeStep);
    system_render();
}

////////////////// bit mask stuff for lookups /////////////////////

bool Scene::has_components(u64 eID, u32 componentsMask) {
    return (bool) (m_activeComponents[eID] & componentsMask);
}

void Scene::add_components(u64 eID, u32 componentsMask) {
    m_activeComponents[eID] |= componentsMask;
}

//////////////////////// add components ///////////////////////////

void Scene::add_render_component(RenderComponent component) {
    if (!has_components(component.eID, CMP_RENDER)) {
        add_components(component.eID, CMP_RENDER);
        m_renderComponents.push_back(component);
    }
}

void Scene::add_control_component(ControlComponent component) {
    if (!has_components(component.eID, CMP_CONTROL)) {
        add_components(component.eID, CMP_CONTROL);
        m_controlComponents.push_back(component);
    }
}

void Scene::add_transform_component(TransformComponent component) {
    if (!has_components(component.eID, CMP_TRANSFORM)) {
        add_components(component.eID, CMP_TRANSFORM);
        m_transformComponents.push_back(component);
    }
}

u64 Scene::get_new_eid() {
    u64 eID;
    if (m_reusableEntityIDs.empty()) {
        eID = m_entityCount++;
    } else {
        eID = m_reusableEntityIDs.back();
        m_reusableEntityIDs.pop_back();
    }
    return eID;
}

////////////////// retrieve component indexes ////////////////////

size_t Scene::get_render_component(u64 eID) {
    size_t left = 0;
    size_t right = m_renderComponents.size() - 1;
    size_t mid;
    while (left <= right) {
        mid = left + (right - left) * 0.5;
        if (m_renderComponents[mid].eID == eID) {
            return mid;
        }
        if (m_renderComponents[mid].eID < eID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return mid;
}

size_t Scene::get_control_component(u64 eID) {
    size_t index;
    for (index = 0; index < m_controlComponents.size(); index++) {
        if (m_controlComponents[index].eID == eID) {
            break;
        }
    }
    return index;
}

size_t Scene::get_transform_component(u64 eID) {
    size_t left = 0;
    size_t right = m_transformComponents.size() - 1;
    size_t mid;
    while (left <= right) {
        mid = left + (right - left) * 0.5;
        if (m_transformComponents[mid].eID == eID) {
            return mid;
        }
        if (m_transformComponents[mid].eID < eID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return mid;
}

///////////////////// systems //////////////////////////

void Scene::system_render() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    for (RenderComponent component : m_renderComponents) {
        SDL_RenderFillRect(m_renderer, &component.rect);
    }
    SDL_RenderPresent(m_renderer);
}

void Scene::system_move(float timeStep) {
    for (size_t i = 0; i < m_transformComponents.size(); i++) {
        u64 eID = m_transformComponents.at(i).eID;
        m_transformComponents.at(i).x += m_transformComponents.at(i).xV * timeStep;
        m_transformComponents.at(i).y += m_transformComponents.at(i).yV * timeStep;
        if (has_components(eID, CMP_RENDER)) {
            size_t renderIndex = get_render_component(eID);
            m_renderComponents.at(renderIndex).rect.x = (int) m_transformComponents.at(i).x;
            m_renderComponents.at(renderIndex).rect.y = (int) m_transformComponents.at(i).y;
        }
    }
}

void Scene::system_control() {
    for (ControlComponent component : m_controlComponents) {
        u64 eID = component.eID;
        if (has_components(eID, CMP_TRANSFORM)) {
            size_t transIndex = get_transform_component(eID);
            m_transformComponents.at(transIndex).xV = 0;
            m_transformComponents.at(transIndex).yV = 0;
            const float speed = 400;
            if (m_input->key_pressed(K_W)) {
                m_transformComponents.at(transIndex).yV = -speed;
            }
            if (m_input->key_pressed(K_A)) {
                m_transformComponents.at(transIndex).xV = -speed;
            }
            if (m_input->key_pressed(K_S)) {
                m_transformComponents.at(transIndex).yV = speed;
            }
            if (m_input->key_pressed(K_D)) {
                m_transformComponents.at(transIndex).xV = speed;
            }
        }
    }
}
