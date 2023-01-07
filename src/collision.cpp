#include "collision.h"

namespace Collision
{
    float getLeft(Rectangle rect)
    {
        return rect.x;
    }

    float getRight(Rectangle rect)
    {
        return rect.x + rect.width;
    }

    float getTop(Rectangle rect)
    {
        return rect.y;
    }

    float getBottom(Rectangle rect)
    {
        return rect.y + rect.height;
    }

    bool AABB(Rectangle rectA, Rectangle rectB)
    {
        return
            getRight(rectA) >= getLeft(rectB) &&
            getLeft(rectA) <= getRight(rectB) &&
            getTop(rectA) <= getBottom(rectB) &&
            getBottom(rectA) >= getTop(rectB);
    }

    Side getCollisionSide(Rectangle rect, Rectangle other)
    {
        int right, left, top, bottom;
        right = getRight(rect) - getLeft(other);
        left = getRight(other) - getLeft(rect);
        top = getBottom(other) - getTop(rect);
        bottom = getBottom(rect) - getTop(other);

        int vals[4] = {left, right, top, bottom};
        int lowest = vals[0];

        for(int i=0;i<4;i++)
        {
            if(vals[i] < lowest)
                lowest = vals[i];
        }

        if(lowest == right) return Side::RIGHT;
        if(lowest == left) return Side::LEFT;
        if(lowest == top) return Side::TOP;
        if(lowest == bottom) return Side::BOTTOM;
        return Side::NONE;
    }
};