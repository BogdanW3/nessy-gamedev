#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifndef NONES
#include "../lib/stdint.hpp"
#else
#include <stdint.h>
#endif

class Player {
public:
	Player();
	void increaseScore();
	void decreaseScore();
	uint8_t getScore() const;
	uint8_t getId() const;
	static void reset();
	struct Vec2D {
		constexpr Vec2D(uint16_t x, uint16_t y): x(x), y(y) {}
		uint16_t x;
		uint16_t y;
	};

	Vec2D getAim() const;

private:
	static uint8_t nextid;
	uint8_t id;
	uint8_t score;
	Vec2D position;

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Direction facing = UP;

	friend class Arena;
};

#endif // !PLAYER_HPP