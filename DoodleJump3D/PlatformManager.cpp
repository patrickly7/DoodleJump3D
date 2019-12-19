#include "PlatformManager.h"

PlatformManager::PlatformManager(const vector3& center, float height, float innerRadius, float outerRadius) 
    : CENTER(center), HEIGHT(height), INNER_RADIUS(innerRadius), OUTER_RADIUS(outerRadius)
{
    // Platform initialization -- initial state of platforms
    // At any time there is a platform every 5units in the y direction.
    // The first element of the deque in the one in the bottom and the 
    // last elemente is at the top
    platYDist = 0.5f;
    entMan = Simplex::MyEntityManager::GetInstance();
    float yOff = -height / 2.0f;
    int initialsPlatforms = std::floor(height / platYDist);
    for (int i = 1; i < initialsPlatforms; i++) {
        float x, y, z;
        x = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 15.0f - 7.5f;
        y = platYDist * i + yOff;
        z = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 15.0f - 7.5f;
        platforms.push_back(new Platform(vector3(x, y, z), "Platform_" + std::to_string(i)));
        entMan->AddEntity((MyEntity*)platforms[i - 1]);
        entMan->UsePhysicsSolver(true);
    }
    platformIndex = initialsPlatforms;
}

void PlatformManager::Update(float delta) {

    if (platforms.back()->GetToDelete()) {
        platforms.back()->Despawn();
        platforms.pop_back();
    }
    for (Platform* p : platforms) p->Move(delta);
}
