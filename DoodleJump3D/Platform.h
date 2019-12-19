#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "MyEntityManager.h"
#include "MyEntity.h"
#include "Definitions.h"
#include <cstdlib>
#include <ctime>
using namespace Simplex;

class Platform : MyEntity 
{
	//vector3 offScreenPosition;
	//bool active;
public:
	vector3 startPosition;
	vector3 endPosition;

	Platform(vector3 startPos, String ID);
	//void Spawn();
	void Despawn();
	void Move(SystemSingleton* a_pSystem, MyEntityManager* a_pEntityMngr, int a_index);
	void ResetStartPosition();
};

#endif //_PLATFORM_H