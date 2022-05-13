#pragma once
class State;
#include <utility>
#include <functional>
#include <map>
#include <assert.h>
#include "State.h"
/* State Manager */
// load state to stack
// game, pause
class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

private:
	struct PendingChange
	{
		PendingChange(Action _action, States::ID _stateID) {
			action = _action;
			stateID = _stateID;
		};
		PendingChange(Action _action) {
			action = _action;
			stateID = States::ID::None;
		};
		Action action;
		States::ID stateID;
	};
private:
	StateContext _context;
	std::vector<std::unique_ptr<State>> statesStack;
	std::vector<PendingChange> mPendingList;
	std::map<States::ID, std::function<std::unique_ptr<State>()>> statesFactories;

public:
	StateStack(const StateContext& context);
	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);
	void pushState(States::ID stateID);
	void popState();
	void clearStates();
	bool isEmpty() const;
	int getStackNum() const;
	template <typename T>
	void registerState(States::ID stateID);

private:
	std::unique_ptr<State> createState(States::ID stateID);
	void applyPendingChanges();
};

template<typename T>
void StateStack::registerState(States::ID stateID)
{
	statesFactories[stateID] = [this]()
	{
		return std::unique_ptr<State>(new T(*this, _context));
	};
}
