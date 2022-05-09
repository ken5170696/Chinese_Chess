#include "GameManager.h"

GameManager::GameManager()
	: playerBlack(Team::Black), playerRed(Team::Red), board()
{
	this->initVar();
	this->initWindow();
	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - board.getBoardSize().y) / 2);
	this->board.setSpritePosition(tmpPos);
	window->setFramerateLimit(144);
	this->status = Status::WaitBlackPressed;
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

		this->processEvent();
		this->update();
		this->render();
	}
}

void GameManager::whoWin(const Player& playerBlack, const Player& playerRed)
{
	if (!playerBlack.getChessList()[0]->getActive())
	{
		std::cout << "RedPlayer Win\n";
		exit(0);
	}
	if (!playerRed.getChessList()[0]->getActive())
	{
		std::cout << "BlackPlayer Win\n";
		exit(0);
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
	//std::cout << boardPosition.x << " " << boardPosition.y << "\n";
	return boardPosition;
}

void GameManager::processEvent()
{
	this->pullEvent();
}

void GameManager::update()
{
	whoWin(playerBlack, playerRed);
	showStatus();
	board.update(playerBlack, playerRed);
	for (auto chess : playerBlack.getChessList())
		chess->resetIsPressed();
	for (auto chess : playerRed.getChessList())
		chess->resetIsPressed();

	
	switch (status)
	{
	case Status::WaitBlackPressed:
	{
		for (auto& blackChess : playerBlack.getChessList())
		{
			if (!blackChess->getActive())
				continue;
			blackChess->setSpritePosition(BoardToWindowPosition(blackChess->getPosition()));
			blackChess->update(*(this->window), ev);
			if (blackChess->getIsPressed())
			{
				selectChess = blackChess;
				status = Status::BlackFindPath;
			}
		}
		for (auto& redChess : playerRed.getChessList())
		{
			redChess->setSpritePosition(BoardToWindowPosition(redChess->getPosition()));
		}
		break;
	}
	case Status::BlackFindPath:
	{
		chessMovement = std::make_unique<ChessMovement>(selectChess->findPath(this->board));
		inputClock.restart();
		if (chessMovement == nullptr)
		{
			status = Status::WaitBlackPressed;
			break;
		}
		else
		{
			Factory tmpChessfac;
			for (const auto& validPath : chessMovement.get()->validPath) {
				// create tmp chess
				if (selectChess != nullptr && selectChess->getActive()) 
				{
					Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
					tmpChess->setPosition(validPath);
					tmpChessObj.push_back(tmpChess);
				}
				else
				{
					status = Status::WaitBlackPressed;

					chessMovement.release();
					break;
				}
			}
			status = Status::WaitBlackPathPressed;
			break;
		}
		break;
	}
	case Status::WaitBlackPathPressed:
	{
		bool isPressed = false, validPressed = false;
		
		for (auto& tmpChess : tmpChessObj) {
			tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
			tmpChess->update(*(this->window), ev);
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				isPressed = true;
				if (tmpChess->getIsPressed()) 
				{
					validPressed = true;
					selectPathChess = tmpChess;
					break;
				}
			}
			tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
		}
		if (isPressed && validPressed)
		{
			status = Status::BlackMove;
			chessMovement.release();
			break;
		}
		else if(isPressed && !validPressed)
		{
			status = Status::WaitBlackPressed;
			for (auto& tmpChess : tmpChessObj)
			{
				delete tmpChess;
			}
			tmpChessObj.clear();
			chessMovement.release();
			break;
		}
		else
		{ }
		break;
	}
	case Status::BlackMove:
	{
		if (inputClock.getElapsedTime().asMilliseconds() > DELAY_TIME)
		{
			bool validPressed = false;
			inputClock.restart();
			for (auto& tmpChess : tmpChessObj)
			{
				if (selectPathChess == tmpChess)
					validPressed = true;
			}

			if (validPressed == false)
			{
				tmpChessObj.clear();
				status = Status::WaitBlackPressed;
				break;
			}
			else
			{
				for (auto& tmpChess : tmpChessObj)
				{
					if (tmpChess->getIsPressed())
						selectChess->move(tmpChess, board);
					delete tmpChess;
				}
				tmpChessObj.clear();
				status = Status::WaitRedPressed;
				chessMovement.release();
				break;
			}
		}
		break;
	}
	case Status::WaitRedPressed:
	{
		for (auto& blackChess : playerBlack.getChessList())
		{
			blackChess->setSpritePosition(BoardToWindowPosition(blackChess->getPosition()));
		}
		for (auto& redChess : playerRed.getChessList())
		{
			if (!redChess->getActive())
				continue;
			redChess->setSpritePosition(BoardToWindowPosition(redChess->getPosition()));
			redChess->update(*(this->window), ev);
			if (redChess->getIsPressed())
			{
				selectChess = redChess;
				status = Status::RedFindPath;
			}
		}
		break;
	}
	case Status::RedFindPath:
	{
		chessMovement = std::make_unique<ChessMovement>(selectChess->findPath(this->board));
		inputClock.restart();
		if (chessMovement == nullptr)
		{
			status = Status::WaitRedPressed;
			break;
		}
		else
		{
			Factory tmpChessfac;
			for (const auto& validPath : chessMovement.get()->validPath) {
				// create tmp chess
				if (selectChess != nullptr && selectChess->getActive())
				{
					Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
					tmpChess->setPosition(validPath);
					tmpChessObj.push_back(tmpChess);
				}
				else
				{
					status = Status::WaitRedPressed;
					chessMovement.release();
					break;
				}
			}
			status = Status::WaitRedPathPressed;
			break;
		}
		break;
	}
	case Status::WaitRedPathPressed:
	{
		bool isPressed = false, validPressed = false;

		for (auto& tmpChess : tmpChessObj) {
			tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
			tmpChess->update(*(this->window), ev);
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				isPressed = true;
				if (tmpChess->getIsPressed())
				{
					validPressed = true;
					selectPathChess = tmpChess;
					break;
				}
			}
			tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
		}
		if (isPressed && validPressed)
		{
			status = Status::RedMove;
			chessMovement.release();
			break;
		}
		else if (isPressed && !validPressed)
		{
			status = Status::WaitRedPressed;
			for (auto& tmpChess : tmpChessObj)
			{
				delete tmpChess;
			}
			tmpChessObj.clear();
			chessMovement.release();
			break;
		}
		else
		{
		}
		break;
	}
	case Status::RedMove:
	{
		if (inputClock.getElapsedTime().asMilliseconds() > DELAY_TIME)
		{
			bool validPressed = false;
			inputClock.restart();
			for (auto& tmpChess : tmpChessObj)
			{
				if (selectPathChess == tmpChess)
					validPressed = true;
			}

			if (validPressed == false)
			{
				tmpChessObj.clear();
				status = Status::WaitRedPressed;
				break;
			}
			else
			{
				for (auto& tmpChess : tmpChessObj)
				{
					if (tmpChess->getIsPressed())
						selectChess->move(tmpChess, board);
					delete tmpChess;
				}
				tmpChessObj.clear();
				status = Status::WaitBlackPressed;
				chessMovement.release();
				break;
			}
		}
		break;
	}


	}

}
void GameManager::render()
{

	window->clear(sf::Color::White);

	/* Drawing */
	window->draw(board.getSprite());
	for (auto& tmpChess : playerBlack.getChessList()) {
		if (tmpChess->getActive())
			window->draw(tmpChess->getSprite());
	}
	for (auto& tmpChess : playerRed.getChessList()) {
		if (tmpChess->getActive())
			window->draw(tmpChess->getSprite());
	}

	for (auto& tmpChess : tmpChessObj) {
		window->draw(tmpChess->getSprite());
	}
	window->display();
}

void GameManager::showStatus()
{
	if(status == Status::WaitBlackPressed)
		std::cout << "1";
	else if (status == Status::BlackFindPath)
		std::cout << "2";
	else if (status == Status::WaitBlackPathPressed)
		std::cout << "3";
	else if (status == Status::BlackMove)
		std::cout << "4";
	else if (status == Status::WaitRedPressed)
		std::cout << "5";
	else if (status == Status::RedFindPath)
		std::cout << "6";
	else if (status == Status::WaitRedPathPressed)
		std::cout << "7";
	else if (status == Status::RedMove)
		std::cout << "8";
	std::cout << "\n";
}
