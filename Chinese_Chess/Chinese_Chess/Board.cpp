#include "Board.h"

Board::Board()
{
	textTure.loadFromFile(CHECKBOARD_IMG);
	sprite.setTexture(textTure);
	sprite.setScale(CHESSBOARD_IMG_SCALE, CHESSBOARD_IMG_SCALE);
	boardArray = std::vector <std::vector<Chess*>>(10, std::vector<Chess*>(9, nullptr));
}
void Board::printBoard()
{
	for (auto& y : boardArray)
	{
		for (auto& x : y)
		{
			if (x == nullptr)
				std::cout << "X\t";
			else
				std::cout << x->getId() << "\t";

		}
		std::cout << "\n";
	}
}
void Board::setBoard(Chess *startChess , sf::Vector2f goalPos)
{
	boardArray[startChess->getPosition().y][startChess->getPosition().x] = nullptr;
	boardArray[goalPos.y][goalPos.x] = startChess;
}
void Board::setSpritePosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

void Board::printChessPos()
{
	for (auto& y : this->boardArray)
	{
		for (auto& x : y)
		{
			if (x == nullptr)
			{
				std::cout << "X\t";
				continue;
			}
				
			std::cout << x->getId() << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "==========================\n";
}

sf::Sprite& Board::getSprite()
{
	return this->sprite;
}
void Board::update(const Player& playerBlack, const Player& playerRed)
{
	resetBoardArray();
	for (auto& tmpChess : playerBlack.getChessList())
	{
		if (tmpChess->getActive()) {
			int x = tmpChess->getPosition().x;
			int y = tmpChess->getPosition().y;
			boardArray[y][x] = tmpChess;
		}
	}
	for (auto& tmpChess : playerRed.getChessList())
	{
		if (tmpChess->getActive()) {
			int x = tmpChess->getPosition().x;
			int y = tmpChess->getPosition().y;
			boardArray[y][x] = tmpChess;
		}
	}
}
void Board::resetBoardArray()
{
	boardArray = std::vector <std::vector<Chess*>>(10, std::vector<Chess*>(9, nullptr));
}

sf::Vector2f Board::getBoardSize() const
{
	return sf::Vector2f(sprite.getScale().x * sprite.getTexture()->getSize().x, sprite.getScale().y * sprite.getTexture()->getSize().y);
}
