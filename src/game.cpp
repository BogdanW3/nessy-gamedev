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
		if (/*time >= 72 * 30 ||*/
			Arena::players[0].getScore() >= 100 ||
			Arena::players[1].getScore() >= 100)
		{
			//stop();
			//MainMenu::start();
			Arena::start();
			time = 0;
		}
		Arena::update();
	}
}