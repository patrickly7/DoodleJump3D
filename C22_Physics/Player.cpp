#include "Player.h"

Player::Player(String ID, vector3 centerPos) 
: MyEntity("Minecraft\\Steve.obj", ID)
{
    centerPosition = centerPos;
    jumpForce = vector3(0.0f, 1.5f, 0.0f);
    movementFactor = 3.0f;
    direction = Movement_Key::NONE;
    dir = centerPos - GetPosition();
}

void Player::Update() 
{
    m_pSolver->Update();
    SetModelMatrix(glm::translate(m_pSolver->GetPosition()) * glm::scale(m_pSolver->GetSize()));
}

void Player::Jump() 
{
    if (m_pSolver->GetOnAir()) 
		return;

    m_pSolver->SetOnAir(true);
    ApplyForce(jumpForce);
}


glm::quat fromTo(const vector3& v1, const vector3& v2)
{
    vector3 a = glm::cross(v1, v2);
    glm::quat q;

    float dot = glm::dot(v1, v2);

    if (dot >= 0.999999f)
    {
        q = glm::quat(0, 0, 0, 1);

    }
    else if (dot <= -0.99999f)
    {
        vector3 axis = glm::cross(vector3(1, 0, 0), v2);

        if (glm::length(axis) < 0.0001) // pick another if colinear
            axis = glm::cross(vector3(0, 1, 0), v2);
        glm::normalize(axis);
        q = glm::quat(-axis);
    }
    else
    {
        float s = sqrt((1 + dot) * 2);
        float invs = 1 / s;

        vector3 c = glm::cross(v1, v2);

        q.x = c.x * invs;
        q.y = c.y * invs;
        q.z = c.z * invs;
        q.w = s * 0.5f;
    }
    glm::normalize(q);
    return q;
}

void Player::Move(Movement_Key k, float ellapsed) {
    if (k == Movement_Key::NONE) return;
    Movement_Key cur = Movement_Key::NONE;
    auto pos = GetPosition();
    printf("============================\nposition %f, %f, %f\n", pos.x, pos.y, pos.z);
    vector3 fwDir = glm::normalize(-centerPosition + pos);
    vector3 upDir = vector3(0.0f, 1.0f, 0.0f);
    vector3 movDir;
    switch (k)
    {
    case Movement_Key::RIGHT:
        movDir = -glm::cross(upDir, fwDir);
        cur = Movement_Key::RIGHT;
        break;
    case Movement_Key::TOP_RIGHT:
        movDir = (-glm::normalize(glm::cross(upDir, fwDir)) + fwDir) * 0.5f;
        cur = Movement_Key::TOP_RIGHT;
        break;
    case Movement_Key::TOP:
        movDir = fwDir;
        cur = Movement_Key::TOP;
        break;
    case Movement_Key::TOP_LEFT:
        movDir = (glm::normalize(glm::cross(upDir, fwDir)) + fwDir) * 0.5f;
        cur = Movement_Key::TOP_LEFT;
        break;
    case Movement_Key::LEFT:
        movDir = glm::cross(upDir, fwDir);
        cur = Movement_Key::LEFT;
        break;
    case Movement_Key::BOTTOM_LEFT:
        movDir = (glm::normalize(glm::cross(upDir, fwDir)) - fwDir) * 0.5f;
        cur = Movement_Key::BOTTOM_LEFT;
        break;
    case Movement_Key::BOTTOM:
        movDir = -fwDir;
        cur = Movement_Key::BOTTOM;
        break;
    case Movement_Key::BOTTOM_RIGHT:
        movDir = (-glm::normalize(glm::cross(upDir, fwDir)) - fwDir) * 0.5f;
        cur = Movement_Key::BOTTOM_RIGHT;
        break;
    default:
        return;
    }
    movDir = -glm::normalize(movDir);
    printf("dir %f, %f, %f\n", movDir.x, movDir.y, movDir.z);
    if (direction != cur) {
        printf("CHANGED\n");
        auto q = fromTo(dir, movDir);
        auto aux = dir * q; //Result is correct
        matrix4 m = glm::toMat4(q);
        SetModelMatrix(GetModelMatrix() * m);
        dir = movDir;
        direction = cur;
    }
    ApplyForce(movDir * ellapsed * movementFactor);
    printf("position %f, %f, %f\n", pos.x, pos.y, pos.z);
}