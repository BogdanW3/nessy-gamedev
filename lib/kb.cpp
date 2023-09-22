#include "kb.hpp"

// Data is first latched by writing 1 to the control register
// Then, the data is read from the data registers
// The register at 0x4016 has 0,0,0,0,0,X,P2,P1
// The register at 0x4017 has 0,0,0,0,0,X,P4,P3
// The data is read sequentially, and the order is
// A, B, Select, Start, Up, Down, Left, Right
// Player 1: Q, E, R, F, W, S, A, D
// Player 2: KP7, KP9, 0, 0, KP8, KP5, KP4, KP6
// Players 3 and 4 have the same keybinds, on the second keyboard

namespace KB
{
#ifdef NONES
#include <raylib.h>
	PlayerKBData *PLAYER_KB_DATA;
#else
volatile PlayerKBData PLAYER_KB_DATA[4];
#endif

	void tick()
	{
#ifdef NONES
		// TODO: implement
		//  the player kb data structs should get the current presssed states of buttons
		//  {ALSO PUT KEYBINDS HERE IN A COMMENT}
		PLAYER_KB_DATA[0].A = IsKeyDown(KEY_Q);
		PLAYER_KB_DATA[0].B = IsKeyDown(KEY_E);
		PLAYER_KB_DATA[0].SELECT = IsKeyDown(KEY_R);
		PLAYER_KB_DATA[0].START = IsKeyDown(KEY_F);
		PLAYER_KB_DATA[0].UP = IsKeyDown(KEY_W);
		PLAYER_KB_DATA[0].DOWN = IsKeyDown(KEY_S);
		PLAYER_KB_DATA[0].LEFT = IsKeyDown(KEY_A);
		PLAYER_KB_DATA[0].RIGHT = IsKeyDown(KEY_D);

		PLAYER_KB_DATA[1].A = IsKeyDown(KEY_KP_7);
		PLAYER_KB_DATA[1].B = IsKeyDown(KEY_KP_9);
		PLAYER_KB_DATA[1].SELECT = false;
		PLAYER_KB_DATA[1].START = false;
		PLAYER_KB_DATA[1].UP = IsKeyDown(KEY_KP_8);
		PLAYER_KB_DATA[1].DOWN = IsKeyDown(KEY_KP_5);
		PLAYER_KB_DATA[1].LEFT = IsKeyDown(KEY_KP_4);
		PLAYER_KB_DATA[1].RIGHT = IsKeyDown(KEY_KP_6);

		// the last two players have no input sadly
		PLAYER_KB_DATA[2].A = false;
		PLAYER_KB_DATA[2].B = false;
		PLAYER_KB_DATA[2].SELECT = false;
		PLAYER_KB_DATA[2].START = false;
		PLAYER_KB_DATA[2].UP = false;
		PLAYER_KB_DATA[2].DOWN = false;
		PLAYER_KB_DATA[2].LEFT = false;
		PLAYER_KB_DATA[2].RIGHT = false;

		PLAYER_KB_DATA[3].A = false;
		PLAYER_KB_DATA[3].B = false;
		PLAYER_KB_DATA[3].SELECT = false;
		PLAYER_KB_DATA[3].START = false;
		PLAYER_KB_DATA[3].UP = false;
		PLAYER_KB_DATA[3].DOWN = false;
		PLAYER_KB_DATA[3].LEFT = false;
		PLAYER_KB_DATA[3].RIGHT = false;
#else
		*KB_CONTROL = 1;
		*KB_CONTROL = 0;

		char data = 0;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].A = data & 0x01;
		PLAYER_KB_DATA[1].A = data & 0x02;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].B = data & 0x01;
		PLAYER_KB_DATA[1].B = data & 0x02;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].SELECT = data & 0x01;
		PLAYER_KB_DATA[1].SELECT = data & 0x02;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].START = data & 0x01;
		PLAYER_KB_DATA[1].START = data & 0x02;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].UP = data & 0x01;
		PLAYER_KB_DATA[1].UP = data & 0x02;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].DOWN = data & 0x01;
		PLAYER_KB_DATA[1].DOWN = data & 0x02;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].LEFT = data & 0x01;
		PLAYER_KB_DATA[1].LEFT = data & 0x02;

		data = *KB_DATA1;
		PLAYER_KB_DATA[0].RIGHT = data & 0x01;
		PLAYER_KB_DATA[1].RIGHT = data & 0x02;


		data = *KB_DATA2;
		PLAYER_KB_DATA[2].A = data & 0x01;
		PLAYER_KB_DATA[3].A = data & 0x02;

		data = *KB_DATA2;
		PLAYER_KB_DATA[2].B = data & 0x01;
		PLAYER_KB_DATA[3].B = data & 0x02;

		data = *KB_DATA2;
		PLAYER_KB_DATA[2].SELECT = data & 0x01;
		PLAYER_KB_DATA[3].SELECT = data & 0x02;

		data = *KB_DATA2;
		PLAYER_KB_DATA[2].START = data & 0x01;
		PLAYER_KB_DATA[3].START = data & 0x02;

		data = *KB_DATA2;
		PLAYER_KB_DATA[2].UP = data & 0x01;
		PLAYER_KB_DATA[3].UP = data & 0x02;

		data = *KB_DATA2;
		PLAYER_KB_DATA[2].DOWN = data & 0x01;
		PLAYER_KB_DATA[3].DOWN = data & 0x02;

		data = *KB_DATA2;
		PLAYER_KB_DATA[2].LEFT = data & 0x01;
		PLAYER_KB_DATA[3].LEFT = data & 0x02;

		data = *KB_DATA2;
		PLAYER_KB_DATA[2].RIGHT = data & 0x01;
		PLAYER_KB_DATA[3].RIGHT = data & 0x02;
#endif
	}
}