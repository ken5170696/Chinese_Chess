#include "Chess.h"

Chess::Chess(const Team& _team, int _id) 
	: chessCharacter()
{

	id = _id;
	active = true;
	team = _team;
	sprite.setScale(CHESS_IMG_SCALE, CHESS_IMG_SCALE);
	isPressed = false;


	if (id == -1)
		sprite.setColor(sf::Color(230, 0, 0, 170));
}

void Chess::update(sf::RenderWindow& win, sf::Event ev)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(win);
	//std::cout << mousePos.x << " " << mousePos.y << "\n";

	if (sprite.getGlobalBounds().contains(win.mapPixelToCoords(sf::Mouse::getPosition(win)))) {
		sprite.setScale(CHESS_IMG_SCALE + 0.01, CHESS_IMG_SCALE + 0.01);
		if (ev.type == sf::Event::MouseButtonPressed)
		{
			sprite.setScale(CHESS_IMG_SCALE + 0.01, CHESS_IMG_SCALE + 0.01);
			isPressed = true;
		}
		else {
			isPressed = false;
		}
	}
	else {
		sprite.setScale(CHESS_IMG_SCALE, CHESS_IMG_SCALE);
		isPressed = false;
	}

}


King::King(const Team& _team, int _id)
	:Chess(_team, _id)
{
	chessCharacter = Characters::King;
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_KING_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_KING_RED_IMG);
		sprite.setTexture(texture);
	}
	texture.setSmooth(true);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Advisors::Advisors(const Team& _team, int _id)
	: Chess(_team, _id)
{
	chessCharacter = Characters::Advisors;
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_ADVISORS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_ADVISORS_RED_IMG);
		sprite.setTexture(texture);
	}
	texture.setSmooth(true);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Minister::Minister(const Team& _team, int _id)
	: Chess(_team, _id)
{
	chessCharacter = Characters::Minister;
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_MINISTER_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_MINISTER_RED_IMG);
		sprite.setTexture(texture);
	}
	texture.setSmooth(true);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Chariots::Chariots(const Team& _team, int _id)
	:Chess(_team, _id)
{
	chessCharacter = Characters::Chariots;
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_CHARIOTS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_CHARIOTS_RED_IMG);
		sprite.setTexture(texture);
	}
	texture.setSmooth(true);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Knights::Knights(const Team& _team, int _id)
	:Chess(_team, _id)
{
	chessCharacter = Characters::Knights;
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_KNIGHTS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_KNIGHTS_RED_IMG);
		sprite.setTexture(texture);
	}
	texture.setSmooth(true);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Cannons::Cannons(const Team& _team, int _id)
	: Chess(_team, _id)
{
	chessCharacter = Characters::Cannons;
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_CANNONS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_CANNONS_RED_IMG);
		sprite.setTexture(texture);
	}
	texture.setSmooth(true);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}
Soldiers::Soldiers(const Team& _team, int _id)
	: Chess(_team, _id)
{
	chessCharacter = Characters::Soldiers;
	if (_team == Team::Black) {
		texture.loadFromFile(CHESS_SOLDIERS_BLACK_IMG);
		sprite.setTexture(texture);
	}
	else {
		texture.loadFromFile(CHESS_SOLDIERS_RED_IMG);
		sprite.setTexture(texture);
	}
	texture.setSmooth(true);
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
}

Chess* Factory::getChess(const Characters& ch, const Team& team, int _id)
{
	switch (ch)
	{
	case Characters::King: {
		return new King(team, _id);
	}
	case Characters::Advisors: {
		return new Advisors(team, _id);
	}case Characters::Minister: {
		return new Minister(team, _id);
	}case Characters::Chariots: {
		return new Chariots(team, _id);
	}case Characters::Knights: {
		return new Knights(team, _id);
	}case Characters::Cannons: {
		return new Cannons(team, _id);
	}case Characters::Soldiers: {
		return new Soldiers(team, _id);
	}
	}
	return nullptr;
}

void King::move()
{

}
ChessMovement King::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(-1,-1),
		sf::Vector2f(0,-1),
		sf::Vector2f(1,-1),
		sf::Vector2f(-1,0),
		sf::Vector2f(1,0),
		sf::Vector2f(1,-1),
		sf::Vector2f(1,0),
		sf::Vector2f(1,1),
	};
	struct ChessMovement chessMovement{};
	for (int i = 0; i < 8; i++) {
		sf::Vector2f tmpPos = boardPosition + direction[i];
		if (team == Team::Red) {
			// 限制在九宮格
			if (5 >= tmpPos.x && tmpPos.x >= 3 && 2 >= tmpPos.y && tmpPos.y >= 1) {
				// 能走
				if (board.getBoard()[tmpPos.y][tmpPos.x] == nullptr) {
					chessMovement.validPath.push_back(tmpPos);
				}
				else if (board.getBoard()[tmpPos.y][tmpPos.x]->getCharacters() > this->chessCharacter
						&& board.getBoard()[tmpPos.y][tmpPos.x]->getCharacters() != Characters::Soldiers) {
					chessMovement.validToEat.push_back(board.getBoard()[tmpPos.y][tmpPos.x]);
				}
			}
		}
		else {
			// 限制在九宮格
			if (5 >= tmpPos.x && tmpPos.x >= 3 && 9 >= tmpPos.y && tmpPos.y >= 7) {
				// 能走
				if (board.getBoard()[tmpPos.y][tmpPos.x] == nullptr) {
					chessMovement.validPath.push_back(tmpPos);
				}
				else if (board.getBoard()[tmpPos.y][tmpPos.x]->getCharacters() > this->chessCharacter
					&& board.getBoard()[tmpPos.y][tmpPos.x]->getCharacters() != Characters::Soldiers) {
					chessMovement.validToEat.push_back(board.getBoard()[tmpPos.y][tmpPos.x]);
				}
			}
		}
	}
	return chessMovement;
}
void Advisors::move()
{
}
ChessMovement Advisors::findPath(const Board& board)
{
	return ChessMovement();
}
void Minister::move()
{
}
ChessMovement Minister::findPath(const Board& board)
{
	return ChessMovement();
}
void Chariots::move()
{
}
ChessMovement Chariots::findPath(const Board& board)
{
	return ChessMovement();
}
void Knights::move()
{
}
ChessMovement Knights::findPath(const Board& board)
{
	return ChessMovement();
}
void Cannons::move()
{
}
ChessMovement Cannons::findPath(const Board& board)
{
	return ChessMovement();
}
void Soldiers::move()
{
}

ChessMovement Soldiers::findPath(const Board& board)
{
	return ChessMovement();
}
