#ifndef ARENA_HPP
#define ARENA_HPP

#include "player.hpp"
#include "../lib/gpu.hpp"

class Arena
{
public:
	constexpr inline uint8_t getWidth() const;
	constexpr inline uint8_t getHeight() const;
	inline bool isPaintable(uint8_t x, uint8_t y) const;
	void paint(
		uint8_t player_id,
		uint8_t x,
		uint8_t y);

	void tick();
	void update();

protected:
	uint8_t height = 0;
	uint8_t width = 0;
	uint8_t player_count = 0;
	bool dirty = false;
	uint8_t *tile_map = nullptr;
	Player *players = nullptr;

	const Colour *pTILE_COLOURS = nullptr;

	void start(const uint8_t width, const uint8_t height, const uint8_t player_count);

	void initTileMap();
	void initTileMapWalls();
	void initPlayers();

	void drawTile(uint8_t x, uint8_t y) const;

	constexpr const Player::Vec2D getScalingFactor() const;
};

#endif // !ARENA_HPP