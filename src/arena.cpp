#include "../h/arena.hpp"

#include "../h/tile.hpp"
#include "../lib/kb.hpp"

namespace Arena {


static constexpr const Colour PLAYER_COLOURS[4] =
{
	{0xF, 0x0, 0x0},
	{0x0, 0x0, 0xF},
	{0x0, 0xF, 0x0},
	{0xF, 0xF, 0x0}
};


static constexpr const Vec2D PLAYER_STARTPOS[4] =
{
	{2, 2},
	{18, 13},
	{1, 13},
	{18, 2}
};

uint8_t tile_map[WIDTH_TILES][HEIGHT_TILES];
Player players[PLAYER_COUNT];
uint8_t timeoutKilled[PLAYER_COUNT];
bool dirty;

inline Colour getTileColour(uint8_t tile)
{
	if(tile & TILE_WALL_MASK) {
		//Walls are white;
		return Colour(0xF, 0xF, 0xF);
	}

	if(tile & TILE_TAKEN_MASK) {
		//Return taken tile colour
		return TILE_COLOURS[tile & TILE_OWNER_MASK];
	}

	//black floor;
	return Colour(0x0, 0x0, 0x0);
}

void setDirty(uint8_t x, uint8_t y)
{
	if (x >= WIDTH_TILES)
		return;
	if (y >= HEIGHT_TILES)
		return;
	tile_map[x][y] |= TILE_DIRTY_MASK;
}

void drawTile(uint8_t x, uint8_t y)
{
	uint8_t &tile = tile_map[x][y];
	if (!(tile & TILE_DIRTY_MASK)) return;

	const constexpr Vec2D scale = SCALING_FACTOR;

	uint16_t startX = x*scale.x;
	uint16_t startY = y*scale.y;
	uint16_t endX = (x + 1)*scale.x - 1;
	uint16_t endY = (y + 1)*scale.y - 1;
	Colour colour = getTileColour(tile);

	draw_rect(PRIO_HIGH, startX, startY, endX, endY, colour);

	tile &= ~TILE_DIRTY_MASK;

}

void initPlayers()
{
	for (uint8_t id = 0; id < PLAYER_COUNT; id++)
	{
		initPlayer(id);
	}
}


void initPlayer(uint8_t playerID)
{
		Player &player = players[playerID];
		player.position = PLAYER_STARTPOS[playerID];
		tile_map[player.position.x][player.position.y] = TILE_TAKEN_MASK | TILE_DIRTY_MASK | playerID;
		player.position.x <<= Player::position_multiplier_shift;
		player.position.y <<= Player::position_multiplier_shift;
}

inline bool isFloor(uint8_t x, uint8_t y)
{
	if (x >= WIDTH_TILES)
		return false;
	if (y >= HEIGHT_TILES)
		return false;
	uint8_t tile = tile_map[x][y];
	return !(tile & TILE_WALL_MASK);
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

inline void initTileMapWalls()
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

void killPlayer(uint8_t playerID)
{
	timeoutKilled[playerID] = 72*3;

}

void takeFloor(uint8_t playerID, uint8_t x, uint8_t y)
{
	if (playerID >= PLAYER_COUNT) return;
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
	tile |= playerID & TILE_OWNER_MASK;

	// Increase score of new owner
	players[playerID].increaseScore();
}


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
	//draw_rect(PRIO_HIGH, 799, 0, 800, 599, Colour(0x0, 0x0, 0x0));
}

void tick()
{
	for (uint8_t playerID = 0; playerID < PLAYER_COUNT; playerID++)
	{
		if (timeoutKilled[playerID] != 0)
		{
			if (--timeoutKilled[playerID] != 0)
				continue;
			initPlayer(playerID);
			dirty = true;
			continue;
		}

		Player &player = players[playerID];
		volatile KB::PlayerKBData &data = KB::PLAYER_KB_DATA[playerID];
		if (data.A)
		{
			tickPlayerAttack(playerID);
			dirty = true;
		}
		tickPlayerMovement(playerID);
		if (dirty)
		{
			uint8_t x = (player.position.x >> Player::position_multiplier_shift);
			uint8_t y = (player.position.y >> Player::position_multiplier_shift);
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
					setDirty(x + i, y + j);
			takeFloor(player.getID(), x, y);
		}
	}
}

void tickPlayerAttack(uint8_t playerID)
{
	Player& player = players[playerID];
	Vec2D aim = player.getAim();

	uint8_t playerTileX = player.getTileX();
	uint8_t playerTileY = player.getTileY();

	while (aim.x || aim.y)
	{
		uint8_t absTileX = playerTileX + aim.x;
		uint8_t absTileY = playerTileY + aim.y;

		for(int targetID = 0; targetID < PLAYER_COUNT; targetID++)
		{
			Player& target = players[targetID];

			if(targetID == playerID) continue;

			uint8_t targetTileX = target.getTileX();
			uint8_t targetTileY = target.getTileY();

			if(targetTileX == absTileX && targetTileY == absTileY)
			{
				killPlayer(targetID);
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
						setDirty(targetTileX + i, targetTileY + j);

			}
		}
		takeFloor(player.getID(), playerTileX + aim.x,
			  playerTileY + aim.y);
		if (aim.x > 0x8000)
			aim.x++;
		else if (aim.x < 0x8000 && aim.x != 0)
			aim.x--;
		if (aim.y > 0x8000)
			aim.y++;
		else if (aim.y < 0x8000 && aim.y != 0)
			aim.y--;
	}
}

void tickPlayerMovement(uint8_t playerID)
{
	Player& player = players[playerID];
	volatile KB::PlayerKBData& data = KB::PLAYER_KB_DATA[playerID];

	if (data.UP)
	{
		if (isFloor(player.getTileX(), player.getTileY(-1)))
		{
			player.position.y--;
			player.facing = Player::UP;
			dirty = true;
		}
	}
	if (data.DOWN)
	{
		if (isFloor(player.getTileX(), player.getTileY(1)))
		{
			player.position.y++;
			player.facing = Player::DOWN;
			dirty = true;
		}
	}
	if (data.LEFT)
	{
		if (isFloor(player.getTileX(-1), player.getTileY()))
		{
			player.position.x--;
			player.facing = Player::LEFT;
			dirty = true;
		}
	}
	if (data.RIGHT)
	{
		if (isFloor(player.getTileX(1), player.getTileY()))
		{
			player.position.x++;
			player.facing = Player::RIGHT;
			dirty = true;
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
		draw_line(0,0,40,40, Colour(0x0, 0x0u, 0x0u));
		draw_line(760,560,800,600, Colour(0x0, 0x0u, 0x0u));
		draw_line(760,40,800,0, Colour(0x0, 0x0u, 0x0u));
		draw_line(40,560,0,600, Colour(0x0, 0x0u, 0x0u));

		dirty = false;
		Vec2D scale = SCALING_FACTOR;
		for (uint8_t i = 0; i < PLAYER_COUNT; i++)
		{
			if (timeoutKilled[i] != 0) continue;
			Player &player = players[i];
			draw_rect(PRIO_LOW, ((player.position.x * scale.x) >> Player::position_multiplier_shift) - 8,
					  ((player.position.y * scale.y) >> Player::position_multiplier_shift) - 8,
					  ((player.position.x * scale.x) >> Player::position_multiplier_shift) + 6,
					  ((player.position.y * scale.y) >> Player::position_multiplier_shift) + 6,
					  PLAYER_COLOURS[i]);
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