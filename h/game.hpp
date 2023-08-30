#ifndef GAME_HPP
#define GAME_HPP


#include "../lib/stdint.hpp"
#include "arena.hpp"

namespace Game {
	// when the game starts from the main menu
	void start();
	// when the game stops and we go to the scorescreen
	void stop();
	// when the timer ticks
	void tick();
	// all the time while the game is running, checks if tick caused changes
	void update();
	extern bool running;
	extern uint8_t time;
	extern Arena* arena;

};

#endif // !GAME_HPP