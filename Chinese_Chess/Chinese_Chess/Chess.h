#pragma once

#include "GameHeader.h"
class Chess
{
private:
	sf::Vector2f pos;

public:
	virtual void move() = 0;
};

