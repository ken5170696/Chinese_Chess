#pragma once

#include "GameHeader.h"
#include "Player.h"
#include "Board.h"

class GameManager
{

private:
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::CircleShape cir;
	
private:
	Player playerBlack;
	Player playerRed;
	Board board;

public:
	GameManager();
	~GameManager();
	void run();

private:
	void initWindow();
	void initVar();
	void pullEvent();

	sf::Vector2f BoardToWindowPosition(sf::Vector2f boardPosition);

	void processEvent();
	void update();
	void render();
};

