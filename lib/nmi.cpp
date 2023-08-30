#include "nmi.hpp"

#include "kb.hpp"
#include "../h/mainmenu.hpp"
#include "../h/game.hpp"

// happens at around 72Hz, equal to the display refresh rate for our NES
extern "C" __attribute__((interrupt)) void nmi()
{
	KB::tick();
	MainMenu::tick();
	Game::tick();
}