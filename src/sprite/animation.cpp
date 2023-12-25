#include "animation.h"
#include <iostream>

Animation::Animation() {
    memset(m_frames, 0, sizeof(SDL_Rect) * MAX_FRAMES);
    m_frameCount = 0;
}

void Animation::set_frames(std::vector<SDL_Rect>& frames) { 
    m_frameCount = frames.size();
    if (m_frameCount > MAX_FRAMES) {
        std::cout << "animation exceeds the maximum frames ("
            << MAX_FRAMES << ")\n";
    } else {
        for (size_t i = 0; i < m_frameCount; i++) {
            m_frames[i] = frames[i];
        }
    }
}

Animations::Animations() {
    m_animationCount = 0;
}

void Animations::add_animation(std::vector<SDL_Rect>& frames) {
    if (m_animationCount == MAX_ANIMATIONS) {
        std::cout << "exceeded maximum animations ("
            << MAX_ANIMATIONS << ")\n";
    } else {
        m_animations[m_animationCount++].set_frames(frames);
    }
}
