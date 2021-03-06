#pragma once

#include "Base.h"

#include "playerMotor.h"


class PlayerController
{

	
public:
	float speed = 10, turnSpeed = 1;
	
	//float dt = sfw::getDeltaTime();

	float shotTimer = 0.0f;

	bool pre, cur;
	bool ButtonD = false;
	bool shotgunRequest = false;
	bool startStimer = false;

	unsigned short UP;
	unsigned short DOWN;
	unsigned short LEFT;
	unsigned short RIGHT;
	unsigned short Fire;
	int playerID;

	void poll(base::Transform *T, base::Rigidbody *rb, playerMotor *pm, float dt)
	{
		pre = cur;
		cur = sfw::getKey(Fire);


		if (sfw::getKey(LEFT))
		{
			
			pm->accelDir.x = -1;
			if (rb->velocity.x >= 0)
			{
				rb->velocity.x = -10;
			}
		}
		

		if (sfw::getKey(RIGHT))
		{
			

			pm->accelDir.x = 1;
			if (rb->velocity.x <= 0)
			{
				rb->velocity.x = 10;
			}
		}
		if (sfw::getKey(DOWN))
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
			if (sfw::getKey(UP))
			{		

				rb->addImpulse(base::vec2{ 0,800 });
				pm->accelDir.y = -1 ;


				//rb->addImpulse(base::vec2{ 0, 0 });
				rb->isGrounded = false;
			}

	
		

		}

		///shooting function
		

				if (!pre && cur && shotTimer <= 0.0f)// is key is pressed
				{

				
						shotgunRequest = true;
						shotTimer = 1.0f;


				}

				if (pre && !cur) //the key was released 
				{

					shotgunRequest = false;

				}

				if (pre && cur)// key is being held down
				{
					shotTimer -= dt;
					shotgunRequest = false;
					
					if (shotTimer <= 0.0f)
					{
						shotTimer = 2.0f;
						shotgunRequest = true;
					}

				}
				if (!pre && !cur)// key is up and no touchy
				{
					shotTimer -= dt;
				}		
		
		
	}

};