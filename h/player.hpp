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
private:
	static uint8_t nextid;
	uint8_t id;
	uint8_t score;
	struct {
		uint8_t x;
		uint8_t y;
	} position;
	friend class Arena;
};

#endif // !PLAYER_HPP