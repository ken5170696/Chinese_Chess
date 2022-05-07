#pragma once

#include "GameHeader.h"

class GameManager
{
private:
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;

public:
	GameManager();
	~GameManager();
	void run();

private:
	void initWindow();
	void initVar();
	void pullEvent();

	void processEvent();
	void update();
	void render();
};

