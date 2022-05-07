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
	//工廠返回商品
public:
	virtual Chess* getProduct() = 0;
};