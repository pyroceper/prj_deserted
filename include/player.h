#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace Player
{
    extern Rectangle rec;
    extern const float GRAVITY;
    extern float jump_height;
    extern const float JUMP_HEIGHT;
    extern float fall_speed;
    extern bool on_floor;
    extern bool is_jump;

    enum State { IDLE, JUMP, RUN};
    extern State state;
};

#endif