#include "State.h"

State::State(StateStack& stack, StateContext context)
	: _context(context)
{
	_stack = &stack;
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

StateContext State::getContext() const
{
	return _context;
}