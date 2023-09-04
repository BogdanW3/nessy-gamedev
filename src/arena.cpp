#include "../h/arena.hpp"

#include "../h/tile.hpp"
#include "../lib/kb.hpp"
#include "../lib/gpu.hpp"

static constexpr Colour PLAYER_COLOURS[4] = {
	{0xFFu, 0x00u, 0x00u},
	{0x00u, 0xFFu, 0x00u},
	{0x00u, 0x00u, 0xFFu},
	{0xFFu, 0xFFu, 0x00u}
};

constexpr const Player::Vec2D Arena::getScalingFactor() const
{
	return {800u/width, 600u/height};
}

void Arena::start(const uint8_t width, const uint8_t height, const uint8_t player_count)
{
	this->width = width;
	this->height = height;
	this->player_count = player_count;
	dirty = true;
	players = (Player*)(this + 1);
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

void Arena::drawTile(uint8_t x, uint8_t y) const
{
	uint8_t tile = tile_map[x + width * y];
	consts Player::Vec2D scaling = getScalingFactor();
	draw_rect(x*scaling.x, y*scaling.y, (x+1)*scaling.x, (y+1)*scaling.y, TILE_COLOURS[tile]);
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
			Player::Vec2D aim = p.getAim();
			paint(p.id, p.position.x + aim.x, p.position.y + aim.y);
			dirty = true;
		}
		if(data->UP) {
			if(isPaintable(p.position.x, p.position.y-1)) {
				p.position.y--;
				paint(p.id, p.position.x, p.position.y);
				dirty = true;
				p.dirty = true;
			}
		}
		if(data->DOWN) {
			if(isPaintable(p.position.x, p.position.y+1)) {
				p.position.y++;
				paint(p.id, p.position.x, p.position.y);
				dirty = true;
				p.dirty = true;
			}
		}
		if(data->LEFT) {
			if(isPaintable(p.position.x-1, p.position.y)) {
				p.position.x--;
				paint(p.id, p.position.x, p.position.y);
				dirty = true;
				p.dirty = true;
			}
		}
		if(data->RIGHT) {
			if(isPaintable(p.position.x+1, p.position.y)) {
				p.position.x++;
				paint(p.id, p.position.x, p.position.y);
				dirty = true;
				p.dirty = true;
			}
		}
	}

}

void Arena::update()
{
	if(dirty)
	{
		for(uint8_t i = 0; i < width; i++)
		{
			for(uint8_t j = 0; j < height; j++)
			{
				drawTile(i,j);
			}
		}
		dirty = false;
	}
	for(uint8_t i = 0; i < player_count; i++)
	{
		Player& p = players[i];
		if(p.dirty)
		{
			draw_rect(p.position.x*10 - 4, p.position.y*10 - 4,
				 p.position.x*10 + 4, p.position.y*10 + 4, PLAYER_COLOURS[p.id]);
			p.dirty = false;
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