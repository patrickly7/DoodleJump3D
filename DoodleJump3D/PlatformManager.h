#ifndef _PLATFORM_MANAGER_H
#define _PLATFORM_MANAGER_H

#include <deque>
#include <random>

#include "Simplex/Simplex.h"
#include "Platform.h"

class PlatformManager
{
    Simplex::MyEntityManager* entMan;
    Simplex::SystemSingleton* sysMan;
    const vector3 CENTER;
    const float HEIGHT;
    const float OUTER_RADIUS;
    const float INNER_RADIUS;
    float platYDist;
    std::deque<Platform*> platforms;
    uint64_t platformIndex;
public:
    PlatformManager(const vector3& center, float height, float innerRadius, float outerRadius);
    void Update(float delta);
};

#endif // !_PLATFORM_MANAGER_H