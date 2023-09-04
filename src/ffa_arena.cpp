#include "../h/ffa_arena.hpp"

static const constexpr uint8_t sizes[4][2] = {
	{ 20, 15 },
	{ 28, 21 },
	{ 32, 24 },
	{ 36, 27 }
};

const Colour FFA_Arena::TILE_COLOURS[4] = { {0x99, 0x00, 0x00}, {0x00, 0x00, 0x99},
												  {0x00, 0x99, 0x00}, {0x99, 0x99, 0x00} };

void FFA_Arena::start(const FFA_Arena::Size size)
{
	Arena::start(sizes[size][0], sizes[size][1], 4);
	pTILE_COLOURS = (const Colour*)&TILE_COLOURS[0];
}

void FFA_Arena::update()
{

}