#pragma once
#include "BaseState.h"
#include "sfwdraw.h"
class Splash : public BaseState
{
	int font;
	float timer;
public:
	//called on startup
	void init(int a_font) { font = a_font; }
	//call play function
	void play() { timer = 5.f; }

	// called on update
	void draw()
	{
		char buffer[64];
		//sprintf_s(buffer, "Press Enter to start the game! \n %f", timer);
		sfw::drawString(font, buffer, 100, 100, 20, 20);
		sfw::drawLine(100, 80, 100 + 500 * (timer / 5.f), 80);
	}
	//works like update
	void step() { timer -= sfw::getDeltaTime(); }

	APP_STATE next()
	{
		if (timer < 0 || (sfw::getKey(KEY_ENTER)))
			return TERMINATE;
		return SPLASH;
	}
};