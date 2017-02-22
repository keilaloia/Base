#pragma once
#include "sfwdraw.h"
#include "BaseState.h"
class Victory : public BaseState
{
	int font;
	float timer;
	int select;
public:
	//called on startup
	void init(int a_font)
	{ 
		font = a_font;
		select = 0;
	}
	//call play function
	void play() 
	{
		//int a_P1score, int a_P2score
		select = 0;
		//P1score = a_P1score;
		//P2score = a_P2score;
	}

	// called on update
	void draw()
	{
		char buffer[64];
	}
	//works like update
	void step() 
	{ 
		if (sfw::getKey('w') || sfw::getKey(KEY_UP))
		{
			select = 0;
		}
		if (sfw::getKey('s') || sfw::getKey(KEY_DOWN))
		{
			select = 1;
		}
	}

	APP_STATE next() const
	{


		if (sfw::getKey(KEY_ENTER))
		{
			if (select == 0)
				return ENTER_GAME;
			if (select == 1)
				return ENTER_SPLASH;
		}
	}
};