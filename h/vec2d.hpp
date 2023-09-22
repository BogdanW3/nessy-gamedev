#ifndef VEC2D_H
#define VEC2D_H


#ifndef NONES
#include "../lib/stdint.hpp"
#else
#include <stdint.h>
#endif

struct Vec2D
{
	constexpr Vec2D(uint16_t x, uint16_t y) : x(x), y(y) {}
	constexpr Vec2D() : x(0), y(0) {}
	uint16_t x;
	uint16_t y;
};

#endif