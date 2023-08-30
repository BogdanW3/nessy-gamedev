#ifndef ARENA_HPP
#define ARENA_HPP

#include "player.hpp"

const constexpr uint8_t PLAYER_COUNT = 4;

class Arena
{
public:
	constexpr inline uint8_t getWidth() const;
	constexpr inline uint8_t getHeight() const;
	inline bool isPaintable(uint8_t x, uint8_t y) const;
	void paint(
		uint8_t player_id,
		uint8_t x,
		uint8_t y
	);

private:
	const uint8_t height;
	const uint8_t width;
	uint8_t **tile_map;
	Player player[PLAYER_COUNT];

	Arena(const uint8_t width, const uint8_t height);

	void initTileMap();
};

#endif // !ARENA_HPP