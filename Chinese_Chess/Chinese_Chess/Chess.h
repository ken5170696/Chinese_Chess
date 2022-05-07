#pragma once

#include "GameHeader.h"

class Chess
{
private:
	sf::Vector2f pos;
	bool active;
	Team team;

protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Chess(const Team& _team);
	virtual void move() = 0;

	bool getActive() const { return active; };
	void setActive(const bool& _active) { active = _active; };

	sf::Vector2f getPosition() const { return pos; };
	void setPosition(const sf::Vector2f& _pos) { pos = _pos; };

	Team getTeam() const { return team; };
	void setTeam(const Team& _team) { team = _team; };

	sf::Sprite getSprite() const
	{
		return this->sprite;
	};
	void setSpritePosition(sf::Vector2f _pos) { sprite.setPosition(_pos); };
};

class King :public Chess
{
public:
	King(const Team& _team);
	virtual void move() override;
};
class Advisors :public Chess
{
public:
	Advisors(const Team& _team);
	virtual void move() override;
};
class Minister :public Chess
{
public:
	Minister(const Team& _team);
	virtual void move() override;

};
class Chariots :public Chess
{
public:
	Chariots(const Team& _team);
	virtual void move() override;

};
class Knights :public Chess
{
public:
	Knights(const Team& _team);
	virtual void move() override;

};
class Cannons :public Chess
{
public:
	Cannons(const Team& _team);
	virtual void move() override;

};
class Soldiers :public Chess
{
public:
	Soldiers(const Team& _team);
	virtual void move() override;

};


class Factory {

public:
	Chess* getChess(const Characters& ch, const Team& team);
};