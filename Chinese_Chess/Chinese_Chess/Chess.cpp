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

void King::move(const sf::Vector2f& pos, const Board& board)
{
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
	boardPosition = pos;
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
}
ChessMovement King::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(0,-1),
		sf::Vector2f(-1,0),
		sf::Vector2f(1,0),
		sf::Vector2f(0,1),
	};
	struct ChessMovement chessMovement {};
	for (int i = 0; i < 4; i++) {
		sf::Vector2f goalPos = boardPosition + direction[i];
		if (team == Team::Red) {
			// 限制在九宮格
			if (5 >= goalPos.x && goalPos.x >= 3 && 2 >= goalPos.y && goalPos.y >= 0) {
				// 能走
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//若目標Pos的不為空 && 隊伍不一樣 && 角色不為兵或卒 則可吃
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() != Characters::Soldiers) {
					chessMovement.validToEat.push_back(board.getBoard()[goalPos.y][goalPos.x]);
				}
			}
		}
		else {
			// 限制在九宮格
			if (5 >= goalPos.x && goalPos.x >= 3 && 9 >= goalPos.y && goalPos.y >= 7) {
				// 能走
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//若目標Pos的不為空 && 隊伍不一樣 && 角色不為兵或卒 則可吃
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() != Characters::Soldiers) {
					chessMovement.validToEat.push_back(board.getBoard()[goalPos.y][goalPos.x]);
				}
			}
		}
	}
	return chessMovement;
}
void Advisors::move(const sf::Vector2f& pos, const Board& board)
{
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
	boardPosition = pos;
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
}
ChessMovement Advisors::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(-1,-1),
		sf::Vector2f(1,1),
		sf::Vector2f(1,-1),
		sf::Vector2f(-1,1),
	};
	struct ChessMovement chessMovement {};
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f goalPos = boardPosition + direction[i];
		if (team == Team::Red) {
			// 限制在九宮格
			if (5 >= goalPos.x && goalPos.x >= 3 && 2 >= goalPos.y && goalPos.y >= 0) {
				// 能走
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//若目標Pos的不為空 && 隊伍不一樣 則可吃
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam()) {
					chessMovement.validToEat.push_back(board.getBoard()[goalPos.y][goalPos.x]);
				}
			}
		}
		else {
			// 限制在九宮格
			if (5 >= goalPos.x && goalPos.x >= 3 && 9 >= goalPos.y && goalPos.y >= 7) {
				// 能走
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//若目標Pos的不為空 && 隊伍不一樣 則可吃
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam()) {
					chessMovement.validToEat.push_back(board.getBoard()[goalPos.y][goalPos.x]);
				}
			}
		}

	}
	return chessMovement;
}
void Minister::move(const sf::Vector2f& pos, const Board& board)
{
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
	boardPosition = pos;
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
}
ChessMovement Minister::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(2,2),
		sf::Vector2f(-2,2),
		sf::Vector2f(2,-2),
		sf::Vector2f(-2,-2),
	};
	const std::vector<sf::Vector2f> throughDirection{
		sf::Vector2f(1,1),
		sf::Vector2f(-1,1),
		sf::Vector2f(1,-1),
		sf::Vector2f(-1,-1),
	};
	struct ChessMovement chessMovement {};
	for (int i = 0; i < 4; i++) {
		sf::Vector2f goalPos = boardPosition + direction[i];
		sf::Vector2f throughPos = boardPosition + throughDirection[i];
		if (team == Team::Red) {
			// 限制不越過楚河漢界
			if (8 >= goalPos.x && goalPos.x >= 0 && 4 >= goalPos.y && goalPos.y >= 0) {
				// 能走
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr && board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//若目標Pos的不為空 && 隊伍不一樣 && 路上沒棋子 則可吃
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validToEat.push_back(board.getBoard()[goalPos.y][goalPos.x]);
				}
			}
		}
		else {
			// 限制不越過楚河漢界
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 5) {
				// 能走
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//若目標Pos的不為空 && 隊伍不一樣 && 路上沒棋子 則可吃
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validToEat.push_back(board.getBoard()[goalPos.y][goalPos.x]);
				}
			}
		}

	}

	return chessMovement;
}
void Chariots::move(const sf::Vector2f& pos, const Board& board)
{
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
	boardPosition = pos;
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
}
ChessMovement Chariots::findPath(const Board& board)
{

	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(0,-1),
		sf::Vector2f(1,0),
		sf::Vector2f(0,1),
		sf::Vector2f(-1,0),
	};
	bool upStop = false, rightStop = false, downStop = false, leftStop = false;
	int multiple = 1;
	struct ChessMovement chessMovement {};
	while (!(upStop && rightStop && downStop && leftStop))
	{
		for (int i = 0; i < 4; i++)
		{
			sf::Vector2f dxy(direction[i].x * multiple, direction[i].y * multiple);
			sf::Vector2f goalPos = boardPosition + dxy;
			if (i == 0 && upStop == true)
				continue;
			else if (i == 1 && rightStop == true)
				continue;
			else if (i == 2 && downStop == true)
				continue;
			else if (i == 3 && leftStop == true)
				continue;

			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0) 
			{
				// 能走
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//若目標Pos的不為空 && 隊伍不一樣 則可吃
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
				{
					if (i == 0)
						upStop = true;
					else if (i == 1)
						rightStop = true;
					else if (i == 2)
						downStop = true;
					else if (i == 3)
						leftStop = true;
					chessMovement.validToEat.push_back(board.getBoard()[goalPos.y][goalPos.x]);
				}
				//若目標Pos的不為空 && 隊伍一樣 紀錄狀態
				else
				{
					if (i == 0)
						upStop = true;
					else if (i == 1)
						rightStop = true;
					else if (i == 2)
						downStop = true;
					else if (i == 3)
						leftStop = true;
				}
				
			}
			//超過範圍 紀錄狀態
			else
			{
				if (i == 0)
					upStop = true;
				else if (i == 1)
					rightStop = true;
				else if (i == 2)
					downStop = true;
				else if(i == 3)
					leftStop = true;
			}
			
		}
		multiple++;
	}
	std::cout << chessMovement.validPath.size() << std::endl;
	return chessMovement;
}
void Knights::move(const sf::Vector2f& pos, const Board& board)
{
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
	boardPosition = pos;
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
}
ChessMovement Knights::findPath(const Board& board)
{
	return ChessMovement();
}
void Cannons::move(const sf::Vector2f& pos, const Board& board)
{
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
	boardPosition = pos;
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
}
ChessMovement Cannons::findPath(const Board& board)
{
	return ChessMovement();
}
void Soldiers::move(const sf::Vector2f& pos, const Board& board)
{
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
	boardPosition = pos;
	board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
}

ChessMovement Soldiers::findPath(const Board& board)
{
	return ChessMovement();
}
