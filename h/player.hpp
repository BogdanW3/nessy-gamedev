#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifndef NONES
#include "../lib/stdint.hpp"
#else
#include <stdint.h>
#endif

class Player
{
public:
	Player();
	void increaseScore();
	void decreaseScore();
	uint8_t getScore() const;
	uint8_t getId() const;
	static void reset();
	struct Vec2D
	{
		constexpr Vec2D(uint16_t x, uint16_t y) : x(x), y(y) {}
		uint16_t x;
		uint16_t y;
	};

	Vec2D getAim() const;

private:
	static uint8_t nextid;
	uint8_t id;
	uint8_t score;
	// the player's position is 2^4 (or 5?) times larger than tile position,
	// for slower movement
	Vec2D position;
	static constexpr const uint8_t position_multiplier_shift = 5;

	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Direction facing = UP;

	friend class Arena;
};

#endif // !PLAYER_HPP