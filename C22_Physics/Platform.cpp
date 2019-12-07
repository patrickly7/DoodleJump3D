#include "Platform.h"

Platform::Platform(vector3 startPos, String ID)
: MyEntity("Minecraft\\Cube.obj", ID)
{
	//assign position vector, with randomized x and z coords. set y to 5.0f for now
	startPosition = startPos;
	endPosition = vector3(startPosition.x, startPosition.y - 10.0f, startPosition.z);
}

void Platform::Spawn() 
{
	//at start position
}

void Platform::Despawn() 
{
	//at end position or when hitting spikes
}

void Platform::Move(SystemSingleton* a_pSystem) 
{
	//// Get a timer
	//static float fTimer = 0;	//store the new timer
	//static uint uClock = a_pSystem->GenClock(); //generate a new clock for that timer
	//fTimer += a_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	///*
	////Stop list(s)
	//// i want platforms to lerp only across their y values. x and z will stay the same across the lerp.
	////// need to find access and save the platform's x and z positions, then lerp their y
	//// startPos = vector3(pos.x, pos.y, pos.z);
	//// endPos = vector3(pos.x, pos.y - 20.0f, pos.z);
	////it's really only one sprint per loop
	//*/



	////-------------------
	//// Set current sprint number, start, and end points
	//static uint sprintCounter = 0;	// Keeps track of number of the current "sprint", ie. the path between the current and next stops.
	//vector3 v3SprintStart = m_stopsList[sprintCounter];	// Sets starting point for the current sprint, using sprintCounter as an index for the stops vector.
	//vector3 v3SprintEnd = m_stopsList[(sprintCounter + 1) % m_stopsList.size()];	/*	Sets the next stop as the end of the current sprint.
	//																					% used to loop to first stop if at end of stops vector. */
	//																					// Calculate percentage to LERP by
	//float fTimeBtwnStops = 1.0f;
	//float fLerpPercentage = MapValue(fTimer, 0.0f, fTimeBtwnStops, 0.0f, 1.0f);		/*	Converts the ratio of [current elapsed time(fTimer) : fTimeBtwnStops]
	//																					into a percentage value, scaled between 0.0f and 1.0f. */
	//																					// Use LERP percentage to calculate the current position
	//vector3 v3CurrentPos = glm::lerp(v3SprintStart, v3SprintEnd, fLerpPercentage);

	//// Reset timer and percentage when sprint ends (percentage == 100%)
	//if (fLerpPercentage >= 1.0f)
	//{
	//	sprintCounter++;							// increment sprintCounter to set start of next sprint
	//	sprintCounter %= m_stopsList.size();		// if this was the last sprint, reset the sprint number to allow looping
	//	fTimer = a_pSystem->GetDeltaTime(uClock);	// reset timer to allow LERPing for next sprint
	//}
	////-------------------

	//matrix4 m4Model = glm::translate(v3CurrentPos);
	//m_pModel->SetModelMatrix(m4Model);
}