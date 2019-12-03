#include "AppClass.h"
using namespace Simplex;

void Application::InitVariables(void)
{
	// Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 5.0f, 25.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	// Add Player Entity (Index 0)
	currentPlayer = new Player("Player00");
	m_pEntityMngr->AddEntity((MyEntity*)currentPlayer);
	currentPlayerIndex = m_pEntityMngr->GetEntityIndex("Player00");
	m_pEntityMngr->UsePhysicsSolver();

	// Death Bed (Index 1)
	auto spikeHeight = -25.0f;
	auto scaleByThis = 40.0f;

	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Spike_Bed");
	auto spikeBedMatrix = glm::translate(IDENTITY_M4, vector3(-scaleByThis / 2, spikeHeight, -scaleByThis / 2));
	spikeBedMatrix = glm::scale(spikeBedMatrix, vector3(scaleByThis, 1.0f, scaleByThis));
	m_pEntityMngr->SetModelMatrix(spikeBedMatrix, "Spike_Bed");
	m_pEntityMngr->UsePhysicsSolver();

	// Walls (Index 2 - 9)
	auto wallWidth = 20.0f;
	auto wallHeight = 50.0f;
	for (int index = 0; index < 8; index++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall_" + std::to_string(index));

		auto scalingMatrix = glm::scale(vector3(wallWidth, 0.5f, wallHeight));
		auto rotationMatrix = glm::rotate(IDENTITY_M4, glm::radians(90.0f), vector3(1.0f, 0.0f, 0.0f));
		rotationMatrix *= glm::rotate(glm::radians(45.0f * index), vector3(0.0f, 0.0f, 1.0f));

		// Position the Walls into a Cylindrical-Like Shape
		auto translationMatrix = glm::translate(vector3(-wallWidth / 2, wallHeight / 2, -20.0f)); // Back
		if (index == 1) // Back Right
			translationMatrix = glm::translate(vector3(wallWidth / 2, wallHeight / 2, -20.0f));
		else if (index == 2) // Right
			translationMatrix = glm::translate(vector3(wallWidth, wallHeight / 2, -10.0f));
		else if (index == 3) // Front Right
			translationMatrix = glm::translate(vector3(wallWidth, wallHeight / 2, 10.0f));
		else if (index == 4) // Front
			translationMatrix = glm::translate(vector3(wallWidth / 2, wallHeight / 2, 20.0f));
		else if (index == 5) // Front Left
			translationMatrix = glm::translate(vector3(-wallWidth / 2, wallHeight / 2, 20.0f));
		else if (index == 6) // Left
			translationMatrix = glm::translate(vector3(-wallWidth, wallHeight / 2, 10.0f));
		else if (index == 7) // Back Left
			translationMatrix = glm::translate(vector3(-wallWidth, wallHeight / 2, -10.0f));
	
		auto wallMatrix = translationMatrix * rotationMatrix * scalingMatrix;

		m_pEntityMngr->SetModelMatrix(wallMatrix, "Wall_" + std::to_string(index));
	}

	// Platforms (Index 10+)
	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_0");
	m_pEntityMngr->SetModelMatrix(IDENTITY_M4 * glm::scale(vector3(5.0f, 0.1f, 5.0f)), "Platform_0");
	m_pEntityMngr->UsePhysicsSolver();

	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1");
	m_pEntityMngr->SetModelMatrix(glm::translate(vector3(4.0f, 3.0f, -3.0f)) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), "Platform_1");
	m_pEntityMngr->UsePhysicsSolver();
}

void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}

void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	float tubeHeight = 50.0f;
	// Draw a Tube to Represent the Play Area
	m_pMeshMngr->AddTubeToRenderList(glm::scale(IDENTITY_M4, vector3(50.0f, tubeHeight, 50.f)), C_RED, 2);

	// Draw the Spike Bed to Represent the Death Area
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			matrix4 modelMatrix = glm::scale(IDENTITY_M4, vector3(2.0f));
			m_pMeshMngr->AddConeToRenderList(glm::translate(modelMatrix, vector3(-10.0f + (1.0f * j), -tubeHeight / 4 + 1.0f, -10.0f + (1.0f * i))), C_GRAY);
		}
	}

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