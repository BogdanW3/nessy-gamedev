#include "../h/game.hpp"

#include "../h/mainmenu.hpp"

namespace Game
{
	bool running = false;
	uint16_t time = 0;
	Arena *arena = (Arena *)0x1000;

	void start()
	{
		running = true;
	}

	void stop()
	{
		running = false;
	}

	void tick()
	{
		if (!running) return;
		time++;
		arena->tick();
		if (time == 72 * 60)
		{
			stop();
			MainMenu::start();
		}
	}

	void update()
	{
		if (!running) return;
		arena->update();
	}
}