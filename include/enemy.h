#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "collision.h"

namespace Enemy
{
    extern Rectangle rect[50];
    extern float dx;
    extern float dy;
    extern const float GRAVITY;
    extern int is_left[50];
    extern bool is_active[50];
    enum Type { PATROL, NONE};
    extern Type type[50];
};

#endif
