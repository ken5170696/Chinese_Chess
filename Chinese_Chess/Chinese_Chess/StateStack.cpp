#include "StateStack.h"

std::unique_ptr<State> StateStack::createState(States::ID stateID)
{
	auto found = statesFactories.find(stateID);
	assert(found != statesFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for(PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			statesStack.push_back(createState(change.stateID));
			statesStack.back()->setStateID(change.stateID);
			break;
		case Pop:
			statesStack.pop_back();
			break;
		case Clear:
			statesStack.clear();
			break;
		}
	}
	mPendingList.clear();
}
StateStack::StateStack(const StateContext& context)
	: _context(context)
{

}
void StateStack::update(sf::Time dt)
{
	for (auto statesItr = statesStack.begin(); statesItr != statesStack.end(); ++statesItr)
	{
		if (!(*statesItr)->update(dt))
			return;
	}
	applyPendingChanges();
}

void StateStack::draw()
{
	for (auto statesItr = statesStack.begin(); statesItr != statesStack.end(); ++statesItr)
	{
		(*statesItr)->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto statesItr = statesStack.begin(); statesItr != statesStack.end(); ++statesItr)
	{
		if (!(*statesItr)->handleEvent(event))
			return;
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return statesStack.empty();
}

int StateStack::getStackNum() const
{
	return statesStack.size();
}

bool StateStack::inStack(States::ID stateID) const
{
	for (const auto& stackElement : statesStack)
		if (stateID == stackElement->getStateID())
			return true;

	return false;
}
