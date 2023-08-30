#include "kb.hpp"

// Data is first latched by writing 1 to the control register
// Then, the data is read from the data registers
// The register at 0x4016 has 0,0,0,0,0,X,P2,P1
// The register at 0x4017 has 0,0,0,0,0,X,P4,P3
// The data is read sequentially, and the order is
// A, B, Select, Start, Up, Down, Left, Right

void kb_handle_nmi()
{
	*KB_CONTROL = 1;
	*KB_CONTROL = 0;

	char data = 0;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->A = data & 0x01;
	PLAYER2_KB_DATA->A = data & 0x02;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->B = data & 0x01;
	PLAYER2_KB_DATA->B = data & 0x02;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->SELECT = data & 0x01;
	PLAYER2_KB_DATA->SELECT = data & 0x02;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->START = data & 0x01;
	PLAYER2_KB_DATA->START = data & 0x02;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->UP = data & 0x01;
	PLAYER2_KB_DATA->UP = data & 0x02;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->DOWN = data & 0x01;
	PLAYER2_KB_DATA->DOWN = data & 0x02;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->LEFT = data & 0x01;
	PLAYER2_KB_DATA->LEFT = data & 0x02;

	data = *KB_DATA1;
	PLAYER1_KB_DATA->RIGHT = data & 0x01;
	PLAYER2_KB_DATA->RIGHT = data & 0x02;


	data = *KB_DATA2;
	PLAYER3_KB_DATA->A = data & 0x01;
	PLAYER4_KB_DATA->A = data & 0x02;

	data = *KB_DATA2;
	PLAYER3_KB_DATA->B = data & 0x01;
	PLAYER4_KB_DATA->B = data & 0x02;

	data = *KB_DATA2;
	PLAYER3_KB_DATA->SELECT = data & 0x01;
	PLAYER4_KB_DATA->SELECT = data & 0x02;

	data = *KB_DATA2;
	PLAYER3_KB_DATA->START = data & 0x01;
	PLAYER4_KB_DATA->START = data & 0x02;

	data = *KB_DATA2;
	PLAYER3_KB_DATA->UP = data & 0x01;
	PLAYER4_KB_DATA->UP = data & 0x02;

	data = *KB_DATA2;
	PLAYER3_KB_DATA->DOWN = data & 0x01;
	PLAYER4_KB_DATA->DOWN = data & 0x02;

	data = *KB_DATA2;
	PLAYER3_KB_DATA->LEFT = data & 0x01;
	PLAYER4_KB_DATA->LEFT = data & 0x02;

	data = *KB_DATA2;
	PLAYER3_KB_DATA->RIGHT = data & 0x01;
	PLAYER4_KB_DATA->RIGHT = data & 0x02;
}