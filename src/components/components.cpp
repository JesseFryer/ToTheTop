#include "components.h"

bool is_active(u32 activeComps, u32 checkComps) {
    return ((activeComps & checkComps) == checkComps);
}

PositionComponent::PositionComponent() {
    x = 0.0f;
    y = 0.0f;
}

VelocityComponent::VelocityComponent() {
    xV = 0.0f;
    yV = 0.0f;
}

RenderComponent::RenderComponent() {
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    textureRect.x = 0;
    textureRect.y = 0;
    textureRect.w = 0;
    textureRect.h = 0;
    texture = nullptr;
}

ControlComponent::ControlComponent() {
    control_func = nullptr;
}

Entity::Entity() {
    activeComponents = 0;
}

bool Entity::operator<(const Entity& other) {
    return eID < other.eID;
}
