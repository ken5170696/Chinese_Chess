#include "GameManager.h"

GameManager::GameManager()
{
	this->initVar();
	this->initWindow();
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
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(videoMode, "Game1", sf::Style::Titlebar | sf::Style::Close);
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

		}
	}
}

void GameManager::processEvent()
{
}

void GameManager::update()
{
	this->pullEvent();
}

void GameManager::render()
{
	window->clear(sf::Color::White);
	window->display();
}
