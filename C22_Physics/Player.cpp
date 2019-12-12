#include "Player.h"

Player::Player(String ID, vector3 centerPos) 
: MyEntity("Minecraft\\Steve.obj", ID)
{
    centerPosition = centerPos;
    jumpForce = vector3(0.0f, 1.5f, 0.0f);
    movementFactor = 3.0f;
    direction = Movement_Key::NONE;
    dir = centerPos - GetPosition();

    angleRotations = {
        { Movement_Key::RIGHT, 0.0f },
        { Movement_Key::TOP_RIGHT, 45.0f },
        { Movement_Key::TOP, 90.0f },
        { Movement_Key::TOP_LEFT, 135.0f },
        { Movement_Key::LEFT, 180.0f },
        { Movement_Key::BOTTOM_LEFT, 225.0f },
        { Movement_Key::BOTTOM, 270.0f },
        { Movement_Key::BOTTOM_RIGHT, 315.0f }
    };
}

void Player::Update() 
{
    vector3 pos = GetPosition();
    centerPosition.y = GetPosition().y;
    m_pSolver->Update();
    vector3 npos = GetPosition();

    SetModelMatrix(glm::translate(GetModelMatrix(), npos - pos));
}

void Player::Jump() 
{
    if (m_pSolver->GetOnAir()) 
		return;

    m_pSolver->SetOnAir(true);
    ApplyForce(jumpForce);
}

void Player::rotateTo(Movement_Key k) {
    float angleFrom = -angleRotations[direction];
    float angleTo = angleRotations[k];
    float angle = angleTo - angleFrom;
    printf("Angle To = %f\n", angleTo);
    angle = glm::radians(angle);
    matrix4 old = GetModelMatrix();
    matrix4 newm = glm::rotate(old, angle, AXIS_Y);
    SetModelMatrix(newm);
}
void Player::Move(Movement_Key k, float ellapsed) {
    if (k == Movement_Key::NONE) return;
    Movement_Key cur = k;
    auto pos = GetPosition();
    if (direction != cur) {
        rotateTo(cur);
        direction = cur;
    }
    // goes forward (in local coordinates)
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
    ApplyForce(movDir * ellapsed * movementFactor);
}