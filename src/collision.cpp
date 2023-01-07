#include "collision.h"

namespace Collision
{
    bool AABB(Rectangle rectA, Rectangle rectB)
    {
        if(rectA.x < rectB.x + rectB.width &&
            rectA.x + rectA.width > rectB.x &&
            rectA.y < rectB.y + rectB.height &&
            rectA.y + rectA.height > rectB.y)
        return true;

        return false;
    }
};