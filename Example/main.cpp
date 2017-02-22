
#include "sfwdraw.h"
#include "GameState.h"
#include "Option.h"
#include "Instructions.h"
#include "Victory.h"
#include "BaseState.h"

#include <cassert>

/*
	The main function should be used for application state management.
	Currently, only one state is implemented here, you'll need to add additional
	and get them to behave properly.
*/
void main()
{
	sfw::initContext();
	
	unsigned font = sfw::loadTextureMap("../res/fontmap.png", 16, 16);

	GameState gs;
	Option option;
	Instructions instruct;
	Victory victory;

	option.init(font);
	instruct.init(font);
	option.init(font);
	victory.init(font);

	gs.init();
	gs.play();


	APP_STATE state = ENTER_OPTIONS;
	bool quit = false;



	while (sfw::stepContext() && !quit)
	{
		switch (state)
		{
		case ENTER_OPTIONS:
			option.play();

		case OPTION:
			option.step();
			option.draw();
			state = option.next();
			break;

		//case ENTER_INSTRUCTIONS:
		//	instruct.play();
	//	case INSTRUCTIONS:
			//sfw::drawTexture(r, 0, 600, 800, 600, 0, false, 0, GREEN);

		//	instruct.draw();

		//	instruct.step();
		//	state = instruct.next();
		//	break;
		case ENTER_GAME:
			//gs.play();
			gs.play(); // Should be called each time the state is transitioned into

		case GAME:
			gs.draw();
			gs.step();

			state =gs.next();
			break;

		case ENTER_SPLASH:
			victory.play();

		case VICTORY:
			gs.draw();
			gs.step();

			victory.draw();
			victory.step();
			state = victory.next();
			break;
		case TERMINATE: quit = true;
		}
				

		//gs.next(); Determine the ID of the next state to transition to.
	}

	//gs.stop(); // should be called each time the state is transitioned out of

	//gs.term(); // called once


	sfw::termContext();

}