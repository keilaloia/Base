#pragma once

#include "Base.h"

#include "playerMotor.h"


class PlayerController
{
	
public:
	float speed = 10, turnSpeed = 1;
	
	//float dt = sfw::getDeltaTime();

	float shotTimer = 0.0f;

	bool shotRequest = false;

	void poll(base::Transform *T, base::Rigidbody *rb, playerMotor *pm, float dt)
	{
		/*if (sfw::getKey('W'))
			rb->addForce(T->getGlobalUp() * speed);*/

		if (sfw::getKey('A'))
			pm->accelDir.x = -1;

		if (sfw::getKey('D'))
			pm->accelDir.x = 1;

		if (sfw::getKey('S'))
			pm->accelDir.y = -1;
			
		// jump
		if (rb->isGrounded == true)
		{
			if (sfw::getKey('W'))
			{
				rb->addImpulse(base::vec2{ 0,70 });
				pm->accelDir.y = -1;
				if (rb->velocity.y >= 70)
				{
					rb->velocity.y = 70;
				}
				
				//rb->addImpulse(base::vec2{ 0, 0 });
				rb->isGrounded = false;
			}
		}
		

	/*	shotTimer -= dt;
		if (sfw::getKey(' ') && shotTimer < 0)
		{
			shotRequest = true;
			shotTimer = 0.86f;
		}
		else shotRequest = false;*/
	}

};