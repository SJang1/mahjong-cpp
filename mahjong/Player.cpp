#include "std.h"

Player::Player(string _name) : name(_name), Reach(false), Win(false)
{
}
string Player::getName() const
{
	return name;
}
bool Player::getReach() const
{
	return Reach;
}

bool Player::getWin() const
{
	return Win;
}

void Player::setReach()
{
	Reach = true;
}

void Player::setWin()
{
	Win = true;
}