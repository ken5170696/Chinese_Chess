#include "GameManager.h"

GameManager::GameManager()
	: playerBlack(Team::Black), playerRed(Team::Red), board()
{
	this->initVar();
	this->initWindow();
	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - board.getBoardSize().y) / 2);
	this->board.setSpritePosition(tmpPos);

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
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0, 0, ev.size.width, ev.size.height)));
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

void GameManager::processEvent()
{
}

void GameManager::update()
{
	this->pullEvent();
	for (auto& tmpChess : playerBlack.getChessList()) {
		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
	}
	for (auto& tmpChess : playerRed.getChessList()) {
		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
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

	window->display();
}
