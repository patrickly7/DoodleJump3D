#include "Platform.h"

Platform::Platform(vector3 startPos, String id)
: MyEntity("Minecraft\\Cube.obj", id)
{
	//start position fed into constructor, x and z coords should be random floats
    entMan = MyEntityManager::GetInstance();
    ID = id;
    m_pSolver->SetPosition(startPos);
    toDelete = false;
    entMan->SetModelMatrix(glm::translate(startPos) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), ID);
}

void Platform::Despawn()
{
	//at end position or when hitting spikes
	MyEntityManager::ReleaseInstance();
}

void Platform::Move(float delta)
{
    vector3 position = m_pSolver->GetPosition();
    position.y -= SPEED * delta;
    if (position.x > 100.0f) {
        toDelete = true;
    }
    m_pSolver->SetPosition(position);
    entMan->SetModelMatrix(glm::translate(position) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), ID);
}
