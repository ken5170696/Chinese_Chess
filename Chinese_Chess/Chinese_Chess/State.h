#pragma once
class StateStack;
#include <memory>

#include "GameHeader.h"
#include "StateStack.h"

class State
{
public:
	State(StateStack& stack, StateContext context);
	/*virtual ~State();*/
	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();
	int getStackNum() const;
	StateContext getContext() const;

private:
	StateStack* _stack;
	StateContext _context;
};