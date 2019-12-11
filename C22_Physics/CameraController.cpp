#include "CameraController.h"

CameraController::CameraController(const Player& active, Simplex::vector3 center, float height, float radius) :
    ACTIVE_PLAYER(active), CENTER_POINT(center), HEIGHT(height), RADIUS(radius) {
    camera = Simplex::CameraManager::GetInstance();
};

void CameraController::Update() {
    //vector3 v = ACTIVE_PLAYER.GetPosition() - CENTER_POINT;
    //vector3 n = vector3(0.0f, 1.0f, 0.0f); //normal to the xz plane
    //float dot = glm::dot(v, n);
    //vector3 dir = v - dot * n;
    //if (dir == vector3(0.0f, 0.0f, 0.0f)) dir = vector3(1.0f, 0.0f, 0.0f);
    //vector3 newPos = glm::normalize(dir) * RADIUS;
    //newPos[1] = HEIGHT;
    //camera->SetPosition(newPos);
    //camera->SetPositionTargetAndUpward(newPos, CENTER_POINT, vector3(0.0f, 1.0f, 0.0f));
    //printf("position %f, %f, %f\n", newPos.x, newPos.y, newPos.z);
}