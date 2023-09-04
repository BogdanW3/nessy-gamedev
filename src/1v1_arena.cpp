#include "../h/1v1_arena.hpp"

static const constexpr uint8_t sizes[3][2] =
{
	{ 12, 9 },
	{ 16, 12 },
	{ 20, 15 }
};

const Colour One_V_One_Arena::TILE_COLOURS[2] = {  {0x99, 0x00, 0x00}, {0x00, 0x00, 0x99} };

void One_V_One_Arena::start(const One_V_One_Arena::Size size)
{
	Arena::start(sizes[size][0], sizes[size][1], 2);
	pTILE_COLOURS = (const Colour*)&TILE_COLOURS[0];
}

void One_V_One_Arena::update()
{

}