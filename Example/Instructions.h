#pragma once
#include "GameState.h"
class Instructions : public BaseState
{
	float timer;
	int font;
public:
	void init(int a_font) { font = a_font;  }
	void play() { timer = 7.0f; }
	void draw()
	{

		char buffer[64];
		sprintf_s(buffer, "Player 1:\n Jump up: W \n Move down: S \n Move Left: A \n Move Right: D \n Fire: F", 80);
		sfw::drawString(font, buffer, 100, 525, 17, 17);

		sprintf_s(buffer, "Player 2:\n Move up: Up Arrow \n Move down: Down Arrow", 80);
		sfw::drawString(font, buffer, 425, 525, 17, 17);

		sprintf_s(buffer, "Press Space to begin", 80);
		sfw::drawString(font, buffer, 250, 325, 17, 17);

		sfw::drawString(font, " game is starting in ", 100, 120, 16, 16, 0, 0, CYAN);
		sfw::drawLine(100, 80, 100 + 500 * (timer / 7.f), 80);
	}
	void step() { timer -= sfw::getDeltaTime(); }
	APP_STATE next() const
	{
		if ((timer < 0) || sfw::getKey(' '))
		{
			return ENTER_GAME;
		}
		return INSTRUCTIONS;
	}
};