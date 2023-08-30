#include "../lib/gpu.hpp"

#include "../h/mainmenu.hpp"
#include "../h/game.hpp"

int main()
{
	#ifdef NONES_SIM
	// write a fake status register state, to allow all draws
	*GPU_STATUS = 0xFF;
	// set up the window, and all other graphics stuff

	// set up the nmi to happen at 72Hz
	std::thread nmi_thread([](){
		while(true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000/72));
			nmi();
		}
	});
	#endif

	Colour colour(0xFF, 0xFF, 0x00);
	draw_pixel(GPU_RENDER_PIXEL1, 400, 20, colour);
	draw_shape(GPU_RENDER_LINE2, 10, 20, 200, 100, colour);
	draw_rect(PRIO_HIGH, 10, 20, 200, 100, colour);

	// after this test, start the actual game logic

	MainMenu::start();
	while(true)
	{
		MainMenu::update();
		Game::update();
	}


	return 0;
}