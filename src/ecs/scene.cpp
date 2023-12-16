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

void Scene::add_velocity_component(VelocityComponent component) {
    if (!has_components(component.eID, CMP_VELOCITY)) {
        add_components(component.eID, CMP_VELOCITY);
        m_velocityComponents.push_back(component);
    }
}

void Scene::add_position_component(PositionComponent component) {
    if (!has_components(component.eID, CMP_POSITION)) {
        add_components(component.eID, CMP_POSITION);
        m_positionComponents.push_back(component);
    }
}

////////////////// retrieve component indexes ////////////////////

//TODO: since I'm assuming we know its in there we can use size_t
//      and not bother having a failure value (-1)

int Scene::get_render_component(u64 eID) {
    for (int i = 0; i < m_renderComponents.size(); i++) {
        if (m_renderComponents[i].eID == eID) {
            return i;
        }
    }
    return -1;
}

int Scene::get_control_component(u64 eID) {
    for (int i = 0; i < m_controlComponents.size(); i++) {
        if (m_controlComponents[i].eID == eID) {
            return i;
        }
    }
    return -1;
}

int Scene::get_velocity_component(u64 eID) {
    for (int i = 0; i < m_velocityComponents.size(); i++) {
        if (m_velocityComponents[i].eID == eID) {
            return i;
        }
    }
    return -1;
}

int Scene::get_position_component(u64 eID) {
    for (int i = 0; i < m_positionComponents.size(); i++) {
        if (m_positionComponents[i].eID == eID) {
            return i;
        }
    }
    return -1;
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
    for (size_t i = 0; i < m_positionComponents.size(); i++) {
        u64 eID = m_positionComponents[i].eID;
        if (has_components(eID, CMP_VELOCITY)) {
            int velIndex = get_velocity_component(eID);
            VelocityComponent vel = m_velocityComponents[velIndex];
            m_positionComponents.at(i).x += vel.x * timeStep;
            m_positionComponents.at(i).y += vel.y * timeStep;
        }
        if (has_components(eID, CMP_RENDER)) {
            int renderIndex = get_render_component(eID);
            m_renderComponents.at(renderIndex).rect.x = (int) m_positionComponents[i].x;
            m_renderComponents.at(renderIndex).rect.y = (int) m_positionComponents[i].y;
        }
    }
}

void Scene::system_control() {
    for (ControlComponent component : m_controlComponents) {
        u64 eID = component.eID;
        if (has_components(eID, CMP_VELOCITY)) {
            int velIndex = get_velocity_component(eID);
            m_velocityComponents.at(velIndex).x = 0;
            m_velocityComponents.at(velIndex).y = 0;
            const float speed = 400;
            if (m_input->key_pressed(K_W)) {
                m_velocityComponents.at(velIndex).y = -speed;
            }
            if (m_input->key_pressed(K_A)) {
                m_velocityComponents.at(velIndex).x = -speed;
            }
            if (m_input->key_pressed(K_S)) {
                m_velocityComponents.at(velIndex).y = speed;
            }
            if (m_input->key_pressed(K_D)) {
                m_velocityComponents.at(velIndex).x = speed;
            }
        }
    }
}
