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
		else
		{
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
	active = true;
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
	active = true;
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
	active = true;
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
	active = true;
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
	active = true;
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
	active = true;
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
	active = true;
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

void King::move(Chess* chess, const Board& board)
{
	sf::Vector2f goalPos = chess->getPosition();

	//�Y�ؼЦ�m����
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
		boardPosition = goalPos;
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
	}
	//�Y�ؼЦ�m������
	else
	{
		//�Y�ؼЦ�m���Ѥl�s��
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
		//�Y�ؼЦ�m���Ѥl�w��
		else
		{
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
	}

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
			// ����b�E�c��
			if (5 >= goalPos.x && goalPos.x >= 3 && 2 >= goalPos.y && goalPos.y >= 0) {
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�Y�ؼ�Pos�������� && ����@�� && ���⤣���L�Ψ� �h�i�Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() != Characters::Soldiers)
				{
					chessMovement.validPath.push_back(goalPos);
				}
			}
		}
		else {
			// ����b�E�c��
			if (5 >= goalPos.x && goalPos.x >= 3 && 9 >= goalPos.y && goalPos.y >= 7) {
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�Y�ؼ�Pos�������� && ����@�� && ���⤣���L�Ψ� �h�i�Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() != Characters::Soldiers) {
					chessMovement.validPath.push_back(goalPos);
				}
			}
		}
	}
	return chessMovement;
}
void Advisors::move(Chess* chess, const Board& board)
{
	sf::Vector2f goalPos = chess->getPosition();

	//�Y�ؼЦ�m����
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
		boardPosition = goalPos;
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
	}
	//�Y�ؼЦ�m������
	else
	{
		//�Y�ؼЦ�m���Ѥl�s��
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
		//�Y�ؼЦ�m���Ѥl�w��
		else
		{
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
	}

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
			// ����b�E�c��
			if (5 >= goalPos.x && goalPos.x >= 3 && 2 >= goalPos.y && goalPos.y >= 0) {
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�Y�ؼ�Pos�������� && ����@�� �h�i�Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam()) {
					chessMovement.validPath.push_back(goalPos);
				}
			}
		}
		else {
			// ����b�E�c��
			if (5 >= goalPos.x && goalPos.x >= 3 && 9 >= goalPos.y && goalPos.y >= 7) {
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�Y�ؼ�Pos�������� && ����@�� �h�i�Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam()) {
					chessMovement.validPath.push_back(goalPos);
				}
			}
		}

	}
	return chessMovement;
}
void Minister::move(Chess* chess, const Board& board)
{
	sf::Vector2f goalPos = chess->getPosition();

	//�Y�ؼЦ�m����
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
		boardPosition = goalPos;
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
	}
	//�Y�ؼЦ�m������
	else
	{
		//�Y�ؼЦ�m���Ѥl�s��
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
		//�Y�ؼЦ�m���Ѥl�w��
		else
		{
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
	}

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
			// ����V�L���e�~��
			if (8 >= goalPos.x && goalPos.x >= 0 && 4 >= goalPos.y && goalPos.y >= 0) {
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr && board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�Y�ؼ�Pos�������� && ����@�� && ���W�S�Ѥl �h�i�Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);;
				}
			}
		}
		else {
			// ����V�L���e�~��
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 5) {
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�Y�ؼ�Pos�������� && ����@�� && ���W�S�Ѥl �h�i�Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);;
				}
			}
		}

	}

	return chessMovement;
}
void Chariots::move(Chess* chess, const Board& board)
{
	sf::Vector2f goalPos = chess->getPosition();

	//�Y�ؼЦ�m����
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
		boardPosition = goalPos;
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
	}
	//�Y�ؼЦ�m������
	else
	{
		//�Y�ؼЦ�m���Ѥl�s��
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
		//�Y�ؼЦ�m���Ѥl�w��
		else
		{
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
	}

}
ChessMovement Chariots::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(0,-1),
		sf::Vector2f(1,0),
		sf::Vector2f(0,1),
		sf::Vector2f(-1,0),
	};

	struct ChessMovement chessMovement {};
	for (int i = 0;i < 4; i++)
	{
		for (int multiple = 1;multiple <= 9;multiple++)
		{
			sf::Vector2f dxy(direction[i].x * multiple, direction[i].y * multiple);
			sf::Vector2f goalPos = boardPosition + dxy;
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
			{
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�Y�ؼ�Pos�������� && ����@�� �h�i�Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
				{
					chessMovement.validPath.push_back(goalPos);
					break;
				}
				//�Y�ؼ�Pos�������� && ����@�� ���X�j��
				else
					break;
			}
			//�W�X�d�� ���X�j��
			else
				break;
		}
	}
	return chessMovement;
}
void Knights::move(Chess* chess, const Board& board)
{
	sf::Vector2f goalPos = chess->getPosition();

	//�Y�ؼЦ�m����
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
		boardPosition = goalPos;
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
	}
	//�Y�ؼЦ�m������
	else
	{
		//�Y�ؼЦ�m���Ѥl�s��
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
		//�Y�ؼЦ�m���Ѥl�w��
		else
		{
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
	}

}
ChessMovement Knights::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(-1,-2),
		sf::Vector2f(1,-2),
		sf::Vector2f(2,-1),
		sf::Vector2f(2,1),
		sf::Vector2f(1,2),
		sf::Vector2f(-1,2),
		sf::Vector2f(-2,1),
		sf::Vector2f(-2,-1),
	};
	const std::vector<sf::Vector2f> throughDirection{
		sf::Vector2f(0,-1),
		sf::Vector2f(0,-1),
		sf::Vector2f(1,0),
		sf::Vector2f(1,0),
		sf::Vector2f(0,1),
		sf::Vector2f(0,1),
		sf::Vector2f(-1,0),
		sf::Vector2f(-1,0),
	};
	struct ChessMovement chessMovement {};
	for (int i = 0; i < 8; i++)
	{
		sf::Vector2f goalPos = boardPosition + direction[i];
		sf::Vector2f throughPos = boardPosition + throughDirection[i];

		if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
		{
			// �ਫ
			if (board.getBoard()[goalPos.y][goalPos.x] == nullptr && board.getBoard()[throughPos.y][throughPos.x] == nullptr)
			{
				chessMovement.validPath.push_back(goalPos);
			}
			//�Y�ؼ�Pos�������� && ����@�� && ���W�S�Ѥl �h�i�Y
			else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
				board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
				board.getBoard()[throughPos.y][throughPos.x] == nullptr)
			{
				chessMovement.validPath.push_back(goalPos);;
			}
		}
	}

	return chessMovement;
}
void Cannons::move(Chess* chess, const Board& board)
{
	sf::Vector2f goalPos = chess->getPosition();

	//�Y�ؼЦ�m����
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
		boardPosition = goalPos;
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
	}
	//�Y�ؼЦ�m������
	else
	{
		//�Y�ؼЦ�m���Ѥl�s��
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
		//�Y�ؼЦ�m���Ѥl�w��
		else
		{
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
	}

}
ChessMovement Cannons::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
	sf::Vector2f(0,-1),
	sf::Vector2f(1,0),
	sf::Vector2f(0,1),
	sf::Vector2f(-1,0),
	};

	struct ChessMovement chessMovement {};
	for (int i = 0;i < 4; i++)
	{
		bool findChessToEat = false;
		for (int multiple = 1;multiple <= 9;multiple++)
		{
			sf::Vector2f dxy(direction[i].x * multiple, direction[i].y * multiple);
			sf::Vector2f goalPos = boardPosition + dxy;
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
			{
				// �ਫ
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					chessMovement.validPath.push_back(goalPos);
				}
				//�������Ѥl�i�H��
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr)
				{
					multiple++;
					for (multiple;multiple <= 9;multiple++)
					{

						dxy = sf::Vector2f(direction[i].x * multiple, direction[i].y * multiple);
						goalPos = boardPosition + dxy;

						if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
						{
							//��Y
							if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
								board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
							{
								chessMovement.validPath.push_back(goalPos);
								findChessToEat = true;
								break;
							}
						}
					}
					if (findChessToEat)
						break;
				}
			}
			//�W�X�d�� ���X�j��
			else
				break;
		}
	}
	return chessMovement;
}
void Soldiers::move(Chess* chess, const Board& board)
{
	sf::Vector2f goalPos = chess->getPosition();

	//�Y�ؼЦ�m����
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
		boardPosition = goalPos;
		board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
	}
	//�Y�ؼЦ�m������
	else
	{
		//�Y�ؼЦ�m���Ѥl�s��
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
		//�Y�ؼЦ�m���Ѥl�w��
		else
		{
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = nullptr;
			boardPosition = goalPos;
			board.getBoard()[this->boardPosition.y][this->boardPosition.x] = this;
		}
	}

}
ChessMovement Soldiers::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> BlackDirection
	{
	sf::Vector2f(0,-1),
	sf::Vector2f(-1,0),
	sf::Vector2f(1,0),
	};
	const std::vector<sf::Vector2f> RedDirection
	{
	sf::Vector2f(0,1),
	sf::Vector2f(-1,0),
	sf::Vector2f(1,0),
	};
	struct ChessMovement chessMovement {};

	if (team == Team::Red)
	{
		if (boardPosition.y <= 4)
		{
			chessMovement.validPath.push_back(sf::Vector2f(0, 1) + boardPosition);
		}
		else
		{
			for (int i = 0; i < 3; i++) {
				sf::Vector2f goalPos = boardPosition + RedDirection[i];
				if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 5) {
					// �ਫ
					if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
						chessMovement.validPath.push_back(goalPos);
					}
					//�Y�ؼ�Pos�������� && ����@�� && �h�i�Y
					else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
						board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
					{
						chessMovement.validPath.push_back(goalPos);
					}
				}
			}
		}

	}
	else
	{
		if (boardPosition.y >= 5)
		{
			chessMovement.validPath.push_back(sf::Vector2f(0, -1) + boardPosition);
		}
		else
		{
			for (int i = 0; i < 3; i++) {
				sf::Vector2f goalPos = boardPosition + BlackDirection[i];
				if (8 >= goalPos.x && goalPos.x >= 0 && 4 >= goalPos.y && goalPos.y >= 0) {
					// �ਫ
					if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
						chessMovement.validPath.push_back(goalPos);
					}
					//�Y�ؼ�Pos�������� && ����@�� �h�i�Y
					else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
						board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
					{
						chessMovement.validPath.push_back(goalPos);
					}
				}
			}
		}
	}
	return chessMovement;
}
