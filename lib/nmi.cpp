#include "nmi.hpp"

#include "kb.hpp"
#include "../h/game.hpp"

// happens at around 72Hz, equal to the display refresh rate for our NES
extern "C"
#ifndef NONES
__attribute__((interrupt))
#endif
void nmi()
{
	KB::tick();
	Game::tick();
}