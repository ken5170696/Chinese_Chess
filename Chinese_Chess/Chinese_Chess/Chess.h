#pragma once
class Board;
#include "GameHeader.h"
#include "Board.h"
#include <iostream>
#include <vector>

class Chess
	: public sf::Transformable, public sf::Drawable, private sf::NonCopyable
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
	virtual void move(Chess* chess, const Board& board) = 0;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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

	sf::Sprite getSprite() const { return this->sprite; };


	void setSpritePosition(sf::Vector2f _pos) { sprite.setPosition(_pos); };

	int getId() { return id; };

	void resetIsPressed() { isPressed = false; };
	bool getIsPressed() const { return this->isPressed; };


};

class King :public Chess
{
public:
	King(const Team& _team, int _id);
	virtual void move(Chess* chess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;
};
class Advisors :public Chess
{
public:
	Advisors(const Team& _team, int _id);
	virtual void move(Chess* chess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;
};
class Minister :public Chess
{
public:
	Minister(const Team& _team, int _id);
	virtual void move(Chess* chess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Chariots :public Chess
{
public:
	Chariots(const Team& _team, int _id);
	virtual void move(Chess* chess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Knights :public Chess
{
public:
	Knights(const Team& _team, int _id);
	virtual void move(Chess* chess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Cannons :public Chess
{
public:
	Cannons(const Team& _team, int _id);
	virtual void move(Chess* chess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Soldiers :public Chess
{
public:
	Soldiers(const Team& _team, int _id);
	virtual void move(Chess* chess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};

class Factory {

public:
	Chess* getChess(const Characters& ch, const Team& team, int _id);
};