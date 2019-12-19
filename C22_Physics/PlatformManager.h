#ifndef _PLATFORM_MANAGER_H
#define _PLATFORM_MANAGER_H

#include <deque>
#include "Platform.h"

class PlatformManager
{
    const vector3 CENTER;
    const float HEIGHT;
    const float OUTER_RADIUS;
    const float INNER_RADIUS;
    std::deque<Platform> platforms;

public:
    PlatformManager(const vector3& center, float height, float innerRadius, float outerRadius);
    void Update();
};

#endif // !_PLATFORM_MANAGER_H