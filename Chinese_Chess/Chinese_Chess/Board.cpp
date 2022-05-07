#include "Board.h"

Board::Board()
{
	textTure.loadFromFile(CHECKBOARD_IMG);
	sprite.setTexture(textTure);
	sprite.setScale(CHESSBOARD_IMG_SCALE, CHESSBOARD_IMG_SCALE);
}

void Board::setSpritePosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
}

sf::Sprite& Board::getSprite()
{
	return this->sprite;
}

sf::Vector2f Board::getBoardSize() const
{
	return sf::Vector2f(sprite.getScale().x * sprite.getTexture()->getSize().x, sprite.getScale().y * sprite.getTexture()->getSize().y);
}
