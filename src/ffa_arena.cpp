#include "../h/ffa_arena.hpp"

static const uint8_t sizes[4][2] = {
	{ 20, 15 },
	{ 28, 21 },
	{ 32, 24 },
	{ 36, 27 }
};

void FFA_Arena::start(const FFA_Arena::Size size)
{
	Arena::start(sizes[size][0], sizes[size][1], 4);
}

void FFA_Arena::update()
{

}