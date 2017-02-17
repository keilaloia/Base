#pragma once

#include "Base.h"

#include "playerMotor.h"


class PlayerController
{

	
public:
	float speed = 10, turnSpeed = 1;
	
	//float dt = sfw::getDeltaTime();

	float shotTimer = 0.0f;

	bool ButtonD = false;
	bool shotgunRequest = false;

	void poll(base::Transform *T, base::Rigidbody *rb, playerMotor *pm, float dt)
	{
		/*if (sfw::getKey('W'))
			rb->addForce(T->getGlobalUp() * speed);*/
	
		if (sfw::getKey('A'))
		{
			
			pm->accelDir.x = -1;
			if (rb->velocity.x >= 0)
			{
				rb->velocity.x = -10;
			}
		}
		

		if (sfw::getKey('D'))
		{
			

			pm->accelDir.x = 1;
			if (rb->velocity.x <= 0)
			{
				rb->velocity.x = 10;
			}
		}
		if (sfw::getKey('S'))
		{
			pm->accelDir.y = -1;

			if (rb->velocity.y >= 0)
			{
				rb->velocity.y = -10;
			}
		}
			
		// jump
		if (rb->isGrounded == true)
		{
			rb->acceleration.y = 0;
			rb->velocity.y = 0;
			if (sfw::getKey('W'))
			{
			
				//b->velocity.y = 100;

				rb->addImpulse(base::vec2{ 0,800 });
				pm->accelDir.y = -1 ;


				//rb->addImpulse(base::vec2{ 0, 0 });
				rb->isGrounded = false;
			}
		}
		

		shotTimer -= dt;
		if (sfw::getKey('F') && shotTimer < 0)
		{
			shotgunRequest = true;
			shotTimer = 0.86f;
		}
		else shotgunRequest = false;
	}

};