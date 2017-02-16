#pragma once
#include "BaseState.h"
#include "Factory.h"
#include "Base.h"

using namespace base;
class playerMotor
{


	vec2 Accelerate(vec2 acceldir, vec2 preVelocity, float accelerate, float max_velocity, float dt)
	{
		float projVel = dot(preVelocity, acceldir);
		float accelVel = accelerate * dt;

		if (projVel + accelVel > max_velocity)
			accelVel = max_velocity - projVel;

		return preVelocity + acceldir * accelVel;
	};

	// keeps from going over max velocity

	vec2 MoveGround(vec2 acceldir, vec2 prevVolocity, float dt)
	{
		float speed = prevVolocity.magnitude();
		if (speed != 0) // To avoid divide by zero errors
		{
			float drop = speed * friction * dt;
			prevVolocity *= tmax((speed - drop), 0) / speed;// Scale the velocity based on friction.
		}

		return Accelerate(acceldir, prevVolocity, ground_accelerate, max_velocity_ground,dt);
	}

	vec2 MoveAir(vec2 acceldir, vec2 prevVelocity, float dt)
	{
		return Accelerate(acceldir, prevVelocity, Air_accelerate, max_velocity_ground,dt);
	}

	
public:
	float maxg = 150;
	float speed = 5;
	float drop = 0;
	float friction = 7;
	float ground_accelerate = 1000, max_velocity_ground = maxg;
	float Air_accelerate= 150, max_velocity_Air = 30;

	
	vec2 accelDir = vec2{ 0,0 };

	playerMotor() : accelDir(0, 0) {}

	void update(base::Rigidbody *rb, float dt)
	{
		accelDir = accelDir.magnitude() > 0 ? accelDir.normal() : vec2{0,0};
		rb->velocity = rb->isGrounded ? MoveGround(accelDir, rb->velocity, dt) : MoveAir(accelDir, rb->velocity, dt);// : MoveAir(accelDir, rb->velocity, dt);

		accelDir = vec2{ 0,0 };

		debugPrint(rb);

		//if (ground_accelerate = maxg)
		//{
		//	ground_accelerate--;
		//}
	}

	void debugPrint(base::Rigidbody *rb)
	{
		std::cout << "player grounded:" << (rb->isGrounded ? "true" : "false") << std::endl;
	}
};