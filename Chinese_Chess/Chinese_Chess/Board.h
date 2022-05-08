#pragma once
class Chess;
class Player;
#include <vector>

#include "GameHeader.h"
#include "Chess.h"
#include "Player.h"

/*
  0 1 2 3 4 5 6 7 8
0  _ _ _ _ _ _ _ _
  | | | |\|/| | | |
1  ─ ─ ─ ─X─ ─ ─ ─
  | | | |/|\| | | |
2  ─*─ ─ ─ ─ ─ ─*─
  | | | | | | | | |
3 *─ ─*─ ─*─ ─*─ ─*
  | | | | | | | | |
4  ‾ ‾ ‾ ‾ ‾ ‾ ‾ ‾
  |               |
5  _ _ _ _ _ _ _ _
  | | | | | | | | |
6 *─ ─*─ ─*─ ─*─ ─*
  | | | | | | | | |
7  ─*─ ─ ─ ─ ─ ─*─
  | | | |\|/| | | |
8  ─ ─ ─ ─X─ ─ ─ ─
  | | | |/|\| | | |
9  ‾ ‾ ‾ ‾ ‾ ‾ ‾ ‾
*/
class Board
{

private:
	std::vector <std::vector<Chess*>> boardArray;
	sf::Texture textTure;
	sf::Sprite sprite;

public:
	Board();
	void update(const Player& playerBlack, const Player& playerRed);
	void resetBoardArray();
	sf::Sprite& getSprite();
	sf::Vector2f getBoardSize() const;
	std::vector<std::vector<Chess*>> getBoard() const { return boardArray;	};
	void setSpritePosition(const sf::Vector2f& pos);
};

