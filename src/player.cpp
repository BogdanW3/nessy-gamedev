#include "../h/player.hpp"

uint8_t Player::nextid = 0;

Player::Player(): id(nextid++), score(0) {}

void Player::increaseScore()
{
	score++;
}

void Player::decreaseScore()
{
	score--;
}

uint8_t Player::getScore() const
{
	return score;
}

uint8_t Player::getId() const
{
	return id;
}