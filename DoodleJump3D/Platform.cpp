#include "Platform.h"

Platform::Platform(vector3 startPos, String id)
: MyEntity("Minecraft\\Cube.obj", id)
{
	//start position fed into constructor, x and z coords should be random floats
    entMan = MyEntityManager::GetInstance();
    ID = id;
	position = startPos;
    toDelete = false;
    entMan->SetModelMatrix(glm::translate(position) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), ID);
}

void Platform::Despawn()
{
	//at end position or when hitting spikes
	MyEntityManager::ReleaseInstance();
}

void Platform::Move(float delta)
{
    if (m_pSolver->GetPosition().x == 300.0f) toDelete = true;
    position.y -= SPEED * delta;
    entMan->SetModelMatrix(glm::translate(position) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), ID);
}
