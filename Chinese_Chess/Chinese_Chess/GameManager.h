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
	Status status;

	std::unique_ptr<ChessMovement> chessMovement;
	std::vector<Chess*> tmpChessObj;
	Chess* selectChess;
	Chess* selectPathChess;
	sf::Clock inputClock;

public:
	GameManager();
	~GameManager();
	void run();

private:
	void whoWin(const Player& playerBlack, const Player& playerRed);

	void initWindow();
	void initVar();
	void pullEvent();

	sf::Vector2f BoardToWindowPosition(sf::Vector2f boardPosition);
	sf::Vector2f WindowToBoardPosition(sf::Vector2f windowPosition);
	
	void processEvent();
	void update();
	void render();

	void showStatus();
};

