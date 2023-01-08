#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "collision.h"

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
    extern bool is_running;
    extern bool is_attack;
    extern int is_left;
    extern bool left, right, top, bottom;
    extern Collision::Side collision_side;
    extern float collision_array[4];
    extern float animation_idle_tick;
    extern float animation_walk_tick;
    extern float animation_attack_tick;
};
#endif