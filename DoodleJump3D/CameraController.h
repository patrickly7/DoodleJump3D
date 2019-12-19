#ifndef _CAMERA_CONTROLLER_H
#define _CAMERA_CONTROLLER_H

#include "Definitions.h"
#include "Player.h"
#include "Simplex/Simplex.h"

class CameraController
{
public:
    CameraController(const Player& activePlayer, Simplex::vector3 centerPoint, float height, float radius);
    void Update();
private:
    const Simplex::vector3 CENTER_POINT;
    const float HEIGHT;
    const float RADIUS;
    const Player& ACTIVE_PLAYER;
    Simplex::CameraManager* camera;
};

#endif // !_CAMERA_CONTROLLER_H