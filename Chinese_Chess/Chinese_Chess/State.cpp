#include "State.h"

State::State(StateStack& stack, StateContext context)
	: _context(context)
{
	_stack = &stack;
}
void State::setStateID(States::ID _stateID)
{
	stateID = _stateID;
}
States::ID State::getStateID() const
{
	return stateID;
}
void State::requestStackPush(States::ID stateID)
{
	_stack->pushState(stateID);
}

void State::requestStackPop()
{
	_stack->popState();
}

void State::requestStateClear()
{
	_stack->clearStates();
}

int State::getStackNum() const
{
	return _stack->getStackNum();
}

bool State::inStack(States::ID stateID) const
{
	return _stack->inStack(stateID);
}

StateContext State::getContext() const
{
	return _context;
}