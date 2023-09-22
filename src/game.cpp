#include "../h/game.hpp"

#ifdef NONES
#include <cstdlib>
#endif
namespace Game
{
	bool running = false;
	uint16_t time = 0;

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
		Arena::tick();
	}

	void update()
	{
		if (!running) return;
		Arena::update();
		if (time >= 72 * 60)
		{
			//stop();
			//MainMenu::start();
			Arena::start();
		}
	}
}