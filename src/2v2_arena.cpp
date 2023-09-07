#include "../h/2v2_arena.hpp"

static const constexpr uint8_t sizes[3][2] =
{
	{20, 15},
	{28, 21},
	{32, 24},
};

const Colour Two_V_Two_Arena::TILE_COLOURS[4] = {{0x99, 0x00, 0x00}, {0x00, 0x00, 0x99},
												 {0x99, 0x00, 0x00}, {0x00, 0x00, 0x99}};

void Two_V_Two_Arena::start(const Two_V_Two_Arena::Size size)
{
	Arena::start(sizes[size][0], sizes[size][1], 4);
	pTILE_COLOURS = (const Colour *)&TILE_COLOURS[0];
}

void Two_V_Two_Arena::update()
{
}
