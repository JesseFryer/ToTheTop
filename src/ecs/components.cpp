#include "components.h"

bool Entity::operator<(const Entity& other) {
    return eID < other.eID;
}
