#include "enemy.h"

namespace Enemy
{
    Rectangle rect[50];
    float dx;
    float dy;
    const float GRAVITY = 35.0f;
    int is_left[50];// 1 -> right, -1 -> left
    bool is_active[50] = {0};
    bool is_dead[50] = {0};
    Type type[50];
    float animation_tick[50] = {0};
    float animation_death_tick[50] = {0};
    float death_timer[50] = {0};
};