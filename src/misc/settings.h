# pragma once

// 1 -> on 0 -> off
#define DEV_STATS 1 

#define WIN_W 1280
#define WIN_H 720

#define MAX_FPS 1000 
#define FRAME_TIME ((1000 + MAX_FPS - 1) / MAX_FPS) // ms
#define MAX_FRAME_TIME 40 // TODO: figure out what this should be
