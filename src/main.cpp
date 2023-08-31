#include "../lib/gpu.hpp"

#include "../h/mainmenu.hpp"
#include "../h/game.hpp"

#ifdef NONES
#include <raylib.h>
#include <thread>

#include "../lib/nmi.hpp"
#include "../lib/kb.hpp"
#else
bool WindowShouldClose()
{
	return false;
}
#endif

int main()
{
	#ifdef NONES
	// write a fake status register state, to allow all draws
	GPU_STATUS = new char(0xFF);
	GPU_RENDER_PIXEL1 = GPU_STATUS + 1;
	GPU_RENDER_PIXEL2 = GPU_STATUS + 2;
	GPU_RENDER_LINE1 = GPU_STATUS + 3;
	GPU_RENDER_LINE2 = GPU_STATUS + 4;
	GPU_RENDER_RECT1 = GPU_STATUS + 5;
	GPU_RENDER_RECT2 = GPU_STATUS + 6;

	KB::PLAYER_KB_DATA = new KB::PlayerKBData*[4];
	for (int i = 0; i < 4; i++)
		KB::PLAYER_KB_DATA[i] = new KB::PlayerKBData();


	// set up the window, and all other graphics stuff
	InitWindow(800, 600, "NESSY");
	SetTargetFPS(72);
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
	while(!WindowShouldClose())
	{
		#ifdef NONES
		BeginDrawing();
		#endif
		MainMenu::update();
		Game::update();
		#ifdef NONES
		EndDrawing();
		#endif
	}


	return 0;
}