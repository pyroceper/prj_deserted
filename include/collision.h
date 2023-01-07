#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"

namespace Collision
{
    enum Side { LEFT, RIGHT, BOTTOM, TOP, NONE};
    bool AABB(Rectangle rectA, Rectangle rectB);
    Side getCollisionSide(Rectangle rect, Rectangle other);
    float getLeft(Rectangle rect);
    float getRight(Rectangle rect);
    float getTop(Rectangle rect);
    float getBottom(Rectangle rect);
};

#endif