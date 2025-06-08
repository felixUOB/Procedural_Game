#ifndef TIMER_H
#define TIMER_H

struct Timer {
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void update();
};

#endif