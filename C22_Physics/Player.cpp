#include "Player.h"

Player::Player(String ID) 
: MyEntity("Minecraft\\Steve.obj", ID)
{
    gravityForce = vector3(0.0f, 1.0f, 0.0f);
}

void Player::Update() {
    m_pSolver->Update();
    SetModelMatrix(glm::translate(m_pSolver->GetPosition()) * glm::scale(m_pSolver->GetSize()));
}