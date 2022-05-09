#include "GameManager.h"

GameManager::GameManager()
	: playerBlack(Team::Black), playerRed(Team::Red), board()
{
	this->initVar();
	this->initWindow();
	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - board.getBoardSize().y) / 2);
	this->board.setSpritePosition(tmpPos);
	window->setFramerateLimit(10);
	this->status = Status::WaitForBlack;
	board.update(playerBlack, playerRed);
}

GameManager::~GameManager()
{
	delete window;
}

void GameManager::run()
{

	while (this->window->isOpen())
	{
		this->update();
		this->processEvent();
		this->render();
	}
}

void GameManager::initWindow()
{
	this->videoMode.width = WINDOW_RESOLUTION_WIDTH;
	this->videoMode.height = WINDOW_RESOLUTION_HEIGHT;
	this->window = new sf::RenderWindow(videoMode, "Game1", sf::Style::Close | sf::Style::Titlebar);

}

void GameManager::initVar()
{
	this->window = nullptr;
}

void GameManager::pullEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

sf::Vector2f GameManager::BoardToWindowPosition(sf::Vector2f boardArrPosition)
{
	sf::Vector2f windowPosition;
	int x = (board.getBoardSize().x / 8) * boardArrPosition.x + board.getSprite().getPosition().x;
	int y = (board.getBoardSize().y / 9) * boardArrPosition.y + board.getSprite().getPosition().y;
	windowPosition = sf::Vector2f(x, y);
	return windowPosition;
}

sf::Vector2f GameManager::WindowToBoardPosition(sf::Vector2f windowPosition)
{
	sf::Vector2f boardPosition;
	int x = (windowPosition.x - (board.getSprite().getPosition().x - board.getBoardSize().x / 16)) / (board.getBoardSize().x / 8);
	int y = (windowPosition.y - (board.getSprite().getPosition().y - board.getBoardSize().x / 18)) / (board.getBoardSize().y / 9);
	boardPosition.x = x;
	boardPosition.y = y;
	std::cout << boardPosition.x << " " << boardPosition.y << "\n";
	return boardPosition;
}

void GameManager::processEvent()
{
	this->pullEvent();
}

void GameManager::update()
{
	// update board infomation
	board.update(playerBlack, playerRed);

	for (auto chess : playerBlack.getChessList())
		chess->resetIsPressed();
	for (auto chess : playerRed.getChessList())
		chess->resetIsPressed();
	/*for (auto chess : playerBlack.getChessList())
	{
		std::cout << chess->getId() << ": " << chess->getIsPressed() << std::endl;
	}
	for (auto chess : playerRed.getChessList())
	{
		std::cout << chess->getId() << ": " << chess->getIsPressed() << std::endl;
	}*/
	for (auto& blackChess : playerBlack.getChessList()) {
		blackChess->setSpritePosition(BoardToWindowPosition(blackChess->getPosition()));
		switch (status)
		{
		case Status::WaitForBlack:
		{
			//std::cout << "status : 1\n";
			blackChess->update(*(this->window), ev);
			if (blackChess->getIsPressed()) {
				if (chessMovement == nullptr) {
					selectChess = blackChess;
					chessMovement = std::make_unique<ChessMovement>(blackChess->findPath(this->board));
					status = Status::BlackChessPressed;
					inputClock.restart();
				}
			}
			break;
		}
		case Status::BlackChessPressed:
		{
			//std::cout << "status : 2\n";
			if (chessMovement != nullptr) {
				Factory tmpChessfac;
				for (const auto& validPath : chessMovement.get()->validPath) {
					// create tmp chess
					if (selectChess != nullptr) {
						Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
						tmpChess->setPosition(validPath);
						tmpChessObj.push_back(tmpChess);
					}
				}
				for (const auto& validPath : chessMovement.get()->validToEat) {

				}
				chessMovement.release();
			}
			//else 
			bool isPressed = false, validPressed = false;
			for (auto& tmpChess : tmpChessObj) {
				tmpChess->update(*(this->window), ev);
				if (ev.type == ev.MouseButtonPressed) {
					isPressed = true;
					if (tmpChess->getIsPressed()) {
						validPressed = true;
						break;
					}
				}
				tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
			}
			if (inputClock.getElapsedTime().asMilliseconds() > 10 && isPressed == true) {
				inputClock.restart();
				if (validPressed == false) {
					// cancel move
					for (auto& tmpChess : tmpChessObj) {
						delete tmpChess;
					}
					tmpChessObj.clear();
					status = Status::WaitForBlack;
				}
				else {
					for (auto& tmpChess : tmpChessObj) {
						if (tmpChess->getIsPressed())
							selectChess->move(tmpChess->getPosition(), board);
						delete tmpChess;
					}
					tmpChessObj.clear();
					status = Status::WaitForRed;
				}
			}
			break;
		}
		}

		for (auto& redChess : playerRed.getChessList()) {
			redChess->setSpritePosition(BoardToWindowPosition(redChess->getPosition()));
			switch (status)
			{
			case Status::WaitForRed:
			{
				//std::cout << "status : 3\n";
				redChess->update(*(this->window), ev);
				if (redChess->getIsPressed()) {
					if (chessMovement == nullptr) {
						selectChess = redChess;
						chessMovement = std::make_unique<ChessMovement>(redChess->findPath(this->board));
						status = Status::RedChessPressed;
						inputClock.restart();
					}
				}
				break;
			}
			case Status::RedChessPressed:
			{

				//std::cout << "status : 4\n";
				if (chessMovement != nullptr) {
					Factory tmpChessfac;
					for (const auto& validPath : chessMovement.get()->validPath) {
						// create tmp chess
						if (selectChess != nullptr) {
							Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
							tmpChess->setPosition(validPath);
							tmpChessObj.push_back(tmpChess);
						}
					}
					for (const auto& validPath : chessMovement.get()->validToEat) {

					}
					chessMovement.release();
				}
				//else 

				bool isPressed = false, validPressed = false;
				for (auto& tmpChess : tmpChessObj) {
					tmpChess->update(*(this->window), ev);
					if (ev.type == ev.MouseButtonPressed) {
						isPressed = true;
						if (tmpChess->getIsPressed()) {
							validPressed = true;
							break;
						}
					}
					tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
				}
				if (inputClock.getElapsedTime().asMilliseconds() > 20 && isPressed == true) {
					inputClock.restart();
					if (validPressed == false) {
						// cancel move
						for (auto& tmpChess : tmpChessObj) {
							delete tmpChess;
						}
						tmpChessObj.clear();
						status = Status::WaitForRed;
					}
					else {
						for (auto& tmpChess : tmpChessObj) {
							if (tmpChess->getIsPressed())
								selectChess->move(tmpChess->getPosition(),board);
							delete tmpChess;
						}
						tmpChessObj.clear();
						status = Status::WaitForBlack;
					}

				}
				break;
			}
			}
		}
	}

}


void GameManager::render()
{

	window->clear(sf::Color::White);

	/* Drawing */
	window->draw(board.getSprite());
	for (auto& tmpChess : playerBlack.getChessList()) {
		window->draw(tmpChess->getSprite());
	}
	for (auto& tmpChess : playerRed.getChessList()) {
		window->draw(tmpChess->getSprite());
	}

	for (auto& tmpChess : tmpChessObj) {
		window->draw(tmpChess->getSprite());
	}
	window->display();
}
