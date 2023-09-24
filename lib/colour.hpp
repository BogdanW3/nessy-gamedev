#ifndef COLOUR_HPP
#define COLOUR_HPP


#ifndef NONES
#include "stdint.hpp"
#else
#include <stdint.h>
#endif

struct Colour
{
	// Only the bottom 4 bits of each colour are used
	constexpr Colour(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

#endif