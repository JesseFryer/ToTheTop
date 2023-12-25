#include "../misc/types.h"

#define MAX_TILES 1000

struct EntityGroups {
    u64 m_tiles[MAX_TILES];
    u64 m_tileCount;

    EntityGroups();
};
