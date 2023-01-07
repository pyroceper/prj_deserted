#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

namespace Cam
{
    extern Vector2 offset;
    extern Vector2 max_offset;
    extern void followTarget(float target_x, float target_y, float camera_width, float camera_height);
};

#endif