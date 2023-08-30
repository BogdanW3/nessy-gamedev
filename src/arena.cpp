#include "../h/arena.hpp"
#include "../h/tile.hpp"

Arena::Arena(const uint8_t width, const uint8_t height):
	width(width), height(height)
{
	tile_map = new uint8_t*[width];
	for(uint8_t i = 0; i < width; i++)
	{
		tile_map[i] = new uint8_t[height];
	}
	initTileMap();
}

void Arena::initTileMap()
{
	uint8_t TILE_WALL = TILE_WALL_MASK;


	for(uint8_t i = 0; i < width; i++)
	{
		tile_map[i][0] = TILE_WALL;
		tile_map[i][height-1] = TILE_WALL;
	}

	for(uint8_t i = 0; i < height; i++)
	{
		tile_map[0][i] = TILE_WALL;
		tile_map[width-1][i] = TILE_WALL;
	}
}

constexpr inline uint8_t Arena::getWidth() const
{
	return width;
}

constexpr inline uint8_t Arena::getHeight() const
{
	return height;
}

bool inline Arena::isPaintable(uint8_t x, uint8_t y) const
{
	if(x >= width) return false;
	if(y >= height) return false;
	uint8_t tile = tile_map[x][y];
	return !(tile & TILE_WALL_MASK);
}

void Arena::paint(uint8_t player_id, uint8_t x, uint8_t y)
{
	if(player_id >= PLAYER_COUNT) return;
	if(!isPaintable(x,y)) return;
	uint8_t tile = tile_map[x][y];

	//Decrease score of last owner (if they exists)
	if(tile & TILE_TAKEN_MASK) {
		player[tile & TILE_OWNER_MASK].decreaseScore();
	}

	//Set taken bit;
	tile |= TILE_TAKEN_MASK;

	//Write tile owner ID;
	tile &= ~TILE_OWNER_MASK;
	tile |= player_id & TILE_OWNER_MASK;

	//Increase score of new owner
	player[player_id].increaseScore();
}