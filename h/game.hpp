#ifndef GAME_HPP
#define GAME_HPP

#ifndef NONES
#include "../lib/stdint.hpp"
#else
#include <stdint.h>
#endif
#include "arena.hpp"

namespace Game
{
	// when the game starts from the main menu
	void start();
	// when the game stops and we go back to the main menu
	void stop();
	// when the timer ticks
	void tick();
	// all the time while the game is running, checks if tick caused changes
	void update();
	extern bool running;
	extern uint16_t time;
	extern Arena * const arena;

};

#endif // !GAME_HPP