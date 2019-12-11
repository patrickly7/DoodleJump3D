#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>

#include "MyEntity.h"
#include "Definitions.h"

using namespace Simplex;

class Player : public MyEntity
{
private:
    vector3 jumpForce;
	vector3 inputForce;
	vector3 otherForce;
    vector3 centerPosition;
    float movementFactor;
    Movement_Key direction;
    vector3 dir;

    void Update();
    void Jump();
public:
	/*
	TODO
	*/
    Player(String ID, vector3 centerPos);

	/*
	TODO
	*/
    void Move(Movement_Key k, float ellapsed);
};
#endif
