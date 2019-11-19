#include "Player.h"

Player::Player(String ID) 
: MyEntity("Minecraft\\Steve.obj", ID)
{
    jumpForce = vector3(0.0f, 1.5f, 0.0f);
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