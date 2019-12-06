#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "MyEntity.h"
#include "Definitions.h"
using namespace Simplex;

class Platform : MyEntity 
{

public:
	Platform(String ID);
	void Spawn();
	void Despawn();
	void Move();

};

#endif //_PLATFORM_H