#pragma once

#include <SDL2/SDL.h>

#define K_W      0x00000001
#define K_A      0x00000002
#define K_S      0x00000004
#define K_D      0x00000008
#define K_UP     0x00000010
#define K_LEFT   0x00000020
#define K_DOWN   0x00000040
#define K_RIGHT  0x00000080
#define K_ESC    0x00000100
#define K_QUIT   0x00000200

#define K_W_OFF     0xfffffffe
#define K_A_OFF     0xfffffffd
#define K_S_OFF     0xfffffffb
#define K_D_OFF     0xfffffff7
#define K_UP_OFF    0xffffffef
#define K_LEFT_OFF  0xffffffdf
#define K_DOWN_OFF  0xffffffbf
#define K_RIGHT_OFF 0xffffff7f
#define K_ESC_OFF   0xfffffeff
#define K_QUIT_OFF  0xfffffdff

typedef unsigned long t_keystate;
typedef unsigned long t_key;

struct MouseState {
    bool leftClick;
    bool rightClick;
    int  xpos;
    int  ypos;
    int  xmove;
    int  ymove;
    int  scroll;
};

class InputState {
    public:
        InputState();
        void update();               // empties the SDL event queue

        // Keyboard
        bool key_pressed(t_key key); // returns true if key is pressed

        // Mouse
        bool left_click();           // returns true if left click is pressed
        bool right_click();          // returns true if right click is pressed
        int  get_mouse_x();          // returns mouse x position
        int  get_mouse_y();          // returns mouse y position

    private:
        t_keystate m_keyState;
        MouseState m_mouseState;

        void update_keys(SDL_Event* keyEvent);
        void update_mouse_motion(SDL_Event* mouseMotionEvent);
        void update_mouse_button(SDL_Event* mouseButtonEvent);

};
