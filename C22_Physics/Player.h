#ifndef _PLAYER_H
#define _PLAYER_H

#include <map>

#include "MyEntity.h"
#include "Definitions.h"

using namespace Simplex;
using std::map;

class Player : public MyEntity
{
private:
    vector3 jumpForce;
	vector3 inputForce;
	vector3 otherForce;
    vector3 centerPosition;
    float movementFactor;
    float cylinderRotation; //in radians
    float currentAngle; //in radians
    Movement_Key direction;
    vector3 dir;
    map<Movement_Key, float> angleRotations;


    void rotateTo(Movement_Key k);
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
