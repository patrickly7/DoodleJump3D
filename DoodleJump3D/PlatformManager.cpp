#include "PlatformManager.h"

PlatformManager::PlatformManager(const vector3& center, float height, float innerRadius, float outerRadius) 
    : CENTER(center), HEIGHT(height), INNER_RADIUS(innerRadius), OUTER_RADIUS(outerRadius)
{
    // Platform initialization -- initial state of platforms
    // At any time there is a platform every 5units in the y direction.
    // The first element of the deque in the one in the bottom and the 
    // last elemente is at the top
    platYDist = 0.5f;
    timePassed = 0.0f;
    entMan = Simplex::MyEntityManager::GetInstance();
    float yOff = -height / 2.0f;
    int initialsPlatforms = std::floor(height / platYDist);
    for (int i = 1; i < initialsPlatforms; i++) {
        float x, y, z;
        float angle = (rand()) % 360;
        float len = (rand()) % (int)(OUTER_RADIUS - INNER_RADIUS);
        x = sin(angle) * len;
        y = platYDist * (initialsPlatforms - i) + yOff;
        z = cos(angle) * len;
        platforms.push_back(new Platform(vector3(x, y, z), "Platform_" + std::to_string(i)));
        entMan->AddEntity((MyEntity*)platforms[i - 1]);
        entMan->UsePhysicsSolver(true);
    }
    platformIndex = initialsPlatforms;
}

void PlatformManager::Update(float delta) {
    timePassed += delta;
    Platform* back;
    while (true) {
        back = platforms.back();
        if (back->GetToDelete()) {
            entMan->RemoveEntity(back->ID);
            delete back;
            platforms.pop_back();
        }
        else break;
    }
    if (timePassed >= 0.5f) {
        timePassed -= 0.5f;
        float x, y, z;
        float angle = (rand()) % 360;
        float len = (rand()) % (int)(OUTER_RADIUS - INNER_RADIUS);
        x = sin(angle) * len;
        y = platYDist * HEIGHT/2.0f;
        z = cos(angle) * len;
        platforms.push_back(new Platform(vector3(x, y, z), "Platform_" + std::to_string(size(platforms))));
        entMan->AddEntity((MyEntity*)platforms[size(platforms)-1]);
        entMan->UsePhysicsSolver(true);
    }
    for (Platform* p : platforms) p->Move(delta);
}
