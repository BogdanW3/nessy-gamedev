#include "../h/game.hpp"

#ifdef NONES
#include <cstdlib>
#endif
namespace Game
{
	bool running = false;
	uint16_t time = 0;
#ifdef NONES
	Arena *arena = nullptr;
#else
	Arena * const arena = (Arena * const)0x1000;
#endif

	void start()
	{
		running = true;
		time = 0;
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
	}

	void update()
	{
		if (!running) return;
		arena->update();
		if (time >= 72 * 60)
		{
			//stop();
			//MainMenu::start();
			arena->start();
		}
	}
}