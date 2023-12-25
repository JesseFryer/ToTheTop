#include "entity_groups.h"

EntityGroups::EntityGroups() {
    memset(m_tiles, 0, sizeof(u64) * MAX_TILES);
}
