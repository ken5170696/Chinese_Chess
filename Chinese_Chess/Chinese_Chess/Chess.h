#pragma once
class Board;
#include "GameHeader.h"
#include "Board.h"
#include <iostream>
#include <vector>

class Chess
	: public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
private:
	enum class ButtonStatus
	{
		hover = 1,
		pressed = 1 << 1,
	};

protected:
	int id;
	Team team;
	Characters chessCharacter;
	sf::Vector2f boardPosition;
	sf::Texture texture;
	sf::Sprite sprite;
	unsigned int buttonStatus;
	bool active;
public:
	virtual void move(Chess* goalChess, const Board& board) = 0;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Chess(const Team& _team, int _id);
	void update(const sf::RenderWindow& win);
	void handleEvent(sf::RenderWindow& win);

	bool getActive() const { return active; };
	void setActive(const bool& _active) { active = _active; };

	sf::Vector2f getBoardPosition() const { return boardPosition; };
	void setBoardPosition(const sf::Vector2f& _pos) { boardPosition = _pos; };

	Team getTeam() const { return team; };
	void setTeam(const Team& _team) { team = _team; };

	Characters getCharacters() const { return chessCharacter; };

	sf::Sprite getSprite() const { return this->sprite; };


	void setSpritePosition(const sf::Vector2f& _pos) { sprite.setPosition(_pos); };

	int getId() { return id; };

	bool isPressed() const { 
		return (buttonStatus >> 1) & 1;
	};
	bool isHover() const {
		return (buttonStatus >> 0) & 1;
	};
};

class King :public Chess
{
public:
	King(const Team& _team, int _id);
	virtual void move(Chess* goalChess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;
};
class Advisors :public Chess
{
public:
	Advisors(const Team& _team, int _id);
	virtual void move(Chess* goalChess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;
};
class Minister :public Chess
{
public:
	Minister(const Team& _team, int _id);
	virtual void move(Chess* goalChess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Chariots :public Chess
{
public:
	Chariots(const Team& _team, int _id);
	virtual void move(Chess* goalChess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Knights :public Chess
{
public:
	Knights(const Team& _team, int _id);
	virtual void move(Chess* goalChess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Cannons :public Chess
{
public:
	Cannons(const Team& _team, int _id);
	virtual void move(Chess* goalChess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};
class Soldiers :public Chess
{
public:
	Soldiers(const Team& _team, int _id);
	virtual void move(Chess* goalChess, const Board& board) override;
	virtual std::vector<sf::Vector2f> findPath(const Board& board) override;

};

class Factory {

public:
	Chess* getChess(const Characters& ch, const Team& team, int _id);
};