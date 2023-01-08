#include "enemy.h"

namespace Enemy
{
    Rectangle rect[50];
    float dx;
    float dy;
    const float GRAVITY = 35.0f;
    int is_left[50];// 1 -> right, -1 -> left
    bool is_active[50] = {0};
    Type type[50];
};