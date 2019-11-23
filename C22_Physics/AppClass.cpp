#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 5.0f, 25.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

    currentPlayer = new Player("Player00");
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");

	m_pEntityMngr->UsePhysicsSolver();

	//scale and place these
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_0");
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1");

	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(-2.0f, -0.05f, 3.0f)) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), "Platform_0");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(4.0f, 3.0f, -3.0f)) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), "Platform_1");

	// create and place pit of spikes (pawns)
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++) 
		{
			m_pEntityMngr->AddEntity("Sorted\\Pawn.obj", "Spike_" + std::to_string(i) + std::to_string(j));
			m_pEntityMngr->SetModelMatrix(glm::translate(vector3((i * 1.25f) - 5.5f, -5.0f, (j * 1.25f) - 5.5f)) * glm::scale(vector3(0.5f)), "Spike_" + std::to_string(i) + std::to_string(j));
		} 
	}
    m_pEntityMngr->AddEntity((MyEntity*)currentPlayer);
    currentPlayerIndex = m_pEntityMngr->GetEntityIndex("Player00");
    cameraController = new CameraController(*currentPlayer, vector3(0.0f, 3.0f, 0.0f), 4.0f, 50.0f);

}
void Application::Update(void)
{
    cameraController->Update();
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Set the model matrix for the main object
	//m_pEntityMngr->SetModelMatrix(m_m4Steve, "Steve");

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
	//m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui,
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}