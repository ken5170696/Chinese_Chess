#pragma once
/* This class manage the whole program*/
#include "GameHeader.h"
#include "StateStack.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
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

