#include "GameManager.h"

GameManager::GameManager()
	: playerBlack(Team::Black), playerRed(Team::Red), board()
{
	this->initVar();
	this->initWindow();
	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - board.getBoardSize().y) / 2);
	this->board.setSpritePosition(tmpPos);
	window->setFramerateLimit(144);
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
	int x = (board.getBoardSize().x / 8)* boardArrPosition.x + board.getSprite().getPosition().x;
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

	for (auto& tmpChess : playerBlack.getChessList()) {
		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
		switch (status)
		{
		case Status::WaitForBlack:
		{
			tmpChess->update(*(this->window), ev);
			if (tmpChess->getIsPressed()) {
				if (chessMovement == nullptr) {
					selectChess = tmpChess;
					chessMovement = std::make_unique<ChessMovement>(tmpChess->findPath(this->board));
					status = Status::BlackChessPressed;
					inputClock.restart();
				}
			}
			break;
		}
		case Status::BlackChessPressed:
		{
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
			if (inputClock.getElapsedTime().asMilliseconds() > 50 && isPressed == true) {
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
					// move chess
				}
			}
			break;
		}
		case Status::BlackChessPathPressed:
		{

			break;
		}
		case Status::BlackMove:
		{

			break;
		}
		}

	}
	for (auto& tmpChess : playerRed.getChessList()) {
		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
		switch (status)
		{
		case Status::WaitForRed:
		{
			tmpChess->update(*(this->window), ev);
			if (tmpChess->getIsPressed())
				status = Status::RedChessPressed;
			break;
		}
		case Status::RedChessPressed:
		{

			break;
		}
		case Status::RedChessPathPressed:
		{

			break;
		}
		case Status::RedMove:
		{

			break;
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
