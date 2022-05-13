#include "Board.h"

Board::Board()
{
	textTure.loadFromFile(CHECKBOARD_IMG);
	sprite.setTexture(textTure);
	sprite.setScale(CHESSBOARD_IMG_SCALE, CHESSBOARD_IMG_SCALE);
	boardArray = std::vector<std::vector<Chess*>>(10, std::vector<Chess*>(9, nullptr));
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
sf::Vector2f Board::getBoardSize() const
{
	return sf::Vector2f(sprite.getScale().x * sprite.getTexture()->getSize().x, sprite.getScale().y * sprite.getTexture()->getSize().y);
}
std::vector<std::vector<Chess*>> Board::getBoard() const
{
	return boardArray;
}
void Board::setBoard(Chess* startChess, sf::Vector2f goalPos)
{
	boardArray[startChess->getPosition().y][startChess->getPosition().x] = nullptr;
	boardArray[goalPos.y][goalPos.x] = startChess;
}
void Board::update(const std::vector<Chess*>& playerBlack, const std::vector<Chess*>& playerRed)
{
	boardArray = std::vector<std::vector<Chess*>>(10, std::vector<Chess*>(9, nullptr));
	for (const auto& tmpChess : playerBlack) {
		const sf::Vector2f& tmpPos = tmpChess->getBoardPosition();
		boardArray[tmpPos.y][tmpPos.x] = tmpChess;
	}
	for (const auto& tmpChess : playerRed) {
		const sf::Vector2f& tmpPos = tmpChess->getBoardPosition();
		boardArray[tmpPos.y][tmpPos.x] = tmpChess;
	}
}
void Board::setSpritePosition(sf::Vector2f _pos)
{
	sprite.setPosition(_pos);
}
//Board::Board()
//{
//	textTure.loadFromFile(CHECKBOARD_IMG);
//	sprite.setTexture(textTure);
//	sprite.setScale(CHESSBOARD_IMG_SCALE, CHESSBOARD_IMG_SCALE);
//	boardArray = std::vector <std::vector<Chess*>>(10, std::vector<Chess*>(9, nullptr));
//}
//void Board::printBoard()
//{
//	for (auto& y : boardArray)
//	{
//		for (auto& x : y)
//		{
//			if (x == nullptr)
//				std::cout << "X\t";
//			else
//				std::cout << x->getId() << "\t";
//
//		}
//		std::cout << "\n";
//	}
//}
//void Board::setBoard(Chess *startChess , sf::Vector2f goalPos)
//{
//	boardArray[startChess->getPosition().y][startChess->getPosition().x] = nullptr;
//	boardArray[goalPos.y][goalPos.x] = startChess;
//}
//void Board::setSpritePosition(const sf::Vector2f& pos)
//{
//	sprite.setPosition(pos);
//}
//
//void Board::printChessPos()
//{
//	for (auto& y : this->boardArray)
//	{
//		for (auto& x : y)
//		{
//			if (x == nullptr)
//			{
//				std::cout << "X\t";
//				continue;
//			}
//				
//			std::cout << x->getId() << "\t";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << "==========================\n";
//}
//
//sf::Sprite& Board::getSprite()
//{
//	return this->sprite;
//}
//void Board::update(const Player& playerBlack, const Player& playerRed)
//{
//	resetBoardArray();
//	for (auto& tmpChess : playerBlack.getChessList())
//	{
//		if (tmpChess->getActive()) {
//			int x = tmpChess->getPosition().x;
//			int y = tmpChess->getPosition().y;
//			boardArray[y][x] = tmpChess;
//		}
//	}
//	for (auto& tmpChess : playerRed.getChessList())
//	{
//		if (tmpChess->getActive()) {
//			int x = tmpChess->getPosition().x;
//			int y = tmpChess->getPosition().y;
//			boardArray[y][x] = tmpChess;
//		}
//	}
//}
//void Board::resetBoardArray()
//{
//	boardArray = std::vector <std::vector<Chess*>>(10, std::vector<Chess*>(9, nullptr));
//}
//
////sf::Vector2f Board::getBoardSize() const
//{
//	return sf::Vector2f(sprite.getScale().x * sprite.getTexture()->getSize().x, sprite.getScale().y * sprite.getTexture()->getSize().y);
//}

sf::Vector2f Board::BoardToWindowPosition(sf::Vector2f boardPosition)
{
	sf::Vector2f windowPosition;
	int x = (getBoardSize().x / 8) * boardPosition.x + sprite.getPosition().x;
	int y = (getBoardSize().y / 9) * boardPosition.y + sprite.getPosition().y;
	windowPosition = sf::Vector2f(x, y);

	return windowPosition;
}

sf::Vector2f Board::WindowToBoardPosition(sf::Vector2f windowPosition)
{
	sf::Vector2f boardPosition;
	int x = (windowPosition.x - (sprite.getPosition().x - getBoardSize().x / 16)) / (getBoardSize().x / 8);
	int y = (windowPosition.y - (sprite.getPosition().y - getBoardSize().x / 18)) / (getBoardSize().y / 9);
	boardPosition = sf::Vector2f(x, y);
	return boardPosition;
}
