#pragma once
class Chess;
#include <vector>
#include <vector>
#include "Chess.h"
/*
  0 1 2 3 4 5 6 7 8
0  _ _ _ _ _ _ _ _
  | | | |\|/| | | |
1  ─ ─ ─ ─X─ ─ ─ ─
  | | | |/|\| | | |
2  ─*─ ─ ─ ─ ─ ─*─
  | | | | | | | | |
3 *─ ─*─ ─*─ ─*─ ─*
  | | | | | | | | | Red
4  ‾ ‾ ‾ ‾ ‾ ‾ ‾ ‾
  |               |
5  _ _ _ _ _ _ _ _
  | | | | | | | | | Black
6 *─ ─*─ ─*─ ─*─ ─*
  | | | | | | | | |
7  ─*─ ─ ─ ─ ─ ─*─
  | | | |\|/| | | |
8  ─ ─ ─ ─X─ ─ ─ ─
  | | | |/|\| | | |
9  ‾ ‾ ‾ ‾ ‾ ‾ ‾ ‾
*/
class Board : public sf::Drawable
{
private:
	std::vector<std::vector<Chess*>> boardArray;
	sf::Texture textTure;
	sf::Sprite sprite;

public:
	Board();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getBoardSize() const;
	std::vector<std::vector<Chess*>> getBoard() const;
	void setBoard(Chess* startChess, sf::Vector2f goalPos);
	void update(const std::vector<Chess*>& playerBlack, const std::vector<Chess*>& playerRed);

	void printChessPos();

	void setSpritePosition(sf::Vector2f _pos);
	sf::Vector2f BoardToWindowPosition(sf::Vector2f boardPosition);
	sf::Vector2f WindowToBoardPosition(sf::Vector2f windowPosition);
};
//class Chess;
//class Player;
//#include <vector>
//
//#include "GameHeader.h"
//#include "Chess.h"
//#include "Player.h"
//
//class Board
//{
//
//private:
//	std::vector <std::vector<Chess*>> boardArray;
//	sf::Texture textTure;
//	sf::Sprite sprite;
//	/*Player playerBlackExit;
//	Player playerRedExit;*/
//
//public:
//	Board();
//	void update(const Player& playerBlack, const Player& playerRed);
//	void resetBoardArray();
//	sf::Sprite& getSprite();
//	sf::Vector2f getBoardSize() const;
//	std::vector<std::vector<Chess*>> getBoard() const { return boardArray; };
//	void printBoard();
//	void setBoard(Chess* startChess, sf::Vector2f goalPos);
//	void setSpritePosition(const sf::Vector2f& pos);
//	void printChessPos();
//};