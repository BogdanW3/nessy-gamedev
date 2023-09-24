#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "vec2d.hpp"

class Player
{
public:
	void start();
	void increaseScore();
	void decreaseScore();

	uint8_t getTileX(signed char offset = 0);
	uint8_t getTileY(signed char offset = 0);
	uint8_t getScore() const;
	uint8_t getID() const;
	static void reset();


	Vec2D getAim() const;

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

private:
	static uint8_t nextid;
	uint8_t id;
	uint8_t score;
};

#endif // !PLAYER_HPP