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

class King :public Chess
{
public:
	virtual void move() override;
};
class Advisors :public Chess
{
public:
	virtual void move() override;
};
class Minister :public Chess
{
public:
	virtual void move() override;

};
class Chariots :public Chess
{
public:
	virtual void move() override;

};
class Knights :public Chess
{
public:
	virtual void move() override;

};
class Cannons :public Chess
{
public:
	virtual void move() override;

};
class Soldiers :public Chess
{
public:
	virtual void move() override;
	
};


class Factory {
	//¤u¼tªð¦^°Ó«~
public:
	Chess* getChess(Characters ch)
	{
		switch (ch)
		{
		case Characters::King:
			return new King;
		case Characters::Advisors:
			return new Advisors;
		case Characters::Minister:
			return new Minister;
		case Characters::Chariots:
			return new Chariots;
		case Characters::Knights:
			return new Knights;
		case Characters::Cannons:
			return new Cannons;
		case Characters::Soldiers:
			return new Soldiers;
		}
	}
};