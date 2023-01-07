#include "player.h"


namespace Player
{
    Rectangle rec{0, 0, 32, 16};
    float dx = 0.0f;
    float dy = 0.0f;
    const float GRAVITY = 35.0f;
    const float JUMP_HEIGHT = 350.0f;
    float jump_height = JUMP_HEIGHT;
    float fall_speed = 0.0f;
    float speed = 100.0f;
    bool on_floor = false; // change this!
    bool is_jump = false;
    State state = State::IDLE; 

};