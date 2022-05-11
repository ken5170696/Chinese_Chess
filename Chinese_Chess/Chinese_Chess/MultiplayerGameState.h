#pragma once
#include "GameHeader.h"
#include "State.h"
class MultiplayerGameState
	: public State
{
private:
	sf::RenderWindow* window;

public:
	MultiplayerGameState(StateStack& _stack, StateContext _context);
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

};