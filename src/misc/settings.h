# pragma once

// 1 -> on 0 -> off
#define DEV_STATS 1

#define WIN_W 1280
#define WIN_H 720

#define MAX_FPS 1000 
#define FRAME_TIME ((1000 + MAX_FPS - 1) / MAX_FPS) // ms
#define MAX_FRAME_TIME 40 // TODO: figure out what this should be

#define GRAVITY    100.0f
#define JUMP_TIMER 0.5f

#define PLAYER_W 48
#define PLAYER_H 64
#define PLAYER_SPEED 800
#define PLAYER_JUMP_STR 1200
#define PLAYER_GRAV_STR 50.0f

#define MOVING_SQUARE_W 16
#define MOVING_SQUARE_H 16
#define SQUARE_SPEED 600
