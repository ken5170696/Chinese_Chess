#pragma once
/* This class manage the whole program*/
#include "GameHeader.h"
#include "StateStack.h"
#include "GameState.h"
#include "MultiplayerGameState.h"
#include "MutiplayerMenu.h"
#include "GameServer.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameMessage.h"

class GameManager
{
private:
	StateStack stateStack;
	sf::RenderWindow window;
	FontHolder fontHolder;
	TextureHolder textureHolder;
	bool pause;
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