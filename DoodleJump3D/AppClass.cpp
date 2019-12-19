#include "AppClass.h"
using namespace Simplex;

constexpr float cylinderHeight = 70.0f;
constexpr float cylinderRadius = 40.0f;

void Application::InitVariables(void)
{
    // Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 5.0f, 25.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)
	m_pEntityMngr = MyEntityManager::GetInstance();


    //m_pEntityMngr = MyEntityManager::GetInstance();	//duplicate
  
    currentPlayer = new Player("Player00", vector3(0.0f, 0.0f, 0.0f), cylinderRadius, 7.0f);
    currentPlayer->SetPosition(vector3(10.0f, 0.0f, 0.0f));
    m_pEntityMngr->AddEntity((MyEntity*)currentPlayer);
    currentPlayerIndex = m_pEntityMngr->GetEntityIndex("Player00");

	// Death Bed (Index 1)
	auto spikeHeight = -cylinderHeight/2.0f;
	auto scaleByThis = cylinderRadius*2.0f;

	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Spike_Bed");
	auto spikeBedMatrix = glm::translate(IDENTITY_M4, vector3(-scaleByThis / 2, spikeHeight, -scaleByThis / 2));
	spikeBedMatrix = glm::scale(spikeBedMatrix, vector3(scaleByThis, 2.0f, scaleByThis));
	spikeBedMatrix = glm::translate(spikeBedMatrix, vector3(0.0f, 4.0f, 0.0f));
	m_pEntityMngr->SetModelMatrix(spikeBedMatrix, "Spike_Bed");
	m_pEntityMngr->UsePhysicsSolver();

	// Walls (Index 2 - 9)
	auto wallWidth = cylinderRadius;
	auto wallHeight = cylinderHeight;
    for (int index = 0; index < 8; index++) //starts at 0 because base case (0) also generates a used wall
    {
        m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Wall_" + std::to_string(index));

        auto scalingMatrix = glm::scale(vector3(wallWidth, 0.5f, wallHeight));
        auto rotationMatrix = glm::rotate(IDENTITY_M4, glm::radians(90.0f), vector3(1.0f, 0.0f, 0.0f));
        rotationMatrix *= glm::rotate(glm::radians(45.0f * index), vector3(0.0f, 0.0f, 1.0f));

        // Position the Walls into a Cylindrical-Like Shape
        auto translationMatrix = glm::translate(vector3(-wallWidth / 2, wallHeight / 2, -wallWidth)); // Back
        if (index == 1) // Back Right
            translationMatrix = glm::translate(vector3(wallWidth / 2, wallHeight / 2, -wallWidth));
        else if (index == 2) // Right
            translationMatrix = glm::translate(vector3(wallWidth, wallHeight / 2, -wallWidth / 2.0f));
        else if (index == 3) // Front Right
            translationMatrix = glm::translate(vector3(wallWidth, wallHeight / 2, wallWidth / 2.0f));
        else if (index == 4) // Front
            translationMatrix = glm::translate(vector3(wallWidth / 2, wallHeight / 2, wallWidth));
        else if (index == 5) // Front Left
            translationMatrix = glm::translate(vector3(-wallWidth / 2, wallHeight / 2, wallWidth));
        else if (index == 6) // Left
            translationMatrix = glm::translate(vector3(-wallWidth, wallHeight / 2, wallWidth / 2.0f));
        else if (index == 7) // Back Left
            translationMatrix = glm::translate(vector3(-wallWidth, wallHeight / 2, -wallWidth / 2.0f));

        auto wallMatrix = translationMatrix * rotationMatrix * scalingMatrix;

        m_pEntityMngr->SetModelMatrix(wallMatrix, "Wall_" + std::to_string(index));
    }

	// Add Central Pillar (Index 10)
	m_pEntityMngr->AddEntity("Additional\\pillar.obj", "central_pillar");
	m_pEntityMngr->SetModelMatrix(glm::scale(IDENTITY_M4, vector3(3.0f, 10.0f, 3.0f)), "central_pillar");
	m_pEntityMngr->UsePhysicsSolver();

    // Platforms (Index 11+)
    m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_0");

    m_pEntityMngr->SetModelMatrix(glm::scale(glm::translate(IDENTITY_M4, vector3(0.0f, -20.0f, -15.0f)),
                                     vector3(50.0f, 0.1f, 50.0f)), "Platform_0");
    m_pEntityMngr->UsePhysicsSolver();

    m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Platform_1");
    m_pEntityMngr->SetModelMatrix(glm::translate(vector3(4.0f, 3.0f, -3.0f)) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), "Platform_1");
    m_pEntityMngr->UsePhysicsSolver();

    cameraController = new CameraController(*currentPlayer, vector3(0.0f, 3.0f, 0.0f), cylinderHeight, cylinderRadius);
}

void Application::Update(void)
{
    cameraController->Update();
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

    // Platforms movement logic
    for (int i = 0; i < platforms.size(); i++)
    {
        platforms[i]->Move(m_pSystem, m_pEntityMngr, i);
    }

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
	// Check if the Game has Ended (Player has hit Spikes)
	if (m_pEntityMngr->GetIsGameOver())
	{
		state = GameState::END_MENU;

		m_pEntityMngr->SetIsGameOver(false);

		auto initModelMatrix = glm::translate(IDENTITY_M4, vector3(10.0f, 0.0f, 0.0f));
		m_pEntityMngr->SetModelMatrix(initModelMatrix, currentPlayerIndex);

        return;
	}

	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	float tubeHeight = cylinderHeight;
	// Draw a Tube to Represent the Play Area
	m_pMeshMngr->AddTubeToRenderList(glm::scale(IDENTITY_M4, vector3(tubeHeight, tubeHeight, tubeHeight)), C_RED, 2);

	// Draw the Spike Bed to Represent the Death Area
    float sc = 4.0f;
    float hei = -cylinderHeight / (2.0f * sc) + 1.0f;
    vector3 starting(-cylinderRadius / sc, hei, -cylinderRadius / sc);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			matrix4 modelMatrix = glm::scale(IDENTITY_M4, vector3(sc));
			m_pMeshMngr->AddConeToRenderList(glm::translate(modelMatrix, starting + vector3((1.0f * j), 2.0f, (1.0f * i))), C_GRAY);
		}
	}

	// Only Update the Total Time Played While Not Paused/Over
	if (state == GameState::GAME)
	{	
		m_timePlaying += 0.01f;
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