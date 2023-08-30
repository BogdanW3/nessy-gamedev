#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "../lib/stdint.hpp"

namespace MainMenu {
	// at the very beginning, and after scoresreen
	void start();
	// when the game starts
	void stop();
	// when the timer ticks
	void tick();
	// all the time while the main menu is running, checks if tick caused changes
	void update();
	extern bool running;

	enum Item {
		ONE_V_ONE,
		TWO_V_TWO,
		FFA
	};
	extern Item activeItem;

	extern bool dirty;
};

#endif // !MAINMENU_HPP