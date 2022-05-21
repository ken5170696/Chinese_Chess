#pragma once
class StateStack;
#include <memory>

#include "GameHeader.h"
#include "StateStack.h"
// Base class about every state
class State
{
public:
	State(StateStack& stack, StateContext context);
	/*virtual ~State();*/
	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;
	void setStateID(States::ID _stateID);
	States::ID getStateID() const;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();
	int getStackNum() const;
	bool inStack(States::ID stateID) const;
	StateContext getContext() const;

private:
	States::ID stateID;
	StateStack	* _stack;
	StateContext _context;
};