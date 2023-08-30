#include "../h/game.hpp"

namespace Game {
	bool running = false;
	uint8_t time = 0;
	Arena* arena = (Arena*)0x1000;

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
	}

	void update()
	{
		if (!running) return;
		arena->update();
	}
}