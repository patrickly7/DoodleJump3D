#include "Platform.h"

Platform::Platform(vector3 startPos, String ID)
: MyEntity("Minecraft\\Cube.obj", ID)
{
	//start position fed into constructor, x and z coords should be random floats
	startPosition = startPos;
	endPosition = vector3(startPosition.x, startPosition.y - 90.0f, startPosition.z);
	//offScreenPosition = vector3(-20.0f, -20.0f, -20.0f);  // DEPRECATE
	//active = true;  // DEPRECATE
	
}

//void Platform::Spawn()  // DEPRECATE
//{
//	//at start position	//resets x and z of startPosition vector with new random values every 5 seconds (whenever platforms hit bottom)
//	//active = true;
//
//	//Move();
//}

void Platform::Despawn()
{
	//at end position or when hitting spikes
	//active = false;

	MyEntityManager::ReleaseInstance();
}

void Platform::Move(SystemSingleton* a_pSystem, MyEntityManager* a_pEntityMngr, int a_index)
{
	//behavior I want to emulate: startPosition (lerps to) endPosition (blips to) offScreenPosition (waits x seconds, blips to) startPosition  // DEPRECATE

	// Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = a_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += a_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	// Calculate percentage to LERP by
	float fTimeBtwnStops = 5.0f;
	float fLerpPercentage = MapValue(fTimer, 0.0f, fTimeBtwnStops, 0.0f, 1.0f);		/*	Converts the ratio of [current elapsed time(fTimer) : fTimeBtwnStops]
																						into a percentage value, scaled between 0.0f and 1.0f. */
	// Use LERP percentage to calculate the current position
	vector3 v3CurrentPos = glm::lerp(startPosition, endPosition, fLerpPercentage);

	// Reset timer and percentage when sprint ends (percentage == 100%)
	if (fLerpPercentage >= 1.0f)
	{
		//sprintCounter++;							// increment sprintCounter to set start of next sprint
		//sprintCounter %= m_stopsList.size();		// if this was the last sprint, reset the sprint number to allow looping
		fTimer = a_pSystem->GetDeltaTime(uClock);	// reset timer to allow LERPing for next sprint

		////Despawn();

		ResetStartPosition();	//WORKS BUT ONLY ON ONE PLATFORM FOR SOME REASON  // DEPRECATE
	}

	a_pEntityMngr->SetModelMatrix(glm::translate(v3CurrentPos) * glm::scale(vector3(5.0f, 0.1f, 5.0f)), "Platform_TEST_" + std::to_string(a_index));

}

void Platform::ResetStartPosition() // DEPRECATE
{
	startPosition = vector3(
		(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 15.0f - 7.5f,
		70.0f,
		(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 15.0f - 7.5f);

	endPosition = vector3(startPosition.x, startPosition.y - 10.0f, startPosition.z);
}
