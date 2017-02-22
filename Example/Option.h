#pragma once
#include "BaseState.h"

class Option : public BaseState
{
	int font;
	float timer;
	int select;
public:
	void init(int a_font) { font = a_font; }
	void play() { select = 0; timer = 1.f; }
	void draw()
	{
		sfw::drawString(font, "Start Game!", 100, 120, 16, 16, 0, 0, select == 0 ? MAGENTA : WHITE);
		sfw::drawString(font, "Not cool enough to play this game", 100, 100, 16, 16, 0, 0, select == 1 ? MAGENTA : WHITE);

		sfw::drawLine(100, 80, 100 + 500 * (timer / 5.f), 80);
	}
	void step()
	{
		timer -= sfw::getDeltaTime();
		if (timer < 0)
		{
			timer = 2.f;
			select = 1 - select; //flips seletion between 0 and 1
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
		return OPTION;

	}
};