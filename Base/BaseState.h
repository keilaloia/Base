#pragma once

enum APP_STATE
{
	TERMINATE,
	ENTER_SPLASH,
	SPLASH,
	ENTER_OPTIONS,
	OPTION,
	ENTER_GAME,
	GAME,
	ENTER_VICTORY,
	VICTORY,
	ENTER_INSTRUCTIONS,
	INSTRUCTIONS
};

class BaseState
{
public:
	virtual void init() {} // called once, on application startup.
	virtual void term() {} // called once, on shutdown.

	virtual void play() {} // called on enter transition
	virtual void stop() {} // called on exit transition

	virtual APP_STATE next() const = 0; // called every frame
	
	virtual void step() {} // called every frame
	virtual void draw() {} // called every frame
};