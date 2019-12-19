#include "CameraController.h"

CameraController::CameraController(const Player& active, Simplex::vector3 center, float height, float radius) :
    ACTIVE_PLAYER(active), CENTER_POINT(center), HEIGHT(height), RADIUS(radius) {
    camera = Simplex::CameraManager::GetInstance();
    camera->SetPosition(ACTIVE_PLAYER.GetPosition());
};

void CameraController::Update() {
    //generates position in the edge of the cylinder
    vector3 v = ACTIVE_PLAYER.GetPosition() - CENTER_POINT;
    vector3 n = vector3(0.0f, 1.0f, 0.0f); //normal to the xz plane
    float dot = glm::dot(v, n);
    vector3 dir = v - dot * n;
    if (dir == vector3(0.0f, 0.0f, 0.0f)) dir = vector3(1.0f, 0.0f, 0.0f); //avoids errors when player and center at same position
    vector3 newPos = glm::normalize(dir) * RADIUS;
    //moves the camera to the correct position
    newPos[1] = ACTIVE_PLAYER.GetPosition()[1] + 10.0f;
    //  Could work and be better ----- vector3 newCenter = CENTER_POINT + vector3(v[0]/1.2f, ACTIVE_PLAYER.GetPosition()[1], v[2] / 1.2f);
    vector3 newCenter = ACTIVE_PLAYER.GetPosition();
    camera->SetPositionTargetAndUpward(newPos, newCenter, vector3(0.0f, 1.0f, 0.0f));
}