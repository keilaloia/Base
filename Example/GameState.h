#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"
#include "playerMotor.h"


/*
	The gamestate represents a discrete container of all that is 
	necessary to drive the game experience.

	A factory object is used to manage the creation and deletion of
	objects in the simulation.

	The game state updates the entities within the factory using
	a series of 'systems.'
*/

class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_ship,spr_shipr, spr_bullet, spr_roid, spr_font;
	ObjectPool<Entity>::iterator currentCamera;

protected:// check for no collision
	virtual base::collision checkCollision(const Transform &T, const Collider &C)
	{
		for (auto it = factory.begin(); it != factory.end(); it++) // for each entity
		{
			// if this entity is collidable...
			if (it->transform && it->collider && !it->controller)
			{
				auto &rT = *it->transform;
				auto &rC = *it->collider;
				// test their bounding boxes
				if (base::BoundsTest(&T, &C, &it->transform, &it->collider))
				{
					// if true, get the penetration and normal from the convex hulls
					auto cd = base::ColliderTest(&T, &C, &it->transform, &it->collider);

					return cd;
				}

			}
		}
		// no collision was found
		return { -1 };
	}
	
public:
	virtual void init()
	{
		spr_bullet = sfw::loadTextureMap("../res/bullet.png");
		spr_space = sfw::loadTextureMap("../res/space.jpg");
		spr_ship = sfw::loadTextureMap("../res/ship.png");
		spr_roid = sfw::loadTextureMap("../res/rock.png");
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
		spr_shipr = sfw::loadTextureMap("../res/shipr.png");


	}

	virtual void play()
	{
		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });

		// call some spawning functions!
		//factory.spawnStaticImage(spr_space, 0, 0, 800, 600);

		//factory.spawnPlayer(spr_ship, spr_font, vec2{ 200,-230 });
		//factory.spawnAsteroid(spr_roid);

		factory.spawnPlayer(spr_ship, spr_font, vec2{ -200,100 });


		/* base */	factory.spawnPlatform(spr_ship, vec2{ 0,-350 }, { -400,0 }, { 400, 0 }, { 400,100 }, { -400, 100 });
		/* left */	factory.spawnPlatform(spr_ship, vec2{ -150,-170 }, { 50,0 }, { -100, 0 }, { -100,10 },{  50, 10 });
		/* right */	factory.spawnPlatform(spr_ship, vec2{ 200,-170 }, { 50,0 }, { -100, 0 }, { -100,10 }, { 50, 10 });
		/* middle */factory.spawnPlatform(spr_ship, vec2{ 30,-65 }, { 50,0 }, { -100, 0 }, { -100,10 }, { 50, 10 });


	}

	virtual void stop()
	{

	}

	// should return what state we're going to.
	// REMEMBER TO HAVE ENTRY AND STAY states for each application state!
	virtual size_t next() const { return 0; }

	// update loop, where 'systems' exist
	virtual void step()
	{
		float dt = sfw::getDeltaTime();
		dt = dt > 5.0f ? 5.0f : dt;

		// maybe spawn some asteroids here.
		for(auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

			

			// controller update
			if (e.transform && e.rigidbody && e.controller && e.playerm)
			{

				

				// ground check
				float checkRad = 5.0f;
				// check feet if colliding
				Transform controllerFeet;

				vec2 newPos;
				auto box = e.collider->getGlobalHull(&e.transform);
				newPos.y = box.min(vec2::up());
				newPos.x = e.transform->getGlobalPosition().x;

				controllerFeet.setGlobalPosition(newPos);

				//std::cout << controllerFeet.getGlobalPosition().x << "," << controllerFeet.getGlobalPosition().y << std::endl;
				
				Collider controllerColl = Collider(checkRad);

				auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

				controllerColl.draw(&controllerFeet, cam);

				// check to see if colliding if it is is grounded is true
				auto cd = checkCollision(controllerFeet, controllerColl);
				e.rigidbody->isGrounded = cd.result();
				
				// update controller
				e.controller->poll(&e.transform, &e.rigidbody, &e.playerm, dt);
				if (e.controller->shotgunRequest) // controller requested a bullet fire
				{
					for (int i = 0; i < 5; i++)
					{
						factory.spawnBullet(spr_bullet, e.transform->getGlobalPosition() + e.transform->getGlobalUp() * 48,
							vec2{ 32,32 }, e.transform->getGlobalAngle(), 200, 1);
					}
					
				}
				std::cout << " " << e.rigidbody->velocity.y << std::endl;

			}

			if (e.playerm && e.rigidbody)
				e.playerm->update(&e.rigidbody, dt);
			// lifetime decay update

			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}
		}


		// Physics system!
		// You'll want to extend this with custom collision responses

		// it is iterator on
		// bit is other iterator your checkking collision with
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for(auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				// if they aren't the same and they both have collidable bits...
				{
					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
						// if there was a collision,
						if (cd.result())
						{
							// condition for dynamic resolution
							if (it->rigidbody && bit->rigidbody)
								base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);
							
							// condition for static resolution
							else if (it->rigidbody && !bit->rigidbody)
							{
								auto& e = *it;
							

								base::StaticResolution(cd, &it->transform, &it->rigidbody, 1, it->rigidbody->staticBouncer);
							
							}

						}
						

					}

				}

	}

	virtual void draw()	
	{
		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, cam);

		// draw text
		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);


#ifdef _DEBUG
		for each(auto &e in factory)
			if (e.transform)
			{
				//std::cout << e.transform->getGlobalPosition().x << "," << e.transform->getGlobalPosition().y << std::endl;
				e.transform->draw(cam);
			}

		//std::cout << std::endl;

		for each(auto &e in factory)
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.rigidbody)
				e.rigidbody->draw(&e.transform, cam);
#endif
	}
};