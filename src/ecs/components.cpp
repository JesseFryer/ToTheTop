#include "components.h"

bool Component::operator<(const Component& other) {
    return eID < other.eID;
}
