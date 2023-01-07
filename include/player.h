#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace Player
{
    extern Rectangle rec;
    extern float dx;
    extern float dy;
    extern const float GRAVITY;
    extern float jump_height;
    extern const float JUMP_HEIGHT;
    extern float fall_speed;
    extern float speed;
    extern bool on_floor;
    extern bool is_jump;

    enum State { IDLE, JUMP, RUN};
    extern State state;

};

#endif