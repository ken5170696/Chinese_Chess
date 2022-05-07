#pragma once

#include "GameHeader.h"

enum class Characters
{
	King,
	Advisors,
	Minister,
	Chariots,
	Knights,
	Cannons,
	Soldiers,
};

class Chess
{
private:
	sf::Vector2f pos;

public:
	virtual void move() = 0;
};

class Factory {
	//�u�t��^�ӫ~
public:
	virtual Chess* getProduct() = 0;
};