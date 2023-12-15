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

