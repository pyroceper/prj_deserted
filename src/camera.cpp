#include "camera.h"

namespace Cam
{
    Vector2 offset{0.f, 0.f};
    Vector2 max_offset{2500.f, 2500.f};

    void followTarget(float target_x, float target_y, float camera_width, float camera_height)
    {
        offset.x = target_x - (camera_width * 0.5f);
        offset.y = target_y - (camera_height * 0.5f);

        if(offset.x < 0)
            offset.x = 0;
        if(offset.y < 0)
            offset.y = 0;
        if(offset.x > max_offset.x)
            offset.x = max_offset.x;
        if(offset.y > max_offset.y)
            offset.y = max_offset.y;
    }
};