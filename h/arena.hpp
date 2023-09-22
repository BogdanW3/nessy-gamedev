#ifndef ARENA_HPP
#define ARENA_HPP

#include "player.hpp"
#include "../lib/colour.hpp"

namespace Arena
{
	static constexpr const uint16_t WIDTH = 800;
	static constexpr const uint16_t HEIGHT = 600;
	static constexpr const uint8_t WIDTH_TILES = 20;
	static constexpr const uint8_t HEIGHT_TILES = 15;
	static constexpr const uint8_t PLAYER_COUNT = 2;
	static constexpr const Vec2D SCALING_FACTOR = Vec2D { WIDTH/WIDTH_TILES, HEIGHT/HEIGHT_TILES };

	extern uint8_t tile_map[WIDTH_TILES][HEIGHT_TILES];
	extern Player players[2];
	extern bool dirty;

	inline bool isFloor(uint8_t x, uint8_t y);
	void tick();
	void update();

	void takeFloor(
		uint8_t player_id,
		uint8_t x,
		uint8_t y);
	void setDirty(
		uint8_t x,
		uint8_t y);

	void start();

	void initTileMap();
	void initTileMapWalls();
	void initPlayers();

	void drawTile(uint8_t x, uint8_t y);
};

#endif // !ARENA_HPP