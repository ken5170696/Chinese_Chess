#pragma once
/* This class manage the whole program*/
#include "GameHeader.h"
#include "StateStack.h"
#include "GameState.h"
#include "MultiplayerGameState.h"
#include "MultiplayerLobbyState.h"
#include "GameServer.h"
#include "MenuState.h"
#include "PauseState.h"
#include "BlackIsCheckMate.h"
#include "RedIsCeckMate.h"
#include "BlackIsStalemate.h"
#include "RedIsStalemate.h"

class GameManager
{
private:
	StateStack stateStack;
	sf::RenderWindow window;
	FontHolder fontHolder;

public:
	GameManager();	
	~GameManager();
	void run();

private:
	static const sf::Time TimePerFrame;
	void registerStates();
	void processEvent();
	void update(sf::Time dt);
	void render();
};

