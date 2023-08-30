#include "kb.hpp"

// Data is first latched by writing 1 to the control register
// Then, the data is read from the data registers
// The register at 0x4016 has 0,0,0,0,0,X,P2,P1
// The register at 0x4017 has 0,0,0,0,0,X,P4,P3
// The data is read sequentially, and the order is
// A, B, Select, Start, Up, Down, Left, Right

void KB::tick()
{
	#ifdef NONES_SIM
	//TODO: implement
	// the player kb data structs should get the current presssed states of buttons
	// {ALSO PUT KEYBINDS HERE IN A COMMENT}
	#else
	*KB_CONTROL = 1;
	*KB_CONTROL = 0;

	char data = 0;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->A = data & 0x01;
	PLAYER_KB_DATA[1]->A = data & 0x02;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->B = data & 0x01;
	PLAYER_KB_DATA[1]->B = data & 0x02;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->SELECT = data & 0x01;
	PLAYER_KB_DATA[1]->SELECT = data & 0x02;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->START = data & 0x01;
	PLAYER_KB_DATA[1]->START = data & 0x02;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->UP = data & 0x01;
	PLAYER_KB_DATA[1]->UP = data & 0x02;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->DOWN = data & 0x01;
	PLAYER_KB_DATA[1]->DOWN = data & 0x02;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->LEFT = data & 0x01;
	PLAYER_KB_DATA[1]->LEFT = data & 0x02;

	data = *KB_DATA1;
	PLAYER_KB_DATA[0]->RIGHT = data & 0x01;
	PLAYER_KB_DATA[1]->RIGHT = data & 0x02;


	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->A = data & 0x01;
	PLAYER_KB_DATA[3]->A = data & 0x02;

	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->B = data & 0x01;
	PLAYER_KB_DATA[3]->B = data & 0x02;

	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->SELECT = data & 0x01;
	PLAYER_KB_DATA[3]->SELECT = data & 0x02;

	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->START = data & 0x01;
	PLAYER_KB_DATA[3]->START = data & 0x02;

	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->UP = data & 0x01;
	PLAYER_KB_DATA[3]->UP = data & 0x02;

	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->DOWN = data & 0x01;
	PLAYER_KB_DATA[3]->DOWN = data & 0x02;

	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->LEFT = data & 0x01;
	PLAYER_KB_DATA[3]->LEFT = data & 0x02;

	data = *KB_DATA2;
	PLAYER_KB_DATA[2]->RIGHT = data & 0x01;
	PLAYER_KB_DATA[3]->RIGHT = data & 0x02;
	#endif
}