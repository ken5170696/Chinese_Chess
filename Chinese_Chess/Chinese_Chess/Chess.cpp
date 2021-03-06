#include "Chess.h"

void Chess::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (active) {
		target.draw(sprite, states);
	}
}
Chess::Chess(const Team& _team, int _id)
	: chessCharacter()
{
	id = _id;
	active = true;
	team = _team;
	sprite.setScale(CHESS_IMG_SCALE, CHESS_IMG_SCALE);

	if (id == -1)
		sprite.setColor(sf::Color(230, 0, 0, 170));
}
void Chess::update(const sf::RenderWindow& win)
{
	if (active) {
		// update button appearance by status
		sf::Vector2i mousePos = sf::Mouse::getPosition(win);
		if (isHover()) {
			sprite.setScale(CHESS_IMG_SCALE + 0.01, CHESS_IMG_SCALE + 0.01);
		}
		else {
			sprite.setScale(CHESS_IMG_SCALE, CHESS_IMG_SCALE);
		}
	}
}
void Chess::handleEvent(sf::RenderWindow& win)
{
	if (active) {
		buttonStatus = 0;
		if (sprite.getGlobalBounds().contains(win.mapPixelToCoords(sf::Mouse::getPosition(win)))) {
			buttonStatus += unsigned int(ButtonStatus::hover);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				buttonStatus += unsigned int(ButtonStatus::pressed);
			}
		}
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

void King::move(Chess* goalChess, const Board& board)
{
	sf::Vector2f goalPos = goalChess->getBoardPosition();

	//?Y???????m????
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		boardPosition = goalPos;
	}
	//?Y???????m??????
	else
	{
		//?Y???????m?????l?s??
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			boardPosition = goalPos;
		}
		//?Y???????m?????l?w??
		else
		{
			boardPosition = goalPos;
		}
	}

}
std::vector<sf::Vector2f> King::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(0,-1),
		sf::Vector2f(-1,0),
		sf::Vector2f(1,0),
		sf::Vector2f(0,1),
	};
	std::vector<sf::Vector2f> validPath;
	for (int i = 0; i < 4; i++) {
		sf::Vector2f goalPos = boardPosition + direction[i];
		if (team == Team::Red) {
			// ?????b?E?c??
			if (5 >= goalPos.x && goalPos.x >= 3 && 2 >= goalPos.y && goalPos.y >= 0) {
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?Y????Pos???????? && ???????@?? && ?????????L???? ?h?i?Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() != Characters::Soldiers)
				{
					validPath.push_back(goalPos);
				}
			}
		}
		else {
			// ?????b?E?c??
			if (5 >= goalPos.x && goalPos.x >= 3 && 9 >= goalPos.y && goalPos.y >= 7) {
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?Y????Pos???????? && ???????@?? && ?????????L???? ?h?i?Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() != Characters::Soldiers) {
					validPath.push_back(goalPos);
				}
			}
		}
	}
	if (team == Team::Red)
	{
		for (int i = 1;i <= 9;i++)
		{
			sf::Vector2f dxy(direction[3].x * i, direction[3].y * i);
			sf::Vector2f goalPos = boardPosition + dxy;
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
			{
				if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() == Characters::King)
				{
					validPath.push_back(goalPos);
				}
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr)
				{
					break;
				}
			}
			else {
				break;
			}
		}
	}
	else
	{
		for (int i = 1;i <= 10;i++)
		{
			sf::Vector2f dxy(direction[0].x * i, direction[0].y * i);
			sf::Vector2f goalPos = boardPosition + dxy;
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
			{
				if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getCharacters() == Characters::King)
				{
					validPath.push_back(goalPos);
				}
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}/**/
	return validPath;
}
void Advisors::move(Chess* goalChess, const Board& board)
{
	sf::Vector2f goalPos = goalChess->getBoardPosition();

	//?Y???????m????
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		boardPosition = goalPos;
	}
	//?Y???????m??????
	else
	{
		//?Y???????m?????l?s??
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			boardPosition = goalPos;
		}
		//?Y???????m?????l?w??
		else
		{
			boardPosition = goalPos;
		}
	}


}
std::vector<sf::Vector2f> Advisors::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(-1,-1),
		sf::Vector2f(1,1),
		sf::Vector2f(1,-1),
		sf::Vector2f(-1,1),
	};
	std::vector<sf::Vector2f> validPath;
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f goalPos = boardPosition + direction[i];
		if (team == Team::Red) {
			// ?????b?E?c??
			if (5 >= goalPos.x && goalPos.x >= 3 && 2 >= goalPos.y && goalPos.y >= 0) {
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?Y????Pos???????? && ???????@?? ?h?i?Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam()) {
					validPath.push_back(goalPos);
				}
			}
		}
		else {
			// ?????b?E?c??
			if (5 >= goalPos.x && goalPos.x >= 3 && 9 >= goalPos.y && goalPos.y >= 7) {
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?Y????Pos???????? && ???????@?? ?h?i?Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam()) {
					validPath.push_back(goalPos);
				}
			}
		}

	}
	return validPath;
}
void Minister::move(Chess* goalChess, const Board& board)
{
	sf::Vector2f goalPos = goalChess->getBoardPosition();

	//?Y???????m????
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		boardPosition = goalPos;
	}
	//?Y???????m??????
	else
	{
		//?Y???????m?????l?s??
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			boardPosition = goalPos;
		}
		//?Y???????m?????l?w??
		else
		{
			boardPosition = goalPos;
		}
	}

}
std::vector<sf::Vector2f> Minister::findPath(const Board& board)
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
	std::vector<sf::Vector2f> validPath;
	for (int i = 0; i < 4; i++) {
		sf::Vector2f goalPos = boardPosition + direction[i];
		sf::Vector2f throughPos = boardPosition + throughDirection[i];
		if (team == Team::Red) {
			// ???????V?L???e?~??
			if (8 >= goalPos.x && goalPos.x >= 0 && 4 >= goalPos.y && goalPos.y >= 0) {
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr && board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?Y????Pos???????? && ???????@?? && ???W?S???l ?h?i?Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					validPath.push_back(goalPos);;
				}
			}
		}
		else {
			// ???????V?L???e?~??
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 5) {
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?Y????Pos???????? && ???????@?? && ???W?S???l ?h?i?Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
					board.getBoard()[throughPos.y][throughPos.x] == nullptr) {
					validPath.push_back(goalPos);;
				}
			}
		}

	}

	return validPath;
}
void Chariots::move(Chess* goalChess, const Board& board)
{
	sf::Vector2f goalPos = goalChess->getBoardPosition();

	//?Y???????m????
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		boardPosition = goalPos;
	}
	//?Y???????m??????
	else
	{
		//?Y???????m?????l?s??
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			boardPosition = goalPos;
		}
		//?Y???????m?????l?w??
		else
		{
			boardPosition = goalPos;
		}
	}


}
std::vector<sf::Vector2f> Chariots::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
		sf::Vector2f(0,-1),
		sf::Vector2f(1,0),
		sf::Vector2f(0,1),
		sf::Vector2f(-1,0),
	};

	std::vector<sf::Vector2f> validPath;
	for (int i = 0;i < 4; i++)
	{
		for (int multiple = 1;multiple <= 9;multiple++)
		{
			sf::Vector2f dxy(direction[i].x * multiple, direction[i].y * multiple);
			sf::Vector2f goalPos = boardPosition + dxy;
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
			{
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?Y????Pos???????? && ???????@?? ?h?i?Y
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
					board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
				{
					validPath.push_back(goalPos);
					break;
				}
				//?Y????Pos???????? && ?????@?? ???X?j??
				else
					break;
			}
			//?W?X?d?? ???X?j??
			else
				break;
		}
	}
	return validPath;
}
void Knights::move(Chess* goalChess, const Board& board)
{
	sf::Vector2f goalPos = goalChess->getBoardPosition();

	//?Y???????m????
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		boardPosition = goalPos;
	}
	//?Y???????m??????
	else
	{
		//?Y???????m?????l?s??
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			boardPosition = goalPos;
		}
		//?Y???????m?????l?w??
		else
		{
			boardPosition = goalPos;
		}
	}


}
std::vector<sf::Vector2f> Knights::findPath(const Board& board)
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
	std::vector<sf::Vector2f> validPath;
	for (int i = 0; i < 8; i++)
	{
		sf::Vector2f goalPos = boardPosition + direction[i];
		sf::Vector2f throughPos = boardPosition + throughDirection[i];

		if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
		{
			// ????
			if (board.getBoard()[goalPos.y][goalPos.x] == nullptr && board.getBoard()[throughPos.y][throughPos.x] == nullptr)
			{
				validPath.push_back(goalPos);
			}
			//?Y????Pos???????? && ???????@?? && ???W?S???l ?h?i?Y
			else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
				board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam() &&
				board.getBoard()[throughPos.y][throughPos.x] == nullptr)
			{
				validPath.push_back(goalPos);;
			}
		}
	}

	return validPath;
}
void Cannons::move(Chess* goalChess, const Board& board)
{
	sf::Vector2f goalPos = goalChess->getBoardPosition();

	//?Y???????m????
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		boardPosition = goalPos;
	}
	//?Y???????m??????
	else
	{
		//?Y???????m?????l?s??
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			boardPosition = goalPos;
		}
		//?Y???????m?????l?w??
		else
		{
			boardPosition = goalPos;
		}
	}


}
std::vector<sf::Vector2f> Cannons::findPath(const Board& board)
{
	const std::vector<sf::Vector2f> direction{
	sf::Vector2f(0,-1),
	sf::Vector2f(1,0),
	sf::Vector2f(0,1),
	sf::Vector2f(-1,0),
	};

	std::vector<sf::Vector2f> validPath;
	for (int i = 0;i < 4; i++)
	{
		bool findChessToEat = false;
		for (int multiple = 1;multiple <= 9;multiple++)
		{
			sf::Vector2f dxy(direction[i].x * multiple, direction[i].y * multiple);
			sf::Vector2f goalPos = boardPosition + dxy;
			if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
			{
				// ????
				if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
					validPath.push_back(goalPos);
				}
				//?????????l?i?H??
				else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr)
				{
					multiple++;
					for (multiple;multiple <= 9;multiple++)
					{

						dxy = sf::Vector2f(direction[i].x * multiple, direction[i].y * multiple);
						goalPos = boardPosition + dxy;

						if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 0)
						{
							//???Y
							if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
								board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
							{
								validPath.push_back(goalPos);
								findChessToEat = true;
								break;
							}
							else if(board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
									board.getBoard()[goalPos.y][goalPos.x]->getTeam() == this->getTeam())
							{
								findChessToEat = true;
									break;
							}
						}
					}
					if (findChessToEat)
						break;
				}
			}
			//?W?X?d?? ???X?j??
			else
				break;
		}
	}
	return validPath;
}
void Soldiers::move(Chess* goalChess, const Board& board)
{
	sf::Vector2f goalPos = goalChess->getBoardPosition();

	//?Y???????m????
	if (board.getBoard()[goalPos.y][goalPos.x] == nullptr)
	{
		boardPosition = goalPos;
	}
	//?Y???????m??????
	else
	{
		//?Y???????m?????l?s??
		if (board.getBoard()[goalPos.y][goalPos.x]->getActive())
		{
			board.getBoard()[goalPos.y][goalPos.x]->setActive(false);
			boardPosition = goalPos;
		}
		//?Y???????m?????l?w??
		else
		{
			boardPosition = goalPos;
		}
	}

}
std::vector<sf::Vector2f> Soldiers::findPath(const Board& board)
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
	std::vector<sf::Vector2f> validPath;

	if (team == Team::Red)
	{
		if (boardPosition.y <= 4)
		{
			validPath.push_back(sf::Vector2f(0, 1) + boardPosition);
		}
		else
		{
			for (int i = 0; i < 3; i++) {
				sf::Vector2f goalPos = boardPosition + RedDirection[i];
				if (8 >= goalPos.x && goalPos.x >= 0 && 9 >= goalPos.y && goalPos.y >= 5) {
					// ????
					if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
						validPath.push_back(goalPos);
					}
					//?Y????Pos???????? && ???????@?? && ?h?i?Y
					else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
						board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
					{
						validPath.push_back(goalPos);
					}
				}
			}
		}

	}
	else
	{
		if (boardPosition.y >= 5)
		{
			validPath.push_back(sf::Vector2f(0, -1) + boardPosition);
		}
		else
		{
			for (int i = 0; i < 3; i++) {
				sf::Vector2f goalPos = boardPosition + BlackDirection[i];
				if (8 >= goalPos.x && goalPos.x >= 0 && 4 >= goalPos.y && goalPos.y >= 0) {
					// ????
					if (board.getBoard()[goalPos.y][goalPos.x] == nullptr) {
						validPath.push_back(goalPos);
					}
					//?Y????Pos???????? && ???????@?? ?h?i?Y
					else if (board.getBoard()[goalPos.y][goalPos.x] != nullptr &&
						board.getBoard()[goalPos.y][goalPos.x]->getTeam() != this->getTeam())
					{
						validPath.push_back(goalPos);
					}
				}
			}
		}
	}
	return validPath;
}