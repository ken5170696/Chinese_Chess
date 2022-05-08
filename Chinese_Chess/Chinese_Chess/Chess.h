#pragma once
class Board;
#include "GameHeader.h"
#include "Board.h"
#include <iostream>
#include <vector>

struct ChessMovement {
	std::vector<sf::Vector2f> validPath;
	std::vector<Chess*> validToEat;
};

class Chess
{
protected:
	int id;
	bool active;
	Team team;
	Characters chessCharacter;
	sf::Vector2f boardPosition;
	sf::Texture texture;
	sf::Sprite sprite;
	bool isPressed;

public:
	virtual void move() = 0;
	virtual ChessMovement findPath(const Board& board) = 0;

public:
	Chess(const Team& _team, int _id);
	void update(sf::RenderWindow& win, sf::Event ev);

	bool getActive() const { return active; };
	void setActive(const bool& _active) { active = _active; };
	sf::Vector2f getPosition() const { return boardPosition; };
	void setPosition(const sf::Vector2f& _pos) { boardPosition = _pos; };
	Team getTeam() const { return team; };
	void setTeam(const Team& _team) { team = _team; };
	Characters getCharacters() const { return chessCharacter; };
	sf::Sprite getSprite() const
	{
		return this->sprite;
	};
	void setSpritePosition(sf::Vector2f _pos) { sprite.setPosition(_pos); };

	

	bool getIsPressed() const
	{
		return this->isPressed;
	};
};

class King :public Chess
{
public:
	King(const Team& _team, int _id);
	virtual void move() override;
	virtual ChessMovement findPath(const Board& board) override;
};
class Advisors :public Chess
{
public:
	Advisors(const Team& _team, int _id);
	virtual void move() override;
	virtual ChessMovement findPath(const Board& board) override;
};
class Minister :public Chess
{
public:
	Minister(const Team& _team, int _id);
	virtual void move() override;
	virtual ChessMovement findPath(const Board& board) override;

};
class Chariots :public Chess
{
public:
	Chariots(const Team& _team, int _id);
	virtual void move() override;
	virtual ChessMovement findPath(const Board& board) override;

};
class Knights :public Chess
{
public:
	Knights(const Team& _team, int _id);
	virtual void move() override;
	virtual ChessMovement findPath(const Board& board) override;

};
class Cannons :public Chess
{
public:
	Cannons(const Team& _team, int _id);
	virtual void move() override;
	virtual ChessMovement findPath(const Board& board) override;

};
class Soldiers :public Chess
{
public:
	Soldiers(const Team& _team, int _id);
	virtual void move() override;
	virtual ChessMovement findPath(const Board& board) override;

};


class Factory {

public:
	Chess* getChess(const Characters& ch, const Team& team, int _id);
};