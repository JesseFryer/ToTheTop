#include "scene.h"

void Scene::set_renderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

void Scene::set_input(InputState* input) {
    m_input = input;
}

void Scene::update(float timeStep) {
    system_render();
}

////////////////// query functions /////////////////////

void Scene::add_render_component(RenderComponent component) {
    m_renderComponents.push_back(component);
}

bool Scene::has_render_component(u64 eID) {
    for (RenderComponent component : m_renderComponents) {
        if (component.eID == eID) {
            return true;
        }
    }
    return false;
}

void Scene::add_control_component(ControlComponent component) {
    m_controlComponents.push_back(component);
}

bool Scene::has_control_component(u64 eID) {
    for (ControlComponent component : m_controlComponents) {
        if (component.eID == eID) {
            return true;
        }
    }
    return false;
}

void Scene::add_velocity_component(VelocityComponent component) {
    m_velocityComponents.push_back(component);
}

bool Scene::has_velocity_component(u64 eID) {
    for (VelocityComponent component : m_velocityComponents) {
        if (component.eID == eID) {
            return true;
        }
    }
    return false;
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

void Scene::system_control() {
    for (ControlComponent component : m_controlComponents) {
        if (has_velocity_component(component.eID)) {
        }
    }
}

