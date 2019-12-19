#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "MyEntity.h"
#include "Definitions.h"
#include "MyEntityManager.h"

#include <cstdlib>
#include <ctime>
using namespace Simplex;

static const float SPEED = 2.0f;

class Platform : public MyEntity 
{
private:
    MyEntityManager* entMan;
public:
    String ID;
	Platform(vector3 startPos, String ID);
	void Despawn();
	void Move(float delta);
};

#endif //_PLATFORM_H