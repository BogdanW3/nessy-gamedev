#include "../h/arena.hpp"

#include "../h/tile.hpp"
#include "../lib/kb.hpp"

namespace Arena {


static constexpr const Colour PLAYER_COLOURS[4] =
{
	{0xFFu, 0x00u, 0x00u},
	{0x00u, 0x00u, 0xFFu},
	{0x00u, 0xFFu, 0x00u},
	{0xFFu, 0xFFu, 0x00u}
};


static constexpr const Vec2D PLAYER_STARTPOS[4] =
{
	{1, 1},
	{18, 13},
	{1, 13},
	{18, 1}
};

uint8_t tile_map[WIDTH_TILES][HEIGHT_TILES];
Player players[2];
bool dirty;

void start()
{
	Player::reset();
	dirty = true;
	for (uint8_t i = 0; i < PLAYER_COUNT; i++)
	{
		players[i].start();
	}
	initTileMap();
	initPlayers();
	draw_rect(PRIO_HIGH, 799, 0, 800, 599, Colour(0x60u, 0x60u, 0x60u));
}

void initTileMap()
{
	for (uint8_t i = 1; i < WIDTH_TILES - 1; i++)
	{
		for (uint8_t j = 1; j < HEIGHT_TILES - 1; j++)
		{
			tile_map[i][j] = TILE_DIRTY_MASK;
		}
	}

	initTileMapWalls();
}
void initTileMapWalls()
{
	uint8_t TILE_WALL = TILE_WALL_MASK | TILE_DIRTY_MASK;

	for (uint8_t i = 0; i < WIDTH_TILES; i++)
	{
		tile_map[i][0] = TILE_WALL;
		tile_map[i][HEIGHT_TILES - 1] = TILE_WALL;
	}

	for (uint8_t i = 0; i < HEIGHT_TILES; i++)
	{
		tile_map[0][i] = TILE_WALL;
		tile_map[WIDTH_TILES - 1][i] = TILE_WALL;
	}
}

void initPlayers()
{
	for (uint8_t i = 0; i < PLAYER_COUNT; i++)
	{
		Player &p = players[i];
		p.position = PLAYER_STARTPOS[i];
		tile_map[p.position.x][p.position.y] = TILE_TAKEN_MASK | TILE_DIRTY_MASK | p.getID();
		p.position.x <<= Player::position_multiplier_shift;
		p.position.y <<= Player::position_multiplier_shift;
	}
}

void drawTile(uint8_t x, uint8_t y)
{
	uint8_t tile = tile_map[x][y];
	if (!(tile & TILE_DIRTY_MASK)) return;
	const constexpr Vec2D scale = SCALING_FACTOR;

<<<<<<< HEAD
	draw_rect(PRIO_HIGH, x * scaling.x, y * scaling.y, (x + 1) * scaling.x - 1, (y + 1) * scaling.y - 1,
=======
	draw_rect(PRIO_HIGH, x * scale.x, y * scale.y, (x + 1) * scale.x - 1, (y + 1) * scale.y - 1,
>>>>>>> 4a9fc7e (Prettify)
	(tile & TILE_WALL_MASK) ? Colour(0xFFu, 0xFFu, 0xFFu) :
	(tile & TILE_TAKEN_MASK ? TILE_COLOURS[tile & TILE_OWNER_MASK] :
							  Colour(0x00u, 0x00u, 0x00u)));
	tile_map[x][y] &= ~TILE_DIRTY_MASK;
}

bool inline isFloor(uint8_t x, uint8_t y)
{
	if (x >= WIDTH_TILES)
		return false;
	if (y >= HEIGHT_TILES)
		return false;
	uint8_t tile = tile_map[x][y];
	return !(tile & TILE_WALL_MASK);
}

void setDirty(uint8_t x, uint8_t y)
{
	if (x >= WIDTH_TILES)
		return;
	if (y >= HEIGHT_TILES)
		return;
	tile_map[x][y] |= TILE_DIRTY_MASK;
}

void takeFloor(uint8_t player_id, uint8_t x, uint8_t y)
{
	if (player_id >= PLAYER_COUNT) return;
	if (!isFloor(x, y)) return;
	uint8_t &tile = tile_map[x][y];

	// Decrease score of last owner (if they exists)
	if (tile & TILE_TAKEN_MASK)
	{
		players[tile & TILE_OWNER_MASK].decreaseScore();
	}

	// Set taken bit;
	tile |= TILE_TAKEN_MASK | TILE_DIRTY_MASK;

	// Write tile owner ID;
	tile &= ~TILE_OWNER_MASK;
	tile |= player_id & TILE_OWNER_MASK;

	// Increase score of new owner
	players[player_id].increaseScore();
}

void tick()
{
	for (uint8_t i = 0; i < PLAYER_COUNT; i++)
	{
		Player &p = players[i];
		volatile KB::PlayerKBData &data = KB::PLAYER_KB_DATA[i];
		if (data.A)
		{
			Vec2D aim = p.getAim();
			while (aim.x || aim.y)
			{
				takeFloor(p.getID(), (p.position.x >> Player::position_multiplier_shift) + aim.x,
					  (p.position.y >> Player::position_multiplier_shift) + aim.y);
				if (aim.x > 0x8000)
					aim.x++;
				else if (aim.x < 0x8000 && aim.x != 0)
					aim.x--;
				if (aim.y > 0x8000)
					aim.y++;
				else if (aim.y < 0x8000 && aim.y != 0)
					aim.y--;
			}
			dirty = true;
		}
		if (data.UP)
		{
			if (isFloor((p.position.x >> Player::position_multiplier_shift),
							((p.position.y - 1) >> Player::position_multiplier_shift)))
			{
				p.position.y--;
				p.facing = Player::UP;
				dirty = true;
			}
		}
		if (data.DOWN)
		{
			if (isFloor((p.position.x >> Player::position_multiplier_shift),
							((p.position.y + 1) >> Player::position_multiplier_shift)))
			{
				p.position.y++;
				p.facing = Player::DOWN;
				dirty = true;
			}
		}
		if (data.LEFT)
		{
			if (isFloor(((p.position.x - 1) >> Player::position_multiplier_shift),
							(p.position.y >> Player::position_multiplier_shift)))
			{
				p.position.x--;
				p.facing = Player::LEFT;
				dirty = true;
			}
		}
		if (data.RIGHT)
		{
			if (isFloor(((p.position.x + 1) >> Player::position_multiplier_shift),
							(p.position.y >> Player::position_multiplier_shift)))
			{
				p.position.x++;
				p.facing = Player::RIGHT;
				dirty = true;
			}
		}
		if (dirty)
		{
			uint8_t x = (p.position.x >> Player::position_multiplier_shift);
			uint8_t y = (p.position.y >> Player::position_multiplier_shift);
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
					setDirty(x + i, y + j);
			takeFloor(p.getID(), x, y);
		}
	}
}

void update()
{
	if (dirty)
	{
		for (uint8_t i = 0; i < WIDTH_TILES; i++)
		{
			for (uint8_t j = 0; j < HEIGHT_TILES; j++)
			{
				drawTile(i, j);
			}
		}
		dirty = false;
		Vec2D scale = SCALING_FACTOR;
		for (uint8_t i = 0; i < PLAYER_COUNT; i++)
		{
			Player &p = players[i];
			draw_rect(PRIO_LOW, ((p.position.x * scale.x) >> Player::position_multiplier_shift) - 8,
					  ((p.position.y * scale.y) >> Player::position_multiplier_shift) - 8,
					  ((p.position.x * scale.x) >> Player::position_multiplier_shift) + 6,
					  ((p.position.y * scale.y) >> Player::position_multiplier_shift) + 6,
					  PLAYER_COLOURS[p.getID()]);
		}
	}
}
/*
~Arena()
{
	for(uint8_t i = 0; i < WIDTH_TILES; i++)
	{
		delete[] tile_map[i];
	}
	delete[] tile_map;

	delete[] players;
}*/
}