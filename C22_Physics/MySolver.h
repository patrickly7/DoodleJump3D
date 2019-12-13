/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/07
Contributors: Scribble Hop
Date: 2019/11
----------------------------------------------*/
#ifndef __MYSOLVER_H_
#define __MYSOLVER_H_

#include "MyRigidBody.h"

namespace Simplex
{
	class MySolver
	{
		vector3 m_v3Acceleration = ZERO_V3; // Acceleration of the MySolver
		vector3 m_v3Position = ZERO_V3; // Position of the MySolver
		vector3 m_v3Size = vector3(1.0f); // Size of the MySolver
		vector3 m_v3Velocity = ZERO_V3; // Velocity of the MySolver
		float m_fMass = 1.0f; // Mass of the solver

		const vector3 m_v3Gravity = vector3(0.0f, -0.020f, 0.0f); // Force of Gravity
		const float m_friction = 0.1f; // Coefficient of Friction
		const float m_minVelocity = 0.005f; // Lower bound for Velocity
		const float m_maxVelocity = 5.0f; // Upper bound for Velocity

		bool m_onAir = false; // Check if Object is in the Air
		bool m_staticObject = true; // Check if this Object is Meant to Move

	public:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT: object instance
		*/
		MySolver(void);

		/*
		USAGE: Copy Constructor
		ARGUMENTS: object to copy
		OUTPUT: object instance
		*/
		MySolver(MySolver const& other);

		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS: object to copy
		OUTPUT: this instance
		*/
		MySolver& operator=(MySolver const& other);

		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~MySolver(void);

		/*
		USAGE: Content Swap
		ARGUMENTS: object to swap content with
		OUTPUT: ---
		*/
		void Swap(MySolver& other);

		/*
		USAGE: Sets the position of the solver
		ARGUMENTS: vector3 a_v3Position -> position to set
		OUTPUT: ---
		*/
		void SetPosition(vector3 a_v3Position);
		/*
		USAGE: Gets the position of the solver
		ARGUMENTS: ---
		OUTPUT: position of the solver
		*/
		vector3 GetPosition(void);

		/*
		USAGE: Sets the Size of the solver
		ARGUMENTS: vector3 a_v3Size -> position to set
		OUTPUT: ---
		*/
		void SetSize(vector3 a_v3Size);
		/*
		USAGE: Gets the size of the solver
		ARGUMENTS: ---
		OUTPUT: size of the solver
		*/
		vector3 GetSize(void);

		/*
		USAGE: Sets the velocity of the solver
		ARGUMENTS: vector3 a_v3Velocity -> velocity to set
		OUTPUT: ---
		*/
		void SetVelocity(vector3 a_v3Velocity);
		/*
		USAGE: Gets the velocity of the solver
		ARGUMENTS: ---
		OUTPUT: velocity of the solver
		*/
		vector3 GetVelocity(void);

		/*
		USAGE: Sets the mass of the solver
		ARGUMENTS: float a_fMass -> mass to set
		OUTPUT: ---
		*/
		void SetMass(float a_fMass);

		/*
		USAGE: Gets mass of the solver
		ARGUMENTS: ---
		OUTPUT: mass of the object
		*/
		float GetMass(void);

		/*
		USAGE: Sets the current state of the object being in the air
		ARGUMENTS: float a_isOnAir -> new state to set
		OUTPUT: ---
		*/
		void SetOnAir(bool a_isOnAir);

		/*
		USAGE: Gets if the object is currently mid-air
		ARGUMENTS: ---
		OUTPUT: True if in the air, otherwise False
		*/
		bool GetOnAir(void);

		/*
		USAGE: Applies friction to the movement
		ARGUMENTS: float a_fFriction = 0.1f -> friction to apply negative friction gets minimized to 0.01f
		OUTPUT: ---
		*/
		void ApplyFriction(float a_fFriction = 0.1f);

		/*
		USAGE: Applies a force to the solver
		ARGUMENTS: vector3 a_v3Force -> Force to apply
		OUTPUT: ---
		*/
		void ApplyForce(vector3 a_v3Force);

		/*
		USAGE: Updates the MySolver
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Update(void);

		/*
		USAGE: Resolve the collision between the player and a platform
		ARGUMENTS: MySolver* a_pOther -> other solver to resolve collision with
		OUTPUT: ---
		*/
		void ResolvePlayerToPlatform(MySolver* a_pPlatform);

		/*
		USAGE: Resolve the collision between the player and the spike bed
		ARGUMENTS: MySolver* a_pOther -> other solver to resolve collision with
		OUTPUT: ---
		*/
		void ResolvePlayerToSpikeBed(MySolver* a_pSpikeBed);

		/*
		USAGE: Resolve the collision between the player and a wall
		ARGUMENTS: MySolver* a_pOther -> other solver to resolve collision with
		OUTPUT: ---
		*/
		void ResolvePlayerToWall(MySolver* a_pWall);

		/*
		USAGE: Resolve the collision between a platform and the spike bed
		ARGUMENTS: MySolver* a_pOther -> other solver to resolve collision with
		OUTPUT: ---
		*/
		void ResolvePlatformToSpikeBed(MySolver* a_pSpikeBed);

	private:
		/*
		Usage: Deallocates member fields
		Arguments: ---
		Output: ---
		*/
		void Release(void);

		/*
		Usage: Allocates member fields
		Arguments: ---
		Output: ---
		*/
		void Init(void);
	};
}

#endif //__SOLVER_H_