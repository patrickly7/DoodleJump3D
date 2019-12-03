#ifndef _PLAYER_H
#define _PLAYER_H

#include "MyEntity.h"
#include "Definitions.h"
using namespace Simplex;

class Player : public MyEntity
{
	vector3 jumpForce;
	void Update();
	void Jump();
	vector3 inputForce;
	vector3 otherForce;

public:
	/*
	TODO
	*/
    Player(String ID);

	/*
	TODO
	*/
    void Move();
};

#endif
