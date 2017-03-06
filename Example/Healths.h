#pragma once

#include "Entity.h"

class pHealth
{
public:
	int phealth = 100;

	void TakeDamage(Sprite *sp)
	{
		phealth -= 10;

		std::cout << "hit" << std::endl;
	}

	bool isDead(Sprite *sp)
	{
		if (phealth <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	
};