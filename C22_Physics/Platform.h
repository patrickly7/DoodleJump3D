#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "MyEntity.h"
#include "Definitions.h"
#include <cstdlib>
#include <ctime>
using namespace Simplex;

class Platform : MyEntity 
{
public:
	vector3 startPosition;
	vector3 endPosition;

	Platform(vector3 startPos, String ID);
	void Spawn();
	void Despawn();
	void Move(SystemSingleton* a_pSystem);
};

#endif //_PLATFORM_H