#pragma once

#include <vector>

#include "GameHeader.h"
#include "Chess.h"


class Board
{

private:
	std::vector <std::vector<Chess*>> boardArray;
	sf::Texture textTure;
	sf::Sprite sprite;

public:
	Board();
	sf::Sprite& getSprite();
	sf::Vector2f getBoardSize() const;
	void setSpritePosition(const sf::Vector2f& pos);
};

