#include "../h/arena.hpp"

#include "../h/tile.hpp"
#include "../lib/kb.hpp"

void Arena::start(const uint8_t width, const uint8_t height, const uint8_t player_count)
{
	const_cast<uint8_t&>(this->width) = width;
	const_cast<uint8_t&>(this->height) = height;
	const_cast<uint8_t&>(this->player_count) = player_count;
	dirty = true;
	players = (Player*)(&(this->player_count) + 1);
	for (uint8_t i = 0; i < player_count; i++)
	{
		players[i] = Player();
	}
	tile_map = (uint8_t*)(&(players[player_count]) + 1);
	initTileMap();
	initPlayers();
}

void Arena::initTileMap()
{

	initTileMapWalls();

	for(uint8_t i = 1; i < width-1; i++)
	{
		for(uint8_t j = 1; j < height-1; j++)
		{
			tile_map[i + width * j] = 0;
		}
	}
}
void Arena::initTileMapWalls()
{
	uint8_t TILE_WALL = TILE_WALL_MASK;

	for(uint8_t i = 0; i < width; i++)
	{
		tile_map[i + width * 0] = TILE_WALL;
		tile_map[i + width * height-1] = TILE_WALL;
	}

	for(uint8_t i = 0; i < height; i++)
	{
		tile_map[0 + width * i] = TILE_WALL;
		tile_map[width-1 + width * i] = TILE_WALL;
	}
}

void Arena::initPlayers()
{
	for(uint8_t i = 0; i < player_count; i++)
	{
		Player& p = players[i];
		p.position.x = width/10 + (p.id & 0x1) * (width - width/5);
		p.position.y = height/10 + (!(p.id & 0x2)) * (height - height/5);
		tile_map[p.position.x + width * p.position.y] = TILE_TAKEN_MASK | p.id;
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
	uint8_t tile = tile_map[x + width * y];
	return !(tile & TILE_WALL_MASK);
}

void Arena::paint(uint8_t player_id, uint8_t x, uint8_t y)
{
	if(player_id >= player_count) return;
	if(!isPaintable(x,y)) return;
	uint8_t tile = tile_map[x + width * y];

	//Decrease score of last owner (if they exists)
	if(tile & TILE_TAKEN_MASK) {
		players[tile & TILE_OWNER_MASK].decreaseScore();
	}

	//Set taken bit;
	tile |= TILE_TAKEN_MASK;

	//Write tile owner ID;
	tile &= ~TILE_OWNER_MASK;
	tile |= player_id & TILE_OWNER_MASK;

	//Increase score of new owner
	players[player_id].increaseScore();
}

void Arena::tick()
{
	for(uint8_t i = 0; i < player_count; i++)
	{
		Player& p = players[i];
		KB::PlayerKBData* data = KB::PLAYER_KB_DATA[i];
		if(data->A) {
			paint(p.id, p.position.x, p.position.y);
			dirty = true;
		}
		if(data->UP) {
			if(isPaintable(p.position.x, p.position.y-1)) {
				p.position.y--;
				dirty = true;
			}
		}
		if(data->DOWN) {
			if(isPaintable(p.position.x, p.position.y+1)) {
				p.position.y++;
				dirty = true;
			}
		}
		if(data->LEFT) {
			if(isPaintable(p.position.x-1, p.position.y)) {
				p.position.x--;
				dirty = true;
			}
		}
		if(data->RIGHT) {
			if(isPaintable(p.position.x+1, p.position.y)) {
				p.position.x++;
				dirty = true;
			}
		}

	}

}

/*
Arena::~Arena()
{
	for(uint8_t i = 0; i < width; i++)
	{
		delete[] tile_map[i];
	}
	delete[] tile_map;

	delete[] players;
}*/