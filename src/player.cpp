#include "player.h"


namespace Player
{
    Rectangle rec{0, 0, 32, 16};
    float dx = 0.0f;
    float dy = 0.0f;
    const float GRAVITY = 35.0f;
    const float JUMP_HEIGHT = 400.0f;
    float jump_height = JUMP_HEIGHT;
    float fall_speed = 0.0f;
    float speed = 150.0f;
    bool on_floor = false; // change this!
    bool is_jump = false;
    bool is_running = false;
    int is_left = 1; // 1 -> right, -1 -> left
    bool left, right, top, bottom;
    Collision::Side collision_side = Collision::Side::NONE;
    float collision_array[4] = {0.f};
    float animation_idle_tick = 0.0f;
    float animation_walk_tick = 0.0f;
};