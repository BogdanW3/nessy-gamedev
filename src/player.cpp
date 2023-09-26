#include "../h/player.hpp"

uint8_t Player::nextid = 0;

void Player::start()
{
	id = nextid++;
	score = 0;
	position = Vec2D(0, 0);
	facing = UP;
}

uint8_t Player::getTileX(signed char offset)
{
	return (position.x + offset) >> position_multiplier_shift;
}

uint8_t Player::getTileY(signed char offset)
{
	return (position.y + offset) >> position_multiplier_shift;
}

void Player::increaseScore()
{
	score++;
}

void Player::decreaseScore()
{
	score--;
}

void Player::resetScore()
{
	score = 0;
}

uint8_t Player::getScore() const
{
	return score;
}

uint8_t Player::getID() const
{
	return id;
}

void Player::reset()
{
	nextid = 0;
}

Vec2D Player::getAim() const
{
	Vec2D aim(0, 0);
	switch (facing)
	{
	case UP:
		aim.x = 0;
		aim.y = -3;
		break;
	case DOWN:
		aim.x = 0;
		aim.y = 3;
		break;
	case LEFT:
		aim.x = -3;
		aim.y = 0;
		break;
	case RIGHT:
		aim.x = 3;
		aim.y = 0;
		break;
	}
	return aim;
}