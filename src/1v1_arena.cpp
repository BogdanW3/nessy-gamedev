#include "../h/1v1_arena.hpp"

static const uint8_t sizes[3][2] =
{
	{ 12, 9 },
	{ 16, 12 },
	{ 20, 15 }
};

void One_V_One_Arena::start(const One_V_One_Arena::Size size)
{
	Arena::start(sizes[size][0], sizes[size][1], 2);
}

void One_V_One_Arena::update()
{

}