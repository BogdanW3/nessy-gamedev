#ifndef TILE_HPP
#define TILE_HPP

#ifndef NONES
#include "../lib/stdint.hpp"
#else
#include <stdint.h>
#endif

const uint8_t TILE_DIRTY_MASK = 0b10000;
const uint8_t TILE_WALL_MASK =  0b01000;
const uint8_t TILE_TAKEN_MASK = 0b00100;
const uint8_t TILE_OWNER_MASK = 0b00011;

#endif // !TILE_HPP