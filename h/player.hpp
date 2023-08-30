#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../lib/stdint.hpp"

class Player {
public:
	Player();
	void increaseScore();
	void decreaseScore();
	uint8_t getScore() const;
	uint8_t getId() const;
private:
	static uint8_t nextid;
	uint8_t id;
	uint8_t score;
};

#endif // !PLAYER_HPP