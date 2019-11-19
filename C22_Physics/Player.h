#ifndef _PLAYER_H
#define _PLAYER_H
#include "MyEntity.h"
#include "Definitions.h"
using namespace Simplex;
class Player : MyEntity
{
public:
    Player(String ID);

    void Move();
    void Jump();
private:

    void Update();

    vector3 gravityForce;
    vector3 inputForce;
    vector3 otherForce;
};

#endif
