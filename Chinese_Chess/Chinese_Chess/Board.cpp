#include "Board.h"

Board::Board()
{
	textTure.loadFromFile(CHECKBOARD_IMG);
	sprite.setTexture(textTure);
	sprite.setScale(CHESSBOARD_IMG_SCALE, CHESSBOARD_IMG_SCALE);
	boardArray = std::vector <std::vector<Chess*>>(10, std::vector<Chess*>(9, nullptr));
}
void Board::setSpritePosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
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
		int x = tmpChess->getPosition().x;
		int y = tmpChess->getPosition().y;
		boardArray[y][x] = tmpChess;
	}
	for (auto& tmpChess : playerRed.getChessList())
	{
		int x = tmpChess->getPosition().x;
		int y = tmpChess->getPosition().y;
		boardArray[y][x] = tmpChess;
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
