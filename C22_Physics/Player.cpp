#include "Player.h"

Player::Player(String ID, vector3 centerPos) 
: MyEntity("Minecraft\\Steve.obj", ID)
{
    centerPosition = centerPos;
    jumpForce = vector3(0.0f, 1.5f, 0.0f);
    movementFactor = 2.0f;
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

void Player::Move(Movement_Key k, float ellapsed) {
    if (k == Movement_Key::NONE) return;
    vector3 fwDir = glm::normalize(-centerPosition + GetPosition());
    vector3 upDir = vector3(0.0f, 1.0f, 0.0f);
    vector3 movDir;
    switch (k)
    {
    case Movement_Key::RIGHT:
        movDir = -glm::cross(upDir, fwDir);
        break;
    case Movement_Key::TOP_RIGHT:
        movDir = (-glm::normalize(glm::cross(upDir, fwDir)) + fwDir) * 0.5f;
        break;
    case Movement_Key::TOP:
        movDir = fwDir;
        break;
    case Movement_Key::TOP_LEFT:
        movDir = (glm::normalize(glm::cross(upDir, fwDir)) + fwDir) * 0.5f;
        break;
    case Movement_Key::LEFT:
        movDir = glm::cross(upDir, fwDir);
        break;
    case Movement_Key::BOTTOM_LEFT:
        movDir = (glm::normalize(glm::cross(upDir, fwDir)) - fwDir) * 0.5f;
        break;
    case Movement_Key::BOTTOM:
        movDir = -fwDir;
        break;
    case Movement_Key::BOTTOM_RIGHT:
        movDir = (glm::normalize(glm::cross(upDir, fwDir)) - fwDir) * 0.5f;
        break;
    default:
        return;
    }
    movDir = -glm::normalize(movDir);
    ApplyForce(movDir * ellapsed);
}