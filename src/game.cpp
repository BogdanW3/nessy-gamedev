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
#ifdef NONES
		if (arena == nullptr) arena = (Arena*)malloc(800*600*32);
#endif
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