#include "GameManager.h"

Game::Game()
{
	this->initVar();
	this->initWindow();
}

Game::~Game()
{
	delete window;
}

void Game::initWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(videoMode, "Game1", sf::Style::Titlebar | sf::Style::Close);
}

void Game::initVar()
{
	this->window = nullptr;
}

void Game::pullEvent()
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

bool Game::windowIsOpen()
{
	return this->window->isOpen();
}

void Game::update()
{
	this->pullEvent();
}

void Game::render()
{
	window->clear();
	window->display();
}
