#include "PlatformManager.h"

PlatformManager::PlatformManager(const vector3& center, float height, float innerRadius, float outerRadius) 
    : CENTER(center), HEIGHT(height), INNER_RADIUS(innerRadius), OUTER_RADIUS(outerRadius)
{
    // Platform initialization -- initial state of platforms
    // At any time there is a platform every 5units in the y direction.
    // The first element of the deque in the one in the bottom and the 
    // last elemente is at the top
    int initialsPlatforms = std::floor(height / 5.0f);
    for (int i = 1; i < initialsPlatforms; i++) {
        float x, y, z;
        x = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 15.0f - 7.5f;
        y = 5.0f * i;
        z = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 15.0f - 7.5f;
        platforms.push_back(Platform(vector3(x, y, z), "Platform_" + std::to_string(i)));
    }
}
