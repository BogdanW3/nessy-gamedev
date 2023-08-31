#ifndef TILE_HPP
#define TILE_HPP

#ifndef NONES
#include "../lib/stdint.hpp"
#else
#include <stdint.h>
#endif

const uint8_t TILE_WALL_MASK = 0b1000;
const uint8_t TILE_TAKEN_MASK = 0b0100;
const uint8_t TILE_OWNER_MASK = 0b0011;

#endif // !TILE_HPP