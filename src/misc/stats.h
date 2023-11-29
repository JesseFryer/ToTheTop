#pragma once

#include "types.h"

typedef struct DevStats {
    u32 timeAccumulator;
    u32 frames;
    u32 lastTime;
} DevStats;
