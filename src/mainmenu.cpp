#include "../h/mainmenu.hpp"

#include "../h/arena.hpp"
#include "../h/1v1_arena.hpp"
#include "../h/2v2_arena.hpp"
#include "../h/ffa_arena.hpp"
#include "../h/game.hpp"

#include "../lib/kb.hpp"
#include "../lib/gpu.hpp"

namespace MainMenu {
	bool running = false;
	Item activeItem = MainMenu::ONE_V_ONE;
	bool dirty = false;

	void start()
	{
		running = true;
		dirty = true;
		Colour black(0, 0, 0);
		draw_rect(0, 0, 800, 600, black);
	}

	void stop()
	{
		running = false;
	}

	void tick()
	{
		if (!running) return;

		KB::PlayerKBData* P1DATA = KB::PLAYER_KB_DATA[0];

		if (P1DATA->UP) {
			if (activeItem == ONE_V_ONE) activeItem = FFA;
			else activeItem = (Item)((int)activeItem - 1);
			dirty = true;
		}
		if (P1DATA->DOWN) {
			if (activeItem == FFA) activeItem = ONE_V_ONE;
			else activeItem = (Item)((int)activeItem + 1);
			dirty = true;
		}
		if (P1DATA->START) {
			stop();
			switch (activeItem)
			{
			case ONE_V_ONE:
				((One_V_One_Arena*)Game::arena)->start(One_V_One_Arena::MEDIUM);
				break;
			case TWO_V_TWO:
				((Two_V_Two_Arena*)Game::arena)->start(Two_V_Two_Arena::MEDIUM);
				break;
			case FFA:
				((FFA_Arena*)Game::arena)->start(FFA_Arena::LARGE);
				break;
			}
			Game::start();
		}
	}

	void update()
	{
		if (!dirty) return;
		dirty = false;

		// draw the 3 menu tiles (red for selected, grey for unselected)
		Colour red(255, 0, 0);
		Colour grey(128, 128, 128);
		draw_rect(200, 100, 600, 150, activeItem == ONE_V_ONE ? red : grey);
		draw_rect(200, 200, 600, 250, activeItem == TWO_V_TWO ? red : grey);
		draw_rect(200, 300, 600, 350, activeItem == FFA ? red : grey);
	}
} // namespace MainMenu